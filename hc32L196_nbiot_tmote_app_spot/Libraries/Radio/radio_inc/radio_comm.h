#ifndef __RADIO_COMM_H
#define   __RADIO_COMM_H

#include "platform_config.h"
#include "radio_compiler_defs.h"

#if RADIO_IS_TYPE == RADIO_IS_BOOT
#define RADIO_CTS_TIMEOUT		15000
#define RADIO_CTS_LOOPCNT		150

#define RADIO_COM_SENDCMD_CNT		10
#define RADIO_COM_WRITE_CNT		10
#define RADIO_COM_READ_CNT		10
#endif

#if RADIO_IS_TYPE == RADIO_IS_APP
#define RADIO_CTS_TIMEOUT		200
#define RADIO_CTS_LOOPCNT		5

#define RADIO_COM_SENDCMD_CNT		3
#define RADIO_COM_WRITE_CNT		6
#define RADIO_COM_READ_CNT		6
#endif

void Radio_Comm_ClearsCTS(void);															//Clears the CTS state variable
void Radio_Comm_AssertCTS(void);															//Assert the CTS state variable

u8   Radio_Comm_PollCTS(void);															//Waits for CTS to be high

void Radio_Comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData);							//Write Data

void Radio_Comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData);							//Read Data

void Radio_Comm_SendCmd(u8 cmdByteCount, u8* pCmdData);										//Send a command to the radio chip

u8   Radio_Comm_GetResp(u8 respByteCount, u8* pRespData);										//Gets a command response from the radio chip

u8   Radio_Comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData);		//Send a command to the radio chip and gets a response

#endif /* __RADIO_COMM_H */
