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

#define MMESH_CHECKSUM_SIZE		2

typedef enum _radio_trf_errcode
{
	rTRF_OK					= 0U,
	rTRF_ERROR				= 1U,
} radio_trf_errcode;

void Radio_Hal_RF_Init(void);																//Radio RF 初始化

char Radio_Hal_RF_Get_Status(void);														//Radio RF 获取状态

void Radio_Hal_RF_Interface_Init(void);														//Radio RF 接口初始化

void Radio_Hal_RF_Interrupt_Enable(void);													//Radio RF 中断引脚使能

void Radio_Hal_RF_Interrupt_Disable(void);													//Radio RF 中断引脚失能

void Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len);											//Radio RF 发送数据包

void Radio_Hal_RF_ISR(void);																//Radio RF 中断处理

#endif /* __RADIO_HAL_RF_H */
