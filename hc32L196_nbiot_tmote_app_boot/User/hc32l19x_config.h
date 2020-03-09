#ifndef __HC32L19X_CONFIG_H
#define   __HC32L19X_CONFIG_H

#include "sys.h"















typedef enum
{
	RCC_RESET_FLAG_NONE			= 0x00,													/*!< None Reset Flag				*/
	RCC_RESET_FLAG_IWDGRST		= 0x01,													/*!< Independent Watchdog Reset Flag	*/
	RCC_RESET_FLAG_SFTRST		= 0x02,													/*!< Software Reset Flag				*/
	RCC_RESET_FLAG_PORRST		= 0x04,													/*!< POR/PDR Reset Flag				*/
	RCC_RESET_FLAG_PINRST		= 0x08,													/*!< PIN Reset Flag					*/
	RCC_RESET_FLAG_LPWRRST		= 0x03,													/*!< Low-Power Reset Flag			*/
	RCC_RESET_FLAG_PCA			= 0x05,													/*!< Options Bytes Loading Reset Flag	*/
	RCC_RESET_FLAG_LOCKUP		= 0x09													/*!< CPU Lockup Reset Flag			*/
}HC32_RESET_FLAG_TypeDef;

extern HC32_RESET_FLAG_TypeDef	HC32_Reset_Flag;											//HC32系统复位标志

HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void);										//HC32获取复位标志位



















#endif /* __HC32L19X_CONFIG_H */
