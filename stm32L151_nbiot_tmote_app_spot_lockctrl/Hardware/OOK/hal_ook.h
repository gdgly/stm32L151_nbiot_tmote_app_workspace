#ifndef __HAL_OOK_H
#define   __HAL_OOK_H

#include "sys.h"

#define OOK_DEBUG_LOG_RF_PRINT
#define OOK_DEBUG_LOG_PRINTF				Radio_Trf_Printf

#define OOK_ENCODED_EEPROM_MAX			5
#define OOK_ENCODED_EEPROM_DEFAULT			2

#define OOK_ENCODED_BEEPDELAY_SEC			5
#define OOK_ENCODED_RXECUTION_SEC			20
#define OOK_ENCODED_EXECUTION_SEC			60

#define OOK_GPIOx						GPIOB
#define OOK_PIN						GPIO_PIN_5
#define OOK_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define OOK_RCC_GPIO_CLK_DISABLE()			__HAL_RCC_GPIOB_CLK_DISABLE()

#define OOK_DATA_IN()					HAL_GPIO_ReadPin(OOK_GPIOx, OOK_PIN)

#define OOK_DATA_IRQn					EXTI9_5_IRQn

#define OOK_EXTI_SetFrameFlag(n)			(OOKDataFrameFlag = n)
#define OOK_EXTI_GetFrameFlag()			(OOKDataFrameFlag)

#define OOK_EXTI_SetRecvdFlag(n)			(OOKDataRecvdFlag = n)
#define OOK_EXTI_GetRecvdFlag()			(OOKDataRecvdFlag)

#define OOK_EXTI_SetMotorFlag(n)			(OOKDataMotorFlag = n)
#define OOK_EXTI_GetMotorFlag()			(OOKDataMotorFlag)

extern uint32_t OOKDataFrameData;
extern uint8_t  OOKDataFrameFlag;
extern uint8_t  OOKDataRecvdFlag;
extern uint8_t  OOKDataMotorFlag;

void OOK_EXTI_Initialization(void);

void OOK_EXTI_PollExecution(bool EnableEEPROMCode);

void OOK_EXTI_IRQPollExecution(bool EnableEEPROMCode);

uint8_t OOK_EXTI_GetHighPulseTime(void);
uint8_t OOK_EXTI_GetLowPulseTime(void);

uint32_t OOK_EXTI_Process(void);

#endif /* __HAL_OOK_H */
