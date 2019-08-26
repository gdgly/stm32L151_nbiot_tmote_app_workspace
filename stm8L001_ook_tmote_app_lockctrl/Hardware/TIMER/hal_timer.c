/**
  *********************************************************************************************************
  * @file    hal_timer.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "hal_timer.h"

/**********************************************************************************************************
 @Function			void Stm8_TIM4_Init(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period)
 @Description			Stm8_TIM4_Init
 @Input				TIM4_Prescaler
                         TIM4_Period
 @Return				void
**********************************************************************************************************/
void Stm8_TIM4_Init(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period)
{
     /* 使能 TIM4 时钟 */
     CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
     
     /* 复位 TIM4 */
     TIM4_DeInit();
     
     /* 配置 TIM4 */
     TIM4_TimeBaseInit(TIM4_Prescaler, (TIM4_Period - 1));
     
     /* 清除 TIM4 更新中断标志位 */
     TIM4_ClearFlag(TIM4_FLAG_Update);
     
     /* 使能更新中断 */
     TIM4_ITConfig(TIM4_IT_Update, ENABLE);
     
     /* 使能总中断 */
     enableInterrupts();
     
     /* 使能 TIM4 */
     TIM4_Cmd(ENABLE);
}

/**********************************************************************************************************
 @Function			void Stm8_TIM4_InterruptHandler(void)
 @Description			Stm8_TIM4_InterruptHandler
 @Input				void
 @Return				void
**********************************************************************************************************/
void Stm8_TIM4_InterruptHandler(void)
{
     
     
     
     
}

/********************************************** END OF FLEE **********************************************/
