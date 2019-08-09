#ifndef __HAL_INFRARED_TUBE_H
#define   __HAL_INFRARED_TUBE_H

#include "sys.h"

#define OPT_K1_GPIOx					GPIOB
#define OPT_K1_PIN						GPIO_PIN_14
#define OPT_K1_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K1_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K2_GPIOx					GPIOB
#define OPT_K2_PIN						GPIO_PIN_15
#define OPT_K2_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K2_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K3_GPIOx					GPIOB
#define OPT_K3_PIN						GPIO_PIN_13
#define OPT_K3_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define OPT_K3_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define OPT_K1_IN()						HAL_GPIO_ReadPin(OPT_K1_GPIOx, OPT_K1_PIN)
#define OPT_K2_IN()						HAL_GPIO_ReadPin(OPT_K2_GPIOx, OPT_K2_PIN)
#define OPT_K3_OUT(n)					(n?HAL_GPIO_WritePin(OPT_K3_GPIOx, OPT_K3_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(OPT_K3_GPIOx, OPT_K3_PIN, GPIO_PIN_RESET))

#define INFRARED_TUBE_TRANSMIT_ENABLE()		InfraredTube_OPT_K3_OUT(ON)
#define INFRARED_TUBE_TRANSMIT_DISABLE()	InfraredTube_OPT_K3_OUT(OFF)

#define INFRARED_TUBE_RECEIVE_STATE()		InfraredTube_SpotLock_Read()
#define INFRARED_TUBE_SPOTLOCK_STATE()		InfraredTube_SpotLock_State()

/* Infrared Tube Status */
typedef enum
{
	INFRARED_TUBE_ERROR					= 0x00,
	INFRARED_TUBE_PROCESS				= 0x01,
	INFRARED_TUBE_RISE					= 0x02,
	INFRARED_TUBE_FALL					= 0x03
}INFRARED_Tube_StatusTypeDef;

void InfraredTube_OPT_K3_OUT(u8 enable);									//红外对管发射管输出控制

u8 InfraredTube_OPT_K1_IN(void);											//红外对管接收管输入
u8 InfraredTube_OPT_K2_IN(void);											//红外对管接收管输入

INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_Read(void);					//车位锁状态读取
INFRARED_Tube_StatusTypeDef InfraredTube_SpotLock_State(void);					//车位锁状态读取











#endif /* __HAL_INFRARED_TUBE_H */
