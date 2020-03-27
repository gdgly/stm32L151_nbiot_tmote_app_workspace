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
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_48M)
	HC32_RCHClock48M_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_32M)
	HC32_RCHClock32M_Init();																//HC32RCH时钟初始化32MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH_24M)
	HC32_XTHClock24M_Init();																//HC32XTH时钟初始化24MHz
#endif
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
	HC32_RTC_Init();																	//HC32实时时钟初始化
	
	HC32_LowPowerIO_Init();																//HC32低功耗IO初始化
	HC32_RstPowerIO_Init();																//HC32复位电源初始化
	HC32_CtrPowerIO_Init();																//HC32控制电源初始化
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	HC32_Uart0_Init(9600);																//UART0初始化
	HC32_Uart1_Init(9600);																//UART1初始化
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
#ifdef	DEVICE_DEBUG
	DeBugMain();
#endif
	
	while (true) {
		
		
		
		
		
		
		printf("Runing\r\n");
		
		
		
		HC32_IWDG_Feed();
		
		Delay_MS(1000);
		
		
		
		
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
