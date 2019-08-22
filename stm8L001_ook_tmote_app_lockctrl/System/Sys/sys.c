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
     CLK_HSICmd(ENABLE);
     
     CLK_SYSCLKSourceSwitchCmd(ENABLE);
     
     CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
     
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
     CLK_LSICmd(ENABLE);
     
     CLK_SYSCLKSourceSwitchCmd(ENABLE);
     
     CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);
     
     CLK_SYSCLKDivConfig(CLK_SYSCLKDiv);
}










/********************************************** END OF FLEE **********************************************/
