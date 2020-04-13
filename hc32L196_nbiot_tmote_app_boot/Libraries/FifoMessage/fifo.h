#ifndef __FIFO_H
#define   __FIFO_H

#include "sys.h"

struct data_fifo_s
{
	unsigned char *buf;
	int putP, getP, size, free;
};

void Fifo_init(struct data_fifo_s *fifo, int size, unsigned char *buf);									//初始化Fifo

int  Fifo_putPut(struct data_fifo_s *fifo, unsigned char data);											//向Fifo中写入1个字节

int  Fifo_get(struct data_fifo_s *fifo);															//从Fifo中读取1个字节

void Fifo_WriteBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len);						//向Fifo中写入数据

void Fifo_ReadBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int len);						//从Fifo中读取数据

void Fifo_ReadOnlyBuffer(struct data_fifo_s *fifo, unsigned char* buf, unsigned int offset, unsigned int len);	//从Fifo中读取数据(只读)

int  Fifo_status(struct data_fifo_s *fifo);															//Fifo已用大小

int  Fifo_free(struct data_fifo_s *fifo);															//Fifo剩余大小

#endif /* __MESSAGE_H */
