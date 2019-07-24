#ifndef __HAL_RTC_H
#define   __HAL_RTC_H

#include "sys.h"
#include <time.h>


extern RTC_HandleTypeDef RTC_Handler;										//RTC句柄

struct tm Time_ConvUnixToCalendar(time_t t);									//转换UNIX时间戳为日历时间
time_t Time_ConvCalendarToUnix(struct tm t);									//转换日历时间时间戳为UNIX

u8 RTC_Init(void);														//RTC初始化
HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec);						//RTC时间设置
HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date);						//RTC日期设置
void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec);							//设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel, u16 cnt);									//周期性唤醒定时器设置

#endif
