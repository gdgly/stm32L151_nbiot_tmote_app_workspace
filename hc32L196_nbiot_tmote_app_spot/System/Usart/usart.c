/**
  *********************************************************************************************************
  * @file    usart.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-06
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
#include "usart.h"

/**********************************************************************************************************
 @Function			static void UART0_Port_Init(void)
 @Description			UART0_Port_Init							: HC32 UART0引脚初始化
 @Input				void
 @Return				void
 @attention			UART0_TXD => PA09
					UART0_RXD => PA10
**********************************************************************************************************/
static void UART0_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* UART0_TXD => PA09 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(UART0_TXD_GPIOx, UART0_TXD_PIN, &GPIO_Initure);
	Gpio_SetAfMode(UART0_TXD_GPIOx, UART0_TXD_PIN, UART0_TXD_AF);
	
	/* UART0_RXD => PA10 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(UART0_RXD_GPIOx, UART0_RXD_PIN, &GPIO_Initure);
	Gpio_SetAfMode(UART0_RXD_GPIOx, UART0_RXD_PIN, UART0_RXD_AF);
}

/**********************************************************************************************************
 @Function			static void UART1_Port_Init(void)
 @Description			UART1_Port_Init							: HC32 UART1引脚初始化
 @Input				void
 @Return				void
 @attention			UART1_TXD => PA02
					UART1_RXD => PA03
**********************************************************************************************************/
static void UART1_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* UART1_TXD => PA02 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(UART1_TXD_GPIOx, UART1_TXD_PIN, &GPIO_Initure);
	Gpio_SetAfMode(UART1_TXD_GPIOx, UART1_TXD_PIN, UART1_TXD_AF);
	
	/* UART1_RXD => PA03 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(UART1_RXD_GPIOx, UART1_RXD_PIN, &GPIO_Initure);
	Gpio_SetAfMode(UART1_RXD_GPIOx, UART1_RXD_PIN, UART1_RXD_AF);
}

/**********************************************************************************************************
 @Function			void HC32_Uart0_Init(u32 bound)
 @Description			HC32_Uart0_Init							: HC32 UART0初始化
 @Input				bound									: 波特率
 @Return				void
**********************************************************************************************************/
void HC32_Uart0_Init(u32 bound)
{
	stc_uart_cfg_t UART_Initure;
	
	UART0_Port_Init();
	
	DDL_ZERO_STRUCT(UART_Initure);
	
	/* UART0 (Mode3, Data_8b, Stop_1b, Check_None) */
	UART_Initure.enRunMode		= UartMskMode3;
	UART_Initure.enStopBit		= UartMsk1bit;
	UART_Initure.enMmdorCk		= UartMskDataOrAddr;
	UART_Initure.stcBaud.u32Baud	= bound;
	UART_Initure.stcBaud.enClkDiv	= UartMsk8Or16Div;
	UART_Initure.stcBaud.u32Pclk	= Sysctrl_GetPClkFreq();
	Uart_Init(M0P_UART0, &UART_Initure);
	
	/* 清 发送数据完成标记 */
	Uart_ClrStatus(M0P_UART0, UartTC);
	/* 清 接收数据完成标记 */
	Uart_ClrStatus(M0P_UART0, UartRC);
	
	/* UART0 TX IT Config */
#if UART0_TXD_IRQ
	Uart_EnableIrq(M0P_UART0, UartTxIrq);
#endif
	/* UART0 RX IT Config */
#if UART0_RXD_IRQ
	Uart_EnableIrq(M0P_UART0, UartRxIrq);
#endif
	
	/* Enable UART0 IRQn */
	EnableNvic(UART0_IRQn, UART0_IRQLevel, TRUE);
}

/**********************************************************************************************************
 @Function			void HC32_Uart1_Init(u32 bound)
 @Description			HC32_Uart1_Init							: HC32 UART1初始化
 @Input				bound									: 波特率
 @Return				void
**********************************************************************************************************/
void HC32_Uart1_Init(u32 bound)
{
	stc_uart_cfg_t UART_Initure;
	
	UART1_Port_Init();
	
	DDL_ZERO_STRUCT(UART_Initure);
	
	/* UART1 (Mode3, Data_8b, Stop_1b, Check_None) */
	UART_Initure.enRunMode		= UartMskMode3;
	UART_Initure.enStopBit		= UartMsk1bit;
	UART_Initure.enMmdorCk		= UartMskDataOrAddr;
	UART_Initure.stcBaud.u32Baud	= bound;
	UART_Initure.stcBaud.enClkDiv	= UartMsk8Or16Div;
	UART_Initure.stcBaud.u32Pclk	= Sysctrl_GetPClkFreq();
	Uart_Init(M0P_UART1, &UART_Initure);
	
	/* 清 发送数据完成标记 */
	Uart_ClrStatus(M0P_UART1, UartTC);
	/* 清 接收数据完成标记 */
	Uart_ClrStatus(M0P_UART1, UartRC);
	
	/* UART1 TX IT Config */
#if UART1_TXD_IRQ
	Uart_EnableIrq(M0P_UART1, UartTxIrq);
#endif
	/* UART1 RX IT Config */
#if UART1_RXD_IRQ
	Uart_EnableIrq(M0P_UART1, UartRxIrq);
#endif
	
	/* Enable UART1 IRQn */
	EnableNvic(UART1_IRQn, UART1_IRQLevel, TRUE);
}

/**********************************************************************************************************
 @Function			int fputc(int ch, FILE *f)
 @Description			fputc									: Re-target putchar function
 @Input				ch
					FILE
 @Return				ch
**********************************************************************************************************/
int fputc(int ch, FILE *f)
{
	while (FALSE == Uart_GetStatus(PRINTF_USART, UartTxe));
	PRINTF_USART->SBUF_f.DATA = (u8) ch;
	while (FALSE == Uart_GetStatus(PRINTF_USART, UartTC));
	Uart_ClrStatus(PRINTF_USART, UartTC);
	return ch;
}

/********************************************** END OF FLEE **********************************************/
