/**
  *********************************************************************************************************
  * @file    radio_comm.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-01
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
#include "radio_hal_rf.h"
#include "delay.h"
#include "usart.h"

#define RADIO_CTS_TIMEOUT		200

static __IO u8 ctsWentHigh = 0;

/**********************************************************************************************************
 @Function			void radio_comm_ClearCTS(void)
 @Description			radio_comm_ClearCTS
 @Input				void
 @Return				void
**********************************************************************************************************/
void radio_comm_ClearCTS(void)
{
	ctsWentHigh = 0;
}

/**********************************************************************************************************
 @Function			u8 radio_comm_PollCTS(void)
 @Description			radio_comm_PollCTS							: Waits for CTS to be high
 @Input				void
 @Return				CTS value
**********************************************************************************************************/
u8 radio_comm_PollCTS(void)
{
#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS
	while (!Radio_Hal_Wrapper_GPIO1Level()) {
		/* Wait...*/
	}
	ctsWentHigh = 1;
	return 0xFF;
#else
	return radio_comm_GetResp(0, 0);
#endif
}

/**********************************************************************************************************
 @Function			u8 radio_comm_GetResp(u8 byteCount, u8* pData)
 @Description			radio_comm_GetResp							: Gets a command response from the radio chip
 @Input				byteCount									: Number of bytes to get from the radio chip
					pData									: Pointer to where to put the data
 @Return				CTS value
**********************************************************************************************************/
u8 radio_comm_GetResp(u8 byteCount, u8* pData)
{
	u8 ctsVal = 0;
	u32 errCnt = RADIO_CTS_TIMEOUT;
	int loopCount;
	
	while (errCnt != 0) {
		RADIO_HAL_NSS_ENABLE();
		Radio_Hal_Wrapper_SendByte(0x44);
		ctsVal = Radio_Hal_Wrapper_ReadByte(RADIO_CMD_DUMMY_BYTE);
		if (ctsVal == 0xFF) {
			if (byteCount) {
				Radio_Hal_Wrapper_ReadData(byteCount, pData);
			}
			RADIO_HAL_NSS_DISABLE();
			break;
		}
		RADIO_HAL_NSS_DISABLE();
		errCnt--;
		for (loopCount = 5; loopCount != 0; loopCount--);
	}
	
	if (errCnt == 0) {
		while (1) {
			/* ERROR!!!!  CTS should never take this long. */
		#ifdef RADIO_COMM_ERROR_CALLBACK
			RADIO_COMM_ERROR_CALLBACK();
		#else
			break;
		#endif
		}
	}
	
	if (ctsVal == 0xFF) {
		ctsWentHigh = 1;
	}
	
	return ctsVal;
}

/**********************************************************************************************************
 @Function			void radio_comm_SendCmd(u8 byteCount, u8* pData)
 @Description			radio_comm_SendCmd							: Sends a command to the radio chip
 @Input				byteCount									: Number of bytes in the command to send to the radio device
					pData									: Pointer to the command to send
 @Return				CTS value
**********************************************************************************************************/
void radio_comm_SendCmd(u8 byteCount, u8* pData)
{
	char count = 3;
	
	while (!ctsWentHigh) {
		radio_comm_PollCTS();
		count--;
		if (count == 0) break;
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendData(byteCount, pData);
	RADIO_HAL_NSS_DISABLE();
	ctsWentHigh = 0;
}

/**********************************************************************************************************
 @Function			void radio_comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
 @Description			radio_comm_ReadData							: Read
 @Input				cmd           								: Command ID
					pollCts									: Set to poll CTS
					byteCount									: Number of bytes to get from the radio chip
					pData									: Pointer to where to put the data
 @Return				void
**********************************************************************************************************/
void radio_comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
{
	char count = 6;
	
	if (pollCts) {
		while (!ctsWentHigh) {
			radio_comm_PollCTS();
			count--;
			if (count == 0) break;
		}
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendByte(cmd);
	Radio_Hal_Wrapper_ReadData(byteCount, pData);
	RADIO_HAL_NSS_DISABLE();
	ctsWentHigh = 0;
}

/**********************************************************************************************************
 @Function			void radio_comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
 @Description			radio_comm_WriteData						: Write
 @Input				cmd           								: Command ID
					pollCts									: Set to poll CTS
					byteCount									: Number of bytes to get from the radio chip
					pData									: Pointer to where to put the data
 @Return				void
**********************************************************************************************************/
void radio_comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData)
{
	char count = 6;
	
	if (pollCts) {
		while (!ctsWentHigh) {
			radio_comm_PollCTS();
			count--;
			if (count == 0) break;
		}
	}
	
	RADIO_HAL_NSS_ENABLE();
	Radio_Hal_Wrapper_SendByte(cmd);
	Radio_Hal_Wrapper_SendData(byteCount, pData);
	RADIO_HAL_NSS_DISABLE();
	ctsWentHigh = 0;
}

/**********************************************************************************************************
 @Function			u8 radio_comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData)
 @Description			radio_comm_SendCmdGetResp					: Send a command to the radio chip and gets a response
 @Input				cmdByteCount								: Number of bytes in the command to send
					pCmdData									: Pointer to the command data
					respByteCount								: Number of bytes in the response to fetch
					pRespData									: Pointer to where to put the response data
 @Return				CTS value
**********************************************************************************************************/
u8 radio_comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData)
{
	radio_comm_SendCmd(cmdByteCount, pCmdData);
	
	return radio_comm_GetResp(respByteCount, pRespData);
}

/********************************************** END OF FLEE **********************************************/
