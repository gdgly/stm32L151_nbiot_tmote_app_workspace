#ifndef __INSPECT_FLOW_PARAMETER_H
#define   __INSPECT_FLOW_PARAMETER_H

#include "sys.h"
#include "inspectflowconfig.h"

void			INSPECT_FLOW_Para_SetDetectMode(unsigned char detectMode);							//设置detectMode工作模式
unsigned char	INSPECT_FLOW_Para_GetDetectMode(void);											//读取detectMode工作模式

void			INSPECT_FLOW_Para_SetMagMeasureFreq(unsigned char magFreq);							//设置magFreq地磁扫描频率
unsigned char	INSPECT_FLOW_Para_GetMagMeasureFreq(void);										//读取magFreq地磁扫描频率

void			INSPECT_FLOW_Para_SetCarinThreshhold(unsigned char carinThreshhold);					//设置carinThreshhold车辆触发灵敏度
unsigned char	INSPECT_FLOW_Para_GetCarinThreshhold(void);										//读取carinThreshhold车辆触发灵敏度

void			INSPECT_FLOW_Para_SetCaroutThreshhold(unsigned char caroutThreshhold);				//设置caroutThreshhold车辆离开参数
unsigned char	INSPECT_FLOW_Para_GetCaroutThreshhold(void);										//读取caroutThreshhold车辆离开参数

void			INSPECT_FLOW_Para_SetRecalibrationOvernum(unsigned char recalibrationOvernum);			//设置recalibrationOvernum基准值更新阈值
unsigned char	INSPECT_FLOW_Para_GetRecalibrationOvernum(void);									//读取recalibrationOvernum基准值更新阈值

void			INSPECT_FLOW_Para_SetRecalibrationOvertime(unsigned char recalibrationOvertime);		//设置recalibrationOvertime背景值重新计算时间
unsigned char	INSPECT_FLOW_Para_GetRecalibrationOvertime(void);									//读取recalibrationOvertime背景值重新计算时间

void			INSPECT_FLOW_Para_SetWaitSendHeartbeatMin(unsigned int waitSendHeartbeatMin);			//设置waitSendHeartbeatMin心跳等待时间
unsigned int	INSPECT_FLOW_Para_GetWaitSendHeartbeatMin(void);									//读取waitSendHeartbeatMin心跳等待时间

void			INSPECT_FLOW_Para_SetQmc5883lDataReady(bool qmc5883lDataReady);						//设置qmc5883lDataReady数据准备标志位
bool			INSPECT_FLOW_Para_GetQmc5883lDataReady(void);									//读取qmc5883lDataReady数据准备标志位

void			INSPECT_FLOW_Para_SetQmc5883lRunFail(bool qmc5883lRunFail);							//设置qmc5883lRunFail运行异常标志位
bool			INSPECT_FLOW_Para_GetQmc5883lRunFail(void);										//读取qmc5883lRunFaily运行异常标志位

void			INSPECT_FLOW_Para_SetSavedSensitivity(unsigned char Sens);							//设置Sens传感器灵敏度

unsigned int	INSPECT_FLOW_Para_ObtainMagnetismScanCnt(void);									//获取MagnetismScanCnt地磁扫描次数
unsigned char	INSPECT_FLOW_Para_ObtainCarFlowStatus(void);										//获取CarFlowStatus车辆状态值
unsigned short	INSPECT_FLOW_Para_ObtainCarFlowNumber(void);										//获取CarFlowNumber车辆数
unsigned short INSPECT_FLOW_Para_ObtainMagnetismDiff(void);										//获取MagnetismDiff地磁变化值
signed short	INSPECT_FLOW_Para_ObtainMagnetismX(void);										//获取MagnetismX地磁X轴值
signed short	INSPECT_FLOW_Para_ObtainMagnetismY(void);										//获取MagnetismY地磁Y轴值
signed short	INSPECT_FLOW_Para_ObtainMagnetismZ(void);										//获取MagnetismY地磁Z轴值
signed short	INSPECT_FLOW_Para_ObtainMagnetismBackX(void);									//获取MagnetismBackX地磁X轴背景值
signed short	INSPECT_FLOW_Para_ObtainMagnetismBackY(void);									//获取MagnetismBackY地磁Y轴背景值
signed short	INSPECT_FLOW_Para_ObtainMagnetismBackZ(void);									//获取MagnetismBackZ地磁Z轴背景值

#endif /* __INSPECT_FLOW_PARAMETER_H */
