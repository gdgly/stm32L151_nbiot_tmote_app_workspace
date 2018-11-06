/**
  *********************************************************************************************************
  * @file    rader_adc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-31
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "radar_adc.h"


__IO uint16_t ADC_ConvertedValue = 10;

ADC_HandleTypeDef				ADC_Handler;								//ADC句柄
DMA_HandleTypeDef				ADC_DMA_Handler;							//ADC DMA句柄

/**********************************************************************************************************
 @Function			void Rader_ADC_Init(void)
 @Description			雷达ADC初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_ADC_Init(void)
{
	ADC_ChannelConfTypeDef ADC_ChanelConfig;
	
	ADC_Handler.Instance = ADC1;
	ADC_Handler.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
	ADC_Handler.Init.Resolution = ADC_RESOLUTION12b;
	ADC_Handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC_Handler.Init.ScanConvMode = ADC_SCAN_DISABLE;
	ADC_Handler.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	ADC_Handler.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
	ADC_Handler.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
	ADC_Handler.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
	ADC_Handler.Init.ContinuousConvMode = ENABLE;
	ADC_Handler.Init.NbrOfConversion = 1;
	ADC_Handler.Init.DiscontinuousConvMode = DISABLE;
	ADC_Handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	ADC_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC_Handler.Init.DMAContinuousRequests = ENABLE;
	HAL_ADC_Init(&ADC_Handler);
	
	ADC_ChanelConfig.Channel = ADC_CHANNEL_1;
	ADC_ChanelConfig.Rank = ADC_REGULAR_RANK_1;
	ADC_ChanelConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
	HAL_ADC_ConfigChannel(&ADC_Handler, &ADC_ChanelConfig);
	
	/* 启动AD转换并使能DMA传输和中断 */
	HAL_ADC_Start_DMA(&ADC_Handler, (uint32_t*)&ADC_ConvertedValue, 1);
}

/**********************************************************************************************************
 @Function			void Rader_ADC_DeInit(void)
 @Description			雷达ADC复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_ADC_DeInit(void)
{
	HAL_ADC_DeInit(&ADC_Handler);
}

/********************************************** END OF FLEE **********************************************/
