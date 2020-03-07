#ifndef __HAL_RTC_H
#define   __HAL_RTC_H

#include "sys.h"
#include "rtc.h"

#define RTC_DEFAULT_YEAR			0x20
#define RTC_DEFAULT_MONTH		0x03
#define RTC_DEFAULT_DAY			0x01
#define RTC_DEFAULT_HOUR			0x12
#define RTC_DEFAULT_MINUTE		0x30
#define RTC_DEFAULT_SECOND		0x00

u8 RTC_ByteToBcd2(u8 Value);
u8 RTC_Bcd2ToByte(u8 Value);

u8 RTC_WeekDayNum(u8 nYear, u8 nMonth, u8 nDay);

void HC32_RTC_Init(void);																//HC32实时时钟初始化
























#endif /* __HAL_RTC_H */
