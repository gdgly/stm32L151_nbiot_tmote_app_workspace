/**
  *********************************************************************************************************
  * @file    sys.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-22
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "sys.h"

/**********************************************************************************************************
 @Function			void Stm8_HSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
 @Description			Stm8_HSIClock_Init
 @Input				CLK_SYSCLKDiv
 @Return				void
**********************************************************************************************************/
void Stm8_HSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
     /* 使能HSI */
     CLK_HSICmd(ENABLE);
     
     /* 使能系统时钟源选择 */
     CLK_SYSCLKSourceSwitchCmd(ENABLE);
     
     /* 系统时钟源选择HSI */
     CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
     
     /* 设置系统分频系数 */
     CLK_SYSCLKDivConfig(CLK_SYSCLKDiv);
}

/**********************************************************************************************************
 @Function			void Stm8_LSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
 @Description			Stm8_LSIClock_Init
 @Input				CLK_SYSCLKDiv
 @Return				void
**********************************************************************************************************/
void Stm8_LSIClock_Init(CLK_SYSCLKDiv_TypeDef CLK_SYSCLKDiv)
{
     /* 使能LSI */
     CLK_LSICmd(ENABLE);
     
     /* 使能系统时钟源选择 */
     CLK_SYSCLKSourceSwitchCmd(ENABLE);
     
     /* 系统时钟源选择LSI */
     CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);
     
     /* 设置系统分频系数 */
     CLK_SYSCLKDivConfig(CLK_SYSCLKDiv);
}

/********************************************** END OF FLEE **********************************************/
