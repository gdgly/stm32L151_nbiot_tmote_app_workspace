/**
  *********************************************************************************************************
  * @file    hal_base_tim2.c
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
#include "hal_base_tim2.h"
#include "delay.h"
#include "usart.h"

static stc_bt_mode0_cfg_t BaseTim2_Initure;

/**********************************************************************************************************
 @Function			void HC32_BaseTim2_Init(u16 period, en_bt_cr_timclkdiv_t psc)
 @Description			HC32_BaseTim2_Init
 @Input				period									: 自动重装值
					psc										: 时钟预分频数
 @Return				void
 @attention			T = period * (1/PCLK) * psc
**********************************************************************************************************/
void HC32_BaseTim2_Init(u16 period, en_bt_cr_timclkdiv_t psc)
{
	u16 u16ArrValue;
	u16 u16CntValue;
	
	DDL_ZERO_STRUCT(BaseTim2_Initure);
	
	BaseTim2_Initure.enWorkMode	= BtWorkMode0;
	BaseTim2_Initure.enCT		= BtTimer;
	BaseTim2_Initure.enCntMode	= Bt16bitArrMode;
	BaseTim2_Initure.enPRS		= psc;
	BaseTim2_Initure.bEnTog		= FALSE;
	BaseTim2_Initure.bEnGate		= FALSE;
	BaseTim2_Initure.enGateP		= BtGatePositive;
	
	Bt_Mode0_Init(TIM2, &BaseTim2_Initure);
	
	u16ArrValue = 0x10000 - period;
	Bt_M0_ARRSet(TIM2, u16ArrValue);
	
	u16CntValue = 0x10000 - period;
	Bt_M0_Cnt16Set(TIM2, u16CntValue);
	
	Bt_ClearIntFlag(TIM2, BtUevIrq);
	
	Bt_Mode0_EnableIrq(TIM2);
	
	EnableNvic(TIM2_IRQ_Channel, TIM2_IRQ_Level, TRUE);
}

/**********************************************************************************************************
 @Function			void HC32_BaseTim2_Register_nIRQ(func_ptr_t func)
 @Description			HC32_BaseTim2_Register_nIRQ
 @Input				func
 @Return				void
**********************************************************************************************************/
void HC32_BaseTim2_Register_nIRQ(func_ptr_t func)
{
	BaseTim2_Initure.pfnTim2Cb	= func;
}

/**********************************************************************************************************
 @Function			void Tim2_IRQHandler(void)
 @Description			Tim2_IRQHandler
 @Input				void
 @Return				void
**********************************************************************************************************/
void Tim2_IRQHandler(void)
{
	if (Bt_GetIntFlag(TIM2, BtUevIrq)) {
		
		if (BaseTim2_Initure.pfnTim2Cb) BaseTim2_Initure.pfnTim2Cb();
		
		Bt_ClearIntFlag(TIM2, BtUevIrq);
	}
}

/********************************************** END OF FLEE **********************************************/
