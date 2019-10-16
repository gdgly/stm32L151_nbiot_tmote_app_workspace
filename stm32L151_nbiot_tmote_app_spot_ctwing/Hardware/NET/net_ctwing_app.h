#ifndef __NET_CTWING_APP_H
#define   __NET_CTWING_APP_H

#include "sys.h"
#include "ctwingconfig.h"
#include "ctwingfunc.h"
#include "ctwingtransport.h"
#include "nbiotconfig.h"
#include "nbiotfunc.h"
#include "nbiottransport.h"
#include "net_ctwing_message_operate.h"
#include "platform_map.h"

#define CTWING_DEBUG_LOG_RF_PRINT											//定义开启RF输出DEBUG信息
#define CTWING_DEBUG_LOG_PRINTF			Radio_Trf_Debug_Printf_Level2			//定义开启RF输出DEBUG信息函数

void NET_CTWING_APP_PollExecution(CTWING_ClientsTypeDef* pClient);				//CTWing逻辑处理
void NET_CTWING_NBIOT_Event_StopMode(CTWING_ClientsTypeDef* pClient);				//停止模式
void NET_CTWING_NBIOT_Event_HardwareReboot(CTWING_ClientsTypeDef* pClient);		//硬件重启
void NET_CTWING_NBIOT_Event_ReportError(CTWING_ClientsTypeDef* pClient);			//错误码输出
void NET_CTWING_NBIOT_Event_ModuleCheck(CTWING_ClientsTypeDef* pClient);			//模块检测
void NET_CTWING_NBIOT_Event_ParameterConfig(CTWING_ClientsTypeDef* pClient);		//参数配置
void NET_CTWING_NBIOT_Event_SimICCIDCheck(CTWING_ClientsTypeDef* pClient);			//Sim卡检测
void NET_CTWING_NBIOT_Event_FullFunctionality(CTWING_ClientsTypeDef* pClient);		//完整功能
void NET_CTWING_NBIOT_Event_MinimumFunctionality(CTWING_ClientsTypeDef* pClient);	//最小功能
void NET_CTWING_NBIOT_Event_ClearStoredEARFCN(CTWING_ClientsTypeDef* pClient);		//清除小区频点
void NET_CTWING_NBIOT_Event_CDPServerCheck(CTWING_ClientsTypeDef* pClient);		//CDP服务器查询
void NET_CTWING_NBIOT_Event_CDPServerConfig(CTWING_ClientsTypeDef* pClient);		//CDP服务器配置
void NET_CTWING_NBIOT_Event_NbandModeCheck(CTWING_ClientsTypeDef* pClient);		//NBAND模式查询
void NET_CTWING_NBIOT_Event_NbandModeConfig(CTWING_ClientsTypeDef* pClient);		//NBAND模式配置
void NET_CTWING_NBIOT_Event_MiscEquipConfig(CTWING_ClientsTypeDef* pClient);		//其他配置
void NET_CTWING_NBIOT_Event_AttachCheck(CTWING_ClientsTypeDef* pClient);			//注网检查
void NET_CTWING_NBIOT_Event_AttachExecute(CTWING_ClientsTypeDef* pClient);			//注网进行
void NET_CTWING_NBIOT_Event_AttachInquire(CTWING_ClientsTypeDef* pClient);			//注网查询
void NET_CTWING_NBIOT_Event_ParameterCheckOut(CTWING_ClientsTypeDef* pClient);		//参数检出













#endif /* __NET_ONENET_APP_H */
