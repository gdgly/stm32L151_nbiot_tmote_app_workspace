#ifndef __RADIO_CORE_H
#define   __RADIO_CORE_H

#include "platform_config.h"
#include "radio_compiler_defs.h"

#define SI4438_B1				0
#define SI4438_C2				1
#define SI4438_TYPE				SI4438_B1

#define RF_STATE_SLEEP			0
#define RF_STATE_RX				1
#define RF_STATE_TX				2
#define RF_STATE_STANDBY			3

#if RADIO_IS_TYPE == RADIO_IS_BOOT
/*! Maximal packet length definition (FIFO size) */
#define RADIO_MAX_PACKET_LENGTH			64u
#define RADIO_TX_ALMOST_EMPTY_THRESHOLD		48u
#define RADIO_RX_ALMOST_FULL_THRESHOLD		48u
#define RADIO_MAX_LONG_PACKET_LENGTH		255u
#define RADIO_RX_FIFO_DATA_ARRAY			128u
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
/*! Maximal packet length definition (FIFO size) */
#define RADIO_MAX_PACKET_LENGTH			64u
#define RADIO_TX_ALMOST_EMPTY_THRESHOLD		62u
#define RADIO_RX_ALMOST_FULL_THRESHOLD		62u
#define RADIO_MAX_LONG_PACKET_LENGTH		255u
#define RADIO_RX_FIFO_DATA_ARRAY			128u
#endif

void Radio_Core_PowerUp(void);

u8   Radio_Core_Check(void);

void Radio_Core_StartRX(u8 channel, u8 packetLenght);

void Radio_Core_StartRX_Tune(u8 channel, u8 packetLenght);

u8   Radio_Core_StartTx_Variable_Packet(u8 channel, u8* pioRadioPacket, u8 length);

void Radio_Core_StartTx(u8 channel, u8* pioRadioPacket, u8 length);

void Radio_Core_StartTx_Dummy(u8 channel);

void Radio_Core_Sleep(void);

s8   Radio_Core_Get_State(void);

#endif /* __RADIO_CORE_H */
