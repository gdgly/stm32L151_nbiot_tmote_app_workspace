/**
  *********************************************************************************************************
  * @file    hc32l19x_config.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-09
  * @brief   1TAB = 5Speace
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"
#include "usart.h"

HC32_RESET_FLAG_TypeDef HC32_Reset_Flag = RCC_RESET_FLAG_NONE;

/**********************************************************************************************************
 @Function			HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
 @Description			HC32_SystemReset_GetStatus					: HC32获取复位标志位
 @Input				void
 @Return				HC32_RESET_FLAG_TypeDef						: 复位标志位
**********************************************************************************************************/
HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
{
	HC32_RESET_FLAG_TypeDef resetStatus = RCC_RESET_FLAG_NONE;
	
	if (Reset_GetFlag(ResetFlagMskPor5V) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (Reset_GetFlag(ResetFlagMskPor1_5V) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (Reset_GetFlag(ResetFlagMskLvd) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_LPWRRST;
	}
	else if (Reset_GetFlag(ResetFlagMskWdt) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_IWDGRST;
	}
	else if (Reset_GetFlag(ResetFlagMskPca) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PCA;
	}
	else if (Reset_GetFlag(ResetFlagMskLockup) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_LOCKUP;
	}
	else if (Reset_GetFlag(ResetFlagMskSysreq) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_SFTRST;
	}
	else if (Reset_GetFlag(ResetFlagMskRstb) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PINRST;
	}
	
	return resetStatus;
}






































































/********************************************** END OF FLEE **********************************************/
