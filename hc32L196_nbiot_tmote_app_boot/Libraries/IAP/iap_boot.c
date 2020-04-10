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








/**********************************************************************************************************
 @Function			void IAP_Boot_form_flash(unsigned int app_address)
 @Description			IAP_Boot_form_flash
 @Input				app_address
 @Return				void
**********************************************************************************************************/
void IAP_Boot_form_flash(unsigned int app_address)
{
	
	
	printf("Ready jump to application: 0x%08X!\r\n", app_address);//Todo Debug
	
	
}

















/********************************************** END OF FLEE **********************************************/
