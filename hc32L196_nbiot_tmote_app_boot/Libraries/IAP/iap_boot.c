/**
  *********************************************************************************************************
  * @file    iap_boot.c
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
#include "iap_boot.h"
#include "delay.h"
#include "usart.h"
#include "hal_flash.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"

#define HC32_SRAM_BASE			((uint32_t)0x20000000)
#define HC32_SRAM_SIZE			(0x8000ul)

func_ptr_t JumpToApplication;

/**********************************************************************************************************
 @Function			static en_result_t IAP_JumpToApplication(unsigned int u32Addr)
 @Description			IAP_JumpToApplication
 @Input				app_address
 @Return				void
**********************************************************************************************************/
static en_result_t IAP_JumpToApplication(unsigned int u32Addr)
{
	__IO uint32_t JumpAddress;
	
	uint32_t FirmStackTop = *((__IO u32 *)u32Addr);
	
	if ((FirmStackTop > HC32_SRAM_BASE) && (FirmStackTop <= (HC32_SRAM_BASE + HC32_SRAM_SIZE)))
	{
		/* Jump to user application */
		JumpAddress = *(__IO uint32_t *) (u32Addr + 4);
		
		JumpToApplication = (func_ptr_t) JumpAddress;
		
		/* Initialize user application's Stack Pointer */
		__set_MSP(*(__IO uint32_t *) u32Addr);
		
		JumpToApplication();
	}
	
	return Error;
}

/**********************************************************************************************************
 @Function			void IAP_Boot_form_flash(unsigned int app_address)
 @Description			IAP_Boot_form_flash
 @Input				app_address
 @Return				void
**********************************************************************************************************/
void IAP_Boot_form_flash(unsigned int app_address)
{
	IAP_JumpToApplication(app_address);
}

/********************************************** END OF FLEE **********************************************/
