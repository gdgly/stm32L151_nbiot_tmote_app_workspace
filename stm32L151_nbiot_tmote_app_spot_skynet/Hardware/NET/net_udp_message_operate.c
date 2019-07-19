/**
  *********************************************************************************************************
  * @file    net_udp_message_operate.c
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

#include "net_udp_message_operate.h"
#include "inspectmessageoperate.h"
#include "platform_config.h"
#include "platform_map.h"
#include "stm32l1xx_config.h"
#include "fifomessage.h"
#include "hal_rtc.h"
#include "radar_api.h"
#include "tmesh_algorithm.h"
#include "string.h"

#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
UDP_SwapSendDataTypeDef		NETUdpMessageSendPark;
UDP_SwapRecvDataTypeDef		NETUdpMessageRecvPark;
#endif

#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
#define MESSAGEUDPFIFO_SENDPARKNUM_MAX			NETFIFO_UDPSENDPARKNUM_MAX
#define MESSAGEUDPFIFO_RECVPARKNUM_MAX			NETFIFO_UDPRECVPARKNUM_MAX
#define MESSAGEUDPFIFO_SENDPARKSIZE_MAX			NETFIFO_UDPSENDPARKSIZE_MAX
#define MESSAGEUDPFIFO_RECVPARKSIZE_MAX			NETFIFO_UDPRECVPARKSIZE_MAX

MessageFifoTypeDef			NETUDPFifoMessageSendPark;
MessageFifoTypeDef			NETUDPFifoMessageRecvPark;

unsigned char				UDPFifoMessageSendBuf[MESSAGEUDPFIFO_SENDPARKSIZE_MAX];
unsigned char				UDPFifoMessageRecvBuf[MESSAGEUDPFIFO_RECVPARKSIZE_MAX];
#endif

#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
/**********************************************************************************************************
 @Function			static bool NET_UDP_Message_SendDataisFull(void)
 @Description			NET_UDP_Message_SendDataisFull	: 检查发送队列是否已满
 @Input				void
 @Return				true							: 已满
					false						: 未满
**********************************************************************************************************/
static bool NET_UDP_Message_SendDataisFull(void)
{
	bool MessageState;
	
	if ((NETUdpMessageSendPark.Rear + 1) % UDP_SEND_PARK_NUM == NETUdpMessageSendPark.Front) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			static bool NET_UDP_Message_RecvDataisFull(void)
 @Description			NET_UDP_Message_RecvDataisFull	: 检查接收队列是否已满
 @Input				void
 @Return				true							: 已满
					false						: 未满
**********************************************************************************************************/
static bool NET_UDP_Message_RecvDataisFull(void)
{
	bool MessageState;
	
	if ((NETUdpMessageRecvPark.Rear + 1) % UDP_RECV_PARK_NUM == NETUdpMessageRecvPark.Front) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			static bool NET_UDP_Message_SendDataisEmpty(void)
 @Description			NET_UDP_Message_SendDataisEmpty	: 检查发送队列是否已空
 @Input				void
 @Return				true							: 已空
					false						: 未空
**********************************************************************************************************/
static bool NET_UDP_Message_SendDataisEmpty(void)
{
	bool MessageState;
	
	if (NETUdpMessageSendPark.Front == NETUdpMessageSendPark.Rear) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			static bool NET_UDP_Message_RecvDataisEmpty(void)
 @Description			NET_UDP_Message_RecvDataisEmpty	: 检查接收队列是否已空
 @Input				void
 @Return				true							: 已空
					false						: 未空
**********************************************************************************************************/
static bool NET_UDP_Message_RecvDataisEmpty(void)
{
	bool MessageState;
	
	if (NETUdpMessageRecvPark.Front == NETUdpMessageRecvPark.Rear) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}
#endif

/**********************************************************************************************************
 @Function			void NET_UDP_FifoSendMessageInit(void)
 @Description			NET_UDP_FifoSendMessageInit		: 发送数据Fifo初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void NET_UDP_FifoSendMessageInit(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	netMessageFifoInit(&NETUDPFifoMessageSendPark, UDPFifoMessageSendBuf, sizeof(UDPFifoMessageSendBuf), MESSAGEUDPFIFO_SENDPARKNUM_MAX);
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_FifoRecvMessageInit(void)
 @Description			NET_UDP_FifoRecvMessageInit		: 接收数据Fifo初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void NET_UDP_FifoRecvMessageInit(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	netMessageFifoInit(&NETUDPFifoMessageRecvPark, UDPFifoMessageRecvBuf, sizeof(UDPFifoMessageRecvBuf), MESSAGEUDPFIFO_RECVPARKNUM_MAX);
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_Message_SendDataEnqueue(unsigned char* dataBuf, unsigned short dataLength)
 @Description			NET_UDP_Message_SendDataEnqueue	: 发送数据写入队列
 @Input				dataBuf	 		 			: 需写入数据
					dataLength					: 需写入数据长度
 @Return				void
**********************************************************************************************************/
void NET_UDP_Message_SendDataEnqueue(unsigned char* dataBuf, unsigned short dataLength)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	if ((dataBuf == NULL) || (dataLength > UDP_SEND_BUFFER_SIZE)) {
		return;
	}
	
	NETUdpMessageSendPark.Rear = (NETUdpMessageSendPark.Rear + 1) % UDP_SEND_PARK_NUM;						//队尾偏移1
	memset((u8 *)&NETUdpMessageSendPark.Park[NETUdpMessageSendPark.Rear], 0x0, sizeof(NETUdpMessageSendPark.Park[NETUdpMessageSendPark.Rear]));
	memcpy(NETUdpMessageSendPark.Park[NETUdpMessageSendPark.Rear].Buffer, dataBuf, dataLength);
	NETUdpMessageSendPark.Park[NETUdpMessageSendPark.Rear].Length = dataLength;
	
	if (NET_UDP_Message_SendDataisFull() == true) {													//队列已满
		NETUdpMessageSendPark.Front = (NETUdpMessageSendPark.Front + 1) % UDP_SEND_PARK_NUM;					//队头偏移1
	}
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	netMessageFifoEnqueue(&NETUDPFifoMessageSendPark, dataBuf, dataLength);
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_Message_RecvDataEnqueue(unsigned char* dataBuf, unsigned short dataLength)
 @Description			NET_UDP_Message_RecvDataEnqueue	: 接收数据写入队列
 @Input				dataBuf	 		 			: 需写入数据
					dataLength					: 需写入数据长度
 @Return				void
**********************************************************************************************************/
void NET_UDP_Message_RecvDataEnqueue(unsigned char* dataBuf, unsigned short dataLength)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	if ((dataBuf == NULL) || (dataLength > UDP_RECV_BUFFER_SIZE)) {
		return;
	}
	
	NETUdpMessageRecvPark.Rear = (NETUdpMessageRecvPark.Rear + 1) % UDP_RECV_PARK_NUM;						//队尾偏移1
	memset((u8 *)&NETUdpMessageRecvPark.Park[NETUdpMessageRecvPark.Rear], 0x0, sizeof(NETUdpMessageRecvPark.Park[NETUdpMessageRecvPark.Rear]));
	memcpy(NETUdpMessageRecvPark.Park[NETUdpMessageRecvPark.Rear].Buffer, dataBuf, dataLength);
	NETUdpMessageRecvPark.Park[NETUdpMessageRecvPark.Rear].Length = dataLength;
	
	if (NET_UDP_Message_RecvDataisFull() == true) {													//队列已满
		NETUdpMessageRecvPark.Front = (NETUdpMessageRecvPark.Front + 1) % UDP_RECV_PARK_NUM;					//队头偏移1
	}
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	netMessageFifoEnqueue(&NETUDPFifoMessageRecvPark, dataBuf, dataLength);
#endif
}

/**********************************************************************************************************
 @Function			bool NET_UDP_Message_SendDataDequeue(unsigned char* dataBuf, unsigned short* dataLength)
 @Description			NET_UDP_Message_SendDataDequeue	: 发送数据读出队列
 @Input				dataBuf	 		 			: 需读出数据地址
					dataLength					: 需读出数据长度地址
 @Return				true							: 未空
					false						: 已空
**********************************************************************************************************/
bool NET_UDP_Message_SendDataDequeue(unsigned char* dataBuf, unsigned short* dataLength)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	bool MessageState;
	unsigned char front;
	
	if (NET_UDP_Message_SendDataisEmpty() == true) {													//队列已空
		MessageState = false;
	}
	else {																					//队列未空
		front = (NETUdpMessageSendPark.Front + 1) % UDP_SEND_PARK_NUM;									//队头偏移1
		memcpy(dataBuf, NETUdpMessageSendPark.Park[front].Buffer, NETUdpMessageSendPark.Park[front].Length);
		*dataLength = NETUdpMessageSendPark.Park[front].Length;
		MessageState = true;
	}
	
	return MessageState;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoDequeue(&NETUDPFifoMessageSendPark, dataBuf, dataLength);
#endif
}

/**********************************************************************************************************
 @Function			bool NET_UDP_Message_RecvDataDequeue(unsigned char* dataBuf, unsigned short* dataLength)
 @Description			NET_UDP_Message_RecvDataDequeue	: 接收数据读出队列
 @Input				dataBuf	 		 			: 需读出数据地址
					dataLength					: 需读出数据长度地址
 @Return				true							: 未空
					false						: 已空
**********************************************************************************************************/
bool NET_UDP_Message_RecvDataDequeue(unsigned char* dataBuf, unsigned short* dataLength)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	bool MessageState;
	unsigned char front;
	
	if (NET_UDP_Message_RecvDataisEmpty() == true) {													//队列已空
		MessageState = false;
	}
	else {																					//队列未空
		front = (NETUdpMessageRecvPark.Front + 1) % UDP_RECV_PARK_NUM;									//队头偏移1
		memcpy(dataBuf, NETUdpMessageRecvPark.Park[front].Buffer, NETUdpMessageRecvPark.Park[front].Length);
		*dataLength = NETUdpMessageRecvPark.Park[front].Length;
		MessageState = true;
	}
	
	return MessageState;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoDequeue(&NETUDPFifoMessageRecvPark, dataBuf, dataLength);
#endif
}

/**********************************************************************************************************
 @Function			bool NET_UDP_Message_SendDataOffSet(void)
 @Description			NET_UDP_Message_SendDataOffSet	: 发送数据队列(队列头偏移1)
 @Input				void
 @Return				true							: 未空
					false						: 已空
**********************************************************************************************************/
bool NET_UDP_Message_SendDataOffSet(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	bool MessageState;
	
	if (NET_UDP_Message_SendDataisEmpty() == true) {													//队列已空
		MessageState = false;
	}
	else {																					//队列未空
		NETUdpMessageSendPark.Front = (NETUdpMessageSendPark.Front + 1) % UDP_SEND_PARK_NUM;
		MessageState = true;
	}
	
	return MessageState;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoDiscard(&NETUDPFifoMessageSendPark);
#endif
}

/**********************************************************************************************************
 @Function			bool NET_UDP_Message_RecvDataOffSet(void)
 @Description			NET_UDP_Message_RecvDataOffSet	: 接收数据队列(队列头偏移1)
 @Input				void
 @Return				true							: 未空
					false						: 已空
**********************************************************************************************************/
bool NET_UDP_Message_RecvDataOffSet(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	bool MessageState;
	
	if (NET_UDP_Message_RecvDataisEmpty() == true) {													//队列已空
		MessageState = false;
	}
	else {																					//队列未空
		NETUdpMessageRecvPark.Front = (NETUdpMessageRecvPark.Front + 1) % UDP_RECV_PARK_NUM;
		MessageState = true;
	}
	
	return MessageState;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoDiscard(&NETUDPFifoMessageRecvPark);
#endif
}

/**********************************************************************************************************
 @Function			unsigned char NET_UDP_Message_SendDataRear(void)
 @Description			NET_UDP_Message_SendDataRear		: 发送数据队尾值
 @Input				void
 @Return				发送数据队尾值
**********************************************************************************************************/
unsigned char NET_UDP_Message_SendDataRear(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	return NETUdpMessageSendPark.Rear;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoRear(&NETUDPFifoMessageSendPark);
#endif
}

/**********************************************************************************************************
 @Function			unsigned char NET_UDP_Message_RecvDataRear(void)
 @Description			NET_UDP_Message_RecvDataRear		: 接收数据队尾值
 @Input				void
 @Return				接收数据队尾值
**********************************************************************************************************/
unsigned char NET_UDP_Message_RecvDataRear(void)
{
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEDISABLE
	return NETUdpMessageRecvPark.Rear;
#endif
	
#if NETFIFOMESSAGETYPE == NETFIFOMESSAGEENABLE
	return netMessageFifoRear(&NETUDPFifoMessageRecvPark);
#endif
}

/********************************************** END OF FLEE **********************************************/
