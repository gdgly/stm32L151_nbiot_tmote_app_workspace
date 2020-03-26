#ifndef __SYS_H
#define   __SYS_H

#include "ddl.h"
#include "stdbool.h"
#include "hc32l19x_cc.h"
#include "hc32l19x_hal.h"

typedef struct time_meter
{
	u32			xTicksToWait;
	u32			xTicksToOut;
} timeMeterTypeDef;















void HC32_PeripheralClockGate_Init(void);													//HC32外设时钟门控初始化




void HC32_SysTick_Init(void);																//HC32系统嘀嗒定时器初始化





void HC32_TimeMeter_CountdownMS(timeMeterTypeDef* timer, u32 timeout);							//HC32配置计时器倒数时间(MS)
bool HC32_TimeMeter_IsExpiredMS(timeMeterTypeDef* timer);										//HC32查询是否到达计时器计时时间(MS)
void HC32_TimeMeter_CountdownSS(timeMeterTypeDef* timer, u32 timeout);							//HC32配置计时器倒数时间(SS)
bool HC32_TimeMeter_IsExpiredSS(timeMeterTypeDef* timer);										//HC32查询是否到达计时器计时时间(SS)










#endif
