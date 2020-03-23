#ifndef __HAL_VPTAT_H
#define   __HAL_VPTAT_H

#include "sys.h"
#include "adc.h"
#include "bgr.h"
#include "gpio.h"

#define VPTAT_ADC_GPIOx			GpioPortB
#define VPTAT_ADC_PIN			GpioPin15

#define VPTAT_ADC_CHANNEL		AdcExInputCH22

u32 HC32_VPtat_Read(u32 timeoutMS);														//HC32VPTAT电压读取

#endif /* __HAL_VPTAT_H */
