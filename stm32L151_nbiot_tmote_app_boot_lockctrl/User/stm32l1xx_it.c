/**
  *********************************************************************************************************
  * @file    stm32l1xx_it.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "main.h"
#include "stm32l1xx_it.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hal_rtc.h"
#include "hal_iwdg.h"

#include "tmesh_misc.h"
#include "hal_rf.h"

#if 0
/**********************************************************************************************************
 @Function			void RTC_Alarm_IRQHandler(void)
 @Description			RTC闹钟中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void RTC_Alarm_IRQHandler(void)
{
	HAL_RTC_AlarmIRQHandler(&RTC_Handler);									//调用HAL库公共闹钟中断处理函数
}

/**********************************************************************************************************
 @Function			void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
 @Description			RTC闹钟A中断处理回调函数
 @Input				hrtc : RTC句柄
 @Return				void
**********************************************************************************************************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	if (hrtc->Instance == RTC) {
		
	}
}


/**********************************************************************************************************
 @Function			void RTC_WKUP_IRQHandler(void)
 @Description			RTC WAKE UP中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void RTC_WKUP_IRQHandler(void)
{
	HAL_RTCEx_WakeUpTimerIRQHandler(&RTC_Handler);							//调用HAL库公共WKUPTime中断处理函数
}

/**********************************************************************************************************
 @Function			void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
 @Description			RTC WAKE UP中断处理回调函数
 @Input				hrtc : RTC句柄
 @Return				void
**********************************************************************************************************/
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	if (hrtc->Instance == RTC) {
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	}	
}


/**********************************************************************************************************
 @Function			void USART1_IRQHandler(void)
 @Description			串口1中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void USART1_IRQHandler(void)
{

}

/**********************************************************************************************************
 @Function			void USART2_IRQHandler(void)
 @Description			串口2中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void USART2_IRQHandler(void)
{
//	u32 timeout = 0;
//	
//	HAL_UART_IRQHandler(&UART2_Handler);									//调用HAL库中断处理公用函数
//	
//	timeout = 0;
//	while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY) {			//等待就绪
//		timeout++;													//超时处理
//		if (timeout > HAL_MAX_DELAY) break;
//	}
//	
//	timeout = 0;
//	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
//	while (HAL_UART_Receive_IT(&UART2_Handler, (u8 *)USART2_aRxBuffer, USART2_RXBUFFERSIZE) != HAL_OK) {
//		timeout++;													//超时处理
//		if (timeout > HAL_MAX_DELAY) break;
//	}
}

/**********************************************************************************************************
 @Function			void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 @Description			串口接收中断处理回调函数
					在HAL库中所有串口接收中断服务函数都会调用此函数
 @Input				hrtc : RTC句柄
 @Return				void
**********************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)										//如果是串口1
	{
		if ((USART1_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART1_RX_STA & 0x4000) {									//接收到了0x0D
				if (USART1_aRxBuffer[0] != 0x0a) USART1_RX_STA = 0;			//接收错误, 重新开始
				else USART1_RX_STA |= 0x8000;								//接收完成了
			}
			else {													//还没收到0x0D
				if (USART1_aRxBuffer[0] == 0x0d) {
					USART1_RX_STA |= 0x4000;
				}
				else {
					USART1_RX_BUF[USART1_RX_STA&0X3FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if (USART1_RX_STA > (USART1_REC_LEN-1)) USART1_RX_STA = 0;	//接收数据错误, 重新开始接收
				}
			}
		}
	}
	
	if (huart->Instance == USART2)										//如果是串口2
	{
		if ((USART2_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART2_aRxBuffer[0] == 0x0a) {								//接收到了0x0a
				USART2_RX_STA |= 0x8000;									//标记接收完成
			}
			else {
				USART2_RX_BUF[USART2_RX_STA&0X3FFF] = USART2_aRxBuffer[0];
				USART2_RX_STA++;
				if (USART2_RX_STA > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
			}
		}
	}
}
#endif

/**********************************************************************************************************
 @Function			void TIM2_IRQHandler(void)
 @Description			定时器2中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM2_IRQHandler(void)
{
}

/**********************************************************************************************************
 @Function			void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 @Description			定时器中断处理回调函数
					在HAL库中所有定时器中断服务函数都会调用此函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
	}
}


/**********************************************************************************************************
 @Function			void NMI_Handler(void)
 @Description			This function handles NMI exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void NMI_Handler(void)
{
}

/**********************************************************************************************************
 @Function			void HardFault_Handler(void)
 @Description			This function handles Hard Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void MemManage_Handler(void)
 @Description			This function handles Memory Manage exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void BusFault_Handler(void)
 @Description			This function handles Bus Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void UsageFault_Handler(void)
 @Description			This function handles Usage Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void SVC_Handler(void)
 @Description			This function handles SVCall exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void SVC_Handler(void)
{
}

/**********************************************************************************************************
 @Function			void DebugMon_Handler(void)
 @Description			This function handles Debug Monitor exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void DebugMon_Handler(void)
{
}

/**********************************************************************************************************
 @Function			void PendSV_Handler(void)
 @Description			This function handles PendSVC exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void PendSV_Handler(void)
{
}

/**********************************************************************************************************
 @Function			void SysTick_Handler(void)
 @Description			This function handles SysTick Handler.
 @Input				void
 @Return				void
**********************************************************************************************************/
int softResetTime;
void SysTick_Handler(void)
{
	HAL_IncTick();
	Sys_IncSecond();
	Sys_Inc100ms();
}

void EXTI15_10_IRQHandler(void)
{
	/* EXTI line interrupt detected */
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) 
	{ 
	  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
	  tmesh_rf_ISR();
	  HAL_GPIO_EXTI_Callback(GPIO_PIN_10);
	}

}


/********************************************** END OF FLEE **********************************************/
