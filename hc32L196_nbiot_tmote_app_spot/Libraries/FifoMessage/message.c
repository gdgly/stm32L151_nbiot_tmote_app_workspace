/**
  *********************************************************************************************************
  * @file    message.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-13
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "message.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void messageFifoInit(message_fifo_s *pMessageFifo, unsigned char *buf, int size, unsigned char parkNum)
 @Description			messageFifoInit				: 初始化消息队列
 @Input				pMessageFifo					: FiFo队列地址
					buf							: FiFo队列数据存储地址
					size							: FiFo队列数据存储大小
					parkNum						: 消息存储最大包数
 @Return				void
**********************************************************************************************************/
void messageFifoInit(message_fifo_s *pMessageFifo, unsigned char *buf, int size, unsigned char parkNum)
{
	Fifo_init(&pMessageFifo->dataFifo, size, buf);
	
	pMessageFifo->Front = 0;
	pMessageFifo->Rear = 0;
	pMessageFifo->ParkNum = parkNum;
	pMessageFifo->ParkFree = parkNum;
}

/**********************************************************************************************************
 @Function			bool messageFifoisFull(message_fifo_s *pMessageFifo, int writtenLen)
 @Description			messageFifoisFull				: 消息队列是否已满
 @Input				pMessageFifo					: FiFo队列地址
					writtenLen					: 将要写入FiFo数据大小
 @Return				true							: 已满
					false						: 未满
**********************************************************************************************************/
bool messageFifoisFull(message_fifo_s *pMessageFifo, int writtenLen)
{
	if ((writtenLen + 2) > Fifo_free(&pMessageFifo->dataFifo)) {
		return true;
	}
	
	if (((pMessageFifo->Rear + 1) % pMessageFifo->ParkNum) == pMessageFifo->Front) {
		return true;
	}
	
	return false;
}

/**********************************************************************************************************
 @Function			bool messageFifoisEmpty(message_fifo_s *pMessageFifo)
 @Description			messageFifoisEmpty				: 消息队列是否已空
 @Input				pMessageFifo					: FiFo队列地址
 @Return				true							: 已空
					false						: 未空
**********************************************************************************************************/
bool messageFifoisEmpty(message_fifo_s *pMessageFifo)
{
	if (Fifo_status(&pMessageFifo->dataFifo) == 0) {
		return true;
	}
	
	if (pMessageFifo->Front == pMessageFifo->Rear) {
		return true;
	}
	
	return false;
}

/**********************************************************************************************************
 @Function			bool messageFifoDiscard(message_fifo_s *pMessageFifo)
 @Description			messageFifoDiscard				: 丢弃最早一包消息队列数据
 @Input				pMessageFifo					: FiFo队列地址
 @Return				true							: 丢弃成功
					false						: 丢弃失败
**********************************************************************************************************/
bool messageFifoDiscard(message_fifo_s *pMessageFifo)
{
	unsigned char lenbuf[2];
	unsigned short len = 0;
	
	if (messageFifoisEmpty(pMessageFifo) == true) {
		return false;
	}
	
	/* step1 : 读取消息数据前2字节的数据长度 */
	Fifo_ReadBuffer(&pMessageFifo->dataFifo, lenbuf, 2);
	len = lenbuf[0];
	len |= lenbuf[1] << 8;
	
	/* step2 : 丢弃队列有效消息数据 */
	while (len--) {
		Fifo_get(&pMessageFifo->dataFifo);
	}
	
	/* step3 : 数据包处理 */
	pMessageFifo->Front = (pMessageFifo->Front + 1) % pMessageFifo->ParkNum;
	pMessageFifo->ParkFree++;
	
	return true;
}

/**********************************************************************************************************
 @Function			bool messageFifoEnqueue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short len)
 @Description			messageFifoEnqueue				: 数据写入消息队列
 @Input				pMessageFifo					: FiFo队列地址
					buf							: 需写入数据地址
					len							: 需写入数据长度
 @Return				true							: 写入成功
					false						: 写入失败
**********************************************************************************************************/
bool messageFifoEnqueue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short len)
{
	unsigned char lenbuf[2];
	
	if ((len + 2) > pMessageFifo->dataFifo.size) {
		return false;
	}
	
	/* step1 : 腾出需写入数据空间 */
	while (messageFifoisFull(pMessageFifo, len) == true) {
		messageFifoDiscard(pMessageFifo);
	}
	
	/* step2 : 写入消息数据前2字节的数据长度 */
	lenbuf[0] = len & 0xFF;
	lenbuf[1] = (len >> 8) & 0xFF;
	Fifo_WriteBuffer(&pMessageFifo->dataFifo, lenbuf, 2);
	
	/* step3 : 写入队列有效消息数据 */
	Fifo_WriteBuffer(&pMessageFifo->dataFifo, buf, len);
	
	/* step4 : 数据包处理 */
	pMessageFifo->Rear = (pMessageFifo->Rear + 1) % pMessageFifo->ParkNum;
	pMessageFifo->ParkFree--;
	
	return true;
}

/**********************************************************************************************************
 @Function			bool messageFifoDequeue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short* len)
 @Description			messageFifoDequeue				: 数据读出消息队列
 @Input				pMessageFifo					: FiFo队列地址
					buf							: 需读出数据地址
					len							: 需读出数据长度地址
 @Return				true							: 读取成功
					false						: 读取失败
**********************************************************************************************************/
bool messageFifoDequeue(message_fifo_s *pMessageFifo, unsigned char* buf, unsigned short* len)
{
	unsigned char lenbuf[2];
	
	if (messageFifoisEmpty(pMessageFifo) == true) {
		return false;
	}
	
	/* step1 : 读取消息数据前2字节的数据长度 */
	Fifo_ReadOnlyBuffer(&pMessageFifo->dataFifo, lenbuf, 0, 2);
	*len = lenbuf[0];
	*len |= lenbuf[1] << 8;
	
	/* step2 : 读取队列有效消息数据 */
	Fifo_ReadOnlyBuffer(&pMessageFifo->dataFifo, buf, 2, *len);
	
	return true;
}

/**********************************************************************************************************
 @Function			unsigned char messageFifoFront(message_fifo_s *pMessageFifo)
 @Description			messageFifoFront				: 获取消息队列队头值
 @Input				pMessageFifo					: FiFo队列地址
 @Return				消息队列队头值
**********************************************************************************************************/
unsigned char messageFifoFront(message_fifo_s *pMessageFifo)
{
	return pMessageFifo->Front;
}

/**********************************************************************************************************
 @Function			unsigned char messageFifoRear(message_fifo_s *pMessageFifo)
 @Description			messageFifoRear				: 获取消息队列队尾值
 @Input				pMessageFifo					: FiFo队列地址
 @Return				消息队列队尾值
**********************************************************************************************************/
unsigned char messageFifoRear(message_fifo_s *pMessageFifo)
{
	return pMessageFifo->Rear;
}

/********************************************** END OF FLEE **********************************************/
