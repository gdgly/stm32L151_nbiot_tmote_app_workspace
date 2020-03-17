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
	return (u8)NOR_Status;
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
