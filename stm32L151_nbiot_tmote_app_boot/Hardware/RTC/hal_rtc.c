/**
  *********************************************************************************************************
  * @file    hal_rtc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-24
  * @brief   HAL RTC Device
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "hal_rtc.h"


RTC_HandleTypeDef RTC_Handler;											//RTC句柄

/**********************************************************************************************************
 @Function			u8 RTC_Init(void)
 @Description			RTC初始化
 @Input				void
 @Return				0 : 初始化成功
					2 : 进入初始化模式失败
**********************************************************************************************************/
u8 RTC_Init(void)
{
	RTC_Handler.Instance = RTC;
	RTC_Handler.Init.HourFormat = RTC_HOURFORMAT_24;							//RTC设置为24小时格式
	RTC_Handler.Init.AsynchPrediv = 0X7F;									//RTC异步分频系数(1~0X7F)
	RTC_Handler.Init.SynchPrediv = 0XFF;									//RTC同步分频系数(0~7FFF)
	RTC_Handler.Init.OutPut = RTC_OUTPUT_DISABLE;
	RTC_Handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	RTC_Handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&RTC_Handler) != HAL_OK) return 2;
	
	if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR0) != 0X5050)				//是否第一次配置
	{
		//RTC_Set_Time(12, 10, 00);										//设置时间
		//RTC_Set_Date(17, 11, 8);											//设置日期
		HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR0, 0X5050);				//标记已经初始化过了
	}
	
	return 0;
}

/**********************************************************************************************************
 @Function			HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec)
 @Description			RTC时间设置
 @Input				hour, min, sec : 小时, 分钟, 秒钟
					ampm 		: RTC_HOURFORMAT12_AM / RTC_HOURFORMAT12_PM
 @Return				SUCEE(1) : 成功
					ERROR(0) : 进入初始化模式失败
**********************************************************************************************************/
HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	
	RTC_TimeStructure.Hours = hour;
	RTC_TimeStructure.Minutes = min;
	RTC_TimeStructure.Seconds = sec;
	RTC_TimeStructure.TimeFormat = (hour < 12)?RTC_HOURFORMAT12_AM:RTC_HOURFORMAT12_PM;
	RTC_TimeStructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	RTC_TimeStructure.StoreOperation = RTC_STOREOPERATION_RESET;
	return HAL_RTC_SetTime(&RTC_Handler, &RTC_TimeStructure, RTC_FORMAT_BIN);
}

/**********************************************************************************************************
 @Function			HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date)
 @Description			RTC日期设置
 @Input				year, month, date 	: 年(0~99), 月(1~12), 日(0~31)
					week 			: 星期(1~7,0,非法!)
 @Return				SUCEE(1) : 成功
					ERROR(0) : 进入初始化模式失败
**********************************************************************************************************/
HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date)
{
	u8 week;
	RTC_DateTypeDef RTC_DateStructure;
	
	RTC_DateStructure.Date = date;
	RTC_DateStructure.Month = month;
	RTC_DateStructure.Year = year;
	
	if (month == 1 || month == 2) {
          month += 12;
          year--;
     }
	
	week = (date+2*month+3*(month+1)/5+year+year/4-year/100+year/400+1)%7;
     RTC_DateStructure.WeekDay = (week == 0) ? 7 : week;
	
	return HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStructure, RTC_FORMAT_BIN);
}

/**********************************************************************************************************
 @Function			struct tm Time_ConvUnixToCalendar(time_t t)
 @Description			转换UNIX时间戳为日历时间
 @Input				当前时间的UNIX时间戳
 @Return				struct tm
**********************************************************************************************************/
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;												//localtime转换结果的tm_year是相对值, 需要转成绝对值
	
	return *t_tm;
}

/**********************************************************************************************************
 @Function			time_t Time_ConvCalendarToUnix(struct tm t)
 @Description			写入RTC时钟当前时间
 @Input				struct tm t
 @Return				time_t
**********************************************************************************************************/
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year += 100;													//外部tm结构体存储的年份为20xx格式,比如2017年即17
																	//而time.h中定义的年份格式为1900年开始的年份
																	//所以,在日期转换时要考虑到这个因素
	return mktime(&t);
}

/**********************************************************************************************************
 @Function			void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec)
 @Description			设置闹钟时间(按星期闹铃,24小时制)
 @Input				week, hour, min, sec : 星期几(1~7), 小时, 分钟, 秒钟
 @Return				void
**********************************************************************************************************/
void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec)
{
	RTC_AlarmTypeDef RTC_AlarmStructure;
	
	RTC_AlarmStructure.AlarmTime.Hours = hour;
	RTC_AlarmStructure.AlarmTime.Minutes = min;
	RTC_AlarmStructure.AlarmTime.Seconds = sec;
	RTC_AlarmStructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
	
	RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_NONE;						//精确匹配星期, 时分秒
	RTC_AlarmStructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;		//按星期
	RTC_AlarmStructure.AlarmDateWeekDay = week;								//星期
	RTC_AlarmStructure.Alarm = RTC_ALARM_A;									//闹钟A
	
	HAL_RTC_SetAlarm_IT(&RTC_Handler, &RTC_AlarmStructure, RTC_FORMAT_BIN);
	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0x02, 0x01);							//抢占优先级2, 子优先级1
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/**********************************************************************************************************
 @Function			void RTC_Set_WakeUp(u32 wksel, u16 cnt)
 @Description			周期性唤醒定时器设置
 @Input				wksel : @ ref RTCEx_Wakeup_Timer_Definitions : 
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        ((uint32_t)0x00000000)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         ((uint32_t)0x00000001)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         ((uint32_t)0x00000002)
							#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         ((uint32_t)0x00000003)
							#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS      ((uint32_t)0x00000004)
							#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS      ((uint32_t)0x00000006)
					cnt   : 自动重装载值 减到0, 产生中断
 @Return				void
**********************************************************************************************************/
void RTC_Set_WakeUp(u32 wksel, u16 cnt)
{
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTC_Handler, RTC_FLAG_WUTF);				//清除RTC WAKE UP的标志
	
	HAL_RTCEx_SetWakeUpTimer_IT(&RTC_Handler, cnt, wksel);						//设置重装载值和时钟
	
	HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x02, 0x02);							//抢占优先级2,子优先级2s
	HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

/********************************************** END OF FLEE **********************************************/
