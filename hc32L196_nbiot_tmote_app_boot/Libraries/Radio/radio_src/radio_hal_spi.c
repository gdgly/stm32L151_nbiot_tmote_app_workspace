/**
  *********************************************************************************************************
  * @file    radio_hal_spi.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-17
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
#include "radio_hal_spi.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void Radio_Hal_Spix_Init(void)
 @Description			Radio_Hal_Spix_Init							: Radio Hal Spix初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Hal_Spix_Init(void)
{
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI0_TYPE
	HC32_SPI0_Init();
#endif
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI1_TYPE
	HC32_SPI1_Init();
#endif
}

/**********************************************************************************************************
 @Function			u8 Radio_Hal_Spix_SendByte(u8 byte)
 @Description			Radio_Hal_Spix_SendByte						: Radio Hal Spix发送1字节
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Hal_Spix_SendByte(u8 byte)
{
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI0_TYPE
	return HC32_SPI0_SendByte(byte, RADIO_SPI_TRANSMIT_TIMEOUT);
#endif
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI1_TYPE
	return HC32_SPI1_SendByte(byte, RADIO_SPI_TRANSMIT_TIMEOUT);
#endif
}

/**********************************************************************************************************
 @Function			u8 Radio_Hal_Spix_ReadByte(u8 byte)
 @Description			Radio_Hal_Spix_ReadByte						: Radio Hal Spix读取1字节
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Radio_Hal_Spix_ReadByte(u8 byte)
{
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI0_TYPE
	return HC32_SPI0_ReadByte(byte, RADIO_SPI_TRANSMIT_TIMEOUT);
#endif
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI1_TYPE
	return HC32_SPI1_ReadByte(byte, RADIO_SPI_TRANSMIT_TIMEOUT);
#endif
}

/********************************************** END OF FLEE **********************************************/
