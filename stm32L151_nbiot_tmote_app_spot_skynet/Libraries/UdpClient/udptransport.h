#ifndef __UDP_TRANSPORT_H
#define   __UDP_TRANSPORT_H

#include "sys.h"
#include "udpconfig.h"

UDP_StatusTypeDef UDP_Transport_Open(UDP_SocketNetTypeDef* NetSock);													//创建一个Socket连接
UDP_StatusTypeDef UDP_Transport_Close(UDP_SocketNetTypeDef* NetSock);													//关闭一个Socket连接
UDP_StatusTypeDef UDP_Transport_Write(UDP_SocketNetTypeDef* NetSock, const char *buf, u16 sendlen);							//发送一条负载数据
UDP_StatusTypeDef UDP_Transport_Read(UDP_SocketNetTypeDef* NetSock, char *buf, u16 maxrlen, int *rlen, int *rleft);			//读取一条负载数据

UDP_StatusTypeDef UDP_Transport_Init(UDP_SocketNetTypeDef* NetSock, NBIOT_ClientsTypeDef* NBIotStack, u16 , const char *, u16 );	//初始化

#endif /* __UDP_TRANSPORT_H */
