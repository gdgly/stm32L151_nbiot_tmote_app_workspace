#ifndef __HAL_OOK_H
#define   __HAL_OOK_H

#include "sys.h"

#define OOK_GPIOx						GPIOB
#define OOK_PIN						GPIO_PIN_5
#define OOK_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define OOK_RCC_GPIO_CLK_DISABLE()			__HAL_RCC_GPIOB_CLK_DISABLE()

#define OOK_DATA_IN()					HAL_GPIO_ReadPin(OOK_GPIOx, OOK_PIN)

#define OOK_DATA_IRQn					EXTI9_5_IRQn

extern uint32_t OOKDataFrameData;
extern uint8_t  OOKDataFrameFlag;

void OOK_EXTI_Initialization(void);

uint8_t OOK_EXTI_GetHighPulseTime(void);
uint8_t OOK_EXTI_GetLowPulseTime(void);

uint32_t OOK_EXTI_Process(void);

#endif /* __HAL_OOK_H */
