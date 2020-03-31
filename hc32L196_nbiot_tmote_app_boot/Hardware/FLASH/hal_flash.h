#ifndef __HAL_FLASH_H
#define   __HAL_FLASH_H

#include "sys.h"
#include "flash.h"

#define HC32_FLASH_SECTOR_SIZE	0x200ul
#define HC32_FLASH_SECTOR_BLOCK	512u

#define HC32_FLASH_BASE			((u32)(0x00000000))
#define HC32_FLASH_SIZE			((u32)(HC32_FLASH_SECTOR_SIZE * HC32_FLASH_SECTOR_BLOCK))

#define HC32_FLASH_SECTOR_ADDR(n)	((u32)(n * HC32_FLASH_SECTOR_SIZE) + HC32_FLASH_BASE)

typedef enum _flash_hclk_freq
{
	flashHCLK_4MHz				= 1U,
	flashHCLK_8MHz				= 2U,
	flashHCLK_16MHz			= 4U,
	flashHCLK_24MHz			= 6U,
	flashHCLK_32MHz			= 8U,
	flashHCLK_48MHz			= 12U,
} flash_hclk_freq_t;

typedef enum _flash_erase_mode
{
	flashErase_Mode_Chip		= 0U,
	flashErase_Mode_Sector		= 1U,
} flash_erase_mode_t;

void HC32_FLASH_Init(flash_hclk_freq_t hclkFreq, boolean_t bDpstbEn);								//HC32 FLASH 初始化

u32  HC32_FLASH_Status(void);

u32  HC32_FLASH_Erase(flash_erase_mode_t mode, u32 addr);

u8   HC32_FLASH_ReadByte(u32 addr);
u16  HC32_FLASH_ReadHalfWord(u32 addr);
u32  HC32_FLASH_ReadWord(u32 addr);

u8   HC32_FLASH_WriteByte(u32 addr, u8 data);
u16  HC32_FLASH_WriteHalfWord(u32 addr, u16 data);
u32  HC32_FLASH_WriteWord(u32 addr, u32 data);

u8   HC32_FLASH_ReadBuffer(u32 addr, u8* buf, u32 len);
u8   HC32_FLASH_WriteBuffer(u32 addr, u8* buf, u32 len);

#endif /* __HAL_FLASH_H */
