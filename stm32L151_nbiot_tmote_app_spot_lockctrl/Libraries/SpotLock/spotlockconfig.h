#ifndef __SPOT_LOCK_CONFIG_H
#define   __SPOT_LOCK_CONFIG_H

#include "sys.h"
#include "hal_infraredtube.h"
#include "hal_buzzer.h"
#include "hal_motor.h"



typedef struct SpotLock_ClientsTypeDef		SpotLock_ClientsTypeDef;




/* SpotLock Status */
typedef enum
{
	SPOT_LOCK_OK						= 0x00,
	SPOT_LOCK_ERROR					= 0x01
}SpotLock_StatusTypeDef;

/* SpotLock State Flag */
typedef enum
{
	SPOT_LOCK_NONE						= 0x00,
	SPOT_LOCK_RISE						= 0x01,
	SPOT_LOCK_FALL						= 0x02
}SpotLock_StateFlagTypeDef;




/* SpotLock Clients */
struct SpotLock_ClientsTypeDef
{
	MOTOR_SpotLockCtrlTypeDef			SpotLockState;
	MOTOR_SpotLockCtrlTypeDef			SpotLockControl;
	
	bool								ControlRISEEnable;
	bool								ControlFALLEnable;
	Stm32_CalculagraphTypeDef			ControlRISEAfterS;
	Stm32_CalculagraphTypeDef			ControlFALLDelayS;
	
	SpotLock_StateFlagTypeDef			SpotLockStateFlag;
	
	
};




extern SpotLock_ClientsTypeDef			SpotLockClientHandler;




void SPOT_Lock_Client_Init(SpotLock_ClientsTypeDef* pClient);

void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient, u32 timerSec);
void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient, u32 timerSec);

SpotLock_StateFlagTypeDef SPOT_Lock_Client_SetStateFlag(SpotLock_ClientsTypeDef* pClient, SpotLock_StateFlagTypeDef LockState);
SpotLock_StateFlagTypeDef SPOT_Lock_Client_GetStateFlag(SpotLock_ClientsTypeDef* pClient);






#endif /* __SPOT_LOCK_CONFIG_H */
