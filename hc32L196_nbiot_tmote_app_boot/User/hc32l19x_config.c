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

HC32_RESET_FLAG_TypeDef			HC32_Reset_Flag = RCC_RESET_FLAG_NONE;

/**********************************************************************************************************
 @Function			HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
 @Description			HC32_SystemReset_GetStatus					: HC32获取复位标志位
 @Input				void
 @Return				HC32_RESET_FLAG_TypeDef						: 复位标志位
**********************************************************************************************************/
HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
{
	HC32_RESET_FLAG_TypeDef resetStatus = RCC_RESET_FLAG_NONE;
	
	if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_POR5V) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_POR5V);
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_POR15V) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_POR15V);
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_LVD) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_LVD);
		resetStatus = RCC_RESET_FLAG_LPWRRST;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_WDT) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_WDT);
		resetStatus = RCC_RESET_FLAG_IWDGRST;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_PCA) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_PCA);
		resetStatus = RCC_RESET_FLAG_PCA;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_LOCKUP) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_LOCKUP);
		resetStatus = RCC_RESET_FLAG_LOCKUP;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_SYSREQ) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_SYSREQ);
		resetStatus = RCC_RESET_FLAG_SFTRST;
	}
	else if (__HAL_RESET_GET_FLAG(STC_RESET_FLAG_RSTB) != RESET) {
		__HAL_RESET_CLR_FLAG(STC_RESET_FLAG_RSTB);
		resetStatus = RCC_RESET_FLAG_PINRST;
	}
	
	return resetStatus;
}
































/********************************************** END OF FLEE **********************************************/
