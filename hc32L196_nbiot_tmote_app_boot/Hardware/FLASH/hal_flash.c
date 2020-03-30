/**
  *********************************************************************************************************
  * @file    hal_flash.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-28
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
#include "hal_flash.h"
#include "delay.h"
#include "usart.h"

static __IO en_result_t FLASH_Status = Error;

/**********************************************************************************************************
 @Function			void HC32_FLASH_Init(flash_hclk_freq_t hclkFreq, boolean_t bDpstbEn)
 @Description			HC32_FLASH_Init							: HC32 FLASH 初始化
 @Input				hclkFreq									: HC32 FLASH 编程时钟频率配置
					bDpstbEn									: TRUE  - 当系统进入DeepSleep模式, FLASH进入低功耗模式
															  FALSE - 当系统进入DeepSleep模式, FLASH不进入低功耗模式
 @Return				void
**********************************************************************************************************/
void HC32_FLASH_Init(flash_hclk_freq_t hclkFreq, boolean_t bDpstbEn)
{
#ifdef FLASH_HC32NOR
	FLASH_Status = Flash_Init((u8)hclkFreq, bDpstbEn);
#endif
}

/**********************************************************************************************************
 @Function			u32 HC32_FLASH_Status(void)
 @Description			HC32_FLASH_Status
 @Input				void
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 HC32_FLASH_Status(void)
{
#ifdef FLASH_HC32NOR
	return (u32)FLASH_Status;
#else
	return (u32)Error;
#endif
}

/**********************************************************************************************************
 @Function			u32 HC32_FLASH_Erase(flash_erase_mode_t mode, u32 addr)
 @Description			HC32_FLASH_Erase
 @Input				mode
					addr
 @Return				0 OK
					1 Error
**********************************************************************************************************/
u32 HC32_FLASH_Erase(flash_erase_mode_t mode, u32 addr)
{
	en_result_t enResult = Ok;
	
	if (HC32_FLASH_Status()) return 1;
	
	switch (mode)
	{
	case flashErase_Mode_Chip:
		enResult = Flash_ChipErase();
		break;
	
	case flashErase_Mode_Sector:
		enResult = Flash_SectorErase(addr);
		break;
	
	default:
		enResult = Error;
		break;
	}
	
	if (enResult != Ok) return 1;
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 HC32_FLASH_ReadByte(u32 addr)
 @Description			HC32_FLASH_ReadByte
 @Input				addr
 @Return				data
**********************************************************************************************************/
u8 HC32_FLASH_ReadByte(u32 addr)
{
	if (HC32_FLASH_Status()) return 0;
	
	return (*(__IO u8 *)addr);
}

/**********************************************************************************************************
 @Function			u8 HC32_FLASH_WriteByte(u32 addr, u8 data)
 @Description			HC32_FLASH_WriteByte
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u8 HC32_FLASH_WriteByte(u32 addr, u8 data)
{
	en_result_t enResult = Ok;
	
	if (HC32_FLASH_Status()) return 1;
	
	enResult = Flash_WriteByte(addr, data);
	
	if (enResult != Ok) return 1;
	
	return 0;
}

/**********************************************************************************************************
 @Function			u16 HC32_FLASH_ReadHalfWord(u32 addr)
 @Description			HC32_FLASH_ReadHalfWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u16 HC32_FLASH_ReadHalfWord(u32 addr)
{
	if (HC32_FLASH_Status()) return 0;
	
	return (*(__IO u16 *)addr);
}

/**********************************************************************************************************
 @Function			u16 HC32_FLASH_WriteHalfWord(u32 addr, u16 data)
 @Description			HC32_FLASH_WriteHalfWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u16 HC32_FLASH_WriteHalfWord(u32 addr, u16 data)
{
	en_result_t enResult = Ok;
	
	if (HC32_FLASH_Status()) return 1;
	
	enResult = Flash_WriteHalfWord(addr, data);
	
	if (enResult != Ok) return 1;
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 HC32_FLASH_ReadWord(u32 addr)
 @Description			HC32_FLASH_ReadWord
 @Input				addr
 @Return				data
**********************************************************************************************************/
u32 HC32_FLASH_ReadWord(u32 addr)
{
	if (HC32_FLASH_Status()) return 0;
	
	return (*(__IO u32 *)addr);
}

/**********************************************************************************************************
 @Function			u32 HC32_FLASH_WriteWord(u32 addr, u32 data)
 @Description			HC32_FLASH_WriteWord
 @Input				addr
					data
 @Return				0 OK
					1 Err
**********************************************************************************************************/
u32 HC32_FLASH_WriteWord(u32 addr, u32 data)
{
	en_result_t enResult = Ok;
	
	if (HC32_FLASH_Status()) return 1;
	
	enResult = Flash_WriteWord(addr, data);
	
	if (enResult != Ok) return 1;
	
	return 0;
}























/********************************************** END OF FLEE **********************************************/
