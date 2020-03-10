#ifndef __HC32L19X_IT_H
#define   __HC32L19X_IT_H

#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

void Uart0_IRQHandler(void);																//HC32 UART0中断服务函数

void Uart1_IRQHandler(void);																//HC32 UART1中断服务函数















void SysTick_IRQHandler(void);															//HC32 系统嘀嗒定时器中断服务函数

#ifdef __cplusplus
}
#endif

#endif /* __HC32L19X_IT_H */
