#ifndef __HC32L19X_HAL_H
#define   __HC32L19X_HAL_H

#include "hc32l19x_cc.h"

u32  HAL_IncTick(void);																	//HAL Tick++
u32  HAL_GetTick(void);																	//HAL Get Tick
void HAL_Delay(__IO u32 Delay);															//HAL Delay Tick

#endif /* __HC32L19X_HAL_H */
