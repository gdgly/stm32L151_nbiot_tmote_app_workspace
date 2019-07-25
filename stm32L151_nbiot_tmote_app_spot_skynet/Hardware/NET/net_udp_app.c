/**
  *********************************************************************************************************
  * @file    net_udp_app.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-04-25
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "net_udp_app.h"
#include "inspectmessageoperate.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_rtc.h"
#include "hal_beep.h"
#include "radar_api.h"
#include "hal_qmc5883l.h"
#include "string.h"
#include "radio_rf_app.h"

/**********************************************************************************************************
 @Function			void NET_UDP_APP_PollExecution(UDP_ClientsTypeDef* pClient)
 @Description			UDP_APP_PollExecution				: UDP逻辑处理
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_APP_PollExecution(UDP_ClientsTypeDef* pClient)
{
	switch (pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent)
	{
	case STOP_MODE:
		NET_UDP_NBIOT_Event_StopMode(pClient);
		break;
	
	case HARDWARE_REBOOT:
		NET_UDP_NBIOT_Event_HardwareReboot(pClient);
		break;
	
	case REPORT_ERROE:
		NET_UDP_NBIOT_Event_ReportError(pClient);
		break;
	
	case MODULE_CHECK:
		NET_UDP_NBIOT_Event_ModuleCheck(pClient);
		break;
	
	case PARAMETER_CONFIG:
		NET_UDP_NBIOT_Event_ParameterConfig(pClient);
		break;
	
	case ICCID_CHECK:
		NET_UDP_NBIOT_Event_SimICCIDCheck(pClient);
		break;
	
	case MISC_EQUIP_CONFIG:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case ATTACH_CHECK:
		NET_UDP_NBIOT_Event_AttachCheck(pClient);
		break;
	
	case ATTACH_EXECUTE:
		NET_UDP_NBIOT_Event_AttachExecute(pClient);
		break;
	
	case ATTACH_INQUIRE:
		NET_UDP_NBIOT_Event_AttachInquire(pClient);
		break;
	
	case PARAMETER_CHECKOUT:
		NET_UDP_NBIOT_Event_ParameterCheckOut(pClient);
		break;
	
	case MINIMUM_FUNCTIONALITY:
		NET_UDP_NBIOT_Event_MinimumFunctionality(pClient);
		break;
	
	case FULL_FUNCTIONALITY:
		NET_UDP_NBIOT_Event_FullFunctionality(pClient);
		break;
	
	case CLEAR_STORED_EARFCN:
		NET_UDP_NBIOT_Event_ClearStoredEARFCN(pClient);
		break;
	
	case CDP_SERVER_CHECK:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case CDP_SERVER_CONFIG:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case NBAND_MODE_CHECK:
		NET_UDP_NBIOT_Event_NbandModeCheck(pClient);
		break;
	
	case NBAND_MODE_CONFIG:
		NET_UDP_NBIOT_Event_NbandModeConfig(pClient);
		break;
	
	case MQTTSN_PROCESS_STACK:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case DNS_PROCESS_STACK:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case ONENET_PROCESS_STACK:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	case UDP_PROCESS_STACK:
		NET_UDP_APP_ProcessExecution(pClient);
		break;
	
	case LISTEN_RUN_CTL:
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	
	default :
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		break;
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_APP_ProcessExecution(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_APP_ProcessExecution			: UDP协议逻辑处理
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_APP_ProcessExecution(UDP_ClientsTypeDef* pClient)
{
	switch (pClient->ProcessState)
	{
	case UDP_PROCESS_CREAT_UDP_SOCKET:
		NET_UDP_Event_CreatUDPSocket(pClient);
		break;
	
	case UDP_PROCESS_CONNECT_SERVER:
		NET_UDP_Event_ConnectServer(pClient);
		break;
	
	case UDP_PROCESS_SEND_DATA:
		NET_UDP_Event_SendData(pClient);
		break;
	
	case UDP_PROCESS_SLEEP:
		NET_UDP_Event_Sleep(pClient);
		break;
	
	case UDP_PROCESS_HEART:
		NET_UDP_Event_Heart(pClient);
		break;
	}
	
	if (pClient->UDPRunFailFlag != 1) {
		pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_MQTTSN;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = MQTTSN_PROCESS_STACK;
	}
	else {
		pClient->UDPRunFailFlag = 0;
	}
}

/**********************************************************************************************************
 @Function			static void UDP_NBIOT_DictateEvent_SetTime(UDP_ClientsTypeDef* pClient, unsigned int TimeoutSec)
 @Description			UDP_NBIOT_DictateEvent_SetTime		: 事件运行控制器注入时间(内部使用)
 @Input				pClient							: UDP客户端实例
					TimeoutSec						: 注入超时时间
 @Return				void
 @attention			事件运行之前判断是否需要注入时间
**********************************************************************************************************/
static void UDP_NBIOT_DictateEvent_SetTime(UDP_ClientsTypeDef* pClient, unsigned int TimeoutSec)
{
	Stm32_CalculagraphTypeDef dictateRunTime;
	
	/* It is the first time to execute */
	if (pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable != true) {
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = true;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateTimeoutSec = TimeoutSec;
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, pClient->SocketStack->NBIotStack->DictateRunCtl.dictateTimeoutSec);
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRunTime = dictateRunTime;
	}
}

/**********************************************************************************************************
 @Function			static void UDP_DictateEvent_SetTime(UDP_ClientsTypeDef* pClient, unsigned int TimeoutSec)
 @Description			UDP_DictateEvent_SetTime				: 事件运行控制器注入时间(内部使用)
 @Input				pClient							: UDP客户端实例
					TimeoutSec						: 注入超时时间
 @Return				void
 @attention			事件运行之前判断是否需要注入时间
**********************************************************************************************************/
static void UDP_DictateEvent_SetTime(UDP_ClientsTypeDef* pClient, unsigned int TimeoutSec)
{
	Stm32_CalculagraphTypeDef dictateRunTime;
	
	/* It is the first time to execute */
	if (pClient->DictateRunCtl.dictateEnable != true) {
		pClient->DictateRunCtl.dictateEnable = true;
		pClient->DictateRunCtl.dictateTimeoutSec = TimeoutSec;
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, pClient->DictateRunCtl.dictateTimeoutSec);
		pClient->DictateRunCtl.dictateRunTime = dictateRunTime;
	}
}

static unsigned char* UDP_NBIOT_GetDictateFailureCnt(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	switch (dictateNoTimeOut)
	{
	case HARDWARE_REBOOT:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRebootFailureCnt;
		break;
	
	case REPORT_ERROE:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateReportErrorFailureCnt;
		break;
	
	case MODULE_CHECK:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateModuleCheckFailureCnt;
		break;
	
	case PARAMETER_CONFIG:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateParameterConfigFailureCnt;
		break;
	
	case ICCID_CHECK:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateSimICCIDCheckFailureCnt;
		break;
	
	case ATTACH_CHECK:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateAttachCheckFailureCnt;
		break;
	
	case ATTACH_EXECUTE:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateAttachExecuteFailureCnt;
		break;
	
	case ATTACH_INQUIRE:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateAttachInquireFailureCnt;
		break;
	
	case PARAMETER_CHECKOUT:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictatePatameterCheckOutFailureCnt;
		break;
	
	case MINIMUM_FUNCTIONALITY:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateMinimumFunctionalityFailureCnt;
		break;
	
	case FULL_FUNCTIONALITY:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateFullFunctionalityFailureCnt;
		break;
	
	case NBAND_MODE_CHECK:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateNbandModeCheckFailureCnt;
		break;
	
	case NBAND_MODE_CONFIG:
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateNbandModeConfigFailureCnt;
		break;
	
	default :
		dictateFailureCnt = &pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRebootFailureCnt;
		break;
	}
	
	return dictateFailureCnt;
}

static unsigned char* UDP_GetDictateFailureCnt(UDP_ClientsTypeDef* pClient, UDP_ProcessStateTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	switch (dictateNoTimeOut)
	{
	case UDP_PROCESS_CREAT_UDP_SOCKET:
		dictateFailureCnt = &pClient->DictateRunCtl.dictateCreatUDPSocketFailureCnt;
		break;
	
	case UDP_PROCESS_CONNECT_SERVER:
		dictateFailureCnt = &pClient->DictateRunCtl.dictateConnectServerFailureCnt;
		break;
	
	case UDP_PROCESS_SEND_DATA:
		dictateFailureCnt = &pClient->DictateRunCtl.dictateSendDataFailureCnt;
		break;
	
	case UDP_PROCESS_SLEEP:
		dictateFailureCnt = &pClient->DictateRunCtl.dictateSleepFailureCnt;
		break;
	
	case UDP_PROCESS_HEART:
		dictateFailureCnt = &pClient->DictateRunCtl.dictateHeartFailureCnt;
		break;
	}
	
	return dictateFailureCnt;
}

/**********************************************************************************************************
 @Function			static void UDP_NBIOT_DictateEvent_FailExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
																				 NBIOT_DictateEventTypeDef dictateFail, \
																				 NBIOT_DictateEventTypeDef dictateNoTimeOut)
 @Description			UDP_NBIOT_DictateEvent_FailExecute		: 事件运行控制器出错执行(内部使用)
 @Input				pClient							: UDP客户端实例
					dictateTimeOut						: 事假处理错误超时
					dictateFail						: 事件处理错误次数溢出
					dictateNoTimeOut					: 事假处理错误未超时
 @Return				void
**********************************************************************************************************/
static void UDP_NBIOT_DictateEvent_FailExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
															 NBIOT_DictateEventTypeDef dictateFail, \
															 NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	dictateFailureCnt = UDP_NBIOT_GetDictateFailureCnt(pClient, dictateNoTimeOut);
	
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
		/* Dictate TimeOut */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = false;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateTimeOut;
		*dictateFailureCnt += 1;
		if (*dictateFailureCnt > 3) {
			*dictateFailureCnt = 0;
			pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateFail;
		}
	}
	else {
		/* Dictate isn't TimeOut */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateNoTimeOut;
	}
}

/**********************************************************************************************************
 @Function			static void UDP_NBIOT_DictateEvent_SuccessExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
																				    NBIOT_DictateEventTypeDef dictateNoTimeOut)
 @Description			UDP_NBIOT_DictateEvent_SuccessExecute	: 事件运行控制器正确执行(内部使用)
 @Input				pClient							: UDP客户端实例
					dictateSuccess						: 事假处理正确
					dictateNoTimeOut					: 事假处理错误未超时
 @Return				void
**********************************************************************************************************/
static void UDP_NBIOT_DictateEvent_SuccessExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
															    NBIOT_DictateEventTypeDef dictateNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	dictateFailureCnt = UDP_NBIOT_GetDictateFailureCnt(pClient, dictateNoTimeOut);
	
	pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = false;
	pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateSuccess;
	*dictateFailureCnt = 0;
}

/**********************************************************************************************************
 @Function			static void UDP_DictateEvent_FailExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
																			UDP_ProcessStateTypeDef dictateSubTimeOut, \
																			UDP_ProcessStateTypeDef dictateSubNoTimeOut)
 @Description			UDP_DictateEvent_FailExecute			: 事件运行控制器出错执行(内部使用)
 @Input				pClient							: UDP客户端实例
					dictateTimeOut						: 事件处理错误超时
					dictateSubTimeOut					: 事件处理错误次数溢出
					dictateNoTimeOut					: 事件处理错误未超时
 @Return				void
**********************************************************************************************************/
static void UDP_DictateEvent_FailExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateTimeOut, \
														UDP_ProcessStateTypeDef dictateSubTimeOut, \
														UDP_ProcessStateTypeDef dictateSubNoTimeOut)
{
	unsigned char* dictateFailureCnt;
	
	dictateFailureCnt = UDP_GetDictateFailureCnt(pClient, dictateSubNoTimeOut);
	
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->DictateRunCtl.dictateRunTime) == true) {
		/* Dictate TimeOut */
		pClient->DictateRunCtl.dictateEnable = false;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateTimeOut;
		pClient->ProcessState = dictateSubTimeOut;
		pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_DNS;
		*dictateFailureCnt += 1;
		if (*dictateFailureCnt > 3) {
			*dictateFailureCnt = 0;
			pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_MQTTSN;
			pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			pClient->ProcessState = UDP_PROCESS_CREAT_UDP_SOCKET;
		}
		pClient->UDPRunFailFlag = 1;
	}
	else {
		/* Dictate isn't TimeOut */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = UDP_PROCESS_STACK;
		pClient->ProcessState = dictateSubNoTimeOut;
	}
}

/**********************************************************************************************************
 @Function			static void UDP_DictateEvent_SuccessExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
																			   UDP_ProcessStateTypeDef dictateSubSuccess, \
																			   UDP_ProcessStateTypeDef dictateSubNoTimeOut, \
																			   bool dictateFailureCntState)
 @Description			UDP_DictateEvent_SuccessExecute		: 事件运行控制器正确执行(内部使用)
 @Input				pClient							: UDP客户端实例
					dictateSuccess						: 事件处理正确
					dictateSubSuccess					: 事件处理正确
					dictateNoTimeOut					: 事件处理错误未超时
 @Return				void
**********************************************************************************************************/
static void UDP_DictateEvent_SuccessExecute(UDP_ClientsTypeDef* pClient, NBIOT_DictateEventTypeDef dictateSuccess, \
														   UDP_ProcessStateTypeDef dictateSubSuccess, \
														   UDP_ProcessStateTypeDef dictateSubNoTimeOut, \
														   bool dictateFailureCntState)
{
	unsigned char* dictateFailureCnt;
	
	if (dictateFailureCntState) {
		dictateFailureCnt = UDP_GetDictateFailureCnt(pClient, dictateSubNoTimeOut);
		pClient->DictateRunCtl.dictateEnable = false;
		*dictateFailureCnt = 0;
	}
	
	pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = dictateSuccess;
	pClient->ProcessState = dictateSubSuccess;
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_StopMode(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_StopMode			: 停止模式
 @Input				pClient							: UDP客户端实例
 @Return				void
 @attention			当30分钟或有数据需要发送时退出停止模式尝试重启NB,开启NB运行
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_StopMode(UDP_ClientsTypeDef* pClient)
{
	Stm32_CalculagraphTypeDef dictateRunTime;
	static unsigned char UDPByteStreamIndex;
	
	/* It is the first time to execute */
	if (pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable != true) {
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = true;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateTimeoutSec = 1800;
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, pClient->SocketStack->NBIotStack->DictateRunCtl.dictateTimeoutSec);
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRunTime = dictateRunTime;
		/* NBIOT Module Poweroff */
		NBIOT_Neul_NBxx_HardwarePoweroff(pClient->SocketStack->NBIotStack);
		/* Clear Stored EARFCN */
		pClient->SocketStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_TRUE;
		/* Init Message Index */
		UDPByteStreamIndex = NET_UDP_Message_SendDataRear();
	}
	
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->SocketStack->NBIotStack->DictateRunCtl.dictateRunTime) == true) {
		/* Dictate TimeOut */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = false;
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
		pClient->ProcessState = UDP_PROCESS_CREAT_UDP_SOCKET;
		pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_DNS;
	}
	else {
		/* Dictate isn't TimeOut */
		if ( NET_UDP_Message_SendDataRear() != UDPByteStreamIndex ) {
			pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEnable = false;
			pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = HARDWARE_REBOOT;
			pClient->ProcessState = UDP_PROCESS_CREAT_UDP_SOCKET;
			pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_DNS;
		}
		else {
			pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = STOP_MODE;
			pClient->ProcessState = UDP_PROCESS_CREAT_UDP_SOCKET;
			pClient->NetNbiotStack->PollExecution = NET_POLL_EXECUTION_UDP;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_HardwareReboot(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_HardwareReboot		: 硬件重启
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_HardwareReboot(UDP_ClientsTypeDef* pClient)
{
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (NBIOT_Neul_NBxx_HardwareReboot(pClient->SocketStack->NBIotStack, 8000) == NBIOT_OK) {
		/* Dictate execute is Success */
#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, REPORT_ERROE, HARDWARE_REBOOT);
#else
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, MODULE_CHECK, HARDWARE_REBOOT);
#endif
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB HDRBT Ok, Baud:%d", NBIOTBaudRate.Baud);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, HARDWARE_REBOOT);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB HDRBT Fail");
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_ReportError(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_ReportError		: 错误码输出
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_ReportError(UDP_ClientsTypeDef* pClient)
{
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBIOT_Neul_NBxx_SetReportTerminationError(pClient->SocketStack->NBIotStack, CMEEnable) == NBIOT_OK)) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, MODULE_CHECK, REPORT_ERROE);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB ReportECde %d Ok", CMEEnable);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, REPORT_ERROE);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB ReportECde %d Fail", CMEEnable);
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_ModuleCheck(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_ModuleCheck		: 模块检测
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_ModuleCheck(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if (((NBStatus = NBIOT_Neul_NBxx_CheckReadManufacturer(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadManufacturerModel(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadModuleVersion(pClient->SocketStack->NBIotStack)) == NBIOT_OK)) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, PARAMETER_CONFIG, MODULE_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB Module Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MODULE_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB Module Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB Module Fail");
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_ParameterConfig(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_ParameterConfig	: 参数配置
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_ParameterConfig(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadConfigUE(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB Para Cfg Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB Para Cfg Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB Para Cfg Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.autoConnect != AutoConnectVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, AutoConnect, AutoConnectVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", AutoConnect, AutoConnectVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", AutoConnect, AutoConnectVal);
#endif
			return;
		}
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.crScrambling != CrScramblingVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, CrScrambling, CrScramblingVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", CrScrambling, CrScramblingVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", CrScrambling, CrScramblingVal);
#endif
			return;
		}
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.crSiAvoid != CrSiAvoidVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, CrSiAvoid, CrSiAvoidVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", CrSiAvoid, CrSiAvoidVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", CrSiAvoid, CrSiAvoidVal);
#endif
			return;
		}
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.combineAttach != CombineAttachVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, CombineAttach, CombineAttachVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", CombineAttach, CombineAttachVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", CombineAttach, CombineAttachVal);
#endif
			return;
		}
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.cellReselection != CellReselectionVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, CellReselection, CellReselectionVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", CellReselection, CellReselectionVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", CellReselection, CellReselectionVal);
#endif
			return;
		}
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.nconfig.enableBip != EnableBipVal) {
		if (NBIOT_Neul_NBxx_SetConfigUE(pClient->SocketStack->NBIotStack, EnableBip, EnableBipVal) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ICCID_CHECK, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Ok", EnableBip, EnableBipVal);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB %s %d Fail", EnableBip, EnableBipVal);
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_SimICCIDCheck(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_SimICCIDCheck		: Sim卡检测
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_SimICCIDCheck(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadICCID(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, ICCID_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB ICCID Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ICCID_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB ICCID Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB ICCID Fail");
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_FullFunctionality(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_FullFunctionality		: 完整功能
 @Input				pClient								: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_FullFunctionality(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadMinOrFullFunc(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		if (pClient->SocketStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
			/* 需清除频点 */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, MINIMUM_FUNCTIONALITY, FULL_FUNCTIONALITY);
		}
		else {
			/* 无需清除频点 */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CHECK, FULL_FUNCTIONALITY);
		}
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB FullFunc Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, FULL_FUNCTIONALITY);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB FullFunc Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB FullFunc Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.functionality != FullFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetMinOrFullFunc(pClient->SocketStack->NBIotStack, FullFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
			if (pClient->SocketStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
				/* 需清除频点 */
				UDP_NBIOT_DictateEvent_SuccessExecute(pClient, MINIMUM_FUNCTIONALITY, FULL_FUNCTIONALITY);
			}
			else {
				/* 无需清除频点 */
				UDP_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CHECK, FULL_FUNCTIONALITY);
			}
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB FullFunc Set Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, FULL_FUNCTIONALITY);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			UDP_DEBUG_LOG_PRINTF("NB FullFunc Fail ECde %d", NBStatus);
		#else
			UDP_DEBUG_LOG_PRINTF("NB FullFunc Fail");
		#endif
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_MinimumFunctionality(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_MinimumFunctionality	: 最小功能
 @Input				pClient								: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_MinimumFunctionality(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadMinOrFullFunc(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		if (pClient->SocketStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
			/* 需清除频点 */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, CLEAR_STORED_EARFCN, MINIMUM_FUNCTIONALITY);
		}
		else {
			/* 无需清除频点 */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CONFIG, MINIMUM_FUNCTIONALITY);
		}
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB MinFunc Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MINIMUM_FUNCTIONALITY);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB MinFunc Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB MinFunc Fail");
	#endif
#endif
		return;
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.functionality != MinFunc) {
		if ((NBStatus = NBIOT_Neul_NBxx_SetMinOrFullFunc(pClient->SocketStack->NBIotStack, MinFunc)) == NBIOT_OK) {
			/* Dictate execute is Success */
			if (pClient->SocketStack->NBIotStack->ClearStoredEARFCN != NBIOT_CLEAR_STORED_EARFCN_FALSE) {
				/* 需清除频点 */
				UDP_NBIOT_DictateEvent_SuccessExecute(pClient, CLEAR_STORED_EARFCN, MINIMUM_FUNCTIONALITY);
			}
			else {
				/* 无需清除频点 */
				UDP_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CONFIG, MINIMUM_FUNCTIONALITY);
			}
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB MinFunc Set Ok");
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, MINIMUM_FUNCTIONALITY);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			UDP_DEBUG_LOG_PRINTF("NB MinFunc Fail ECde %d", NBStatus);
		#else
			UDP_DEBUG_LOG_PRINTF("NB MinFunc Fail");
		#endif
#endif
			return;
		}
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_ClearStoredEARFCN(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_ClearStoredEARFCN		: 清除小区频点
 @Input				pClient								: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_ClearStoredEARFCN(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_ClearStoredEarfcn(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->SocketStack->NBIotStack->ClearStoredEARFCN = NBIOT_CLEAR_STORED_EARFCN_FALSE;
		
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, CLEAR_STORED_EARFCN);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB Clear Stored EARFCN OK");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, CLEAR_STORED_EARFCN);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB Clear Stored EARFCN Fail Ecde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB Clear Stored EARFCN Fail");
	#endif
#endif
		return;
	}
}

static bool NET_UDP_CheckNband(UDP_ClientsTypeDef* pClient, NBIOT_NBandTypeDef nbandsrc, NBIOT_NBandTypeDef nbanddst)
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
 @Function			void NET_UDP_NBIOT_Event_NbandModeCheck(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_NbandModeCheck			: NBAND模式查询
 @Input				pClient								: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_NbandModeCheck(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadSupportedBands(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, NBAND_MODE_CHECK, NBAND_MODE_CHECK);
		
#ifdef DNS_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB BAND %d:%d.%d.%d Ok", pClient->SocketStack->NBIotStack->Parameter.band.NBandNum, \
											  pClient->SocketStack->NBIotStack->Parameter.band.NBandVal[0], \
											  pClient->SocketStack->NBIotStack->Parameter.band.NBandVal[1], \
											  pClient->SocketStack->NBIotStack->Parameter.band.NBandVal[2]);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB BAND Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB BAND Fail");
	#endif
#endif
	}
	
	if (NET_UDP_CheckNband(pClient, pClient->SocketStack->NBIotStack->Parameter.band, DNS_NBIOT_BAND_TYPE) != true) {
		/* BAND Mode Mast be Config */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = MINIMUM_FUNCTIONALITY;
	}
	else {
		/* BAND Mode Needn't be Config */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_CHECK;
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_NbandModeConfig(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_NbandModeConfig		: NBAND模式配置
 @Input				pClient								: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_NbandModeConfig(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadSupportedBands(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, NBAND_MODE_CONFIG);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB BAND Read Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CONFIG);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB BAND Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB BAND Fail");
	#endif
#endif
	}
	
	if (NET_UDP_CheckNband(pClient, pClient->SocketStack->NBIotStack->Parameter.band, DNS_NBIOT_BAND_TYPE) != true) {
		/* BAND Mode Mast be Config */
		if ((NBStatus = NBIOT_Neul_NBxx_SetSupportedBands(pClient->SocketStack->NBIotStack, DNS_NBIOT_BAND_TYPE)) == NBIOT_OK) {
			/* Dictate execute is Success */
			UDP_NBIOT_DictateEvent_SuccessExecute(pClient, FULL_FUNCTIONALITY, NBAND_MODE_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("NB BAND Set %d:%d.%d.%d Ok", DNS_NBIOT_BAND_TYPE.NBandNum, \
													 DNS_NBIOT_BAND_TYPE.NBandVal[0], \
													 DNS_NBIOT_BAND_TYPE.NBandVal[1], \
													 DNS_NBIOT_BAND_TYPE.NBandVal[2]);
#endif
		}
		else {
			/* Dictate execute is Fail */
			UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, NBAND_MODE_CONFIG);
			
#ifdef UDP_DEBUG_LOG_RF_PRINT
		#if NBIOT_PRINT_ERROR_CODE_TYPE
			UDP_DEBUG_LOG_PRINTF("NB BAND Fail ECde %d", NBStatus);
		#else
			UDP_DEBUG_LOG_PRINTF("NB BAND Fail");
		#endif
#endif
			return;
		}
	}
	else {
		/* BAND Mode Needn't be Config */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = FULL_FUNCTIONALITY;
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_AttachCheck(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_AttachCheck		: 注网检查
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_AttachCheck(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_CHECK, ATTACH_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Ok", pClient->SocketStack->NBIotStack->Parameter.netstate);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_CHECK);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Fail ECde %d", pClient->SocketStack->NBIotStack->Parameter.netstate, NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Fail", pClient->SocketStack->NBIotStack->Parameter.netstate);
	#endif
#endif
		return;
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.netstate != Attach) {
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_EXECUTE;
	}
	else {
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_INQUIRE;
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_AttachExecute(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_AttachExecute		: 注网进行
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_AttachExecute(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 30);
	
	if ((NBStatus = NBIOT_Neul_NBxx_SetAttachOrDetach(pClient->SocketStack->NBIotStack, Attach)) == NBIOT_OK) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, ATTACH_INQUIRE, ATTACH_EXECUTE);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB Set CGATT %d Ok", Attach);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_EXECUTE);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB Set CGATT %d Fail ECde %d", Attach, NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB Set CGATT %d Fail", Attach);
	#endif
#endif
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_AttachInquire(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_AttachInquire		: 注网查询
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_AttachInquire(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 60);
	
	if ((NBStatus = NBIOT_Neul_NBxx_CheckReadAttachOrDetach(pClient->SocketStack->NBIotStack)) == NBIOT_OK) {
		/* Dictate execute is Success */
		pClient->SocketStack->NBIotStack->DictateRunCtl.dictateEvent = ATTACH_INQUIRE;
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Ok", pClient->SocketStack->NBIotStack->Parameter.netstate);
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_INQUIRE);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Fail ECde %d", pClient->SocketStack->NBIotStack->Parameter.netstate, NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB CGATT %d Fail", pClient->SocketStack->NBIotStack->Parameter.netstate);
	#endif
#endif
		return;
	}
	
	if (pClient->SocketStack->NBIotStack->Parameter.netstate != Attach) {
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, ATTACH_INQUIRE);
	}
	else {
		/* 注网成功 */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, PARAMETER_CHECKOUT, ATTACH_INQUIRE);
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_NBIOT_Event_ParameterCheckOut(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_NBIOT_Event_ParameterCheckOut	: 参数检出
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_NBIOT_Event_ParameterCheckOut(UDP_ClientsTypeDef* pClient)
{
	NBIOT_StatusTypeDef NBStatus = NBStatus;
	
	UDP_NBIOT_DictateEvent_SetTime(pClient, 60);
	
	if (((NBStatus = NBIOT_Neul_NBxx_CheckReadIMEI(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadIMSI(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadCGPADDR(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadPDPContext(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadRSSI(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadStatisticsRADIO(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadAreaCode(pClient->SocketStack->NBIotStack)) == NBIOT_OK) && 
	    ((NBStatus = NBIOT_Neul_NBxx_CheckReadDateTime(pClient->SocketStack->NBIotStack)) == NBIOT_OK)) {
		/* Dictate execute is Success */
		UDP_NBIOT_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, PARAMETER_CHECKOUT);
		
		pClient->SocketStack->NBIotStack->Registered = true;
		
#ifdef DNS_DEBUG_LOG_RF_PRINT
		DNS_DEBUG_LOG_PRINTF("NB Para Check Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_NBIOT_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, STOP_MODE, PARAMETER_CHECKOUT);
		
#ifdef UDP_DEBUG_LOG_RF_PRINT
	#if NBIOT_PRINT_ERROR_CODE_TYPE
		UDP_DEBUG_LOG_PRINTF("NB Para Check Fail ECde %d", NBStatus);
	#else
		UDP_DEBUG_LOG_PRINTF("NB Para Check Fail");
	#endif
#endif
		return;
	}
	
	/* Set System Time */
	RTC_Set_Date(pClient->SocketStack->NBIotStack->Parameter.dataTime.year, pClient->SocketStack->NBIotStack->Parameter.dataTime.month, pClient->SocketStack->NBIotStack->Parameter.dataTime.day);
	RTC_Set_Time(pClient->SocketStack->NBIotStack->Parameter.dataTime.hour, pClient->SocketStack->NBIotStack->Parameter.dataTime.min,   pClient->SocketStack->NBIotStack->Parameter.dataTime.sec);
}

/**********************************************************************************************************
 @Function			void NET_UDP_Event_CreatUDPSocket(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_Event_CreatUDPSocket			: CreatUDPSocket
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_Event_CreatUDPSocket(UDP_ClientsTypeDef* pClient)
{
	UDP_DictateEvent_SetTime(pClient, 30);
	
	/* Creat UDP Socket */
	if (pClient->SocketStack->Open(pClient->SocketStack) == UDP_OK) {
		/* Dictate execute is Success */
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_CONNECT_SERVER, UDP_PROCESS_CREAT_UDP_SOCKET, true);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Ct UDP Ok");
#endif
	}
	else {
		/* Dictate execute is Fail */
		UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_CREAT_UDP_SOCKET);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Ct UDP Fail");
#endif
		return;
	}
}

/**********************************************************************************************************
 @Function			void NET_UDP_Event_ConnectServer(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_Event_ConnectServer			: ConnectServer
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_Event_ConnectServer(UDP_ClientsTypeDef* pClient)
{
#if NETNEWPROTOCAL == NETMQTTSNUDP
	UDP_AUTOCTRL_message_Connect_option options = UDP_AUTOCTRL_Packet_connectData_initializer;
	
	UDP_DictateEvent_SetTime(pClient, 60);
	
	/* Connecting AUTOCTRL Server */
	options.MacSN			= TCFG_EEPROM_Get_MAC_SN();
	options.IMEI			= TCFG_Utility_Get_Nbiot_Imei_String();
	options.IMSI			= TCFG_Utility_Get_Nbiot_Iccid_String();
	if (UDP_AUTOControl_Connect(pClient, &options) != UDP_OK) {
		/* Dictate execute is Fail */
		UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_CONNECT_SERVER);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Cont Fail");
#endif
	}
	else {
		/* Dictate execute is Success */
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_CONNECT_SERVER, true);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Cont Ok");
#endif
	}
#endif

#if NETNEWPROTOCAL == NETMQTTSNSKY
	UDP_SKYNET_message_Connect_option options = UDP_SKYNET_Packet_connectData_initializer;
	
	UDP_DictateEvent_SetTime(pClient, 60);
	
	/* Connecting SkyNet Server */
	options.MacSN				= TCFG_EEPROM_Get_MAC_SN();
	options.ManufacturerCode		= SKYNET_CONNECT_MANUFACTURER;
	options.HardwareVer			= SKYNET_CONNECT_HARDWAREVER;
	options.SoftwareVer			= SKYNET_CONNECT_SOFTWAREVER;
	options.IMEI				= TCFG_Utility_Get_Nbiot_Imei_String();
	options.ICCID				= TCFG_Utility_Get_Nbiot_Iccid_String();
	if (UDP_SkyNet_Connect(pClient, &options) != UDP_OK) {
		/* Dictate execute is Fail */
		UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_CONNECT_SERVER);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Cont Fail");
#endif
	}
	else {
		/* Dictate execute is Success */
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_CONNECT_SERVER, true);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Cont Ok");
#endif
	}
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_Event_SendData(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_Event_SendData				: SendData
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_Event_SendData(UDP_ClientsTypeDef* pClient)
{
#if NETNEWPROTOCAL == NETMQTTSNUDP
	UDP_AUTOCTRL_message_Status_option options = UDP_AUTOCTRL_Packet_statusData_initializer;
	unsigned short len = 0;
	
	Stm32_CalculagraphTypeDef dictateRunTime;
	
	UDP_DictateEvent_SetTime(pClient, 60);
	
	/* Data packets need to be sent*/
	if (NET_UDP_Message_SendDataDequeue((unsigned char *)&options, &len) == true) {
		/* Sending Data AUTOCTRL Server */
		if (UDP_AUTOControl_Status(pClient, &options) != UDP_OK) {
			/* Dictate execute is Fail */
			UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_SEND_DATA);
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("UDP Send Payload Fail");
#endif
		}
		else {
			/* Dictate execute is Success */
			UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_SEND_DATA, true);
			NET_UDP_Message_SendDataOffSet();
#if UDP_MSGID_STATUS_TYPE
			UDP_AUTOControl_GetNextStatusNumber(pClient);
#endif
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("UDP Send Payload Ok");
#endif
		}
	}
	/* No packets need to be sent */
	else {
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SLEEP, UDP_PROCESS_SEND_DATA, true);
		/* Set Heart Duration */
		Stm32_Calculagraph_CountdownSec(&dictateRunTime, 10 * 60);
		pClient->HeartTimer = dictateRunTime;
	}
#endif

#if NETNEWPROTOCAL == NETMQTTSNSKY
	UDP_SKYNET_message_Status_option options = UDP_SKYNET_Packet_statusData_initializer;
	unsigned short len = 0;
	
	UDP_DictateEvent_SetTime(pClient, 60);
	
	/* Data packets need to be sent*/
	if (NET_UDP_Message_SendDataDequeue((unsigned char *)&options, &len) == true) {
		/* Sending Data SkyNet Server */
		options.MacSN			= TCFG_EEPROM_Get_MAC_SN();
		options.ManufacturerCode	= SKYNET_STATUS_MANUFACTURER;
		options.HardwareVer		= SKYNET_STATUS_HARDWAREVER;
		options.SoftwareVer		= SKYNET_STATUS_SOFTWAREVER;
		options.IMEI			= TCFG_Utility_Get_Nbiot_Imei_String();
		options.ICCID			= TCFG_Utility_Get_Nbiot_Iccid_String();
		if (UDP_SkyNet_Status(pClient, &options) != UDP_OK) {
			/* Dictate execute is Fail */
			UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_SEND_DATA);
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("UDP Send Payload Fail");
#endif
		}
		else {
			/* Dictate execute is Success */
			UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_SEND_DATA, true);
			NET_UDP_Message_SendDataOffSet();
#ifdef UDP_DEBUG_LOG_RF_PRINT
			UDP_DEBUG_LOG_PRINTF("UDP Send Payload Ok");
#endif
		}
	}
	/* No packets need to be sent */
	else {
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SLEEP, UDP_PROCESS_SEND_DATA, true);
	}
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_Event_Sleep(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_Event_Sleep					: Sleep
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_Event_Sleep(UDP_ClientsTypeDef* pClient)
{
#if NETNEWPROTOCAL == NETMQTTSNUDP
	UDP_AUTOCTRL_message_Status_option options = UDP_AUTOCTRL_Packet_statusData_initializer;
	unsigned short len = 0;
	
	if (NET_UDP_Message_SendDataDequeue((unsigned char *)&options, &len) == true) {
		/* Data packets need to be sent*/
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_SLEEP, true);
		return;
	}
	
	/* If time to Heart, then send a Heart */
	if (Stm32_Calculagraph_IsExpiredSec(&pClient->HeartTimer) == true) {
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_HEART, UDP_PROCESS_SLEEP, true);
	}
	else {
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SLEEP, UDP_PROCESS_SLEEP, true);
	}
#endif

#if NETNEWPROTOCAL == NETMQTTSNSKY
	UDP_SKYNET_message_Status_option options = UDP_SKYNET_Packet_statusData_initializer;
	unsigned short len = 0;
	
	if (NET_UDP_Message_SendDataDequeue((unsigned char *)&options, &len) == true) {
		/* Data packets need to be sent*/
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SEND_DATA, UDP_PROCESS_SLEEP, true);
		return;
	}
#endif
}

/**********************************************************************************************************
 @Function			void NET_UDP_Event_Heart(UDP_ClientsTypeDef* pClient)
 @Description			NET_UDP_Event_Heart					: Heart
 @Input				pClient							: UDP客户端实例
 @Return				void
**********************************************************************************************************/
void NET_UDP_Event_Heart(UDP_ClientsTypeDef* pClient)
{
	UDP_AUTOCTRL_message_Heart_option options = UDP_AUTOCTRL_Packet_heartData_initializer;
	
	SpotStatusTypedef SpotStatusData;
	
	Stm32_CalculagraphTypeDef dictateRunTime;
	
	UDP_DictateEvent_SetTime(pClient, 60);
	
	Inspect_Message_SpotStatusDequeueEx(&SpotStatusData);
	
	/* Sending Heart AUTOCTRL Server */
	options.MacSN			= TCFG_EEPROM_Get_MAC_SN();
	options.Debuff			= 0x00;
	options.Algorithm		= 0x00;
	options.Heartbeat		= 4 * 60;
	options.SpotStatus		= SpotStatusData.spot_status == 0 ? 0x00 : \
						  SpotStatusData.spot_status == 2 ? 0x00 : \
						  SpotStatusData.spot_status == 1 ? 0x01 : \
						  SpotStatusData.spot_status == 3 ? 0x01 : 0x00;
	options.VbatStatus		= TCFG_Utility_Get_Device_Batt_ShortVal() > 300 ? 0x00 : \
						  TCFG_Utility_Get_Device_Batt_ShortVal() < 270 ? 0x02 : 0x01;
	options.MagneticX		= SpotStatusData.qmc5883lData.X_Now;
	options.MagneticY		= SpotStatusData.qmc5883lData.Y_Now;
	options.MagneticZ		= SpotStatusData.qmc5883lData.Z_Now;
	options.SleepTime		= 0x00;
	options.RSSI			= (char)TCFG_Utility_Get_Nbiot_Rssi_IntVal();
	options.SNR			= TCFG_Utility_Get_Nbiot_RadioSNR() >  -5 ? 0x00 : \
						  TCFG_Utility_Get_Nbiot_RadioSNR() < -50 ? 0x02 : 0x01;
	options.Temperature		= TCFG_Utility_Get_Device_Temperature();
	if (UDP_AUTOControl_Heart(pClient, &options) != UDP_OK) {
		/* Dictate execute is Fail */
		UDP_DictateEvent_FailExecute(pClient, HARDWARE_REBOOT, UDP_PROCESS_CREAT_UDP_SOCKET, UDP_PROCESS_HEART);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Send Heart Fail");
#endif
		return;
	}
	else {
		/* Dictate execute is Success */
		UDP_DictateEvent_SuccessExecute(pClient, UDP_PROCESS_STACK, UDP_PROCESS_SLEEP, UDP_PROCESS_HEART, true);
#ifdef UDP_DEBUG_LOG_RF_PRINT
		UDP_DEBUG_LOG_PRINTF("UDP Send Heart Ok");
#endif
	}
	
	/* Set Heart Duration */
	Stm32_Calculagraph_CountdownSec(&dictateRunTime, 4 * 60 * 60);
	pClient->HeartTimer = dictateRunTime;
}

/********************************************** END OF FLEE **********************************************/
