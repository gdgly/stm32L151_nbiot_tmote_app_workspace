/**
  *********************************************************************************************************
  * @file    radio_hal_rf.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-18
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
#include "radio_rfa_app.h"
#include "radio_core.h"
#include "si446x_api_lib.h"
#include "si446x_defs.h"
#include "si446x_cmd.h"
#include "delay.h"
#include "usart.h"

#if SI4438_TYPE == SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#endif
#if SI4438_TYPE == SI4438_C2
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif

radioClientsTypeDef si4438Client = {
	.rf_status				= rTRF_ERROR,
	.rf_inited				= rTRF_Uninited,
	.rf_channel1				= RADIO_RF_CHANNEL1,
	.rf_corestate				= RF_STATE_SLEEP,
	.rf_ctsWentHigh			= 0,
	.rf_g_Send_Num				= 0,
	.rf_g_Rest_Num				= 0,
	.rf_g_Pack_Len				= 0,
	.rf_g_Data_sending			= rTRF_Sending,
	.rf_g_Wait_enable			= rTRF_WaitOver,
	.rf_recv_len				= 0,
	.rf_current_num			= 0,
	.rf_LT_int				= 0,
};

static const U8 Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;

/**********************************************************************************************************
 @Function		radio_trf_errcode Radio_Hal_RF_Init(radioClientsTypeDef* pClient)
 @Description 		Radio_Hal_RF_Init								: Radio RF 初始化
 @Input			pClient										: Radio Client
 @Return		  	errcode
**********************************************************************************************************/
radio_trf_errcode Radio_Hal_RF_Init(radioClientsTypeDef* pClient)
{
	timeMeterTypeDef radioRFTimer;
	
	/* step 0: radio interface init */
	Radio_Hal_RF_Interface_Init();
	
	/* step 1: radio reset and check chip */
	pClient->rf_status = Radio_Hal_RF_ResetChip(pClient);
	if (pClient->rf_status != rTRF_OK) return rTRF_ERROR;
	
	HC32_TimeMeter_CountdownMS(&radioRFTimer, RADIO_CONFIG_TIMER);
	
	/* step 2: radio set up */
	while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array)) {
		Radio_Core_PowerUp();
		if (HC32_TimeMeter_IsExpiredMS(&radioRFTimer)) {
			pClient->rf_status = rTRF_ERROR;
			return rTRF_ERROR;
		}
	}
	
	/* step 3: radio get the chip's Interrupt status/pending flags form the radio and clear flags if requested */
	si446x_get_int_status(0u, 0u, 0u);
	
	/* step 4: radio set the rf chip to rx state */
	Radio_Core_StartRX(pClient->rf_channel1, 0);
	
	/* step 5: radio enable interrupt */
	Radio_Hal_RF_Interrupt_Enable();
	
	return rTRF_OK;
}

/**********************************************************************************************************
 @Function		radio_trf_errcode Radio_Hal_RF_ResetChip(radioClientsTypeDef* pClient)
 @Description 		Radio_Hal_RF_ResetChip							: Radio RF 复位检查芯片
 @Input			pClient										: Radio Client
 @Return		  	errcode
**********************************************************************************************************/
radio_trf_errcode Radio_Hal_RF_ResetChip(radioClientsTypeDef* pClient)
{
	for (int nCount = 0; nCount < RADIO_NRESET_COUNT; nCount++) {
		
		Radio_Core_PowerUp();
		
		si446x_part_info();
		
		if (Si446xCmd.PART_INFO.PART != 0x4438) {
			pClient->rf_status = rTRF_ERROR;
		}
		else {
			pClient->rf_status = rTRF_OK;
			pClient->rf_inited = rTRF_Isinited;
			break;
		}
	}
	
	return (pClient->rf_status == rTRF_OK) ? rTRF_OK: rTRF_ERROR;
}

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
	
	/* Radio RF IRQ => Falling */
	Gpio_EnableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQMode);
	/* Radio RF Enable IRQn */
	EnableNvic(RADIO_SI4438_IRQn, RADIO_SI4438_IRQLevel, TRUE);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interface_Init(void)
 @Description 		Radio_Hal_RF_Interface_Init						: Radio RF 接口初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interface_Init(void)
{
	/* Radio SPIx Init */
	Radio_Hal_Wrapper_Init();
	
	/* Radio Port (SDN/NSS/IRQ) Init */
	Radio_Hal_RF_Port_Init();
	
	/* Radio NSS = 1 SPIx Disable */
	Radio_Hal_Wrapper_nSELAssert();
	
	/* Radio SDN = 0 SI4438 Working */
	Radio_Hal_Wrapper_ShutdownDeassert();
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Enable(void)
 @Description 		Radio_Hal_RF_Interrupt_Enable						: Radio RF 中断引脚使能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Enable(void)
{
	Gpio_EnableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQMode);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Disable(void)
 @Description 		Radio_Hal_RF_Interrupt_Disable					: Radio RF 中断引脚失能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Disable(void)
{
	Gpio_DisableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQMode);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Set_Sleep(void)
 @Description 		Radio_Hal_RF_Set_Sleep							: Radio RF 设置Sleep模式
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Set_Sleep(void)
{
	Radio_Core_Sleep();
}

/**********************************************************************************************************
 @Function		char Radio_Hal_RF_Get_Sleep(void)
 @Description 		Radio_Hal_RF_Get_Sleep							: Radio RF 获取Sleep模式
 @Input			void
 @Return		  	void
**********************************************************************************************************/
char Radio_Hal_RF_Get_Sleep(void)
{
	return (RF_STATE_SLEEP == Radio_Core_Get_State());
}

/**********************************************************************************************************
 @Function		char Radio_Hal_RF_Get_Status(void)
 @Description 		Radio_Hal_RF_Get_Status							: Radio RF 获取Radio状态
 @Input			void
 @Return		  	void
**********************************************************************************************************/
char Radio_Hal_RF_Get_Status(void)
{
#ifdef RADIO_SI4438A
	return si4438Client.rf_status;
#else
	return rTRF_ERROR;
#endif
}

#if RADIO_IS_TYPE == RADIO_IS_BOOT
/**********************************************************************************************************
 @Function			radio_trf_errcode Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
 @Description			Radio_Hal_RF_PrepareToTx						: Radio RF 发送数据包
 @Input				pPacket									: pointer of pPacket to be sent
					len										: length of pPacket to be sent
 @Return				errcode
**********************************************************************************************************/
radio_trf_errcode Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
{
	timeMeterTypeDef radioRFToTxTimer;
	
	HC32_TimeMeter_CountdownMS(&radioRFToTxTimer, len + 5);
	
	si4438Client.rf_g_Poin_frame = pPacket;
	si4438Client.rf_g_Data_sending = rTRF_Sending;
	si4438Client.rf_g_Pack_Len = len + 1;
	si4438Client.rf_g_Send_Num = 0;
	
	if (si4438Client.rf_g_Pack_Len > si4438Client.rf_g_Send_Num) {
		si4438Client.rf_g_Send_Num += Radio_Core_StartTx_Variable_Packet(si4438Client.rf_channel1, si4438Client.rf_g_Poin_frame + si4438Client.rf_g_Send_Num, si4438Client.rf_g_Pack_Len - si4438Client.rf_g_Send_Num);
	}
	
	if (si4438Client.rf_g_Wait_enable == rTRF_WaitOver) {
		while (si4438Client.rf_g_Data_sending == rTRF_Sending) {
			if (HC32_TimeMeter_IsExpiredMS(&radioRFToTxTimer)) return rTRF_ERROR;
		}
	}
	
	return rTRF_OK;
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
/**********************************************************************************************************
 @Function			radio_trf_errcode Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
 @Description			Radio_Hal_RF_PrepareToTx						: Radio RF 发送数据包
 @Input				pPacket									: pointer of pPacket to be sent
					len										: length of pPacket to be sent
 @Return				errcode
**********************************************************************************************************/
radio_trf_errcode Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len)
{
	timeMeterTypeDef radioRFToTxTimer;
	
	HC32_TimeMeter_CountdownMS(&radioRFToTxTimer, len + 5);
	
	si4438Client.rf_g_Poin_frame = pPacket;
	si4438Client.rf_g_Data_sending = rTRF_Sending;
	
	Radio_Core_StartTx_Variable_Packet(si4438Client.rf_channel1, si4438Client.rf_g_Poin_frame, len);
	
	si4438Client.rf_g_Pack_Len = len + 1;
	
	if (si4438Client.rf_g_Wait_enable == rTRF_WaitOver) {
		while (si4438Client.rf_g_Data_sending == rTRF_Sending) {
			if (HC32_TimeMeter_IsExpiredMS(&radioRFToTxTimer)) return rTRF_ERROR;
		}
	}
	
	return rTRF_OK;
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_BOOT
/**********************************************************************************************************
 @Function			void Radio_Hal_RF_TxISR(void)
 @Description			Radio_Hal_RF_TxISR							: Radio RF 发送数据中断
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_TxISR(void)
{
	if (si4438Client.rf_g_Pack_Len > si4438Client.rf_g_Send_Num) {
		si4438Client.rf_g_Send_Num += Radio_Core_StartTx_Variable_Packet(si4438Client.rf_channel1, si4438Client.rf_g_Poin_frame + si4438Client.rf_g_Send_Num, si4438Client.rf_g_Pack_Len - si4438Client.rf_g_Send_Num);
	}
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
/**********************************************************************************************************
 @Function			void Radio_Hal_RF_TxISR(void)
 @Description			Radio_Hal_RF_TxISR							: Radio RF 发送数据中断
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_TxISR(void)
{
	if (si4438Client.rf_g_Rest_Num > RADIO_TX_ALMOST_EMPTY_THRESHOLD) {
		si446x_write_tx_fifo(RADIO_TX_ALMOST_EMPTY_THRESHOLD, si4438Client.rf_g_Poin_frame);
		si4438Client.rf_g_Poin_frame += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		si4438Client.rf_g_Send_Num += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		si4438Client.rf_g_Rest_Num = si4438Client.rf_g_Pack_Len - si4438Client.rf_g_Send_Num;
	}
	else if (si4438Client.rf_g_Rest_Num > 0) {
		si446x_write_tx_fifo(si4438Client.rf_g_Rest_Num, si4438Client.rf_g_Poin_frame);
	}
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_BOOT
/**********************************************************************************************************
 @Function			void Radio_Hal_RF_TxOverISR(void)
 @Description			Radio_Hal_RF_TxOverISR						: Radio RF 发送结束中断
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_TxOverISR(void)
{
	if (si4438Client.rf_g_Data_sending != rTRF_Sendover) {
		si4438Client.rf_g_Send_Num = 0;
		si4438Client.rf_g_Data_sending = rTRF_Sendover;
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		Radio_Core_StartRX(si4438Client.rf_channel1, 0);
	}
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
/**********************************************************************************************************
 @Function			void Radio_Hal_RF_TxOverISR(void)
 @Description			Radio_Hal_RF_TxOverISR						: Radio RF 发送结束中断
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_TxOverISR(void)
{
	si4438Client.rf_g_Send_Num = 0;
	si4438Client.rf_g_Rest_Num = 0;
	si4438Client.rf_g_Data_sending = rTRF_Sendover;
	si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
}
#endif

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

#if RADIO_IS_TYPE == RADIO_IS_BOOT
/**********************************************************************************************************
 @Function			void Radio_Hal_RF_ISR(void)
 @Description			Radio_Hal_RF_ISR							: Radio RF 中断处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_RF_ISR(void)
{
	u8 s_numOfRecvBytes = 0;
	u8 framelen;
	u8 tmp;
	
	u8* g_Recvlong = si4438Client.mrfiIncomingPacket.frame;
	
	tmp = Radio_Core_Check();
	if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		Radio_Hal_RF_TxOverISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT) {
		Radio_Hal_RF_TxISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT) {
		s_numOfRecvBytes = si4438Client.rf_recv_len + 1 - si4438Client.rf_current_num;
		
		if (!si4438Client.rf_LT_int) {
			si446x_read_rx_fifo(1, (u8*)&si4438Client.rf_recv_len);
			si446x_read_rx_fifo(si4438Client.rf_recv_len, &g_Recvlong[1]);
			g_Recvlong[0] = si4438Client.rf_recv_len;
		}
		else {
			si446x_read_rx_fifo(s_numOfRecvBytes, &g_Recvlong[si4438Client.rf_current_num]);
			si4438Client.rf_current_num += s_numOfRecvBytes;
		}
		
		si4438Client.rf_g_Wait_enable = rTRF_WaitNo;
		
		framelen = g_Recvlong[0] - MMESH_CHECKSUM_SIZE;
		si4438Client.rf_current_num = 0;
		si4438Client.rf_LT_int = 0;
		
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		Radio_Core_StartRX(si4438Client.rf_channel1, 0);
		
		if (xm_CheckSum(g_Recvlong)) {
			/* TODO: handle the data received */
			Radio_RFA_Boot_Data_Handle_ISR(&si4438Client.mrfiIncomingPacket);
		}
		memset(g_Recvlong, 0x00, sizeof(si4438Client.mrfiIncomingPacket.frame));
		
		si4438Client.rf_g_Wait_enable = rTRF_WaitOver;
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT) {
		
		if (!si4438Client.rf_LT_int) {
			si446x_read_rx_fifo(1, g_Recvlong);
			si4438Client.rf_recv_len = g_Recvlong[0];
			si4438Client.rf_current_num = 0;
		}
		
		s_numOfRecvBytes = si4438Client.rf_recv_len + 1 - si4438Client.rf_current_num;
		if (s_numOfRecvBytes >= RADIO_RX_ALMOST_FULL_THRESHOLD) {
			if (!si4438Client.rf_LT_int)
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD - 1, &g_Recvlong[1]);
			else
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD, &g_Recvlong[si4438Client.rf_current_num]);
			
			si4438Client.rf_current_num += RADIO_RX_ALMOST_FULL_THRESHOLD;
			
			if (!si4438Client.rf_LT_int) si4438Client.rf_LT_int++;
		}
	}
}
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
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
	
	u8* g_Recvlong = si4438Client.mrfiIncomingPacket.frame;
	
	if ((si4438Client.rf_inited == rTRF_Uninited) || (Radio_Hal_RF_Get_Sleep())) return;
	
	tmp = Radio_Core_Check();
	if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		Radio_Hal_RF_TxOverISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT) {
		Radio_Hal_RF_TxISR();
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT) {
		s_numOfRecvBytes = si4438Client.rf_recv_len + 1 - si4438Client.rf_current_num;
		
		if (!si4438Client.rf_LT_int) {
			si446x_read_rx_fifo(1, (u8*)&si4438Client.rf_recv_len);
			si446x_read_rx_fifo(si4438Client.rf_recv_len, &g_Recvlong[1]);
			g_Recvlong[0] = si4438Client.rf_recv_len;
		}
		else {
			si446x_read_rx_fifo(s_numOfRecvBytes, &g_Recvlong[si4438Client.rf_current_num]);
			si4438Client.rf_current_num += s_numOfRecvBytes;
		}
		
		si4438Client.rf_g_Wait_enable = rTRF_WaitNo;
		
		si4438Client.rf_current_num = 0;
		si4438Client.rf_LT_int = 0;
		
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		Radio_Core_StartRX(si4438Client.rf_channel1, 0);
		
		if (xm_CheckSum(g_Recvlong)) {
			/* TODO: handle the data received */
			//Radio_RFA_App_Data_Handle_ISR(&si4438Client.mrfiIncomingPacket);
		}
		memset(g_Recvlong, 0x00, sizeof(si4438Client.mrfiIncomingPacket.frame));
		
		si4438Client.rf_g_Wait_enable = rTRF_WaitOver;
	}
	else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT) {
		
		if (!si4438Client.rf_LT_int) {
			si446x_read_rx_fifo(1, g_Recvlong);
			si4438Client.rf_recv_len = g_Recvlong[0];
			si4438Client.rf_current_num = 0;
		}
		
		s_numOfRecvBytes = si4438Client.rf_recv_len + 1 - si4438Client.rf_current_num;
		if (s_numOfRecvBytes >= RADIO_RX_ALMOST_FULL_THRESHOLD) {
			if (!si4438Client.rf_LT_int)
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD - 1, &g_Recvlong[1]);
			else
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD, &g_Recvlong[si4438Client.rf_current_num]);
			
			si4438Client.rf_current_num += RADIO_RX_ALMOST_FULL_THRESHOLD;
			
			if (!si4438Client.rf_LT_int) si4438Client.rf_LT_int++;
		}
	}
}
#endif

/********************************************** END OF FLEE **********************************************/
