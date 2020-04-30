/**
  *********************************************************************************************************
  * @file    hal_base_tim1.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-28
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
#include "hal_base_tim1.h"
#include "delay.h"
#include "usart.h"

static stc_bt_mode0_cfg_t BaseTim1_Initure;

/**********************************************************************************************************
 @Function			void HC32_BaseTim1_Init(u16 period, en_bt_cr_timclkdiv_t psc)
 @Description			HC32_BaseTim1_Init
 @Input				period									: 自动重装值
					psc										: 时钟预分频数
 @Return				void
 @attention			T = period * (1/PCLK) * psc
**********************************************************************************************************/
void HC32_BaseTim1_Init(u16 period, en_bt_cr_timclkdiv_t psc)
{
	u16 u16ArrValue;
	u16 u16CntValue;
	
	DDL_ZERO_STRUCT(BaseTim1_Initure);
	
	BaseTim1_Initure.enWorkMode	= BtWorkMode0;
	BaseTim1_Initure.enCT		= BtTimer;
	BaseTim1_Initure.enCntMode	= Bt16bitArrMode;
	BaseTim1_Initure.enPRS		= psc;
	BaseTim1_Initure.bEnTog		= FALSE;
	BaseTim1_Initure.bEnGate		= FALSE;
	BaseTim1_Initure.enGateP		= BtGatePositive;
	
	Bt_Mode0_Init(TIM1, &BaseTim1_Initure);
	
	u16ArrValue = 0x10000 - period;
	Bt_M0_ARRSet(TIM1, u16ArrValue);
	
	u16CntValue = 0x10000 - period;
	Bt_M0_Cnt16Set(TIM1, u16CntValue);
	
	Bt_ClearIntFlag(TIM1, BtUevIrq);
	
	Bt_Mode0_EnableIrq(TIM1);
	
	EnableNvic(TIM1_IRQ_Channel, TIM1_IRQ_Level, TRUE);
}

/**********************************************************************************************************
 @Function			void HC32_BaseTim1_Register_nIRQ(func_ptr_t func)
 @Description			HC32_BaseTim1_Register_nIRQ
 @Input				func
 @Return				void
**********************************************************************************************************/
void HC32_BaseTim1_Register_nIRQ(func_ptr_t func)
{
	BaseTim1_Initure.pfnTim1Cb	= func;
}

/**********************************************************************************************************
 @Function			void Tim1_IRQHandler(void)
 @Description			Tim1_IRQHandler
 @Input				void
 @Return				void
**********************************************************************************************************/
void Tim1_IRQHandler(void)
{
	if (Bt_GetIntFlag(TIM1, BtUevIrq)) {
		
		if (BaseTim1_Initure.pfnTim1Cb) BaseTim1_Initure.pfnTim1Cb();
		
		Bt_ClearIntFlag(TIM1, BtUevIrq);
	}
}

/********************************************** END OF FLEE **********************************************/
