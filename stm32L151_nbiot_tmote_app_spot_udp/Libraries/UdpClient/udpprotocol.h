#ifndef __UDP_PROTOCOL_H
#define   __UDP_PROTOCOL_H

#include "sys.h"
#include "udpconfig.h"

#define	AUTOCTRL_MESSAGEHEAD_HEAD		0x80
#define	AUTOCTRL_MESSAGETAIL_TAIL		0x81

#define	AUTOCTRL_MESSAGEHEAD_CMD			0xFF
#define	AUTOCTRL_MESSAGEHEAD_COM			0x0000

#define	AUTOCTRL_CONNECT_START			0xAA
#define	AUTOCTRL_CONNECT_DEV			0x02000A83
#define	AUTOCTRL_CONNECT_CMD			0xF1
#define	AUTOCTRL_CONNECT_ACK			0xFF
#define	AUTOCTRL_CONNECT_SER			0x88888888
#define	AUTOCTRL_CONNECT_END			0xBB

/* AUTOCTRL message Head */
typedef __packed struct
{
	u8								Head;
	u8								Cmd;
	u16								Len;
	u16								Com;
} UDP_AUTOCTRL_messageHead;

/* AUTOCTRL message Tail */
typedef __packed struct
{
	u8								CRCCheck;
	u8								Tail;
} UDP_AUTOCTRL_messageTail;

/* AUTOCTRL message Data connect */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	u8								MacSN[12];
	u32								SerCode;
	u8								VerInfo[5];
	u8								IMEI[8];
	u8								IMSI[10];
	u8								SpotID[7];
	u8								Reserved[8];
	u8								PackNumber;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Connect;

/* AUTOCTRL message Data connack */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	u8								MacSN[12];
	u32								SerCode;
	u8								ResultCode;
	u8								Reserved[3];
	u8								PackNumber;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Connack;













































#endif /* __UDP_PROTOCOL_H */
