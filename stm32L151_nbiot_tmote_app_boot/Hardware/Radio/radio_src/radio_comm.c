/*!
 * File:
 *  radio_comm.h
 *
 * Description:
 *  This file contains the RADIO communication layer.
 *
 * Silicon Laboratories Confidential
 * Copyright 2012 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */
#include "compiler_defs.h"
#include "radio_hal.h"
#include "radio_comm.h"

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

uint8_t ctsWentHigh = 0;

                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */

//#if (defined SILABS_RADIO_SI446X) || (defined SILABS_RADIO_SI4455)

/*!
 * Gets a command response from the radio chip
 *
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 *
 * @return CTS value
 */
U8 radio_comm_GetResp(U8 byteCount, U8* pData)
{
  U8 ctsVal = 0;
  U16 errCnt = RADIO_CTS_TIMEOUT;
  int loopCount;
  while (errCnt != 0)      //wait until radio IC is ready with the data
  {
	radio_hal_ClearNsel();
    radio_hal_SpiWriteByte(0x44);    //read CMD buffer
    ctsVal = radio_hal_SpiReadByte();
    if (ctsVal == 0xFF)
    {
      if (byteCount)
      {
        radio_hal_SpiReadData(byteCount, pData);
      }
      radio_hal_SetNsel();
      break;
    }
    radio_hal_SetNsel();
    errCnt--;
	for (loopCount = 100; loopCount != 0; loopCount--);
  }

  if (errCnt == 0)
  {
    while(1)
    {
      /* ERROR!!!!  CTS should never take this long. */
      #ifdef RADIO_COMM_ERROR_CALLBACK
        RADIO_COMM_ERROR_CALLBACK();
      #else
		break;
	  #endif
    }
  }

  if (ctsVal == 0xFF)
  {
    ctsWentHigh = 1;
  }

  return ctsVal;
}

/*!
 * Sends a command to the radio chip
 *
 * @param byteCount     Number of bytes in the command to send to the radio device
 * @param pData         Pointer to the command to send.
 */
void radio_comm_SendCmd(U8 byteCount, U8* pData)
{
	char rc,count=10;
    while (!ctsWentHigh)
    {
        rc = radio_comm_PollCTS();
		count--;
		if(count == 0)
			break;
    }
	radio_hal_ClearNsel();
	radio_hal_SpiWriteData(byteCount, pData);
    radio_hal_SetNsel();
    ctsWentHigh = 0;
}

/*!
 * Gets a command response from the radio chip
 *
 * @param cmd           Command ID
 * @param pollCts       Set to poll CTS
 * @param byteCount     Number of bytes to get from the radio chip.
 * @param pData         Pointer to where to put the data.
 */
void radio_comm_ReadData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData)
{
	char rc,count=10;
	if (pollCts)
	{
		while (!ctsWentHigh)
		{
			rc = radio_comm_PollCTS();
			count--;
			if(count == 0)
				break;
		}
		
	}
	radio_hal_ClearNsel();
	radio_hal_SpiWriteByte(cmd);
	radio_hal_SpiReadData(byteCount, pData);
    radio_hal_SetNsel();
	ctsWentHigh = 0;
}



/*!
 * Gets a command response from the radio chip
 *
 * @param cmd           Command ID
 * @param pollCts       Set to poll CTS
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 */
void radio_comm_WriteData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData)
{
	char rc,count=10;
	if (pollCts)
	{
		while (!ctsWentHigh)
		{
			rc = radio_comm_PollCTS();
			count--;
			if(count == 0)
				break;
		}
	}
	//radio_hal_ClearNsel();
	radio_hal_ClearNsel();
	radio_hal_SpiWriteByte(cmd);
	radio_hal_SpiWriteData(byteCount, pData);
	radio_hal_SetNsel();
	ctsWentHigh = 0;
}

/*!
 * Waits for CTS to be high
 *
 * @return CTS value
 */
uint8_t radio_comm_PollCTS(void)
{
#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS
	while(!radio_hal_Gpio1Level())
	{
		/* Wait...*/
	}
	ctsWentHigh = 1;
	return 0xFF;
#else
	return radio_comm_GetResp(0, 0);
#endif
}

/**
 * Clears the CTS state variable.
 */
void radio_comm_ClearCTS()
{
  ctsWentHigh = 0;
}

#if 0
//#elif (defined SILABS_RADIO_SI4012)

/*!
 * Gets a command response from the radio chip
 *
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 *
 * @return CTS value
 */
uint8_t radio_comm_GetResp(uint8_t byteCount, uint8_t* pData)
{
	uint8_t ctsVal = 0;
	uint16_t errCnt = RADIO_CTS_TIMEOUT;
	while (errCnt != 0)      //wait until radio IC is ready with the data
	{
		//radio_hal_ClearNsel();
			radio_hal_ClearNsel();
		radio_hal_SpiWriteByte(0x44);    //read CMD buffer
		ctsVal = radio_hal_SpiReadByte();
		if (ctsVal == 0xFF)
		{
			if (byteCount)
			{
				radio_hal_SpiReadData(byteCount, pData);
			}
			      radio_hal_SetNsel();
			break;
		}
		      radio_hal_SetNsel();
		errCnt--;
	}

	if (errCnt == 0)
	{
		while (1)
		{
			/* ERROR!!!!  CTS should never take this long. */
#ifdef RADIO_COMM_ERROR_CALLBACK
			RADIO_COMM_ERROR_CALLBACK();
#else
		break;
#endif
		}
	}

	if (ctsVal == 0xFF)
	{
		ctsWentHigh = 1;
	}

	return ctsVal;
}

/*!
 * Sends a command to the radio chip
 *
 * @param byteCount     Number of bytes in the command to send to the radio device
 * @param pData         Pointer to the command to send.
 */
void radio_comm_SendCmd(uint8_t byteCount, uint8_t* pData)
{
	char rc,count=10;
	while (!ctsWentHigh)
	{
		rc = radio_comm_PollCTS();
		count--;
		if(count == 0)
			break;
	}
	// radio_hal_ClearNsel();
	radio_hal_ClearNsel();
	radio_hal_SpiWriteData(byteCount, pData);
	radio_hal_SetNsel();
	//radio_hal_SetNsel();
	ctsWentHigh = 0;
}
#endif

/*!
 * Sends a command to the radio chip and gets a response
 *
 * @param cmdByteCount  Number of bytes in the command to send to the radio device
 * @param pCmdData      Pointer to the command data
 * @param respByteCount Number of bytes in the response to fetch
 * @param pRespData     Pointer to where to put the response data
 *
 * @return CTS value
 */
uint8_t radio_comm_SendCmdGetResp(uint8_t cmdByteCount, uint8_t* pCmdData, uint8_t respByteCount, uint8_t* pRespData)
{
	radio_comm_SendCmd(cmdByteCount, pCmdData);
	return radio_comm_GetResp(respByteCount, pRespData);
}

