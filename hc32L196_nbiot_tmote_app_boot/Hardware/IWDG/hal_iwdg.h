#ifndef __HAL_IWDG_H
#define   __HAL_IWDG_H

#include "sys.h"
#include "wdt.h"

#define HC32_IWDG_Feed()			Wdt_Feed()								//WDT喂狗

void HC32_IWDG_Init(en_wdt_time_t enTime);									//WDT初始化

#endif /* __HAL_IWDG_H */
