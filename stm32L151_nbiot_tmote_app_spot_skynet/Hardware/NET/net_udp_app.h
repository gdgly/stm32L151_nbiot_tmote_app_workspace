#ifndef __NET_UDP_APP_H
#define   __NET_UDP_APP_H

#include "sys.h"
#include "udpconfig.h"
#include "udpfunc.h"
#include "udpprotocol.h"
#include "udptransport.h"
#include "nbiotconfig.h"
#include "nbiotfunc.h"
#include "nbiottransport.h"
#include "net_udp_message_operate.h"
#include "platform_map.h"

#define UDP_DEBUG_LOG_RF_PRINT											//定义开启RF输出DEBUG信息
#define UDP_DEBUG_LOG_PRINTF				Radio_Trf_Debug_Printf_Level2			//定义开启RF输出DEBUG信息函数

void NET_UDP_APP_PollExecution(UDP_ClientsTypeDef* pClient);					//UDP逻辑处理
void NET_UDP_NBIOT_Event_StopMode(UDP_ClientsTypeDef* pClient);					//停止模式
void NET_UDP_NBIOT_Event_HardwareReboot(UDP_ClientsTypeDef* pClient);				//硬件重启
void NET_UDP_NBIOT_Event_ReportError(UDP_ClientsTypeDef* pClient);				//错误码输出
void NET_UDP_NBIOT_Event_ModuleCheck(UDP_ClientsTypeDef* pClient);				//模块检测
void NET_UDP_NBIOT_Event_ParameterConfig(UDP_ClientsTypeDef* pClient);			//参数配置
void NET_UDP_NBIOT_Event_SimICCIDCheck(UDP_ClientsTypeDef* pClient);				//Sim卡检测
void NET_UDP_NBIOT_Event_FullFunctionality(UDP_ClientsTypeDef* pClient);			//完整功能
void NET_UDP_NBIOT_Event_MinimumFunctionality(UDP_ClientsTypeDef* pClient);		//最小功能
void NET_UDP_NBIOT_Event_ClearStoredEARFCN(UDP_ClientsTypeDef* pClient);			//清除小区频点
void NET_UDP_NBIOT_Event_NbandModeCheck(UDP_ClientsTypeDef* pClient);				//NBAND模式查询
void NET_UDP_NBIOT_Event_NbandModeConfig(UDP_ClientsTypeDef* pClient);			//NBAND模式配置
void NET_UDP_NBIOT_Event_AttachCheck(UDP_ClientsTypeDef* pClient);				//注网检查
void NET_UDP_NBIOT_Event_AttachExecute(UDP_ClientsTypeDef* pClient);				//注网进行
void NET_UDP_NBIOT_Event_AttachInquire(UDP_ClientsTypeDef* pClient);				//注网查询
void NET_UDP_NBIOT_Event_ParameterCheckOut(UDP_ClientsTypeDef* pClient);			//参数检出

void NET_UDP_APP_ProcessExecution(UDP_ClientsTypeDef* pClient);					//UDP协议逻辑处理
void NET_UDP_Event_CreatUDPSocket(UDP_ClientsTypeDef* pClient);					//CreatUDPSocket
void NET_UDP_Event_ConnectServer(UDP_ClientsTypeDef* pClient);					//ConnectServer
void NET_UDP_Event_SendData(UDP_ClientsTypeDef* pClient);						//SendData
void NET_UDP_Event_Sleep(UDP_ClientsTypeDef* pClient);							//Sleep
void NET_UDP_Event_Heart(UDP_ClientsTypeDef* pClient);							//Heart

#endif /* __NET_UDP_APP_H */
