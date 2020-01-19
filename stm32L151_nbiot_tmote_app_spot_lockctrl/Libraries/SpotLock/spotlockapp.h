#ifndef __SPOT_LOCK_APP_H
#define   __SPOT_LOCK_APP_H

#include "sys.h"
#include "spotlockconfig.h"

void SPOT_Lock_Initialization(void);

void SPOT_Lock_App_Task(void);

void SPOT_Lock_App_RISE(u32 timerSec);

void SPOT_Lock_App_FALL(u32 timerSec);

#endif /* __SPOT_LOCK_APP_H */
