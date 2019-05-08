#ifndef __RADER_API_H
#define   __RADER_API_H

#include "sys.h"



void Rader_Init(void);													//雷达初始化
void Rader_InitBG(void);													//雷达初始化背景值
u8   Rader_GetData(u8 dataNum);											//获取雷达数据

void Rader_RunTest(void);												//雷达运行测试
void Rader_Get_Sample(void);												//雷达采样
void Rader_Get_Sample_Time(void);											//雷达采样节拍

#endif
