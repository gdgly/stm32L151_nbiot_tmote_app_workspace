#ifndef __RADER_TIMER_H
#define   __RADER_TIMER_H

#include "sys.h"


extern TIM_HandleTypeDef			Radar_TIM2_Handler;							//雷达定时器2句柄

void Radar_TIM2_Init(u16 arr, u16 psc);										//雷达通用定时器2中断初始化
void Radar_TIM2_DeInit(void);												//雷达通用定时器2中断复位

#endif
