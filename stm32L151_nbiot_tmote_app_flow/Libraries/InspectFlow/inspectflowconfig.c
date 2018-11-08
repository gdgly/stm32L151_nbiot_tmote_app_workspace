/**
  *********************************************************************************************************
  * @file    inspectflowconfig.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-11-05
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "inspectflowconfig.h"
#include "inspectflowfunc.h"
#include "inspectflowparameter.h"
#include "inspectflowmessageoperate.h"
#include "platform_config.h"
#include "platform_map.h"
#include "stm32l1xx_config.h"
#include "hal_beep.h"
#include "hal_rtc.h"
#include "hal_qmc5883l.h"
#include "radio_rf_app.h"

INSPECT_FlowClientsTypeDef				InspectFlowClientHandler;

/**********************************************************************************************************
 @Function			void Inspect_Flow_Init(void)
 @Description			Inspect_Flow_Init						: 车流量检测算法初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_Init(void)
{
	InspectFlowClientHandler.Configuration.detectMode				= INSPECT_FLOW_DETECT_MODE;						//工作模式
	InspectFlowClientHandler.Configuration.magMeasureFreq			= INSPECT_FLOW_MEASURE_FREQ;						//地磁扫描频率
	InspectFlowClientHandler.Configuration.carinThreshhold			= INSPECT_FLOW_CARIN_THRESHHOLD;					//车辆触发灵敏度
	InspectFlowClientHandler.Configuration.caroutThreshhold		= INSPECT_FLOW_CAROUT_THRESHHOLD;					//车辆离开参数
	InspectFlowClientHandler.Configuration.recalibrationOvernum		= INSPECT_FLOW_RECALIBRA_OVERNUM;					//基准值更新阈值
	InspectFlowClientHandler.Configuration.recalibrationOvertime	= INSPECT_FLOW_RECALIBRA_OVERTIME;					//背景值重新计算时间
	InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt	= INSPECT_FLOW_RECALIBRA_OVERTIMECNT;				//背景重计算累加器
	InspectFlowClientHandler.Configuration.recalibrationBackSeconds	= INSPECT_FLOW_RECALIBRA_BACKSECONDS;				//背景校准之后时间
	InspectFlowClientHandler.Configuration.waitSendHeartbeatMin		= INSPECT_FLOW_WAITSEND_HEARTMIN;					//心跳等待时间
	
	InspectFlowClientHandler.qmc5883lDataReady					= false;										//数据准备标志位
	InspectFlowClientHandler.qmc5883lRunFail					= false;										//运行异常标志位
}

/**********************************************************************************************************
 @Function			void Inspect_Flow_ExistenceDetect(void)
 @Description			Inspect_Flow_ExistenceDetect				: 车流量检测算法处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_ExistenceDetect(void)
{
	INSPECT_FlowStatusTypeDef retStatus = FLOW_CAR_NONE;
	FlowStatusTypeDef FlowStatusData;
	static uint32_t sendFlowTime = 0;
	static uint32_t snedHeartTime = 0;
	static uint32_t carNumberCnt = 0;
	
	if (QMC_DRDY_READ() == 1) Inspect_Flow_ISR();
	
	if (INSPECT_FLOW_Para_GetQmc5883lDataReady()) {
		/* 读取地磁数据 */
		QMC5883L_ReadData_Multiple(&InspectFlowClientHandler.magnetismX, &InspectFlowClientHandler.magnetismY, &InspectFlowClientHandler.magnetismZ);
		/* 数据准备标志清空 */
		INSPECT_FLOW_Para_SetQmc5883lDataReady(false);
		/* 地磁扫描次数累加 */
		InspectFlowClientHandler.DetectCtrl.detectCnt++;
		/* 算法检测 */
		retStatus = INSPECT_FLOW_Func_PassDetect(&InspectFlowClientHandler, InspectFlowClientHandler.magnetismX, InspectFlowClientHandler.magnetismY, InspectFlowClientHandler.magnetismZ);
		
#if INSPECT_FLOW_BEEP_TYPE
		if (retStatus == FLOW_CAR_COME) {
			BEEP_CtrlRepeat_Extend(2, 30, 70);
		}
		else if (retStatus == FLOW_CAR_GO) {
			BEEP_CtrlRepeat_Extend(1, 30, 70);
		}
#endif
		
		if (retStatus == FLOW_CAR_COME) {
			/* 表示检测到有车接近了 */
			if ((INSPECT_FLOW_Para_GetDetectMode() == FLOW_MODE_CAR_COME) || (INSPECT_FLOW_Para_GetDetectMode() == FLOW_MODE_CAR_COME_GO)) {
				FlowStatusData.FlowState				= SPOT_CAR_OCCUPY;
				FlowStatusData.FlowCount				= INSPECT_FLOW_Para_ObtainCarFlowNumber();
				
				FlowStatusData.magnetismX			= INSPECT_FLOW_Para_ObtainMagnetismX();
				FlowStatusData.magnetismY			= INSPECT_FLOW_Para_ObtainMagnetismY();
				FlowStatusData.magnetismZ			= INSPECT_FLOW_Para_ObtainMagnetismZ();
				FlowStatusData.magnetismBackX			= INSPECT_FLOW_Para_ObtainMagnetismBackX();
				FlowStatusData.magnetismBackY			= INSPECT_FLOW_Para_ObtainMagnetismBackY();
				FlowStatusData.magnetismBackZ			= INSPECT_FLOW_Para_ObtainMagnetismBackZ();
				FlowStatusData.magnetismDiff			= INSPECT_FLOW_Para_ObtainMagnetismDiff();
				
				FlowStatusData.timeCounter			= Stm32_GetSecondTick();
				FlowStatusData.unixTime				= RTC_GetUnixTimeToStamp();
				
				Inspect_Message_FlowStatusEnqueue(FlowStatusData);
				
				snedHeartTime = Stm32_GetSecondTick();
			}
		}
		else if (retStatus == FLOW_CAR_GO) {
			/* 表示检测到有车离开了 */
			if ((INSPECT_FLOW_Para_GetDetectMode() == FLOW_MODE_CAR_GO) || (INSPECT_FLOW_Para_GetDetectMode() == FLOW_MODE_CAR_COME_GO)) {
				FlowStatusData.FlowState				= SPOT_CAR_FREE;
				FlowStatusData.FlowCount				= INSPECT_FLOW_Para_ObtainCarFlowNumber();
				
				FlowStatusData.magnetismX			= INSPECT_FLOW_Para_ObtainMagnetismX();
				FlowStatusData.magnetismY			= INSPECT_FLOW_Para_ObtainMagnetismY();
				FlowStatusData.magnetismZ			= INSPECT_FLOW_Para_ObtainMagnetismZ();
				FlowStatusData.magnetismBackX			= INSPECT_FLOW_Para_ObtainMagnetismBackX();
				FlowStatusData.magnetismBackY			= INSPECT_FLOW_Para_ObtainMagnetismBackY();
				FlowStatusData.magnetismBackZ			= INSPECT_FLOW_Para_ObtainMagnetismBackZ();
				FlowStatusData.magnetismDiff			= INSPECT_FLOW_Para_ObtainMagnetismDiff();
				
				FlowStatusData.timeCounter			= Stm32_GetSecondTick();
				FlowStatusData.unixTime				= RTC_GetUnixTimeToStamp();
				
				Inspect_Message_FlowStatusEnqueue(FlowStatusData);
				
				snedHeartTime = Stm32_GetSecondTick();
			}
		}
	}
	
	/* 流量统计模式 */
	if ((INSPECT_FLOW_Para_GetDetectMode() == FLOW_MODE_FLOW) && (Stm32_GetSecondTick() > sendFlowTime + 60 * INSPECT_FLOW_Para_GetWaitSendHeartbeatMin())) {
		if (INSPECT_FLOW_Para_ObtainCarFlowNumber() != carNumberCnt) {
			FlowStatusData.FlowState					= INSPECT_FLOW_Para_ObtainCarFlowStatus() ? SPOT_CAR_OCCUPY : SPOT_CAR_FREE;
			FlowStatusData.FlowCount					= INSPECT_FLOW_Para_ObtainCarFlowNumber();
			
			FlowStatusData.magnetismX				= INSPECT_FLOW_Para_ObtainMagnetismX();
			FlowStatusData.magnetismY				= INSPECT_FLOW_Para_ObtainMagnetismY();
			FlowStatusData.magnetismZ				= INSPECT_FLOW_Para_ObtainMagnetismZ();
			FlowStatusData.magnetismBackX				= INSPECT_FLOW_Para_ObtainMagnetismBackX();
			FlowStatusData.magnetismBackY				= INSPECT_FLOW_Para_ObtainMagnetismBackY();
			FlowStatusData.magnetismBackZ				= INSPECT_FLOW_Para_ObtainMagnetismBackZ();
			FlowStatusData.magnetismDiff				= INSPECT_FLOW_Para_ObtainMagnetismDiff();
			
			FlowStatusData.timeCounter				= Stm32_GetSecondTick();
			FlowStatusData.unixTime					= RTC_GetUnixTimeToStamp();
			
			Inspect_Message_FlowStatusEnqueue(FlowStatusData);
			
			sendFlowTime = Stm32_GetSecondTick();
			snedHeartTime = Stm32_GetSecondTick();
			carNumberCnt = FlowStatusData.FlowCount;
		}
	}
	
	/* 心跳数据包 */
	if (Stm32_GetSecondTick() > (snedHeartTime + 3600 * TCFG_EEPROM_GetNbiotHeart())) {
		Inspect_Message_FlowStatusDequeueEx(&FlowStatusData);
		if (FlowStatusData.timeCounter != 0) {
			FlowStatusData.FlowState					|= 0x02;
			
			FlowStatusData.magnetismX				= INSPECT_FLOW_Para_ObtainMagnetismX();
			FlowStatusData.magnetismY				= INSPECT_FLOW_Para_ObtainMagnetismY();
			FlowStatusData.magnetismZ				= INSPECT_FLOW_Para_ObtainMagnetismZ();
			FlowStatusData.magnetismBackX				= INSPECT_FLOW_Para_ObtainMagnetismBackX();
			FlowStatusData.magnetismBackY				= INSPECT_FLOW_Para_ObtainMagnetismBackY();
			FlowStatusData.magnetismBackZ				= INSPECT_FLOW_Para_ObtainMagnetismBackZ();
			FlowStatusData.magnetismDiff				= INSPECT_FLOW_Para_ObtainMagnetismDiff();
			
			FlowStatusData.timeCounter				= Stm32_GetSecondTick();
			
			Inspect_Message_FlowStatusEnqueue(FlowStatusData);
		}
		snedHeartTime = Stm32_GetSecondTick();
	}
}

/**********************************************************************************************************
 @Function			void Inspect_Flow_InitBackground(void)
 @Description			Inspect_Flow_InitBackground				: 车流量检测算法初始化背景
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_InitBackground(void)
{
	INSPECT_FLOW_Func_InitBackground(&InspectFlowClientHandler);
}

/**********************************************************************************************************
 @Function			void Inspect_Flow_ISR(void)
 @Description			Inspect_Flow_ISR						: 车流量检测算法中断处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_ISR(void)
{
	INSPECT_FLOW_Para_SetQmc5883lDataReady(true);
}

/********************************************** END OF FLEE **********************************************/
