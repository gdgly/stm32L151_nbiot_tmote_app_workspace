/**
  *********************************************************************************************************
  * @file    rader_api.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-31
  * @brief   
  *********************************************************************************************************
  * @attention
  * 2017-11-9:by Bell Zhong,update the radar algorithm.double the sample rate .the uart baudrate is must be 115200 when run Radar_test
  * 
  *
  *********************************************************************************************************
  */

#include "radar_api.h"
#include "radar_adc.h"
#include "radar_dac.h"
#include "radar_dma.h"
#include "radar_timer.h"
#include "tmesh_radar_algorithm.h"
#include "stm32_dsp.h"
#include "hal_eeprom.h"
#include "hal_radar.h"
#include "stm32l1xx_config.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include <math.h>

#define SAMPLE_NUM	TRADAR_SAMPLE_NUM

//#define		VDDA2V8
#define		VDDA3V3
//#define		RADAR_VPTAT
// VDDA=2.8V 0~2633 -> 0~1.8V
// VDDA=3.3V 0~2234 -> 0~1.8V
#ifdef VDDA3V3
 #ifdef RADAR_VPTAT
  #define	RADER_LOW			650	//650	//50	//
  #define	RADER_RANGE			7	//7	//8		//
 #else
  #define	RADER_LOW			50	//650	//50	//
  #define	RADER_RANGE			6	//8		//
 #endif
#else
 #define	RADER_LOW			50	//650	//50	//
 #define	RADER_RANGE			8	//8		//
#endif
u16 fre_magBG[TRADAR_BACKGROUND_NUM] = {10};
//u32 fft_buff[256] = {0};

int n_array = 0;
u32 sample_array0[SAMPLE_NUM] = {0};
u32 sample_array1[SAMPLE_NUM] = {0};

int flag_in_array = 0;
int flag_main_go = 0;

u8  bgTimes = 1;														//背景记录 标志位
tradar_targetinfo_s targetinfo;
/**********************************************************************************************************
 @Function			void Rader_Init(void)
 @Description			雷达初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_Init(void)
{
	Rader_DMA_Init();
	Rader_ADC_Init();
	Rader_DAC_Init();
	
	Radar_TIM2_Init(10-1, 32-1);											//10us中断一次
	__HAL_TIM_DISABLE(&Radar_TIM2_Handler);									//先关闭TIM2,等待使用雷达时开启
	RADAR_InitDataPack();												//初始化雷达接收队列

	EEPROM_ReadBytes(EEPROM_BASE_ADDR1, (u8 *)fre_magBG, sizeof(fre_magBG));		//读取EEPROM背景值
	
	tradar_background_set(fre_magBG, (sizeof(fre_magBG))/2);
}

/**********************************************************************************************************
 @Function			void Rader_InitBG(void)
 @Description			雷达初始化背景值
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_InitBG(void)
{
#if 1	
	RADERPOWER(ON);													//开启雷达电源
	Delay_MS(500);
	__HAL_TIM_ENABLE(&Radar_TIM2_Handler);									//雷达工作开启
	
	bgTimes = 31;														//标记需初始化雷达背景
	
	while (1) {
		while (flag_main_go != 0) {
			if (bgTimes > 1) {
				if (flag_main_go == 1)
				{									
					tradar_background_transform(sample_array0,SAMPLE_NUM,fre_magBG,(sizeof(fre_magBG))/2);
				}
				else
				{
					tradar_background_transform(sample_array1,SAMPLE_NUM,fre_magBG,(sizeof(fre_magBG))/2);
				}
				
				bgTimes--;
				if (bgTimes == 1) {										//初始化背景完成
					EEPROM_WriteBytes(EEPROM_BASE_ADDR1, (u8 *)fre_magBG, sizeof(fre_magBG));
					__HAL_TIM_DISABLE(&Radar_TIM2_Handler);					//雷达工作结束
					RADERPOWER(OFF);									//关闭雷达电源
					tradar_background_set(fre_magBG,(sizeof(fre_magBG))/2);
					flag_main_go = 0;
					return ;
				}
			}						
			flag_main_go = 0;
		}
	}
#endif
}

/**********************************************************************************************************
 @Function			u8 RADAR_ModuleGetData(u8 dataNum)
 @Description			获取雷达数据
 @Input				dataNum : 雷达数据条数
 @Return				1 : 异常
					0 : 正确
**********************************************************************************************************/
u8 Rader_GetData(u8 dataNum)
{
	u8 buf[RADAR_CACHE_SIZE];	
	RADAR_InitDataPack();												//初始化雷达接收队列
	
	RADERPOWER(ON);													//开启雷达电源
	Delay_MS(300);
	__HAL_TIM_ENABLE(&Radar_TIM2_Handler);									//雷达工作开启
	
	while (dataNum) {
		while (flag_main_go != 0) {
			if (bgTimes > 1) {
				if (flag_main_go == 1)
				{
					tradar_background_transform(sample_array0, SAMPLE_NUM, fre_magBG, (sizeof(fre_magBG))/2);
				}
				else
				{
					tradar_background_transform(sample_array1, SAMPLE_NUM, fre_magBG, (sizeof(fre_magBG))/2);
				}
				
				bgTimes--;
				if (bgTimes == 1) {										//初始化背景完成
					EEPROM_WriteBytes(EEPROM_BASE_ADDR1, (u8 *)fre_magBG, sizeof(fre_magBG));
					tradar_background_set(fre_magBG, (sizeof(fre_magBG))/2);
					flag_main_go = 0;
					return 1;
				}
			}
			else if (flag_main_go == 1)
			{
				tradar_target_detect(sample_array0, SAMPLE_NUM, &targetinfo);
			}
			else
			{
				tradar_target_detect(sample_array1, SAMPLE_NUM, &targetinfo);
			}
			
			if (targetinfo.status == TRADAR_BE_COVERED) {
				//printf("COVER !!!diff=%d\n",targetinfo.strenth_total_diff);
				memset(buf, 0, RADAR_CACHE_SIZE);
				sprintf((char *)buf, "COVER !!!diff=%d", targetinfo.strenth_total_diff);
				RADAR_DataPackEnqueue((u8 *)buf, strlen((char *)buf));			//雷达数据写入队列
				dataNum--;
			}
			else if (targetinfo.status == TRADAR_NO_TARGET) {
				//printf("No target ...diff=%d\n",targetinfo.strenth_total_diff);
				memset(buf, 0, RADAR_CACHE_SIZE);
				sprintf((char *)buf, "No target ...diff=%d", targetinfo.strenth_total_diff);
				RADAR_DataPackEnqueue((u8 *)buf, strlen((char *)buf));			//雷达数据写入队列
				dataNum--;
			}
			else if (targetinfo.status == TRADAR_HAS_TARGET) {
				//printf("dis=%d.0 cm., mag=%d,diff=%d\n", targetinfo.distance_cm, targetinfo.signal_strength,targetinfo.strenth_total_diff);
				memset(buf, 0, RADAR_CACHE_SIZE);
				sprintf((char *)buf, "dis=%d,mag=%d,diff=%d", targetinfo.distance_cm, targetinfo.signal_strength, targetinfo.strenth_total_diff);
				RADAR_DataPackEnqueue((u8 *)buf, strlen((char *)buf));			//雷达数据写入队列
				dataNum--;
			}
			
			flag_main_go = 0;
		}
	}
	
	__HAL_TIM_DISABLE(&Radar_TIM2_Handler);									//雷达工作结束
	RADERPOWER(OFF);													//关闭雷达电源
	
	return 0;
}

/**********************************************************************************************************
 @Function			void Rader_RunTest(void)
 @Description			雷达运行测试,the uart baudrate must be 115200
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_RunTest(void)
{
	RADERPOWER(ON);													//开启雷达电源
	Delay_MS(500);
	__HAL_TIM_ENABLE(&Radar_TIM2_Handler);									//雷达工作开启
	
	while (1) {
		while (flag_main_go != 0) {
			if (bgTimes > 1) {
				if (flag_main_go == 1)
				{
					tradar_background_transform(sample_array0, SAMPLE_NUM, fre_magBG, (sizeof(fre_magBG))/2);
				}
				else
				{
					tradar_background_transform(sample_array1, SAMPLE_NUM, fre_magBG, (sizeof(fre_magBG))/2);
				}
				
				bgTimes--;
				if (bgTimes == 1) {										//初始化背景完成
					EEPROM_WriteBytes(EEPROM_BASE_ADDR1, (u8 *)fre_magBG, sizeof(fre_magBG));
					tradar_background_set(fre_magBG, (sizeof(fre_magBG))/2);
				}
			}
			else if (flag_main_go == 1)
			{
				tradar_target_detect(sample_array0, SAMPLE_NUM, &targetinfo);
			}
			else
			{
				tradar_target_detect(sample_array1, SAMPLE_NUM, &targetinfo);
			}
			if (targetinfo.status == TRADAR_BE_COVERED) {
				printf("COVER !!!diff=%d\n", targetinfo.strenth_total_diff);
			}
			else if (targetinfo.status == TRADAR_NO_TARGET) {
				printf("No target ...diff=%d\n", targetinfo.strenth_total_diff);
			}
			else if (targetinfo.status == TRADAR_HAS_TARGET) {
				printf("dis=%d.0 cm., mag=%d, diff=%d\n", targetinfo.distance_cm, targetinfo.signal_strength, targetinfo.strenth_total_diff);
			}
			flag_main_go = 0;
		}
	}
}


/**********************************************************************************************************
 @Function			void Rader_Get_Sample(void)
 @Description			雷达采样
 @Input				void
 @Return				void
**********************************************************************************************************/
// flag_main_go flag_in_array
// 0            0
// 1            1
// 2            0
void Rader_Get_Sample(void)
{
	if (n_array >= SAMPLE_NUM) {
		if (flag_main_go != 0) {
			return;
		}
		n_array = 0;
		flag_main_go = 1 + flag_in_array;
		flag_in_array = 1 - flag_in_array;		
	}
	
	if (flag_in_array == 0) {
		
		sample_array0[n_array] = ADC_ConvertedValue;
		
		/* 设置DAC通道值 */
		HAL_DAC_SetValue(&DAC_Handler, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (SAMPLE_NUM - n_array) * RADER_RANGE + RADER_LOW);
		/* 启动DAC */
		HAL_DAC_Start(&DAC_Handler, DAC_CHANNEL_1);
		
		n_array++;
	}
	else {
		
		sample_array1[n_array] = ADC_ConvertedValue;
		
		/* 设置DAC通道值 */
		HAL_DAC_SetValue(&DAC_Handler, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (SAMPLE_NUM - n_array) * RADER_RANGE + RADER_LOW);
		
		/* 启动DAC */
		HAL_DAC_Start(&DAC_Handler, DAC_CHANNEL_1);
		
		n_array++;
	}
}

/**********************************************************************************************************
 @Function			void Rader_Get_Sample_Time(void)
 @Description			雷达采样节拍
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_Get_Sample_Time(void)
{
	static int xx = 0;
	
	//if ((xx < 1) && (flag_main_go == 0)) 
	if (xx < 1) {
		xx = 10;
		Rader_Get_Sample();
	}
	else {
		xx--;
	}
}


/********************************************** END OF FLEE **********************************************/
