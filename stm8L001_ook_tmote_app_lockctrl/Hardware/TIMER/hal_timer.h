#ifndef __HAL_TIMER_H
#define   __HAL_TIMER_H

#include "sys.h"

void Stm8_TIM4_Init(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period);

void Stm8_TIM4_InterruptHandler(void);










#endif /* __HAL_TIMER_H */
