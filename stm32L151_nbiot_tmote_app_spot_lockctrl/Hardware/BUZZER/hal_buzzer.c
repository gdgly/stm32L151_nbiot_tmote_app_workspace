/**
  *********************************************************************************************************
  * @file    hal_buzzer.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-06
  * @brief   
  *********************************************************************************************************
  * @attention
  *		  BUZZER ---> PA12
  *
  *
  *********************************************************************************************************
  */

#include "hal_buzzer.h"
#include "platform_config.h"
#include "platform_map.h"

/**********************************************************************************************************
 @Function			void BUZZERCtrlIO(u8 enable)
 @Description			BUZZERCtrlIO
 @Input				ON or OFF
 @Return				void
**********************************************************************************************************/
void BUZZERCtrlIO(u8 enable)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	BUZZER_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = BUZZER_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(BUZZER_GPIOx, &GPIO_Initure);
	
	BUZZER(enable);
}

/********************************************** END OF FLEE **********************************************/
