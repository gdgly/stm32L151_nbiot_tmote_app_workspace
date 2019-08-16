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
	
	
	
	
	
	
	
	
	
	
	
	
	
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient)
 @Description			SPOT_Lock_Client_ControlRISE				: SpotLock客户端控制升锁
 @Input				pClient								: SpotLock客户端实例
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient)
{
	pClient->SpotLockControl									= SPOTLOCK_CTRL_RISE;
}

/**********************************************************************************************************
 @Function			void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient)
 @Description			SPOT_Lock_Client_ControlFALL				: SpotLock客户端控制降锁
 @Input				pClient								: SpotLock客户端实例
 @Return				void
**********************************************************************************************************/
void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient)
{
	pClient->SpotLockControl									= SPOTLOCK_CTRL_FALL;
}
















/********************************************** END OF FLEE **********************************************/
