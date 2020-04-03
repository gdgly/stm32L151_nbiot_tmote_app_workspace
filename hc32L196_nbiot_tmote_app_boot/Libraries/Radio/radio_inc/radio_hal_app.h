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
	u8						sub_softver;
	u8						dev_type;
	u8						sub_hardver;
	u8						work_status;
} radio_trf_heartbeat_s;








void Radio_RF_Data_Handle_ISR(mrfiPacket_t* rfpacket);

char Radio_RF_Receive(u8 *outmsg, u8 *len);

char Radio_RF_Transmit(u8 *inmsg, u8 len);

char Radio_RF_Operate_Recvmsg(u8 *inmsg, u8 len);











void Radio_RF_Xmit_Heartbeat(void);

void Radio_RF_Xmit_Printfbuf(char* info);



















#endif /* __RADIO_HAL_APP_H */
