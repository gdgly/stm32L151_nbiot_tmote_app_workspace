/**
  *********************************************************************************************************
  * @file    hal_testbench.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-07-24
  * @brief   
  *********************************************************************************************************
  * @attention
  *		  
  *
  *********************************************************************************************************
  */

#include "hal_testbench.h"
#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"
#include "usart.h"

TESTBenchClientTypeDef TestBenchClient = {
	.TestState		= 0x00,
	.SendTimes		= 0x03,
	.Data			= {
		.StartCode	= 0xFAFA,
		
		.RF4438ID		= 0x0000,
		.CheckNum		= 0x00,
	},
};

/**********************************************************************************************************
 @Function			bool TestBench_FLASH_CheckSubSN(void)
 @Description			TestBench_FLASH_CheckSubSN
 @Input				void
 @Return				bool
**********************************************************************************************************/
bool TestBench_FLASH_CheckSubSN(void)
{
	if ( (0x00 == *(__IO uint8_t *)(FLASH_END - 0)) && \
		(0x00 == *(__IO uint8_t *)(FLASH_END - 1)) && \
		(0x00 == *(__IO uint8_t *)(FLASH_END - 2)) && \
		(0x00 == *(__IO uint8_t *)(FLASH_END - 3)) ) {
		return false;
	}
	else {
		return true;
	}
}

/**********************************************************************************************************
 @Function			void TestBench_FLASH_WriteSubSN(void)
 @Description			TestBench_FLASH_WriteSubSN
 @Input				void
 @Return				void
**********************************************************************************************************/
void TestBench_FLASH_WriteSubSN(void)
{
	unsigned int subsn = 0x00000000;
	
	subsn |= *(__IO uint8_t *)(FLASH_END - 0) << 0;
	subsn |= *(__IO uint8_t *)(FLASH_END - 1) << 8;
	subsn |= *(__IO uint8_t *)(FLASH_END - 2) << 16;
	subsn |= *(__IO uint8_t *)(FLASH_END - 3) << 24;
	
	TCFG_EEPROM_Set_MAC_SN(subsn);
	TCFG_EEPROM_SetVender("mvb");
}

/**********************************************************************************************************
 @Function			void TestBench_StateCtrl_ALL_ENBALE(void)
 @Description			TestBench_StateCtrl_ALL_ENBALE
 @Input				void
 @Return				void
**********************************************************************************************************/
void TestBench_StateCtrl_ALL_ENBALE(void)
{
	TestBenchClient.TestState |=  (1<<0);
	TestBenchClient.SendTimes = 0x03;
}

/**********************************************************************************************************
 @Function			void TestBench_StateCtrl_ALL_DISABLE(void)
 @Description			TestBench_StateCtrl_ALL_DISABLE
 @Input				void
 @Return				void
**********************************************************************************************************/
void TestBench_StateCtrl_ALL_DISABLE(void)
{
	TestBenchClient.TestState &= ~(1<<0);
	TestBenchClient.SendTimes = 0x00;
}

/**********************************************************************************************************
 @Function			bool TestBench_StateCtrl_ALL_STATE(void)
 @Description			TestBench_StateCtrl_ALL_STATE
 @Input				void
 @Return				bool
**********************************************************************************************************/
bool TestBench_StateCtrl_ALL_STATE(void)
{
	return (TestBenchClient.TestState & (1<<0)) ? true : false;
}




















/********************************************** END OF FLEE **********************************************/
