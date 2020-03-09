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
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_32000)
	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
#endif
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_38400)
	Sysctrl_SetRCLTrim(SysctrlRclFreq38400);
#endif
	
	/* 开启内部低速时钟RCL */
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_32000 || SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_38400)
	Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
#endif
	/* 开启外部低速时钟XTL */
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_XTL_32768)
	Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);
#endif
	
	RTC_Initure.rtcAmpm				= RtcPm;
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_32000 || SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_RCL_38400)
	RTC_Initure.rtcClksrc			= RtcClkRcl;
#endif
#if (SYSTEM_RTCCLOCK_TYPE == SYSTEM_RTCCLOCK_XTL_32768)
	RTC_Initure.rtcClksrc			= RtcClkXtl;
#endif
	
	RTC_Initure.rtcTime.u8Year		= RTC_DEFAULT_YEAR;
	RTC_Initure.rtcTime.u8Month		= RTC_DEFAULT_MONTH;
	RTC_Initure.rtcTime.u8Day		= RTC_DEFAULT_DAY;
	RTC_Initure.rtcTime.u8Hour		= RTC_DEFAULT_HOUR;
	RTC_Initure.rtcTime.u8Minute		= RTC_DEFAULT_MINUTE;
	RTC_Initure.rtcTime.u8Second		= RTC_DEFAULT_SECOND;
	RTC_Initure.rtcTime.u8DayOfWeek	= RTC_ByteToBcd2(RTC_WeekDayNum(RTC_Bcd2ToByte(RTC_DEFAULT_YEAR), RTC_Bcd2ToByte(RTC_DEFAULT_MONTH), RTC_Bcd2ToByte(RTC_DEFAULT_DAY)));
	
	RTC_Initure.rtcCompen			= RtcCompenEnable;
	RTC_Initure.rtcCompValue			= 0;
	
	Rtc_Init(&RTC_Initure);
	
	Rtc_Cmd(TRUE);
}

/**********************************************************************************************************
 @Function			void HC32_RTC_SetTime(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
 @Description			HC32_RTC_SetTime							: HC32实时时钟设置时间
 @Input				year, month, day							: 年(0~99), 月(1~12), 日(0~31)
					hour, min, sec								: 小时, 分钟, 秒钟
 @Return				void
**********************************************************************************************************/
void HC32_RTC_SetTime(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
{
	stc_rtc_time_t RTC_Time;
	
	RTC_Time.u8Year				= RTC_ByteToBcd2(year);
	RTC_Time.u8Month				= RTC_ByteToBcd2(month);
	RTC_Time.u8Day					= RTC_ByteToBcd2(day);
	RTC_Time.u8Hour				= RTC_ByteToBcd2(hour);
	RTC_Time.u8Minute				= RTC_ByteToBcd2(min);
	RTC_Time.u8Second				= RTC_ByteToBcd2(sec);
	RTC_Time.u8DayOfWeek			= RTC_ByteToBcd2(RTC_WeekDayNum(year, month, day));
	
	Rtc_SetTime(&RTC_Time);
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

/**********************************************************************************************************
 @Function			time_t HC32_RTC_GetUnixTimeToStamp(void)
 @Description			HC32_RTC_GetUnixTimeToStamp					: HC32实时时钟获取当前时间戳
 @Input				void
 @Return				当前时间时间戳
**********************************************************************************************************/
time_t HC32_RTC_GetUnixTimeToStamp(void)
{
	stc_rtc_time_t readTime;
	
	Rtc_ReadDateTime(&readTime);
	
	return HC32_RTC_TimeToStamp(RTC_Bcd2ToByte(readTime.u8Year), RTC_Bcd2ToByte(readTime.u8Month), RTC_Bcd2ToByte(readTime.u8Day), RTC_Bcd2ToByte(readTime.u8Hour), RTC_Bcd2ToByte(readTime.u8Minute), RTC_Bcd2ToByte(readTime.u8Second));
}

/**********************************************************************************************************
 @Function			struct tm HC32_RTC_GetUnixTimeToCalendar(void)
 @Description			HC32_RTC_GetUnixTimeToCalendar				: HC32实时时钟获取当前时间体
 @Input				void
 @Return				当前时间日历时间
**********************************************************************************************************/
struct tm HC32_RTC_GetUnixTimeToCalendar(void)
{
	stc_rtc_time_t readTime;
	
	Rtc_ReadDateTime(&readTime);
	
	return HC32_RTC_TimeToCalendar(RTC_Bcd2ToByte(readTime.u8Year), RTC_Bcd2ToByte(readTime.u8Month), RTC_Bcd2ToByte(readTime.u8Day), RTC_Bcd2ToByte(readTime.u8Hour), RTC_Bcd2ToByte(readTime.u8Minute), RTC_Bcd2ToByte(readTime.u8Second));
}

/**********************************************************************************************************
 @Function			time_t HC32_RTC_TimeToStamp(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
 @Description			HC32_RTC_TimeToStamp						: HC32实时时钟时间转换时间戳
 @Input				void
 @Return				时间戳
**********************************************************************************************************/
time_t HC32_RTC_TimeToStamp(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
{
	struct tm time;
	
	time.tm_year	= 100 + year;
	time.tm_mon	= month - 1;
	time.tm_mday	= day;
	time.tm_hour	= hour;
	time.tm_min	= min;
	time.tm_sec	= sec;
	
	return mktime(&time);
}

/**********************************************************************************************************
 @Function			struct tm HC32_RTC_TimeToCalendar(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
 @Description			HC32_RTC_TimeToCalendar						: HC32实时时钟时间转换时间体
 @Input				void
 @Return				日历时间
**********************************************************************************************************/
struct tm HC32_RTC_TimeToCalendar(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec)
{
	struct tm *t_time;
	time_t t = HC32_RTC_TimeToStamp(year, month, day, hour, min, sec);
	
	t_time = localtime(&t);
	t_time->tm_year	-= 100;
	t_time->tm_mon		+= 1;
	
	return *t_time;
}

/********************************************** END OF FLEE **********************************************/
