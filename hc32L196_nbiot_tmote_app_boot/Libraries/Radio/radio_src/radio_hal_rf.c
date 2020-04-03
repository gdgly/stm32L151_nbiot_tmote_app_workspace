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
#include "radio_hal_rf.h"
#include "radio_hal_wrap.h"
#include "radio_hal_common.h"
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
	rTRF_Check_Success			= 1U
} radio_trf_check;

static u8 radio_status = rTRF_ERROR;
static u8 radio_channel = RADIO_RF_CHANNEL1;

static volatile u8 radio_Send_num;
static volatile u8 radio_Rest_num;

static u8 *radio_P_frame;

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
	
	/* step 1: radio reset chip */
	radio_core_PowerUp();
	
	/* step 2: radio check chip */
	si446x_part_info();
	
	if (Si446xCmd.PART_INFO.PART != 0x4438) {
		radio_status = rTRF_ERROR;
		return;
	}
	else {
		radio_status = rTRF_OK;
	}
	
	HC32_TimeMeter_CountdownMS(&radioRFTimer, 10000);
	
	/* step 3: radio set up */
	while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array)) {
		radio_core_PowerUp();
		if (HC32_TimeMeter_IsExpiredMS(&radioRFTimer)) {
			radio_status = rTRF_ERROR;
			return;
		}
	}
	
	/* step 4: radio get the chip's Interrupt status/pending flags form the radio and clear flags if requested */
	si446x_get_int_status(0u, 0u, 0u);
	
	/* step 5: radio set the rf chip to rx state */
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
 @Function			void Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
 @Description			Radio_Hal_RF_PrepareToTx						: Radio RF 发送数据包
 @Input				pPacket
					len
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
{
	u32 s_count = 80000;
	
	radio_P_frame = pPacket;
	radio_Data_sending = rTRF_Sending;
	radio_Packet_len = len + 1;
	radio_Send_num = 0;
	
	if (radio_Packet_len > radio_Send_num) {
		radio_Send_num += radio_core_StartTx_Variable_Packet(radio_channel, radio_P_frame + radio_Send_num, radio_Packet_len - radio_Send_num);
	}
	
	if (radio_Wait_enable) {
		while ((radio_Data_sending == rTRF_Sending) && (s_count--));
	}
}

/**********************************************************************************************************
 @Function			static void Radio_Hal_RF_TxISR(void)
 @Description			Radio_Hal_RF_TxISR
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Radio_Hal_RF_TxISR(void)
{
	if (radio_Packet_len > radio_Send_num) {
		radio_Send_num += radio_core_StartTx_Variable_Packet(radio_channel, radio_P_frame + radio_Send_num, radio_Packet_len - radio_Send_num);
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
	if (radio_Data_sending != rTRF_Sendover) {
		radio_Send_num = 0;
		radio_Data_sending = rTRF_Sendover;
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		radio_core_StartRX(radio_channel, 0);
	}
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

/**********************************************************************************************************
 @Function			void Radio_Hal_RF_ISR(void)
 @Description			Radio_Hal_RF_ISR							: Radio RF 中断处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_ISR(void)
{
	u8 s_numOfRecvBytes = 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
}


































/********************************************** END OF FLEE **********************************************/
