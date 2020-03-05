#ifndef __DELAY_H
#define   __DELAY_H

#include "sys.h"

#define Delay_US(n)				HC32_Delay_US(n)
#define Delay_MS(n)				HC32_Delay_MS(n)

void HC32_Delay_Init(u32 systemClock);														//HC32系统延时初始化

void HC32_Delay_US(u32 nUs);																//HC32延时US
void HC32_Delay_10US(u32 nUs);															//HC32延时10US
void HC32_Delay_100US(u32 nUs);															//HC32延时100US

void HC32_Delay_MS(u32 nMs);																//HC32延时MS

#endif
