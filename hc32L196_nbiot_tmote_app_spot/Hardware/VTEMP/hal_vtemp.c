/**
  *********************************************************************************************************
  * @file    hal_vtemp.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-11
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_vtemp.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void VTemp_ADC_Init(void)
 @Description			VTemp_ADC_Init								: VTemp ADC 模块配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VTemp_ADC_Init(void)
{
	stc_adc_cfg_t ADC_Initure;
	
	DDL_ZERO_STRUCT(ADC_Initure);
	
	ADC_Initure.enAdcMode		= AdcSglMode;
	ADC_Initure.enAdcClkDiv		= AdcMskClkDiv8;
	ADC_Initure.enAdcSampCycleSel	= AdcMskSampCycle12Clk;
	ADC_Initure.enAdcRefVolSel	= AdcMskRefVolSelInBgr2p5;
	ADC_Initure.enAdcOpBuf		= AdcMskBufEnable;
	ADC_Initure.enInRef			= AdcMskInRefEnable;
	ADC_Initure.enAdcAlign		= AdcAlignRight;
	Adc_Init(&ADC_Initure);
}

/**********************************************************************************************************
 @Function			static void VTemp_Channel_Init(void)
 @Description			VTemp_Channel_Init							: VTemp ADC 通道配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VTemp_Channel_Init(void)
{
	Adc_CfgSglChannel(VTEMP_ADC_CHANNEL);
}

/**********************************************************************************************************
 @Function			s16 HC32_VTemp_Read(u32 timeoutMS)
 @Description			HC32_VTemp_Read							: HC32VTEMP温度读取
 @Input				timeoutMS									: 超时时间MS
 @Return				温度值
**********************************************************************************************************/
s32 HC32_VTemp_Read(u32 timeoutMS)
{
	s32 pwr_vol = 0;
	u16 trim_val = 0;
	s32 temp_val = 0;
	
	timeMeterTypeDef ADCtimerMS;
	
	HC32_TimeMeter_CountdownMS(&ADCtimerMS, timeoutMS);
	
	Bgr_BgrEnable();
	Bgr_TempSensorEnable();
	
	Adc_Enable();
	
	Delay_US(20);
	
	VTemp_ADC_Init();
	
	VTemp_Channel_Init();
	
	M0P_ADC->ICR_f.SGLIC = 0u;
	
	Adc_SGL_Start();
	
	while (!M0P_ADC->IFR_f.SGLIF) {
		if (HC32_TimeMeter_IsExpiredMS(&ADCtimerMS) != false) break;
	}
	
	pwr_vol = Adc_GetSglResult();
	
	Adc_Disable();
	
	Bgr_TempSensorDisable();
	Bgr_BgrDisable();
	
	trim_val = VTEMP_TRIM2V5_VAL;
	
	temp_val = 25 + (0.0795 * 2.5 * ( pwr_vol - trim_val ));
	
	return temp_val;
}

/********************************************** END OF FLEE **********************************************/
