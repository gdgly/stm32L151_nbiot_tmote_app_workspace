/**
  *********************************************************************************************************
  * @file    mqttpcpsock.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-09-21
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "mqttpcpsock.h"
#include "platform_config.h"
#include "platform_map.h"
#include "stm32l1xx_config.h"
#include "sock.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			unsigned long int MqttPCPSock_htonl(unsigned long int h)
 @Description			MqttPCPSock_htonl					: 模拟htonl函数,本机字节序转网络字节序
 @Input				host	4byte
 @Return				net	4byte
**********************************************************************************************************/
unsigned long int MqttPCPSock_htonl(unsigned long int h)
{
	return htonl(h);
}

/**********************************************************************************************************
 @Function			unsigned long int MqttPCPSock_ntohl(unsigned long int n)
 @Description			MqttPCPSock_ntohl					: 模拟ntohl函数,网络字节序转本机字节序
 @Input				net	4byte
 @Return				host	4byte
**********************************************************************************************************/
unsigned long int MqttPCPSock_ntohl(unsigned long int n)
{
	return ntohl(n);
}

/**********************************************************************************************************
 @Function			unsigned short int MqttPCPSock_htons(unsigned short int h)
 @Description			MqttPCPSock_htons					: 模拟htons函数,本机字节序转网络字节序
 @Input				host	2byte
 @Return				net	2byte
**********************************************************************************************************/
unsigned short int MqttPCPSock_htons(unsigned short int h)
{
	return htons(h);
}

/**********************************************************************************************************
 @Function			unsigned short int MqttPCPSock_ntohs(unsigned short int n)
 @Description			MqttPCPSock_ntohs					: 模拟ntohs函数,网络字节序转本机字节序
 @Input				net	2byte
 @Return				host	2byte
**********************************************************************************************************/
unsigned short int MqttPCPSock_ntohs(unsigned short int n)
{
	return ntohs(n);
}

/********************************************** END OF FLEE **********************************************/
