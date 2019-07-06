#ifndef __HAL_IO_CTRL_H
#define   __HAL_IO_CTRL_H

#include "sys.h"

#define IOCTRL_IO1_GPIOx					GPIOB
#define IOCTRL_IO1_PIN					GPIO_PIN_5
#define IOCTRL_IO1_RCC_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define IOCTRL_IO1_RCC_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()

#define IOCTRL_IO2_GPIOx					GPIOH
#define IOCTRL_IO2_PIN					GPIO_PIN_1
#define IOCTRL_IO2_RCC_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOH_CLK_ENABLE()
#define IOCTRL_IO2_RCC_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOH_CLK_DISABLE()

void IOControl_IO1_HIGH(void);
void IOControl_IO1_LOW(void);
void IOControl_IO2_HIGH(void);
void IOControl_IO2_LOW(void);

extern Stm32_CalculagraphTypeDef	IOControlIO1Time;
extern Stm32_CalculagraphTypeDef	IOControlIO2Time;

void IOControl_IO1_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec);
void IOControl_IO2_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec);

void IOControl_IO1_Check(Stm32_CalculagraphTypeDef* timer);
void IOControl_IO2_Check(Stm32_CalculagraphTypeDef* timer);

bool IOControl_IO1_State(void);
bool IOControl_IO2_State(void);

#endif /* __HAL_IO_CTRL_H */
