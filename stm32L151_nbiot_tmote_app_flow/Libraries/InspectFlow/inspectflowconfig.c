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
#include "platform_config.h"
#include "platform_map.h"
#include "hal_beep.h"
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
	InspectFlowClientHandler.Configuration.magMeasureFreq			= INSPECT_FLOW_MEASURE_FREQ;						//地磁扫描频率
	InspectFlowClientHandler.Configuration.carinThreshhold			= INSPECT_FLOW_CARIN_THRESHHOLD;					//车辆触发灵敏度
	InspectFlowClientHandler.Configuration.caroutThreshhold		= INSPECT_FLOW_CAROUT_THRESHHOLD;					//车辆离开参数
	InspectFlowClientHandler.Configuration.recalibrationOvernum		= INSPECT_FLOW_RECALIBRA_OVERNUM;					//基准值更新阈值
	InspectFlowClientHandler.Configuration.recalibrationOvertime	= INSPECT_FLOW_RECALIBRA_OVERTIME;					//背景值重新计算时间
	InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt	= INSPECT_FLOW_RECALIBRA_OVERTIMECNT;				//背景重计算累加器
	InspectFlowClientHandler.Configuration.recalibrationBackSeconds	= INSPECT_FLOW_RECALIBRA_BACKSECONDS;				//背景校准之后时间
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void Inspect_Flow_ExistenceDetect(void)
 @Description			Inspect_Flow_ExistenceDetect				: 车流量检测算法处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_ExistenceDetect(void)
{
	
	
	
}





























/********************************************** END OF FLEE **********************************************/
