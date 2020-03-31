/**
  *********************************************************************************************************
  * @file    hal_spi.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-14
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_spi.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void SPI0_Port_Init(void)
 @Description			SPI0_Port_Init								: HC32 SPI0引脚初始化
 @Input				void
 @Return				void
 @attention			SPI0_SCLK => PA05
					SPI0_MISO => PA06
					SPI0_MOSI => PA07
**********************************************************************************************************/
static void SPI0_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* SPI0_SCLK => PA05 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI0_SCLK_GPIOx, SPI0_SCLK_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI0_SCLK_GPIOx, SPI0_SCLK_PIN, SPI0_SCLK_AF);
	
	/* SPI0_MOSI => PA07 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI0_MOSI_GPIOx, SPI0_MOSI_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI0_MOSI_GPIOx, SPI0_MOSI_PIN, SPI0_MOSI_AF);
	
	/* SPI0_MISO => PA06 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI0_MISO_GPIOx, SPI0_MISO_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI0_MISO_GPIOx, SPI0_MISO_PIN, SPI0_MISO_AF);
}

/**********************************************************************************************************
 @Function			static void SPI1_Port_Init(void)
 @Description			SPI1_Port_Init								: HC32 SPI1引脚初始化
 @Input				void
 @Return				void
 @attention			SPI1_SCLK => PB13
					SPI1_MISO => PB14
					SPI1_MOSI => PB15
**********************************************************************************************************/
static void SPI1_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* SPI1_SCLK => PB13 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI1_SCLK_GPIOx, SPI1_SCLK_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI1_SCLK_GPIOx, SPI1_SCLK_PIN, SPI1_SCLK_AF);
	
	/* SPI1_MOSI => PB15 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI1_MOSI_GPIOx, SPI1_MOSI_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI1_MOSI_GPIOx, SPI1_MOSI_PIN, SPI1_MOSI_AF);
	
	/* SPI1_MISO => PB14 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(SPI1_MISO_GPIOx, SPI1_MISO_PIN, &GPIO_Initure);
	Gpio_SetAfMode(SPI1_MISO_GPIOx, SPI1_MISO_PIN, SPI1_MISO_AF);
}

/**********************************************************************************************************
 @Function			void HC32_SPI0_Init(void)
 @Description			HC32_SPI0_Init								: HC32 SPI0初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_SPI0_Init(void)
{
	stc_spi_cfg_t SPI_Initure;
	
	SPI0_Port_Init();
	
	DDL_ZERO_STRUCT(SPI_Initure);
	
	SPI_Initure.enSpiMode		= SpiMskMaster;											//SPI Master
	SPI_Initure.enPclkDiv		= SpiClkMskDiv4;											//SPI CLK PLCK/DIV4 Mast 4MHz
	SPI_Initure.enCPHA			= SpiMskCphafirst;											//SPI CLK Mode 0
	SPI_Initure.enCPOL			= SpiMskcpollow;											//SPI CLK Mode 0
	Spi_Init(M0P_SPI0, &SPI_Initure);
}

/**********************************************************************************************************
 @Function			void HC32_SPI1_Init(void)
 @Description			HC32_SPI1_Init								: HC32 SPI1初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_SPI1_Init(void)
{
	stc_spi_cfg_t SPI_Initure;
	
	SPI1_Port_Init();
	
	DDL_ZERO_STRUCT(SPI_Initure);
	
	SPI_Initure.enSpiMode		= SpiMskMaster;											//SPI Master
	SPI_Initure.enPclkDiv		= SpiClkMskDiv4;											//SPI CLK PLCK/DIV4 Mast 4MHz
	SPI_Initure.enCPHA			= SpiMskCphafirst;											//SPI CLK Mode 0
	SPI_Initure.enCPOL			= SpiMskcpollow;											//SPI CLK Mode 0
	Spi_Init(M0P_SPI1, &SPI_Initure);
}

/**********************************************************************************************************
 @Function			u8 HC32_SPI0_SendByte(u8 byte, u32 timeout)
 @Description			HC32_SPI0_SendByte							: HC32 SPI0发送一个字节数据
 @Input				byte										: 发送的数据
					timeout									: 超时时间MS
 @Return				void
**********************************************************************************************************/
u8 HC32_SPI0_SendByte(u8 byte, u32 timeout)
{
	timeMeterTypeDef spiTimer;
	
	HC32_TimeMeter_CountdownMS(&spiTimer, timeout);
	
	while (Spi_GetStatus(M0P_SPI0, SpiTxe) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	Spi_SendData(M0P_SPI0, byte);
	
	return byte;
}

/**********************************************************************************************************
 @Function			u8 HC32_SPI1_SendByte(u8 byte, u32 timeout)
 @Description			HC32_SPI1_SendByte							: HC32 SPI1发送一个字节数据
 @Input				byte										: 发送的数据
					timeout									: 超时时间MS
 @Return				void
**********************************************************************************************************/
u8 HC32_SPI1_SendByte(u8 byte, u32 timeout)
{
	timeMeterTypeDef spiTimer;
	
	HC32_TimeMeter_CountdownMS(&spiTimer, timeout);
	
	while (Spi_GetStatus(M0P_SPI1, SpiTxe) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	Spi_SendData(M0P_SPI1, byte);
	
	return byte;
}

/**********************************************************************************************************
 @Function			u8 HC32_SPI0_ReadByte(u8 byte, u32 timeout)
 @Description			HC32_SPI0_ReadByte							: HC32 SPI0读取一个字节数据
 @Input				byte										: 发送的数据
					timeout									: 超时时间MS
 @Return				byte										: 读取的数据
**********************************************************************************************************/
u8 HC32_SPI0_ReadByte(u8 byte, u32 timeout)
{
	u8 readByte = 0x00;
	
	timeMeterTypeDef spiTimer;
	
	HC32_TimeMeter_CountdownMS(&spiTimer, timeout);
	
	while (Spi_GetStatus(M0P_SPI0, SpiTxe) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	Spi_SendData(M0P_SPI0, byte);
	Delay_US(20);
	while (Spi_GetStatus(M0P_SPI0, SpiRxne) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	readByte = Spi_ReceiveData(M0P_SPI0);
	
	return readByte;
}

/**********************************************************************************************************
 @Function			u8 HC32_SPI1_ReadByte(u8 byte, u32 timeout)
 @Description			HC32_SPI1_ReadByte							: HC32 SPI1读取一个字节数据
 @Input				byte										: 发送的数据
					timeout									: 超时时间MS
 @Return				byte										: 读取的数据
**********************************************************************************************************/
u8 HC32_SPI1_ReadByte(u8 byte, u32 timeout)
{
	u8 readByte = 0x00;
	
	timeMeterTypeDef spiTimer;
	
	HC32_TimeMeter_CountdownMS(&spiTimer, timeout);
	
	while (Spi_GetStatus(M0P_SPI1, SpiTxe) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	Spi_SendData(M0P_SPI1, byte);
	Delay_US(20);
	while (Spi_GetStatus(M0P_SPI1, SpiRxne) == FALSE) {
		if (HC32_TimeMeter_IsExpiredMS(&spiTimer)) break;
	}
	readByte = Spi_ReceiveData(M0P_SPI1);
	
	return readByte;
}

/********************************************** END OF FLEE **********************************************/
