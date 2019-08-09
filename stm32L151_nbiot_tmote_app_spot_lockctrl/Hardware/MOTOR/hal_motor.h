#ifndef __HAL_MOTOR_H
#define   __HAL_MOTOR_H

#include "sys.h"

#define MOTOR_SNS_GPIOx					GPIOB
#define MOTOR_SNS_PIN					GPIO_PIN_0
#define MOTOR_SNS_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTOR_SNS_RCC_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()
#define MOTOR_SNS_RCC_ADC1_CLK_ENABLE()		__HAL_RCC_ADC1_CLK_ENABLE()
#define MOTOR_SNS_RCC_ADC1_CLK_DISABLE()	__HAL_RCC_ADC1_CLK_DISABLE()

#define MOTOR_BI_GPIOx					GPIOB
#define MOTOR_BI_PIN					GPIO_PIN_9
#define MOTOR_BI_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTOR_BI_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define MOTOR_FI_GPIOx					GPIOB
#define MOTOR_FI_PIN					GPIO_PIN_8
#define MOTOR_FI_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTOR_FI_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define MOTOR_BI(n)						(n?HAL_GPIO_WritePin(MOTOR_BI_GPIOx, MOTOR_BI_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(MOTOR_BI_GPIOx, MOTOR_BI_PIN, GPIO_PIN_RESET))
#define MOTOR_FI(n)						(n?HAL_GPIO_WritePin(MOTOR_FI_GPIOx, MOTOR_FI_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(MOTOR_FI_GPIOx, MOTOR_FI_PIN, GPIO_PIN_RESET))

#define MOTOR_RISE()					{MOTOR_FI_OUT(OFF); MOTOR_BI_OUT(ON); }																							//升锁
#define MOTOR_FALL()					{MOTOR_BI_OUT(OFF); MOTOR_FI_OUT(ON); }																							//降锁

#define MOTOR_LOCK()					{MOTOR_BI_OUT(ON);  MOTOR_FI_OUT(ON); }																							//电机锁定
#define MOTOR_OPEN()					{MOTOR_BI_OUT(OFF); MOTOR_FI_OUT(OFF);}																							//电机开路

/* Motor SpotLock Ctrl Status */
typedef enum
{
	SPOTLOCK_CTRL_FALL					= 0x00,																													//降锁态
	SPOTLOCK_CTRL_RISE					= 0x01																													//升锁态
}MOTOR_SpotLockCtrlTypeDef;

extern ADC_HandleTypeDef		MOTOR_SNS_Handler;

void MOTOR_SNS_Init(void);
u16  MOTOR_SNS_Read(u32 timeout);




void MOTOR_BI_OUT(u8 val);
void MOTOR_FI_OUT(u8 val);




void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl);																										//车位锁初始化锁态
void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl);																											//车位锁控制锁态






#endif /* __HAL_MOTOR_H */
