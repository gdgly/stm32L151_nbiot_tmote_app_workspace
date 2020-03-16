/**
  *********************************************************************************************************
  * @file    hal_bl24cxxp.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-13
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
#include "hal_p25qxxh.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void P25QXXH_Port_Init(void)
 @Description			P25QXXH_Port_Init							: P25QXXH引脚初始化
 @Input				void
 @Return				void
 @attention			P25QXXH_NSS => PB12
**********************************************************************************************************/
static void P25QXXH_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* P25QXXH_NSS => PB12 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, P25QXXH_SPIx_NSS_AF);
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_Init(void)
 @Description			P25QXXH_Init								: P25QXXH初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void P25QXXH_Init(void)
{
#if P25QXXH_SPIx_TYPE == SPI0_TYPE
	HC32_SPI0_Init();
#endif
#if P25QXXH_SPIx_TYPE == SPI1_TYPE
	HC32_SPI1_Init();
#endif
	
	P25QXXH_Port_Init();
}

/**********************************************************************************************************
 @Function			u8 P25QXXH_SendByte(u8 byte)
 @Description			P25QXXH_SendByte							: P25QXXH发送1字节
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 P25QXXH_SendByte(u8 byte)
{
#if P25QXXH_SPIx_TYPE == SPI0_TYPE
	return HC32_SPI0_SendByte(byte, P25QXXH_TRANSMIT_TIMEOUT);
#endif
#if P25QXXH_SPIx_TYPE == SPI1_TYPE
	return HC32_SPI1_SendByte(byte, P25QXXH_TRANSMIT_TIMEOUT);
#endif
}

/**********************************************************************************************************
 @Function			u8 P25QXXH_ReadByte(u8 byte)
 @Description			P25QXXH_ReadByte							: P25QXXH读取1字节
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 P25QXXH_ReadByte(u8 byte)
{
#if P25QXXH_SPIx_TYPE == SPI0_TYPE
	return HC32_SPI0_ReadByte(byte, P25QXXH_TRANSMIT_TIMEOUT);
#endif
#if P25QXXH_SPIx_TYPE == SPI1_TYPE
	return HC32_SPI1_ReadByte(byte, P25QXXH_TRANSMIT_TIMEOUT);
#endif
}

/**********************************************************************************************************
 @Function			u32 P25QXXH_ReadElectronicID(void)
 @Description			P25QXXH_ReadElectronicID						: P25QXXH读取ElectronicID
 @Input				void
 @Return				ElectronicID
**********************************************************************************************************/
u32 P25QXXH_ReadElectronicID(void)
{
	u32 ElectronicID = 0;
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_ELECTRONIC_ID);
	P25QXXH_SendByte(P25QXXH_CMD_DUMMY_BYTE);
	P25QXXH_SendByte(P25QXXH_CMD_DUMMY_BYTE);
	P25QXXH_SendByte(P25QXXH_CMD_DUMMY_BYTE);
	
	ElectronicID = P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	return ElectronicID;
}

/**********************************************************************************************************
 @Function			u32 P25QXXH_ReadMDeviceID(void)
 @Description			P25QXXH_ReadMDeviceID						: P25QXXH读取MDeviceID
 @Input				void
 @Return				MDeviceID
**********************************************************************************************************/
u32 P25QXXH_ReadMDeviceID(void)
{
	u32 MDeviceID = 0;
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_MDEVICE_ID);
	P25QXXH_SendByte(0x00);
	P25QXXH_SendByte(0x00);
	P25QXXH_SendByte(0x00);
	
	MDeviceID |= P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE) << 8;
	MDeviceID |= P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE) << 0;
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	return MDeviceID;
}

/**********************************************************************************************************
 @Function			u32 P25QXXH_ReadJedecID(void)
 @Description			P25QXXH_ReadJedecID							: P25QXXH读取JedecID
 @Input				void
 @Return				JedecID
**********************************************************************************************************/
u32 P25QXXH_ReadJedecID(void)
{
	u32 JedecID = 0;
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_JEDEC_ID);
	
	JedecID |= P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE) << 16;
	JedecID |= P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE) <<  8;
	JedecID |= P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE) <<  0;
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	return JedecID;
}

/**********************************************************************************************************
 @Function			void P25QXXH_WriteEnable(void)
 @Description			P25QXXH_WriteEnable							: P25QXXH写使能
 @Input				void
 @Return				void
 @attention			WEL置位
**********************************************************************************************************/
void P25QXXH_WriteEnable(void)
{
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_WREN);
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_WriteDisable(void)
 @Description			P25QXXH_WriteDisable						: P25QXXH写禁止
 @Input				void
 @Return				void
 @attention			WEL清零
**********************************************************************************************************/
void P25QXXH_WriteDisable(void)
{
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_WRDI);
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_WriteVolatileEnable(void)
 @Description			P25QXXH_WriteVolatileEnable					: P25QXXH写易失性寄存器使能
 @Input				void
 @Return				void
**********************************************************************************************************/
void P25QXXH_WriteVolatileEnable(void)
{
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_VWREN);
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			u8 P25QXXH_ReadStatusRegister1(void)
 @Description			P25QXXH_ReadStatusRegister1					: P25QXXH读取状态寄存器1
 @Input				void
 @Return				SR1
**********************************************************************************************************/
u8 P25QXXH_ReadStatusRegister1(void)
{
	u8 readByte = 0;
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_RDSR1);
	readByte = P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	return readByte;
}

/**********************************************************************************************************
 @Function			u8 P25QXXH_ReadStatusRegister2(void)
 @Description			P25QXXH_ReadStatusRegister2					: P25QXXH读取状态寄存器2
 @Input				void
 @Return				SR2
**********************************************************************************************************/
u8 P25QXXH_ReadStatusRegister2(void)
{
	u8 readByte = 0;
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_RDSR2);
	readByte = P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	return readByte;
}

/**********************************************************************************************************
 @Function			void P25QXXH_WriteStatusRegisterNoVolatile(u16 dat)
 @Description			P25QXXH_WriteStatusRegisterNoVolatile			: P25QXXH写入状态寄存器(非易失性)
 @Input				dat
 @Return				void
**********************************************************************************************************/
void P25QXXH_WriteStatusRegisterNoVolatile(u16 dat)
{
	P25QXXH_WriteEnable();
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_WRSR);
	P25QXXH_SendByte((u8)(dat>>0));
	P25QXXH_SendByte((u8)(dat>>8));
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_WriteStatusRegisterIsVolatile(u16 dat)
 @Description			P25QXXH_WriteStatusRegisterIsVolatile			: P25QXXH写入状态寄存器(易易失性)
 @Input				dat
 @Return				void
**********************************************************************************************************/
void P25QXXH_WriteStatusRegisterIsVolatile(u16 dat)
{
	P25QXXH_WriteVolatileEnable();
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_WRSR);
	P25QXXH_SendByte((u8)(dat>>0));
	P25QXXH_SendByte((u8)(dat>>8));
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_WaitForBusy(u32 timeout)
 @Description			P25QXXH_WaitForBusy							: P25QXXH等待设备空闲
 @Input				timeout
 @Return				void
**********************************************************************************************************/
void P25QXXH_WaitForBusy(u32 timeout)
{
	u8 readByte = 0;
	
	timeMeterTypeDef P25QXXTimer;
	
	HC32_TimeMeter_CountdownMS(&P25QXXTimer, timeout);
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_RDSR1);
	
	do {
		readByte = P25QXXH_ReadByte(P25QXXH_CMD_DUMMY_BYTE);
		
		if (HC32_TimeMeter_IsExpiredMS(&P25QXXTimer)) break;
	}
	while ((readByte & P25QXXH_REG_WIP) == 0x01);
	
	P25QXXH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void P25QXXH_EnterDeepPowerDownMode(void)
 @Description			P25QXXH_EnterDeepPowerDownMode				: P25QXXH进入深度休眠模式
 @Input				void
 @Return				void
**********************************************************************************************************/
void P25QXXH_EnterDeepPowerDownMode(void)
{
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_PWRDN);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	Delay_US(5);
}

/**********************************************************************************************************
 @Function			void P25QXXH_ReleaseDeepPowerDownMode(void)
 @Description			P25QXXH_ReleaseDeepPowerDownMode				: P25QXXH退出深度休眠模式
 @Input				void
 @Return				void
**********************************************************************************************************/
void P25QXXH_ReleaseDeepPowerDownMode(void)
{
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_RPWRDN);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	Delay_US(10);
}

/**********************************************************************************************************
 @Function			void P25QXXH_EraseChip(void)
 @Description			P25QXXH_EraseChip							: P25QXXH全片擦除
 @Input				void
 @Return				void
**********************************************************************************************************/
void P25QXXH_EraseChip(void)
{
	P25QXXH_WriteEnable();
	
	P25QXXH_WaitForBusy(P25QXXH_MAX_CHIP_ERASE_T);
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(P25QXXH_CMD_CE);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	P25QXXH_WaitForBusy(P25QXXH_MAX_CHIP_ERASE_T);
}

/**********************************************************************************************************
 @Function			void P25QXXH_EraseBlock(u8 blockType, u32 blockAddr)
 @Description			P25QXXH_EraseBlock							: P25QXXH区块擦除
 @Input				blockType									: P25QXXH_CMD_BE64 or P25QXXH_CMD_BE32
					blockAddr									: Block Address
 @Return				void
**********************************************************************************************************/
void P25QXXH_EraseBlock(u8 blockType, u32 blockAddr)
{
	P25QXXH_WriteEnable();
	
	P25QXXH_WaitForBusy(P25QXXH_MAX_BLOCK_ERASE_T);
	
	P25QXXH_SPIx_NSS_ENABLE();
	
	P25QXXH_SendByte(blockType);
	
	P25QXXH_SendByte((blockAddr & 0x00FF0000) >> 16);
	P25QXXH_SendByte((blockAddr & 0x0000FF00) >>  8);
	P25QXXH_SendByte((blockAddr & 0x000000FF) >>  0);
	
	P25QXXH_SPIx_NSS_DISABLE();
	
	P25QXXH_WaitForBusy(P25QXXH_MAX_BLOCK_ERASE_T);
}
































/********************************************** END OF FLEE **********************************************/
