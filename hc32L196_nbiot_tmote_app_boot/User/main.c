/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-03
  * @brief   1TAB = 5Speace
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_beep.h"
#include "hal_iwdg.h"
#include "hal_rtc.h"
#include "hal_vbat.h"
#include "hal_vptat.h"
#include "hal_vtemp.h"
#include "hal_iic.h"
#include "hal_bl24cxxp.h"
#include "hal_eeprom.h"
#include "hal_qmc5883l.h"
#include "hal_spi.h"
#include "hal_p25qxxh.h"
#include "hal_norflash.h"
#include "radio_hal_rf.h"
#include "radio_rfa_boot.h"
#include "iap_boot.h"
#include "iap_core.h"
#include "iap_ugrade.h"

/****************************************** Select DEBUG *************************************************/
//#define	DEVICE_DEBUG																	//定义开启设备调试
/********************************************* DEBUG *****************************************************/
#ifdef	DEVICE_DEBUG
void DeBugMain(void);
#endif
/****************************************** Debug Ending *************************************************/

/**********************************************************************************************************
 @Function			int main(void)
 @Description			Main
 @Input				void
 @Return				int
**********************************************************************************************************/
int main(void)
{
	HC32_PeripheralClockGate_Init();														//HC32外设时钟门控初始化
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH)
	HC32_RCHClock_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH)
	HC32_XTHClock_Init();																//HC32XTH时钟初始化32MHz
#endif
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
	HC32_RTC_Init();																	//HC32实时时钟初始化
	
	HC32_LowPowerIO_Init();																//HC32低功耗IO初始化
	HC32_RstPowerIO_Init();																//HC32复位电源初始化
	HC32_CtrPowerIO_Init();																//HC32控制电源初始化
	
	MODEL_POWER_IO_SET(ON);																//外设模块电源开启(QMC5883L/SI4438)
	
	BEEP_GPIO_InitControl(OFF);															//蜂鸣器关闭
	
	Delay_MS(100);																		//供电稳定
	HC32_IWDG_Feed();																	//喂狗
	
	FLASH_EEPROM_Init();																//片外EEPROM初始化
	
	FLASH_NOR_Init();																	//片外NOR初始化
	
	QMC5883L_Init();																	//QMC5883L初始化
	
	Radio_Hal_RF_Init(&si4438Client);														//SI44382A初始化
	
	HC32_Uart0_Init(9600);																//UART0初始化
	HC32_Uart1_Init(9600);																//UART1初始化
	
	HC32_IWDG_Feed();																	//喂狗
	
	HC32_AutomaticSystem_Check();															//HC32系统自检
	
	BEEP_Repeat_Control(1, 150, 0);
	Delay_MS(100);
	BEEP_Repeat_Control(2, 50, 25);
	Delay_MS(80);
	BEEP_Repeat_Control(1, 150, 0);
	Delay_MS(100);
	BEEP_Repeat_Control(2, 50, 25);														//di~didi~di~didi
	
#ifdef MVB_SUBSN
	TCFG_EEPROM_Set_MAC_SN(MVB_SUBSN);														//写入SN
	TCFG_EEPROM_Set_Vender(MVB_BRAND);														//写入VENDER
#endif
	
	TCFG_EEPROM_Set_BootVersion(MVB_BOOT_SOFTWARE_SUB);										//写入BootVersion
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	while (true) {
		
#ifdef	DEVICE_DEBUG
		DeBugMain();
#endif
		
		HC32_IWDG_Feed();
		
		Delay_MS(1000);
		
		
		
		
		
		
		
		
		
		
	}
}

#ifdef	DEVICE_DEBUG
/********************************************* DEBUG *****************************************************/
/****************************************** Debug Ending *************************************************/
/**********************************************************************************************************
 @Function			void DeBugMain(void)
 @Description			DeBugMain
 @Input				void
 @Return				void
**********************************************************************************************************/
void DeBugMain(void)
{
	
}
#endif

/********************************************** END OF FLEE **********************************************/
