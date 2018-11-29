/**
  *********************************************************************************************************
  * @file    inspectflowparameter.c
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

#include "inspectflowparameter.h"
#include "platform_config.h"
#include "platform_map.h"

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetDetectMode(unsigned char detectMode)
 @Description			INSPECT_FLOW_Para_SetDetectMode				: 设置detectMode工作模式
 @Input				detectMode
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetDetectMode(unsigned char detectMode)
{
	detectMode = (detectMode > FLOW_MODE_CAR_COME_GO) ? INSPECT_FLOW_DETECT_MODE : detectMode;
	
	InspectFlowClientHandler.Configuration.detectMode = (INSPECT_FlowDetectModeTypeDef)detectMode;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetDetectMode(void)
 @Description			INSPECT_FLOW_Para_GetDetectMode				: 读取detectMode工作模式
 @Input				void
 @Return				detectMode
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetDetectMode(void)
{
	return InspectFlowClientHandler.Configuration.detectMode;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetMagMeasureFreq(unsigned char magFreq)
 @Description			INSPECT_FLOW_Para_SetMagMeasureFreq			: 设置magFreq地磁扫描频率
 @Input				magFreq
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetMagMeasureFreq(unsigned char magFreq)
{
	magFreq = (magFreq > MEASURE_FREQ_200HZ) ? INSPECT_FLOW_MEASURE_FREQ : magFreq;
	
	InspectFlowClientHandler.Configuration.magMeasureFreq = (INSPECT_FlowMeasureFreqTypeDef)magFreq;
	
	switch (InspectFlowClientHandler.Configuration.magMeasureFreq)
	{
	case MEASURE_FREQ_10HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 600 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_50HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 3000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_100HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 6000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_200HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 12000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	}
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetMagMeasureFreq(void)
 @Description			INSPECT_FLOW_Para_GetMagMeasureFreq			: 读取magFreq地磁扫描频率
 @Input				void
 @Return				magFreq
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetMagMeasureFreq(void)
{
	return InspectFlowClientHandler.Configuration.magMeasureFreq;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetCarinThreshhold(unsigned char carinThreshhold)
 @Description			INSPECT_FLOW_Para_SetCarinThreshhold			: 设置carinThreshhold车辆触发灵敏度
 @Input				carinThreshhold
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetCarinThreshhold(unsigned char carinThreshhold)
{
	InspectFlowClientHandler.Configuration.carinThreshhold = carinThreshhold;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetCarinThreshhold(void)
 @Description			INSPECT_FLOW_Para_GetCarinThreshhold			: 读取carinThreshhold车辆触发灵敏度
 @Input				void
 @Return				carinThreshhold
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetCarinThreshhold(void)
{
	return InspectFlowClientHandler.Configuration.carinThreshhold;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetCaroutThreshhold(unsigned char caroutThreshhold)
 @Description			INSPECT_FLOW_Para_SetCaroutThreshhold			: 设置caroutThreshhold车辆离开参数
 @Input				caroutThreshhold
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetCaroutThreshhold(unsigned char caroutThreshhold)
{
	InspectFlowClientHandler.Configuration.caroutThreshhold = caroutThreshhold;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetCaroutThreshhold(void)
 @Description			INSPECT_FLOW_Para_GetCaroutThreshhold			: 读取caroutThreshhold车辆离开参数
 @Input				void
 @Return				caroutThreshhold
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetCaroutThreshhold(void)
{
	return InspectFlowClientHandler.Configuration.caroutThreshhold;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetRecalibrationOvernum(unsigned char recalibrationOvernum)
 @Description			INSPECT_FLOW_Para_SetRecalibrationOvernum		: 设置recalibrationOvernum基准值更新阈值
 @Input				recalibrationOvernum
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetRecalibrationOvernum(unsigned char recalibrationOvernum)
{
	recalibrationOvernum = (recalibrationOvernum > 15) ? 15 : recalibrationOvernum;
	
	InspectFlowClientHandler.Configuration.recalibrationOvernum = recalibrationOvernum;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetRecalibrationOvernum(void)
 @Description			INSPECT_FLOW_Para_GetRecalibrationOvernum		: 读取recalibrationOvernum基准值更新阈值
 @Input				void
 @Return				recalibrationOvernum
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetRecalibrationOvernum(void)
{
	return InspectFlowClientHandler.Configuration.recalibrationOvernum;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetRecalibrationOvertime(unsigned char recalibrationOvertime)
 @Description			INSPECT_FLOW_Para_SetRecalibrationOvertime		: 设置recalibrationOvertime背景值重新计算时间
 @Input				recalibrationOvertime
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetRecalibrationOvertime(unsigned char recalibrationOvertime)
{
	recalibrationOvertime = (recalibrationOvertime > 15) ? 15 : recalibrationOvertime;
	
	InspectFlowClientHandler.Configuration.recalibrationOvertime = recalibrationOvertime;
	
	switch (InspectFlowClientHandler.Configuration.magMeasureFreq)
	{
	case MEASURE_FREQ_10HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 600 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_50HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 3000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_100HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 6000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	
	case MEASURE_FREQ_200HZ:
		InspectFlowClientHandler.Configuration.recalibrationOvertimeCnt = 12000 * InspectFlowClientHandler.Configuration.recalibrationOvertime;
		break;
	}
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_GetRecalibrationOvertime(void)
 @Description			INSPECT_FLOW_Para_GetRecalibrationOvertime		: 读取recalibrationOvertime背景值重新计算时间
 @Input				void
 @Return				recalibrationOvertime
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_GetRecalibrationOvertime(void)
{
	return InspectFlowClientHandler.Configuration.recalibrationOvertime;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetWaitSendHeartbeatMin(unsigned int waitSendHeartbeatMin)
 @Description			INSPECT_FLOW_Para_SetWaitSendHeartbeatMin		: 设置waitSendHeartbeatMin心跳等待时间
 @Input				waitSendHeartbeatMin
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetWaitSendHeartbeatMin(unsigned int waitSendHeartbeatMin)
{
	waitSendHeartbeatMin = (waitSendHeartbeatMin > 12 * 60) ? 12 * 60 : waitSendHeartbeatMin;
	
	InspectFlowClientHandler.Configuration.waitSendHeartbeatMin = waitSendHeartbeatMin;
}

/**********************************************************************************************************
 @Function			unsigned int INSPECT_FLOW_Para_GetWaitSendHeartbeatMin(void)
 @Description			INSPECT_FLOW_Para_GetWaitSendHeartbeatMin		: 读取waitSendHeartbeatMin心跳等待时间
 @Input				void
 @Return				waitSendHeartbeatMin
**********************************************************************************************************/
unsigned int INSPECT_FLOW_Para_GetWaitSendHeartbeatMin(void)
{
	return InspectFlowClientHandler.Configuration.waitSendHeartbeatMin;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetWaitSendFlowCarCount(unsigned int waitSendFlowCarCount)
 @Description			INSPECT_FLOW_Para_SetWaitSendFlowCarCount		: 设置waitSendFlowCarCount统计车辆发送次数
 @Input				waitSendFlowCarCount
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetWaitSendFlowCarCount(unsigned int waitSendFlowCarCount)
{
	waitSendFlowCarCount = (waitSendFlowCarCount > 65535) ? 65535 : waitSendFlowCarCount;
	
	InspectFlowClientHandler.Configuration.waitSendFlowCnt = waitSendFlowCarCount;
}

/**********************************************************************************************************
 @Function			unsigned int INSPECT_FLOW_Para_GetWaitSendFlowCarCount(void)
 @Description			INSPECT_FLOW_Para_GetWaitSendFlowCarCount		: 读取waitSendFlowCarCount统计车辆发送次数
 @Input				void
 @Return				waitSendFlowCarCount
**********************************************************************************************************/
unsigned int INSPECT_FLOW_Para_GetWaitSendFlowCarCount(void)
{
	return InspectFlowClientHandler.Configuration.waitSendFlowCnt;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetQmc5883lDataReady(bool qmc5883lDataReady)
 @Description			INSPECT_FLOW_Para_SetQmc5883lDataReady			: 设置qmc5883lDataReady数据准备标志位
 @Input				qmc5883lDataReady
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetQmc5883lDataReady(bool qmc5883lDataReady)
{
	InspectFlowClientHandler.qmc5883lDataReady = qmc5883lDataReady;
}

/**********************************************************************************************************
 @Function			bool INSPECT_FLOW_Para_GetQmc5883lDataReady(void)
 @Description			INSPECT_FLOW_Para_GetQmc5883lDataReady			: 读取qmc5883lDataReady数据准备标志位
 @Input				void
 @Return				qmc5883lDataReady
**********************************************************************************************************/
bool INSPECT_FLOW_Para_GetQmc5883lDataReady(void)
{
	return InspectFlowClientHandler.qmc5883lDataReady;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetQmc5883lRunFail(bool qmc5883lRunFail)
 @Description			INSPECT_FLOW_Para_SetQmc5883lRunFail			: 设置qmc5883lRunFail运行异常标志位
 @Input				qmc5883lRunFail
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetQmc5883lRunFail(bool qmc5883lRunFail)
{
	InspectFlowClientHandler.qmc5883lRunFail = qmc5883lRunFail;
}

/**********************************************************************************************************
 @Function			bool INSPECT_FLOW_Para_GetQmc5883lRunFail(void)
 @Description			INSPECT_FLOW_Para_GetQmc5883lRunFail			: 读取qmc5883lRunFaily运行异常标志位
 @Input				void
 @Return				qmc5883lRunFail
**********************************************************************************************************/
bool INSPECT_FLOW_Para_GetQmc5883lRunFail(void)
{
	return InspectFlowClientHandler.qmc5883lRunFail;
}

/**********************************************************************************************************
 @Function			void INSPECT_FLOW_Para_SetSavedSensitivity(unsigned char Sens)
 @Description			INSPECT_FLOW_Para_SetSavedSensitivity			: 设置Sens传感器灵敏度
 @Input				Sens
 @Return				void
**********************************************************************************************************/
void INSPECT_FLOW_Para_SetSavedSensitivity(unsigned char Sens)
{
	switch (Sens)
	{
	case SENSE_HIGHEST:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_HIGHEST;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_HIGHEST;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_HIGHEST);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_HIGHEST);
		break;
	
	case SENSE_HIGH:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_HIGH;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_HIGH;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_HIGH);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_HIGH);
		break;
	
	case SENSE_MIDDLE:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_MIDDLE;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_MIDDLE;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_MIDDLE);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_MIDDLE);
		break;
	
	case SENSE_LOW:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_LOW;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_LOW;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_LOW);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_LOW);
		break;
	
	case SENSE_LOWEST:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_LOWEST;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_LOWEST;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_LOWEST);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_LOWEST);
		break;
	
	default:
		TCFG_SystemData.FlowCarinThresh = INSPECT_FLOW_CARIN_THRESH_MIDDLE;
		TCFG_EEPROM_SetFlowCarinThresh(TCFG_SystemData.FlowCarinThresh);
		TCFG_SystemData.FlowCaroutThresh = INSPECT_FLOW_CAROUT_THRESH_MIDDLE;
		TCFG_EEPROM_SetFlowCaroutThresh(TCFG_SystemData.FlowCaroutThresh);
		INSPECT_FLOW_Para_SetCarinThreshhold(INSPECT_FLOW_CARIN_THRESH_MIDDLE);
		INSPECT_FLOW_Para_SetCaroutThreshhold(INSPECT_FLOW_CAROUT_THRESH_MIDDLE);
		break;
	}
}


/**********************************************************************************************************
 @Function			unsigned int INSPECT_FLOW_Para_ObtainMagnetismScanCnt(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismScanCnt		: 获取MagnetismScanCnt地磁扫描次数
 @Input				void
 @Return				MagnetismScanCnt
**********************************************************************************************************/
unsigned int INSPECT_FLOW_Para_ObtainMagnetismScanCnt(void)
{
	return InspectFlowClientHandler.DetectCtrl.detectCnt;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_ObtainCarFlowStatus(void)
 @Description			INSPECT_FLOW_Para_ObtainCarFlowStatus			: 获取CarFlowStatus车辆状态值
 @Input				void
 @Return				CarFlowStatus
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Para_ObtainCarFlowStatus(void)
{
	return InspectFlowClientHandler.DetectCtrl.bInStatus;
}

/**********************************************************************************************************
 @Function			unsigned short INSPECT_FLOW_Para_ObtainCarFlowNumber(void)
 @Description			INSPECT_FLOW_Para_ObtainCarFlowNumber			: 获取CarFlowNumber车辆数
 @Input				void
 @Return				CarFlowNumber
**********************************************************************************************************/
unsigned short INSPECT_FLOW_Para_ObtainCarFlowNumber(void)
{
	return InspectFlowClientHandler.Parameter.carNumber;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Para_ObtainMagnetismDiff(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismDiff			: 获取MagnetismDiff地磁变化值
 @Input				void
 @Return				MagnetismDiff
**********************************************************************************************************/
unsigned short INSPECT_FLOW_Para_ObtainMagnetismDiff(void)
{
	return InspectFlowClientHandler.Parameter.magnetismDiff;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismX(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismX				: 获取MagnetismX地磁X轴值
 @Input				void
 @Return				MagnetismX
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismX(void)
{
	return InspectFlowClientHandler.magnetismX;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismY(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismY				: 获取MagnetismY地磁Y轴值
 @Input				void
 @Return				MagnetismY
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismY(void)
{
	return InspectFlowClientHandler.magnetismY;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismZ(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismZ				: 获取MagnetismZ地磁Z轴值
 @Input				void
 @Return				MagnetismZ
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismZ(void)
{
	return InspectFlowClientHandler.magnetismZ;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismBackX(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismBackX			: 获取MagnetismBackX地磁X轴背景值
 @Input				void
 @Return				MagnetismBackX
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismBackX(void)
{
	InspectFlowClientHandler.Parameter.magnetismBackX = InspectFlowClientHandler.MagnetismVal.x_back;
	return InspectFlowClientHandler.Parameter.magnetismBackX;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismBackY(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismBackY			: 获取MagnetismBackY地磁Y轴背景值
 @Input				void
 @Return				MagnetismBackY
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismBackY(void)
{
	InspectFlowClientHandler.Parameter.magnetismBackY = InspectFlowClientHandler.MagnetismVal.y_back;
	return InspectFlowClientHandler.Parameter.magnetismBackY;
}

/**********************************************************************************************************
 @Function			signed short INSPECT_FLOW_Para_ObtainMagnetismBackZ(void)
 @Description			INSPECT_FLOW_Para_ObtainMagnetismBackZ			: 获取MagnetismBackZ地磁Z轴背景值
 @Input				void
 @Return				MagnetismBackZ
**********************************************************************************************************/
signed short INSPECT_FLOW_Para_ObtainMagnetismBackZ(void)
{
	InspectFlowClientHandler.Parameter.magnetismBackZ = InspectFlowClientHandler.MagnetismVal.z_back;
	return InspectFlowClientHandler.Parameter.magnetismBackZ;
}

/********************************************** END OF FLEE **********************************************/
