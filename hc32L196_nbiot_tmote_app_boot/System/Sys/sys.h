#ifndef __SYS_H
#define   __SYS_H

#include "ddl.h"
#include "stdbool.h"

typedef int32_t				s32;
typedef int16_t				s16;
typedef int8_t					s8;

typedef const int32_t			sc32;
typedef const int16_t			sc16;
typedef const int8_t			sc8;

typedef __IO int32_t			vs32;
typedef __IO int16_t			vs16;
typedef __IO int8_t				vs8;

typedef __I int32_t				vsc32;
typedef __I int16_t				vsc16;
typedef __I int8_t				vsc8;

typedef uint32_t				u32;
typedef uint16_t				u16;
typedef uint8_t				u8;

typedef const uint32_t			uc32;
typedef const uint16_t			uc16;
typedef const uint8_t			uc8;

typedef __IO uint32_t			vu32;
typedef __IO uint16_t			vu16;
typedef __IO uint8_t			vu8;

typedef __I uint32_t			vuc32;
typedef __I uint16_t			vuc16;
typedef __I uint8_t				vuc8;

void HC32_PeripheralClockGate_Init(void);													//HC32外设时钟门控初始化

void HC32_RCHClock_Init(void);															//HC32内部RCH高速时钟初始化48MHz
void HC32_XTHClock_Init(void);															//HC32外部XTH高速时钟初始化32MHz

void HC32_SysTick_Init(void);																//HC32系统嘀嗒定时器初始化









#endif
