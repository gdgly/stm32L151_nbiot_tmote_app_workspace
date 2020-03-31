#ifndef __USART_H
#define   __USART_H

#include "sys.h"
#include "gpio.h"
#include "uart.h"
#include "stdio.h"
#include "string.h"

#define PRINTF_UART0			M0P_UART0
#define PRINTF_UART1			M0P_UART1
#define PRINTF_UART2			M0P_UART2
#define PRINTF_UART3			M0P_UART3
#define PRINTF_USART			PRINTF_UART1												//Printf使用串口

#define UART0_TXD_GPIOx			GpioPortA
#define UART0_TXD_PIN			GpioPin9
#define UART0_TXD_AF			GpioAf1

#define UART0_RXD_GPIOx			GpioPortA
#define UART0_RXD_PIN			GpioPin10
#define UART0_RXD_AF			GpioAf1

#define UART0_IRQ_Level			IrqLevel1
#define UART0_IRQ_Channel		UART0_2_IRQn

#define UART1_TXD_GPIOx			GpioPortA
#define UART1_TXD_PIN			GpioPin2
#define UART1_TXD_AF			GpioAf1

#define UART1_RXD_GPIOx			GpioPortA
#define UART1_RXD_PIN			GpioPin3
#define UART1_RXD_AF			GpioAf1

#define UART1_IRQ_Level			IrqLevel1
#define UART1_IRQ_Channel		UART1_3_IRQn

#define BR_9600				(  9600ul)
#define BR_19200				( 19200ul)
#define BR_38400				( 38400ul)
#define BR_57600				( 57600ul)
#define BR_76800				( 76800ul)
#define BR_115200				(115200ul)
#define BR_256000				(256000ul)
#define BR_512000				(512000ul)
#define BR_921600				(921600ul)

#define UART0_BAUD_RATE			BR_9600
#define UART1_BAUD_RATE			BR_9600

#define UARTX_IRQ_DISABLE		(0)
#define UARTX_IRQ_ENABLE			(1)

#define UART0_TXD_IRQ			UARTX_IRQ_DISABLE
#define UART0_RXD_IRQ			UARTX_IRQ_ENABLE

#define UART1_TXD_IRQ			UARTX_IRQ_DISABLE
#define UART1_RXD_IRQ			UARTX_IRQ_ENABLE

void HC32_Uart0_Init(u32 bound);															//HC32 UART0初始化
void HC32_Uart1_Init(u32 bound);															//HC32 UART1初始化

#endif
