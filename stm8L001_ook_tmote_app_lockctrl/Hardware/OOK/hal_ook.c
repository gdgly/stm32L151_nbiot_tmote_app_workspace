/**
  *********************************************************************************************************
  * @file    hal_ook.c
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

#include "hal_ook.h"

/**********************************************************************************************************
 @Function			void Stm8_OOK_Init(void)
 @Description			Stm8_OOK_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void Stm8_OOK_Init(void)
{
     GPIO_Init(OOK_DATA_RX_PORT, OOK_DATA_RX_PINS, GPIO_Mode_In_FL_No_IT);
     
     GPIO_Init(OOK_DATA_TX_PORT, OOK_DATA_TX_PINS, GPIO_Mode_Out_PP_High_Fast);
}



















/********************************************** END OF FLEE **********************************************/
