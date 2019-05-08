#ifndef __RADER_ADC_H
#define   __RADER_ADC_H

#include "sys.h"


extern __IO uint16_t ADC_ConvertedValue;

extern ADC_HandleTypeDef			ADC_Handler;								//ADC句柄
extern DMA_HandleTypeDef			ADC_DMA_Handler;							//ADC DMA句柄

void Rader_ADC_Init(void);												//雷达ADC初始化
void Rader_ADC_DeInit(void);												//雷达ADC复位

#endif
