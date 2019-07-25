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

#define	AUTOCTRL_STATUS_START			0xAA
#define	AUTOCTRL_STATUS_DEV				0x02000A83
#define	AUTOCTRL_STATUS_CMD				0xE7
#define	AUTOCTRL_STATUS_ACK				0xFF
#define	AUTOCTRL_STATUS_SER				0x88888888
#define	AUTOCTRL_STATUS_END				0xBB

#define	AUTOCTRL_STATUS_SPOT_FREE		0x00
#define	AUTOCTRL_STATUS_SPOT_OCCUPY		0x01

#define	AUTOCTRL_STATUS_VBAT_NORMAL		0x00
#define	AUTOCTRL_STATUS_VBAT_UNDER		0x01
#define	AUTOCTRL_STATUS_VBAT_EXHAUST		0x02

#define	AUTOCTRL_HEART_START			0xAA
#define	AUTOCTRL_HEART_DEV				0x02000A83
#define	AUTOCTRL_HEART_CMD				0x0D
#define	AUTOCTRL_HEART_ACK				0xFF
#define	AUTOCTRL_HEART_SER				0x88888888
#define	AUTOCTRL_HEART_END				0xBB

/* AUTOCTRL message Type */
enum AUTOCTRL_msgTypes
{
	AUTOCTRL_CONNACK					= AUTOCTRL_CONNECT_CMD,
	AUTOCTRL_STAACK					= AUTOCTRL_STATUS_CMD,
	AUTOCTRL_HEACK						= AUTOCTRL_HEART_CMD
};

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

/* AUTOCTRL Data connect */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u8								VerInfo[5];
	u8								IMEI[8];
	u8								IMSI[10];
	u8								SpotID[7];
	u8								Reserved[8];
	u8								PackNumber;
} AUTOCTRL_Connect_Data;

/* AUTOCTRL Data connack */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u8								ResultCode;
	u8								Reserved[3];
	u8								PackNumber;
} AUTOCTRL_Connack_Data;

/* AUTOCTRL message Data connect */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	AUTOCTRL_Connect_Data				ConnectData;
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
	AUTOCTRL_Connack_Data				ConnackData;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Connack;

/* AUTOCTRL message connect options */
typedef struct
{
	u32								MacSN;
	char*							IMEI;
	char*							IMSI;
	u8								PackNumber;
} UDP_AUTOCTRL_message_Connect_option;

#define UDP_AUTOCTRL_Packet_connectData_initializer	{0x00000000, NULL, NULL, 0x00}

/* AUTOCTRL Data status */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u8								SpotStatus;
	u8								VbatStatus;
	u8								SpotID[7];
	u32								MagneticX;
	u32								MagneticY;
	u32								MagneticZ;
	u8								Algorithm;
	u8								Heartbeat;
	u8								Timer[6];
	u32								SpotCounts;
	u8								BatchCode;
	u8								Reserved[8];
	u8								PackNumber;
} AUTOCTRL_Status_Data;

/* AUTOCTRL Data staack */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u8								ResultCode;
	u8								Reserved[3];
	u8								PackNumber;
} AUTOCTRL_Staack_Data;

/* AUTOCTRL message Data status */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	AUTOCTRL_Status_Data				StatusData;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Status;

/* AUTOCTRL message Data staack */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	AUTOCTRL_Staack_Data				StaackData;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Staack;

/* AUTOCTRL message status options */
typedef struct
{
	u32								MacSN;
	u8								SpotStatus;
	u32								SpotCounts;
	u8								VbatStatus;
	u32								MagneticX;
	u32								MagneticY;
	u32								MagneticZ;
	u8								Algorithm;
	u8								Heartbeat;
	u32								unixTime;
	u8								PackNumber;
} UDP_AUTOCTRL_message_Status_option;

#define UDP_AUTOCTRL_Packet_statusData_initializer	{0x00000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00}

/* AUTOCTRL Data heart */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u16								Debuff;
	u8								SpotID[7];
	u32								MagneticX;
	u32								MagneticY;
	u32								MagneticZ;
	u8								Algorithm;
	u8								Heartbeat;
	u8								SpotStatus;
	u8								VbatStatus;
	u8								SleepTime;
	char								RSSI;
	u8								SNR;
	u8								Temperature;
	u8								Reserved[8];
	u8								PackNumber;
} AUTOCTRL_Heart_Data;

/* AUTOCTRL Data heack */
typedef __packed struct
{
	u8								MacSN[12];
	u32								SerCode;
	u8								ResultCode;
	u8								Reserved[3];
	u8								PackNumber;
} AUTOCTRL_Heack_Data;

/* AUTOCTRL message Data heart */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	AUTOCTRL_Heart_Data					HeartData;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Heart;

/* AUTOCTRL message Data heack */
typedef __packed struct
{
	UDP_AUTOCTRL_messageHead				messageHead;
	u8								StartCode;
	u32								DevCode;
	u8								CmdCode;
	u8								AckCode;
	u8								DataLen;
	AUTOCTRL_Heack_Data					HeackData;
	u8								DataCheck;
	u8								EndCode;
	UDP_AUTOCTRL_messageTail				messageTail;
} UDP_AUTOCTRL_messageData_Heack;

/* AUTOCTRL message heart options */
typedef struct
{
	u32								MacSN;
	u16								Debuff;
	u8								Algorithm;
	u8								Heartbeat;
	u8								SpotStatus;
	u8								VbatStatus;
	u32								MagneticX;
	u32								MagneticY;
	u32								MagneticZ;
	u8								SleepTime;
	char								RSSI;
	u8								SNR;
	u8								Temperature;
	u8								PackNumber;
} UDP_AUTOCTRL_message_Heart_option;

#define UDP_AUTOCTRL_Packet_heartData_initializer		{0x00000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00}

#define	SKYNET_MESSAGEHEAD_START			0xAA
#define	SKYNET_MESSAGETALL_END			0xBB

#define	SKYNET_MANUFACTURER				"0571830312582019070901"
#define	SKYNET_HARDWAREVER				"05718303125810123001"
#define	SKYNET_SOFTWAREVER				"05718303125810010001"

#define	SKYNET_MONITOR_SINGLE			1
#define	SKYNET_MONITOR_DOUBLE			2
#define	SKYNET_MONITOR_TYPE				SKYNET_MONITOR_DOUBLE

#define	SKYNET_CONNECT_CMD				0xF1
#define	SKYNET_CONNECT_MANUFACTURER		SKYNET_MANUFACTURER
#define	SKYNET_CONNECT_HARDWAREVER		SKYNET_HARDWAREVER
#define	SKYNET_CONNECT_SOFTWAREVER		SKYNET_SOFTWAREVER
#define	SKYNET_CONNECT_ACK				0xF1

#define	SKYNET_STATUS_CMD				0xE7
#define	SKYNET_STATUS_MANUFACTURER		SKYNET_MANUFACTURER
#define	SKYNET_STATUS_HARDWAREVER		SKYNET_HARDWAREVER
#define	SKYNET_STATUS_SOFTWAREVER		SKYNET_SOFTWAREVER
#define	SKYNET_STATUS_ACK				0xE7

#define	SKYNET_HEART_CMD				0X0D
#define	SKYNET_HEART_ACK				0X0D

/* SKYNET message Type */
enum SKYNET_msgTypes
{
	SKYNET_CONNACK						= SKYNET_CONNECT_CMD,
	SKYNET_STAACK						= SKYNET_STATUS_CMD,
	SKYNET_HEACK						= SKYNET_HEART_CMD
};

/* SKYNET message Head */
typedef __packed struct
{
	u8								StartCode;
	u8								CmdType;
	u16								DataLen;
} UDP_SKYNET_messageHead;

/* SKYNET message Tail */
typedef __packed struct
{
	u8								SumCheck;
	u8								TailCode;
} UDP_SKYNET_messageTail;

/* SKYNET Data connect */
typedef __packed struct
{
	u8								ManufacturerCode[11];
	u8								IMEI[8];
	u8								MacSN[20];
	u8								HardwareVer[10];
	u8								SoftwareVer[10];
	u8								ICCID[10];
	u8								Reserved[6];
	u8								PackNumber;
} SKYNET_Connect_Data;

/* SKYNET Data connack */
typedef __packed struct
{
	u8								ResultCode;
	u8								ServerDate[7];
	u8								PackNumber;
} SKYNET_Connack_Data;

/* SKYNET message Data connect */
typedef __packed struct
{
	UDP_SKYNET_messageHead				messageHead;
	SKYNET_Connect_Data					ConnectData;
	UDP_SKYNET_messageTail				messageTail;
} UDP_SKYNET_messageData_Connect;

/* SKYNET message Data connack */
typedef __packed struct
{
	UDP_SKYNET_messageHead				messageHead;
	SKYNET_Connack_Data					ConnackData;
	UDP_SKYNET_messageTail				messageTail;
} UDP_SKYNET_messageData_Connack;

/* SKYNET message connect options */
typedef struct
{
	u32								MacSN;
	char*							ManufacturerCode;
	char*							IMEI;
	char*							ICCID;
	char*							HardwareVer;
	char*							SoftwareVer;
	u8								PackNumber;
} UDP_SKYNET_message_Connect_option;

#define UDP_SKYNET_Packet_connectData_initializer		{0x00000000, NULL, NULL, NULL, NULL, NULL, 0x00}

/* SKYNET Data status */
typedef __packed struct
{
	u8								ManufacturerCode[11];
	u8								IMEI[8];
	u8								MacSN[20];
	u8								HardwareVer[10];
	u8								SoftwareVer[10];
	u8								ICCID[10];
	u8								Rssi;
	u8								Batt;
	char								Temperature;
	u16								MagneticX;
	u16								MagneticY;
	u16								MagneticZ;
	s16								MagneticBackX;
	s16								MagneticBackY;
	s16								MagneticBackZ;
	u8								MonitorMode;
	u8								Sensitivity;
	u16								HeartTimer;
	u8								SpotStatus;
	u8								SpotTimer[7];
	u16								SpotCounts;
	u8								Reserved[6];
	u8								PackNumber;
} SKYNET_Status_Data;

/* SKYNET Data staack */
typedef __packed struct
{
	u8								ResultCode;
	u8								ServerDate[7];
	u8								PackNumber;
} SKYNET_Staack_Data;

/* SKYNET message Data connect */
typedef __packed struct
{
	UDP_SKYNET_messageHead				messageHead;
	SKYNET_Status_Data					StatusData;
	UDP_SKYNET_messageTail				messageTail;
} UDP_SKYNET_messageData_Status;

/* SKYNET message Data connack */
typedef __packed struct
{
	UDP_SKYNET_messageHead				messageHead;
	SKYNET_Staack_Data					StaackData;
	UDP_SKYNET_messageTail				messageTail;
} UDP_SKYNET_messageData_Staack;

/* SKYNET message status options */
typedef struct
{
	u32								MacSN;
	char*							ManufacturerCode;
	char*							IMEI;
	char*							ICCID;
	char*							HardwareVer;
	char*							SoftwareVer;
	u8								Rssi;
	u8								Batt;
	char								Temperature;
	u16								MagneticX;
	u16								MagneticY;
	u16								MagneticZ;
	s16								MagneticBackX;
	s16								MagneticBackY;
	s16								MagneticBackZ;
	u8								MonitorMode;
	u8								Sensitivity;
	u16								HeartTimer;
	u8								SpotStatus;
	u32								unixTime;
	u16								SpotCounts;
	u8								PackNumber;
} UDP_SKYNET_message_Status_option;

#define UDP_SKYNET_Packet_statusData_initializer		{0x00000000, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00}

int UDPAUTOCTRLSerialize_connect(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options);
int UDPAUTOCTRLDeserialize_connack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options);

int UDPAUTOCTRLSerialize_status(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options);
int UDPAUTOCTRLDeserialize_staack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options);

int UDPAUTOCTRLSerialize_heart(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options);
int UDPAUTOCTRLDeserialize_heack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options);

int UDPSKYNETSerialize_connect(unsigned char* buf, int buflen, UDP_SKYNET_message_Connect_option* options);
int UDPSKYNETDeserialize_connack(unsigned char* buf, int buflen, UDP_SKYNET_message_Connect_option* options);

int UDPSKYNETSerialize_status(unsigned char* buf, int buflen, UDP_SKYNET_message_Status_option* options);
int UDPSKYNETDeserialize_staack(unsigned char* buf, int buflen, UDP_SKYNET_message_Status_option* options);

#endif /* __UDP_PROTOCOL_H */
