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
#include "hal_flash.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
#include "iap_boot.h"
#include "iap_core.h"

#define PACK_SIZE				128

u32 app_offset = 0;
u32 firm_offset = 0;

u32 iap_subsn = 0;
u8  iap_bootmode = 0;
u8  iap_upgrad_state = 0;
u8  iap_progrm_state = 0;
u8  iap_joined_state = JOINING;

u8  overflow = 0;

int packnum_received = 0;
int firmlen_received = 0;

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

/**********************************************************************************************************
 @Function			u8 xm_Ugrade_programUpdate(u8 *recvlong, u8 *sn)
 @Description			xm_Ugrade_programUpdate
 @Input				recvlong
					sn
 @Return				progrm_state
**********************************************************************************************************/
u8 xm_Ugrade_programUpdate(u8 *recvlong, u8 *sn)
{
	u8 packetno, rc = 0, *p = NULL, type;
	
	u8 buf_send[UPGD_FRAME_PAYLOAD_OFS + UPGD_FRAME_CRC_SIZE + UPGRADE_TYPE_SIZE];
	
	int rt;
	
	unsigned char* pData;
	
	type = (UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(recvlong), UPGD_HEAD_TYPE_OS));
	
	packetno = (UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(recvlong), UPGD_PKTNUM_OS));
	
	if (type == UPGRADE_VALIDDATA)
	{
		if ((packetno == 1) && (!overflow))
		{
			TCFG_EEPROM_Set_BootMode(TCFG_ENV_BOOTMODE_UPDATING);
			pData = (unsigned char*)UPGD_P_FRAME_PAYLOAD(recvlong);
			app_offset &= 0xFFFF00FF;
			firm_offset = (pData[5]);
			app_offset |= (firm_offset << 8);
			if (app_offset >= APP_LOWEST_ADDRESS) {
				xm_iap_program(APP_LOWEST_ADDRESS - HC32_FLASH_SECTOR_BLOCK, 0, 4, (unsigned char*)(&app_offset));
			}
		}
		
		if (app_offset < APP_LOWEST_ADDRESS) return TRANSERROR;
		
		if ((packnum_received % 256) != packetno)
		{
			rt = xm_iap_program(app_offset, packnum_received * PACK_SIZE, PACK_SIZE, (unsigned char*)UPGD_P_FRAME_PAYLOAD(recvlong));
			
			if (rt == IAP_OK)
			{
				packnum_received += 1;
				firmlen_received += PACK_SIZE;
				rc =  UNCOMPLETE;
			}
			else {
				rc =  TRANSERROR;
			}
			
			if (packetno == 255) {
				overflow++;
			}
			
			if ((packnum_received % 256) != packetno) {
				rc =  TRANSERROR;
			}
		}
	}
	else if (type == UPGRADE_END) {
		rc = COMPLETE;
	}
	
	xm_Ugrade_buildframe(p, UPGRADE_VALIDDATA_RSP, packetno, sn, buf_send, 0);
	
	Radio_RF_Transmit(buf_send, buf_send[0]);
	
	return rc;
}

/********************************************** END OF FLEE **********************************************/
