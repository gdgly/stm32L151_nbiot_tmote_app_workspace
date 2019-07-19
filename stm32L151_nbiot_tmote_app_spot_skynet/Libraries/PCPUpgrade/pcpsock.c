/**
  *********************************************************************************************************
  * @file    pcpsock.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-07-16
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "pcpsock.h"
#include "platform_config.h"
#include "platform_map.h"
#include "stm32l1xx_config.h"
#include "sock.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			unsigned long int PCPSock_htonl(unsigned long int h)
 @Description			PCPSock_htonl						: 模拟htonl函数,本机字节序转网络字节序
 @Input				host	4byte
 @Return				net	4byte
**********************************************************************************************************/
unsigned long int PCPSock_htonl(unsigned long int h)
{
	return htonl(h);
}

/**********************************************************************************************************
 @Function			unsigned long int PCPSock_ntohl(unsigned long int n)
 @Description			PCPSock_ntohl						: 模拟ntohl函数,网络字节序转本机字节序
 @Input				net	4byte
 @Return				host	4byte
**********************************************************************************************************/
unsigned long int PCPSock_ntohl(unsigned long int n)
{
	return ntohl(n);
}

/**********************************************************************************************************
 @Function			unsigned short int PCPSock_htons(unsigned short int h)
 @Description			PCPSock_htons						: 模拟htons函数,本机字节序转网络字节序
 @Input				host	2byte
 @Return				net	2byte
**********************************************************************************************************/
unsigned short int PCPSock_htons(unsigned short int h)
{
	return htons(h);
}

/**********************************************************************************************************
 @Function			unsigned short int PCPSock_ntohs(unsigned short int n)
 @Description			PCPSock_ntohs						: 模拟ntohs函数,网络字节序转本机字节序
 @Input				net	2byte
 @Return				host	2byte
**********************************************************************************************************/
unsigned short int PCPSock_ntohs(unsigned short int n)
{
	return ntohs(n);
}

/********************************************** END OF FLEE **********************************************/
