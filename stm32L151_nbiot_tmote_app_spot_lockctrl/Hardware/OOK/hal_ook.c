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
#include "hal_iwdg.h"
#include "hal_beep.h"
#include "radio_hal_rf.h"
#include "radio_rf_app.h"
#include "spotlockconfig.h"
#include "spotlockapp.h"
#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"

uint32_t OOKDataFrameData = 0;
uint8_t  OOKDataFrameFlag = 0;
uint8_t  OOKDataRecvdFlag = 0;

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
	
	OOK_EXTI_PollExecution(true);
}

/**********************************************************************************************************
 @Function			void OOK_EXTI_PollExecution(bool EnableEEPROMCode)
 @Description			OOK_EXTI_PollExecution
 @Input				EnableEEPROMCode
 @Return				void
**********************************************************************************************************/
void OOK_EXTI_PollExecution(bool EnableEEPROMCode)
{
	uint32_t OOKCode;
	uint32_t OOKArr[5] = {1, 2, 3, 4, 5};
	Stm32_CalculagraphTypeDef BeepTime;
	Stm32_CalculagraphTypeDef EncodeTime;
	
#ifdef OOK_DEBUG_LOG_RF_PRINT
	//OOK_DEBUG_LOG_PRINTF("Remote code: 0x%08X", TCFG_EEPROM_GetOOKEncoded());
#endif
	
	if (OOK_EXTI_GetFrameFlag()) {
		OOKCode = OOK_EXTI_Process();
		if ((OOKCode & 0xFFFFF000) == TCFG_EEPROM_GetOOKEncoded()) {
			if ((OOKCode & (~0xFFFFF0FF)) == 0x0400) {
				SPOT_Lock_App_FALL(300);
			}
			if ((OOKCode & (~0xFFFFF0FF)) == 0x0100) {
				SPOT_Lock_App_RISE(0);
			}
		}
		OOK_EXTI_SetFrameFlag(0);
	}
	
	if (EnableEEPROMCode && (TCFG_EEPROM_GetOOKEncoded() != 0)) return;
	
	if ((!EnableEEPROMCode) && (OOK_EXTI_GetRecvdFlag() != 1)) return;
	
	Stm32_Calculagraph_CountdownSec(&BeepTime, OOK_ENCODED_BEEPDELAY_SEC);
	Stm32_Calculagraph_CountdownSec(&EncodeTime, OOK_ENCODED_EXECUTION_SEC);
	
	while (1) {
		IWDG_Feed();
		
		if (OOK_EXTI_GetFrameFlag()) {
			OOKArr[0] = OOKArr[1];
			OOKArr[1] = OOKArr[2];
			OOKArr[2] = OOKArr[3];
			OOKArr[3] = OOKArr[4];
			OOKArr[4] = OOK_EXTI_Process();
			OOK_EXTI_SetFrameFlag(0);
		}
		
		if ((OOKArr[0] != 0) && (OOKArr[0] == OOKArr[1]) && (OOKArr[1] == OOKArr[2]) && (OOKArr[2] == OOKArr[3]) && (OOKArr[3] == OOKArr[4])) {
			TCFG_EEPROM_SetOOKEncoded(0xFFFFF000 & OOKArr[0]);
#ifdef OOK_DEBUG_LOG_RF_PRINT
			OOK_DEBUG_LOG_PRINTF("Remote code: 0x%08X", TCFG_EEPROM_GetOOKEncoded());
#endif
			BEEP_CtrlRepeat_Extend(5, 50, 25);
			break;
		}
		
		if (Stm32_Calculagraph_IsExpiredSec(&BeepTime)) {
#ifdef OOK_DEBUG_LOG_RF_PRINT
			OOK_DEBUG_LOG_PRINTF("Please press the remote control");
#endif
			BEEP_CtrlRepeat_Extend(2, 50, 50);
			Stm32_Calculagraph_CountdownSec(&BeepTime, OOK_ENCODED_BEEPDELAY_SEC);
		}
		
		if (Stm32_Calculagraph_IsExpiredSec(&EncodeTime)) {
#ifdef OOK_DEBUG_LOG_RF_PRINT
			OOK_DEBUG_LOG_PRINTF("Remote control code not received");
#endif
			BEEP_CtrlRepeat_Extend(1, 500, 10);
			break;
		}
	}
	
	OOK_EXTI_SetRecvdFlag(0);
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
