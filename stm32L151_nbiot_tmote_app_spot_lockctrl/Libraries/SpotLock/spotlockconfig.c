/**
  *********************************************************************************************************
  * @file    spotlockconfig.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-16
  * @brief   车位锁控制器
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "spotlockconfig.h"

SpotLock_ClientsTypeDef SpotLockClientHandler;

/**********************************************************************************************************
 @Function			void SPOT_Lock_Client_Init(SpotLock_ClientsTypeDef* pClient)
 @Description			SPOT_Lock_Client_Init					: SpotLock客户端初始化
 @Input				pClient								: SpotLock客户端实例
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Client_Init(SpotLock_ClientsTypeDef* pClient)
{
	pClient->SpotLockState									= SPOTLOCK_CTRL_FALL;
	pClient->SpotLockControl									= SPOTLOCK_CTRL_FALL;
	
	pClient->ControlRISEEnable								= false;
	pClient->ControlFALLEnable								= false;
	
	
	
	
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient, u32 timerSec)
 @Description			SPOT_Lock_Client_ControlRISE				: SpotLock客户端控制升锁
 @Input				pClient								: SpotLock客户端实例
					timerSec								: SpotLock滞后升锁时间
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient, u32 timerSec)
{
	pClient->SpotLockControl									= SPOTLOCK_CTRL_RISE;
	
	pClient->ControlRISEEnable								= true;
	
	Stm32_Calculagraph_CountdownSec(&pClient->ControlRISEAfterS, timerSec);
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient, u32 timerSec)
 @Description			SPOT_Lock_Client_ControlFALL				: SpotLock客户端控制降锁
 @Input				pClient								: SpotLock客户端实例
					timerSec								: SpotLock保持降锁时间
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient, u32 timerSec)
{
	pClient->SpotLockControl									= SPOTLOCK_CTRL_FALL;
	
	pClient->ControlFALLEnable								= true;
	
	Stm32_Calculagraph_CountdownSec(&pClient->ControlFALLDelayS, timerSec);
}
















/********************************************** END OF FLEE **********************************************/
