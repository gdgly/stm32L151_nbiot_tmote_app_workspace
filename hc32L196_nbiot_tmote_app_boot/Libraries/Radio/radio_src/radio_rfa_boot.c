/**
  *********************************************************************************************************
  * @file    radio_rfa_boot.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-20
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
#include "radio_rfa_boot.h"
#include "radio_hal_rf.h"
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

#define RADIO_RFA_BOOT_PAYLOAD_MAC_SN				0x81011000

#define RADIO_RFA_BOOT_HEARTBT_MAJOR_SOFTVER			MVB_BOOT_SOFTWARE_MAJOR
#define RADIO_RFA_BOOT_HEARTBT_SUB_SOFTVER			MVB_BOOT_SOFTWARE_SUB
#define RADIO_RFA_BOOT_HEARTBT_SUB_HARDVER			MVB_BOOT_HARDWARE
#define RADIO_RFA_BOOT_HEARTBT_DEV_TYPE				MVB_MODEL_TYPE
#define RADIO_RFA_BOOT_HEARTBT_WORK_STATUS			0x01






static frameInfo_t b_sInFrameQ[SIZE_INFRAME_Q];

u8 b_trf_send_buf[RADIO_RFA_BOOT_SDBUF_SIZE] = {0};
u8 b_trf_recv_buf[RADIO_RFA_BOOT_RVBUF_SIZE] = {0};
u8 b_trf_prit_buf[RADIO_RFA_BOOT_PTBUF_SIZE] = {0};





/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_QInit(void)
 @Description			Radio_RFA_Boot_QInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_QInit(void)
{
	memset(b_sInFrameQ, 0, sizeof(b_sInFrameQ));
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_QPush(mrfiPacket_t* rfpacket)
 @Description			Radio_RFA_Boot_QPush
 @Input				rfpacket
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_QPush(mrfiPacket_t* rfpacket)
{
	s8 i, oldest = 0, avail = -1;
	
	for (i = 0; i < SIZE_INFRAME_Q; i++) {
		if (b_sInFrameQ[i].fi_usage == FI_AVAILABLE) {
			avail = i;
		}
		if (b_sInFrameQ[i].orderStamp < b_sInFrameQ[oldest].orderStamp) {
			oldest = i;
		}
	}
	
	if (avail < 0) avail = oldest;
	
	memcpy(&b_sInFrameQ[avail].mrfiPkt, rfpacket, sizeof(mrfiPacket_t));
	b_sInFrameQ[avail].fi_usage = FI_INUSE_UNTIL_DEL;
	b_sInFrameQ[avail].orderStamp = b_sInFrameQ[oldest].orderStamp++;
}

/**********************************************************************************************************
 @Function			mrfiPacket_t* Radio_RFA_Boot_QPop(void)
 @Description			Radio_RFA_Boot_QPop
 @Input				void
 @Return				rfpacket
**********************************************************************************************************/
mrfiPacket_t* Radio_RFA_Boot_QPop(void)
{
	s8 i;
	
	for (i = 0; i < SIZE_INFRAME_Q; i++) {
		if (b_sInFrameQ[i].fi_usage == FI_INUSE_UNTIL_DEL) {
			b_sInFrameQ[i].fi_usage = FI_AVAILABLE;
			return &b_sInFrameQ[i].mrfiPkt;
		}
	}
	
	return NULL;
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Data_Handle_ISR(mrfiPacket_t* rfpacket)
 @Description			Radio_RFA_Boot_Data_Handle_ISR
 @Input				rfpacket
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Data_Handle_ISR(mrfiPacket_t* rfpacket)
{
	Radio_RFA_Boot_QPush(rfpacket);
}

/**********************************************************************************************************
 @Function			char Radio_RFA_Boot_Receive(u8 *outmsg, u8 *len)
 @Description			Radio_RFA_Boot_Receive
 @Input				outmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RFA_Boot_Receive(u8 *outmsg, u8 *len)
{
	mrfiPacket_t* rfpacket;
	
	rfpacket = Radio_RFA_Boot_QPop();
	
	if (rfpacket != NULL) {
		*len = 1 + (CFG_GET_FROM_FRAME(CFG_P_FRAME_LEN(rfpacket->frame), CFG_LEN_OS));
		memcpy(outmsg, rfpacket->frame, *len);
		
		return TRF_SUCCESS;
	}
	
	return TRF_NO_PAYLOAD;
}

/**********************************************************************************************************
 @Function			char Radio_RFA_Boot_Send(u8 *inmsg, u8 len)
 @Description			Radio_RFA_Boot_Send
 @Input				inmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RFA_Boot_Send(u8 *inmsg, u8 len)
{
	Radio_Hal_RF_PrepareToTx(inmsg, len);
	
	return TRF_SUCCESS;
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Cfg_Buildframe(u8 *inmsg, u8 pkttype, u8 pktnum, u32 sn, u8 *outsend, u8 len)
 @Description			Radio_RFA_Boot_Cfg_Buildframe
 @Input				...
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Cfg_Buildframe(u8 *inmsg, u8 pkttype, u8 pktnum, u32 sn, u8 *outsend, u8 len)
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

static u8 Radio_RFA_Boot_Xmit_Get_Pktnum(void)
{
	static u8 spktnum = 0;
	
	return spktnum++;
}

/**********************************************************************************************************
 @Function			char Radio_RFA_Boot_Operate_Recvmsg(u8 *inmsg, u8 len)
 @Description			Radio_RFA_Boot_Operate_Recvmsg
 @Input				inmsg
					len
 @Return				errcode
**********************************************************************************************************/
char Radio_RFA_Boot_Operate_Recvmsg(u8 *inmsg, u8 len)
{
	char rc = TRF_SUCCESS;
	
	if (CFG_GET_FROM_FRAME(CFG_P_FRAME_PRE(inmsg), CFG_PRE_TYPE_OS) == UPGRADE_PRT) {
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	else {
		rc = TRF_BAD_PROTOCAL;
	}
	
	return rc;
}

























/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Do_Xmit_Heartbeat(void)
 @Description			Radio_RFA_Boot_Do_Xmit_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Do_Xmit_Heartbeat(void)
{
	radio_boot_trf_heartbeat_s *pHeartBeat = (radio_boot_trf_heartbeat_s*)(b_trf_send_buf + 32);
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	Radio_Hal_RF_Interface_Init();
	Radio_Hal_RF_Interrupt_Enable();
	
	pHeartBeat->head.destSN		= 0xFFFFFFFF;
	pHeartBeat->head.version		= TRF_MSG_VERSION;
	pHeartBeat->head.type		= TRF_MSG_HEART_BOOTLOADER;
	
	pHeartBeat->MajorSoftver		= RADIO_RFA_BOOT_HEARTBT_MAJOR_SOFTVER;
	pHeartBeat->SubSoftver		= RADIO_RFA_BOOT_HEARTBT_SUB_SOFTVER;
	pHeartBeat->SubHardver		= RADIO_RFA_BOOT_HEARTBT_SUB_HARDVER;
	pHeartBeat->DevType			= RADIO_RFA_BOOT_HEARTBT_DEV_TYPE;
	pHeartBeat->WorkStatus		= RADIO_RFA_BOOT_HEARTBT_WORK_STATUS;
	
	Radio_RFA_Boot_Cfg_Buildframe((u8*)pHeartBeat, TMOTE_PLAIN_PUB, Radio_RFA_Boot_Xmit_Get_Pktnum(), RADIO_RFA_BOOT_PAYLOAD_MAC_SN, b_trf_send_buf, sizeof(radio_boot_trf_heartbeat_s));
	
	Radio_RFA_Boot_Send(b_trf_send_buf, b_trf_send_buf[0]);
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Xmit_Heartbeat(void)
 @Description			Radio_RFA_Boot_Xmit_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Xmit_Heartbeat(void)
{
	Radio_RFA_Boot_Do_Xmit_Heartbeat();
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Do_RF_Printf(s8* info)
 @Description			Radio_RFA_Boot_Do_RF_Printf
 @Input				info
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Do_RF_Printf(s8* info)
{
	u8 infolen;
	
	radio_boot_trf_msgdata_s *pMsg = (radio_boot_trf_msgdata_s*)(b_trf_send_buf + 32);
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	infolen = strlen((const char*)info);
	if (infolen > RADIO_RFA_BOOT_MAX_PRINTF) {
		infolen = RADIO_RFA_BOOT_MAX_PRINTF;
	}
	
	Radio_Hal_RF_Interface_Init();
	Radio_Hal_RF_Interrupt_Enable();
	
	pMsg->head.destSN			= 0xFFFFFFFF;
	pMsg->head.version			= TRF_MSG_VERSION;
	pMsg->head.type			= TRF_MSG_DEBUG_INFO;
	
	memcpy(pMsg->pData, info, infolen);
	
	Radio_RFA_Boot_Cfg_Buildframe((u8*)pMsg, TMOTE_PLAIN_PUB, Radio_RFA_Boot_Xmit_Get_Pktnum(), RADIO_RFA_BOOT_PAYLOAD_MAC_SN, b_trf_send_buf, sizeof(radio_boot_trf_msghead_s) + infolen);
	
	Radio_RFA_Boot_Send(b_trf_send_buf, b_trf_send_buf[0]);
}

/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Trf_Printf(const char *fmt, ...)
 @Description			Radio_RFA_Boot_Trf_Printf
 @Input				...
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Trf_Printf(const char *fmt, ...)
{
	__va_list args;
	
	va_start (args, fmt);
	memset(b_trf_prit_buf, 0x00, sizeof(b_trf_prit_buf));
	vsprintf ((char*)b_trf_prit_buf, fmt, args);
	va_end (args);
	Radio_RFA_Boot_Do_RF_Printf((s8*)b_trf_prit_buf);
}

/********************************************** END OF FLEE **********************************************/
