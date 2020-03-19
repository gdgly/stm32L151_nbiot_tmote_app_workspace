/**
  *********************************************************************************************************
  * @file    radio_comm.c
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
#include "radio_comm.h"
#include "radio_hal_wrap.h"
#include "delay.h"
#include "usart.h"

static __IO u8 ctsWentHigh = 0;

/**********************************************************************************************************
 @Function			void Radio_Comm_ClearsCTS(void)
 @Description			Radio_Comm_ClearsCTS						: Clears the CTS state variable
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Comm_ClearsCTS(void)
{
	ctsWentHigh = 0;
}

/**********************************************************************************************************
 @Function			void Radio_Comm_AssertCTS(void)
 @Description			Radio_Comm_AssertCTS						: Assert the CTS state variable
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Comm_AssertCTS(void)
{
	ctsWentHigh = 1;
}

/**********************************************************************************************************
 @Function			u8 Radio_Comm_PollCTS(void)
 @Description			Radio_Comm_PollCTS							: Waits for CTS to be high
 @Input				void
 @Return				CTS value
**********************************************************************************************************/
u8 Radio_Comm_PollCTS(void)
{
#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS
	while (!Radio_Hal_Wrapper_GPIO1Level()) {
		/* Wait...*/
	}
	Radio_Comm_AssertCTS();
	return 0xFF;
#else
	return Radio_Comm_GetResp(0, 0);
#endif
}

/**********************************************************************************************************
 @Function			u8 Radio_Comm_GetResp(u8 respByteCount, u8* pRespData)
 @Description			Radio_Comm_GetResp							: Gets a command response from the radio chip
 @Input				respByteCount								: Number of bytes to get from the radio chip
					pRespData									: Pointer to where to put the data
 @Return				CTS value
**********************************************************************************************************/
u8 Radio_Comm_GetResp(u8 respByteCount, u8* pRespData)
{
	u8 ctsVal = 0;
	u32 errCnt = RADIO_CTS_TIMEOUT;
	s32 loopCount;
	
	while (errCnt != 0) {
		RADIO_HAL_NSS_ENABLE();
		Radio_Hal_Wrapper_SendByte(0x44);
		ctsVal = Radio_Hal_Wrapper_ReadByte(RADIO_CMD_DUMMY_BYTE);
		if (ctsVal == 0xFF) {
			if (respByteCount) {
				Radio_Hal_Wrapper_ReadData(respByteCount, pRespData);
			}
			RADIO_HAL_NSS_DISABLE();
			break;
		}
		RADIO_HAL_NSS_DISABLE();
		errCnt--;
		for (loopCount = RADIO_CTS_LOOPCNT; loopCount > 0; loopCount--);
	}
	
	if (errCnt == 0) {
		while (1) {
		#ifdef RADIO_COMM_ERROR_CALLBACK
			RADIO_COMM_ERROR_CALLBACK();
		#else
			break;
		#endif
		}
	}
	
	if (ctsVal == 0xFF) {
		Radio_Comm_AssertCTS();
	}
	
	return ctsVal;
}

/**********************************************************************************************************
 @Function			void Radio_Comm_SendCmd(u8 cmdByteCount, u8* pCmdData)
 @Description			Radio_Comm_SendCmd							: Sends a command to the radio chip
 @Input				cmdByteCount								: Number of bytes in the command to send to the radio device
					pCmdData									: Pointer to the command to send
 @Return				void
**********************************************************************************************************/
void Radio_Comm_SendCmd(u8 cmdByteCount, u8* pCmdData)
{
	s8 count = RADIO_COM_SENDCMD_CNT;
	
	while (!ctsWentHigh) {
		Radio_Comm_PollCTS();
		count--;
		if (count == 0) break;
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendData(cmdByteCount, pCmdData);
	RADIO_HAL_NSS_DISABLE();
	Radio_Comm_ClearsCTS();
}

/**********************************************************************************************************
 @Function			void Radio_Comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
 @Description			Radio_Comm_ReadData				: Read
 @Input				cmd           					: Command ID
					pollCts						: Set to poll CTS
					byteCount						: Number of bytes to get from the radio chip
					pData						: Pointer to where to put the data
 @Return				void
**********************************************************************************************************/
void Radio_Comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
{
	s8 count = RADIO_COM_READ_CNT;
	
	if (pollCts) {
		while (!ctsWentHigh) {
			Radio_Comm_PollCTS();
			count--;
			if (count == 0) break;
		}
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendByte(cmd);
	Radio_Hal_Wrapper_ReadData(byteCount, pData);
	RADIO_HAL_NSS_DISABLE();
	Radio_Comm_ClearsCTS();
}

/**********************************************************************************************************
 @Function			void Radio_Comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
 @Description			Radio_Comm_WriteData			: Write
 @Input				cmd           					: Command ID
					pollCts						: Set to poll CTS
					byteCount						: Number of bytes to get from the radio chip
					pData						: Pointer to where to put the data
 @Return				void
**********************************************************************************************************/
void Radio_Comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
{
	s8 count = RADIO_COM_WRITE_CNT;
	
	if (pollCts) {
		while (!ctsWentHigh) {
			Radio_Comm_PollCTS();
			count--;
			if (count == 0) break;
		}
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendByte(cmd);
	Radio_Hal_Wrapper_SendData(byteCount, pData);
	RADIO_HAL_NSS_DISABLE();
	Radio_Comm_ClearsCTS();
}

/**********************************************************************************************************
 @Function			u8 Radio_Comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData)
 @Description			Radio_Comm_SendCmdGetResp					: Send a command to the radio chip and gets a response
 @Input				cmdByteCount								: Number of bytes in the command to send
					pCmdData									: Pointer to the command data
					respByteCount								: Number of bytes in the response to fetch
					pRespData									: Pointer to where to put the response data
 @Return				CTS value
**********************************************************************************************************/
u8 Radio_Comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData)
{
	Radio_Comm_SendCmd(cmdByteCount, pCmdData);
	
	return Radio_Comm_GetResp(respByteCount, pRespData);
}

/********************************************** END OF FLEE **********************************************/
