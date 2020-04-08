/**
  *********************************************************************************************************
  * @file    iap_ugrade.c
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
#include "iap_ugrade.h"
#include "delay.h"
#include "usart.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"

u32 app_offset = 0;

u32 iap_subsn = 0;
u8  iap_bootmode = 0;
u8  iap_upgrad_state = 0;
u8  iap_joined_state = JOINING;

u8  subsn[4];

/**********************************************************************************************************
 @Function			void xm_Ugrade_buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len)
 @Description			xm_Ugrade_buildframe
 @Input				...
 @Return				void
**********************************************************************************************************/
void xm_Ugrade_buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len)
{
	u8 i;
	u16 check_sum = 0;
	
	UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_LEN(send), UPGD_LEN_OS, UPGD_FRAME_PAYLOAD_OFS + UPGD_FRAME_CRC_SIZE + len - UPGD_FRAME_LEN_SIZE);
	
	UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_PRE(send), UPGD_PRE_TYPE_OS, UPGRADE_PRT);
	
	UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_PRE(send), UPGD_PRE_VS_OS, UPGRADEVERSION);
	
	UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_HEAD(send), UPGD_HEAD_TYPE_OS, type);
	
	if (((type == UPGRADE_VALIDDATA) || (type == UPGRADE_VALIDDATA_RSP) || (type == UPGRADE_END))) {
		UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_HEAD(send), UPGD_PKTNUM_OS, pktnum);
	}
	
	if (len) {
		memcpy(UPGD_P_FRAME_PAYLOAD(send), msg, len);
	}
	
	memcpy(UPGD_P_FRAME_SN(send), sn, 4);
	
	for (i = 1; i < UPGD_FRAME_PAYLOAD_OFS + len; i++) {
		check_sum += send[i];
	}
	
	send[UPGD_FRAME_PAYLOAD_OFS + len + 0] = check_sum / 0x100;
	send[UPGD_FRAME_PAYLOAD_OFS + len + 1] = check_sum % 0x100;
}

/**********************************************************************************************************
 @Function			void xm_Ugrade_join(void)
 @Description			xm_Ugrade_join
 @Input				void
 @Return				void
**********************************************************************************************************/
void xm_Ugrade_join(void)
{
	u8 buf[UPGD_FRAME_PAYLOAD_OFS + UPGD_FRAME_CRC_SIZE + UPGRADE_TYPE_SIZE];
	
	xm_Ugrade_buildframe((u8 *)&iap_bootmode, UPGRADE_REQUEST, 0, subsn, buf, UPGRADE_TYPE_SIZE);
	
	Radio_RF_Transmit(buf, buf[0]);
}

















































/********************************************** END OF FLEE **********************************************/
