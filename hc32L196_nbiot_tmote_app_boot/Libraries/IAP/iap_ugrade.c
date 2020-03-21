/**
  *********************************************************************************************************
  * @file    iap_ugrade.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-21
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
#include "iap_ugrade.h"
#include "delay.h"
#include "usart.h"

__IO u8 upgradState = READY_TO_JUMP;
__IO u8 joinState = JOINING;

/**********************************************************************************************************
 @Function			u8 IAP_Ugrade_GetBootMode(void)
 @Description			IAP_Ugrade_GetBootMode
 @Input				void
 @Return				BootMode
**********************************************************************************************************/
u8 IAP_Ugrade_GetBootMode(void)
{
	u8 bootMode = 0;
	
	bootMode = TCFG_EEPROM_Get_BootMode();
	switch (bootMode)
	{
	case TCFG_ENV_BOOTMODE_TOUPDATE:
		bootMode = TCFG_ENV_BOOTMODE_TOUPDATE;
		break;
	
	case TCFG_ENV_BOOTMODE_UPDATING:
		bootMode = TCFG_ENV_BOOTMODE_UPDATING;
		break;
	
	case TCFG_ENV_BOOTMODE_REUPDATE:
		bootMode = TCFG_ENV_BOOTMODE_REUPDATE;
		break;
	
	default:
		bootMode = TCFG_ENV_BOOTMODE_NORMAL;
		break;
	}
	
	return bootMode;
}






















































/********************************************** END OF FLEE **********************************************/
