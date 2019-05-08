/**
  *********************************************************************************************************
  * @tmesh_misc.c
  * @author  Bell Zhong
  * @version V1.0
  * @date    2017-11-10
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "tmesh_misc.h"



uint32_t tbsp_runningtime_s;
uint32_t tbsp_runningtime_100ms;

void Sys_IncSecond(void)
{
	static uint32_t tick_s_pre;
	uint32_t tick_s_now;
	tick_s_now = HAL_GetTick();
	if((tick_s_now > tick_s_pre)&&((tick_s_now-tick_s_pre)>1000))
	{
		tbsp_runningtime_s++;
		tick_s_pre+=1000;
	}else if((0xffffffff-tick_s_pre+tick_s_now)>=1000){
		tbsp_runningtime_s++;
		tick_s_pre+=1000;
	}
}
uint32_t Sys_GetSecond(void)
{
	return tbsp_runningtime_s;
}

uint32_t tbsp_runningtime_100ms;
void Sys_Inc100ms(void)
{
	static uint32_t tick_pre;
	uint32_t tick_now;
	tick_now = HAL_GetTick();
	if((tick_now > tick_pre)&&((tick_now-tick_pre)>100))
	{
		tbsp_runningtime_100ms++;
		tick_pre+=100;
	}else if((0xffffffff-tick_pre+tick_now)>=100){
		tbsp_runningtime_100ms++;
		tick_pre+=100;
	}
}
uint32_t Sys_Get100ms(void)
{
	return tbsp_runningtime_100ms;
}


















/********************************************** END OF FLEE **********************************************/
