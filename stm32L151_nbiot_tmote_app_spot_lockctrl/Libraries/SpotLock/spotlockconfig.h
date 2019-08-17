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




/* SpotLock Clients */
struct SpotLock_ClientsTypeDef
{
	MOTOR_SpotLockCtrlTypeDef			SpotLockState;
	MOTOR_SpotLockCtrlTypeDef			SpotLockControl;
	
	bool								ControlRISEEnable;
	bool								ControlFALLEnable;
	Stm32_CalculagraphTypeDef			ControlRISEAfterS;
	Stm32_CalculagraphTypeDef			ControlFALLDelayS;
	
	
	
	
};




extern SpotLock_ClientsTypeDef			SpotLockClientHandler;




void SPOT_Lock_Client_Init(SpotLock_ClientsTypeDef* pClient);

void SPOT_Lock_Client_ControlRISE(SpotLock_ClientsTypeDef* pClient, u32 timerSec);
void SPOT_Lock_Client_ControlFALL(SpotLock_ClientsTypeDef* pClient, u32 timerSec);



#endif /* __SPOT_LOCK_CONFIG_H */
