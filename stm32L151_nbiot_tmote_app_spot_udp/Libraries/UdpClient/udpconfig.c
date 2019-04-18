/**
  *********************************************************************************************************
  * @file    udpconfig.c
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

#include "udpconfig.h"
#include "udpfunc.h"
#include "udptransport.h"

unsigned char UDP_SendBuf[UDP_BUFFER_SIZE];
unsigned char UDP_RecvBuf[UDP_BUFFER_SIZE];
unsigned char UDP_DataStack[UDP_DATASTACK_SIZE];

/**********************************************************************************************************
 @Function			void UDP_Client_Init(UDP_ClientsTypeDef* pClient, UDP_SocketNetTypeDef* NetSock, NET_NBIOT_ClientsTypeDef* NetNbiotStack)
 @Description			UDP_Client_Init						: 初始化UDP客户端
 @Input				pClient								: UDP客户端实例
					NetSock								: UDP Socket 协议栈
					NetNbiotStack							: NET NBIOT 协议栈
 @Return				void
**********************************************************************************************************/
void UDP_Client_Init(UDP_ClientsTypeDef* pClient, UDP_SocketNetTypeDef* NetSock, NET_NBIOT_ClientsTypeDef* NetNbiotStack)
{
	pClient->Sendbuf									= UDP_SendBuf;
	pClient->Recvbuf									= UDP_RecvBuf;
	pClient->Sendbuf_size								= sizeof(UDP_SendBuf);
	pClient->Recvbuf_size								= sizeof(UDP_RecvBuf);
	pClient->Sendlen									= 0;
	pClient->Recvlen									= 0;
	pClient->DataProcessStack							= UDP_DataStack;
	pClient->DataProcessStack_size						= sizeof(UDP_DataStack);
	
	pClient->Command_Timeout_Sec							= UDP_COMMAND_TIMEOUT_SEC;
	pClient->Command_Failure_Cnt							= UDP_COMMAND_FAILURE_CNT;
	
	
	
	
	
	
	
	
	pClient->SocketStack								= NetSock;
	pClient->NetNbiotStack								= NetNbiotStack;
}

























/********************************************** END OF FLEE **********************************************/
