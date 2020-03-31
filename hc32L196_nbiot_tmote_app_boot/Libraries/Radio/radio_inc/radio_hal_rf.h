#ifndef __RADIO_HAL_RF_H
#define   __RADIO_HAL_RF_H

#include "sys.h"
#include "gpio.h"

#define RADIO_SI4438_SDN_GPIOx	GpioPortB
#define RADIO_SI4438_SDN_PIN		GpioPin4
#define RADIO_SI4438_SDN_AF		GpioAf0

#define RADIO_SI4438_NSS_GPIOx	GpioPortA
#define RADIO_SI4438_NSS_PIN		GpioPin15
#define RADIO_SI4438_NSS_AF		GpioAf0

#define RADIO_SI4438_IRQ_GPIOx	GpioPortB
#define RADIO_SI4438_IRQ_PIN		GpioPin10
#define RADIO_SI4438_IRQ_AF		GpioAf0

#define RADIO_SI4438_IRQ_Mode		GpioIrqFalling
#define RADIO_SI4438_IRQ_Level	IrqLevel3
#define RADIO_SI4438_IRQ_Channel	PORTB_IRQn






















#endif /* __RADIO_HAL_RF_H */
