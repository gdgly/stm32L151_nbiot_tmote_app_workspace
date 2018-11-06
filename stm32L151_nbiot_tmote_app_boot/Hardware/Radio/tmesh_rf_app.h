#ifndef __TMESH_RF_APP_H
#define   __TMESH_RF_APP_H

#include "sys.h"



#define SIZE_INFRAME_Q		2
#define MRFI_RX_METRICS_SIZE 2

typedef struct
{
  uint8_t frame[255];
  uint8_t rxMetrics[MRFI_RX_METRICS_SIZE];
} mrfiPacket_t;

typedef struct
{
  volatile uint8_t      fi_usage;
           uint32_t      orderStamp;
           mrfiPacket_t mrfiPkt;
} frameInfo_t;

#define   FI_AVAILABLE         0   /* entry available for use */
#define   FI_INUSE_UNTIL_DEL   1   /* in use. will be explicitly reclaimed */

enum trfStatus  {
  TRF_SUCCESS,
  TRF_NO_PAYLOAD,
  TRF_BAD_PROTOCAL,
  TRF_BAD_MSGTYPE,
  TRF_NOT_FORME,
};


////zhangdh@20170810 redefine the message header type
typedef __packed struct trfmsg_h
{
	uint32_t       destSN;	// the dest sn
	uint8_t        version;	// the protocal version  
	uint8_t        type;	// the msg type 
}trf_msghead_s;       //8 Bytes


typedef __packed struct _trf_msg
{
	trf_msghead_s head;
	char pData[1];		//
}trf_msg_s;

#define TRF_MSG_VERSION	0x01

#define TRF_MSG_REBOOT             24
#define TRF_MSG_HEART              27


#define TRF_MSG_DEFAULT		   	   49
#define TRF_MSG_SENSITIVITY		   50
#define TRF_MSG_WORKMODE		   51
#define TRF_MSG_INITBACKGROUND 	   52
#define TRF_MSG_BASICINFO		   53
#define TRF_MSG_UPGRADE			   54
#define TRF_MSG_STATUS			   55
#define TRF_MSG_HEART_BOOTLOADER   56
#define TRF_MSG_RFHEART_INTERVAL   57
#define TRF_MSG_DEBUG_INFO   	   58
#define TRF_MSG_DEBUG_STATUS   	   58
#define TRF_MSG_REMOTE_SERVER  	   59
#define TRF_MSG_DYNAMICINFO		   60
#define TRF_MSG_JSON		   	   61
#define TRF_MSG_GENERAL_CMD   	   62

typedef __packed struct _trf_heartbeat
{
	trf_msghead_s head;
	uint8_t major_softver;		//	increase when the version is released
	uint8_t sub_softver;		//	increase from 0 after the major version is released
	uint8_t DevType;			//	what kind of device
	uint8_t sub_hardver;		//	what kind of hardware
	uint8_t work_status;		//	what kind of hardware
}trf_heartbeat_s;



void tmesh_rf_data_handle_isr(mrfiPacket_t* rfpacket);
char tmesh_rf_receive(uint8_t *outmsg, uint8_t *len);
char tmesh_rf_send(uint8_t *inmsg, uint8_t len);
char tmesh_rf_operate_recvmsg(uint8_t *inmsg, uint8_t len);
void trf_app_task(void);
void trf_receive_task(void);
void trf_xmit_heartbeat(void);
uint32_t trf_get_last_recvtime(void);
//void trf_printf(const char *fmt, ...);
void trf_do_rfpintf(char* info);
#endif

