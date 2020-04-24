#ifndef __RADIO_HAL_APP_H
#define   __RADIO_HAL_APP_H

#include "sys.h"
#include "radio_hal_common.h"

typedef __packed struct _radio_trf_msg_h
{
	u32						destSN;
	u8						version;
	u8						type;
} radio_trf_msghead_s;


typedef __packed struct _radio_trf_msg_m
{
	radio_trf_msghead_s			head;
	char						pData[1];
} radio_trf_msgdata_s;

typedef __packed struct _radio_trf_heartbeat
{
	radio_trf_msghead_s			head;
	u8						major_softver;
	u8						minor_softver;
	u8						dev_type;
	u8						minor_hardver;
	u8						workmode:2;
	u8						status:3;
	u8						nbstate:1;
} radio_trf_heartbeat_s;

typedef __packed struct _radio_trf_defaultrsp
{
	radio_trf_msghead_s			head;
	u8						ret;
} radio_trf_defaultrsp_s;

typedef __packed struct _radio_trf_sensitivity
{
	radio_trf_msghead_s			head;
	u8						sensitivity;
} radio_trf_sensitivity_s;

typedef __packed struct _radio_trf_workmode
{
	radio_trf_msghead_s			head;
	u8						workmode;
} radio_trf_workmode_s;

typedef __packed struct _radio_trf_hearttime
{
	radio_trf_msghead_s			head;
	u16						seconds;
} radio_trf_hearttime_s;

typedef __packed struct _radio_trf_generalcmd
{
	radio_trf_msghead_s			head;
	char						buf[16];
} radio_trf_generalcmd_s;



















void Radio_RF_Data_Handle_ISR(mrfiPacket_t* rfpacket);

char Radio_RF_Receive(u8 *outmsg, u8 *len);

char Radio_RF_Transmit(u8 *inmsg, u8 len);

char Radio_RF_Operate_Recvmsg(u8 *inmsg, u8 len);

void Radio_RF_Xmit_Default_Resp(u8 ret, u8 type);

void Radio_RF_Xmit_Heartbeat(void);

void Radio_Trf_Do_Heartbeat(void);

void Radio_RF_Xmit_Printfbuf(char* info);

void Radio_Trf_Do_Printfbuf(char* info);

void Radio_RF_Trf_App_Task(void);

s32  Radio_RF_Get_Cmdtime_nearby(void);

s32  Radio_RF_Get_Gateway_nearby(void);





void Radio_RF_Trf_Printf_Level0(const char *fmt, ...);
void Radio_RF_Trf_Printf_Level1(const char *fmt, ...);
void Radio_RF_Trf_Printf_Level2(const char *fmt, ...);
void Radio_RF_Trf_Printf_Level3(const char *fmt, ...);

void Radio_RF_Trf_Printf(const char *fmt, ...);




#endif /* __RADIO_HAL_APP_H */
