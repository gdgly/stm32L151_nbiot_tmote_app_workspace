/**
  *********************************************************************************************************
  * @file    hal_beep.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-04
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_beep.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void BEEP_GPIO_InitControl(bool ctrl)
 @Description			BEEP_GPIO_InitControl						: 蜂鸣器GPIO初始化控制
 @Input				void
 @Return				void
**********************************************************************************************************/
void BEEP_GPIO_InitControl(bool ctrl)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	
	if (ctrl)
		Gpio_SetIO(BEEP_GPIOx, BEEP_PIN);
	else
		Gpio_ClrIO(BEEP_GPIOx, BEEP_PIN);
	
	Gpio_Init(BEEP_GPIOx, BEEP_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			static void BEEP_Passive_Control(u16 bnMs)
 @Description			BEEP_Passive_Control						: 蜂鸣器无源响
 @Input				bnMs										: Beep时间
 @Return				void
**********************************************************************************************************/
static void BEEP_Passive_Control(u16 bnMs)
{
	for (u16 nCount = 0; nCount < (bnMs * 2); nCount++) {
#if BEEP_OUTPUT_TYPE
		Gpio_SetIO(BEEP_GPIOx, BEEP_PIN);
#else
		M0P_GPIO->PBOUT |=  (1<<8);
#endif
		Delay_US(BEEP_PASSIVE_ON);
#if BEEP_OUTPUT_TYPE
		Gpio_ClrIO(BEEP_GPIOx, BEEP_PIN);
#else
		M0P_GPIO->PBOUT &= ~(1<<8);
#endif
		Delay_US(BEEP_PASSIVE_OFF);
	}
}

/**********************************************************************************************************
 @Function			void BEEP_Repeat_Control(u16 nCount, u16 speaknMs, u16 shutnMs)
 @Description			BEEP_Repeat_Control							: 蜂鸣器控制重复响
 @Input				nCount									: Beep次数
					speaknMs									: 间隔鸣
					shutnMs									: 间隔闭
 @Return				void
**********************************************************************************************************/
void BEEP_Repeat_Control(u16 nCount, u16 speaknMs, u16 shutnMs)
{
	BEEP_GPIO_InitControl(false);
	
	for (u16 index = 0; index < nCount; index++) {
#if BEEP_MODEL_TYPE
		BEEP_Passive_Control(speaknMs);
		Delay_MS(shutnMs);
#else
		Gpio_SetIO(BEEP_GPIOx, BEEP_PIN);
		Delay_MS(speaknMs);
		Gpio_ClrIO(BEEP_GPIOx, BEEP_PIN);
		Delay_MS(shutnMs);
#endif
	}
}

/********************************************** END OF FLEE **********************************************/
