#ifndef __SYS_H
#define   __SYS_H

#include "ddl.h"
#include "stdbool.h"
#include "hc32l19x_cc.h"
#include "hc32l19x_hal.h"

void HC32_PeripheralClockGate_Init(void);													//HC32外设时钟门控初始化

void HC32_RCHClock_Init(void);															//HC32内部RCH高速时钟初始化48MHz
void HC32_XTHClock_Init(void);															//HC32外部XTH高速时钟初始化32MHz

void HC32_SysTick_Init(void);																//HC32系统嘀嗒定时器初始化














#endif
