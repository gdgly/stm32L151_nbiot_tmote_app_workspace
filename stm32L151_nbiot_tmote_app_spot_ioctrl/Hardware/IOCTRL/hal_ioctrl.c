/**
  *********************************************************************************************************
  * @file    hal_ioctrl.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-07-06
  * @brief   
  *********************************************************************************************************
  * @attention
  *		  
  *
  *********************************************************************************************************
  */

#include "hal_ioctrl.h"

bool IOControlIO1State = false;
bool IOControlIO2State = false;
Stm32_CalculagraphTypeDef	IOControlIO1Time;
Stm32_CalculagraphTypeDef	IOControlIO2Time;

/**********************************************************************************************************
 @Function			void IOControl_IO1_HIGH(void)
 @Description			IOControl_IO1_HIGH
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO1_HIGH(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	IOCTRL_IO1_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = IOCTRL_IO1_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(IOCTRL_IO1_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(IOCTRL_IO1_GPIOx, IOCTRL_IO1_PIN, GPIO_PIN_SET);
}

/**********************************************************************************************************
 @Function			void IOControl_IO1_LOW(void)
 @Description			IOControl_IO1_LOW
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO1_LOW(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	IOCTRL_IO1_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = IOCTRL_IO1_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(IOCTRL_IO1_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(IOCTRL_IO1_GPIOx, IOCTRL_IO1_PIN, GPIO_PIN_RESET);
}

/**********************************************************************************************************
 @Function			void IOControl_IO2_HIGH(void)
 @Description			IOControl_IO2_HIGH
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO2_HIGH(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	IOCTRL_IO2_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = IOCTRL_IO2_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(IOCTRL_IO2_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(IOCTRL_IO2_GPIOx, IOCTRL_IO2_PIN, GPIO_PIN_SET);
}

/**********************************************************************************************************
 @Function			void IOControl_IO2_LOW(void)
 @Description			IOControl_IO2_LOW
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO2_LOW(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	IOCTRL_IO2_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = IOCTRL_IO2_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(IOCTRL_IO2_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(IOCTRL_IO2_GPIOx, IOCTRL_IO2_PIN, GPIO_PIN_RESET);
}

/**********************************************************************************************************
 @Function			void IOControl_IO1_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
 @Description			IOControl_IO1_Activate
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO1_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
{
	IOControl_IO1_HIGH();
	
	Stm32_Calculagraph_CountdownSec(timer, timeout_sec);
	
	IOControlIO1State = true;
}

/**********************************************************************************************************
 @Function			void IOControl_IO2_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
 @Description			IOControl_IO2_Activate
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO2_Activate(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
{
	IOControl_IO2_HIGH();
	
	Stm32_Calculagraph_CountdownSec(timer, timeout_sec);
	
	IOControlIO2State = true;
}

/**********************************************************************************************************
 @Function			void IOControl_IO1_Check(Stm32_CalculagraphTypeDef* timer)
 @Description			IOControl_IO1_Check
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO1_Check(Stm32_CalculagraphTypeDef* timer)
{
	if (IOControlIO1State != true) return;
	
	if (Stm32_Calculagraph_IsExpiredSec(timer) != false) {
		IOControl_IO1_LOW();
		
		IOControlIO1State = false;
	}
	else {
		IOControl_IO1_HIGH();
	}
}

/**********************************************************************************************************
 @Function			void IOControl_IO2_Check(Stm32_CalculagraphTypeDef* timer)
 @Description			IOControl_IO2_Check
 @Input				void
 @Return				void
**********************************************************************************************************/
void IOControl_IO2_Check(Stm32_CalculagraphTypeDef* timer)
{
	if (IOControlIO2State != true) return;
	
	if (Stm32_Calculagraph_IsExpiredSec(timer) != false) {
		IOControl_IO2_LOW();
		
		IOControlIO2State = false;
	}
	else {
		IOControl_IO2_HIGH();
	}
}

/**********************************************************************************************************
 @Function			bool IOControl_IO1_State(void)
 @Description			IOControl_IO1_State
 @Input				void
 @Return				void
**********************************************************************************************************/
bool IOControl_IO1_State(void)
{
	return IOControlIO1State;
}

/**********************************************************************************************************
 @Function			bool IOControl_IO2_State(void)
 @Description			IOControl_IO2_State
 @Input				void
 @Return				void
**********************************************************************************************************/
bool IOControl_IO2_State(void)
{
	return IOControlIO2State;
}

/********************************************** END OF FLEE **********************************************/
