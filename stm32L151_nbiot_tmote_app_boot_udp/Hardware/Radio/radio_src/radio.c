/*! @file radio.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */
#include "si446x_cmd.h"
#include "si446x_api_lib.h"
#include "radio.h"
#ifdef	SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#else
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif
#include "compiler_defs.h"
#include "radio_hal.h"
#include "sys.h"



/*****************************************************************************
 *  Local Macros & Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/
 /*
const SEGMENT_VARIABLE(Radio_Configuration_Data_Array[], U8, SEG_CODE) = \
              RADIO_CONFIGURATION_DATA_ARRAY;

const SEGMENT_VARIABLE(RadioConfiguration, tRadioConfiguration, SEG_CODE) = \
                        RADIO_CONFIGURATION_DATA;
												
*/



 /*
const SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, SEG_CODE, SEG_CODE) = \
                    &RadioConfiguration;
*/    

//SEGMENT_VARIABLE(customRadioPacket[RADIO_MAX_PACKET_LENGTH], U8, SEG_XDATA);


/*****************************************************************************
 *  Local Function Declarations
 *****************************************************************************/


/*!
 *  Power up the Radio.
 *
 *  @note
 *
 */
void vRadio_PowerUp(void)
{
  //SEGMENT_VARIABLE(wDelay,  U16, SEG_XDATA) = 0u;
  U16 wDelay = 0;
  /* Hardware reset the chip */
  si446x_reset();

  /* Wait until reset timeout or Reset IT signal */
  //for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
	for (; wDelay < 0x1000; wDelay++);
}

/*!
 *  Radio Initialization.
 *
 *  @author Sz. Papp
 *
 *  @note
 *
 */



/*!
 *  Check if Packet sent IT flag or Packet Received IT is pending.
 *
 *  @return   SI4455_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT / SI4455_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT
 *
 *  @note
 *
 */

uint8_t bRadio_Check(void)
{
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);
	//tmp = Si446xCmd.GET_INT_STATUS.PH_PEND;
	if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_BIT)
	{
		/* State change to */
		si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_SLEEP);

		/* Reset FIFO */
		si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);

		/* State change to */
		si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_RX);
	}

	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT)
	{
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT;
	}

	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT)
	{
		/* Packet RX */

		/* Get payload length */
		//   si446x_fifo_info(0x00);
		//vRadio_StartRX(CHANNEL1,sizeof());
		// si446x_read_rx_fifo(Si446xCmd.FIFO_INFO.RX_FIFO_COUNT, &customRadioPacket[0]);
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT;
	}

	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_CRC_ERROR_BIT)
	{
		/* Reset FIFO */
		si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
	}
	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT)	 //add by scq 160223
	{
		return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT;
	}

	if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT)	  //add by scq 160223
	{
		return SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT;
	}
	return 0;
}

/*!
 *  Set Radio to RX mode. .
 *
 *  @param channel Freq. Channel,  packetLength : 0 Packet handler fields are used , nonzero: only Field1 is used
 *
 *  @note
 *
 */
void vRadio_StartRX(uint8_t channel, uint8_t packetLenght)
{
	// Read ITs, clear pending ones
	si446x_get_int_status(0u, 0u, 0u);

	// Reset the Rx Fifo
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);

	/* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
	si446x_start_rx(channel, 0u, packetLenght,
					SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
					SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
					//SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_SLEEP,
					SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX);
}




void vRadio_StartRX_Tune(U8 channel, U8 packetLenght )
{
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);

   // Reset the Rx Fifo
   si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);

  /* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
  si446x_start_rx(channel, 0u, packetLenght,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY ,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX_TUNE );

}


/*!
 *  Set Radio to TX mode, variable packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent length of of the packet sent to TXFIFO
 *
 *  @note
 *
 */
uint8_t vRadio_StartTx_Variable_Packet(uint8_t channel, uint8_t *pioRadioPacket, uint8_t length)
{
	uint8_t len_sent = 0;
	/* Leave RX state */
	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_READY);

	/* Reset the Tx Fifo */
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);
	/* Read ITs, clear pending ones */
	si446x_get_int_status(0u, 0u, 0u);

 	if(length>=RADIO_TX_ALMOST_EMPTY_THRESHOLD)
  	{
    	/* Data to be sent is more than the size of TX FIFO */
		si446x_write_tx_fifo(RADIO_TX_ALMOST_EMPTY_THRESHOLD, pioRadioPacket);
		len_sent = RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		//g_P_frame += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		//g_Send_num += RADIO_TX_ALMOST_EMPTY_THRESHOLD;
		//g_Rest_num = length+1 - RADIO_TX_ALMOST_EMPTY_THRESHOLD;    //发送数据中field1中的值为field2数据的长度，所以总长度为field1+field2
  	}
	else{
		si446x_write_tx_fifo(length+1, pioRadioPacket);
		len_sent = length+1;
	}

	si446x_set_property(0x12, 0x02, 0x11, 0x00, length);   //设置发送数据长度

	si446x_start_tx(channel, 0x80, 0x00);   //发送数据

	return len_sent;
  /* Start sending packet, channel 0, START immediately */
   
}
#if 0
/*************************************************
  Function:       // vRadio_StartTx
  Description:    // start send long package data
  Input:          // channel:发送信道
                  // pioRadioPacket 发送数据指针
  Others:         // 发送长度由ilength全局变量传入
*************************************************/
void vRadio_StartTx(U8 channel, U8 *pioRadioPacket,U8 len)
{
	//TX data packet length
  	/* Reset TX FIFO */
  	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);

  	// Read ITs, clear pending ones
  	si446x_get_int_status(0u, 0u, 0u);
  


  	/* Fill the TX fifo with datas */
        if(len>=RADIO_TX_ALMOST_EMPTY_THRESHOLD)
        {
        /* Data to be sent is more than the size of TX FIFO */
          si446x_write_tx_fifo(RADIO_TX_ALMOST_EMPTY_THRESHOLD, pioRadioPacket);
          
          //g_P_frame += RADIO_TX_ALMOST_EMPTY_THRESHOLD;          
          //g_Send_num += RADIO_TX_ALMOST_EMPTY_THRESHOLD;          
          //g_Rest_num = len+1 - g_Send_num;    //发送数据中field1中的值为field2数据的长度，所以总长度为field1+field2
        }
        else
          si446x_write_tx_fifo(len+1, pioRadioPacket);

        si446x_set_property(0x12, 0x02, 0x11, 0x00, len);   //设置发送数据长度

        si446x_start_tx(channel, 0x80, 0x00);   //发送数据

}
#endif













