/*! @file hal_rf.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n movebroad tech Confidential
 * @n Copyright 2017 movebroad, Inc.
 * @n http://www.movebroad.com
 */
#include "tmesh_rf_app.h"
#include "string.h"
#include "xmeshcfg.h" 
#include "hal_rf.h" 
#include "tmesh_misc.h" 
#include "tmesh_net_utility.h" 
#include "tmesh_cfg.h"
#include "ugrade.h"

static frameInfo_t   sInFrameQ[SIZE_INFRAME_Q];

uint8_t trf_send_buf[128] = {0};
uint8_t trf_recv_buf[256] = {0};

uint8_t upgrad_state;
char g_bootmode;
uint8_t Join_state = JOINING;
static uint8_t state;


void tmesh_rf_QInit(void)
{
  memset(sInFrameQ, 0, sizeof(sInFrameQ));
}

void tmesh_rf_QPush(mrfiPacket_t* rfpacket)
{
	int8_t i,oldest = 0,avail = -1;
	for(i=0;i<SIZE_INFRAME_Q;i++){
		if(sInFrameQ[i].fi_usage == FI_AVAILABLE){
			avail = i;
		}
		if(sInFrameQ[i].orderStamp<sInFrameQ[oldest].orderStamp)
			oldest = i;
	}
	if(avail < 0)
		avail = oldest;
  	memcpy(&sInFrameQ[avail].mrfiPkt, rfpacket, sizeof(mrfiPacket_t));
	sInFrameQ[avail].fi_usage = FI_INUSE_UNTIL_DEL;
	sInFrameQ[avail].orderStamp = sInFrameQ[oldest].orderStamp++;
}

mrfiPacket_t* tmesh_rf_QPop(void)
{
	int8_t i;
  	for(i=0;i<SIZE_INFRAME_Q;i++){
		if(sInFrameQ[i].fi_usage == FI_INUSE_UNTIL_DEL){
			sInFrameQ[i].fi_usage = FI_AVAILABLE;
			return &sInFrameQ[i].mrfiPkt;
		}
	}
	return NULL;
}

void tmesh_rf_data_handle_isr(mrfiPacket_t* rfpacket)
{
	// TODO:filter the wrong sn
	tmesh_rf_QPush(rfpacket);
}

char tmesh_rf_receive(uint8_t *outmsg, uint8_t *len)
{
	mrfiPacket_t* rfpacket;
	rfpacket = tmesh_rf_QPop();
	if(rfpacket!=NULL){
		// get the payload
		*len = 1+(CFG_GET_FROM_FRAME(CFG_P_FRAME_LEN(rfpacket->frame),CFG_LEN_OS));
		memcpy(outmsg,rfpacket->frame,*len);
		return TRF_SUCCESS;
	}
	return TRF_NO_PAYLOAD;
}

char tmesh_rf_send(uint8_t *inmsg, uint8_t len)
{
	tmesh_rf_PrepareToTx(inmsg, len);
	return 0;
}

//Function Description: Configure the package wrapper function
void trf_cfg_buildframe(uint8_t *inmsg,uint8_t pkttype,uint8_t pktnum,uint32_t sn,uint8_t *outsend,uint8_t len)
{
	uint8_t i;
	uint16_t check_sum=0;
	
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_LEN(outsend),CFG_LEN_OS,CFG_FRAME_PAYLOAD_OFS+CFG_FRAME_CRC_SIZE+len-CFG_FRAME_LEN_SIZE);
	CFG_PUT_INTO_FRAME(CFG_P_FRAME_PRE(outsend),CFG_PRE_TYPE_OS,XMESHCFG_PRT);//what type of protocol

	CFG_PUT_INTO_FRAME(CFG_P_FRAME_PRE(outsend),CFG_PRE_VS_OS,CONFIG_VERSION);//version of protocol

	CFG_PUT_INTO_FRAME(CFG_P_FRAME_HEAD(outsend),CFG_HEAD_TYPE_OS,pkttype);//the type of head 
	//Fill the package number into the send cache
	if (pktnum)
	{
		CFG_PUT_INTO_FRAME(CFG_P_FRAME_HEAD(outsend),CFG_PKTNUM_OS,pktnum);
	}
	//If there is data to be sent, the data to be sent is filled into the send buffer packet
	if (len)
	{
		memcpy(CFG_P_FRAME_PAYLOAD(outsend),inmsg,len);
	}
	//Fill SUBSN into the send buffer package
	memcpy(CFG_P_FRAME_SN(outsend),&sn,4);
	
	for (i=1; i<CFG_FRAME_PAYLOAD_OFS+len; i++)
	{
		check_sum += outsend[i];
	}
	outsend[CFG_FRAME_PAYLOAD_OFS+len] = check_sum/0x100;
	outsend[CFG_FRAME_PAYLOAD_OFS+len+1] = check_sum%0x100;
	return;
}

uint8_t trf_xmit_get_pktnum(void)
{
	static uint8_t pktnum = 0;
	return pktnum++;
}

char tmesh_rf_operate_recvmsg(uint8_t *inmsg, uint8_t len)
{
	char rc = TRF_SUCCESS;
//	trf_msg_s* pPayload;
	if (CFG_GET_FROM_FRAME(CFG_P_FRAME_PRE(inmsg), CFG_PRE_TYPE_OS) == UPGRADE_PRT)
	{
		if((UPGD_GET_FROM_FRAME(UPGD_P_FRAME_PRE(inmsg),UPGD_PRE_VS_OS) == UPGRADEVERSION)&&(!memcmp(UPGD_P_FRAME_SN(inmsg),subsn,4))) //对sn号进行校验
        {
          /************************************add by xht 3.23 升级代码*********************************/
          if (UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(inmsg),UPGD_HEAD_TYPE_OS ) == (UPGRADE_REQUEST_RSP))
          {
              Join_state = *(UPGD_P_FRAME_PAYLOAD(inmsg));//allow  join?
          }
          else
          {
            if(upgrad_state != TIME_OUT)
            {
              state = programUpdate(inmsg,subsn);
              if (COMPLETE == state)
              {
                upgrad_state = READY_TO_JUMP;
              }
              else if(UNCOMPLETE == state)
              {
                upgrad_state = DOWNLOADING;
              }else{
				upgrad_state = DOWNLOAD_ERROR;
			  }
            }

          }
        } 
	}else{
		rc = TRF_BAD_PROTOCAL;
	}
	return rc;
}






/********************************************************************************************/
/***************name：        trf_xmit_heartbeat        ****************************************/
/***************function:      broadcast heart to the air every 30s*****************************************/
/***************parameters:    none    ***************************************************/
/***************return:        none:sucess    ***********************************************/
void trf_xmit_heartbeat(void)
{
	static uint32_t hearttime_pre = 0;
	//trf_msghead_s heartPacket;
	trf_heartbeat_s * pHeartBeat = (trf_heartbeat_s*)(trf_send_buf+32);
	if(TRF_OK != tmesh_rf_get_status())
		return;
	pHeartBeat->head.destSN = 0xffffffff;
	pHeartBeat->head.version = TRF_MSG_VERSION;
	pHeartBeat->head.type = TRF_MSG_HEART_BOOTLOADER;
	pHeartBeat->major_softver = 0;
	pHeartBeat->sub_softver   = BOOT_VERSION;
	pHeartBeat->DevType		 = 51;
	if(tmesh_rf_get_status() == TRF_OK)
		pHeartBeat->sub_hardver  = 0x02;
	else
		pHeartBeat->sub_hardver  = 0x01;
	pHeartBeat->work_status  = upgrad_state;
	if(hearttime_pre+10 < Sys_GetSecond()){
		hearttime_pre = Sys_GetSecond();
		// TODO:setup the packet and send it
		trf_cfg_buildframe((uint8_t *)pHeartBeat,TMOTE_PLAIN_PUB,trf_xmit_get_pktnum(),tnet_utility_get_mac_sn(),trf_send_buf,sizeof(trf_heartbeat_s));
		tmesh_rf_send(trf_send_buf, trf_send_buf[0]);
	}
}

uint32_t last_recvtime;
/********************************************************************************************/
/***************name：        trf_get_last_recvtime        ****************************************/
/***************function:      *****************************************/
/***************parameters:    none    ***************************************************/
/***************return:        none:sucess    ***********************************************/
uint32_t trf_get_last_recvtime(void)
{
	return last_recvtime;
}

/*
void trf_app_task(void)
{
	uint8_t len = 0;
	// 1st check to send heartbeat
	trf_xmit_heartbeat();
	// 2st check to receive and process data
	if(TRF_SUCCESS == tmesh_rf_receive(trf_recv_buf, &len)){
		if(TRF_SUCCESS == tmesh_rf_operate_recvmsg(trf_recv_buf, len))
		{
			last_recvtime = Sys_GetSecond();
		}
		
	}
	// 3rd check to send dada
	// 4th check to exit config mode
}
*/

void trf_receive_task(void)
{
	uint8_t len = 0;
	if(TRF_OK != tmesh_rf_get_status())
		return;
	// 2st check to receive and process data
	if(TRF_SUCCESS == tmesh_rf_receive(trf_recv_buf, &len)){
		if(TRF_SUCCESS == tmesh_rf_operate_recvmsg(trf_recv_buf, len))
		{
			last_recvtime = Sys_GetSecond();
		}else{
		}
	}
	// 3rd check to send dada
	// 4th check to exit config mode
}


#include <stdarg.h>
char trf_print2buffer[256];

void trf_do_rfpintf(char* info)
{
	uint8_t infolen;
	trf_msg_s * pMsg = (trf_msg_s*)(trf_send_buf+32);
	infolen = strlen(info);
	if(infolen > 30){
		infolen = 30;
	}	
	if(TRF_OK != tmesh_rf_get_status())
		return;
	
	tmesh_rf_interface_init();
	
	pMsg->head.destSN = 0xffffffff;
	pMsg->head.version = TRF_MSG_VERSION;
	pMsg->head.type = TRF_MSG_DEBUG_INFO;
	strncpy(pMsg->pData,info,infolen);
	// TODO:setup the packet and send it
	trf_cfg_buildframe((uint8_t *)pMsg,TMOTE_PLAIN_PUB,trf_xmit_get_pktnum(),tnet_utility_get_mac_sn(),trf_send_buf,sizeof(trf_msghead_s)+infolen);
	tmesh_rf_send(trf_send_buf, trf_send_buf[0]);
}
/*
void trf_printf(const char *fmt, ...)
{
	__va_list args;
	va_start (args, fmt);

	memset(trf_print2buffer,0,sizeof(trf_print2buffer));
	vsprintf (trf_print2buffer, fmt, args);
	va_end (args);
	trf_do_rfpintf(trf_print2buffer);
}
*/
