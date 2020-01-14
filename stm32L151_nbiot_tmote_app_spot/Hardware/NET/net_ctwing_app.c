/**
  *********************************************************************************************************
  * @file    net_ctwing_app.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-10-15
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "net_ctwing_app.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_rtc.h"
#include "hal_beep.h"
#include "radar_api.h"
#include "hal_qmc5883l.h"
#include "string.h"
#include "radio_rf_app.h"

/**********************************************************************************************************
 @Function			void NET_CTWING_APP_PollExecution(CTWING_ClientsTypeDef* pClient)
 @Description			CTWING_APP_PollExecution				: CTWing逻辑处理
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_APP_PollExecution(CTWING_ClientsTypeDef* pClient)
{
	switch (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent)
	{
	case STOP_MODE:
		NET_CTWING_NBIOT_Event_StopMode(pClient);
		break;
	
	case HARDWARE_REBOOT:
		NET_CTWING_NBIOT_Event_HardwareReboot(pClient);
		break;
	
	case REPORT_ERROE:
		NET_CTWING_NBIOT_Event_ReportError(pClient);
		break;
	
	case MODULE_CHECK:
		NET_CTWING_NBIOT_Event_ModuleCheck(pClient);
		break;
	
	case PARAMETER_CONFIG:
		NET_CTWING_NBIOT_Event_ParameterConfig(pClient);
		break;
	
	case ICCID_CHECK:
		NET_CTWING_NBIOT_Event_SimICCIDCheck(pClient);
		break;
	
	case MISC_EQUIP_CONFIG:
		NET_CTWING_NBIOT_Event_MiscEquipConfig(pClient);
		break;
	
	case ATTACH_CHECK:
		NET_CTWING_NBIOT_Event_AttachCheck(pClient);
		break;
	
	case ATTACH_EXECUTE:
		NET_CTWING_NBIOT_Event_AttachExecute(pClient);
		break;
	
	case ATTACH_INQUIRE:
		NET_CTWING_NBIOT_Event_AttachInquire(pClient);
		break;
	
	case PARAMETER_CHECKOUT:
		NET_CTWING_NBIOT_Event_ParameterCheckOut(pClient);
		break;
	
	case MINIMUM_FUNCTIONALITY:
		NET_CTWING_NBIOT_Event_MinimumFunctionality(pClient);
		break;
	
	case FULL_FUNCTIONALITY:
		NET_CTWING_NBIOT_Event_FullFunctionality(pClient);
		break;
	
	case CLEAR_STORED_EARFCN:
#if NBIOT_CLEAR_STORED_EARFCN_STAT
		NET_CTWING_NBIOT_Event_ClearStoredEARFCN(pClient);
#else
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
#endif
		break;
	
	case CDP_SERVER_CHECK:
		NET_CTWING_NBIOT_Event_CDPServerCheck(pClient);
		break;
	
	case CDP_SERVER_CONFIG:
		NET_CTWING_NBIOT_Event_CDPServerConfig(pClient);
		break;
	
	case NBAND_MODE_CHECK:
		NET_CTWING_NBIOT_Event_NbandModeCheck(pClient);
		break;
	
	case NBAND_MODE_CONFIG:
		NET_CTWING_NBIOT_Event_NbandModeConfig(pClient);
		break;
	
	case SEND_DATA:
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_NORMAL_MODE
		NET_CTWING_NBIOT_Event_SendData(pClient);
#endif
		break;
	
	case RECV_DATA:
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_NORMAL_MODE
		NET_CTWING_NBIOT_Event_RecvData(pClient);
#endif
		break;
	
	case SEND_DATA_RA_NORMAL:
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_RAIDLE_MODE
		NET_CTWING_NBIOT_Event_SendDataRANormal(pClient);
#endif
		break;
	
	case RECV_DATA_RA_NORMAL:
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_RAIDLE_MODE
		NET_CTWING_NBIOT_Event_RecvDataRANormal(pClient);
#endif
		break;
	
	case EXECUT_DOWNLINK_DATA:
		NET_CTWING_NBIOT_Event_ExecutDownlinkData(pClient);
		break;
	
	case MQTTSN_PROCESS_STACK:
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case DNS_PROCESS_STACK:
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case ONENET_PROCESS_STACK:
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case LISTEN_RUN_CTL:
		NET_CTWING_Listen_PollExecution(pClient);
		break;
	
	default :
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	}
}

/**********************************************************************************************************
 @Function			static void CTWING_NBIOT_DictateEvent_SetTime(CTWING_ClientsTypeDef* pClient, unsigned int TimeoutSec)
 @Description			CTWING_NBIOT_DictateEvent_SetTime		: 事件运行控制器注入时间(内部使用)
 @Input				pClient							: CTWing客户端实例
					TimeoutSec						: 注入超时时间
 @Return				void
 @attention			事件运行之前判断是否需要注入时间
**********************************************************************************************************/
static void CTWING_NBIOT_DictateEvent_SetTime(CTWING_ClientsTypeDef* pClient, unsigned int TimeoutSec)
{
	Stm32_CalculagraphTypeDef dictateRunTime;
	
	/* It is the first time to execute */
	if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable != true) {
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = true;
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateTimeoutSec = TimeoutSec;
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateTimeoutSec);
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime = dictateRunTime;
	}
}

static unsigned char* CTWING_NBIOT_GetDictateFailureCnt(CTWING_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	switch (dictateNoTimeOut)
	{
	case HARDWARE_REBOOT:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRebootFailureCnt;
		break;
	
	case REPORT_ERROE:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateReportErrorFailureCnt;
		break;
	
	case MODULE_CHECK:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateModuleCheckFailureCnt;
		break;
	
	case PARAMETER_CONFIG:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateParameterConfigFailureCnt;
		break;
	
	case ICCID_CHECK:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSimICCIDCheckFailureCnt;
		break;
	
	case FULL_FUNCTIONALITY:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateFullFunctionalityFailureCnt;
		break;
	
	case MINIMUM_FUNCTIONALITY:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateMinimumFunctionalityFailureCnt;
		break;
	
	case CLEAR_STORED_EARFCN:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateClearStoredEARFCNFailureCnt;
		break;
	
	case CDP_SERVER_CHECK:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateCDPServerCheckFailureCnt;
		break;
	
	case CDP_SERVER_CONFIG:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateCDPServerConfigFailureCnt;
		break;
	
	case NBAND_MODE_CHECK:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateNbandModeCheckFailureCnt;
		break;
	
	case NBAND_MODE_CONFIG:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateNbandModeConfigFailureCnt;
		break;
	
	case MISC_EQUIP_CONFIG:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateMiscEquipConfigFailureCnt;
		break;
	
	case ATTACH_CHECK:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateAttachCheckFailureCnt;
		break;
	
	case ATTACH_EXECUTE:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateAttachExecuteFailureCnt;
		break;
	
	case ATTACH_INQUIRE:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateAttachInquireFailureCnt;
		break;
	
	case PARAMETER_CHECKOUT:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictatePatameterCheckOutFailureCnt;
		break;
	
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_NORMAL_MODE
	case SEND_DATA:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataFailureCnt;
		break;
	
	case RECV_DATA:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt;
		break;
#endif
	
#if CTWING_SENDMODE_CONFIG_TYPE == CTWING_SENDMODE_RAIDLE_MODE
	case SEND_DATA_RA_NORMAL:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataRANormalFailureCnt;
		break;
	
	case RECV_DATA_RA_NORMAL:
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt;
		break;
#endif
	
	default :
		dictateFailureCnt = &pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRebootFailureCnt;
		break;
	}
	
	return dictateFailureCnt;
}

/**********************************************************************************************************
 @Function			static void CTWING_NBIOT_DictateEvent_FailExecute(CTWING_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
																					  NBIOT_DictateEventTypeDef dictateFail, \
																					  NBIOT_DictateEventTypeDef dictateNoTimeOut)
 @Description			CTWING_NBIOT_DictateEvent_FailExecute	: 事件运行控制器出错执行(内部使用)
 @Input				pClient							: CTWing客户端实例
					dictateTimeOut						: 事假处理错误超时
					dictateFail						: 事件处理错误次数溢出
					dictateNoTimeOut					: 事假处理错误未超时
 @Return				void
**********************************************************************************************************/
static void CTWING_NBIOT_DictateEvent_FailExecute(CTWING_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
																  NBIOT_DictateEventTypeDef dictateFail, \
																  NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	dictateFailureCnt = CTWING_NBIOT_GetDictateFailureCnt(pClient, dictateNoTimeOut);
	
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
		/* Dictate TimeOut */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = dictateTimeOut;
		*dictateFailureCnt += 1;
		if (*dictateFailureCnt > 3) {
			*dictateFailureCnt = 0;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = dictateFail;
		}
	}
	else {
		/* Dictate isn't TimeOut */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = dictateNoTimeOut;
	}
}

/**********************************************************************************************************
 @Function			static void CTWING_NBIOT_DictateEvent_SuccessExecute(CTWING_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
																						NBIOT_DictateEventTypeDef dictateNoTimeOut)
 @Description			CTWING_NBIOT_DictateEvent_SuccessExecute: 事件运行控制器正确执行(内部使用)
 @Input				pClient							: CTWing客户端实例
					dictateSuccess						: 事假处理正确
					dictateNoTimeOut					: 事假处理错误未超时
 @Return				void
**********************************************************************************************************/
static void CTWING_NBIOT_DictateEvent_SuccessExecute(CTWING_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
																	NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	dictateFailureCnt = CTWING_NBIOT_GetDictateFailureCnt(pClient, dictateNoTimeOut);
	
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = dictateSuccess;
	*dictateFailureCnt = 0;
}

/**********************************************************************************************************
 @Function			static void CTWING_NBIOT_GetConnectTime(CTWING_ClientsTypeDef* pClient, bool startIdleTime)
 @Description			CTWING_NBIOT_GetConnectTime			: 获取NBConnect状态时间(内部使用)
 @Input				pClient							: CTWing客户端实例
					startIdleTime						: 是否开启Idle状态计时器
 @Return				void
**********************************************************************************************************/
static void CTWING_NBIOT_GetConnectTime(CTWING_ClientsTypeDef* pClient, bool startIdleTime)
{
	unsigned int uICoapConnectTime = 0;
	
	/* Get ConnectTime */
	uICoapConnectTime = Stm32_EventRunningTime_EndMS(&pClient->LWM2MStack->NBIotStack->ConnectTimeMS) / 1000;
	/* End ConnectTime */
	TCFG_SystemData.CoapConnectTime = pClient->LWM2MStack->NBIotStack->CoapConnectTimeSec + uICoapConnectTime;
	pClient->LWM2MStack->NBIotStack->CoapConnectTimeSec = TCFG_SystemData.CoapConnectTime;
	/* Start or End IdleTime */
	if (startIdleTime != false) {
		Stm32_EventRunningTime_StartMS(&pClient->LWM2MStack->NBIotStack->IdleTimeMS);
	}
	else {
		Stm32_EventRunningTime_EndMS(&pClient->LWM2MStack->NBIotStack->IdleTimeMS);
	}
}

/**********************************************************************************************************
 @Function			static void CTWING_NBIOT_GetIdleTime(CTWING_ClientsTypeDef* pClient, bool startConnectTime)
 @Description			CTWING_NBIOT_GetIdleTime				: 获取NBIdle状态时间(内部使用)
 @Input				pClient							: CTWing客户端实例
					startConnectTime					: 是否开启Connect状态计时器
 @Return				void
**********************************************************************************************************/
static void CTWING_NBIOT_GetIdleTime(CTWING_ClientsTypeDef* pClient, bool startConnectTime)
{
	unsigned int uICoapIdleTime = 0;
	
	/* Get IdleTime */
	uICoapIdleTime = Stm32_EventRunningTime_EndMS(&pClient->LWM2MStack->NBIotStack->IdleTimeMS) / 1000;
	/* End IdleTime */
	TCFG_SystemData.CoapIdleTime = pClient->LWM2MStack->NBIotStack->CoapIdleTimeSec + uICoapIdleTime;
	pClient->LWM2MStack->NBIotStack->CoapIdleTimeSec = TCFG_SystemData.CoapIdleTime;
	/* Start or End ConnectTime */
	if (startConnectTime != false) {
		Stm32_EventRunningTime_StartMS(&pClient->LWM2MStack->NBIotStack->ConnectTimeMS);
	}
	else {
		Stm32_EventRunningTime_EndMS(&pClient->LWM2MStack->NBIotStack->ConnectTimeMS);
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_StopMode(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_StopMode		: 停止模式
 @Input				pClient							: CTWing客户端实例
 @Return				void
 @attention			当30分钟或有数据需要发送时退出停止模式尝试重启NB,开启NB运行
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_StopMode(CTWING_ClientsTypeDef* pClient)
{
	Stm32_CalculagraphTypeDef dictateRunTime;
	static unsigned char CTWingSendMessageIndex;
	
	/* It is the first time to execute */
	if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable != true) {
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = true;
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateTimeoutSec = 1800;
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateTimeoutSec);
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime = dictateRunTime;
		/* NBIOT Module Poweroff */
		NBIOT_Neul_NBxx_HardwarePoweroff(pClient->LWM2MStack->NBIotStack);
		/* Clear Stored EARFCN */
		pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_TRUE;
		/* Init Message Index */
		CTWingSendMessageIndex = NET_CTWing_Message_SendDataRear();
		
		/* Get ConnectTime & IdleTime */
		CTWING_NBIOT_GetConnectTime(pClient, false);
		CTWING_NBIOT_GetIdleTime(pClient, false);
	}
	
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
		/* Dictate TimeOut */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
	}
	else {
		/* Dictate isn't TimeOut */
		if (NET_CTWing_Message_SendDataRear() != CTWingSendMessageIndex) {
			/* Have new ctwing message need to Send */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		}
		else {
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_HardwareReboot(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_HardwareReboot	: 硬件重启
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_HardwareReboot(CTWING_ClientsTypeDef* pClient)
{
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (NBIOT_Neul_NBxx_HardwareReboot(pClient->LWM2MStack->NBIotStack, 8000) == NBIOT_OK) {
		/* Dictate execute is Success */
#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, REPORT_ERROE, HARDWARE_REBOOT);
#else
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, MODULE_CHECK, HARDWARE_REBOOT);
#endif
		/* Get IdleTime */
		CTWING_NBIOT_GetIdleTime(pClient, true);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB HDRBT Ok, Baud:%d", NBIOTBaudRate.Baud);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, HARDWARE_REBOOT);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB HDRBT Fail");
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ReportError(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ReportError		: 错误码输出
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ReportError(CTWING_ClientsTypeDef* pClient)
{
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (NBIOT_Neul_NBxx_SetReportTerminationError(pClient->LWM2MStack->NBIotStack, CMEEnable) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, MODULE_CHECK, REPORT_ERROE);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB ReportECde Set %d Ok", CMEEnable);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, REPORT_ERROE);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB ReportECde Set %d Fail", CMEEnable);
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ModuleCheck(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ModuleCheck		: 模块检测
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ModuleCheck(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (((NBStatus = NBIOT_Neul_NBxx_CheckReadManufacturer(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadManufacturerModel(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) &&
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadModuleVersion(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK)) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, PARAMETER_CONFIG, MODULE_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB Module Check Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MODULE_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("NB Module Check Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("NB Module Check Fail");
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ParameterConfig(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ParameterConfig	: 参数配置
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ParameterConfig(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadConfigUE(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB Para Config Read Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("NB Para Config Read Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("NB Para Config Read Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.autoConnect != AutoConnectVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, AutoConnect, AutoConnectVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", AutoConnect, AutoConnectVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", AutoConnect, AutoConnectVal);
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.crScrambling != CrScramblingVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, CrScrambling, CrScramblingVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", CrScrambling, CrScramblingVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", CrScrambling, CrScramblingVal);
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.crSiAvoid != CrSiAvoidVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, CrSiAvoid, CrSiAvoidVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", CrSiAvoid, CrSiAvoidVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", CrSiAvoid, CrSiAvoidVal);
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.combineAttach != CombineAttachVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, CombineAttach, CombineAttachVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", CombineAttach, CombineAttachVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", CombineAttach, CombineAttachVal);
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.cellReselection != CellReselectionVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, CellReselection, CellReselectionVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", CellReselection, CellReselectionVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", CellReselection, CellReselectionVal);
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nconfig.enableBip != EnableBipVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->LWM2MStack->NBIotStack, EnableBip, EnableBipVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Ok", EnableBip, EnableBipVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("NB %s %d Fail", EnableBip, EnableBipVal);
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_SimICCIDCheck(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_SimICCIDCheck	: Sim卡检测
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_SimICCIDCheck(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadICCID(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, ICCID_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB ICCID Check Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ICCID_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("NB ICCID Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("NB ICCID Fail");
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_FullFunctionality(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_FullFunctionality: 完整功能
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_FullFunctionality(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadMinOrFullFunc(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
#if NBIOT_CLEAR_STORED_EARFCN_STAT
		if (pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
			/* 需清除频点 */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, MINIMUM_FUNCTIONALITY, FULL_FUNCTIONALITY);
		}
		else {
			/* 无需清除频点 */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CHECK, FULL_FUNCTIONALITY);
		}
#else
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CHECK, FULL_FUNCTIONALITY);
#endif
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, FULL_FUNCTIONALITY);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.functionality != FullFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetMinOrFullFunc(pClient->LWM2MStack->NBIotStack, FullFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
#if NBIOT_CLEAR_STORED_EARFCN_STAT
			if (pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
				/* 需清除频点 */
				CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, MINIMUM_FUNCTIONALITY, FULL_FUNCTIONALITY);
			}
			else {
				/* 无需清除频点 */
				CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CHECK, FULL_FUNCTIONALITY);
			}
#else
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CHECK, FULL_FUNCTIONALITY);
#endif
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Set Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, FULL_FUNCTIONALITY);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Set Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing FullFunc Set Fail");
		#endif
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_MinimumFunctionality(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_MinimumFunctionality	: 最小功能
 @Input				pClient								: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_MinimumFunctionality(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadMinOrFullFunc(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
#if NBIOT_CLEAR_STORED_EARFCN_STAT
		if (pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
			/* 需清除频点 */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CLEAR_STORED_EARFCN, MINIMUM_FUNCTIONALITY);
		}
		else {
			/* 无需清除频点 */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CONFIG, MINIMUM_FUNCTIONALITY);
		}
#else
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CONFIG, MINIMUM_FUNCTIONALITY);
#endif
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MINIMUM_FUNCTIONALITY);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.functionality != MinFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetMinOrFullFunc(pClient->LWM2MStack->NBIotStack, MinFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
#if NBIOT_CLEAR_STORED_EARFCN_STAT
			if (pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
				/* 需清除频点 */
				CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CLEAR_STORED_EARFCN, MINIMUM_FUNCTIONALITY);
			}
			else {
				/* 无需清除频点 */
				CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CONFIG, MINIMUM_FUNCTIONALITY);
			}
#else
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CONFIG, MINIMUM_FUNCTIONALITY);
#endif
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Set Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MINIMUM_FUNCTIONALITY);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Set Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing MinFunc Set Fail");
		#endif
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ClearStoredEARFCN(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ClearStoredEARFCN: 清除小区频点
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ClearStoredEARFCN(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_ClearStoredEarfcn(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_FALSE;
		
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, CLEAR_STORED_EARFCN);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("NB Clear Stored EARFCN OK");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, CLEAR_STORED_EARFCN);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("NB Clear EARFCN Fail Ecde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("NB Clear EARFCN Fail");
	#endif
#endif
		return;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_CDPServerCheck(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_CDPServerCheck	: CDP服务器查询
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_CDPServerCheck(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadCDPServer(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CDP_SERVER_CHECK, CDP_SERVER_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP %s:%d Ok", pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerHost, pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerPort);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, CDP_SERVER_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP Fail");
	#endif
#endif
	}
	
	if ((strcmp((const char*)pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerHost, TCFG_EEPROM_Get_CTWingIP_String()) != 0) || (pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerPort != TCFG_EEPROM_GetCTWingPort())) {
		/* CDP Server Mast be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = MINIMUM_FUNCTIONALITY;
	}
	else {
		/* CDP Server Needn't be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = NBAND_MODE_CHECK;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_CDPServerConfig(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_CDPServerConfig	: CDP服务器配置
 @Input				pClient							: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_CDPServerConfig(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadCDPServer(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CONFIG, CDP_SERVER_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP %s:%d Ok", pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerHost, pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerPort);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, CDP_SERVER_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing CDP Fail");
	#endif
#endif
	}
	
	if ((strcmp((const char*)pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerHost, TCFG_EEPROM_Get_CTWingIP_String()) != 0) || (pClient->LWM2MStack->NBIotStack->Parameter.cdpserver.CDPServerPort != TCFG_EEPROM_GetCTWingPort())) {
		/* CDP Server Mast be Config */
		if ((NBStatus = NBIOT_Neul_NBxx_SetCDPServer(pClient->LWM2MStack->NBIotStack, TCFG_EEPROM_Get_CTWingIP_String(), TCFG_EEPROM_GetCTWingPort())) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CONFIG, CDP_SERVER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing CDP Set %s:%d Ok", TCFG_EEPROM_Get_CTWingIP_String(), TCFG_EEPROM_GetCTWingPort());
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, CDP_SERVER_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing CDP Set %s:%d Fail ECde %d", TCFG_EEPROM_Get_CTWingIP_String(), TCFG_EEPROM_GetCTWingPort(), NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing CDP Set %s:%d Fail", TCFG_EEPROM_Get_CTWingIP_String(), TCFG_EEPROM_GetCTWingPort());
		#endif
#endif
			return;
		}
	}
	else {
		/* CDP Server Needn't be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = NBAND_MODE_CONFIG;
	}
}

static bool NET_CTWING_CheckNband(CTWING_ClientsTypeDef* pClient, NBIOT_NBandTypeDef nbandsrc, NBIOT_NBandTypeDef nbanddst)
{
	if (nbandsrc.NBandNum != nbanddst.NBandNum) {
		return false;
	}
	
	for (int index = 0; index < nbanddst.NBandNum; index++) {
		if (nbandsrc.NBandVal[index] != nbanddst.NBandVal[index]) {
			return false;
		}
	}
	
	return true;
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_NbandModeCheck(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_NbandModeCheck	: NBAND模式查询
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_NbandModeCheck(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadSupportedBands(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CHECK, NBAND_MODE_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND %d:%d.%d.%d Ok", pClient->LWM2MStack->NBIotStack->Parameter.band.NBandNum, \
												    pClient->LWM2MStack->NBIotStack->Parameter.band.NBandVal[0], \
												    pClient->LWM2MStack->NBIotStack->Parameter.band.NBandVal[1], \
												    pClient->LWM2MStack->NBIotStack->Parameter.band.NBandVal[2]);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND Fail");
	#endif
#endif
	}
	
	if (NET_CTWING_CheckNband(pClient, pClient->LWM2MStack->NBIotStack->Parameter.band, CTWING_NBIOT_BAND_TYPE) != true) {
		/* BAND Mode Mast be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = MINIMUM_FUNCTIONALITY;
	}
	else {
		/* BAND Mode Needn't be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = MISC_EQUIP_CONFIG;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_NbandModeConfig(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_NbandModeConfig	: NBAND模式配置
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_NbandModeConfig(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadSupportedBands(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, NBAND_MODE_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND Read Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing BAND Fail");
	#endif
#endif
	}
	
	if (NET_CTWING_CheckNband(pClient, pClient->LWM2MStack->NBIotStack->Parameter.band, CTWING_NBIOT_BAND_TYPE) != true) {
		/* BAND Mode Mast be Config */
		if ((NBStatus = NBIOT_Neul_NBxx_SetSupportedBands(pClient->LWM2MStack->NBIotStack, CTWING_NBIOT_BAND_TYPE)) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, NBAND_MODE_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing BAND Set %d:%d.%d.%d Ok", CTWING_NBIOT_BAND_TYPE.NBandNum, \
														   CTWING_NBIOT_BAND_TYPE.NBandVal[0], \
														   CTWING_NBIOT_BAND_TYPE.NBandVal[1], \
														   CTWING_NBIOT_BAND_TYPE.NBandVal[2]);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing BAND Set Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing BAND Set Fail");
		#endif
#endif
			return;
		}
	}
	else {
		/* BAND Mode Needn't be Config */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = FULL_FUNCTIONALITY;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_MiscEquipConfig(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_MiscEquipConfig	: 其他配置
 @Input				pClient							: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_MiscEquipConfig(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (((NBStatus = NBIOT_Neul_NBxx_CheckReadNewMessageIndications(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) &&
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadSentMessageIndications(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) &&
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadLWM2MLifetime(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK)) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, MISC_EQUIP_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing Misc Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MISC_EQUIP_CONFIG);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing Misc Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing Misc Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nnmistate != CloseFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetNewMessageIndications(pClient->LWM2MStack->NBIotStack, CloseFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing NNMI %d Ok", CloseFunc);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing NNMI %d Fail ECde %d", CloseFunc, NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing NNMI %d Fail", CloseFunc);
		#endif
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.nsmistate != CloseFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetSentMessageIndications(pClient->LWM2MStack->NBIotStack, CloseFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing NSMI %d Ok", CloseFunc);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing NSMI %d Fail ECde %d", CloseFunc, NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing NSMI %d Fail", CloseFunc);
		#endif
#endif
			return;
		}
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.lwm2mlifetime != CTWING_LWM2M_LIFETIME) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetLWM2MLifetime(pClient->LWM2MStack->NBIotStack, CTWING_LWM2M_LIFETIME)) == NBIOT_OK) {
			/* Dictate execute is Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing LifeTime %d Ok", CTWING_LWM2M_LIFETIME);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MISC_EQUIP_CONFIG);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing LifeTime %d Fail ECde %d", CTWING_LWM2M_LIFETIME, NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing LifeTime %d Fail", CTWING_LWM2M_LIFETIME);
		#endif
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_AttachCheck(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_AttachCheck		: 注网检查
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_AttachCheck(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, ATTACH_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Ok", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_CHECK);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail ECde %d", pClient->LWM2MStack->NBIotStack->Parameter.netstate, NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.netstate != Attach) {
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_EXECUTE;
	}
	else {
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_INQUIRE;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_AttachExecute(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_AttachExecute	: 注网进行
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_AttachExecute(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_SetAttachOrDetach(pClient->LWM2MStack->NBIotStack, Attach)) == NBIOT_OK) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_INQUIRE, ATTACH_EXECUTE);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing Set CGATT %d Ok", Attach);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_EXECUTE);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing Set CGATT %d Fail ECde %d", Attach, NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing Set CGATT %d Fail", Attach);
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_AttachInquire(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_AttachInquire	: 注网查询
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_AttachInquire(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, CTWING_NBIOT_CGATT_TIME_S);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_INQUIRE;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Ok", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_INQUIRE);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail ECde %d", pClient->LWM2MStack->NBIotStack->Parameter.netstate, NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
	#endif
#endif
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.netstate != Attach) {
		/* 未注网 */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_INQUIRE);
		
		/* 开启频点清除 */
		pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_TRUE;
	}
	else {
		/* 注网成功 */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, PARAMETER_CHECKOUT, ATTACH_INQUIRE);
		
		/* 关闭频点清除 */
		pClient->LWM2MStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_FALSE;
		
		/* Get ConnectTime */
		CTWING_NBIOT_GetConnectTime(pClient, true);
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ParameterCheckOut(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ParameterCheckOut: 参数检出
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ParameterCheckOut(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
#if NBIOT_STATION_TIMESTAMP_TYPE
	unsigned int devicetimestamp = 0;
	unsigned int stationtimestamp = 0;
#endif
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (((NBStatus = NBIOT_Neul_NBxx_CheckReadIMEI(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadIMSI(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadCGPADDR(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	#if NBIOT_MODULE_MODE_TYPE == NBIOT_MODULE_MODE_V120
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadCGDCONT(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	#endif
	#if NBIOT_MODULE_MODE_TYPE == NBIOT_MODULE_MODE_V150
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadPDPContext(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	#endif
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadRSSI(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadStatisticsRADIO(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadStatisticsCELL(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadAreaCode(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadDateTime(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK)) {
		/* Dictate execute is Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, CTWING_SENDMODE_TYPE, PARAMETER_CHECKOUT);
		
		/* 标记注网成功 */
		pClient->LWM2MStack->NBIotStack->Registered = true;
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing Para Check Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CHECKOUT);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		CTWING_DEBUG_LOG_PRINTF("CTWing Para Check Fail ECde %d", NBStatus);
	#else
		CTWING_DEBUG_LOG_PRINTF("CTWing Para Check Fail");
	#endif
#endif
		return;
	}
	
#if NBIOT_STATION_TIMESTAMP_TYPE
	devicetimestamp = RTC_GetUnixTimeToStamp() + (8 * 60 * 60);
	stationtimestamp = RTC_TimeToStamp(pClient->LWM2MStack->NBIotStack->Parameter.dataTime.year, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.month, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.day, \
								pClient->LWM2MStack->NBIotStack->Parameter.dataTime.hour, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.min,   pClient->LWM2MStack->NBIotStack->Parameter.dataTime.sec);
	
	if ((((stationtimestamp >= devicetimestamp) ? (stationtimestamp - devicetimestamp) : (devicetimestamp - stationtimestamp)) > (NBIOT_STATION_TIMESTAMP_DIFFTIME)) && (pClient->LWM2MStack->NBIotStack->Parameter.dataTime.errcount < NBIOT_STATION_TIMESTAMP_ERRCOUNT) && (BackUp != true)) {
		pClient->LWM2MStack->NBIotStack->Parameter.dataTime.errcount++;
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, HARDWARE_REBOOT, PARAMETER_CHECKOUT);
		return;
	}
	
	pClient->LWM2MStack->NBIotStack->Parameter.dataTime.errcount = 0;
#endif
	
	/* Set System Time */
	RTC_Set_Date(pClient->LWM2MStack->NBIotStack->Parameter.dataTime.year, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.month, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.day);
	RTC_Set_Time(pClient->LWM2MStack->NBIotStack->Parameter.dataTime.hour, pClient->LWM2MStack->NBIotStack->Parameter.dataTime.min,   pClient->LWM2MStack->NBIotStack->Parameter.dataTime.sec);
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_SendData(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_SendData		: 发送数据
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_SendData(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
#if !CTWING_AEPMODULE_MODE
	NBIOT_ByteStreamUploadHead CTWingUpHead;
#endif
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
	int SendSentNum = 0;
#endif
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	/* Data packets need to be sent*/
	if (NET_CTWing_Message_SendDataDequeue(pClient->LWM2MStack->NBIotStack->Sendbuf, (unsigned short *)&pClient->LWM2MStack->NBIotStack->Sendlen) == true) {
		/* Get IdleTime */
		CTWING_NBIOT_GetIdleTime(pClient, true);
		
#if CTWING_SEND_BEFORE_ATTACH_TYPE
		/* Connect Check */
		if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Ok", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail ECde %d", pClient->LWM2MStack->NBIotStack->Parameter.netstate, NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
		#endif
#endif
			return;
		}
		
		if (pClient->LWM2MStack->NBIotStack->Parameter.netstate != Attach) {
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			return;
		}
#endif
		
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
		if (((NBStatus = NBIOT_Neul_NBxx_QuerySendMessageCOAPPayload(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
		    ((NBStatus = NBIOT_Neul_NBxx_QueryReadMessageCOAPPayload(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK)) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Fail");
		#endif
#endif
			return;
		}
		
		SendSentNum = pClient->LWM2MStack->NBIotStack->Parameter.coapSendMessage.sent;
#endif
		
#if !CTWING_AEPMODULE_MODE
		CTWingUpHead.CMDType		= CTWING_BYTESTREAM_UPLOAD_CMDTYPE;
		CTWingUpHead.DatasetID		= CTWING_BYTESTREAM_UPLOAD_DATASETID;
		CTWingUpHead.StreamLen		= pClient->LWM2MStack->NBIotStack->Sendlen + sizeof(CTWingUpHead.PayloadLen);
		CTWingUpHead.PayloadLen		= pClient->LWM2MStack->NBIotStack->Sendlen;
		
		/* 发送负载数据 */
		if ((NBStatus = NBIOT_Neul_NBxx_SendCTWINGPayload(pClient->LWM2MStack->NBIotStack, &CTWingUpHead)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail");
		#endif
#endif
			return;
		}
#endif
		
#if CTWING_AEPMODULE_MODE
		/* 发送负载数据 */
		if ((NBStatus = NBIOT_Neul_NBxx_SendCOAPPayload(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail");
		#endif
#endif
			return;
		}
#endif
		
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
		if (NBIOT_Neul_NBxx_QuerySendMessageCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA;
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA);
			return;
		}
		
		if ((SendSentNum + 1) != pClient->LWM2MStack->NBIotStack->Parameter.coapSendMessage.sent) {
			/* Send Data Fail */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataFailureCnt++;
			if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataFailureCnt > 3) {
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataFailureCnt = 0;
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			}
		}
		else {
			/* Send Data Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, RECV_DATA, SEND_DATA);
		}
#else
		/* Send Data Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, RECV_DATA, SEND_DATA);
#endif
	}
	/* No packets need to be sent */
	else {
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, EXECUT_DOWNLINK_DATA, SEND_DATA);
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_RecvData(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_RecvData		: 接收数据
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_RecvData(CTWING_ClientsTypeDef* pClient)
{
	u8 CTWINGFeedBackData[] = {0xAA, 0xBB};									//CTWING反馈包数据
	bool CTWINGFeedBackFlag = false;										//CTWING反馈包接收标志位
#if !CTWING_AEPMODULE_MODE
	NBIOT_ByteStreamDnloadHead CTWingDnHead;
#endif
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 60);
	
	if (NBIOT_Neul_NBxx_QueryReadMessageCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = RECV_DATA;
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, RECV_DATA);
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.coapReadMessage.buffered != 0) {
		/* Has Data Need Receive */
		for (int index = 0; index < pClient->LWM2MStack->NBIotStack->Parameter.coapReadMessage.buffered; index++) {
			
#if !CTWING_AEPMODULE_MODE
			/* 读取负载数据 */
			if (NBIOT_Neul_NBxx_ReadCTWINGPayload(pClient->LWM2MStack->NBIotStack, &CTWingDnHead) == NBIOT_OK) {
				/* Dictate execute is Success */
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
			}
			else {
				/* Dictate execute is Fail */
				if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
					/* Dictate TimeOut */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt++;
					if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt > 3) {
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt = 0;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
					}
				}
				else {
					/* Dictate isn't TimeOut */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
				}
				return;
			}
#endif
			
#if CTWING_AEPMODULE_MODE
			/* 读取负载数据 */
			if (NBIOT_Neul_NBxx_ReadCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
				/* Dictate execute is Success */
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
			}
			else {
				/* Dictate execute is Fail */
				if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
					/* Dictate TimeOut */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt++;
					if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt > 3) {
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt = 0;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
					}
				}
				else {
					/* Dictate isn't TimeOut */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
				}
				return;
			}
#endif
			
			if (memcmp((const char*)pClient->LWM2MStack->NBIotStack->Recvbuf, CTWINGFeedBackData, sizeof(CTWINGFeedBackData)) == 0) {
				/* Is Feedback */
				pClient->LWM2MStack->NBIotStack->NetStateIdentification = true;
				if (CTWINGFeedBackFlag == false) {
					CTWINGFeedBackFlag = true;
					NET_CTWing_Message_SendDataOffSet();
				}
				CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, SEND_DATA, RECV_DATA);
				
			#if NBCTWING_LISTEN_PARAMETER_TYPE == NBCTWING_LISTEN_PARAMETER_ENABLE
				NET_CTWING_NBIOT_Listen_Enable_EnterParameter(pClient);
			#endif
				
				/* NB 继续活跃注入时间 */
				TCFG_Utility_Set_Nbiot_IdleLifetime(NBIOT_CONTINUE_LIFETIME);
				
#if NETDATACONNECT_TIMEOUT_TYPE
				/* Net Data Connect Time Clear 0 */
				NetDataConnectTimeout = 0;
#endif
				
				/* Get ConnectTime */
				CTWING_NBIOT_GetConnectTime(pClient, true);
				
#ifdef CTWING_DEBUG_LOG_RF_PRINT
				CTWING_DEBUG_LOG_PRINTF("CTWing Recv Feedback Ok");
#endif
			}
			else {
				/* Not Feedback */
				NET_CTWing_Message_RecvDataEnqueue(pClient->LWM2MStack->NBIotStack->Recvbuf, pClient->LWM2MStack->NBIotStack->Recvlen);
#ifdef CTWING_DEBUG_LOG_RF_PRINT
#if !CTWING_AEPMODULE_MODE
				CTWING_DEBUG_LOG_PRINTF("CTWing Recv Data TaskID: %d Ok", CTWingDnHead.TaskID);
#endif
#if CTWING_AEPMODULE_MODE
				CTWING_DEBUG_LOG_PRINTF("CTWing Recv Data Ok");
#endif
#endif
			}
		}
	}
	else {
		/* Not Data Need Receive */
		if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
			/* Dictate TimeOut */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt++;
			if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt > 3) {
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataFailureCnt = 0;
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			}
		}
		else {
			/* Dictate isn't TimeOut */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = RECV_DATA;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Wait Recv Feedback");
#endif
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_SendDataRANormal(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_SendDataRANormal	: 发送数据RANormal
 @Input				pClient							: CTWing客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_SendDataRANormal(CTWING_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	char* RANormal	= "0x0100";
	char* RAIdle	= "0x0101";
	char* RAState	= RAIdle;
#if !CTWING_AEPMODULE_MODE
	NBIOT_ByteStreamUploadHead CTWingUpHead;
#endif
	
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
	int SendSentNum = 0;
#endif
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	/* Data packets need to be sent*/
	if (NET_CTWing_Message_SendDataDequeue(pClient->LWM2MStack->NBIotStack->Sendbuf, (unsigned short *)&pClient->LWM2MStack->NBIotStack->Sendlen) == true) {
		/* Get IdleTime */
		CTWING_NBIOT_GetIdleTime(pClient, true);
		
#if CTWING_SEND_BEFORE_ATTACH_TYPE
		/* Connect Check */
		if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA_RA_NORMAL;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Ok", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail ECde %d", pClient->LWM2MStack->NBIotStack->Parameter.netstate, NBStatus);
		#else
			CTWing_DEBUG_LOG_PRINTF("CTWing CGATT %d Fail", pClient->LWM2MStack->NBIotStack->Parameter.netstate);
		#endif
#endif
			return;
		}
		
		if (pClient->LWM2MStack->NBIotStack->Parameter.netstate != Attach) {
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			return;
		}
#endif
		
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
		if (((NBStatus = NBIOT_Neul_NBxx_QuerySendMessageCOAPPayload(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK) && 
		    ((NBStatus = NBIOT_Neul_NBxx_QueryReadMessageCOAPPayload(pClient->LWM2MStack->NBIotStack)) == NBIOT_OK)) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA_RA_NORMAL;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing NQMGS NQMGR Fail");
		#endif
#endif
			return;
		}
		
		SendSentNum = pClient->LWM2MStack->NBIotStack->Parameter.coapSendMessage.sent;
#endif
		
#if CTWING_RASENDMODE_TYPE == CTWING_RASENDMODE_NORMAL
		RAState = RANormal;
#elif CTWING_RASENDMODE_TYPE == CTWING_RASENDMODE_IDLE
		if (NBIOT_COAP_RA_NORMAL_GET_STATE(pClient->LWM2MStack->NBIotStack) == true) {
			RAState = RANormal;
		}
		else {
			RAState = RAIdle;
		}
#endif
		
#if !CTWING_AEPMODULE_MODE
		CTWingUpHead.CMDType		= CTWING_BYTESTREAM_UPLOAD_CMDTYPE;
		CTWingUpHead.DatasetID		= CTWING_BYTESTREAM_UPLOAD_DATASETID;
		CTWingUpHead.StreamLen		= pClient->LWM2MStack->NBIotStack->Sendlen + sizeof(CTWingUpHead.PayloadLen);
		CTWingUpHead.PayloadLen		= pClient->LWM2MStack->NBIotStack->Sendlen;
		
		/* 发送负载数据 */
		if ((NBStatus = NBIOT_Neul_NBxx_SendCTWINGPayloadFlag(pClient->LWM2MStack->NBIotStack, &CTWingUpHead, RAState)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA_RA_NORMAL;
			NBIOT_COAP_RA_NORMAL_SET_STATE(pClient->LWM2MStack->NBIotStack, false);
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail");
		#endif
#endif
			return;
		}
#endif
		
#if CTWING_AEPMODULE_MODE
		/* 发送负载数据 */
		if ((NBStatus = NBIOT_Neul_NBxx_SendCOAPPayloadFlag(pClient->LWM2MStack->NBIotStack, RAState)) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA_RA_NORMAL;
			NBIOT_COAP_RA_NORMAL_SET_STATE(pClient->LWM2MStack->NBIotStack, false);
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail ECde %d", NBStatus);
		#else
			CTWING_DEBUG_LOG_PRINTF("CTWing Send Payload Fail");
		#endif
#endif
			return;
		}
#endif
		
#if CTWING_SENDDATA_NQMGSCHECK_TYPE
		if (NBIOT_Neul_NBxx_QuerySendMessageCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = SEND_DATA_RA_NORMAL;
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, SEND_DATA_RA_NORMAL);
			return;
		}
		
		if ((SendSentNum + 1) != pClient->LWM2MStack->NBIotStack->Parameter.coapSendMessage.sent) {
			/* Send Data Fail */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataRANormalFailureCnt++;
			if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataRANormalFailureCnt > 3) {
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateSendDataRANormalFailureCnt = 0;
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			}
		}
		else {
			/* Send Data Success */
			CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, RECV_DATA_RA_NORMAL, SEND_DATA_RA_NORMAL);
		}
#else
		/* Send Data Success */
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, RECV_DATA_RA_NORMAL, SEND_DATA_RA_NORMAL);
#endif
	}
	/* No packets need to be sent */
	else {
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, EXECUT_DOWNLINK_DATA, SEND_DATA_RA_NORMAL);
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_RecvDataRANormal(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_RecvDataRANormal	: 接收数据RANormal
 @Input				pClient							: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_RecvDataRANormal(CTWING_ClientsTypeDef* pClient)
{
#if !CTWING_AEPMODULE_MODE
	NBIOT_ByteStreamDnloadHead CTWingDnHead;
#endif
	
	CTWING_NBIOT_DictateEvent_SetTime(pClient, 60);
	
	if (NBIOT_Neul_NBxx_CheckReadCONDataStatus(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = RECV_DATA_RA_NORMAL;
	}
	else {
		/* Dictate execute is Fail */
		CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, RECV_DATA_RA_NORMAL);
		return;
	}
	
	if (pClient->LWM2MStack->NBIotStack->Parameter.condatastate == SendSussess) {
		/* Send Data To Server Success */
		if (NBIOT_Neul_NBxx_QueryReadMessageCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
			/* Dictate execute is Success */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = RECV_DATA_RA_NORMAL;
		}
		else {
			/* Dictate execute is Fail */
			CTWING_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, RECV_DATA_RA_NORMAL);
			return;
		}
		
		/* 检查是否有下行数据 */
		if (pClient->LWM2MStack->NBIotStack->Parameter.coapReadMessage.buffered != 0) {
			/* Has Data Need Receive */
			for (int index = 0; index < pClient->LWM2MStack->NBIotStack->Parameter.coapReadMessage.buffered; index++) {
#if !CTWING_AEPMODULE_MODE
				/* 读取负载数据 */
				if (NBIOT_Neul_NBxx_ReadCTWINGPayload(pClient->LWM2MStack->NBIotStack, &CTWingDnHead) == NBIOT_OK) {
					/* Dictate execute is Success */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
				}
				else {
					/* Dictate execute is Fail */
					if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
						/* Dictate TimeOut */
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt++;
						if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt > 3) {
							pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt = 0;
							pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
						}
					}
					else {
						/* Dictate isn't TimeOut */
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
					}
					return;
				}
#endif
				
#if CTWING_AEPMODULE_MODE
				/* 读取负载数据 */
				if (NBIOT_Neul_NBxx_ReadCOAPPayload(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) {
					/* Dictate execute is Success */
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
				}
				else {
					/* Dictate execute is Fail */
					if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
						/* Dictate TimeOut */
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt++;
						if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt > 3) {
							pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt = 0;
							pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
						}
					}
					else {
						/* Dictate isn't TimeOut */
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent;
					}
					return;
				}
#endif
				
				NET_CTWing_Message_RecvDataEnqueue(pClient->LWM2MStack->NBIotStack->Recvbuf, pClient->LWM2MStack->NBIotStack->Recvlen);
#ifdef CTWING_DEBUG_LOG_RF_PRINT
#if !CTWING_AEPMODULE_MODE
				CTWING_DEBUG_LOG_PRINTF("CTWing Recv Data TaskID: %d Ok", CTWingDnHead.TaskID);
#endif
#if CTWING_AEPMODULE_MODE
				CTWING_DEBUG_LOG_PRINTF("CTWing Recv Data Ok");
#endif
#endif
			}
		}
		
		pClient->LWM2MStack->NBIotStack->NetStateIdentification = true;
		NET_CTWing_Message_SendDataOffSet();
		CTWING_NBIOT_DictateEvent_SuccessExecute(pClient, SEND_DATA_RA_NORMAL, RECV_DATA_RA_NORMAL);
		
	#if NBCTWING_LISTEN_PARAMETER_TYPE == NBCTWING_LISTEN_PARAMETER_ENABLE
		NET_CTWING_NBIOT_Listen_Enable_EnterParameter(pClient);
	#endif
		
		/* NB 继续活跃注入时间 */
		TCFG_Utility_Set_Nbiot_IdleLifetime(NBIOT_CONTINUE_LIFETIME);
		
#if NETDATACONNECT_TIMEOUT_TYPE
		/* Net Data Connect Time Clear 0 */
		NetDataConnectTimeout = 0;
#endif
		
		/* Get ConnectTime */
		CTWING_NBIOT_GetConnectTime(pClient, true);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		CTWING_DEBUG_LOG_PRINTF("CTWing Send Ok");
#endif
	}
	else {
		/* Not yet Send Data Success */
		if (Stm32_Calculagraph_IsExpiredSec(&pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
			/* Dictate TimeOut */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt++;
			if (pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt > 3) {
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateRecvDataRANormalFailureCnt = 0;
				pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			}
		}
		else {
			/* Dictate isn't TimeOut */
			pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = RECV_DATA_RA_NORMAL;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
			CTWING_DEBUG_LOG_PRINTF("CTWing Wait Send Ok");
#endif
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Event_ExecutDownlinkData(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Event_ExecutDownlinkData	: 下行数据处理
 @Input				pClient								: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Event_ExecutDownlinkData(CTWING_ClientsTypeDef* pClient)
{
	AepCmdData aepCmdResult;
	AepBytes   aepCodeResult;
	
	if (NET_CTWing_Message_RecvDataDequeue(pClient->Recvbuf, (unsigned short*)&pClient->Recvlen) == true) {
		pClient->Recvbuf[pClient->Recvlen] = '\0';
		
		BEEP_CtrlRepeat_Extend(4, 75, 25);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		Radio_Trf_Printf("recvLen: %d", pClient->Recvlen);
#endif
		
		aepCmdResult = CTWing_DecodeCmdDownFromBytes(pClient, (char*)pClient->Recvbuf, pClient->Recvlen);
		
#ifdef CTWING_DEBUG_LOG_RF_PRINT
		Radio_Trf_Printf("code: %d", aepCmdResult.code);
		Radio_Trf_Printf("taskId: %d", aepCmdResult.taskId);
		Radio_Trf_Printf("serviceId: %d", aepCmdResult.serviceId);
#endif
		
		if (aepCmdResult.code == AEP_CMD_SUCCESS) {
			
			if (aepCmdResult.serviceId == AEP_SERVICE_ID_DEVICECTRL_CMD) {
				AepDeviceControlCmdData* data = (AepDeviceControlCmdData*)aepCmdResult.data;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
				Radio_Trf_Printf("command_type: %d", data->command_type);
#endif
				AepDeviceControlRespSrcdata.taskId				= aepCmdResult.taskId;
				AepDeviceControlRespSrcdata.command_type		= data->command_type;
				
				aepCodeResult = CTWing_CodeDataReportByIdToBytes(pClient, AEP_SERVICE_ID_DEVICECTRL_RESP, &AepDeviceControlRespSrcdata);
				
				NET_CTWing_Message_SendDataEnqueue((unsigned char *)aepCodeResult.str, aepCodeResult.len);
			}
			else if (aepCmdResult.serviceId == AEP_SERVICE_ID_HEARTBEAT_CMD) {
				AepHeartbeatTimeCmdData* data = (AepHeartbeatTimeCmdData*)aepCmdResult.data;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
				Radio_Trf_Printf("heartbeat_time: %f", data->heartbeat_time);
#endif
				AepHeartbeatTimeRespSrcdata.taskId				= aepCmdResult.taskId;
				AepHeartbeatTimeRespSrcdata.heartbeat_time		= data->heartbeat_time;
				
				aepCodeResult = CTWing_CodeDataReportByIdToBytes(pClient, AEP_SERVICE_ID_HEARTBEAT_RESP, &AepHeartbeatTimeRespSrcdata);
				
				NET_CTWing_Message_SendDataEnqueue((unsigned char *)aepCodeResult.str, aepCodeResult.len);
			}
			else if (aepCmdResult.serviceId == AEP_SERVICE_ID_PROTECT_CMD) {
				AepProtectTimeCmdData* data = (AepProtectTimeCmdData*)aepCmdResult.data;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
				Radio_Trf_Printf("protect_time: %f", data->protect_time);
#endif
				AepProtectTimeRespSrcdata.taskId				= aepCmdResult.taskId;
				AepProtectTimeRespSrcdata.protect_time			= data->protect_time;
				
				aepCodeResult = CTWing_CodeDataReportByIdToBytes(pClient, AEP_SERVICE_ID_PROTECT_RESP, &AepProtectTimeRespSrcdata);
				
				NET_CTWing_Message_SendDataEnqueue((unsigned char *)aepCodeResult.str, aepCodeResult.len);
			}
			
		}
		
		NET_CTWing_Message_RecvDataOffSet();
	}
	
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = LISTEN_RUN_CTL;
}


/**********************************************************************************************************
 @Function			void NET_CTWING_Listen_PollExecution(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_Listen_PollExecution		: CTWING监听器处理
 @Input				pClient							: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_Listen_PollExecution(CTWING_ClientsTypeDef* pClient)
{
	switch (pClient->ListenRunCtl.listenEvent)
	{
	case NBCTWING_LISTEN_MODE_ENTER_NONE:
		NET_CTWING_NBIOT_Listen_Enable_EnterNone(pClient);
		break;
	
	case NBCTWING_LISTEN_MODE_ENTER_PARAMETER:
#if NBCTWING_LISTEN_PARAMETER_TYPE == NBCTWING_LISTEN_PARAMETER_ENABLE
		NET_CTWING_NBIOT_Listen_Event_EnterParameter(pClient);
#endif
		break;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Listen_Enable_EnterNone(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Listen_Enable_EnterNone	: 事件(进入None模式)监听
 @Input				pClient								: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Listen_Enable_EnterNone(CTWING_ClientsTypeDef* pClient)
{
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = CTWING_SENDMODE_TYPE;
	pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_DEFAULT_BOOTMODE;
	pClient->LWM2MStack->NBIotStack->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_CTWING;
}

#if NBCTWING_LISTEN_PARAMETER_TYPE == NBCTWING_LISTEN_PARAMETER_ENABLE
/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Listen_Enable_EnterParameter(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Listen_Enable_EnterParameter: 使能(进入NBIOT运行信息)监听
 @Input				pClient								: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Listen_Enable_EnterParameter(CTWING_ClientsTypeDef* pClient)
{
	Stm32_CalculagraphTypeDef listenRunTime;
	
	/* Listen Enable */
	if (pClient->ListenRunCtl.ListenEnterParameter.listenEnable == true) {
		pClient->ListenRunCtl.ListenEnterParameter.listenStatus = true;
		Stm32_Calculagraph_CountdownSec(&listenRunTime, pClient->ListenRunCtl.ListenEnterParameter.listenTimereachSec);
		pClient->ListenRunCtl.ListenEnterParameter.listenRunTime = listenRunTime;
	}
}

/**********************************************************************************************************
 @Function			void NET_CTWING_NBIOT_Listen_Event_EnterParameter(CTWING_ClientsTypeDef* pClient)
 @Description			NET_CTWING_NBIOT_Listen_Event_EnterParameter	: 事件(进入NBIOT运行信息)监听
 @Input				pClient								: CTWING客户端实例
 @Return				void
**********************************************************************************************************/
void NET_CTWING_NBIOT_Listen_Event_EnterParameter(CTWING_ClientsTypeDef* pClient)
{
	Stm32_CalculagraphTypeDef eventRunTime;
	
	if ((pClient->ListenRunCtl.ListenEnterParameter.listenEnable == true) && (pClient->ListenRunCtl.ListenEnterParameter.listenStatus == true)) {
		if (Stm32_Calculagraph_IsExpiredSec(&pClient->ListenRunCtl.ListenEnterParameter.listenRunTime) == true) {
			
			/* It is the first time to execute */
			if (pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventEnable != true) {
				pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventEnable = true;
				pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventTimeoutSec = 30;
				Stm32_Calculagraph_CountdownSec(&eventRunTime, pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventTimeoutSec);
				pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventRunTime = eventRunTime;
			}
			
			if ((NBIOT_Neul_NBxx_CheckReadRSSI(pClient->LWM2MStack->NBIotStack) == NBIOT_OK) &&
			    (NBIOT_Neul_NBxx_CheckReadStatisticsRADIO(pClient->LWM2MStack->NBIotStack) == NBIOT_OK)) {
				/* Dictate execute is Success */
				pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventEnable = false;
				pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_MODE_ENTER_PARAMETER;
				pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventFailureCnt = 0;
#ifdef CTWING_DEBUG_LOG_RF_PRINT
				Radio_Trf_Printf("RSSI: %d", pClient->LWM2MStack->NBIotStack->Parameter.rssi);
				Radio_Trf_Printf("SNR: %d", pClient->LWM2MStack->NBIotStack->Parameter.statisticsRADIO.SNR);
#endif
			}
			else {
				/* Dictate execute is Fail */
				if (Stm32_Calculagraph_IsExpiredSec(&pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventRunTime) == true) {
					/* Dictate TimeOut */
					pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventEnable = false;
					pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_MODE_ENTER_PARAMETER;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
					pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
					pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventFailureCnt++;
					if (pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventFailureCnt > 3) {
						pClient->ListenRunCtl.ListenEnterParameter.EventCtl.eventFailureCnt = 0;
						pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
					}
				}
				else {
					/* Dictate isn't TimeOut */
					pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_MODE_ENTER_PARAMETER;
				}
				return;
			}
			
			pClient->ListenRunCtl.ListenEnterParameter.listenEnable = false;
			pClient->ListenRunCtl.ListenEnterParameter.listenStatus = false;
			pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_MODE_ENTER_PARAMETER;
		}
	}
	
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEnable = false;
	pClient->LWM2MStack->NBIotStack->DictateRunCtl.dictateEvent = CTWING_SENDMODE_TYPE;
	pClient->ListenRunCtl.listenEvent = NBCTWING_LISTEN_DEFAULT_BOOTMODE;
	pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_CTWING;
}
#endif

/********************************************** END OF FLEE **********************************************/
