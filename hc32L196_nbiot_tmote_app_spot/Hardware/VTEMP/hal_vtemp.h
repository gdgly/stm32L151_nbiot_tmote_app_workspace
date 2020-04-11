#ifndef __HAL_VTEMP_H
#define   __HAL_VTEMP_H

#include "sys.h"
#include "adc.h"
#include "bgr.h"
#include "gpio.h"

#define VTEMP_ADC_CHANNEL		AdcAiTsInput

#define VTEMP_TRIM1V5_VAL		0x76C
#define VTEMP_TRIM2V5_VAL		0x76C

#define VTEMP_TRIM1V5_ADDR		(*(volatile unsigned short *)(0x00100C34U))
#define VTEMP_TRIM2V5_ADDR		(*(volatile unsigned short *)(0x00100C36U))

s32 HC32_VTemp_Read(u32 timeoutMS);														//HC32VTEMP温度读取

#endif /* __HAL_VTEMP_H */
