/**
  *********************************************************************************************************
  * @file    udpprotocol.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-04-19
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "udpprotocol.h"
#include "stm32l1xx_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_rtc.h"
#include "sock.h"
#include "string.h"
#include "stdlib.h"

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLSerialize_connect(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options)
 @Description			UDPAUTOCTRLSerialize_connect	: Serializes the connect options into the buffer.
 @Input				buf						: buf the buffer into which the packet will be serialized
					len						: len the length in bytes of the supplied buffer
					options					: options the options to be used to build the connect packet
 @Return				serialized length, or error if 0
**********************************************************************************************************/
int UDPAUTOCTRLSerialize_connect(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options)
{
	UDP_AUTOCTRL_messageData_Connect* connect = (UDP_AUTOCTRL_messageData_Connect*)buf;
	
	if (sizeof(UDP_AUTOCTRL_messageData_Connect) > buflen) return 0;
	
	memset((void*)buf, 0x00, buflen);
	
	connect->messageHead.Head = AUTOCTRL_MESSAGEHEAD_HEAD;
	connect->messageHead.Cmd  = AUTOCTRL_MESSAGEHEAD_CMD;
	connect->messageHead.Len  = htons(sizeof(UDP_AUTOCTRL_messageData_Connect) - sizeof(UDP_AUTOCTRL_messageHead) - sizeof(UDP_AUTOCTRL_messageTail));
	connect->messageHead.Com  = htons(AUTOCTRL_MESSAGEHEAD_COM);
	
	connect->StartCode        = AUTOCTRL_CONNECT_START;
	connect->DevCode          = htonl(AUTOCTRL_CONNECT_DEV);
	connect->CmdCode          = AUTOCTRL_CONNECT_CMD;
	connect->AckCode          = AUTOCTRL_CONNECT_ACK;
	connect->DataLen          = sizeof(AUTOCTRL_Connect_Data);
	
	connect->ConnectData.MacSN[sizeof(connect->ConnectData.MacSN) - 4] = (options->MacSN & 0xFF000000) >> 3*8;
	connect->ConnectData.MacSN[sizeof(connect->ConnectData.MacSN) - 3] = (options->MacSN & 0x00FF0000) >> 2*8;
	connect->ConnectData.MacSN[sizeof(connect->ConnectData.MacSN) - 2] = (options->MacSN & 0x0000FF00) >> 1*8;
	connect->ConnectData.MacSN[sizeof(connect->ConnectData.MacSN) - 1] = (options->MacSN & 0x000000FF) >> 0*8;
	
	connect->ConnectData.SerCode = htonl(AUTOCTRL_CONNECT_SER);
	
	connect->ConnectData.VerInfo[0] = 0x00;
	connect->ConnectData.VerInfo[1] = 0x00;
	connect->ConnectData.VerInfo[2] = 0x00;
	connect->ConnectData.VerInfo[3] = TCFG_Utility_Get_Major_Softnumber();
	connect->ConnectData.VerInfo[4] = TCFG_Utility_Get_Sub_Softnumber();
	
	for (int i = sizeof(connect->ConnectData.IMEI) - 1; i >= 0; i--) {
		u32 utmp = 0;
		if (i != 0) {
			sscanf((const char*)(options->IMEI + i * 2 - 1), "%02X", &utmp);
		}
		else {
			sscanf((const char*)(options->IMEI), "%01X", &utmp);
		}
		connect->ConnectData.IMEI[i] = utmp;
	}
	
	for (int i = 0; i < sizeof(connect->ConnectData.IMSI); i++) {
		u32 utmp = 0;
		sscanf((const char*)(options->IMSI + i * 2), "%02X", &utmp);
		connect->ConnectData.IMSI[i] = utmp;
	}
	
	connect->ConnectData.PackNumber = options->PackNumber;
	
	for (int i = 0; i < (sizeof(connect->ConnectData) + sizeof(connect->DevCode) + sizeof(connect->CmdCode) + sizeof(connect->AckCode) + sizeof(connect->DataLen)); i++) {
		u8* ConnectDataVal = (u8*)&connect->DevCode;
		connect->DataCheck += *(ConnectDataVal + i);
	}
	
	connect->EndCode          = AUTOCTRL_CONNECT_END;
	
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Connect) - sizeof(connect->messageTail) - sizeof(connect->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&connect->messageHead.Cmd;
		connect->messageTail.CRCCheck += *(CheckVal + i);
	}
	
	connect->messageTail.Tail = AUTOCTRL_MESSAGETAIL_TAIL;
	
	return sizeof(UDP_AUTOCTRL_messageData_Connect);
}

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLDeserialize_connack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options)
 @Description			UDPAUTOCTRLDeserialize_connack: Deserializes the supplied (wire) buffer into connack data - return code
 @Input				buf						: buf the raw buffer data, of the correct length determined by the remaining length field
					len						: len the length in bytes of the data in the supplied buffer
					options					: options the options to be used to build the connect packet
 @Return				1 is success, 0 is failure, 2 is registed
**********************************************************************************************************/
int UDPAUTOCTRLDeserialize_connack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Connect_option* options)
{
	UDP_AUTOCTRL_messageData_Connack* connack = (UDP_AUTOCTRL_messageData_Connack*)buf;
	unsigned char checkCode;
	int rc = 1;
	
	if (buflen != sizeof(UDP_AUTOCTRL_messageData_Connack)) {
		rc = 0;
		goto exit;
	}
	
	if ((connack->messageHead.Head != AUTOCTRL_MESSAGEHEAD_HEAD) || (connack->messageTail.Tail != AUTOCTRL_MESSAGETAIL_TAIL)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Connack) - sizeof(connack->messageTail) - sizeof(connack->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&connack->messageHead.Cmd;
		checkCode += *(CheckVal + i);
	}
	
	if (checkCode != connack->messageTail.CRCCheck) {
		rc = 0;
		goto exit;
	}
	
	if ((connack->StartCode != AUTOCTRL_CONNECT_START) || (connack->EndCode != AUTOCTRL_CONNECT_END)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(connack->ConnackData) + sizeof(connack->DevCode) + sizeof(connack->CmdCode) + sizeof(connack->AckCode) + sizeof(connack->DataLen)); i++) {
		u8* ConnackDataVal = (u8*)&connack->DevCode;
		checkCode += *(ConnackDataVal + i);
	}
	
	if (checkCode != connack->DataCheck) {
		rc = 0;
		goto exit;
	}
	
	if (connack->ConnackData.PackNumber != options->PackNumber) {
		rc = 0;
		goto exit;
	}
	
	rc = connack->ConnackData.ResultCode;
	
exit:
	return rc;
}

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLSerialize_status(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options)
 @Description			UDPAUTOCTRLSerialize_status	: Serializes the status options into the buffer.
 @Input				buf						: buf the buffer into which the packet will be serialized
					len						: len the length in bytes of the supplied buffer
					options					: options the options to be used to build the connect packet
 @Return				serialized length, or error if 0
**********************************************************************************************************/
int UDPAUTOCTRLSerialize_status(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options)
{
	UDP_AUTOCTRL_messageData_Status* status = (UDP_AUTOCTRL_messageData_Status*)buf;
	
	if (sizeof(UDP_AUTOCTRL_messageData_Status) > buflen) return 0;
	
	memset((void*)buf, 0x00, buflen);
	
	status->messageHead.Head  = AUTOCTRL_MESSAGEHEAD_HEAD;
	status->messageHead.Cmd   = AUTOCTRL_MESSAGEHEAD_CMD;
	status->messageHead.Len   = htons(sizeof(UDP_AUTOCTRL_messageData_Status) - sizeof(UDP_AUTOCTRL_messageHead) - sizeof(UDP_AUTOCTRL_messageTail));
	status->messageHead.Com   = htons(AUTOCTRL_MESSAGEHEAD_COM);
	
	status->StartCode         = AUTOCTRL_STATUS_START;
	status->DevCode           = htonl(AUTOCTRL_STATUS_DEV);
	status->CmdCode           = AUTOCTRL_STATUS_CMD;
	status->AckCode           = AUTOCTRL_STATUS_ACK;
	status->DataLen           = sizeof(AUTOCTRL_Status_Data);
	
	status->StatusData.MacSN[sizeof(status->StatusData.MacSN) - 4] = (options->MacSN & 0xFF000000) >> 3*8;
	status->StatusData.MacSN[sizeof(status->StatusData.MacSN) - 3] = (options->MacSN & 0x00FF0000) >> 2*8;
	status->StatusData.MacSN[sizeof(status->StatusData.MacSN) - 2] = (options->MacSN & 0x0000FF00) >> 1*8;
	status->StatusData.MacSN[sizeof(status->StatusData.MacSN) - 1] = (options->MacSN & 0x000000FF) >> 0*8;
	
	status->StatusData.SerCode = htonl(AUTOCTRL_STATUS_SER);
	
	status->StatusData.SpotStatus = options->SpotStatus;
	status->StatusData.VbatStatus = options->VbatStatus;
	
	status->StatusData.MagneticX  = options->MagneticX;
	status->StatusData.MagneticY  = options->MagneticY;
	status->StatusData.MagneticZ  = options->MagneticZ;
	
	status->StatusData.Heartbeat  = options->Heartbeat;
	status->StatusData.Algorithm  = options->Algorithm;
	
	struct tm Timer = RTC_ConvUnixToCalendar(options->unixTime);
	u8 tempTimer[13] = {0};
	sprintf((char*)tempTimer, "%02d%02d%02d%02d%02d%02d", Timer.tm_year, Timer.tm_mon, Timer.tm_mday, Timer.tm_hour, Timer.tm_min, Timer.tm_sec);
	for (int i = 0; i < 6; i++) {
		u32 utmp = 0;
		sscanf((const char*)(tempTimer + i * 2), "%02X", &utmp);
		status->StatusData.Timer[i] = utmp;
	}
	
	status->StatusData.SpotCounts = htonl(options->SpotCounts);
	
	status->StatusData.BatchCode  = 0x00;
	
	status->StatusData.PackNumber = options->PackNumber;
	
	for (int i = 0; i < (sizeof(status->StatusData) + sizeof(status->DevCode) + sizeof(status->CmdCode) + sizeof(status->AckCode) + sizeof(status->DataLen)); i++) {
		u8* StatusDataVal = (u8*)&status->DevCode;
		status->DataCheck += *(StatusDataVal + i);
	}
	
	status->EndCode           = AUTOCTRL_STATUS_END;
	
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Status) - sizeof(status->messageTail) - sizeof(status->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&status->messageHead.Cmd;
		status->messageTail.CRCCheck += *(CheckVal + i);
	}
	
	status->messageTail.Tail  = AUTOCTRL_MESSAGETAIL_TAIL;
	
	return sizeof(UDP_AUTOCTRL_messageData_Status);
}

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLDeserialize_staack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options)
 @Description			UDPAUTOCTRLDeserialize_staack : Deserializes the supplied (wire) buffer into staack data - return code
 @Input				buf						: buf the raw buffer data, of the correct length determined by the remaining length field
					len						: len the length in bytes of the data in the supplied buffer
					options					: options the options to be used to build the status packet
 @Return				1 is success, 0 is failure
**********************************************************************************************************/
int UDPAUTOCTRLDeserialize_staack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Status_option* options)
{
	UDP_AUTOCTRL_messageData_Staack* staack = (UDP_AUTOCTRL_messageData_Staack*)buf;
	unsigned char checkCode;
	int rc = 1;
	
	if (buflen != sizeof(UDP_AUTOCTRL_messageData_Staack)) {
		rc = 0;
		goto exit;
	}
	
	if ((staack->messageHead.Head != AUTOCTRL_MESSAGEHEAD_HEAD) || (staack->messageTail.Tail != AUTOCTRL_MESSAGETAIL_TAIL)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Staack) - sizeof(staack->messageTail) - sizeof(staack->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&staack->messageHead.Cmd;
		checkCode += *(CheckVal + i);
	}
	
	if (checkCode != staack->messageTail.CRCCheck) {
		rc = 0;
		goto exit;
	}
	
	if ((staack->StartCode != AUTOCTRL_STATUS_START) || (staack->EndCode != AUTOCTRL_STATUS_END)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(staack->StaackData) + sizeof(staack->DevCode) + sizeof(staack->CmdCode) + sizeof(staack->AckCode) + sizeof(staack->DataLen)); i++) {
		u8* ConnackDataVal = (u8*)&staack->DevCode;
		checkCode += *(ConnackDataVal + i);
	}
	
	if (checkCode != staack->DataCheck) {
		rc = 0;
		goto exit;
	}
	
	if (staack->StaackData.PackNumber != options->PackNumber) {
		rc = 0;
		goto exit;
	}
	
	rc = staack->StaackData.ResultCode;
	
exit:
	return rc;
}

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLSerialize_heart(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options)
 @Description			UDPAUTOCTRLSerialize_heart	: Serializes the heart options into the buffer.
 @Input				buf						: buf the buffer into which the packet will be serialized
					len						: len the length in bytes of the supplied buffer
					options					: options the options to be used to build the connect packet
 @Return				serialized length, or error if 0
**********************************************************************************************************/
int UDPAUTOCTRLSerialize_heart(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options)
{
	UDP_AUTOCTRL_messageData_Heart* heart = (UDP_AUTOCTRL_messageData_Heart*)buf;
	
	if (sizeof(UDP_AUTOCTRL_messageData_Heart) > buflen) return 0;
	
	memset((void*)buf, 0x00, buflen);
	
	heart->messageHead.Head   = AUTOCTRL_MESSAGEHEAD_HEAD;
	heart->messageHead.Cmd    = AUTOCTRL_MESSAGEHEAD_CMD;
	heart->messageHead.Len    = htons(sizeof(UDP_AUTOCTRL_messageData_Heart) - sizeof(UDP_AUTOCTRL_messageHead) - sizeof(UDP_AUTOCTRL_messageTail));
	heart->messageHead.Com    = htons(AUTOCTRL_MESSAGEHEAD_COM);
	
	heart->StartCode          = AUTOCTRL_HEART_START;
	heart->DevCode            = htonl(AUTOCTRL_HEART_DEV);
	heart->CmdCode            = AUTOCTRL_HEART_CMD;
	heart->AckCode            = AUTOCTRL_HEART_ACK;
	heart->DataLen            = sizeof(AUTOCTRL_Heart_Data);
	
	heart->HeartData.MacSN[sizeof(heart->HeartData.MacSN) - 4] = (options->MacSN & 0xFF000000) >> 3*8;
	heart->HeartData.MacSN[sizeof(heart->HeartData.MacSN) - 3] = (options->MacSN & 0x00FF0000) >> 2*8;
	heart->HeartData.MacSN[sizeof(heart->HeartData.MacSN) - 2] = (options->MacSN & 0x0000FF00) >> 1*8;
	heart->HeartData.MacSN[sizeof(heart->HeartData.MacSN) - 1] = (options->MacSN & 0x000000FF) >> 0*8;
	
	heart->HeartData.SerCode = htonl(AUTOCTRL_HEART_SER);
	
	heart->HeartData.Debuff      = options->Debuff;
	heart->HeartData.MagneticX   = options->MagneticX;
	heart->HeartData.MagneticY   = options->MagneticY;
	heart->HeartData.MagneticZ   = options->MagneticZ;
	heart->HeartData.Algorithm   = options->Algorithm;
	heart->HeartData.Heartbeat   = options->Heartbeat;
	heart->HeartData.SpotStatus  = options->SpotStatus;
	heart->HeartData.VbatStatus  = options->VbatStatus;
	heart->HeartData.SleepTime   = options->SleepTime;
	heart->HeartData.RSSI        = options->RSSI;
	heart->HeartData.SNR         = options->SNR;
	heart->HeartData.Temperature = options->Temperature;
	
	heart->HeartData.PackNumber  = options->PackNumber;
	
	for (int i = 0; i < (sizeof(heart->HeartData) + sizeof(heart->DevCode) + sizeof(heart->CmdCode) + sizeof(heart->AckCode) + sizeof(heart->DataLen)); i++) {
		u8* HeartDataVal = (u8*)&heart->DevCode;
		heart->DataCheck += *(HeartDataVal + i);
	}
	
	heart->EndCode            = AUTOCTRL_HEART_END;
	
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Heart) - sizeof(heart->messageTail) - sizeof(heart->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&heart->messageHead.Cmd;
		heart->messageTail.CRCCheck += *(CheckVal + i);
	}
	
	heart->messageTail.Tail   = AUTOCTRL_MESSAGETAIL_TAIL;
	
	return sizeof(UDP_AUTOCTRL_messageData_Heart);
}

/**********************************************************************************************************
 @Function			int UDPAUTOCTRLDeserialize_heack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options)
 @Description			UDPAUTOCTRLDeserialize_heack  : Deserializes the supplied (wire) buffer into heack data - return code
 @Input				buf						: buf the raw buffer data, of the correct length determined by the remaining length field
					len						: len the length in bytes of the data in the supplied buffer
					options					: options the options to be used to build the status packet
 @Return				1 is success, 0 is failure
**********************************************************************************************************/
int UDPAUTOCTRLDeserialize_heack(unsigned char* buf, int buflen, UDP_AUTOCTRL_message_Heart_option* options)
{
	UDP_AUTOCTRL_messageData_Heack* heack = (UDP_AUTOCTRL_messageData_Heack*)buf;
	unsigned char checkCode;
	int rc = 1;
	
	if (buflen != sizeof(UDP_AUTOCTRL_messageData_Heack)) {
		rc = 0;
		goto exit;
	}
	
	if ((heack->messageHead.Head != AUTOCTRL_MESSAGEHEAD_HEAD) || (heack->messageTail.Tail != AUTOCTRL_MESSAGETAIL_TAIL)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(UDP_AUTOCTRL_messageData_Heack) - sizeof(heack->messageTail) - sizeof(heack->messageHead.Head)); i++) {
		u8* CheckVal = (u8*)&heack->messageHead.Cmd;
		checkCode += *(CheckVal + i);
	}
	
	if (checkCode != heack->messageTail.CRCCheck) {
		rc = 0;
		goto exit;
	}
	
	if ((heack->StartCode != AUTOCTRL_STATUS_START) || (heack->EndCode != AUTOCTRL_STATUS_END)) {
		rc = 0;
		goto exit;
	}
	
	checkCode = 0;
	for (int i = 0; i < (sizeof(heack->HeackData) + sizeof(heack->DevCode) + sizeof(heack->CmdCode) + sizeof(heack->AckCode) + sizeof(heack->DataLen)); i++) {
		u8* ConnackDataVal = (u8*)&heack->DevCode;
		checkCode += *(ConnackDataVal + i);
	}
	
	if (checkCode != heack->DataCheck) {
		rc = 0;
		goto exit;
	}
	
	if (heack->HeackData.PackNumber != options->PackNumber) {
		rc = 0;
		goto exit;
	}
	
	rc = heack->HeackData.ResultCode;
	
exit:
	return rc;
}

/********************************************** END OF FLEE **********************************************/
