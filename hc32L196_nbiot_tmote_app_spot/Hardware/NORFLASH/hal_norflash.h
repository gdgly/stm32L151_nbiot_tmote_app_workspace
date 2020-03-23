#ifndef __HAL_NORFLASH_H
#define   __HAL_NORFLASH_H

#include "sys.h"
#include "hal_p25qxxh.h"

#define NOR_BASE_ADDR			P25Q40H_BASE_ADDR
#define NOR_BYTE_SIZE			P25Q40H_CHIP512K_BYTE_SIZE

#define NOR_BLOCK64K_ADDR(n)		((u32)(n * P25Q40H_BLOCK64K_BYTE_SIZE) + NOR_BASE_ADDR)
#define NOR_BLOCK32K_ADDR(n)		((u32)(n * P25Q40H_BLOCK32K_BYTE_SIZE) + NOR_BASE_ADDR)
#define NOR_SECTOR4K_ADDR(n)		((u32)(n * P25Q40H_SECTOR4K_BYTE_SIZE) + NOR_BASE_ADDR)
#define NOR_PAGE256B_ADDR(n)		((u32)(n * P25Q40H_PAGE256B_BYTE_SIZE) + NOR_BASE_ADDR)

typedef enum _norflash_erase_mode
{
	mErase_Mode_Chip			= 0U,
	mErase_Mode_Block64K		= 1U,
	mErase_Mode_Block32K		= 2U,
	mErase_Mode_Sector			= 3U,
	mErase_Mode_Page			= 4U
} norflash_erase_mode_t;

void FLASH_NOR_Init(void);

u32  FLASH_NOR_Status(void);

u32  FLASH_NOR_SoftwareReset(void);

u32  FLASH_NOR_Erase(norflash_erase_mode_t mode, u32 addr);

u32  FLASH_NOR_ReadBuffer(u8* pBuf, u32 addr, u32 len);

u32  FLASH_NOR_WriteBuffer(u8* pBuf, u32 addr, u32 len);

u32  FLASH_NOR_GetNumByteOfThisData(u32 addr, u32 len, u8 thisData);

#endif /* __HAL_NORFLASH_H */
