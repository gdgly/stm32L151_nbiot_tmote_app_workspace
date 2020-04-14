/**
  *********************************************************************************************************
  * @file    hal_norflash.c
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
#include "hal_norflash.h"
#include "delay.h"
#include "usart.h"

static __IO en_result_t NOR_Status = Error;

/**********************************************************************************************************
 @Function			void FLASH_NOR_Init(void)
 @Description			FLASH_NOR_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void FLASH_NOR_Init(void)
{
#ifdef FLASH_P25QXXH
	P25QXXH_Init();
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	for (int nCount = 0; nCount < 3; nCount++) {
		if (((P25QXXH_ReadMDeviceID() & 0xFF) != P25Q40H_ELECTRONIC_ID) && ((P25QXXH_ReadMDeviceID() & 0xFF) != GD25Q80_ELECTRONIC_ID)) {
			NOR_Status = Error;
		}
		else {
			NOR_Status = Ok;
			break;
		}
	}
	
	P25QXXH_EnterDeepPowerDownMode();
#endif
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_Status(void)
 @Description			FLASH_NOR_Status
 @Input				void
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 FLASH_NOR_Status(void)
{
#ifdef FLASH_P25QXXH
	return (u32)NOR_Status;
#else
	return (u32)Error;
#endif
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_SoftwareReset(void)
 @Description			FLASH_NOR_SoftwareReset
 @Input				void
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 FLASH_NOR_SoftwareReset(void)
{
	if (FLASH_NOR_Status()) return 1;
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	P25QXXH_SoftwareReset();
	
	P25QXXH_EnterDeepPowerDownMode();
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_Erase(norflash_erase_mode_t mode, u32 addr)
 @Description			FLASH_NOR_Erase
 @Input				mode
					addr
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 FLASH_NOR_Erase(norflash_erase_mode_t mode, u32 addr)
{
	if (FLASH_NOR_Status()) return 1;
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	switch (mode)
	{
	case mErase_Mode_Chip:
		P25QXXH_EraseChip();
		break;
	
	case mErase_Mode_Block64K:
		P25QXXH_EraseBlock(P25QXXH_CMD_BE64, addr);
		break;
	
	case mErase_Mode_Block32K:
		P25QXXH_EraseBlock(P25QXXH_CMD_BE32, addr);
		break;
	
	case mErase_Mode_Sector:
		P25QXXH_EraseSector(addr);
		break;
	
	case mErase_Mode_Page:
		P25QXXH_ErasePage(addr);
		break;
	
	default:
		break;
	}
	
	P25QXXH_EnterDeepPowerDownMode();
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_ReadBuffer(u8* pBuf, u32 addr, u32 len)
 @Description			FLASH_NOR_ReadBuffer
 @Input				pBuf
					addr
					len
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 FLASH_NOR_ReadBuffer(u8* pBuf, u32 addr, u32 len)
{
	if (FLASH_NOR_Status()) return 1;
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	P25QXXH_ReadBufferNormal(pBuf, addr, len);
	
	P25QXXH_EnterDeepPowerDownMode();
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_WriteBuffer(u8* pBuf, u32 addr, u32 len)
 @Description			FLASH_NOR_WriteBuffer
 @Input				pBuf
					addr
					len
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 FLASH_NOR_WriteBuffer(u8* pBuf, u32 addr, u32 len)
{
	if (FLASH_NOR_Status()) return 1;
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	P25QXXH_WriteBuffer(pBuf, addr, len);
	
	P25QXXH_EnterDeepPowerDownMode();
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 FLASH_NOR_ReadByte(u32 addr)
 @Description			FLASH_NOR_ReadByte
 @Input				addr
 @Return				data
**********************************************************************************************************/
u8 FLASH_NOR_ReadByte(u32 addr)
{
	u8 val = 0;
	
	FLASH_NOR_ReadBuffer(&val, addr, 1);
	
	return val;
}

/**********************************************************************************************************
 @Function			u16 FLASH_NOR_ReadHalfWord(u32 addr)
 @Description			FLASH_NOR_ReadHalfWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u16 FLASH_NOR_ReadHalfWord(u32 addr)
{
	u16 val = 0;
	u8 tmpval[2] = {0};
	
	FLASH_NOR_ReadBuffer(tmpval, addr, 2);
	
	val |= tmpval[0] << 0;
	val |= tmpval[1] << 8;
	
	return val;
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_ReadWord(u32 addr)
 @Description			FLASH_NOR_ReadWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u32 FLASH_NOR_ReadWord(u32 addr)
{
	u32 val = 0;
	u8 tmpval[4] = {0};
	
	FLASH_NOR_ReadBuffer(tmpval, addr, 4);
	
	val |= tmpval[0] << 0;
	val |= tmpval[1] << 8;
	val |= tmpval[2] << 16;
	val |= tmpval[3] << 24;
	
	return val;
}

/**********************************************************************************************************
 @Function			u8 FLASH_NOR_WriteByte(u32 addr, u8 data)
 @Description			FLASH_NOR_WriteByte
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u8 FLASH_NOR_WriteByte(u32 addr, u8 data)
{
	return FLASH_NOR_WriteBuffer(&data, addr, 1);
}

/**********************************************************************************************************
 @Function			u16 FLASH_NOR_WriteHalfWord(u32 addr, u16 data)
 @Description			FLASH_NOR_WriteHalfWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u16 FLASH_NOR_WriteHalfWord(u32 addr, u16 data)
{
	u8 tmpval[2] = {0};
	
	tmpval[0] = (data >> 0) & 0xFF;
	tmpval[1] = (data >> 8) & 0xFF;
	
	return FLASH_NOR_WriteBuffer(tmpval, addr, 2);
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_WriteWord(u32 addr, u32 data)
 @Description			FLASH_NOR_WriteWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u32 FLASH_NOR_WriteWord(u32 addr, u32 data)
{
	u8 tmpval[4] = {0};
	
	tmpval[0] = (data >> 0)  & 0xFF;
	tmpval[1] = (data >> 8)  & 0xFF;
	tmpval[2] = (data >> 16) & 0xFF;
	tmpval[3] = (data >> 24) & 0xFF;
	
	return FLASH_NOR_WriteBuffer(tmpval, addr, 4);
}

/**********************************************************************************************************
 @Function			u32 FLASH_NOR_GetNumByteOfThisData(u32 addr, u32 len, u8 thisData)
 @Description			FLASH_NOR_GetNumByteOfThisData
 @Input				addr
					len
					thisData
 @Return				0 Error
					n OK
**********************************************************************************************************/
u32 FLASH_NOR_GetNumByteOfThisData(u32 addr, u32 len, u8 thisData)
{
	u32 numThisData = 0;
	
	if (FLASH_NOR_Status()) return 0;
	
	P25QXXH_ReleaseDeepPowerDownMode();
	
	numThisData = P25QXXH_GetNumByteOfThisData(addr, len, thisData);
	
	P25QXXH_EnterDeepPowerDownMode();
	
	return numThisData;
}

/********************************************** END OF FLEE **********************************************/
