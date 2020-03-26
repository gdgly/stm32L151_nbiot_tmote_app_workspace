/**
  *********************************************************************************************************
  * @file    sys.c
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

#include "platform_config.h"
#include "platform_map.h"
#include "sys.h"

/**********************************************************************************************************
 @Function			void HC32_PeripheralClockGate_Init(void)
 @Description			HC32_PeripheralClockGate_Init					: HC32外设时钟门控初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_PeripheralClockGate_Init(void)
{
	/* -使能SysTick外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTick, SYSTEM_PERIPHERAL_GATE_TICK);
	
	/* -使能GPIO外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, SYSTEM_PERIPHERAL_GATE_GPIO);
	
	/* -使能WDT外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt, SYSTEM_PERIPHERAL_GATE_WDT);
	
	/* -使能RTC外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc, SYSTEM_PERIPHERAL_GATE_RTC);
	
	/* -使能UART0外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0, SYSTEM_PERIPHERAL_GATE_UART0);
	
	/* -使能UART1外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1, SYSTEM_PERIPHERAL_GATE_UART1);
	
	/* -使能I2C0外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c0, SYSTEM_PERIPHERAL_GATE_I2C0);
	
	/* -使能I2C1外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c1, SYSTEM_PERIPHERAL_GATE_I2C1);
	
	/* -使能SPI0外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0, SYSTEM_PERIPHERAL_GATE_SPI0);
	
	/* -使能SPI1外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi1, SYSTEM_PERIPHERAL_GATE_SPI1);
	
	/* -使能ADC/BGR外设时钟门控- */
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, SYSTEM_PERIPHERAL_GATE_ADC);
}









































/**********************************************************************************************************
 @Function			void HC32_SysTick_Init(void)
 @Description			HC32_SysTick_Init							: HC32系统嘀嗒定时器初始化
 @Input				void
 @Return				void
 @attention			时钟改变后嘀嗒定时器需重新配置
**********************************************************************************************************/
void HC32_SysTick_Init(void)
{
	/* 配置系统嘀嗒定时器 */
	SysTick_Config(SystemCoreClock / 1000);
}




















/**********************************************************************************************************
 @Function			void HC32_TimeMeter_CountdownMS(timeMeterTypeDef* timer, u32 timeout)
 @Description			HC32_TimeMeter_CountdownMS					: HC32配置计时器倒数时间(MS)
 @Input				timeMeterTypeDef*							: 计时器结构体指针
					timeout									: 倒计时时间(MS)
 @Return				void
**********************************************************************************************************/
void HC32_TimeMeter_CountdownMS(timeMeterTypeDef* timer, u32 timeout)
{
	timer->xTicksToWait = timeout;
	timer->xTicksToOut  = HAL_GetMecTick() + timeout;
}

/**********************************************************************************************************
 @Function			bool HC32_TimeMeter_IsExpiredMS(timeMeterTypeDef* timer)
 @Description			HC32_TimeMeter_IsExpiredMS					: HC32查询是否到达计时器计时时间(MS)
 @Input				timeMeterTypeDef*							: 计时器结构体指针
 @Return				true										: 到达
					false									: 未到达
**********************************************************************************************************/
bool HC32_TimeMeter_IsExpiredMS(timeMeterTypeDef* timer)
{
	u32 tickNow, tickOld, tickCnt;
	
	tickOld = (timer->xTicksToOut - timer->xTicksToWait);
	tickNow = HAL_GetMecTick();
	
	if (tickNow > tickOld)
		tickCnt = (tickNow - tickOld);
	else
		tickCnt = (0xFFFFFFFF - tickOld + tickNow + 1);
	
	if (tickCnt > timer->xTicksToWait)
		return true;
	else
		return false;
}

/**********************************************************************************************************
 @Function			void HC32_TimeMeter_CountdownSS(timeMeterTypeDef* timer, u32 timeout)
 @Description			HC32_TimeMeter_CountdownSS					: HC32配置计时器倒数时间(SS)
 @Input				timeMeterTypeDef*							: 计时器结构体指针
					timeout									: 倒计时时间(SS)
 @Return				void
**********************************************************************************************************/
void HC32_TimeMeter_CountdownSS(timeMeterTypeDef* timer, u32 timeout)
{
	timer->xTicksToWait = timeout;
	timer->xTicksToOut  = HAL_GetSecTick() + timeout;
}

/**********************************************************************************************************
 @Function			bool HC32_TimeMeter_IsExpiredSS(timeMeterTypeDef* timer)
 @Description			HC32_TimeMeter_IsExpiredSS					: HC32查询是否到达计时器计时时间(SS)
 @Input				timeMeterTypeDef*							: 计时器结构体指针
 @Return				true										: 到达
					false									: 未到达
**********************************************************************************************************/
bool HC32_TimeMeter_IsExpiredSS(timeMeterTypeDef* timer)
{
	u32 tickNow, tickOld, tickCnt;
	
	tickOld = (timer->xTicksToOut - timer->xTicksToWait);
	tickNow = HAL_GetSecTick();
	
	if (tickNow > tickOld)
		tickCnt = (tickNow - tickOld);
	else
		tickCnt = (0xFFFFFFFF - tickOld + tickNow + 1);
	
	if (tickCnt > timer->xTicksToWait)
		return true;
	else
		return false;
}






























/********************************************** END OF FLEE **********************************************/
