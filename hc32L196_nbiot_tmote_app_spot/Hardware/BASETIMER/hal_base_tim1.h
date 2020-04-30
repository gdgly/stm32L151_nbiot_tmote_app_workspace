#ifndef __HAL_BASE_TIM1_H
#define   __HAL_BASE_TIM1_H

#include "sys.h"
#include "bt.h"

#define HC32_HAL_TIM1_ENABLE()	Bt_M0_Run(TIM1)
#define HC32_HAL_TIM1_DISABLE()	Bt_M0_Stop(TIM1)

#define TIM1_IRQ_Level			IrqLevel2
#define TIM1_IRQ_Channel			TIM1_IRQn

void HC32_BaseTim1_Init(u16 period, en_bt_cr_timclkdiv_t psc);

void HC32_BaseTim1_Register_nIRQ(func_ptr_t func);

#endif /* __HAL_BASE_TIM1_H */
