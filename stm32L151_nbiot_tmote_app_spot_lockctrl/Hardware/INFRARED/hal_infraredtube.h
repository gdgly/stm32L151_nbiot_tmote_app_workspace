#ifndef __HAL_INFRARED_TUBE_H
#define   __HAL_INFRARED_TUBE_H

#include "sys.h"

#define OPT_K1_GPIOx					GPIOB
#define OPT_K1_PIN						GPIO_PIN_14
#define OPT_K1_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K1_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K2_GPIOx					GPIOB
#define OPT_K2_PIN						GPIO_PIN_15
#define OPT_K2_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K2_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K3_GPIOx					GPIOB
#define OPT_K3_PIN						GPIO_PIN_13
#define OPT_K3_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K3_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K1_IN()						HAL_GPIO_ReadPin(OPT_K1_GPIOx, OPT_K1_PIN)
#define OPT_K2_IN()						HAL_GPIO_ReadPin(OPT_K2_GPIOx, OPT_K2_PIN)
#define OPT_K3_OUT(n)					(n?HAL_GPIO_WritePin(OPT_K3_GPIOx, OPT_K3_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(OPT_K3_GPIOx, OPT_K3_PIN, GPIO_PIN_RESET))

void InfraredTube_OPT_K3_OUT(u8 enable);									//红外对管发射管输出控制

u8 InfraredTube_OPT_K1_IN(void);											//红外对管接收管输入
u8 InfraredTube_OPT_K2_IN(void);											//红外对管接收管输入




















#endif /* __HAL_INFRARED_TUBE_H */
