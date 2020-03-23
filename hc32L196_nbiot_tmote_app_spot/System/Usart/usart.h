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

#define UART0_IRQn				UART0_2_IRQn
#define UART0_IRQLevel			IrqLevel1

#define UART1_TXD_GPIOx			GpioPortA
#define UART1_TXD_PIN			GpioPin2
#define UART1_TXD_AF			GpioAf1

#define UART1_RXD_GPIOx			GpioPortA
#define UART1_RXD_PIN			GpioPin3
#define UART1_RXD_AF			GpioAf1

#define UART1_IRQn				UART1_3_IRQn
#define UART1_IRQLevel			IrqLevel1

#define UARTX_IRQ_DISABLE		(0)
#define UARTX_IRQ_ENABLE			(1)

#define UART0_TXD_IRQ			UARTX_IRQ_DISABLE
#define UART0_RXD_IRQ			UARTX_IRQ_ENABLE

#define UART1_TXD_IRQ			UARTX_IRQ_DISABLE
#define UART1_RXD_IRQ			UARTX_IRQ_ENABLE

void HC32_Uart0_Init(u32 bound);															//HC32 UART0初始化
void HC32_Uart1_Init(u32 bound);															//HC32 UART1初始化

#endif
