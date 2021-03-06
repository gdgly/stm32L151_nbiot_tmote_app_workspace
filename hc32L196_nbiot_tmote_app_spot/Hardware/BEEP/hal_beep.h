#ifndef __HAL_BEEP_H
#define   __HAL_BEEP_H

#include "sys.h"
#include "gpio.h"

#define HC32_BEEP_Init			BEEP_GPIO_InitControl
#define HC32_BEEP_Repeat			BEEP_Repeat_Control

#define BEEP_GPIOx				GpioPortB
#define BEEP_PIN				GpioPin8
#define BEEP_AF				GpioAf0

#define BEEP_IO_SET(n)			(n ? (Gpio_SetIO(BEEP_GPIOx, BEEP_PIN)) : (Gpio_ClrIO(BEEP_GPIOx, BEEP_PIN)))

#define BEEP_OUTPUT_FAST			0
#define BEEP_OUTPUT_AHB			1
#define BEEP_OUTPUT_TYPE			BEEP_OUTPUT_AHB											//蜂鸣器IO模式

#define BEEP_ACTIVE				0
#define BEEP_PASSIVE			1
#define BEEP_MODEL_TYPE			BEEP_PASSIVE												//蜂鸣器类型

#define BEEP_PASSIVE_ON			225														//无源蜂鸣器开时间
#define BEEP_PASSIVE_OFF			225														//无源蜂鸣器关时间

void BEEP_GPIO_InitControl(bool ctrl);														//蜂鸣器GPIO初始化控制

void BEEP_Repeat_Control(u16 nCount, u16 speaknMs, u16 shutnMs);									//蜂鸣器控制重复响

#endif /* __HAL_BEEP_H */
