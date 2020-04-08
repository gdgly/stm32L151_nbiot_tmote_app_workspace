/**
  *********************************************************************************************************
  * @file    radio_hal_rf.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-02
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "radio_hal_app.h"
#include "radio_hal_rf.h"
#include "radio_hal_wrap.h"
#include "radio_msg_config.h"
#include "radio_core.h"
#include "radio_comm.h"
#include "si446x_api_lib.h"
#include "iap_boot.h"
#include "iap_core.h"
#include "iap_ugrade.h"
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

#define RADIO_RF_PAYLOAD_MAC_SN			TCFG_EEPROM_Get_MAC_SN()

#define RADIO_RF_HEARTBT_MAJOR_SOFTVER		MVB_BOOT_SOFTWARE_MAJOR
#define RADIO_RF_HEARTBT_SUB_SOFTVER		MVB_BOOT_SOFTWARE_SUB
#define RADIO_RF_HEARTBT_SUB_HARDVER		MVB_BOOT_HARDWARE
#define RADIO_RF_HEARTBT_DEV_TYPE			MVB_MODEL_TYPE
#define RADIO_RF_HEARTBT_WORK_STATUS		iap_upgrad_state

#define RADIO_RF_SENDBUF_SIZE				256
#define RADIO_RF_RECVBUF_SIZE				256
#define RADIO_RF_PINTBUF_SIZE				256

static frameInfo_t sInFrameQ[SIZE_INFRAME_Q];

u8 trf_send_buf[RADIO_RF_SENDBUF_SIZE] = {0};
u8 trf_recv_buf[RADIO_RF_RECVBUF_SIZE] = {0};
u8 trf_pint_buf[RADIO_RF_PINTBUF_SIZE] = {0};

u32 last_recvtime = 0;
















/**********************************************************************************************************
 @Function			void tmesh_rf_QInit(void)
 @Description			tmesh_rf_QInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void tmesh_rf_QInit(void)
{
	memset(sInFrameQ, 0, sizeof(sInFrameQ));
}

/**********************************************************************************************************
 @Function			void tmesh_rf_QPush(mrfiPacket_t* rfpacket)
 @Description			tmesh_rf_QPush
 @Input				rfpacket
 @Return				void
**********************************************************************************************************/
void tmesh_rf_QPush(mrfiPacket_t* rfpacket)
{
	int8_t i, oldest = 0, avail = -1;
	
	for (i = 0; i < SIZE_INFRAME_Q; i++) {
		if (sInFrameQ[i].fi_usage == FI_AVAILABLE) {
			avail = i;
		}
		if (sInFrameQ[i].orderStamp < sInFrameQ[oldest].orderStamp) {
			oldest = i;
		}
	}
	
	if (avail < 0) avail = oldest;
	
	memcpy(&sInFrameQ[avail].mrfiPkt, rfpacket, sizeof(mrfiPacket_t));
	sInFrameQ[avail].fi_usage = FI_INUSE_UNTIL_DEL;
	sInFrameQ[avail].orderStamp = sInFrameQ[oldest].orderStamp++;
}

/**********************************************************************************************************
 @Function			mrfiPacket_t* tmesh_rf_QPop(void)
 @Description			tmesh_rf_QPop
 @Input				void
 @Return				rfpacket
**********************************************************************************************************/
mrfiPacket_t* tmesh_rf_QPop(void)
{
	int8_t i;
	
	for (i = 0; i < SIZE_INFRAME_Q; i++) {
		if (sInFrameQ[i].fi_usage == FI_INUSE_UNTIL_DEL) {
			sInFrameQ[i].fi_usage = FI_AVAILABLE;
			return &sInFrameQ[i].mrfiPkt;
		}
	}
	
	return NULL;
}

/**********************************************************************************************************
 @Function			void Radio_RF_Data_Handle_ISR(mrfiPacket_t* rfpacket)
 @Description			Radio_RF_Data_Handle_ISR
 @Input				rfpacket
 @Return				void
**********************************************************************************************************/
void Radio_RF_Data_Handle_ISR(mrfiPacket_t* rfpacket)
{
	tmesh_rf_QPush(rfpacket);
}

/**********************************************************************************************************
 @Function			char Radio_RF_Receive(u8 *outmsg, u8 *len)
 @Description			Radio_RF_Receive
 @Input				outmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RF_Receive(u8 *outmsg, u8 *len)
{
	mrfiPacket_t* rfpacket;
	
	rfpacket = tmesh_rf_QPop();
	
	if (rfpacket != NULL) {
		*len = 1 + (CFG_GET_FROM_FRAME(CFG_P_FRAME_LEN(rfpacket->frame), CFG_LEN_OS));
		memcpy(outmsg, rfpacket->frame, *len);
		return TRF_SUCCESS;
	}
	
	return TRF_NO_PAYLOAD;
}

/**********************************************************************************************************
 @Function			char Radio_RF_Transmit(u8 *inmsg, u8 len)
 @Description			Radio_RF_Transmit
 @Input				inmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RF_Transmit(u8 *inmsg, u8 len)
{
	Radio_Hal_RF_PrepareToTx(inmsg, len);
	
	return 0;
}

/**********************************************************************************************************
 @Function			void Radio_RF_Cfg_Buildframe(u8 *inmsg, u8 pkttype, u8 pktnum, u32 sn, u8 *outsend, u8 len)
 @Description			Radio_RF_Cfg_Buildframe
 @Input				...
 @Return				void
**********************************************************************************************************/
void Radio_RF_Cfg_Buildframe(u8 *inmsg, u8 pkttype, u8 pktnum, u32 sn, u8 *outsend, u8 len)
{
	u8 i;
	u16 check_sum = 0;
	
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_LEN(outsend), CFG_LEN_OS, CFG_FRAME_PAYLOAD_OFS + CFG_FRAME_CRC_SIZE + len - CFG_FRAME_LEN_SIZE);
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_PRE(outsend), CFG_PRE_TYPE_OS, XMESHCFG_PRT);
	
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_PRE(outsend), CFG_PRE_VS_OS, CONFIG_VERSION);
	
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_HEAD(outsend), CFG_HEAD_TYPE_OS, pkttype);
	
	if (pktnum) {
		CFG_PUT_INTO_FRAME(CFG_P_FRAME_HEAD(outsend), CFG_PKTNUM_OS, pktnum);
	}
	
	if (len) {
		memcpy(CFG_P_FRAME_PAYLOAD(outsend), inmsg, len);
	}
	
	memcpy(CFG_P_FRAME_SN(outsend), &sn, 4);
	
	for (i = 1; i < CFG_FRAME_PAYLOAD_OFS + len; i++) {
		check_sum += outsend[i];
	}
	
	outsend[CFG_FRAME_PAYLOAD_OFS + len + 0] = check_sum / 0x100;
	outsend[CFG_FRAME_PAYLOAD_OFS + len + 1] = check_sum % 0x100;
}

static u8 trf_xmit_get_pktnum(void)
{
	static u8 pktnum = 0;
	return pktnum++;
}

/**********************************************************************************************************
 @Function			char Radio_RF_Operate_Recvmsg(u8 *inmsg, u8 len)
 @Description			Radio_RF_Operate_Recvmsg
 @Input				inmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RF_Operate_Recvmsg(u8 *inmsg, u8 len)
{
	char rc = TRF_SUCCESS;
	
	if (CFG_GET_FROM_FRAME(CFG_P_FRAME_PRE(inmsg), CFG_PRE_TYPE_OS) == UPGRADE_PRT)
	{
		if ((UPGD_GET_FROM_FRAME(UPGD_P_FRAME_PRE(inmsg), UPGD_PRE_VS_OS) == UPGRADEVERSION) && (!memcmp(UPGD_P_FRAME_SN(inmsg), subsn, 4)))
		{
			/* This code RF Upgrade */
			if (UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(inmsg), UPGD_HEAD_TYPE_OS) == (UPGRADE_REQUEST_RSP))
			{
				iap_joined_state = *(UPGD_P_FRAME_PAYLOAD(inmsg));
			}
			else {
				
				
				
				
				
				
				
				
				
				
				
			}
		}
	}
	else {
		rc = TRF_BAD_PROTOCAL;
	}
	
	return rc;
}

/**********************************************************************************************************
 @Function			u32 Radio_RF_Trf_Last_Recvtime(void)
 @Description			Radio_RF_Trf_Last_Recvtime
 @Input				void
 @Return				last_recvtime
**********************************************************************************************************/
u32 Radio_RF_Trf_Last_Recvtime(void)
{
	return last_recvtime;
}

/**********************************************************************************************************
 @Function			void Radio_RF_Trf_Receive_Task(void)
 @Description			Radio_RF_Trf_Receive_Task
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RF_Trf_Receive_Task(void)
{
	u8 len = 0;
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	if (TRF_SUCCESS == Radio_RF_Receive(trf_recv_buf, &len)) {
		if (TRF_SUCCESS == Radio_RF_Operate_Recvmsg(trf_recv_buf, len)) {
			last_recvtime = HC32_GetSecondTick();
		}
	}
}

/**********************************************************************************************************
 @Function			void Radio_RF_Xmit_Heartbeat(void)
 @Description			Radio_RF_Xmit_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RF_Xmit_Heartbeat(void)
{
	static u32 hearttime_pre = 0;
	
	radio_trf_heartbeat_s * pHeartBeat = (radio_trf_heartbeat_s*)(trf_send_buf + 32);
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	pHeartBeat->head.destSN		= 0xFFFFFFFF;
	pHeartBeat->head.version		= TRF_MSG_VERSION;
	pHeartBeat->head.type		= TRF_MSG_HEART_BOOTLOADER;
	
	pHeartBeat->major_softver	= RADIO_RF_HEARTBT_MAJOR_SOFTVER;
	pHeartBeat->sub_softver		= RADIO_RF_HEARTBT_SUB_SOFTVER;
	pHeartBeat->sub_hardver		= RADIO_RF_HEARTBT_SUB_HARDVER;
	pHeartBeat->dev_type		= RADIO_RF_HEARTBT_DEV_TYPE;
	pHeartBeat->work_status		= RADIO_RF_HEARTBT_WORK_STATUS;
	
	if (hearttime_pre + 10 < HC32_GetSecondTick()) {
		hearttime_pre = HC32_GetSecondTick();
		Radio_RF_Cfg_Buildframe((u8 *)pHeartBeat, TMOTE_PLAIN_PUB, trf_xmit_get_pktnum(), RADIO_RF_PAYLOAD_MAC_SN, trf_send_buf, sizeof(radio_trf_heartbeat_s));
		Radio_RF_Transmit(trf_send_buf, trf_send_buf[0]);
	}
}

/**********************************************************************************************************
 @Function			void Radio_RF_Xmit_Printfbuf(char* info)
 @Description			Radio_RF_Xmit_Printfbuf
 @Input				info
 @Return				void
**********************************************************************************************************/
void Radio_RF_Xmit_Printfbuf(char* info)
{
	u8 infolen;
	
	radio_trf_msgdata_s * pMsg = (radio_trf_msgdata_s*)(trf_send_buf + 32);
	
	infolen = strlen(info);
	if (infolen > 30) {
		infolen = 30;
	}
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	Radio_Hal_RF_Interface_Init();
	
	pMsg->head.destSN			= 0xFFFFFFFF;
	pMsg->head.version			= TRF_MSG_VERSION;
	pMsg->head.type			= TRF_MSG_DEBUG_INFO;
	strncpy(pMsg->pData, info, infolen);
	
	Radio_RF_Cfg_Buildframe((u8 *)pMsg, TMOTE_PLAIN_PUB, trf_xmit_get_pktnum(), RADIO_RF_PAYLOAD_MAC_SN, trf_send_buf, sizeof(radio_trf_msghead_s) + infolen);
	Radio_RF_Transmit(trf_send_buf, trf_send_buf[0]);
}

/**********************************************************************************************************
 @Function			void Radio_RF_Trf_Printf(const char *fmt, ...)
 @Description			Radio_RF_Trf_Printf
 @Input				fmt
					...
 @Return				void
**********************************************************************************************************/
void Radio_RF_Trf_Printf(const char *fmt, ...)
{
	__va_list args;
	
	memset(trf_pint_buf, 0x00, sizeof(trf_pint_buf));
	
	va_start (args, fmt);
	vsprintf ((char*)trf_pint_buf, fmt, args);
	va_end (args);
	
	Radio_RF_Xmit_Printfbuf((char*)trf_pint_buf);
}

/********************************************** END OF FLEE **********************************************/
