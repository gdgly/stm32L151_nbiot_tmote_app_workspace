/**
  *********************************************************************************************************
  * @file    hal_infraredtube.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-05
  * @brief   
  *********************************************************************************************************
  * @attention
  *		  OPT_K1	---> In  PB14
  *		  OPT_K2	---> In  PB15
  *		  OPT_K3	---> Out PB13
  *
  *********************************************************************************************************
  */

#include "hal_infraredtube.h"
#include "platform_config.h"
#include "platform_map.h"

/**********************************************************************************************************
 @Function			void InfraredTube_OPT_K3_OUT(u8 enable)
 @Description			红外对管发射管输出控制
 @Input				ON or OFF
 @Return				void
**********************************************************************************************************/
void InfraredTube_OPT_K3_OUT(u8 enable)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	OPT_K3_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = OPT_K3_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(OPT_K3_GPIOx, &GPIO_Initure);
	
	OPT_K3_OUT(enable);
}

/**********************************************************************************************************
 @Function			u8 InfraredTube_OPT_K1_IN(void)
 @Description			红外对管接收管输入
 @Input				void
 @Return				IN
**********************************************************************************************************/
u8 InfraredTube_OPT_K1_IN(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	OPT_K1_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = OPT_K1_PIN;
	GPIO_Initure.Mode = GPIO_MODE_INPUT;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(OPT_K1_GPIOx, &GPIO_Initure);
	
	return OPT_K1_IN();
}

/**********************************************************************************************************
 @Function			u8 InfraredTube_OPT_K2_IN(void)
 @Description			红外对管接收管输入
 @Input				void
 @Return				IN
**********************************************************************************************************/
u8 InfraredTube_OPT_K2_IN(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	OPT_K2_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = OPT_K2_PIN;
	GPIO_Initure.Mode = GPIO_MODE_INPUT;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(OPT_K2_GPIOx, &GPIO_Initure);
	
	return OPT_K2_IN();
}




































/********************************************** END OF FLEE **********************************************/
