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

static frameInfo_t b_sInFrameQ[SIZE_INFRAME_Q];

u8 b_trf_send_buf[RADIO_RFA_BOOT_SDBUF_SIZE] = {0};
u8 b_trf_recv_buf[RADIO_RFA_BOOT_RVBUF_SIZE] = {0};






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
 @Function			void Radio_RFA_Boot_Xmit_Heartbeat(void)
 @Description			Radio_RFA_Boot_Xmit_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Xmit_Heartbeat(void)
{
	static u32 hearttime_pre = 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}























/**********************************************************************************************************
 @Function			void Radio_RFA_Boot_Do_Rf_Pintf(s8* info)
 @Description			Radio_RFA_Boot_Do_Rf_Pintf
 @Input				info
 @Return				void
**********************************************************************************************************/
void Radio_RFA_Boot_Do_Rf_Pintf(s8* info)
{
	u8 infolen;
	
	radio_boot_trf_msgdata_s *pMsg = (radio_boot_trf_msgdata_s*)(b_trf_send_buf + 32);
	
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
	
	Radio_RFA_Boot_Cfg_Buildframe((u8*)pMsg, TMOTE_PLAIN_PUB, Radio_RFA_Boot_Xmit_Get_Pktnum(), 0x81011000, b_trf_send_buf, sizeof(radio_boot_trf_msghead_s) + infolen);
	
	Radio_RFA_Boot_Send(b_trf_send_buf, b_trf_send_buf[0]);
}
































/********************************************** END OF FLEE **********************************************/
