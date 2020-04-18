/**
  *********************************************************************************************************
  * @file    radio_hal_rf.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-02
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "radio_hal_app.h"
#include "radio_hal_rf.h"
#include "radio_hal_wrap.h"
#include "radio_core.h"
#include "radio_comm.h"
#include "si446x_api_lib.h"
#include "delay.h"
#include "usart.h"

#if SI4438_TYPE == SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#endif
#if SI4438_TYPE == SI4438_C2
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif

#define RADIO_NRESET_COUNT		3
#define RADIO_CONFIG_TIMER		10000

typedef enum _radio_trf_sendcode
{
	rTRF_Sendover				= 0U,
	rTRF_Sending				= 1U,
} radio_trf_sendcode;

typedef enum _radio_trf_sendtype
{
	rTRF_WaitNo				= 0U,
	rTRF_WaitOver				= 1U,
} radio_trf_sendtype;

typedef enum _radio_trf_check
{
	rTRF_Check_Fail			= 0U,
	rTRF_Check_Success			= 1U,
} radio_trf_check;

static u8 radio_status = rTRF_ERROR;
static u8 radio_inited = rTRF_Uninited;
static u8 radio_channel = RADIO_RF_CHANNEL1;

static u8 radio_Packet_len;
static u8 radio_Data_sending = rTRF_Sending;
static u8 radio_Wait_enable = rTRF_WaitOver;

static const u8 Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;

/**********************************************************************************************************
 @Function		static void Radio_Hal_RF_Port_Init(void)
 @Description 		Radio_Hal_RF_Port_Init							: Radio RF 引脚初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
static void Radio_Hal_RF_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* Radio RF SDN => PB04 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN, RADIO_SI4438_SDN_AF);
	
	/* Radio RF NSS => PA15 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, RADIO_SI4438_NSS_AF);
	
	/* Radio RF IRQ => PB10 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioAHB;
	Gpio_Init(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_AF);
	
	/* Radio RF Enable IRQn */
	EnableNvic(RADIO_SI4438_IRQ_Channel, RADIO_SI4438_IRQ_Level, TRUE);
	
	Radio_Hal_RF_Interrupt_Disable();
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interface_Init(void)
 @Description 		Radio_Hal_RF_Interface_Init						: Radio RF 接口初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interface_Init(void)
{
	/* Radio Port (SDN/NSS/IRQ) Init */
	Radio_Hal_RF_Port_Init();
	
	/* Radio NSS = 1 SPIx Disable */
	Radio_Hal_Wrapper_nSELAssert();
	
	/* Radio SDN = 0 SI4438 Working */
	Radio_Hal_Wrapper_ShutdownDeassert();
	
	/* Radio SPIx Init */
	Radio_Hal_Wrapper_Init();
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Enable(void)
 @Description 		Radio_Hal_RF_Interrupt_Enable						: Radio RF 中断引脚使能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Enable(void)
{
	Gpio_EnableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_Mode);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Disable(void)
 @Description 		Radio_Hal_RF_Interrupt_Disable					: Radio RF 中断引脚失能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Disable(void)
{
	Gpio_DisableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_Mode);
}

/**********************************************************************************************************
 @Function		static char Radio_Hal_RF_ResetChip(void)
 @Description 		Radio_Hal_RF_ResetChip							: Radio RF 复位检查芯片
 @Input			void
 @Return		  	errcode
**********************************************************************************************************/
static char Radio_Hal_RF_ResetChip(void)
{
	int nCount;
	
	for (nCount = 0; nCount < RADIO_NRESET_COUNT; nCount++) {
		
		radio_core_PowerUp();
		
		si446x_part_info();
		
		if (Si446xCmd.PART_INFO.PART != 0x4438) {
			radio_status = rTRF_ERROR;
			radio_inited = rTRF_Uninited;
		}
		else {
			radio_status = rTRF_OK;
			radio_inited = rTRF_Isinited;
			break;
		}
	}
	
	return radio_status;
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Init(void)
 @Description 		Radio_Hal_RF_Init								: Radio RF 初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Init(void)
{
	timeMeterTypeDef radioRFTimer;
	
	/* step 0: radio interface init */
	Radio_Hal_RF_Interface_Init();
	
	/* step 1: radio reset and check chip */
	Radio_Hal_RF_ResetChip();
	
	if (radio_status != rTRF_OK) return;
	
	HC32_TimeMeter_CountdownMS(&radioRFTimer, RADIO_CONFIG_TIMER);
	
	/* step 2: radio set up */
	while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array)) {
		radio_core_PowerUp();
		if (HC32_TimeMeter_IsExpiredMS(&radioRFTimer)) {
			radio_status = rTRF_ERROR;
			radio_inited = rTRF_Uninited;
			return;
		}
	}
	
	/* step 3: radio get the chip's Interrupt status/pending flags form the radio and clear flags if requested */
	si446x_get_int_status(0u, 0u, 0u);
	
	/* step 4: radio set the rf chip to rx state */
	radio_core_StartRX(radio_channel, 0);
	
	/* step 6: radio enable interrupt */
	Radio_Hal_RF_Interrupt_Enable();
}

/**********************************************************************************************************
 @Function		char Radio_Hal_RF_Get_Status(void)
 @Description 		Radio_Hal_RF_Get_Status							: Radio RF 获取状态
 @Input			void
 @Return		  	void
**********************************************************************************************************/
char Radio_Hal_RF_Get_Status(void)
{
#ifdef RADIO_SI4438A
	return radio_status;
#else
	return rTRF_ERROR;
#endif
}

/**********************************************************************************************************
 @Function		char Radio_Hal_RF_Get_Channel(void)
 @Description 		Radio_Hal_RF_Get_Channel							: Radio RF 获取通道
 @Input			void
 @Return		  	void
**********************************************************************************************************/
char Radio_Hal_RF_Get_Channel(void)
{
	return radio_channel;
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Set_Sleep(void)
 @Description 		Radio_Hal_RF_Set_Sleep							: Radio RF 设置Sleep模式
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Set_Sleep(void)
{
	radio_core_Sleep();
}

/**********************************************************************************************************
 @Function		char Radio_Hal_RF_Get_Sleep(void)
 @Description 		Radio_Hal_RF_Get_Sleep							: Radio RF 获取Sleep模式
 @Input			void
 @Return		  	void
**********************************************************************************************************/
char Radio_Hal_RF_Get_Sleep(void)
{
	return (RF_STATE_SLEEP == radio_core_Get_State());
}

/**********************************************************************************************************
 @Function			char Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
 @Description			Radio_Hal_RF_PrepareToTx						: Radio RF 发送数据包
 @Input				pPacket
					len
 @Return				void
**********************************************************************************************************/
char Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
{
	u32 s_count = len + 5;
	
	radio_P_frame = pPacket;
	radio_Data_sending = rTRF_Sending;
	
	radio_core_StartTx_Variable_Packet(radio_channel, radio_P_frame, len);
	
	radio_Packet_len = len + 1;
	
	if (radio_Wait_enable == rTRF_WaitOver) {
		while ((radio_Data_sending == rTRF_Sending) && (s_count--)) {
			Delay_US(150);
		}
		if (s_count == 0) {
			return rTRF_ERROR;
		}
	}
	
	return rTRF_OK;
}

/**********************************************************************************************************
 @Function			static void Radio_Hal_RF_TxISR(void)
 @Description			Radio_Hal_RF_TxISR
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Radio_Hal_RF_TxISR(void)
{
	if (radio_Rest_num > RADIO_TX_ALMOST_EMPTY_THRESHOLD) {
		si446x_write_tx_fifo(RADIO_TX_ALMOST_EMPTY_THRESHOLD, radio_P_frame);
		radio_P_frame += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		radio_Send_num += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		radio_Rest_num = radio_Packet_len - radio_Send_num;
	}
	else if(radio_Rest_num > 0) {
		si446x_write_tx_fifo(radio_Rest_num, radio_P_frame);
	}
}

/**********************************************************************************************************
 @Function			static void Radio_Hal_RF_TxOverISR(void)
 @Description			Radio_Hal_RF_TxOverISR
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Radio_Hal_RF_TxOverISR(void)
{
	radio_Send_num = 0;
	radio_Rest_num = 0;
	radio_Data_sending = rTRF_Sendover;
	si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
}

/**********************************************************************************************************
 @Function			static radio_trf_check xm_CheckSum(u8* recv_data)
 @Description			xm_CheckSum
 @Input				recv_data
 @Return				radio_trf_check
**********************************************************************************************************/
static radio_trf_check xm_CheckSum(u8* recv_data)
{
	u16 check_sum = 0, i, len;
	
	len  = *recv_data;
	
	for (i = 1; i < len - 1; i++) {
		check_sum += recv_data[i];
	}
	
	*recv_data -= 2;
	
	if (check_sum == (recv_data[i] * 0x100 + recv_data[i+1]))
		return rTRF_Check_Success;
	else
		return rTRF_Check_Fail;
}

static u8 Recv_len = 0;
static u8 g_LT_int = 0;
static u8 current_num = 0;
static mrfiPacket_t mrfiIncomingPacket;

/**********************************************************************************************************
 @Function			void Radio_Hal_RF_ISR(void)
 @Description			Radio_Hal_RF_ISR							: Radio RF 中断处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_ISR(void)
{
	u8 s_numOfRecvBytes = 0;
	u8 tmp;
	
	u8* g_Recvlong = mrfiIncomingPacket.frame;
	
	if ((radio_inited == rTRF_Uninited) || (Radio_Hal_RF_Get_Sleep())) return;
	
	tmp = radio_core_Check();
	if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		Radio_Hal_RF_TxOverISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT) {
		Radio_Hal_RF_TxISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT) {
		
		s_numOfRecvBytes = Recv_len + 1 - current_num;
		
		if (!g_LT_int) {
			si446x_read_rx_fifo(1, &Recv_len);
			si446x_read_rx_fifo(Recv_len, &g_Recvlong[1]);
			g_Recvlong[0] = Recv_len;
		}
		else {
			si446x_read_rx_fifo(s_numOfRecvBytes, &g_Recvlong[current_num]);
			current_num += s_numOfRecvBytes;
		}
		
		radio_Wait_enable = rTRF_WaitNo;
		
		current_num = 0;
		g_LT_int = 0;
		
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		radio_core_StartRX(radio_channel, 0);
		
		if (xm_CheckSum(g_Recvlong)) {
			/* TODO: handle the data received */
			Radio_RF_Data_Handle_ISR(&mrfiIncomingPacket);
		}
		memset(g_Recvlong, 0x00, sizeof(mrfiIncomingPacket.frame));
		
		radio_Wait_enable = rTRF_WaitOver;
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT) {
		
		if (!g_LT_int) {
			si446x_read_rx_fifo(1, g_Recvlong);
			Recv_len = g_Recvlong[0];
			current_num = 0;
		}
		
		s_numOfRecvBytes = Recv_len + 1 - current_num;
		
		if (s_numOfRecvBytes >= RADIO_RX_ALMOST_FULL_THRESHOLD) {
			if (!g_LT_int)
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD - 1, &g_Recvlong[1]);
			else
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD, &g_Recvlong[current_num]);
			
			current_num += RADIO_RX_ALMOST_FULL_THRESHOLD;
			
			if (!g_LT_int) g_LT_int++;
		}
	}
}

/**********************************************************************************************************
 @Function			void PortB_IRQHandler(void)
 @Description			PortB_IRQHandler							: HC32 PortB中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortB_IRQHandler(void)
{
	/* Radio RF IRQn */
	if (Gpio_GetIrqStatus(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN)) {
		Gpio_ClearIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN);
		Radio_Hal_RF_ISR();
	}
}

/********************************************** END OF FLEE **********************************************/
