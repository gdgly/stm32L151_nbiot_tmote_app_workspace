/**
  *********************************************************************************************************
  * @file    inspectflowfunc.c
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

#include "inspectflowfunc.h"
#include "platform_config.h"
#include "platform_map.h"
#include <stdlib.h>

/**********************************************************************************************************
 @Function			INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_PassDetect(INSPECT_FlowClientsTypeDef* pClient, int16_t x_mag, int16_t y_mag, int16_t z_mag)
 @Description			INSPECT_FLOW_Func_PassDetect				: 车辆检测
 @Input				pClient								: InspectFlowHander
					x_mag								: X轴磁场值
					y_mag								: Y轴磁场值
					z_mag								: Z轴磁场值
 @Return				INSPECT_FlowStatusTypeDef				: 检测状态
**********************************************************************************************************/
INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_PassDetect(INSPECT_FlowClientsTypeDef* pClient, int16_t x_mag, int16_t y_mag, int16_t z_mag)
{
	INSPECT_FlowStatusTypeDef retStatus = FLOW_CAR_NONE;
	u16 threshhold = pClient->Configuration.carinThreshhold;
	s32 magSumS32 = 0;
	u16 magSumU16 = 0;
	u16 diff = 0;
	
	pClient->MagnetismVal.x_now = x_mag;
	pClient->MagnetismVal.y_now = y_mag;
	pClient->MagnetismVal.z_now = z_mag;
	
	/* 车辆判断, 任意一个基准值如果有不为0的话, 就进行计算 */
	if ((pClient->MagnetismVal.x_back != 0) || (pClient->MagnetismVal.y_back != 0) || (pClient->MagnetismVal.z_back != 0)) {
		/* 已经有基准值 */
		/* 获取地磁平方和 */
		magSumS32 = (INSPECT_FLOW_X_SQUARE + INSPECT_FLOW_Y_SQUARE + INSPECT_FLOW_Z_SQUARE + 8) >> 4;
		
		if (magSumS32 > 0xFFFF) magSumU16 = 0xFFFF;
		else magSumU16 = magSumS32;
		
		/* 指针归0 */
		if (pClient->DetectCtrl.dataIndex >= INSPECT_FLOW_PROCESS_NUM) {
			pClient->DetectCtrl.dataIndex = 0;
		}
		
		if ((pClient->DetectCtrl.minPos >= INSPECT_FLOW_PROCESS_NUM) || (pClient->DetectCtrl.maxPos >= INSPECT_FLOW_PROCESS_NUM)) {
			pClient->DetectCtrl.minPos = pClient->DetectCtrl.dataIndex;
			pClient->DetectCtrl.maxPos = pClient->DetectCtrl.dataIndex;
		}
		
		/* 限制过快增长 */
		if (pClient->DetectCtrl.bInStatus) {
			/* 车辆进入状态 */
			if (magSumU16 > (pClient->DetectCtrl.lastCenter + threshhold)) {
				magSumU16 = pClient->DetectCtrl.lastCenter + threshhold;
			}
		}
		else {
			/* 车辆离开状态 */
			if (magSumU16 > (pClient->DetectCtrl.lastCenter + 3 * threshhold / 2)) {
				magSumU16 = pClient->DetectCtrl.lastCenter + 3 * threshhold / 2;
			}
		}
		
		/** 当前值比原来的最大值小, 原来最大值的位置就是当前要替换掉的位置
		  * 当前值比原来的最小值大, 原来最小值的位置就是当前要替换掉的位置
		  * 最大值的位置等于最小值的位置
		  */
		if (((INSPECT_FLOW_MAX_POS == INSPECT_FLOW_INDEX) && (magSumU16 < INSPECT_FLOW_MAX_SUM)) || \
		    ((INSPECT_FLOW_MIN_POS == INSPECT_FLOW_INDEX) && (magSumU16 > INSPECT_FLOW_MIN_SUM)) || \
		    (INSPECT_FLOW_MAX_POS == INSPECT_FLOW_MIN_POS)) {
			/* 重新计算最大值和最小值的位置 */
			INSPECT_FLOW_INDEX_SUM = magSumU16;
			
			for (unsigned char i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
				if (pClient->DetectData[i].sum < INSPECT_FLOW_MIN_SUM) {
					INSPECT_FLOW_MIN_POS = i;
				}
				else if (pClient->DetectData[i].sum > INSPECT_FLOW_MAX_SUM) {
					INSPECT_FLOW_MAX_POS = i;
				}
			}
		}
		else {
			/* 当前的值比原来的最大值还要大, 则最大值的位置更新为当前值的位置 */
			if (magSumU16 > INSPECT_FLOW_MAX_SUM) {
				INSPECT_FLOW_MAX_POS = INSPECT_FLOW_INDEX;
			}
			/* 当前的值比原来的最小值还要小, 则最小值的位置更新为当前值的位置 */
			else if (magSumU16 < INSPECT_FLOW_MIN_SUM) {
				INSPECT_FLOW_MIN_POS = INSPECT_FLOW_INDEX;
			}
			INSPECT_FLOW_INDEX_SUM = magSumU16;
		}
		
		if (magSumU16 < threshhold) {
			pClient->DetectData[INSPECT_FLOW_INDEX].flag = 0;
			diff = 0;
			pClient->DetectCtrl.lastCenter = INSPECT_FLOW_MIN_SUM;
		}
		else {
			/* K-Means算法, 重新定义质心 */
			
			/* 限制增长过快 */
			pClient->ClusterGroup[0].center = INSPECT_FLOW_MIN_SUM + ((INSPECT_FLOW_MAX_SUM - INSPECT_FLOW_MIN_SUM) >> 2);
			pClient->ClusterGroup[1].center = INSPECT_FLOW_MAX_SUM - ((INSPECT_FLOW_MAX_SUM - INSPECT_FLOW_MIN_SUM) >> 2);
			
			/* 最小值和最大值之差大于阈值才有必要分类 */
			if ((INSPECT_FLOW_MAX_SUM - INSPECT_FLOW_MIN_SUM) >= INSPECT_FLOW_DISTANCE_HIGH) {
				for (unsigned char i = 1; i < (INSPECT_FLOW_PROCESS_NUM / 2); i++) {
					if (INSPECT_FLOW_Func_KmeansAllocate(pClient) == 1) break;
				}
			}
			
			/* 特殊情况调整状态 */
			diff = abs(pClient->ClusterGroup[0].center - pClient->ClusterGroup[1].center);
			
			if (diff < threshhold) {
				/* 如果没达到调整状态的变化值则保持同前面一致 */
				if (pClient->DetectCtrl.bInStatus)
					pClient->DetectData[INSPECT_FLOW_INDEX].flag = 1;
				else
					pClient->DetectData[INSPECT_FLOW_INDEX].flag = 0;
			}
			else {
				/* 如果分类后0类大于1类, 作为异常处理 */
				if (pClient->ClusterGroup[0].center > pClient->ClusterGroup[1].center) {
					for (unsigned char i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
						if (pClient->DetectData[i].flag == 0)
							pClient->DetectData[i].flag = 1;
						else
							pClient->DetectData[i].flag = 0;
					}
					pClient->ClusterGroup[0].center = pClient->ClusterGroup[1].center;
				}
			}
			
			pClient->DetectCtrl.lastCenter = pClient->ClusterGroup[0].center;
		}
		
		/* 状态机算法 */
		retStatus = INSPECT_FLOW_Func_CheckStatus(pClient, INSPECT_FLOW_INDEX);
		INSPECT_FLOW_INDEX++;
		if (INSPECT_FLOW_INDEX >= INSPECT_FLOW_PROCESS_NUM) INSPECT_FLOW_INDEX = 0;
	}
	else {
		/* 还未有基准值 */
		pClient->MagnetismVal.x_back = pClient->MagnetismVal.x_now;
		pClient->MagnetismVal.y_back = pClient->MagnetismVal.y_now;
		pClient->MagnetismVal.z_back = pClient->MagnetismVal.z_now;
	}
	
	/* 背景值计算 */
	if (INSPECT_FLOW_Func_CalculateBackground(pClient)) {
		/* 更新计算数组 */
		for (unsigned char i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
			pClient->DetectData[i].sum = 0;
		}
		INSPECT_FLOW_MIN_POS = INSPECT_FLOW_MAX_POS = INSPECT_FLOW_INDEX;
		pClient->DetectCtrl.lastCenter = 0;
	}
	
	return retStatus;
}

/**********************************************************************************************************
 @Function			INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_CheckStatus(INSPECT_FlowClientsTypeDef* pClient, unsigned char index)
 @Description			INSPECT_FLOW_Func_CheckStatus				: 检查状态
 @Input				pClient								: InspectFlowHander
					index								: 数据标号
 @Return				INSPECT_FlowStatusTypeDef				: 检测状态
**********************************************************************************************************/
INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_CheckStatus(INSPECT_FlowClientsTypeDef* pClient, unsigned char index)
{
	INSPECT_FlowStatusTypeDef Status = FLOW_CAR_NONE;
	
	/* 进入状态1 */
	if (pClient->DetectData[index].flag == 1) {
		pClient->DetectCtrl.detect_nS0 = 0;
		pClient->DetectCtrl.detect_nS1++;
		/* 如果超过最小有车状态时间则判断为有车进入 */
		if (pClient->DetectCtrl.detect_nS1 == INSPECT_FLOW_CNT_1_MIN) {
			/* 车辆数加1 */
			pClient->Parameter.carNumber++;
			pClient->Parameter.magnetismDiff = 0;
			Status = FLOW_CAR_COME;
			pClient->DetectCtrl.bInStatus = 1;
		}
		if (pClient->Parameter.magnetismDiff < pClient->DetectData[index].sum) {
			pClient->Parameter.magnetismDiff = pClient->DetectData[index].sum;
		}
	}
	/* 进入状态0 */
	else {
		/* 有车辆经过后, 进入状态0, 则计数 */
		if (pClient->DetectCtrl.detect_nS1 >= INSPECT_FLOW_CNT_1_MIN) {
			pClient->DetectCtrl.detect_nS0++;
			/* 车辆进入后超过无车状态阈值, 清0, 判断为车辆离开 */
			if (pClient->DetectCtrl.detect_nS0 > pClient->Configuration.caroutThreshhold) {
				Status = FLOW_CAR_GO;
				pClient->DetectCtrl.bInStatus = 0;
				pClient->DetectCtrl.detect_nS0 = 0;
				pClient->DetectCtrl.detect_nS1 = 0;
			}
		}
		else {
			pClient->DetectCtrl.detect_nS1 = 0;
		}
	}
	
	return Status;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Func_KmeansAllocate(INSPECT_FlowClientsTypeDef* pClient)
 @Description			INSPECT_FLOW_Func_KmeansAllocate			: 质心分配
 @Input				pClient								: InspectFlowHander
 @Return				1									: 完成
					0									: 未完成
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Func_KmeansAllocate(INSPECT_FlowClientsTypeDef* pClient)
{
	unsigned char flag;
	unsigned int i, D1, D2;
	unsigned char j, k;
	unsigned int tempCenter;
	
	for (i = 0; i < INSPECT_FLOW_CLUSTER_NUM; i++) {
		pClient->ClusterGroup[i].groupSize = 0;
	}
	
	/* 按距离分配到各聚类域 */
	for (i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
		D1 = abs(pClient->ClusterGroup[0].center - pClient->DetectData[i].sum);
		D2 = abs(pClient->ClusterGroup[1].center - pClient->DetectData[i].sum);
		
		k = 0;
		if (D1 > D2) k = 1;
		
		pClient->DetectData[i].flag = k;
		pClient->ClusterGroup[k].groupSize++;
	}
	
	flag = 1;
	/* 计算新的聚类中心 */
	for (j = 0; j < INSPECT_FLOW_CLUSTER_NUM; j++) {
		tempCenter = 0;
		
		for (i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
			if (pClient->DetectData[i].flag == j) {
				tempCenter += pClient->DetectData[i].sum;
			}
		}
		
		tempCenter /= pClient->ClusterGroup[j].groupSize;
		
		if (tempCenter != pClient->ClusterGroup[j].center) {
			pClient->ClusterGroup[j].center = tempCenter;
			flag = 0;
		}
	}
	
	return flag;	
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Func_CalculateBackground(INSPECT_FlowClientsTypeDef* pClient)
 @Description			INSPECT_FLOW_Func_CalculateBackground		: 背景计算
 @Input				pClient								: InspectFlowHander
 @Return				0									: 正常
					1									: 异常
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Func_CalculateBackground(INSPECT_FlowClientsTypeDef* pClient)
{
	unsigned char ret = 0;
	
	/**
	  * 如果无车, 则计算基准值
	  * 以上一次的基准值为基础, 稳定的作为新的基准值更新
	  * 考虑到特殊情况是, 环境巨变, 则如果稳定时间小于三为之一的计算之间, 按照最新的均值计算
	  * 后面是否考虑保存所有数组, 然后计算稳定的均值
	  */
	if (!pClient->DetectCtrl.bInStatus) {
		/* 车辆离开 */
		if (pClient->MagnetismVal.sum_num < pClient->Configuration.recalibrationOvertimeCnt) {
			/* N分钟采样次数 */
			if ((abs(pClient->MagnetismVal.x_back - pClient->MagnetismVal.x_now) < pClient->Configuration.recalibrationOvernum) && \
			    (abs(pClient->MagnetismVal.y_back - pClient->MagnetismVal.y_now) < pClient->Configuration.recalibrationOvernum) && \
			    (abs(pClient->MagnetismVal.z_back - pClient->MagnetismVal.z_now) < pClient->Configuration.recalibrationOvernum)) {
				pClient->MagnetismVal.sum_back_num++;
				pClient->MagnetismVal.x_back_sum += pClient->MagnetismVal.x_now;
				pClient->MagnetismVal.y_back_sum += pClient->MagnetismVal.y_now;
				pClient->MagnetismVal.z_back_sum += pClient->MagnetismVal.z_now;
			}
			
			pClient->MagnetismVal.sum_num++;
			pClient->MagnetismVal.x_sum += pClient->MagnetismVal.x_now;
			pClient->MagnetismVal.y_sum += pClient->MagnetismVal.y_now;
			pClient->MagnetismVal.z_sum += pClient->MagnetismVal.z_now;
		}
		else {
			/* N分钟计算一次 */
			/* 三分之一的累计采样时间 */
			if (pClient->MagnetismVal.sum_back_num < (pClient->Configuration.recalibrationOvertimeCnt / 3)) {
				pClient->MagnetismVal.x_back = pClient->MagnetismVal.x_sum / pClient->MagnetismVal.sum_num;
				pClient->MagnetismVal.y_back = pClient->MagnetismVal.y_sum / pClient->MagnetismVal.sum_num;
				pClient->MagnetismVal.z_back = pClient->MagnetismVal.z_sum / pClient->MagnetismVal.sum_num;
			}
			else {
				pClient->MagnetismVal.x_back = pClient->MagnetismVal.x_back_sum / pClient->MagnetismVal.sum_back_num;
				pClient->MagnetismVal.y_back = pClient->MagnetismVal.y_back_sum / pClient->MagnetismVal.sum_back_num;
				pClient->MagnetismVal.z_back = pClient->MagnetismVal.z_back_sum / pClient->MagnetismVal.sum_back_num;
			}
			
			pClient->MagnetismVal.sum_num = 0;
			pClient->MagnetismVal.x_sum = 0;
			pClient->MagnetismVal.y_sum = 0;
			pClient->MagnetismVal.z_sum = 0;
			
			pClient->MagnetismVal.sum_back_num = 0;
			pClient->MagnetismVal.x_back_sum = 0;
			pClient->MagnetismVal.y_back_sum = 0;
			pClient->MagnetismVal.z_back_sum = 0;
			
			/* 更新计算数组 */
			for (unsigned char i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
				pClient->DetectData[i].sum = 0;
			}
			pClient->DetectCtrl.maxPos = pClient->DetectCtrl.minPos = pClient->DetectCtrl.dataIndex;
			pClient->DetectCtrl.lastCenter = 0;
		}
		
		pClient->Configuration.recalibrationBackSeconds = 0;
	}
	else {
		/* 车辆进入 */
		/* 如果连续有车 N 分钟, 则认为出错, 认定车辆离开 */
		if (pClient->Configuration.recalibrationBackSeconds >= (pClient->Configuration.recalibrationOvertime * 60)) {
			ret = 1;
			
			/* 以当前值作为基准值 */
			pClient->MagnetismVal.x_back = pClient->MagnetismVal.x_now;
			pClient->MagnetismVal.y_back = pClient->MagnetismVal.y_now;
			pClient->MagnetismVal.z_back = pClient->MagnetismVal.z_now;
			
			pClient->MagnetismVal.sum_num = 0;
			pClient->MagnetismVal.x_sum = 0;
			pClient->MagnetismVal.y_sum = 0;
			pClient->MagnetismVal.z_sum = 0;
			
			pClient->MagnetismVal.sum_back_num = 0;
			pClient->MagnetismVal.x_back_sum = 0;
			pClient->MagnetismVal.y_back_sum = 0;
			pClient->MagnetismVal.z_back_sum = 0;
		}
	}
	
	return ret;
}

/**********************************************************************************************************
 @Function			unsigned char INSPECT_FLOW_Func_InitBackground(INSPECT_FlowClientsTypeDef* pClient)
 @Description			INSPECT_FLOW_Func_InitBackground			: 初始背景
 @Input				pClient								: InspectFlowHander
 @Return				0									: 正常
					1									: 异常
**********************************************************************************************************/
unsigned char INSPECT_FLOW_Func_InitBackground(INSPECT_FlowClientsTypeDef* pClient)
{
	unsigned char ret = 1;
	
	pClient->Configuration.recalibrationBackSeconds += (pClient->Configuration.recalibrationOvertime * 60);
	
	/* 背景值计算 */
	if (INSPECT_FLOW_Func_CalculateBackground(pClient)) {
		/* 更新计算数组 */
		for (unsigned char i = 0; i < INSPECT_FLOW_PROCESS_NUM; i++) {
			pClient->DetectData[i].sum = 0;
		}
		INSPECT_FLOW_MIN_POS = INSPECT_FLOW_MAX_POS = INSPECT_FLOW_INDEX;
		pClient->DetectCtrl.lastCenter = 0;
		
		ret = 0;
	}
	
	return ret;
}

/********************************************** END OF FLEE **********************************************/
