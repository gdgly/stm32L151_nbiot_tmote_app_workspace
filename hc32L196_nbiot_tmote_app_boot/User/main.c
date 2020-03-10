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
#include "hal_beep.h"
#include "hal_iwdg.h"
#include "hal_rtc.h"
#include "hal_vbat.h"

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
	HC32_PeripheralClockGate_Init();														//HC32外设时钟门控初始化
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH)
	HC32_RCHClock_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH)
	HC32_XTHClock_Init();																//HC32XTH时钟初始化32MHz
#endif
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
	HC32_RTC_Init();																	//HC32实时时钟初始化
	
	BEEP_Repeat_Control(5, 50, 25);														//蜂鸣器
	HC32_IWDG_Feed();																	//喂狗
	
	HC32_LowPowerIO_Init();																//HC32低功耗IO初始化
	HC32_RstPowerIO_Init();																//HC32复位电源初始化
	HC32_CtrPowerIO_Init();																//HC32控制电源初始化
	
	
	
	
	
	
	
	
	HC32_Uart0_Init(9600);
	HC32_Uart1_Init(9600);
	
	
	
	
	
	
	
	BEEP_Repeat_Control(10, 50, 25);														//蜂鸣器
	HC32_IWDG_Feed();																	//喂狗
	
	
	
	
	
	
	
	
	
#if 0
	BEEP_Repeat_Control(1, 150, 0);
	Delay_MS(100);
	BEEP_Repeat_Control(2, 50, 25);
	Delay_MS(80);
	BEEP_Repeat_Control(1, 150, 0);
	Delay_MS(100);
	BEEP_Repeat_Control(2, 50, 25);
	
	Delay_MS(500);
	
	BEEP_Repeat_Control(5, 50, 25);
	Delay_MS(1000);
	BEEP_Repeat_Control(10, 50, 25);
#endif
	
	printf("Init OK\r\n");
	
	printf("Modul : %d\r\n", MODEL_POWER_IO_GET());
	printf("Radar : %d\r\n", RADAR_POWER_IO_GET());
	printf("NBIot : %d\r\n", NBIOT_POWER_IO_GET());
	printf("VBate : %d\r\n", VBATE_POWER_IO_GET());
	
	
	
	
	
	
	struct tm date;
	
	
	while (true) {
		
#ifdef	DEVICE_DEBUG
		DeBugMain();
#endif
		
		HC32_IWDG_Feed();
		
		Delay_MS(1000);
		
		date = HC32_RTC_GetUnixTimeToCalendar();
		
		printf("%02d-%02d-%02d %02d:%02d:%02d\r\n", date.tm_year, date.tm_mon, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec);
		
		
		
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
