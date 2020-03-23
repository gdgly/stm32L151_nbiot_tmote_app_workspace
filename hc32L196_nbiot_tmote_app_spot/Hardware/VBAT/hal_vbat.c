/**
  *********************************************************************************************************
  * @file    hal_vbat.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-10
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
#include "hal_vbat.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void VBate_Prot_Init(void)
 @Description			VBate_Prot_Init							: VBate ADC 端口配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VBate_Prot_Init(void)
{
	Gpio_SetAnalogMode(VBATE_ADC_GPIOx, VBATE_ADC_PIN);
}

/**********************************************************************************************************
 @Function			static void VBate_ADC_Init(void)
 @Description			VBate_ADC_Init								: VBate ADC 模块配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VBate_ADC_Init(void)
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
 @Function			static void VBate_Channel_Init(void)
 @Description			VBate_Channel_Init							: VBate ADC 通道配置
 @Input				void
 @Return				void
**********************************************************************************************************/
static void VBate_Channel_Init(void)
{
	Adc_CfgSglChannel(VBATE_ADC_CHANNEL);
}

/**********************************************************************************************************
 @Function			u32 HC32_VBate_Read(u32 timeoutMS)
 @Description			HC32_VBate_Read							: HC32电池电压读取
 @Input				timeoutMS									: 超时时间MS
 @Return				电压值
**********************************************************************************************************/
u32 HC32_VBate_Read(u32 timeoutMS)
{
	u32 pwr_vol = 0;
	
	timeMeterTypeDef ADCtimerMS;
	
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(VBATE_POWER_GPIOx, VBATE_POWER_PIN, &GPIO_Initure);
	
	VBATE_POWER_IO_SET(ON);
	
	VBate_Prot_Init();
	
	Delay_MS(10);
	
	HC32_TimeMeter_CountdownMS(&ADCtimerMS, timeoutMS);
	
	Adc_Enable();
	
	Delay_US(20);
	
	VBate_ADC_Init();
	
	VBate_Channel_Init();
	
	M0P_ADC->ICR_f.SGLIC = 0u;
	
	Adc_SGL_Start();
	
	while (!M0P_ADC->IFR_f.SGLIF) {
		if (HC32_TimeMeter_IsExpiredMS(&ADCtimerMS) != false) break;
	}
	
	pwr_vol = Adc_GetSglResult();
	
	Adc_Disable();
	
	VBATE_POWER_IO_SET(OFF);
	
	return pwr_vol * 200 * 2.8 / 4096.0;
}

/********************************************** END OF FLEE **********************************************/
