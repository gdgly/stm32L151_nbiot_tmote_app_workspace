#ifndef __HAL_P25QXXH_H
#define   __HAL_P25QXXH_H

#include "sys.h"
#include "gpio.h"
#include "hal_spi.h"

#define SPI0_TYPE				0
#define SPI1_TYPE				1
#define P25QXXH_SPIx_TYPE		SPI0_TYPE

#define P25QXXH_TRANSMIT_TIMEOUT	500
#define P25QXXH_EXECUTED_TIMEOUT	500

#define P25QXXH_SPIx_NSS_GPIOx	GpioPortB
#define P25QXXH_SPIx_NSS_PIN		GpioPin12
#define P25QXXH_SPIx_NSS_AF		GpioAf0

#if P25QXXH_SPIx_TYPE == SPI0_TYPE
#define P25QXXH_SPIx_NSS_ENABLE()	{Gpio_ClrIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN); SPI0_NSS_ENABLE();}
#define P25QXXH_SPIx_NSS_DISABLE()	{SPI0_NSS_DISABLE(); Gpio_SetIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN);}
#endif
#if P25QXXH_SPIx_TYPE == SPI1_TYPE
#define P25QXXH_SPIx_NSS_ENABLE()	{Gpio_ClrIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN); SPI1_NSS_ENABLE();}
#define P25QXXH_SPIx_NSS_DISABLE()	{SPI1_NSS_DISABLE(); Gpio_SetIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN);}
#endif

#define P25Q40H_BASE_ADDR		0x00000000U												//P25Q40H Base Addr
#define P25Q40H_CHIP512K_BYTE_SIZE	0x00080000U												//P25Q40H Chip512K Byte Size
#define P25Q40H_BLOCK64K_BYTE_SIZE	0x00010000U												//P25Q40H Block64K Byte Size
#define P25Q40H_BLOCK32K_BYTE_SIZE	0x00008000U												//P25Q40H Block32K Byte Size
#define P25Q40H_SECTOR4K_BYTE_SIZE	0x00001000U												//P25Q40H Sector4K Byte Size
#define P25Q40H_PAGE256B_BYTE_SIZE	0x00000100U												//P25Q40H Page256B Byte Size

#define P25Q40H_BLOCK64K_ADDR_0	((u32)( 0 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_1	((u32)( 1 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_2	((u32)( 2 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_3	((u32)( 3 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_4	((u32)( 4 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_5	((u32)( 5 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_6	((u32)( 6 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK64K_ADDR_7	((u32)( 7 * P25Q40H_BLOCK64K_BYTE_SIZE) + P25Q40H_BASE_ADDR)

#define P25Q40H_BLOCK32K_ADDR_00	((u32)( 0 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_01	((u32)( 1 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_02	((u32)( 2 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_03	((u32)( 3 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_04	((u32)( 4 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_05	((u32)( 5 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_06	((u32)( 6 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_07	((u32)( 7 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_08	((u32)( 8 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_09	((u32)( 9 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_10	((u32)(10 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_11	((u32)(11 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_12	((u32)(12 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_13	((u32)(13 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_14	((u32)(14 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_BLOCK32K_ADDR_15	((u32)(15 * P25Q40H_BLOCK32K_BYTE_SIZE) + P25Q40H_BASE_ADDR)

#define P25Q40H_SECTOR4K_ADDR(n)	((u32)(n  * P25Q40H_SECTOR4K_BYTE_SIZE) + P25Q40H_BASE_ADDR)
#define P25Q40H_PAGE256B_ADDR(n)	((u32)(n  * P25Q40H_PAGE256B_BYTE_SIZE) + P25Q40H_BASE_ADDR)

#define P25Q40H_ELECTRONIC_ID		0x00000012U												//P25Q40H ElectronicID
#define P25Q40H_MDEVICE_ID		0x00008512U												//P25Q40H MDeviceID
#define P25Q40H_JEDEC_ID			0x00856013U												//P25Q40H JedecID

#define GD25Q80_ELECTRONIC_ID		0x00000013U												//GD25Q80 ElectronicID
#define GD25Q80_MDEVICE_ID		0x0000C813U												//GD25Q80 MDeviceID
#define GD25Q80_JEDEC_ID			0x00C84014U												//GD25Q80 JedecID

#define GD25Q40_ELECTRONIC_ID		0x00000012U												//GD25Q40 ElectronicID
#define GD25Q40_MDEVICE_ID		0x0000C812U												//GD25Q40 MDeviceID
#define GD25Q40_JEDEC_ID			0x00C84013U												//GD25Q40 JedecID

#define P25QXXH_CMD_DUMMY_BYTE	0xFF														//Dymmy Byte
#define P25QXXH_CMD_ELECTRONIC_ID	0xAB														//Electronic ID
#define P25QXXH_CMD_MDEVICE_ID	0x90														//Manufacturer & Device ID
#define P25QXXH_CMD_JEDEC_ID		0x9F														//Jedec ID
#define P25QXXH_CMD_WREN			0x06														//Write Enable
#define P25QXXH_CMD_WRDI			0x04														//Write Disable
#define P25QXXH_CMD_VWREN		0x50														//Write Enable for Volatile Status Register
#define P25QXXH_CMD_RDSR1		0x05														//Read Status Register1
#define P25QXXH_CMD_RDSR2		0x35														//Read Status Register2
#define P25QXXH_CMD_WRSR			0x01														//Write data to status/configuration registers
#define P25QXXH_CMD_PWRDN		0xB9														//Enters deep power-down mode
#define P25QXXH_CMD_RPWRDN		0xAB														//Release deep Power-down mode
#define P25QXXH_CMD_CE			0xC7														//Erase whole chip
#define P25QXXH_CMD_BE64			0xD8														//Erase selected 64K block
#define P25QXXH_CMD_BE32			0x52														//Erase selected 32K block
#define P25QXXH_CMD_SE			0x20														//Erase selected  4K sector
#define P25QXXH_CMD_PE			0x81														//Erase selected 256 Byte
#define P25QXXH_CMD_READ			0x03														//Read Array (low power) n bytes read out until
#define P25QXXH_CMD_FREAD		0x0B														//Read Array (fast) n bytes read out until
#define P25QXXH_CMD_PP			0x02														//Program selected page
#define P25QXXH_CMD_RSTEN		0x66														//Enable reset
#define P25QXXH_CMD_RST			0x99														//Reset

#define P25QXXH_REG_WIP			(1<<0)													//When WIP bit sets to 1, means the device is busy
#define P25QXXH_REG_WEL			(1<<1)													//When WEL bit sets to 1, the internal Write Enable Latch is set

void P25QXXH_Init(void);																	//P25QXXH初始化
u8   P25QXXH_SendByte(u8 byte);															//P25QXXH发送1字节
u8   P25QXXH_ReadByte(u8 byte);															//P25QXXH读取1字节

u32  P25QXXH_ReadElectronicID(void);														//P25QXXH读取ElectronicID
u32  P25QXXH_ReadMDeviceID(void);															//P25QXXH读取MDeviceID
u32  P25QXXH_ReadJedecID(void);															//P25QXXH读取JedecID

void P25QXXH_WriteEnable(void);															//P25QXXH写非易失性寄存器使能
void P25QXXH_WriteDisable(void);															//P25QXXH写禁止
void P25QXXH_WriteVolatileEnable(void);														//P25QXXH写易易失性寄存器使能

u8   P25QXXH_ReadStatusRegister1(void);														//P25QXXH读取状态寄存器1
u8   P25QXXH_ReadStatusRegister2(void);														//P25QXXH读取状态寄存器2

void P25QXXH_WriteStatusRegisterNoVolatile(u16 dat);											//P25QXXH写入状态寄存器(非易失性)
void P25QXXH_WriteStatusRegisterIsVolatile(u16 dat);											//P25QXXH写入状态寄存器(易易失性)

void P25QXXH_WaitForBusy(u32 timeout);														//P25QXXH等待设备空闲

void P25QXXH_SendForAddress(u32 addr);														//P25QXXH发送地址值

void P25QXXH_EnterDeepPowerDownMode(void);													//P25QXXH进入深度休眠模式
void P25QXXH_ReleaseDeepPowerDownMode(void);													//P25QXXH退出深度休眠模式

void P25QXXH_EraseChip(void);																//P25QXXH全片擦除
void P25QXXH_EraseBlock(u8 blockType, u32 blockAddr);											//P25QXXH区块擦除
void P25QXXH_EraseSector(u32 sectorAddr);													//P25QXXH扇区擦除
void P25QXXH_ErasePage(u32 pageAddr);														//P25QXXH页区擦除

void P25QXXH_ReadBufferNormal(u8* pBuf, u32 readAddr, u32 numByte);								//P25QXXH读取数据(普通)
void P25QXXH_ReadBufferFast(u8* pBuf, u32 readAddr, u32 numByte);								//P25QXXH读取数据(快速)

void P25QXXH_WritePage(u8* pBuf, u32 writeAddr, u32 numByte);									//P25QXXH写入数据(页写)
void P25QXXH_WriteBuffer(u8* pBuf, u32 writeAddr, u32 numByte);									//P25QXXH写入数据(片写)

void P25QXXH_SoftwareReset(void);															//P25QXXH软件复位

u32  P25QXXH_GetNumByteOfThisData(u32 readAddr, u32 numByte, u8 thisData);							//P25QXXH读取指定地址中指定数据中有该值的个数

#endif /* __HAL_P25QXXH_H */
