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

void HC32_PeripheralClockGate_Init(void);																	//HC32外设时钟门控初始化

void HC32_RCHClock48M_Init(void);																			//HC32内部RCH高速时钟初始化48MHz
void HC32_RCHClock32M_Init(void);																			//HC32内部RCH高速时钟初始化32MHz
void HC32_RCHClock16M_Init(void);																			//HC32内部RCH高速时钟初始化16MHz
void HC32_XTHClock24M_Init(void);																			//HC32外部XTH高速时钟初始化24MHz

void HC32_HPClock_Init(en_sysctrl_clk_source_t enClkSrc, en_sysctrl_hclk_div_t enHClkDiv, en_sysctrl_pclk_div_t enPClkDiv);	//HC32时钟HCLK/PCLK初始化

void HC32_SysTick_Init(void);																				//HC32系统嘀嗒定时器初始化

void HC32_TimeMeter_CountdownMS(timeMeterTypeDef* timer, u32 timeout);											//HC32配置计时器倒数时间(MS)
bool HC32_TimeMeter_IsExpiredMS(timeMeterTypeDef* timer);														//HC32查询是否到达计时器计时时间(MS)
void HC32_TimeMeter_CountdownSS(timeMeterTypeDef* timer, u32 timeout);											//HC32配置计时器倒数时间(SS)
bool HC32_TimeMeter_IsExpiredSS(timeMeterTypeDef* timer);														//HC32查询是否到达计时器计时时间(SS)

#endif
