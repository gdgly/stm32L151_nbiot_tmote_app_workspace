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
	
	connect->ConnectData.VerInfo[0] = 0x22;
	connect->ConnectData.VerInfo[1] = 0x22;
	connect->ConnectData.VerInfo[2] = 0x22;
	connect->ConnectData.VerInfo[3] = 0x22;
	connect->ConnectData.VerInfo[4] = 0x22;
	
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




















































/********************************************** END OF FLEE **********************************************/
