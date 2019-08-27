/**
  *********************************************************************************************************
  * @file    hal_ook.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-27
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_ook.h"
#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"

uint32_t OOKDataFrameData = 0;
uint8_t  OOKDataFrameFlag = 0;

/**********************************************************************************************************
 @Function			void OOK_EXTI_Initialization(void)
 @Description			OOK_EXTI_Initialization
 @Input				void
 @Return				void
**********************************************************************************************************/
void OOK_EXTI_Initialization(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	OOK_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = OOK_PIN;
	GPIO_Initure.Mode = GPIO_MODE_IT_RISING;
	GPIO_Initure.Pull = GPIO_PULLDOWN;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(OOK_GPIOx, &GPIO_Initure);
	
	HAL_NVIC_SetPriority(OOK_DATA_IRQn, 2, 2);
	HAL_NVIC_EnableIRQ(OOK_DATA_IRQn);
}

/**********************************************************************************************************
 @Function			uint8_t OOK_EXTI_GetHighPulseTime(void)
 @Description			OOK_EXTI_GetHighPulseTime
 @Input				void
 @Return				Time
**********************************************************************************************************/
uint8_t OOK_EXTI_GetHighPulseTime(void)
{
	uint8_t time = 0;
	
	while ( OOK_DATA_IN() ) {
		time ++;
		Delay_US(18);
		
		if (time >= 250) return time;
	}
	
	return time;
}

/**********************************************************************************************************
 @Function			uint8_t OOK_EXTI_GetLowPulseTime(void)
 @Description			OOK_EXTI_GetLowPulseTime
 @Input				void
 @Return				Time
**********************************************************************************************************/
uint8_t OOK_EXTI_GetLowPulseTime(void)
{
	uint8_t time = 0;
	
	while ( !OOK_DATA_IN() ) {
		time ++;
		Delay_US(18);
		
		if (time >= 250) return time;
	}
	
	return time;
}

/**********************************************************************************************************
 @Function			uint32_t OOK_EXTI_Process(void)
 @Description			OOK_EXTI_Process
 @Input				void
 @Return				0	: Error
					!0	: Success
**********************************************************************************************************/
uint32_t OOK_EXTI_Process(void)
{
	uint8_t ookData[4];
	uint8_t ookDataCheck;
	
	ookData[0] = (OOKDataFrameData >> 24) & 0xFF;
	ookData[1] = (OOKDataFrameData >> 16) & 0xFF;
	ookData[2] = (OOKDataFrameData >>  8) & 0xFF;
	ookData[3] = (OOKDataFrameData >>  0) & 0xFF;
	
	ookDataCheck = ookData[0] + ookData[1] + ookData[2];
	
	if (ookDataCheck == ookData[3]) {
		return OOKDataFrameData;
	}
	
	return 0;
}


















/********************************************** END OF FLEE **********************************************/
