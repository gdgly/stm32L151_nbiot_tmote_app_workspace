/**
  *********************************************************************************************************
  * @file    radio_hal_wrap.c
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
#include "radio_hal_wrap.h"
#include "radio_hal_rf.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_ShutdownAssert(void)
 @Description			Radio_Hal_Wrapper_ShutdownAssert				: Radio Hal Wrapper Shutdown(SDN) Assert
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_ShutdownAssert(void)
{
	Gpio_SetIO(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN);
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_ShutdownDeassert(void)
 @Description			Radio_Hal_Wrapper_ShutdownDeassert				: Radio Hal Wrapper Shutdown(SDN) Deassert
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_ShutdownDeassert(void)
{
	Gpio_ClrIO(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN);
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_nSELAssert(void)
 @Description			Radio_Hal_Wrapper_nSELAssert					: Radio Hal Wrapper nSEL(NSS) Assert
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_nSELAssert(void)
{
	Gpio_SetIO(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN);
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_nSELDeassert(void)
 @Description			Radio_Hal_Wrapper_nSELDeassert				: Radio Hal Wrapper nSEL(NSS) Deassert
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_nSELDeassert(void)
{
	Gpio_ClrIO(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN);
}

/**********************************************************************************************************
 @Function			u8 Radio_Hal_Wrapper_nIRQLevel(void)
 @Description			Radio_Hal_Wrapper_nIRQLevel					: Radio Hal Wrapper nIRQ(IRQ) Read
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Hal_Wrapper_nIRQLevel(void)
{
	return Gpio_GetInputIO(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN);
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_Init(void)
 @Description			Radio_Hal_Wrapper_Init						: Radio Hal Wrapper初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_Init(void)
{
	Radio_Hal_Spix_Init();
}

/**********************************************************************************************************
 @Function			u8 Radio_Hal_Wrapper_SendByte(u8 byte)
 @Description			Radio_Hal_Wrapper_SendByte					: Radio Hal Wrapper发送1字节数据
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Hal_Wrapper_SendByte(u8 byte)
{
	return Radio_Hal_Spix_SendByte(byte);
}

/**********************************************************************************************************
 @Function			u8 Radio_Hal_Wrapper_ReadByte(u8 byte)
 @Description			Radio_Hal_Wrapper_ReadByte					: Radio Hal Wrapper读取1字节数据
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Hal_Wrapper_ReadByte(u8 byte)
{
	return Radio_Hal_Spix_ReadByte(byte);
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_SendData(u8 biDataLen, u8* pabiData)
 @Description			Radio_Hal_Wrapper_SendData					: Radio Hal Wrapper发送数据
 @Input				biDataLen									: 长度
					pabiData									: 数据
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_SendData(u8 biDataLen, u8* pabiData)
{
	while (biDataLen--) {
		Radio_Hal_Spix_SendByte(*pabiData++);
	}
}

/**********************************************************************************************************
 @Function			void Radio_Hal_Wrapper_ReadData(u8 boDataLen, u8* paboData)
 @Description			Radio_Hal_Wrapper_ReadData					: Radio Hal Wrapper读取数据
 @Input				boDataLen									: 长度
					paboData									: 数据
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Wrapper_ReadData(u8 boDataLen, u8* paboData)
{
	while (boDataLen--) {
		*paboData++ = Radio_Hal_Spix_ReadByte(RADIO_CMD_DUMMY_BYTE);
	}
}

/********************************************** END OF FLEE **********************************************/
