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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
#if USART0_TYPE
	HC32_Uart0_Init(UART0_BAUD_RATE);														//HC32串口0初始化
#endif
#if USART1_TYPE
	HC32_Uart1_Init(UART1_BAUD_RATE);														//HC32串口1初始化
#endif
	
	
	
	
	
	
	
	
	printf("Uart Test\r\n");
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	while (true)
	{
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
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
