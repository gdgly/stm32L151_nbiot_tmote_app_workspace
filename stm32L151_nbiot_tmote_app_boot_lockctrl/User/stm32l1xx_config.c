/**
  *********************************************************************************************************
  * @file    stm32l1xx_config.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-11-01
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "stm32l1xx_config.h"
#include "hal_rtc.h"
#include "delay.h"


/**********************************************************************************************************
 @Function			static void LowPower_StopFront(void)
 @Description			进入低功耗Stop模式前处理(关闭外设)
 @Input				void
 @Return				void
**********************************************************************************************************/
static void LowPower_StopFront(void)
{	

}

/**********************************************************************************************************
 @Function			static void LowPower_StopFrontBehind(void)
 @Description			退出低功耗Stop模式后处理(重新启动外设)
 @Input				void
 @Return				void
**********************************************************************************************************/
static void LowPower_StopFrontBehind(void)
{
	/* 系统时钟配置 */
	Stm32_Clock_Init(RCC_PLLMUL_6, RCC_PLLDIV_3);
	
}

/**********************************************************************************************************
 @Function			void LowPower_Stop(void)
 @Description			进入低功耗Stop模式
 @Input				void
 @Return				void
**********************************************************************************************************/
void LowPower_Stop(void)
{
	LowPower_StopFront();												//进入低功耗Stop模式前处理
	
	__HAL_RCC_PWR_CLK_ENABLE();											//使能PWR时钟
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	HAL_RTCEx_DeactivateWakeUpTimer(&RTC_Handler);
	HAL_RTCEx_SetWakeUpTimer_IT(&RTC_Handler, 0x800, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	uwTick += 1000;
	
	LowPower_StopFrontBehind();											//退出低功耗Stop模式后处理
}



/********************************************** END OF FLEE **********************************************/
