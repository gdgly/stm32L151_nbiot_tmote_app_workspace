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
	
	
	printf("Upgrade: Addr = 0x%08X, Len = %d\r\n", addr_offset, len);
	
	
	
	return IAP_OK;
}






















/********************************************** END OF FLEE **********************************************/
