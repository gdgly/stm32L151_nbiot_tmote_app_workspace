#ifndef __HC32L19X_HAL_H
#define   __HC32L19X_HAL_H

#include "hc32l19x_cc.h"

#define HC32_IncMecondTick		HAL_IncMecTick												//System Mecond Add
#define HC32_GetMecondTick		HAL_GetMecTick												//System Mecond Get

#define HC32_IncSecondTick		HAL_IncSecTick												//System Second Add
#define HC32_GetSecondTick		HAL_GetSecTick												//System Second Get

u32  HAL_IncMecTick(void);																//HAL Inc Mec Tick++
u32  HAL_GetMecTick(void);																//HAL Get Mec Tick

u32  HAL_IncSecTick(void);																//HAL Inc Sec Tick++
u32  HAL_GetSecTick(void);																//HAL Get Sec Tick

void HAL_Delay(__IO u32 Delay);															//HAL Delay Tick

#endif /* __HC32L19X_HAL_H */
