#ifndef __HAL_PRODUCTS_H
#define   __HAL_PRODUCTS_H

#include "sys.h"
#include "gpio.h"

#define HC32_PRODUCTS_Read()		Products_Detection_Read()

#define PRODUCTS_DETECTION_GPIOx	GpioPortB
#define PRODUCTS_DETECTION_PIN	GpioPin5
#define PRODUCTS_DETECTION_AF		GpioAf0

#define PRODUCTS_DETECTION_READ()	(Gpio_GetInputIO(PRODUCTS_DETECTION_GPIOx, PRODUCTS_DETECTION_PIN))

void Products_Detection_Init(void);

void Products_Detection_DeInit(void);

u8   Products_Detection_Read(void);

#endif /* __HAL_PRODUCTS_H */
