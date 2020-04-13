#ifndef __MESSAGE_H
#define   __MESSAGE_H

#include "sys.h"
#include "fifo.h"

typedef struct _message_typedef
{
	struct data_fifo_s			dataFifo;
	unsigned char				Front;
	unsigned char				Rear;
	unsigned char				ParkNum;
	unsigned char				ParkFree;
} message_fifo_s;

void messageFifoInit(message_fifo_s *pMessageFifo, unsigned char *buf, int size, unsigned char parkNum);			//初始化消息队列

bool messageFifoisFull(message_fifo_s *pMessageFifo, int writtenLen);										//消息队列是否已满

bool messageFifoisEmpty(message_fifo_s *pMessageFifo);													//消息队列是否已空

bool messageFifoDiscard(message_fifo_s *pMessageFifo);													//丢弃最早一包消息队列数据

bool messageFifoEnqueue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short len);					//数据写入消息队列

bool messageFifoDequeue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short* len);				//数据读出消息队列

unsigned char messageFifoFront(message_fifo_s *pMessageFifo);											//获取消息队列队头值

unsigned char messageFifoRear(message_fifo_s *pMessageFifo);											//获取消息队列队尾值

#endif /* __MESSAGE_H */
