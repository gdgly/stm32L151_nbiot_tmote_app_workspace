#ifndef __SYS_H
#define   __SYS_H

#include "stm8l15x.h"

#define ON               1
#define OFF              0

void Stm8_HSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv);

void Stm8_LSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv);

#endif
