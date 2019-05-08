/*! @file radio.h
 * @brief This file is contains the public radio interface functions.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef RADIO_H_
#define RADIO_H_
#include "compiler_defs.h"

/*****************************************************************************
 *  Global Macros & Definitions
 *****************************************************************************/
#define SI4438_B1
//#define	SI4438_C2
/*! Maximal packet length definition (FIFO size) */
#define RADIO_MAX_PACKET_LENGTH     64u
#define RADIO_TX_ALMOST_EMPTY_THRESHOLD 48u
#define RADIO_RX_ALMOST_FULL_THRESHOLD 48u
#define RADIO_MAX_LONG_PACKET_LENGTH 255u
#define RADIO_RX_FIFO_DATA_ARRAY 128u


/*****************************************************************************
 *  Global Typedefs & Enums
 *****************************************************************************/
typedef struct
{
    U8   *Radio_ConfigurationArray;

    U8   Radio_ChannelNumber;
    U8   Radio_PacketLength;
    U8   Radio_State_After_Power_Up;

    U16  Radio_Delay_Cnt_After_Reset;

    U8   Radio_CustomPayload[RADIO_MAX_PACKET_LENGTH];
} tRadioConfiguration;

/*****************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
//extern const SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, SEG_CODE, SEG_CODE);
//extern SEGMENT_VARIABLE(customRadioPacket[RADIO_MAX_PACKET_LENGTH], U8, SEG_XDATA);

/*! Si446x configuration array */
//extern const SEGMENT_VARIABLE(Radio_Configuration_Data_Array[], U8, SEG_CODE);

/*****************************************************************************
 *  Global Function Declarations
 *****************************************************************************/
void  vRadio_Init(void);
void vRadio_PowerUp(void);
uint8_t bRadio_Check(void);
void  vRadio_StartRX(U8,U8);
U8    bRadio_Check_Ezconfig(U16);
uint8_t  vRadio_StartTx_Variable_Packet(U8, U8*, U8);
void vRadio_StartTx(U8 channel, U8 *pioRadioPacket,U8 len);    //add by scq 160224
U8 si4438_send_long_package(U8 channel, unsigned char *buffer, unsigned char longth);    //add by scq 160324
U8 si4438_receive_long_package(U8 channel, unsigned char longth);     //add by scq 160324
U8 si4438_send_long_package(U8 channel, unsigned char *buffer, unsigned char longth);     //add by scq 160324
U8 si4438_receive_long_package(U8 channel, unsigned char longth);     //add by scq 160324
void vRadio_StartRX_Tune(U8 channel, U8 packetLenght );
#endif /* RADIO_H_ */
