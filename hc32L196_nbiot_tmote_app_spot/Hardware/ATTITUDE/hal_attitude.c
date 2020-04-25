/**
  *********************************************************************************************************
  * @file    hal_attitude.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-25
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_attitude.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void Attitude_Detection_Init(void)
 @Description			Attitude_Detection_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void Attitude_Detection_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(ATTITUDE_DETECTION_GPIOx, ATTITUDE_DETECTION_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void Attitude_Detection_DeInit(void)
 @Description			Attitude_Detection_DeInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void Attitude_Detection_DeInit(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(ATTITUDE_DETECTION_GPIOx, ATTITUDE_DETECTION_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			u8 Attitude_Detection_Read(void)
 @Description			Attitude_Detection_Read
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Attitude_Detection_Read(void)
{
	u8 ret = 0;
	
	Attitude_Detection_Init();
	
	ret = ATTITUDE_DETECTION_READ();
	
	Attitude_Detection_DeInit();
	
	return ret;
}

/********************************************** END OF FLEE **********************************************/
