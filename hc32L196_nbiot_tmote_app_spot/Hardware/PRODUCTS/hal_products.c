/**
  *********************************************************************************************************
  * @file    hal_products.c
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
#include "hal_products.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void Products_Detection_Init(void)
 @Description			Products_Detection_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void Products_Detection_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(PRODUCTS_DETECTION_GPIOx, PRODUCTS_DETECTION_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void Products_Detection_DeInit(void)
 @Description			Products_Detection_DeInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void Products_Detection_DeInit(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(PRODUCTS_DETECTION_GPIOx, PRODUCTS_DETECTION_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			u8 Products_Detection_Read(void)
 @Description			Products_Detection_Read
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 Products_Detection_Read(void)
{
	u8 ret = 0;
	
	Products_Detection_Init();
	
	ret = PRODUCTS_DETECTION_READ();
	
	Products_Detection_DeInit();
	
	return ret;
}

/********************************************** END OF FLEE **********************************************/
