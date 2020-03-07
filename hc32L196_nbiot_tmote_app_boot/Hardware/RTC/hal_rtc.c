/**
  *********************************************************************************************************
  * @file    hal_rtc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-07
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "platform_config.h"
#include "platform_map.h"
#include "hal_rtc.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void HC32_RTC_Init(void)
 @Description			HC32_RTC_Init								: HC32实时时钟初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_RTC_Init(void)
{
	stc_rtc_initstruct_t RTC_Initure;
	
	DDL_ZERO_STRUCT(RTC_Initure);
	
	/* RTC补偿高速时钟源 */
	Sysctrl_SetRTCAdjustClkFreq(SysctrlRTC24MHz);
	
	/* 设定内部低速时钟RCL频率: 32.768KHz */
	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
	
	/* 开启外部低速时钟XTL */
	Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
	
	RTC_Initure.rtcAmpm				= RtcPm;
	RTC_Initure.rtcClksrc			= RtcClkRcl;
	
	RTC_Initure.rtcTime.u8Year		= RTC_DEFAULT_YEAR;
	RTC_Initure.rtcTime.u8Month		= RTC_DEFAULT_MONTH;
	RTC_Initure.rtcTime.u8Day		= RTC_DEFAULT_DAY;
	RTC_Initure.rtcTime.u8Hour		= RTC_DEFAULT_HOUR;
	RTC_Initure.rtcTime.u8Minute		= RTC_DEFAULT_MINUTE;
	RTC_Initure.rtcTime.u8Second		= RTC_DEFAULT_SECOND;
	RTC_Initure.rtcTime.u8DayOfWeek	= RTC_ByteToBcd2(RTC_WeekDayNum(RTC_DEFAULT_YEAR, RTC_DEFAULT_MONTH, RTC_DEFAULT_DAY) + 1);
	
	RTC_Initure.rtcCompen			= RtcCompenEnable;
	RTC_Initure.rtcCompValue			= 0;
	
	Rtc_Init(&RTC_Initure);
	
	Rtc_Cmd(TRUE);
}

/**********************************************************************************************************
 @Function			u8 RTC_ByteToBcd2(u8 Value)
 @Description			RTC_ByteToBcd2
 @Input				Byte
 @Return				Bcd2
**********************************************************************************************************/
u8 RTC_ByteToBcd2(u8 Value)
{
	u32 bcdhigh = 0;
	
	while (Value >= 10) {
		bcdhigh++;
		Value -= 10;
	}
	
	return  ((u8)(bcdhigh << 4) | Value);
}

/**********************************************************************************************************
 @Function			u8 RTC_Bcd2ToByte(u8 Value)
 @Description			RTC_Bcd2ToByte
 @Input				Bcd2
 @Return				Byte
**********************************************************************************************************/
u8 RTC_Bcd2ToByte(u8 Value)
{
	u32 tmp = 0;
	
	tmp = ((u8)(Value & (u8)0xF0) >> (u8)0x4) * 10;
	
	return (tmp + (Value & (u8)0x0F));
}

/**********************************************************************************************************
 @Function			u8 RTC_WeekDayNum(u8 nYear, u8 nMonth, u8 nDay)
 @Description			RTC_WeekDayNum
 @Input				nYear
					nMonth
					nDay
 @Return				WeekDay
**********************************************************************************************************/
u8 RTC_WeekDayNum(u8 nYear, u8 nMonth, u8 nDay)
{
	u32 year = 0U, weekday = 0U;
	
	year = 2000U + nYear;
	
	if (nMonth < 3U) {
		/*D = { [(23 x month)/9] + day + 4 + year + [(year-1)/4] - [(year-1)/100] + [(year-1)/400] } mod 7*/
		weekday = (((23U * nMonth)/9U) + nDay + 4U + year + ((year-1U)/4U) - ((year-1U)/100U) + ((year-1U)/400U)) % 7U;
	}
	else {
		/*D = { [(23 x month)/9] + day + 4 + year + [year/4] - [year/100] + [year/400] - 2 } mod 7*/
		weekday = (((23U * nMonth)/9U) + nDay + 4U + year + (year/4U) - (year/100U) + (year/400U) - 2U ) % 7U;
	}
	
	return (u8)weekday;
}






























/********************************************** END OF FLEE **********************************************/
