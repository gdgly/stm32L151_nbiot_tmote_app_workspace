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
	SPOT_Lock_Client_Init(&SpotLockClientHandler);
	
	MOTOR_SPOTLOCK_Initialization(SpotLockClientHandler.SpotLockControl);
	
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
	
	MOTOR_SPOTLOCK_Keep(SpotLockClientHandler.SpotLockControl);
	
	
	
	
	
	
	
	
	
	
	
	
	
}




















/********************************************** END OF FLEE **********************************************/
