/**
  *********************************************************************************************************
  * @file    radio_core.c
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
#include "radio_core.h"
#include "si446x_api_lib.h"
#include "si446x_cmd.h"
#include "delay.h"
#include "usart.h"

#if SI4438_TYPE == SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#endif
#if SI4438_TYPE == SI4438_C2
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif

static s8 radio_rf_state = RF_STATE_SLEEP;

/**********************************************************************************************************
 @Function			void Radio_Core_PowerUp(void)
 @Description			Radio_Core_PowerUp
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Core_PowerUp(void)
{
	si446x_reset();
	
	Delay_MS(20);
}

/**********************************************************************************************************
 @Function			u8 Radio_Core_Check(void)
 @Description			Radio_Core_Check
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Core_Check(void)
{
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);
	
	if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_BIT) {
		/* State change to */
		si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_SLEEP);
		
		/* Reset FIFO */
		si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
		
		/* State change to */
		si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_RX);
	}
	
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT) {
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT;
	}
	
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT) {
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT;
	}
	
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_CRC_ERROR_BIT) {
		/* Reset FIFO */
		si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
	}
	
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT) {
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT;
	}
	
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT) {
		return SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT;
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			void Radio_Core_StartRX(u8 channel, u8 packetLenght)
 @Description			Radio_Core_StartRX
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Core_StartRX(u8 channel, u8 packetLenght)
{
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);
	
	/* Reset the Rx Fifo */
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
	
	/* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
	si446x_start_rx(channel, 0u, packetLenght, SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
									   SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
									   SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX);
	
	radio_rf_state = RF_STATE_RX;
}

/**********************************************************************************************************
 @Function			void Radio_Core_StartRX(u8 channel, u8 packetLenght)
 @Description			Radio_Core_StartRX
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Core_StartRX_Tune(u8 channel, u8 packetLenght)
{
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);
	
	/* Reset the Rx Fifo */
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
	
	/* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
	si446x_start_rx(channel, 0u, packetLenght, SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
									   SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
									   SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX_TUNE);
	
	radio_rf_state = RF_STATE_RX;
}

/**********************************************************************************************************
 @Function			u8 Radio_Core_StartTx_Variable_Packet(u8 channel, u8* pioRadioPacket, u8 length)
 @Description			Radio_Core_StartTx_Variable_Packet
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Core_StartTx_Variable_Packet(u8 channel, u8* pioRadioPacket, u8 length)
{
	u8 len_sent = 0;
	
	/* Leave RX state */
	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_READY);
	
	/* Reset the Tx Fifo */
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);
	
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);
	
	if (length >= RADIO_TX_ALMOST_EMPTY_THRESHOLD) {
		/* Data to be sent is more than the size of TX FIFO */
		si446x_write_tx_fifo(RADIO_TX_ALMOST_EMPTY_THRESHOLD, pioRadioPacket);
		len_sent = RADIO_TX_ALMOST_EMPTY_THRESHOLD;
	}
	else {
		si446x_write_tx_fifo(length + 1, pioRadioPacket);
		len_sent = length + 1;
	}
	
	/* Set send data length */
	si446x_set_property(0x12, 0x02, 0x11, 0x00, length);
	
	/* Start send data */
	si446x_start_tx(channel, 0x80, 0x00);
	
	return len_sent;
}




















/********************************************** END OF FLEE **********************************************/
