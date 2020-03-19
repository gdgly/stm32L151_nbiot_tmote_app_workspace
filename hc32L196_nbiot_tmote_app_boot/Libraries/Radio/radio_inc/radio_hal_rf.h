#ifndef __RADIO_HAL_RF_H
#define   __RADIO_HAL_RF_H

#include "sys.h"
#include "gpio.h"
#include "radio_hal_wrap.h"

#define RADIO_SI4438_SDN_GPIOx	GpioPortB
#define RADIO_SI4438_SDN_PIN		GpioPin4
#define RADIO_SI4438_SDN_AF		GpioAf0

#define RADIO_SI4438_NSS_GPIOx	GpioPortA
#define RADIO_SI4438_NSS_PIN		GpioPin15
#define RADIO_SI4438_NSS_AF		GpioAf0

#define RADIO_SI4438_IRQ_GPIOx	GpioPortB
#define RADIO_SI4438_IRQ_PIN		GpioPin10
#define RADIO_SI4438_IRQ_AF		GpioAf0

#define RADIO_SI4438_IRQn		PORTB_IRQn
#define RADIO_SI4438_IRQMode		GpioIrqFalling
#define RADIO_SI4438_IRQLevel		IrqLevel3

#define RADIO_NRESET_COUNT		3
#define RADIO_CONFIG_TIMER		10000

typedef enum _radio_trf_errcode
{
	rTRF_OK					= 0U,
	rTRF_ERROR				= 1U
} radio_trf_errcode;

typedef enum _radio_trf_initede
{
	rTRF_Uninited				= 0U,
	rTRF_Isinited				= 1U
} radio_trf_initede;

typedef struct _radio_client
{
	s8		rf_status;
	s8		rf_inited;
	u8		rf_channel1;
	
	
	
	
	
} radioClientsTypeDef;

extern radioClientsTypeDef si4438Client;









radio_trf_errcode Radio_Hal_RF_Init(radioClientsTypeDef* pClient);								//Radio RF 初始化

radio_trf_errcode Radio_Hal_RF_ResetChip(radioClientsTypeDef* pClient);							//Radio RF 复位检查芯片

void Radio_Hal_RF_Interface_Init(void);														//Radio RF 接口初始化

void Radio_Hal_RF_Interrupt_Enable(void);													//Radio RF 中断引脚使能

void Radio_Hal_RF_Interrupt_Disable(void);													//Radio RF 中断引脚失能

























#endif /* __RADIO_HAL_RF_H */
