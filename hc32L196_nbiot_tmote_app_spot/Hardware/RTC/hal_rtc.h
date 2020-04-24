#ifndef __HAL_RTC_H
#define   __HAL_RTC_H

#include "sys.h"
#include "rtc.h"
#include <time.h>

#define RTC_PRD_SOURCE			RtcPrds
#define RTC_PRD_S				Rtc1S
#define RTC_PRD_X				0

#define RTC_IRQ_Level			IrqLevel3
#define RTC_IRQ_Channel			RTC_IRQn

#define RTC_DEFAULT_YEAR			0x20
#define RTC_DEFAULT_MONTH		0x04
#define RTC_DEFAULT_DAY			0x01
#define RTC_DEFAULT_HOUR			0x12
#define RTC_DEFAULT_MINUTE		0x30
#define RTC_DEFAULT_SECOND		0x00

u8 RTC_ByteToBcd2(u8 Value);
u8 RTC_Bcd2ToByte(u8 Value);

u8 RTC_WeekDayNum(u8 nYear, u8 nMonth, u8 nDay);

void HC32_RTC_Init(void);																//HC32实时时钟初始化

void HC32_RTC_SetTime(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec);							//HC32实时时钟设置时间

void HC32_RTC_Interrupt_Enable(void);														//HC32实时时钟中断使能
void HC32_RTC_Interrupt_Disable(void);														//HC32实时时钟中断失能

time_t    HC32_RTC_GetUnixTimeToStamp(void);													//HC32实时时钟获取当前时间戳
struct tm HC32_RTC_GetUnixTimeToCalendar(void);												//HC32实时时钟获取当前时间体

time_t    HC32_RTC_TimeToStamp(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec);					//HC32实时时钟时间转换时间戳
struct tm HC32_RTC_TimeToCalendar(u8 year, u8 month, u8 day, u8 hour, u8 min, u8 sec);				//HC32实时时钟时间转换时间体

#endif /* __HAL_RTC_H */
