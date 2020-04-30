#ifndef __HAL_BASE_TIM0_H
#define   __HAL_BASE_TIM0_H

#include "sys.h"
#include "bt.h"

#define HC32_HAL_TIM0_ENABLE()	Bt_M0_Run(TIM0)
#define HC32_HAL_TIM0_DISABLE()	Bt_M0_Stop(TIM0)

#define TIM0_IRQ_Level			IrqLevel2
#define TIM0_IRQ_Channel			TIM0_IRQn

void HC32_BaseTim0_Init(u16 period, en_bt_cr_timclkdiv_t psc);

void HC32_BaseTim0_Register_nIRQ(func_ptr_t func);

#endif /* __HAL_BASE_TIM0_H */
