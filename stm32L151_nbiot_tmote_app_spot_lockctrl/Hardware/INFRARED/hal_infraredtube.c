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
	
	InfraredTube_OPT_K1_IN();
	InfraredTube_OPT_K2_IN();
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

/**********************************************************************************************************
 @Function			INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_Read(void)
 @Description			InfraredTube_SpotLock_Read					: 车位锁状态读取
 @Input				void
 @Return				INFRARED_Tube_StatusTypeDef
**********************************************************************************************************/
INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_Read(void)
{
	u8 OPTK1 = OPT_K1_IN();
	u8 OPTK2 = OPT_K2_IN();
	
	if (OPTK1 == 0) {
		if (OPTK2 == 0) return INFRARED_TUBE_ERROR;			/* K1: 0, K2: 0 */
		else return INFRARED_TUBE_PROCESS;					/* K1: 0, K2: 1 */
	}
	else {
		if (OPTK2 == 0) return INFRARED_TUBE_RISE;			/* K1: 1, K2: 0 */
		else return INFRARED_TUBE_FALL;					/* K1: 1, K2: 1 */
	}
}

/**********************************************************************************************************
 @Function			INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_State(void)
 @Description			InfraredTube_SpotLock_State					: 车位锁状态读取
 @Input				void
 @Return				INFRARED_Tube_StatusTypeDef
**********************************************************************************************************/
INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_State(void)
{
	INFRARED_Tube_StatusTypeDef SpotLockState;
	
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	SpotLockState = InfraredTube_SpotLock_Read();
	
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	return SpotLockState;
}


































/********************************************** END OF FLEE **********************************************/
