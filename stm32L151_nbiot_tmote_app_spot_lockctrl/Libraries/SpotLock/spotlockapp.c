/**
  *********************************************************************************************************
  * @file    spotlockapp.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-16
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "spotlockapp.h"
#include "platform_config.h"
#include "platform_map.h"
#include "radio_hal_rf.h"
#include "radio_rf_app.h"
#include "inspectconfig.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void SPOT_Lock_Initialization(void)
 @Description			SPOT_Lock_Initialization
 @Input				void
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Initialization(void)
{
	/* Spot Lock Client Init */
	SPOT_Lock_Client_Init(&SpotLockClientHandler);
	
	/* Spot Lock Motor Init */
	MOTOR_SPOTLOCK_Initialization(SpotLockClientHandler.SpotLockControl);
	
	/* Spot Lock Get SpotLockState & SpotLockControl */
	SpotLockClientHandler.SpotLockState	= MOTOR_SPOTLOCK_STATE();
	SpotLockClientHandler.SpotLockControl	= MOTOR_SPOTLOCK_STATE();
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_App_Task(void)
 @Description			SPOT_Lock_App_Task
 @Input				void
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_App_Task(void)
{
	if (SpotLockClientHandler.SpotLockState != SpotLockClientHandler.SpotLockControl) {
		if ((SpotLockClientHandler.SpotLockControl == SPOTLOCK_CTRL_RISE) && (SpotLockClientHandler.ControlRISEEnable == false)) {
			
			MOTOR_SPOTLOCK_Control(SPOTLOCK_CTRL_RISE);
			
			SpotLockClientHandler.SpotLockState	= MOTOR_SPOTLOCK_STATE();
			SpotLockClientHandler.SpotLockControl	= MOTOR_SPOTLOCK_STATE();
		}
		
		if (SpotLockClientHandler.SpotLockControl == SPOTLOCK_CTRL_FALL) {
			
			MOTOR_SPOTLOCK_Control(SPOTLOCK_CTRL_FALL);
			
			SpotLockClientHandler.SpotLockState	= MOTOR_SPOTLOCK_STATE();
			SpotLockClientHandler.SpotLockControl	= MOTOR_SPOTLOCK_STATE();
		}
	}
	
	if ((SpotLockClientHandler.ControlFALLEnable != true) && (SpotLockClientHandler.ControlRISEEnable != true) && (talgo_get_spotstatus() == 0)) {
		SPOT_Lock_Client_ControlRISE(&SpotLockClientHandler, 3);
	}
	
	if ((SpotLockClientHandler.ControlFALLEnable == true) && (Stm32_Calculagraph_IsExpiredSec(&SpotLockClientHandler.ControlFALLDelayS) == true)) {
		SpotLockClientHandler.ControlFALLEnable = false;
	}
	
	if ((SpotLockClientHandler.ControlRISEEnable == true) && (Stm32_Calculagraph_IsExpiredSec(&SpotLockClientHandler.ControlRISEAfterS) == true)) {
		SpotLockClientHandler.ControlRISEEnable = false;
	}
	
	
	
	
	
	
	MOTOR_SPOTLOCK_Keep(SpotLockClientHandler.SpotLockState);
	
	
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_App_RISE(u32 timerSec)
 @Description			SPOT_Lock_App_RISE
 @Input				timerSec
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_App_RISE(u32 timerSec)
{
	SPOT_Lock_Client_ControlRISE(&SpotLockClientHandler, timerSec);
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_App_FALL(u32 timerSec)
 @Description			SPOT_Lock_App_FALL
 @Input				timerSec
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_App_FALL(u32 timerSec)
{
	SPOT_Lock_Client_ControlFALL(&SpotLockClientHandler, timerSec);
}


































/********************************************** END OF FLEE **********************************************/