#ifndef __RADIO_CORE_H
#define   __RADIO_CORE_H

#include "sys.h"

#define SI4438_B1				0
#define SI4438_C2				1
#define SI4438_TYPE				SI4438_B1

#define RF_STATE_SLEEP					0
#define RF_STATE_RX						1
#define RF_STATE_TX						2
#define RF_STATE_STANDBY					3

/*! Maximal packet length definition (FIFO size) */
#define RADIO_MAX_PACKET_LENGTH			64u
#define RADIO_TX_ALMOST_EMPTY_THRESHOLD		62u
#define RADIO_RX_ALMOST_FULL_THRESHOLD		62u
#define RADIO_MAX_LONG_PACKET_LENGTH		255u
#define RADIO_RX_FIFO_DATA_ARRAY			128u

extern volatile u8 radio_Send_num;
extern volatile u8 radio_Rest_num;

extern u8 *radio_P_frame;

void radio_core_PowerUp(void);

u8   radio_core_Check(void);

void radio_core_StartRX(u8 channel, u8 packetLenght);

void radio_core_StartRX_Tune(u8 channel, u8 packetLenght);

u8   radio_core_StartTx_Variable_Packet(u8 channel, u8* pioRadioPacket, u8 length);

void radio_core_StartTx_dummy(u8 channel);

void radio_core_StartTx(u8 channel, u8* pioRadioPacket, u8 len);

void radio_core_Sleep(void);

char radio_core_Get_State(void);

#endif /* __RADIO_CORE_H */
