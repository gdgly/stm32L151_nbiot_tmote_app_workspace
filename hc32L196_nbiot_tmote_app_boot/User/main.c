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
	
	BEEP_Repeat_Control(1, 150, 20);														//di
	Delay_MS(100);
	BEEP_Repeat_Control(2, 70, 25);														//didi
	Delay_MS(150);
	BEEP_Repeat_Control(1, 150, 20);														//di
	Delay_MS(100);
	BEEP_Repeat_Control(2, 70, 25);														//didi
	
	upgradClient.ug_app_offset = APP_LOWEST_ADDRESS;
	
#ifdef MVB_SUBSN
	TCFG_EEPROM_Set_MAC_SN(MVB_SUBSN);														//写入SN
	TCFG_EEPROM_Set_Vender(MVB_BRAND);														//写入VENDER
	TCFG_EEPROM_WriteConfigData();														//写入系统配置信息
#endif
	
	systemEnvData.BootVersion = TCFG_EEPROM_Get_BootVersion();									//获取BootVersion
	if (systemEnvData.BootVersion != MVB_BOOT_SOFTWARE_SUB) {
		systemEnvData.BootVersion = MVB_BOOT_SOFTWARE_SUB;
		TCFG_EEPROM_Set_BootVersion(systemEnvData.BootVersion);								//写入BootVersion
	}
	
	systemEnvData.BootMode = TCFG_EEPROM_Get_BootMode();										//获取BootMode
	if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_TOUPDATE) {
		upgradClient.ug_boot_mode = TCFG_ENV_BOOTMODE_TOUPDATE;
	}
	else if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_UPDATING) {
		upgradClient.ug_boot_mode = TCFG_ENV_BOOTMODE_UPDATING;
	}
	else if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_REUPDATE) {
		upgradClient.ug_boot_mode = TCFG_ENV_BOOTMODE_REUPDATE;
	}
	else if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_NORMAL) {
		upgradClient.ug_boot_mode = TCFG_ENV_BOOTMODE_NORMAL;
	}
	else {
		upgradClient.ug_boot_mode = TCFG_ENV_BOOTMODE_NORMAL;
		systemEnvData.BootMode = TCFG_ENV_BOOTMODE_NORMAL;
		TCFG_EEPROM_Set_BootMode(systemEnvData.BootMode);										//写入BootMode
	}
	
	systemEnvData.BootCount = TCFG_EEPROM_Get_BootCount();										//获取BootCount
	if (systemEnvData.BootCount > 100) {
		systemEnvData.BootCount = 0;
		TCFG_EEPROM_Set_BootCount(systemEnvData.BootCount);									//写入BootCount
	}
	
	Radio_Trf_Printf("Boot-%d-mode-%d-count-%d-", systemEnvData.BootVersion, systemEnvData.BootMode, systemEnvData.BootCount);
	
#ifdef	DEVICE_DEBUG
	DeBugMain();
#endif
	
	
	
	
	
	
	
	
	
	
	TCFG_EEPROM_Set_BootCount(systemEnvData.BootCount + 1);
	HC32_IWDG_Feed();
	
	
	
	
	
	
	
	
	
	
	upgradClient.ug_upgrad_state = NO_APPDOWNLOAD;
	*(u32*)upgradClient.ug_mac_sn = TCFG_EEPROM_Get_MAC_SN();
	
	while (upgradClient.ug_join_state != JOIN_COMPELET) {
		
		Delay_MS(10);
		
		HC32_IWDG_Feed();
		
		Radio_RFA_Boot_Xmit_Heartbeat();
		
		
		
		
		
		
		
		
	}
	
start:
	while (true) {
		
		if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_TOUPDATE) {
			
			
			
			
			
			
		}
		else if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_UPDATING) {
			
			
			
			
		}
		else if (systemEnvData.BootMode == TCFG_ENV_BOOTMODE_REUPDATE) {
			
			
			
			
		}
		else {
			
			
			
			
		}
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
