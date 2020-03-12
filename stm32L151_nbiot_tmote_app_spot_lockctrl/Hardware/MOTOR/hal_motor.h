#ifndef __HAL_MOTOR_H
#define   __HAL_MOTOR_H

#include "sys.h"

#define MOTOR_DEVICE_TYPE1				0
#define MOTOR_DEVICE_TYPE2				1
#define MOTOR_DEVICE_TYPE				MOTOR_DEVICE_TYPE2																											//电机设备模式(不同锁电机设备不同使用不同模式)

#define MOTOR_BEEP_CTRL_ON				1
#define MOTOR_BEEP_CTRL_OFF				0
#define MOTOR_BEEP_CTRL					MOTOR_BEEP_CTRL_ON																											//电机完成摇臂状态控制蜂鸣器提醒

#define MOTOR_BUZZER_ERR_ON				1																														//外部BUZZER
#define MOTOR_BUZZER_ERR_OFF				0																														//内部BEEP
#define MOTOR_BUZZER_ERR					MOTOR_BUZZER_ERR_ON																											//选择使用外部BUZZER警报器警报

#define MOTOR_ERROR_DELAY_MS				8000																														//单次电机控制超时时间(该时间内电机状态转变未完成将退出)

#define MOTOR_SNS_THRESHOLD_DELAY_MS		300																														//电机控制中电流SNS过大超时时间
#define MOTOR_SNS_THRESHOLD_VOLTAGE		10																														//电机控制中电流SNS过大阈值

#define MOTOR_SNS_READ_VOLTAGE_DELAY_MS		100																														//电机控制中ADC读取电流SNS时间

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

#define MOTOR_CTRL_KEEP_MODE1				0																														//持续控制直到异常
#define MOTOR_CTRL_KEEP_MODE2				1																														//感知阻尼停止控制
#define MOTOR_CTRL_KEEP_MODE				MOTOR_CTRL_KEEP_MODE2																										//电机控制摇臂保持状态模式

#define MOTOR_CTRL_KEEP_ERR_CNT			5																														//电机控制摇臂异常最大次数

#define MOTOR_CTRL_TYPE1					0
#define MOTOR_CTRL_TYPE2					1
#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE1
#define MOTOR_CTRL_TYPE					MOTOR_CTRL_TYPE1																											//电机正反转模式
#endif
#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE2
#define MOTOR_CTRL_TYPE					MOTOR_CTRL_TYPE2																											//电机正反转模式
#endif

#if MOTOR_CTRL_TYPE == MOTOR_CTRL_TYPE1																																//电机正反转模式1
#define MOTOR_RISE()					{MOTOR_FI_OUT(OFF); MOTOR_BI_OUT(ON); }																							//升锁
#define MOTOR_FALL()					{MOTOR_BI_OUT(OFF); MOTOR_FI_OUT(ON); }																							//降锁
#endif

#if MOTOR_CTRL_TYPE == MOTOR_CTRL_TYPE2																																//电机正反转模式2
#define MOTOR_RISE()					{MOTOR_BI_OUT(OFF); MOTOR_FI_OUT(ON); }																							//升锁
#define MOTOR_FALL()					{MOTOR_FI_OUT(OFF); MOTOR_BI_OUT(ON); }																							//降锁
#endif

#define MOTOR_LOCK()					{MOTOR_BI_OUT(ON);  MOTOR_FI_OUT(ON); }																							//电机锁定
#define MOTOR_OPEN()					{MOTOR_BI_OUT(OFF); MOTOR_FI_OUT(OFF);}																							//电机开路

#define MOTOR_SPOTLOCK_STATE()			((INFRARED_TUBE_SPOTLOCK_STATE() == INFRARED_TUBE_FALL) ? SPOTLOCK_CTRL_FALL : SPOTLOCK_CTRL_RISE)											//车锁状态

/* Motor SpotLock Ctrl Status */
typedef enum
{
	SPOTLOCK_CTRL_FALL					= 0x00,																													//降锁态
	SPOTLOCK_CTRL_RISE					= 0x01																													//升锁态
}MOTOR_SpotLockCtrlTypeDef;

extern ADC_HandleTypeDef		MOTOR_SNS_Handler;																														//电机SNS电流值ADCHander

void MOTOR_SNS_Init(void);																																		//电机SNS电流值初始化
u16  MOTOR_SNS_Read(u32 timeout);																																	//电机SNS电流值读取

void MOTOR_BI_OUT(u8 val);																																		//电机BI驱动
void MOTOR_FI_OUT(u8 val);																																		//电机FI驱动

void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl);																										//车位锁初始锁态
void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl);																											//车位锁控制锁态
void MOTOR_SPOTLOCK_Keep(MOTOR_SpotLockCtrlTypeDef ctrl);																												//车位锁保持锁态

#endif /* __HAL_MOTOR_H */
