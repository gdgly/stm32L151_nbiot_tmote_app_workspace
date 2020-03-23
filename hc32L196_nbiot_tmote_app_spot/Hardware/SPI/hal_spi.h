#ifndef __HAL_SPI_H
#define   __HAL_SPI_H

#include "sys.h"
#include "gpio.h"
#include "spi.h"

#define SPI0_SCLK_GPIOx			GpioPortA
#define SPI0_SCLK_PIN			GpioPin5
#define SPI0_SCLK_AF			GpioAf1

#define SPI0_MISO_GPIOx			GpioPortA
#define SPI0_MISO_PIN			GpioPin6
#define SPI0_MISO_AF			GpioAf1

#define SPI0_MOSI_GPIOx			GpioPortA
#define SPI0_MOSI_PIN			GpioPin7
#define SPI0_MOSI_AF			GpioAf1

#define SPI1_SCLK_GPIOx			GpioPortB
#define SPI1_SCLK_PIN			GpioPin13
#define SPI1_SCLK_AF			GpioAf1

#define SPI1_MISO_GPIOx			GpioPortB
#define SPI1_MISO_PIN			GpioPin14
#define SPI1_MISO_AF			GpioAf1

#define SPI1_MOSI_GPIOx			GpioPortB
#define SPI1_MOSI_PIN			GpioPin15
#define SPI1_MOSI_AF			GpioAf1

#define SPI0_NSS_ENABLE()		Spi_SetCS(M0P_SPI0, FALSE)
#define SPI0_NSS_DISABLE()		Spi_SetCS(M0P_SPI0, TRUE)

#define SPI1_NSS_ENABLE()		Spi_SetCS(M0P_SPI1, FALSE)
#define SPI1_NSS_DISABLE()		Spi_SetCS(M0P_SPI1, TRUE)

void HC32_SPI0_Init(void);																//HC32 SPI0初始化
u8   HC32_SPI0_SendByte(u8 byte, u32 timeout);												//HC32 SPI0发送一个字节数据
u8   HC32_SPI0_ReadByte(u8 byte, u32 timeout);												//HC32 SPI0读取一个字节数据

void HC32_SPI1_Init(void);																//HC32 SPI1初始化
u8   HC32_SPI1_SendByte(u8 byte, u32 timeout);												//HC32 SPI1发送一个字节数据
u8   HC32_SPI1_ReadByte(u8 byte, u32 timeout);												//HC32 SPI1读取一个字节数据

#endif /* __HAL_SPI_H */
