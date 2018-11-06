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

INSPECT_FlowClientsTypeDef				InspectFlowClientHandler;

/**********************************************************************************************************
 @Function			void Inspect_Flow_Init(void)
 @Description			Inspect_Flow_Init						: 车流量检测算法初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Inspect_Flow_Init(void)
{
	InspectFlowClientHandler.Configuration.magMeasureFreq			= MEASURE_FREQ_50HZ;							//地磁扫描频率
	InspectFlowClientHandler.Configuration.carinThreshhold			= 77;										//车辆触发灵敏度
	InspectFlowClientHandler.Configuration.caroutThreshhold		= 15;										//车辆离开参数
	InspectFlowClientHandler.Configuration.recalibrationOvernum		= 10;										//基准值更新阈值
	InspectFlowClientHandler.Configuration.recalibrationOvertime	= 5;											//背景值重新计算时间
	
	
	
	
	
	
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
