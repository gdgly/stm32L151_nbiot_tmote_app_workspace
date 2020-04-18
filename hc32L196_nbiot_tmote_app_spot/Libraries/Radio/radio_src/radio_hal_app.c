/**
  *********************************************************************************************************
  * @file    radio_hal_app.c
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
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

#define RADIO_RF_PAYLOAD_MAC_SN			TCFG_EEPROM_Get_MAC_SN()















#define RADIO_RF_SENDBUF_SIZE				256
#define RADIO_RF_RECVBUF_SIZE				256
#define RADIO_RF_PINTBUF_SIZE				256

static frameInfo_t sInFrameQ[SIZE_INFRAME_Q];

u8 trf_send_buf[RADIO_RF_SENDBUF_SIZE] = {0};
u8 trf_recv_buf[RADIO_RF_RECVBUF_SIZE] = {0};
u8 trf_pint_buf[RADIO_RF_PINTBUF_SIZE] = {0};

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
	char rc;
	
	rc = Radio_Hal_RF_PrepareToTx(inmsg, len);
	
	return rc;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return rc;
}

/**********************************************************************************************************
 @Function			void Radio_RF_Xmit_Heartbeat(void)
 @Description			Radio_RF_Xmit_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RF_Xmit_Heartbeat(void)
{
	radio_trf_heartbeat_s * pHeartBeat = (radio_trf_heartbeat_s*)(trf_send_buf + 32);
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	
	
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void Radio_Trf_Do_Heartbeat(void)
 @Description			Radio_Trf_Do_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Trf_Do_Heartbeat(void)
{
	Radio_RF_Xmit_Heartbeat();
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
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	infolen = strlen(info);
	
	if (infolen > 44) infolen = 44;
	
	pMsg->head.destSN					= 0xFFFFFFFF;
	pMsg->head.version					= TRF_MSG_VERSION;
	pMsg->head.type					= TRF_MSG_DEBUG_INFO;
	
	memcpy(pMsg->pData, info, infolen);
	
	Radio_RF_Cfg_Buildframe((u8 *)pMsg, TMOTE_PLAIN_PUB, trf_xmit_get_pktnum(), RADIO_RF_PAYLOAD_MAC_SN, trf_send_buf, sizeof(radio_trf_msghead_s) + infolen);
	
	Radio_RF_Transmit(trf_send_buf, trf_send_buf[0]);
	
	if (trf_send_buf[0] >= RADIO_TX_ALMOST_EMPTY_THRESHOLD) {
		radio_core_StartTx_dummy(Radio_Hal_RF_Get_Channel());
	}
}

/**********************************************************************************************************
 @Function			void Radio_Trf_Do_Printfbuf(char* info)
 @Description			Radio_Trf_Do_Printfbuf
 @Input				info
 @Return				void
**********************************************************************************************************/
void Radio_Trf_Do_Printfbuf(char* info)
{
	Radio_RF_Xmit_Printfbuf(info);
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
	vsprintf ((char *)trf_pint_buf, fmt, args);
	va_end (args);
	
	Radio_Trf_Do_Printfbuf((char *)trf_pint_buf);
	
	Delay_US(300);
}















/********************************************** END OF FLEE **********************************************/
