#ifndef __HC32L19X_HAL_H
#define   __HC32L19X_HAL_H

#include "hc32l19x_cc.h"

#define HC32_IncMecondTick		HAL_IncMecTick												//System Mecond Inc
#define HC32_AddMecondTick		HAL_AddMecTick												//System Mecond Add
#define HC32_GetMecondTick		HAL_GetMecTick												//System Mecond Get

#define HC32_IncSecondTick		HAL_IncSecTick												//System Second Inc
#define HC32_AddSecondTick		HAL_AddSecTick												//System Second Add
#define HC32_GetSecondTick		HAL_GetSecTick												//System Second Get

#define HC32_SystemReset			HAL_SystemReset											//System Reset

u32  HAL_IncMecTick(void);																//HAL Inc Mec Tick++
u32  HAL_AddMecTick(u32 ntick);															//HAL Add Mec Tick
u32  HAL_GetMecTick(void);																//HAL Get Mec Tick

u32  HAL_IncSecTick(void);																//HAL Inc Sec Tick++
u32  HAL_AddSecTick(u32 ntick);															//HAL Add Sec Tick
u32  HAL_GetSecTick(void);																//HAL Get Sec Tick

void HAL_Delay(__IO u32 Delay);															//HAL Delay Tick

void HAL_IRQ_Disable(void);																//HAL IRQ Disable
void HAL_IRQ_Enable(void);																//HAL IRQ Enable

void HAL_SystemReset(void);																//HAL System Reset

#endif /* __HC32L19X_HAL_H */
