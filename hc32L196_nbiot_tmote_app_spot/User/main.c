/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-03
  * @brief   1TAB = 5Speace
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_iwdg.h"
#include "hal_rtc.h"
#include "hal_beep.h"

/****************************************** Select DEBUG *************************************************/
//#define	DEVICE_DEBUG																	//定义开启设备调试
/********************************************* DEBUG *****************************************************/
#ifdef	DEVICE_DEBUG
void DeBugMain(void);
#endif
/****************************************** Debug Ending *************************************************/

/**********************************************************************************************************
 @Function			int main(void)
 @Description			Main
 @Input				void
 @Return				int
**********************************************************************************************************/
int main(void)
{
	HC32_PeripheralAll_Reset();															//HC32外设模块复位
	
	HC32_PeripheralClockGate_Init();														//HC32外设时钟门控初始化
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_48M)
	HC32_RCHClock48M_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_32M)
	HC32_RCHClock32M_Init();																//HC32RCH时钟初始化32MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_16M)
	HC32_RCHClock16M_Init();																//HC32RCH时钟初始化16MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH_24M)
	HC32_XTHClock24M_Init();																//HC32XTH时钟初始化24MHz
#endif
	
	HC32_HPClock_Init(SysctrlClkPLL, SysctrlHclkDiv4, SysctrlPclkDiv1);							//HC32时钟HCLK/PCLK初始化
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
	HC32_RTC_Init();																	//HC32实时时钟初始化
	
	HC32_BEEP_Repeat(5, 60, 25);															//HC32蜂鸣器
	HC32_IWDG_Feed();																	//HC32喂狗
	
	HC32_LowPowerIO_Init();																//HC32低功耗IO初始化
	HC32_RstPowerIO_Init();																//HC32复位电源初始化
	HC32_CtrPowerIO_Init();																//HC32控制电源初始化
	
	HC32_BEEP_Init(OFF);																//HC32蜂鸣器关闭
	
#if USART0_TYPE
	HC32_Uart0_Init(UART0_BAUD_RATE);														//HC32串口0初始化
#endif
#if USART1_TYPE
	HC32_Uart1_Init(UART1_BAUD_RATE);														//HC32串口1初始化
#endif
	
	
	
	
	
	
	
	
	
	HC32_BEEP_Repeat(10, 60, 25);															//HC32蜂鸣器
	HC32_IWDG_Feed();																	//HC32喂狗
	
	
	
	
	
	
	
	
	struct tm date;
	
	HC32_RTC_SetTime(20, 04, 11, 10, 00, 00);
	
	while (true)
	{
		
		date = HC32_RTC_GetUnixTimeToCalendar();
		
		printf("*******************************************************************************************\r\n");
		printf("This is Jump Application\r\n");
		printf("Reset: %d Runing: %8d HCLK: %d PCLK: %d SystemCoreClock: %d\r\n", HC32_Reset_Flag, HC32_GetMecondTick(), Sysctrl_GetHClkFreq(), Sysctrl_GetPClkFreq(), SystemCoreClock);
		printf("Date:  %02d-%02d-%02d %02d:%02d:%02d week %d\r\n", date.tm_year, date.tm_mon, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec, date.tm_wday);
		printf("*******************************************************************************************\r\n\r\n");
		
		Delay_MS(1000);
		
		HC32_IWDG_Feed();
		
		
		
		
		
		
	}
}

#ifdef	DEVICE_DEBUG
/********************************************* DEBUG *****************************************************/
/****************************************** Debug Ending *************************************************/
/**********************************************************************************************************
 @Function			void DeBugMain(void)
 @Description			DeBugMain
 @Input				void
 @Return				void
**********************************************************************************************************/
void DeBugMain(void)
{
	
}
#endif

/********************************************** END OF FLEE **********************************************/
