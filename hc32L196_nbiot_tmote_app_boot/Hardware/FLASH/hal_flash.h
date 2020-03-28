#ifndef __HAL_FLASH_H
#define   __HAL_FLASH_H

#include "sys.h"
#include "flash.h"

#define HC32_FLASH_SECTOR_SIZE	0x200ul
#define HC32_FLASH_SECTOR_BLOCK	512u

#define HC32_FLASH_BASE			((u32)(0x00000000))
#define HC32_FLASH_SIZE			((u32)(HC32_FLASH_SECTOR_SIZE * HC32_FLASH_SECTOR_BLOCK))

















#endif /* __HAL_FLASH_H */
