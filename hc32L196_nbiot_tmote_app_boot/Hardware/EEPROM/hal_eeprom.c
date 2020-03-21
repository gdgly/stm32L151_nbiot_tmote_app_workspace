/**
  *********************************************************************************************************
  * @file    hal_eeprom.c
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
#include "hal_eeprom.h"
#include "delay.h"
#include "usart.h"

static __IO en_result_t EEPROM_Status = Error;

/**********************************************************************************************************
 @Function			void FLASH_EEPROM_Init(void)
 @Description			FLASH_EEPROM_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void FLASH_EEPROM_Init(void)
{
#ifdef EPROM_BL24CXX
	BL24CXX_Init();
	
	if (BL24CXX_Check())
		EEPROM_Status = Error;
	else
		EEPROM_Status = Ok;
#endif
}

/**********************************************************************************************************
 @Function			u8 FLASH_EEPROM_Status(void)
 @Description			FLASH_EEPROM_Status
 @Input				void
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u8 FLASH_EEPROM_Status(void)
{
#ifdef EPROM_BL24CXX
	return (u8)EEPROM_Status;
#else
	return (u8)Error;
#endif
}

/**********************************************************************************************************
 @Function			u8 FLASH_EEPROM_ReadByte(u32 addr)
 @Description			FLASH_EEPROM_ReadByte
 @Input				addr
 @Return				data
**********************************************************************************************************/
u8 FLASH_EEPROM_ReadByte(u32 addr)
{
	if (FLASH_EEPROM_Status()) return 0;
	
	return BL24CXX_ReadOneByte(addr);
}

/**********************************************************************************************************
 @Function			u8 FLASH_EEPROM_WriteByte(u32 addr, u8 data)
 @Description			FLASH_EEPROM_WriteByte
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u8 FLASH_EEPROM_WriteByte(u32 addr, u8 data)
{
	if (FLASH_EEPROM_Status()) return 1;
	
	for (int nCount = 0; nCount < EEPROM_DUPLICATION_COUNT; nCount++) {
		if (FLASH_EEPROM_ReadByte(addr) != data) {
			BL24CXX_WriteOneByte(addr, data);
		}
		else {
			break;
		}
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			u16 FLASH_EEPROM_ReadHalfWord(u32 addr)
 @Description			FLASH_EEPROM_ReadHalfWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u16 FLASH_EEPROM_ReadHalfWord(u32 addr)
{
	u16 val = 0;
	
	if (FLASH_EEPROM_Status()) return 0;
	
	*((unsigned char*)(&val) + 0) = BL24CXX_ReadOneByte(addr + 0);
	*((unsigned char*)(&val) + 1) = BL24CXX_ReadOneByte(addr + 1);
	
	return val;
}

/**********************************************************************************************************
 @Function			u16 FLASH_EEPROM_WriteHalfWord(u32 addr, u16 data)
 @Description			FLASH_EEPROM_WriteHalfWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u16 FLASH_EEPROM_WriteHalfWord(u32 addr, u16 data)
{
	if (FLASH_EEPROM_Status()) return 1;
	
	for (int nCount = 0; nCount < EEPROM_DUPLICATION_COUNT; nCount++) {
		if (FLASH_EEPROM_ReadHalfWord(addr) != data) {
			BL24CXX_WriteOneByte(addr + 0, *((unsigned char*)(&data) + 0));
			BL24CXX_WriteOneByte(addr + 1, *((unsigned char*)(&data) + 1));
		}
		else {
			break;
		}
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 FLASH_EEPROM_ReadWord(u32 addr)
 @Description			FLASH_EEPROM_ReadWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u32 FLASH_EEPROM_ReadWord(u32 addr)
{
	u32 val = 0;
	
	if (FLASH_EEPROM_Status()) return 0;
	
	*((unsigned char*)(&val) + 0) = BL24CXX_ReadOneByte(addr + 0);
	*((unsigned char*)(&val) + 1) = BL24CXX_ReadOneByte(addr + 1);
	*((unsigned char*)(&val) + 2) = BL24CXX_ReadOneByte(addr + 2);
	*((unsigned char*)(&val) + 3) = BL24CXX_ReadOneByte(addr + 3);
	
	return val;
}

/**********************************************************************************************************
 @Function			u32 FLASH_EEPROM_WriteWord(u32 addr, u32 data)
 @Description			FLASH_EEPROM_WriteWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u32 FLASH_EEPROM_WriteWord(u32 addr, u32 data)
{
	if (FLASH_EEPROM_Status()) return 1;
	
	for (int nCount = 0; nCount < EEPROM_DUPLICATION_COUNT; nCount++) {
		if (FLASH_EEPROM_ReadWord(addr) != data) {
			BL24CXX_WriteOneByte(addr + 0, *((unsigned char*)(&data) + 0));
			BL24CXX_WriteOneByte(addr + 1, *((unsigned char*)(&data) + 1));
			BL24CXX_WriteOneByte(addr + 2, *((unsigned char*)(&data) + 2));
			BL24CXX_WriteOneByte(addr + 3, *((unsigned char*)(&data) + 3));
		}
		else {
			break;
		}
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 FLASH_EEPROM_ReadBuffer(u32 addr, u8* buf, u16 len)
 @Description			FLASH_EEPROM_ReadBuffer
 @Input				addr
					buf
					len
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u8 FLASH_EEPROM_ReadBuffer(u32 addr, u8* buf, u16 len)
{
	if (FLASH_EEPROM_Status()) return 1;
	
	BL24CXX_ReadBuffer(addr, buf, len);
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 FLASH_EEPROM_WriteBuffer(u32 addr, u8* buf, u16 len)
 @Description			FLASH_EEPROM_WriteBuffer
 @Input				addr
					buf
					len
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u8 FLASH_EEPROM_WriteBuffer(u32 addr, u8* buf, u16 len)
{
	if (FLASH_EEPROM_Status()) return 1;
	
	BL24CXX_WriteBuffer(addr, buf, len);
	
	return 0;
}

/********************************************** END OF FLEE **********************************************/
