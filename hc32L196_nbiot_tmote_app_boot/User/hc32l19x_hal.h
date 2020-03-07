#ifndef __HC32L19X_HAL_H
#define   __HC32L19X_HAL_H

#include "hc32l19x_cc.h"

u32  HAL_IncTick(void);																	//HAL Inc Tick++
u32  HAL_GetTick(void);																	//HAL Get Tick

u32  HAL_IncSecTick(void);																//HAL Inc Sec Tick++
u32  HAL_GetSecTick(void);																//HAL Get Sec Tick

void HAL_Delay(__IO u32 Delay);															//HAL Delay Tick

#endif /* __HC32L19X_HAL_H */
