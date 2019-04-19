#ifndef __NET_UDP_MESSAGE_OPERATE_H
#define   __NET_UDP_MESSAGE_OPERATE_H

#include "sys.h"

#define UDP_SEND_BUFFER_SIZE				120
#define UDP_RECV_BUFFER_SIZE				120
#define UDP_SEND_PARK_NUM				5
#define UDP_RECV_PARK_NUM				5

/* 发送数据队列 */
typedef struct
{
	unsigned char						Front;
	unsigned char						Rear;
	
	struct UdpSendParkTypeDef
	{
		unsigned char					Buffer[UDP_SEND_BUFFER_SIZE];
		unsigned short					Length;
	}Park[UDP_SEND_PARK_NUM];
}UDP_SwapSendDataTypeDef;

/* 接收数据队列 */
typedef struct
{
	unsigned char						Front;
	unsigned char						Rear;
	
	struct UdpRecvParkTypeDef
	{
		unsigned char					Buffer[UDP_RECV_BUFFER_SIZE];
		unsigned short					Length;
	}Park[UDP_RECV_PARK_NUM];
}UDP_SwapRecvDataTypeDef;


void NET_UDP_FifoSendMessageInit(void);																	//发送数据Fifo初始化
void NET_UDP_FifoRecvMessageInit(void);																	//接收数据Fifo初始化
void NET_UDP_Message_SendDataEnqueue(unsigned char* dataBuf, unsigned short dataLength);							//发送数据写入队列
void NET_UDP_Message_RecvDataEnqueue(unsigned char* dataBuf, unsigned short dataLength);							//接收数据写入队列
bool NET_UDP_Message_SendDataDequeue(unsigned char* dataBuf, unsigned short* dataLength);							//发送数据读出队列
bool NET_UDP_Message_RecvDataDequeue(unsigned char* dataBuf, unsigned short* dataLength);							//接收数据读出队列
bool NET_UDP_Message_SendDataOffSet(void);																//发送数据队列(队列头偏移1)
bool NET_UDP_Message_RecvDataOffSet(void);																//接收数据队列(队列头偏移1)
unsigned char NET_UDP_Message_SendDataRear(void);															//发送数据队尾值
unsigned char NET_UDP_Message_RecvDataRear(void);															//接收数据队尾值

#endif /* __NET_UDP_MESSAGE_OPERATE_H */
