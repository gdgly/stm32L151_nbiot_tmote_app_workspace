/**
  *********************************************************************************************************
  * @file    iap_core.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-07
  * @brief   1TAB = 5Speace
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
#include "iap_core.h"
#include "delay.h"
#include "usart.h"
#include "hal_flash.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"






/**********************************************************************************************************
 @Function			u8 xm_iap_program(u32 base_addr, u32 addr_offset, u32 len, u8* buff)
 @Description			xm_iap_program
 @Input				...
 @Return				iap_progrm_state
**********************************************************************************************************/
u8 xm_iap_program(u32 base_addr, u32 addr_offset, u32 len, u8* buff)
{
	u32 index, wdata, rdata;
	u32 PageNum = 0;
	u32 PageOffset = 0;
	
	PageOffset = addr_offset;
	
	PageNum = (PageOffset / HC32_FLASH_SECTOR_BLOCK);
	PageOffset = (PageOffset % HC32_FLASH_SECTOR_BLOCK);
	
	if ((addr_offset + len) > APP_LOWEST_SIZE) {
		return IAP_LEN_UNSUPPORTED;
	}
	
	if (PageOffset == 0) {
		if (HC32_FLASH_Erase(flashErase_Mode_Sector, (base_addr + (PageNum * HC32_FLASH_SECTOR_BLOCK)))) {
			return IAP_ERASE_ERROR;
		}
	}
	
	for (index = 0; index < len; index += 4) {
		wdata = (uint32_t)(buff[index + 0] << 0)  + (uint32_t)(buff[index + 1] << 8)
		      + (uint32_t)(buff[index + 2] << 16) + (uint32_t)(buff[index + 3] << 24);
		if (HC32_FLASH_WriteWord((base_addr + addr_offset + index), wdata)) {
			return IAP_PROGRAM_ERROR;
		}
		rdata = HC32_FLASH_ReadWord((base_addr + addr_offset + index));
		if (wdata != rdata) {
			return IAP_PROGRAM_ERROR;
		}
	}
	
	return IAP_OK;
}























/********************************************** END OF FLEE **********************************************/
