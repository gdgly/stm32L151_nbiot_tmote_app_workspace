#ifndef __USART_H
#define   __USART_H

#include "sys.h"
#include "gpio.h"
#include "uart.h"

#define UART0_TXD_GPIOx			GpioPortA
#define UART0_TXD_PIN			GpioPin9

#define UART0_RXD_GPIOx			GpioPortA
#define UART0_RXD_PIN			GpioPin10

#define UART1_TXD_GPIOx			GpioPortA
#define UART1_TXD_PIN			GpioPin2

#define UART1_RXD_GPIOx			GpioPortA
#define UART1_RXD_PIN			GpioPin3

void HC32_Uart0_Init(u32 bound);															//HC32 UART0初始化
void HC32_Uart1_Init(u32 bound);															//HC32 UART1初始化

















#endif
