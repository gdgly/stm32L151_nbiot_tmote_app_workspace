/**
  *********************************************************************************************************
  * @file    hc32l19x_it.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-10
  * @brief   1TAB = 5Speace
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_it.h"
#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"
#include "usart.h"
#include "hal_iwdg.h"
#include "hal_rtc.h"
#include "hal_beep.h"
#include "hal_vbat.h"
#include "hal_vptat.h"
#include "hal_vtemp.h"
#include "hal_aes.h"
#include "hal_crc.h"
#include "hal_flash.h"
#include "hal_iic.h"
#include "hal_bl24cxxp.h"
#include "hal_eeprom.h"
#include "hal_qmc5883l.h"
#include "hal_spi.h"
#include "hal_p25qxxh.h"
#include "hal_norflash.h"
#include "fifo.h"
#include "message.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
#include "iap_boot.h"
#include "iap_core.h"
#include "iap_ugrade.h"
#include "fota.h"

/**********************************************************************************************************
 @Function			void Uart0_IRQHandler(void)
 @Description			Uart0_IRQHandler							: HC32 UART0中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void Uart0_IRQHandler(void)
{
#if USART0_TYPE
	
	/* 发送数据完成标记 */
#if UART0_TXD_IRQ
	if (Uart_GetStatus(M0P_UART0, UartTC)) {
		Uart_ClrStatus(M0P_UART0, UartTC);
	}
#endif
	
	/* 接收数据完成标记 */
#if UART0_RXD_IRQ
	if (Uart_GetStatus(M0P_UART0, UartRC)) {
		Uart_ClrStatus(M0P_UART0, UartRC);
	}
#endif
	
#endif
}

/**********************************************************************************************************
 @Function			void Uart1_IRQHandler(void)
 @Description			Uart1_IRQHandler							: HC32 UART1中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void Uart1_IRQHandler(void)
{
#if USART1_TYPE
	
	/* 发送数据完成标记 */
#if UART1_TXD_IRQ
	if (Uart_GetStatus(M0P_UART1, UartTC)) {
		Uart_ClrStatus(M0P_UART1, UartTC);
	}
#endif
	
	/* 接收数据完成标记 */
#if UART1_RXD_IRQ
	if (Uart_GetStatus(M0P_UART1, UartRC)) {
		Uart_ClrStatus(M0P_UART1, UartRC);
	}
#endif
	
#endif
}

/**********************************************************************************************************
 @Function			void PortB_IRQHandler(void)
 @Description			PortB_IRQHandler							: HC32 PortA中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortA_IRQHandler(void)
{
	
}

/**********************************************************************************************************
 @Function			void PortB_IRQHandler(void)
 @Description			PortB_IRQHandler							: HC32 PortB中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortB_IRQHandler(void)
{
	/* Radio RF IRQn */
	if (Gpio_GetIrqStatus(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN)) {
		Gpio_ClearIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN);
		Radio_Hal_RF_ISR();
	}
}

/**********************************************************************************************************
 @Function			void PortC_IRQHandler(void)
 @Description			PortC_IRQHandler							: HC32 PortC中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortC_IRQHandler(void)
{
	
}

/**********************************************************************************************************
 @Function			void PortD_IRQHandler(void)
 @Description			PortD_IRQHandler							: HC32 PortD中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortD_IRQHandler(void)
{
	
}

/**********************************************************************************************************
 @Function			void PortE_IRQHandler(void)
 @Description			PortE_IRQHandler							: HC32 PortE中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortE_IRQHandler(void)
{
	
}

/**********************************************************************************************************
 @Function			void PortF_IRQHandler(void)
 @Description			PortF_IRQHandler							: HC32 PortF中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void PortF_IRQHandler(void)
{
	
}

/**********************************************************************************************************
 @Function			void Rtc_IRQHandler(void)
 @Description			Rtc_IRQHandler								: HC32 RTC中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rtc_IRQHandler(void)
{
#if RTC_TYPE
	
	/* RTC周期中断产生标记 */
	if (Rtc_GetPridItStatus()) {
		Rtc_ClearPrdfItStatus();
	}
	
	/* RTC闹钟中断产生标记 */
	if (Rtc_GetAlmfItStatus()) {
		Rtc_ClearAlmfItStatus();
	}
	
#endif
}

/**********************************************************************************************************
 @Function			void SysTick_IRQHandler(void)
 @Description			SysTick_IRQHandler							: HC32 系统嘀嗒定时器中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void SysTick_IRQHandler(void)
{
	HAL_IncMecTick();
	HAL_IncSecTick();
}

/********************************************** END OF FLEE **********************************************/
