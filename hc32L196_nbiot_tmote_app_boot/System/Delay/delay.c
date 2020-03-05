/**
  *********************************************************************************************************
  * @file    delay.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-04
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "delay.h"

static __IO u32 fac_us = 0;

/**********************************************************************************************************
 @Function			void HC32_Delay_Init(u32 systemClock)
 @Description			HC32_Delay_Init							: HC32系统延时初始化
 @Input				systemClock								: HCLK时钟
 @Return				void
**********************************************************************************************************/
void HC32_Delay_Init(u32 systemClock)
{
	fac_us = systemClock / 1000000;
}

/**********************************************************************************************************
 @Function			void HC32_Delay_US(u32 nUs)
 @Description			HC32_Delay_US								: HC32延时US
 @Input				nUs										: 延时数
 @Return				void
**********************************************************************************************************/
void HC32_Delay_US(u32 nUs)
{
	u32 ticks, reload;
	u32 told, tnow, tcnt = 0;
	
	reload = SysTick->LOAD;
	
	ticks = nUs * fac_us;
	
	told = SysTick->VAL;
	
	while (1) {
		tnow = SysTick->VAL;
		if (tnow != told) {
			
			if (tnow < told)
				tcnt += (told - tnow);
			else
				tcnt += (reload - tnow + told);
			told = tnow;
			
			if (tcnt >= ticks) break;
		}
	}
}

/**********************************************************************************************************
 @Function			void HC32_Delay_10US(u32 nUs)
 @Description			HC32_Delay_10US							: HC32延时10US
 @Input				nUs										: 延时数
 @Return				void
**********************************************************************************************************/
void HC32_Delay_10US(u32 nUs)
{
	u32 ticks, reload;
	u32 told, tnow, tcnt = 0;
	
	reload = SysTick->LOAD;
	
	ticks = nUs * fac_us * 10;
	
	told = SysTick->VAL;
	
	while (1) {
		tnow = SysTick->VAL;
		if (tnow != told) {
			
			if (tnow < told)
				tcnt += (told - tnow);
			else
				tcnt += (reload - tnow + told);
			told = tnow;
			
			if (tcnt >= ticks) break;
		}
	}
}

/**********************************************************************************************************
 @Function			void HC32_Delay_100US(u32 nUs)
 @Description			HC32_Delay_100US							: HC32延时100US
 @Input				nUs										: 延时数
 @Return				void
**********************************************************************************************************/
void HC32_Delay_100US(u32 nUs)
{
	u32 ticks, reload;
	u32 told, tnow, tcnt = 0;
	
	reload = SysTick->LOAD;
	
	ticks = nUs * fac_us * 100;
	
	told = SysTick->VAL;
	
	while (1) {
		tnow = SysTick->VAL;
		if (tnow != told) {
			
			if (tnow < told)
				tcnt += (told - tnow);
			else
				tcnt += (reload - tnow + told);
			told = tnow;
			
			if (tcnt >= ticks) break;
		}
	}
}

/**********************************************************************************************************
 @Function			void HC32_Delay_MS(u32 nMs)
 @Description			HC32_Delay_MS								: HC32延时MS
 @Input				nMs										: 延时数
 @Return				void
**********************************************************************************************************/
void HC32_Delay_MS(u32 nMs)
{
	for (int ms = 0; ms < nMs; ms++) {
		HC32_Delay_100US(10);
	}
}

/********************************************** END OF FLEE **********************************************/
