/**
  *********************************************************************************************************
  * @file    hc32l19x_hal.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-05
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_hal.h"

static __IO u32 uwTick = 0;
static __IO u32 usTick = 0;

/**********************************************************************************************************
 @Function			u32 HAL_IncMecTick(void)
 @Description			HAL_IncMecTick								: HAL Inc Mec Tick++
 @Input				void
 @Return				0
**********************************************************************************************************/
u32 HAL_IncMecTick(void)
{
	uwTick++;
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 HAL_GetMecTick(void)
 @Description			HAL_GetMecTick								: HAL Get Mec Tick
 @Input				void
 @Return				Tick
**********************************************************************************************************/
u32 HAL_GetMecTick(void)
{
	return uwTick;
}

/**********************************************************************************************************
 @Function			u32 HAL_IncSecTick(void)
 @Description			HAL_IncSecTick								: HAL Inc Sec Tick++
 @Input				void
 @Return				0
**********************************************************************************************************/
u32 HAL_IncSecTick(void)
{
	static u32 SecondTickPre;
	static u32 SecondTickNow;
	
	SecondTickNow = HAL_GetMecTick();
	if ((SecondTickNow > SecondTickPre) && ((SecondTickNow - SecondTickPre) >= 1000)) {
		usTick++;
		SecondTickPre += 1000;
	}
	else if ((0xFFFFFFFF - SecondTickPre + SecondTickNow + 1) >= 1000) {
		usTick++;
		SecondTickPre += 1000;
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 HAL_GetSecTick(void)
 @Description			HAL_GetSecTick								: HAL Get Sec Tick
 @Input				void
 @Return				Tick
**********************************************************************************************************/
u32 HAL_GetSecTick(void)
{
	return usTick;
}

/**********************************************************************************************************
 @Function			void HAL_Delay(__IO u32 Delay)
 @Description			HAL_Delay									: HAL Delay Tick
 @Input				Delay
 @Return				void
**********************************************************************************************************/
void HAL_Delay(__IO u32 Delay)
{
	u32 tickstart = 0;
	
	tickstart = HAL_GetMecTick();
	
	while ((HAL_GetMecTick() - tickstart) < Delay) {
		;
	}
}

/********************************************** END OF FLEE **********************************************/
