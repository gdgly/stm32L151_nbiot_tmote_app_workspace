#ifndef __HAL_P25QXXH_H
#define   __HAL_P25QXXH_H

#include "sys.h"
#include "gpio.h"
#include "hal_spi.h"

#define P25QXXH_SPIx_NSS_GPIOx	GpioPortB
#define P25QXXH_SPIx_NSS_PIN		GpioPin12
#define P25QXXH_SPIx_NSS_AF		GpioAf0

#define P25QXXH_SPIx_NSS_ENABLE()	Gpio_ClrIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN)
#define P25QXXH_SPIx_NSS_DISABLE()	Gpio_SetIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN)

























#endif /* __HAL_P25QXXH_H */
