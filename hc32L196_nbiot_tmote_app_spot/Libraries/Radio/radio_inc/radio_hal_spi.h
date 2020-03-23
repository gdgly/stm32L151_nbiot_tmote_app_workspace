#ifndef __RADIO_HAL_SPI_H
#define   __RADIO_HAL_SPI_H

#include "sys.h"
#include "gpio.h"
#include "hal_spi.h"

#define RADIO_SPI0_TYPE			0
#define RADIO_SPI1_TYPE			1
#define RADIO_HAL_SPIx_TYPE		RADIO_SPI0_TYPE

#if RADIO_HAL_SPIx_TYPE == RADIO_SPI0_TYPE
#define RADIO_SPIx_NSS_ENABLE()	SPI0_NSS_ENABLE()
#define RADIO_SPIx_NSS_DISABLE()	SPI0_NSS_DISABLE()
#endif
#if RADIO_HAL_SPIx_TYPE == RADIO_SPI1_TYPE
#define RADIO_SPIx_NSS_ENABLE()	SPI1_NSS_ENABLE()
#define RADIO_SPIx_NSS_DISABLE()	SPI1_NSS_DISABLE()
#endif

#define RADIO_SPI_TRANSMIT_TIMEOUT	100

void Radio_Hal_Spix_Init(void);															//Radio Hal Spix初始化

u8   Radio_Hal_Spix_SendByte(u8 byte);														//Radio Hal Spix发送1字节

u8   Radio_Hal_Spix_ReadByte(u8 byte);														//Radio Hal Spix读取1字节

#endif /* __RADIO_HAL_SPI_H */
