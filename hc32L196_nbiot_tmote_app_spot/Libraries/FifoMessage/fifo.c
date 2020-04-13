/**
  *********************************************************************************************************
  * @file    fifo.c
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
#include "fifo.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void Fifo_init(struct data_fifo_s *fifo, int size, unsigned char *buf)
 @Description			Fifo_init					: 初始化Fifo
 @Input				fifo						: Fifo结构体地址
					size						: Fifo内存大小
					buf						: Fifo内存地址
 @Return				void
**********************************************************************************************************/
void Fifo_init(struct data_fifo_s *fifo, int size, unsigned char *buf)
{
	fifo->buf  = buf;
	fifo->free = size;
	fifo->size = size;
	fifo->putP = 0;
	fifo->getP = 0;
	
	return;
}

/**********************************************************************************************************
 @Function			int Fifo_putPut(struct data_fifo_s *fifo, unsigned char data)
 @Description			Fifo_putPut				: 向Fifo中写入1个字节
 @Input				fifo						: Fifo结构体地址
					data						: 写入字节
 @Return				0						: 成功
					-1						: 失败
**********************************************************************************************************/
int Fifo_putPut(struct data_fifo_s *fifo, unsigned char data)
{
	if (fifo->free == 0) {
		return -1;
	}
	
	fifo->buf[fifo->putP] = data;
	fifo->putP++;
	if (fifo->putP == fifo->size) {
		fifo->putP = 0;
	}
	fifo->free--;
	
	return 0;
}

/**********************************************************************************************************
 @Function			int Fifo_get(struct data_fifo_s *fifo)
 @Description			Fifo_get					: 从Fifo中读取1个字节
 @Input				fifo						: Fifo结构体地址
 @Return				data						: 读取字节
					-1						: 失败
**********************************************************************************************************/
int Fifo_get(struct data_fifo_s *fifo)
{
	unsigned char data;
	
	if (fifo->free == fifo->size) {
		return -1;
	}
	
	data = fifo->buf[fifo->getP];
	fifo->getP++;
	if (fifo->getP == fifo->size) {
		fifo->getP = 0;
	}
	fifo->free++;
	
	return data;
}

/**********************************************************************************************************
 @Function			void Fifo_WriteBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len)
 @Description			Fifo_WriteBuffer			: 向Fifo中写入数据
 @Input				fifo						: Fifo结构体地址
					buf						: 写入数据地址
					len						: 写入数据长度
 @Return				void
**********************************************************************************************************/
void Fifo_WriteBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len)
{
	while (len--) {
		Fifo_putPut(fifo, *buf++);
	}
}

/**********************************************************************************************************
 @Function			void Fifo_ReadBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len)
 @Description			Fifo_ReadBuffer			: 从Fifo中读取数据
 @Input				fifo						: Fifo结构体地址
					buf						: 读取数据地址
					len						: 读取数据长度
 @Return				void
**********************************************************************************************************/
void Fifo_ReadBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len)
{
	while (len--) {
		*buf++ = Fifo_get(fifo);
	}
}

/**********************************************************************************************************
 @Function			void Fifo_ReadOnlyBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int offset, unsigned int len)
 @Description			Fifo_ReadOnlyBuffer			: 从Fifo中读取数据(只读)
 @Input				fifo						: Fifo结构体地址
					buf						: 读取数据地址
					offset					: 数据偏移地址
					len						: 读取数据长度
 @Return				void
**********************************************************************************************************/
void Fifo_ReadOnlyBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int offset, unsigned int len)
{
	int getP = fifo->getP;
	
	while(offset--) {
		getP++;
		if (getP == fifo->size) {
			getP = 0;
		}
	}
	
	while (len--) {
		*buf++ = fifo->buf[getP];
		getP++;
		if (getP == fifo->size) {
			getP = 0;
		}
	}
}

/**********************************************************************************************************
 @Function			int Fifo_status(struct data_fifo_s *fifo)
 @Description			Fifo_status				: Fifo已用大小
 @Input				fifo						: Fifo结构体地址
 @Return				int						: Fifo已用大小
**********************************************************************************************************/
int Fifo_status(struct data_fifo_s *fifo)
{
	return fifo->size-fifo->free;
}

/**********************************************************************************************************
 @Function			int Fifo_free(struct data_fifo_s *fifo)
 @Description			Fifo_free					: Fifo剩余大小
 @Input				fifo						: Fifo结构体地址
 @Return				int						: Fifo剩余大小
**********************************************************************************************************/
int Fifo_free(struct data_fifo_s *fifo)
{
	return fifo->free;
}

/********************************************** END OF FLEE **********************************************/
