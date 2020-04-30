/**
  *********************************************************************************************************
  * @file    hal_base_tim0.c
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
#include "hal_base_tim0.h"
#include "delay.h"
#include "usart.h"

static stc_bt_mode0_cfg_t BaseTim0_Initure;

/**********************************************************************************************************
 @Function			void HC32_BaseTim0_Init(u16 period, en_bt_cr_timclkdiv_t psc)
 @Description			HC32_BaseTim0_Init
 @Input				period									: 自动重装值
					psc										: 时钟预分频数
 @Return				void
 @attention			T = period * (1/PCLK) * psc
**********************************************************************************************************/
void HC32_BaseTim0_Init(u16 period, en_bt_cr_timclkdiv_t psc)
{
	u16 u16ArrValue;
	u16 u16CntValue;
	
	DDL_ZERO_STRUCT(BaseTim0_Initure);
	
	BaseTim0_Initure.enWorkMode	= BtWorkMode0;
	BaseTim0_Initure.enCT		= BtTimer;
	BaseTim0_Initure.enCntMode	= Bt16bitArrMode;
	BaseTim0_Initure.enPRS		= psc;
	BaseTim0_Initure.bEnTog		= FALSE;
	BaseTim0_Initure.bEnGate		= FALSE;
	BaseTim0_Initure.enGateP		= BtGatePositive;
	
	Bt_Mode0_Init(TIM0, &BaseTim0_Initure);
	
	u16ArrValue = 0x10000 - period;
	Bt_M0_ARRSet(TIM0, u16ArrValue);
	
	u16CntValue = 0x10000 - period;
	Bt_M0_Cnt16Set(TIM0, u16CntValue);
	
	Bt_ClearIntFlag(TIM0, BtUevIrq);
	
	Bt_Mode0_EnableIrq(TIM0);
	
	EnableNvic(TIM0_IRQ_Channel, TIM0_IRQ_Level, TRUE);
}

/**********************************************************************************************************
 @Function			void HC32_BaseTim0_Register_nIRQ(func_ptr_t func)
 @Description			HC32_BaseTim0_Register_nIRQ
 @Input				func
 @Return				void
**********************************************************************************************************/
void HC32_BaseTim0_Register_nIRQ(func_ptr_t func)
{
	BaseTim0_Initure.pfnTim0Cb	= func;
}

/**********************************************************************************************************
 @Function			void Tim0_IRQHandler(void)
 @Description			Tim0_IRQHandler
 @Input				void
 @Return				void
**********************************************************************************************************/
void Tim0_IRQHandler(void)
{
	if (Bt_GetIntFlag(TIM0, BtUevIrq)) {
		
		if (BaseTim0_Initure.pfnTim0Cb) BaseTim0_Initure.pfnTim0Cb();
		
		Bt_ClearIntFlag(TIM0, BtUevIrq);
	}
}

/********************************************** END OF FLEE **********************************************/
