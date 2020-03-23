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

upgradClientsTypeDef upgradClient = {
	.ug_boot_mode				= TCFG_ENV_BOOTMODE_NORMAL,
	.ug_upgrad_state			= READY_TO_JUMP,
	.ug_join_state				= JOINING,
	.ug_mac_sn				= 0x00000000,
	
	
	
	
	
	
};






















































/********************************************** END OF FLEE **********************************************/
