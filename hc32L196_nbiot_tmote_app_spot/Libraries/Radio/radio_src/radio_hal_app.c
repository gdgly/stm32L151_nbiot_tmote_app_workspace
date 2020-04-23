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
#include "radio_command.h"
#include "si446x_api_lib.h"
#include "hal_beep.h"
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

#include "tmesh_xtea.h"

#define RADIO_RF_PAYLOAD_MAC_SN			TCFG_Utility_Get_Factory_MacSN()

#define RADIO_RF_HEARTBT_MAJOR_SOFTVER		TCFG_Utility_Get_Major_SoftwareNumber()
#define RADIO_RF_HEARTBT_MINOR_SOFTVER		TCFG_Utility_Get_Minor_SoftwareNumber()
#define RADIO_RF_HEARTBT_MINOR_HARDVER		TCFG_Utility_Get_Minor_HardwareNumber()
#define RADIO_RF_HEARTBT_DEV_TYPE			TCFG_Utility_Get_DeviceType()

#define RADIO_RF_HEARTBT_WORK_MODE			trf_xmit_get_workmode()
#define RADIO_RF_HEARTBT_SPOT_STAT			0
#define RADIO_RF_HEARTBT_NBNT_STAT			1

#define RADIO_RF_GATCMD_NEARBY_HEART_SEC	3
#define RADIO_RF_GATWAY_NEARBY_HEART_SEC	5

#define RADIO_RF_SENDBUF_SIZE				256
#define RADIO_RF_RECVBUF_SIZE				256
#define RADIO_RF_PINTBUF_SIZE				256

static frameInfo_t sInFrameQ[SIZE_INFRAME_Q];

u8 trf_send_buf[RADIO_RF_SENDBUF_SIZE] = {0};
u8 trf_recv_buf[RADIO_RF_RECVBUF_SIZE] = {0};
u8 trf_pint_buf[RADIO_RF_PINTBUF_SIZE] = {0};

static u32 radio_hearttime_pre = 0;

static s32 radio_cmdtime_nearby = -180;
static s32 radio_gateway_nearby = 10;

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

static u8 trf_xmit_get_workmode(void)
{
	if (TCFG_Utility_Get_ActiveMode() == ACTIVE_MODE_ENABLE)
		return TCFG_Utility_Get_WorkMode();
	else
		return WORK_MODE_STANDBY;
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
	
	radio_trf_msgdata_s* pPayload;
	
	u32 mac_sn = 0;
	
	mac_sn = RADIO_RF_PAYLOAD_MAC_SN;
	
	if (CFG_GET_FROM_FRAME(CFG_P_FRAME_PRE(inmsg), CFG_PRE_TYPE_OS) == XMESHCFG_PRT)
	{
		pPayload = (radio_trf_msgdata_s*)CFG_P_FRAME_PAYLOAD(inmsg);
		
		if (CFG_GET_FROM_FRAME(CFG_P_FRAME_HEAD(inmsg), CFG_HEAD_TYPE_OS) == TMOTE_PLAIN_SET)
		{
			u32 cnt;
			u32 payloadlen;
			
			cnt = CFG_GET_FROM_FRAME(CFG_P_FRAME_HEAD(inmsg), CFG_PKTNUM_OS);
			
			payloadlen = CFG_GET_PAYLOAD_LEN(inmsg) + CFG_FRAME_LEN_SIZE;
			
			tmesh_securityMix(mac_sn);
			
			tmesh_decipher((u8 *)pPayload, payloadlen, &cnt);
			
			if (pPayload->head.destSN != mac_sn) return TRF_NOT_FORME;
			
			HC32_BEEP_Repeat(1, 300, 0);
			
			/* 升级指令 */
			if (pPayload->head.type == TRF_MSG_UPGRADE) {
				Radio_Command_Upgrade();
			}
			/* 传感器灵敏度配置指令 */
			else if (pPayload->head.type == TRF_MSG_SENSITIVITY) {
				u8 sensitivity = ((radio_trf_sensitivity_s*)CFG_P_FRAME_PAYLOAD(inmsg))->sensitivity;
				Radio_Command_Sensitivity(sensitivity);
			}
			/* 工作模式配置指令 */
			else if (pPayload->head.type == TRF_MSG_WORKMODE) {
				u8 workmode = ((radio_trf_workmode_s*)CFG_P_FRAME_PAYLOAD(inmsg))->workmode;
				Radio_Command_WorkMode(workmode);
			}
			/* 无线心跳间隔时间配置指令 */
			else if (pPayload->head.type == TRF_MSG_RFHEART_INTERVAL) {
				u16 hearttime = ((radio_trf_hearttime_s*)CFG_P_FRAME_PAYLOAD(inmsg))->seconds;
				Radio_Command_Heartval(hearttime);
			}
			/* 初始化传感器指令 */
			else if (pPayload->head.type == TRF_MSG_INITBACKGROUND) {
				Radio_Command_InitBackground();
			}
			/* 其他下行指令 */
			else if (pPayload->head.type == TRF_MSG_GENERAL_CMD)
			{
				((radio_trf_generalcmd_s*)CFG_P_FRAME_PAYLOAD(inmsg))->buf[15] = 0;
				
				/* reboot */
				if (strstr(((radio_trf_generalcmd_s*)CFG_P_FRAME_PAYLOAD(inmsg))->buf, "reboot")) {
					Radio_Command_Reboot();
				}
				/* restore */
				else if (strstr(((radio_trf_generalcmd_s*)CFG_P_FRAME_PAYLOAD(inmsg))->buf, "restore")) {
					Radio_Command_Restore();
				}
				/* newsn */
				else if (strstr(((radio_trf_generalcmd_s*)CFG_P_FRAME_PAYLOAD(inmsg))->buf, "newsn")) {
					u32 newsn = 0;
					sscanf(((radio_trf_generalcmd_s*)CFG_P_FRAME_PAYLOAD(inmsg))->buf, "newsn:%08x", &newsn);
					Radio_Command_Newsn(newsn);
				}
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				/* Not Support */
				else {
					Radio_Command_NotSupport();
				}
			}
		}
		else {
			if (pPayload->head.destSN != mac_sn) return TRF_NOT_FORME;
			
			if (CFG_GET_FROM_FRAME(CFG_P_FRAME_HEAD(inmsg), CFG_HEAD_TYPE_OS) == TMOTE_PLAIN_GET)
			{
				__NOP();
			}
			else if (CFG_GET_FROM_FRAME(CFG_P_FRAME_HEAD(inmsg), CFG_HEAD_TYPE_OS) == TMOTE_PLAIN_ACK)
			{
				radio_gateway_nearby = 15;
				
				rc = TRF_IS_ACK;
			}
			else {
				rc = TRF_BAD_MSGTYPE;
			}
		}
	}
	else {
		rc = TRF_BAD_PROTOCAL;
	}
	
	if (rc == TRF_SUCCESS) Radio_RF_Xmit_Default_Resp(100, pPayload->head.type);
	
	return rc;
}

/**********************************************************************************************************
 @Function			void Radio_RF_Xmit_Default_Resp(u8 ret, u8 type)
 @Description			Radio_RF_Xmit_Default_Resp
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RF_Xmit_Default_Resp(u8 ret, u8 type)
{
	radio_trf_defaultrsp_s * pDefaultRsp = (radio_trf_defaultrsp_s*)(trf_send_buf + 32);
	
	pDefaultRsp->head.destSN				= 0xFFFFFFFF;
	pDefaultRsp->head.version			= TRF_MSG_VERSION;
	pDefaultRsp->head.type				= type;
	
	pDefaultRsp->ret					= ret;
	
	Radio_RF_Cfg_Buildframe((u8 *)pDefaultRsp, TMOTE_PLAIN_RSP, trf_xmit_get_pktnum(), RADIO_RF_PAYLOAD_MAC_SN, trf_send_buf, sizeof(radio_trf_defaultrsp_s));
	
	Radio_RF_Transmit(trf_send_buf, trf_send_buf[0]);
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
	
	if (radio_gateway_nearby) radio_gateway_nearby--;
	
	memset((void *)pHeartBeat, 0x00, sizeof(pHeartBeat));
	
	pHeartBeat->head.destSN				= 0xFFFFFFFF;
	pHeartBeat->head.version				= TRF_MSG_VERSION;
	pHeartBeat->head.type				= TRF_MSG_HEART;
	
	pHeartBeat->major_softver			= RADIO_RF_HEARTBT_MAJOR_SOFTVER;
	pHeartBeat->minor_softver			= RADIO_RF_HEARTBT_MINOR_SOFTVER;
	pHeartBeat->minor_hardver			= RADIO_RF_HEARTBT_MINOR_HARDVER;
	pHeartBeat->dev_type				= RADIO_RF_HEARTBT_DEV_TYPE;
	
	pHeartBeat->workmode				= RADIO_RF_HEARTBT_WORK_MODE;
	pHeartBeat->status					= RADIO_RF_HEARTBT_SPOT_STAT;
	pHeartBeat->nbstate					= RADIO_RF_HEARTBT_NBNT_STAT;
	
	Radio_RF_Cfg_Buildframe((u8 *)pHeartBeat, TMOTE_PLAIN_PUB, trf_xmit_get_pktnum(), RADIO_RF_PAYLOAD_MAC_SN, trf_send_buf, sizeof(radio_trf_heartbeat_s));
	
	Radio_RF_Transmit(trf_send_buf, trf_send_buf[0]);
	
	Delay_MS(10);
}

/**********************************************************************************************************
 @Function			void Radio_Trf_Do_Heartbeat(void)
 @Description			Radio_Trf_Do_Heartbeat
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Trf_Do_Heartbeat(void)
{
	Radio_Hal_RF_Interface_Init();
	Radio_Hal_RF_Interrupt_Enable();
	
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
	
	memset((void *)pMsg, 0x00, sizeof(pMsg));
	
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
	Radio_Hal_RF_Interface_Init();
	Radio_Hal_RF_Interrupt_Enable();
	
	Radio_RF_Xmit_Printfbuf(info);
}

/**********************************************************************************************************
 @Function			void Radio_RF_Trf_App_Task(void)
 @Description			Radio_RF_Trf_App_Task
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_RF_Trf_App_Task(void)
{
	u8 len = 0;
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) return;
	
	/* 心跳间隔时间发送心跳包 */
	if ((radio_hearttime_pre + Radio_Hal_RF_Get_Heartval()) < HC32_GetSecondTick()) {
		radio_hearttime_pre = HC32_GetSecondTick();
		Radio_Trf_Do_Heartbeat();
	}
	/* 接收到下行指令持续180秒连续间隔3秒发送心跳包 */
	else if (((radio_hearttime_pre + RADIO_RF_GATCMD_NEARBY_HEART_SEC) < HC32_GetSecondTick()) && ((radio_cmdtime_nearby + 180) > HC32_GetSecondTick())) {
		radio_hearttime_pre = HC32_GetSecondTick();
		Radio_Trf_Do_Heartbeat();
	}
	/* 接收到配置器Ping包连续间隔5秒发送心跳包 */
	else if (((radio_hearttime_pre + RADIO_RF_GATWAY_NEARBY_HEART_SEC) < HC32_GetSecondTick()) && (radio_gateway_nearby > 0)) {
		radio_hearttime_pre = HC32_GetSecondTick();
		Radio_Trf_Do_Heartbeat();
	}
	
	/* 接收无线下行数据 */
	if (TRF_SUCCESS == Radio_RF_Receive(trf_recv_buf, &len)) {
		if (TRF_SUCCESS == Radio_RF_Operate_Recvmsg(trf_recv_buf, len)) {
			radio_cmdtime_nearby = HC32_GetSecondTick();
		}
	}
}

/**********************************************************************************************************
 @Function			s32  Radio_RF_Get_Cmdtime_nearby(void)
 @Description			Radio_RF_Get_Cmdtime_nearby
 @Input				void
 @Return				radio_cmdtime_nearby
**********************************************************************************************************/
s32  Radio_RF_Get_Cmdtime_nearby(void)
{
	return radio_cmdtime_nearby;
}

/**********************************************************************************************************
 @Function			s32  Radio_RF_Get_Gateway_nearby(void)
 @Description			Radio_RF_Get_Gateway_nearby
 @Input				void
 @Return				radio_gateway_nearby
**********************************************************************************************************/
s32  Radio_RF_Get_Gateway_nearby(void)
{
	return radio_gateway_nearby;
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
