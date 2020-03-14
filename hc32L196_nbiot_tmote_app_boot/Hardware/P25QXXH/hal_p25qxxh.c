/**
  *********************************************************************************************************
  * @file    hal_bl24cxxp.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-13
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_p25qxxh.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void P25QXXH_Port_Init(void)
 @Description			P25QXXH_Port_Init							: P25QXXH引脚初始化
 @Input				void
 @Return				void
 @attention			P25QXXH_NSS => PB12
**********************************************************************************************************/
static void P25QXXH_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* P25QXXH_NSS => PB12 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, P25QXXH_SPIx_NSS_AF);
	
	P25QXXH_SPIx_NSS_DISABLE();
}
























/********************************************** END OF FLEE **********************************************/
