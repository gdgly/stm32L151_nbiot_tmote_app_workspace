/**
  *********************************************************************************************************
  * @file    udpfunc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-04-18
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "udpfunc.h"
#include "sock.h"
#include "string.h"
#include "stdlib.h"

/**********************************************************************************************************
 @Function			static unsigned int UDP_AUTOControl_GetNextPackNumber(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_GetNextPackNumber		: 获取下一个消息ID
 @Input				pClient							: UDP客户端实例
 @Return				PackNumber						: 消息ID
**********************************************************************************************************/
static unsigned int UDP_AUTOControl_GetNextPackNumber(UDP_ClientsTypeDef* pClient)
{
	pClient->MsgIdNormal = (pClient->MsgIdNormal == UDP_MAX_MSG_ID) ? 1 : pClient->MsgIdNormal + 1;
	return pClient->MsgIdNormal;
}

/**********************************************************************************************************
 @Function			unsigned int UDP_AUTOControl_GetNextStatusNumber(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_GetNextStatusNumber	: 获取下一个消息ID
 @Input				pClient							: UDP客户端实例
 @Return				PackNumber						: 消息ID
**********************************************************************************************************/
unsigned int UDP_AUTOControl_GetNextStatusNumber(UDP_ClientsTypeDef* pClient)
{
	pClient->MsgIdStatus = (pClient->MsgIdStatus == UDP_MAX_MSG_ID) ? 1 : pClient->MsgIdStatus + 1;
	return pClient->MsgIdStatus;
}

/**********************************************************************************************************
 @Function			unsigned int UDP_AUTOControl_GetNowsStatusNumber(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_GetNowsStatusNumber	: 获取下一个消息ID
 @Input				pClient							: UDP客户端实例
 @Return				PackNumber						: 消息ID
**********************************************************************************************************/
unsigned int UDP_AUTOControl_GetNowsStatusNumber(UDP_ClientsTypeDef* pClient)
{
	return pClient->MsgIdStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_ReadPacket(UDP_ClientsTypeDef* pClient, int *msgTypes)
 @Description			UDP_AUTOControl_ReadPacket	: AutoControl获取数据包数据与消息类型
 @Input				pClient					: UDP客户端实例
					msgTypes					: AutoControl消息类型
 @Return				UDP_StatusTypeDef			: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_ReadPacket(UDP_ClientsTypeDef* pClient, int *msgTypes)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int Rlength = 0;													//读取数据长度
	int Rleftlength = 0;												//剩余读取数据长度
	int len = 0;
	int rem_len = 0;
	
	UDP_AUTOCTRL_messageHead* mhead = (UDP_AUTOCTRL_messageHead*)pClient->Recvbuf;
	
	/* 1. read the header four byte. This has the packet length in it */
	UDPStatus = pClient->SocketStack->Read(pClient->SocketStack, (char *)pClient->Recvbuf, 4, &Rlength, &Rleftlength);
	if ((UDPStatus != UDP_OK) || (Rlength != 4)) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	len = Rlength;
	
	rem_len = ntohs(mhead->Len) + sizeof(mhead->Com) + sizeof(UDP_AUTOCTRL_messageTail);
	
	if (rem_len > (pClient->Recvbuf_size - len)) {
		UDPStatus = UDP_BUFFER_OVERFLOW;
		goto exit;
	}
	
	/* 2. read the rest of the buffer using a callback to supply the rest of the data */
	if ((rem_len <= 0) || ((UDPStatus = pClient->SocketStack->Read(pClient->SocketStack, (char *)pClient->Recvbuf + len, rem_len, &Rlength, &Rleftlength)) != UDP_OK)) {
		goto exit;
	}
	
	pClient->Recvlen = len + Rlength;
	
	*msgTypes = pClient->Recvbuf[11];
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_AUTOControl_ConnackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_ConnackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_AUTOControl_ConnackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_AUTOControl_StaackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_StaackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_AUTOControl_StaackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_AUTOControl_HeackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_AUTOControl_HeackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_AUTOControl_HeackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_RecvPacketProcess(UDP_ClientsTypeDef* pClient, int *msgTypes)
 @Description			UDP_AUTOControl_RecvPacketProcess	: AutoControl接收数据包处理
 @Input				pClient						: UDP客户端实例
					msgTypes						: AutoControl消息类型
 @Return				UDP_StatusTypeDef				: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_RecvPacketProcess(UDP_ClientsTypeDef* pClient, int *msgTypes)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int packetType = -1;
	
	UDPStatus = UDP_AUTOControl_ReadPacket(pClient, &packetType);				//获取MqttSN数据并提取消息类型
	if (UDPStatus != UDP_OK) {											//没有获取到数据
		UDPStatus = UDP_RECVPACKET_NONE;
		goto exit;
	}
	
	switch (packetType)													//根据消息类型执行不同处理
	{
	case AUTOCTRL_CONNACK:
		UDPStatus = UDP_AUTOControl_ConnackEvent(pClient);
		break;
	
	case AUTOCTRL_STAACK:
		UDPStatus = UDP_AUTOControl_StaackEvent(pClient);
		break;
	
	case AUTOCTRL_HEACK:
		UDPStatus = UDP_AUTOControl_HeackEvent(pClient);
		break;
	
	default:
		UDPStatus = UDP_ERROR;
		break;
	}
	
	if (UDPStatus == UDP_OK) {
		*msgTypes = packetType;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_WaitforRecvAck(UDP_ClientsTypeDef* pClient, int msgType, Stm32_CalculagraphTypeDef* timerS)
 @Description			UDP_AUTOControl_WaitforRecvAck	: AutoControl等待接收到相应应答消息类型
 @Input				pClient						: UDP客户端实例
					msgType						: AutoControl消息类型
					timer						: 超时计时器
 @Return				UDP_StatusTypeDef				: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_WaitforRecvAck(UDP_ClientsTypeDef* pClient, int msgType, Stm32_CalculagraphTypeDef* timerS)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int packetType = -1;
	
	while (packetType != msgType) {
		if ((UDPStatus = UDP_AUTOControl_RecvPacketProcess(pClient, &packetType)) == UDP_ERROR) {	//接收数据处理
			goto exit;
		}
		if (Stm32_Calculagraph_IsExpiredSec(timerS) == true) {								//到达超时时间
			break;
		}
		
		UDP_WaitforCallback(pClient);
	}
	
	if (packetType != msgType) {
		UDPStatus = UDP_CMD_TIMEOUT;
	}
	else {
		UDPStatus = UDP_OK;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_Connect(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Connect_option* options)
 @Description			UDP_AUTOControl_Connect	: AutoControl发送注册信息服务器
 @Input				pClient				: UDP客户端实例
					options				: AutoControl连接选项
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_Connect(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Connect_option* options)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	UDP_AUTOCTRL_message_Connect_option Default_options = UDP_AUTOCTRL_Packet_connectData_initializer;
	Stm32_CalculagraphTypeDef Connect_timer_s;
	int len = 0;
	
	/* set default options if none were supplied */
	if (options == NULL) {
		options = &Default_options;
	}
	
	/* Configuration Calculagraph for Connect Timer */
	Stm32_Calculagraph_CountdownSec(&Connect_timer_s, pClient->Command_Timeout_Sec);
	
	options->PackNumber = UDP_AUTOControl_GetNextPackNumber(pClient);
	
	/* Serialize Connect Command Buffer */
	if ((len = UDPAUTOCTRLSerialize_connect(pClient->Sendbuf, pClient->Sendbuf_size, options)) <= 0) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* Send Connect Command Buffer to AutoControl Server */
	if ((UDPStatus = pClient->SocketStack->Write(pClient->SocketStack, (char *)pClient->Sendbuf, len)) != UDP_OK) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* This will be a blocking call, wait for the UDPAUTOCTRL_CONNACK */
	if ((UDPStatus = UDP_AUTOControl_WaitforRecvAck(pClient, AUTOCTRL_CONNACK, &Connect_timer_s)) == UDP_OK) {
		if (UDPAUTOCTRLDeserialize_connack(pClient->Recvbuf, pClient->Recvlen, options) != 0) {
			UDPStatus = UDP_OK;
		}
		else {
			UDPStatus = UDP_ERROR;
			goto exit;
		}
	}
	else {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_Status(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Status_option* options)
 @Description			UDP_AUTOControl_Status	: AutoControl发送状态信息服务器
 @Input				pClient				: UDP客户端实例
					options				: AutoControl状态选项
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_Status(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Status_option* options)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	UDP_AUTOCTRL_message_Status_option Default_options = UDP_AUTOCTRL_Packet_statusData_initializer;
	Stm32_CalculagraphTypeDef Connect_timer_s;
	int len = 0;
	
	/* set default options if none were supplied */
	if (options == NULL) {
		options = &Default_options;
	}
	
	/* Configuration Calculagraph for Connect Timer */
	Stm32_Calculagraph_CountdownSec(&Connect_timer_s, pClient->Command_Timeout_Sec);
	
#if UDP_MSGID_STATUS_TYPE
	options->PackNumber = UDP_AUTOControl_GetNowsStatusNumber(pClient);
#else
	options->PackNumber = UDP_AUTOControl_GetNextPackNumber(pClient);
#endif
	
	/* Serialize Status Command Buffer */
	if ((len = UDPAUTOCTRLSerialize_status(pClient->Sendbuf, pClient->Sendbuf_size, options)) <= 0) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* Send Status Command Buffer to AutoControl Server */
	if ((UDPStatus = pClient->SocketStack->Write(pClient->SocketStack, (char *)pClient->Sendbuf, len)) != UDP_OK) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* This will be a blocking call, wait for the AUTOCTRL_STAACK */
	if ((UDPStatus = UDP_AUTOControl_WaitforRecvAck(pClient, AUTOCTRL_STAACK, &Connect_timer_s)) == UDP_OK) {
		if (UDPAUTOCTRLDeserialize_staack(pClient->Recvbuf, pClient->Recvlen, options) != 0) {
			UDPStatus = UDP_OK;
		}
		else {
			UDPStatus = UDP_ERROR;
			goto exit;
		}
	}
	else {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_AUTOControl_Heart(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Heart_option* options)
 @Description			UDP_AUTOControl_Heart	: AutoControl发送心跳信息服务器
 @Input				pClient				: UDP客户端实例
					options				: AutoControl心跳选项
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_AUTOControl_Heart(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Heart_option* options)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	UDP_AUTOCTRL_message_Heart_option Default_options = UDP_AUTOCTRL_Packet_heartData_initializer;
	Stm32_CalculagraphTypeDef Connect_timer_s;
	int len = 0;
	
	/* set default options if none were supplied */
	if (options == NULL) {
		options = &Default_options;
	}
	
	/* Configuration Calculagraph for Connect Timer */
	Stm32_Calculagraph_CountdownSec(&Connect_timer_s, pClient->Command_Timeout_Sec);
	
	options->PackNumber = UDP_AUTOControl_GetNextPackNumber(pClient);
	
	/* Serialize Connect Command Buffer */
	if ((len = UDPAUTOCTRLSerialize_heart(pClient->Sendbuf, pClient->Sendbuf_size, options)) <= 0) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* Send Connect Command Buffer to AutoControl Server */
	if ((UDPStatus = pClient->SocketStack->Write(pClient->SocketStack, (char *)pClient->Sendbuf, len)) != UDP_OK) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* This will be a blocking call, wait for the AUTOCTRL_HEACK */
	if ((UDPStatus = UDP_AUTOControl_WaitforRecvAck(pClient, AUTOCTRL_HEACK, &Connect_timer_s)) == UDP_OK) {
		if (UDPAUTOCTRLDeserialize_heack(pClient->Recvbuf, pClient->Recvlen, options) != 0) {
			UDPStatus = UDP_OK;
		}
		else {
			UDPStatus = UDP_ERROR;
			goto exit;
		}
	}
	else {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static unsigned int UDP_SkyNet_GetNextPackNumber(UDP_ClientsTypeDef* pClient)
 @Description			UDP_SkyNet_GetNextPackNumber			: 获取下一个消息ID
 @Input				pClient							: UDP客户端实例
 @Return				PackNumber						: 消息ID
**********************************************************************************************************/
static unsigned int UDP_SkyNet_GetNextPackNumber(UDP_ClientsTypeDef* pClient)
{
	pClient->MsgIdNormal = (pClient->MsgIdNormal == UDP_MAX_MSG_ID) ? 1 : pClient->MsgIdNormal + 1;
	return pClient->MsgIdNormal;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_SkyNet_ReadPacket(UDP_ClientsTypeDef* pClient, int *msgTypes)
 @Description			UDP_SkyNet_ReadPacket		: SkyNet获取数据包数据与消息类型
 @Input				pClient					: UDP客户端实例
					msgTypes					: SkyNet消息类型
 @Return				UDP_StatusTypeDef			: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_SkyNet_ReadPacket(UDP_ClientsTypeDef* pClient, int *msgTypes)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int Rlength = 0;													//读取数据长度
	int Rleftlength = 0;												//剩余读取数据长度
	int len = 0;
	int rem_len = 0;
	
	UDP_SKYNET_messageHead* mhead = (UDP_SKYNET_messageHead*)pClient->Recvbuf;
	
	/* 1. read the header four byte. This has the packet length in it */
	UDPStatus = pClient->SocketStack->Read(pClient->SocketStack, (char *)pClient->Recvbuf, 4, &Rlength, &Rleftlength);
	if ((UDPStatus != UDP_OK) || (Rlength != 4)) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	len = Rlength;
	
	rem_len = ntohs(mhead->DataLen) + sizeof(UDP_SKYNET_messageTail);
	
	if (rem_len > (pClient->Recvbuf_size - len)) {
		UDPStatus = UDP_BUFFER_OVERFLOW;
		goto exit;
	}
	
	/* 2. read the rest of the buffer using a callback to supply the rest of the data */
	if ((rem_len <= 0) || ((UDPStatus = pClient->SocketStack->Read(pClient->SocketStack, (char *)pClient->Recvbuf + len, rem_len, &Rlength, &Rleftlength)) != UDP_OK)) {
		goto exit;
	}
	
	pClient->Recvlen = len + Rlength;
	
	*msgTypes = pClient->Recvbuf[1];
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_SkyNet_ConnackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_SkyNet_ConnackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_SkyNet_ConnackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_SkyNet_StaackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_SkyNet_StaackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_SkyNet_StaackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			static UDP_StatusTypeDef UDP_SkyNet_HeackEvent(UDP_ClientsTypeDef* pClient)
 @Description			UDP_SkyNet_HeackEvent
 @Input				pClient				: UDP客户端实例
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
static UDP_StatusTypeDef UDP_SkyNet_HeackEvent(UDP_ClientsTypeDef* pClient)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	//Todo
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_SkyNet_RecvPacketProcess(UDP_ClientsTypeDef* pClient, int *msgTypes)
 @Description			UDP_SkyNet_RecvPacketProcess		: SkyNet接收数据包处理
 @Input				pClient						: UDP客户端实例
					msgTypes						: SkyNet消息类型
 @Return				UDP_StatusTypeDef				: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_SkyNet_RecvPacketProcess(UDP_ClientsTypeDef* pClient, int *msgTypes)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int packetType = -1;
	
	UDPStatus = UDP_SkyNet_ReadPacket(pClient, &packetType);					//获取MqttSN数据并提取消息类型
	if (UDPStatus != UDP_OK) {											//没有获取到数据
		UDPStatus = UDP_RECVPACKET_NONE;
		goto exit;
	}
	
	switch (packetType)													//根据消息类型执行不同处理
	{
	case SKYNET_CONNACK:
		UDPStatus = UDP_SkyNet_ConnackEvent(pClient);
		break;
	
	case SKYNET_STAACK:
		UDPStatus = UDP_SkyNet_StaackEvent(pClient);
		break;
	
	case SKYNET_HEACK:
		UDPStatus = UDP_SkyNet_HeackEvent(pClient);
		break;
	
	default:
		UDPStatus = UDP_ERROR;
		break;
	}
	
	if (UDPStatus == UDP_OK) {
		*msgTypes = packetType;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_SkyNet_WaitforRecvAck(UDP_ClientsTypeDef* pClient, int msgType, Stm32_CalculagraphTypeDef* timerS)
 @Description			UDP_SkyNet_WaitforRecvAck		: SkyNet等待接收到相应应答消息类型
 @Input				pClient						: UDP客户端实例
					msgType						: SkyNet消息类型
					timer						: 超时计时器
 @Return				UDP_StatusTypeDef				: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_SkyNet_WaitforRecvAck(UDP_ClientsTypeDef* pClient, int msgType, Stm32_CalculagraphTypeDef* timerS)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	int packetType = -1;
	
	while (packetType != msgType) {
		if ((UDPStatus = UDP_SkyNet_RecvPacketProcess(pClient, &packetType)) == UDP_ERROR) {		//接收数据处理
			goto exit;
		}
		if (Stm32_Calculagraph_IsExpiredSec(timerS) == true) {								//到达超时时间
			break;
		}
		
		UDP_WaitforCallback(pClient);
	}
	
	if (packetType != msgType) {
		UDPStatus = UDP_CMD_TIMEOUT;
	}
	else {
		UDPStatus = UDP_OK;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_SkyNet_Connect(UDP_ClientsTypeDef* pClient, UDP_SKYNET_message_Connect_option* options)
 @Description			UDP_SkyNet_Connect		: SkyNet发送注册信息服务器
 @Input				pClient				: UDP客户端实例
					options				: SkyNet连接选项
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_SkyNet_Connect(UDP_ClientsTypeDef* pClient, UDP_SKYNET_message_Connect_option* options)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	UDP_SKYNET_message_Connect_option Default_options = UDP_SKYNET_Packet_connectData_initializer;
	Stm32_CalculagraphTypeDef Connect_timer_s;
	int len = 0;
	
	/* set default options if none were supplied */
	if (options == NULL) {
		options = &Default_options;
	}
	
	/* Configuration Calculagraph for Connect Timer */
	Stm32_Calculagraph_CountdownSec(&Connect_timer_s, pClient->Command_Timeout_Sec);
	
	options->PackNumber = UDP_SkyNet_GetNextPackNumber(pClient);
	
	/* Serialize Connect Command Buffer */
	if ((len = UDPSKYNETSerialize_connect(pClient->Sendbuf, pClient->Sendbuf_size, options)) <= 0) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* Send Connect Command Buffer to AutoControl Server */
	if ((UDPStatus = pClient->SocketStack->Write(pClient->SocketStack, (char *)pClient->Sendbuf, len)) != UDP_OK) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* This will be a blocking call, wait for the SKYNET_CONNACK */
	if ((UDPStatus = UDP_SkyNet_WaitforRecvAck(pClient, SKYNET_CONNACK, &Connect_timer_s)) == UDP_OK) {
		if (UDPSKYNETDeserialize_connack(pClient->Recvbuf, pClient->Recvlen, options) != 0) {
			UDPStatus = UDP_OK;
		}
		else {
			UDPStatus = UDP_ERROR;
			goto exit;
		}
	}
	else {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
exit:
	return UDPStatus;
}

/**********************************************************************************************************
 @Function			UDP_StatusTypeDef UDP_SkyNet_Status(UDP_ClientsTypeDef* pClient, UDP_SKYNET_message_Status_option* options)
 @Description			UDP_SkyNet_Status		: SkyNet发送状态信息服务器
 @Input				pClient				: UDP客户端实例
					options				: SkyNet状态选项
 @Return				UDP_StatusTypeDef		: UDP处理状态
**********************************************************************************************************/
UDP_StatusTypeDef UDP_SkyNet_Status(UDP_ClientsTypeDef* pClient, UDP_SKYNET_message_Status_option* options)
{
	UDP_StatusTypeDef UDPStatus = UDP_OK;
	UDP_SKYNET_message_Status_option Default_options = UDP_SKYNET_Packet_statusData_initializer;
	Stm32_CalculagraphTypeDef Connect_timer_s;
	int len = 0;
	int msgType = SKYNET_STAACK;
	
	/* set default options if none were supplied */
	if (options == NULL) {
		options = &Default_options;
	}
	
	/* Configuration Calculagraph for Connect Timer */
	Stm32_Calculagraph_CountdownSec(&Connect_timer_s, pClient->Command_Timeout_Sec);
	
	options->PackNumber = UDP_SkyNet_GetNextPackNumber(pClient);
	
	if ((options->SpotStatus == 0) || (options->SpotStatus == 1)) {
		msgType = SKYNET_STAACK;
	}
	else {
		msgType = SKYNET_HEACK;
	}
	
	/* Serialize Connect Command Buffer */
	if ((len = UDPSKYNETSerialize_status(pClient->Sendbuf, pClient->Sendbuf_size, options)) <= 0) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* Send Connect Command Buffer to AutoControl Server */
	if ((UDPStatus = pClient->SocketStack->Write(pClient->SocketStack, (char *)pClient->Sendbuf, len)) != UDP_OK) {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
	/* This will be a blocking call, wait for the SKYNET_STAACK */
	if ((UDPStatus = UDP_SkyNet_WaitforRecvAck(pClient, msgType, &Connect_timer_s)) == UDP_OK) {
		if (UDPSKYNETDeserialize_staack(pClient->Recvbuf, pClient->Recvlen, options) != 0) {
			UDPStatus = UDP_OK;
		}
		else {
			UDPStatus = UDP_ERROR;
			goto exit;
		}
	}
	else {
		UDPStatus = UDP_ERROR;
		goto exit;
	}
	
exit:
	return UDPStatus;
}

/********************************************** END OF FLEE **********************************************/
