#ifndef __HAL_ATTITUDE_H
#define   __HAL_ATTITUDE_H

#include "sys.h"
#include "gpio.h"

#define HC32_ATTITUDE_Read()		Attitude_Detection_Read()

#define ATTITUDE_DETECTION_GPIOx	GpioPortF
#define ATTITUDE_DETECTION_PIN	GpioPin0
#define ATTITUDE_DETECTION_AF		GpioAf0

#define ATTITUDE_DETECTION_READ()	(Gpio_GetInputIO(ATTITUDE_DETECTION_GPIOx, ATTITUDE_DETECTION_PIN))

void Attitude_Detection_Init(void);

void Attitude_Detection_DeInit(void);

u8   Attitude_Detection_Read(void);

#endif /* __HAL_ATTITUDE_H */
