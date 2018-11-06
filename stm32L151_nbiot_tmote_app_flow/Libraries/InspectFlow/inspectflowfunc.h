#ifndef __INSPECT_FLOW_FUNC_H
#define   __INSPECT_FLOW_FUNC_H

#include "sys.h"
#include "inspectflowconfig.h"

#define INSPECT_FLOW_X_D_VALUE			((s32)(pClient->MagnetismVal.x_now - pClient->MagnetismVal.x_back))
#define INSPECT_FLOW_Y_D_VALUE			((s32)(pClient->MagnetismVal.y_now - pClient->MagnetismVal.y_back))
#define INSPECT_FLOW_Z_D_VALUE			((s32)(pClient->MagnetismVal.z_now - pClient->MagnetismVal.z_back))

#define INSPECT_FLOW_X_SQUARE				(INSPECT_FLOW_X_D_VALUE * INSPECT_FLOW_X_D_VALUE)
#define INSPECT_FLOW_Y_SQUARE				(INSPECT_FLOW_Y_D_VALUE * INSPECT_FLOW_Y_D_VALUE)
#define INSPECT_FLOW_Z_SQUARE				(INSPECT_FLOW_Z_D_VALUE * INSPECT_FLOW_Z_D_VALUE)

#define INSPECT_FLOW_INDEX				pClient->DetectCtrl.dataIndex
#define INSPECT_FLOW_MAX_POS				pClient->DetectCtrl.maxPos
#define INSPECT_FLOW_MIN_POS				pClient->DetectCtrl.minPos
#define INSPECT_FLOW_INDEX_SUM			pClient->DetectData[INSPECT_FLOW_INDEX].sum
#define INSPECT_FLOW_MAX_SUM				pClient->DetectData[INSPECT_FLOW_MAX_POS].sum
#define INSPECT_FLOW_MIN_SUM				pClient->DetectData[INSPECT_FLOW_MIN_POS].sum

INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_PassDetect(INSPECT_FlowClientsTypeDef* pClient, int16_t x_mag, int16_t y_mag, int16_t z_mag);	//车辆检测
INSPECT_FlowStatusTypeDef INSPECT_FLOW_Func_CheckStatus(INSPECT_FlowClientsTypeDef* pClient, unsigned char index);						//检查状态

unsigned char INSPECT_FLOW_Func_KmeansAllocate(INSPECT_FlowClientsTypeDef* pClient);												//质心分配
unsigned char INSPECT_FLOW_Func_CalculateBackground(INSPECT_FlowClientsTypeDef* pClient);											//背景计算

unsigned char INSPECT_FLOW_Func_InitBackground(INSPECT_FlowClientsTypeDef* pClient);												//初始背景

#endif /* __INSPECT_FLOW_FUNC_H */
