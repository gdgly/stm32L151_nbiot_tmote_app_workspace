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
#include "iap_boot.h"
#include "iap_core.h"
#include "radio_hal_rf.h"
#include "radio_rfa_boot.h"
#include "delay.h"
#include "usart.h"

#define PACK_SIZE				128

upgradClientsTypeDef upgradClient = {
	.ug_boot_mode				= TCFG_ENV_BOOTMODE_NORMAL,
	.ug_upgrad_state			= READY_TO_JUMP,
	.ug_update_state			= UNCOMPLETE,
	.ug_join_state				= JOINING,
	.ug_over_flow				= 0,
	.ug_app_offset				= 0,
	.ug_firm_offset			= 0,
	.ug_packnum_received		= 0,
	.ug_firmlen_received		= 0,
	.ug_test_pgm_fail_cnt		= 0,
};














/**********************************************************************************************************
 @Function			u8 Ugrade_xm_ProgramUpdate(u8 *recvlong, u8 *sn)
 @Description			Ugrade_xm_ProgramUpdate
 @Input				recvlong
					sn
 @Return				state
**********************************************************************************************************/
u8 Ugrade_xm_ProgramUpdate(u8 *recvlong, u8 *sn)
{
	
	
	
	
	return 0;
}

/**********************************************************************************************************
 @Function			void Ugrade_xm_Join(void)
 @Description			Ugrade_xm_Join
 @Input				void
 @Return				void
**********************************************************************************************************/
void Ugrade_xm_Join(void)
{
	
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void Ugrade_xm_Buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len)
 @Description			Ugrade_xm_Buildframe
 @Input				...
 @Return				void
**********************************************************************************************************/
void Ugrade_xm_Buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len)
{
	
	
	
	
	
	
	
	
	
	
	
}






























/********************************************** END OF FLEE **********************************************/
