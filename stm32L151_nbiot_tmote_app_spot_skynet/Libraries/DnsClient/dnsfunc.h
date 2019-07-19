#ifndef __DNS_FUNC_H
#define   __DNS_FUNC_H

#include "sys.h"
#include "dnsconfig.h"

unsigned char* DNS_GetHostIP(DNS_ClientsTypeDef* pClient, unsigned char* hostname);								//获取转换IP地址

DNS_StatusTypeDef DNS_Seperate(DNS_ClientsTypeDef* pClient, unsigned char* name, unsigned char* host);				//将主机名格式化为DNS查询格式

DNS_StatusTypeDef DNS_ConvertIP(DNS_ClientsTypeDef* pClient, int ip, unsigned char* hostname);						//转换并填入IP地址

DNS_StatusTypeDef DNSSerialize_dnsDataStructure(DNS_ClientsTypeDef* pClient, unsigned char* hostname);				//序列化DNS数据结构体

DNS_StatusTypeDef DNSDeserialize_dnsDataStructure(DNS_ClientsTypeDef* pClient, unsigned char* hostname);				//反序列化DNS数据结构体

#endif /* __DNS_FUNC_H */
