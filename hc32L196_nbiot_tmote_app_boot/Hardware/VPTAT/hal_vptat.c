/**
  *********************************************************************************************************
  * @file    hal_vptat.c
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
#include "hal_vptat.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void VPtat_Prot_Init(void)
 @Description			VPtat_Prot_Init							: VPtat ADC 端口配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VPtat_Prot_Init(void)
{
	Gpio_SetAnalogMode(VPTAT_ADC_GPIOx, VPTAT_ADC_PIN);
}

/**********************************************************************************************************
 @Function			static void VPtat_ADC_Init(void)
 @Description			VPtat_ADC_Init								: VPtat ADC 模块配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VPtat_ADC_Init(void)
{
	stc_adc_cfg_t ADC_Initure;
	
	DDL_ZERO_STRUCT(ADC_Initure);
	
	ADC_Initure.enAdcMode		= AdcSglMode;
	ADC_Initure.enAdcClkDiv		= AdcMskClkDiv1;
	ADC_Initure.enAdcSampCycleSel	= AdcMskSampCycle12Clk;
	ADC_Initure.enAdcRefVolSel	= AdcMskRefVolSelAVDD;
	ADC_Initure.enAdcOpBuf		= AdcMskBufDisable;
	ADC_Initure.enInRef			= AdcMskInRefDisable;
	ADC_Initure.enAdcAlign		= AdcAlignRight;
	Adc_Init(&ADC_Initure);
}

/**********************************************************************************************************
 @Function			static void VPtat_Channel_Init(void)
 @Description			VPtat_Channel_Init							: VPtat ADC 通道配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VPtat_Channel_Init(void)
{
	Adc_CfgSglChannel(VPTAT_ADC_CHANNEL);
}

/**********************************************************************************************************
 @Function			u32 HC32_VPtat_Read(u32 timeoutMS)
 @Description			HC32_VPtat_Read							: HC32VPTAT电压读取
 @Input				timeoutMS									: 超时时间MS
 @Return				电压值
**********************************************************************************************************/
u32 HC32_VPtat_Read(u32 timeoutMS)
{
	u32 pwr_vol = 0;
	
	timeMeterTypeDef ADCtimerMS;
	
	VPtat_Prot_Init();
	
	HC32_TimeMeter_CountdownMS(&ADCtimerMS, timeoutMS);
	
	Adc_Enable();
	
	Delay_US(20);
	
	VPtat_ADC_Init();
	
	VPtat_Channel_Init();
	
	M0P_ADC->ICR_f.SGLIC = 0u;
	
	Adc_SGL_Start();
	
	while (!M0P_ADC->IFR_f.SGLIF) {
		if (HC32_TimeMeter_IsExpiredMS(&ADCtimerMS) != false) break;
	}
	
	pwr_vol = Adc_GetSglResult();
	
	Adc_Disable();
	
	return pwr_vol * 100 * 28 / 40960;
}

/********************************************** END OF FLEE **********************************************/
