#ifndef __HAL_BASE_TIM2_H
#define   __HAL_BASE_TIM2_H

#include "sys.h"
#include "bt.h"

#define HC32_HAL_TIM2_ENABLE()	Bt_M0_Run(TIM2)
#define HC32_HAL_TIM2_DISABLE()	Bt_M0_Stop(TIM2)

#define TIM2_IRQ_Level			IrqLevel2
#define TIM2_IRQ_Channel			TIM2_IRQn

void HC32_BaseTim2_Init(u16 period, en_bt_cr_timclkdiv_t psc);

void HC32_BaseTim2_Register_nIRQ(func_ptr_t func);

#endif /* __HAL_BASE_TIM2_H */
