#ifndef __HAL_VBAT_H
#define   __HAL_VBAT_H

#include "sys.h"
#include "adc.h"
#include "bgr.h"
#include "gpio.h"

#define VBATE_ADC_GPIOx			GpioPortB
#define VBATE_ADC_PIN			GpioPin1

#define VBATE_ADC_CHANNEL		AdcExInputCH9

u32 HC32_VBate_Read(u32 timeoutMS);														//HC32电池电压读取

#endif /* __HAL_VBAT_H */
