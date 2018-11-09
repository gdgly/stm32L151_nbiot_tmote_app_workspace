#ifndef __INSPECT_FLOW_CONFIG_H
#define   __INSPECT_FLOW_CONFIG_H

#include "sys.h"

#define INSPECT_FLOW_LIB_VERSION			1												//检测算法库

#define INSPECT_FLOW_PROCESS_NUM			100												//处理数据量
#define INSPECT_FLOW_CLUSTER_NUM			2												//集群数据量

#define INSPECT_FLOW_DISTANCE_HIGH			20												//启动分类算法上限值
#define INSPECT_FLOW_CNT_1_MIN			3												//检测为有车状态的最少次数

#define INSPECT_FLOW_CARIN_THRESH_HIGHEST	57
#define INSPECT_FLOW_CAROUT_THRESH_HIGHEST	11

#define INSPECT_FLOW_CARIN_THRESH_HIGH		67
#define INSPECT_FLOW_CAROUT_THRESH_HIGH		13

#define INSPECT_FLOW_CARIN_THRESH_MIDDLE	77
#define INSPECT_FLOW_CAROUT_THRESH_MIDDLE	15

#define INSPECT_FLOW_CARIN_THRESH_LOW		87
#define INSPECT_FLOW_CAROUT_THRESH_LOW		17

#define INSPECT_FLOW_CARIN_THRESH_LOWEST	97
#define INSPECT_FLOW_CAROUT_THRESH_LOWEST	19

#define INSPECT_FLOW_DETECT_MODE			FLOW_MODE_FLOW										//工作模式
#define INSPECT_FLOW_MEASURE_FREQ			MEASURE_FREQ_50HZ									//地磁扫描频率
#define INSPECT_FLOW_CARIN_THRESHHOLD		INSPECT_FLOW_CARIN_THRESH_MIDDLE						//车辆触发灵敏度
#define INSPECT_FLOW_CAROUT_THRESHHOLD		INSPECT_FLOW_CAROUT_THRESH_MIDDLE						//车辆离开参数
#define INSPECT_FLOW_RECALIBRA_OVERNUM		10												//基准值更新阈值
#define INSPECT_FLOW_RECALIBRA_OVERTIME		5												//背景值重新计算时间
#define INSPECT_FLOW_RECALIBRA_OVERTIMECNT	15000											//背景重计算累加器
#define INSPECT_FLOW_RECALIBRA_BACKSECONDS	0												//背景校准之后时间
#define INSPECT_FLOW_WAITSEND_HEARTMIN		15												//心跳等待时间

#define INSPECT_FLOW_BEEP_DISABLE			0
#define INSPECT_FLOW_BEEP_ENABLE			1
#define INSPECT_FLOW_BEEP_TYPE			INSPECT_FLOW_BEEP_ENABLE								//蜂鸣器提示

typedef struct INSPECT_FlowClientsTypeDef	INSPECT_FlowClientsTypeDef;

/* Inspect Flow Status */
typedef enum
{
	FLOW_CAR_NONE						= 0x00,
	FLOW_CAR_COME						= 0x01,
	FLOW_CAR_GO						= 0x02,
	FLOW_CAR_EXIST						= 0x03
}INSPECT_FlowStatusTypeDef;

/* Inspect Flow MeasureFreq */
typedef enum
{
	MEASURE_FREQ_10HZ					= 0x00,
	MEASURE_FREQ_50HZ					= 0x01,
	MEASURE_FREQ_100HZ					= 0x02,
	MEASURE_FREQ_200HZ					= 0x03
}INSPECT_FlowMeasureFreqTypeDef;

/* Inspect Flow DetectMode */
typedef enum
{
	FLOW_MODE_CLOSED					= 0x00,
	FLOW_MODE_FLOW						= 0x01,
	FLOW_MODE_CAR_COME					= 0x02,
	FLOW_MODE_CAR_GO					= 0x03,
	FLOW_MODE_CAR_COME_GO				= 0x04
}INSPECT_FlowDetectModeTypeDef;

/* Inspect Flow DetectData */
typedef struct
{
	unsigned short						sum:15;											//数据和
	unsigned char						flag:1;											//标志位
}INSPECT_FlowDetectDataTypeDef;

/* Inspect Flow DetectCtrl */
typedef struct
{
	unsigned char						minPos;											//数组最小值位置
	unsigned char						maxPos;											//数组最大值位置
	unsigned char						dataIndex;										//当前最新得到值位置
	unsigned short						detect_nS0;										//连续状态0个数
	unsigned short						detect_nS1;										//连续状态1个数
	unsigned int						detectCnt;										//地磁扫描次数
	unsigned char						bInStatus;										//车辆状态值 1 : CarIn 0 : CarOut
	unsigned short						lastCenter;										//上次质心值
}INSPECT_FlowDetectCtrlTypeDef;

/* Inspect Flow ClusterGroup */
typedef struct
{
	unsigned short						center;
	unsigned char						groupSize;
}INSPECT_FlowClusterGroupTypeDef;

/* Inspect Flow MagVal */
typedef struct
{
	int16_t							x_now;											//X轴当前磁场值
	int16_t							y_now;											//Y轴当前磁场值
	int16_t							z_now;											//Z轴当前磁场值
	
	int16_t							x_back;											//X轴背景磁场值
	int16_t							y_back;											//Y轴背景磁场值
	int16_t							z_back;											//Z轴背景磁场值
	
	int32_t							x_sum;											//X轴地磁值累加
	int32_t							y_sum;											//Y轴地磁值累加
	int32_t							z_sum;											//Z轴地磁值累加
	int16_t							sum_num;											//累加地磁值数量
	
	int32_t							x_back_sum;										//X轴稳定背景值累加
	int32_t							y_back_sum;										//Y轴稳定背景值累加
	int32_t							z_back_sum;										//Z轴稳定背景值累加
	int16_t							sum_back_num;										//累加稳定背景值数量
}INSPECT_FlowMagnetismValTypeDef;

/* Inspect Flow Configuration */
typedef struct
{
	INSPECT_FlowDetectModeTypeDef			detectMode;										//工作模式
	INSPECT_FlowMeasureFreqTypeDef		magMeasureFreq;									//地磁扫描频率
	unsigned char						carinThreshhold;									//车辆进入参数
	unsigned char						caroutThreshhold;									//车辆离开参数
	unsigned char						recalibrationOvernum:4;								//微小变化重计算次数
	unsigned char						recalibrationOvertime:4;								//激烈变化重计算时间
	unsigned int						recalibrationOvertimeCnt;							//背景重计算累加器
	unsigned int						recalibrationBackSeconds;							//背景校准之后时间
	unsigned int						waitSendHeartbeatMin;								//心跳等待时间
}INSPECT_FlowConfigurationTypeDef;

/* Inspect Flow Parameter */
typedef struct
{
	unsigned short						carNumber;										//车辆次数统计
	unsigned short						magnetismDiff;										//变化值
	int16_t							magnetismBackX;									//x轴背景值
	int16_t							magnetismBackY;									//Y轴背景值
	int16_t							magnetismBackZ;									//Z轴背景值
}INSPECT_FlowParameterTypeDef;

/* Inspect Flow Clients */
struct INSPECT_FlowClientsTypeDef
{
	int16_t							magnetismX;										//x轴磁场值
	int16_t							magnetismY;										//y轴磁场值
	int16_t							magnetismZ;										//z轴磁场值
	
	INSPECT_FlowDetectDataTypeDef			DetectData[INSPECT_FLOW_PROCESS_NUM];					//处理数据
	INSPECT_FlowDetectCtrlTypeDef			DetectCtrl;										//处理控制
	INSPECT_FlowClusterGroupTypeDef		ClusterGroup[INSPECT_FLOW_CLUSTER_NUM];					//集群数据
	INSPECT_FlowMagnetismValTypeDef		MagnetismVal;										//地磁数据
	INSPECT_FlowConfigurationTypeDef		Configuration;										//配置信息
	INSPECT_FlowParameterTypeDef			Parameter;										//参数信息
	
	bool								qmc5883lDataReady;									//数据准备标志位
	bool								qmc5883lRunFail;									//运行异常标志位
};

extern INSPECT_FlowClientsTypeDef			InspectFlowClientHandler;

void Inspect_Flow_Init(void);																//车流量检测算法初始化
void Inspect_Flow_ExistenceDetect(void);													//车流量检测算法处理
void Inspect_Flow_AddRecalibrationBackSeconds(void);											//车流量检测算法学习时间累加
void Inspect_Flow_InitBackground(void);														//车流量检测算法初始化背景
void Inspect_Flow_ISR(void);																//车流量检测算法中断处理

#endif /* __INSPECT_FLOW_CONFIG_H */
