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
#include "hal_iwdg.h"
#include "hal_rtc.h"
#include "hal_beep.h"
#include "hal_vbat.h"
#include "hal_vptat.h"
#include "hal_vtemp.h"
#include "hal_aes.h"
#include "hal_crc.h"
#include "hal_flash.h"
#include "hal_iic.h"
#include "hal_bl24cxxp.h"
#include "hal_eeprom.h"
#include "hal_qmc5883l.h"
#include "hal_spi.h"
#include "hal_p25qxxh.h"
#include "hal_norflash.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
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
	int res = 0, index = 0, loop = 0;
	
	HC32_PeripheralAll_Reset();															//HC32外设模块复位
	
	HC32_PeripheralClockGate_Init();														//HC32外设时钟门控初始化
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_48M)
	HC32_RCHClock48M_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_32M)
	HC32_RCHClock32M_Init();																//HC32RCH时钟初始化32MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH_24M)
	HC32_XTHClock24M_Init();																//HC32XTH时钟初始化24MHz
#endif
	
	HC32_HPClock_Init(SysctrlClkPLL, SysctrlHclkDiv1, SysctrlPclkDiv2);							//HC32时钟HCLK/PCLK初始化
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
#if RTC_TYPE
	HC32_RTC_Init();																	//HC32实时时钟初始化
#endif
	
	HC32_BEEP_Init(OFF);																//HC32蜂鸣器关闭
	
	HC32_LowPowerIO_Init();																//HC32低功耗IO初始化
	HC32_RstPowerIO_Init();																//HC32复位电源初始化
	HC32_CtrPowerIO_Init();																//HC32控制电源初始化
	
	HC32_BEEP_Init(OFF);																//HC32蜂鸣器关闭
	
#if USART0_TYPE
	HC32_Uart0_Init(UART0_BAUD_RATE);														//HC32串口0初始化
#endif
#if USART1_TYPE
	HC32_Uart1_Init(UART1_BAUD_RATE);														//HC32串口1初始化
#endif
	
	HC32_MODEL_POWER_SET(ON);															//HC32外设模块电源开启
	
	Delay_MS(100);																		//HC32供电稳定
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
	FLASH_EEPROM_Init();																//EEPROM初始化
	
	FLASH_NOR_Init();																	//NOR初始化
	
	QMC5883L_Init();																	//QMC5883L初始化
	
	Radio_Hal_RF_Init();																//SI44382A初始化
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
	HC32_AutomaticSystem_Check();															//HC32系统自检
	
	Radio_Hal_RF_Init();																//SI44382A初始化
	
	app_offset = APP_LOWEST_ADDRESS;
	
#ifdef MVB_SUBSN
	TCFG_EEPROM_Set_MAC_SN(MVB_SUBSN);														//写入SN
	TCFG_EEPROM_Set_Vender(MVB_BRAND);														//写入VENDER
#endif
	
	TCFG_EEPROM_Set_BootVersion(MVB_BOOT_SOFTWARE_SUB);
	
	res = TCFG_EEPROM_Get_BootMode();
	if (res == TCFG_ENV_BOOTMODE_TOUPDATE)
		iap_bootmode = TCFG_ENV_BOOTMODE_TOUPDATE;
	else if (res == TCFG_ENV_BOOTMODE_UPDATING)
		iap_bootmode = TCFG_ENV_BOOTMODE_UPDATING;
	else if (res == TCFG_ENV_BOOTMODE_REUPDATE)
		iap_bootmode = TCFG_ENV_BOOTMODE_REUPDATE;
	else
		iap_bootmode = TCFG_ENV_BOOTMODE_NORMALLY;
	
	res = TCFG_EEPROM_Get_BootCount();
	
	HC32_BEEP_Repeat(1, 150, 30);															//di
	Delay_MS(100);
	HC32_BEEP_Repeat(2, 70, 45);															//didi
	Delay_MS(100);
	HC32_BEEP_Repeat(1, 150, 30);															//di
	Delay_MS(100);
	HC32_BEEP_Repeat(2, 70, 45);															//didi
	
	Radio_RF_Trf_Printf("Boot-%d-mode-%d-count-%d-nor-%d-", MVB_BOOT_SOFTWARE_SUB, iap_bootmode, res, FLASH_NOR_Status() ? 0 : 1);
	
	if (res > 7) {
		if (res % 2 == 0)
			iap_bootmode = TCFG_ENV_BOOTMODE_UPDATING;
		else
			iap_bootmode = TCFG_ENV_BOOTMODE_REUPDATE;
		
		if (res >= 100) res = 7;
	}
	
	TCFG_EEPROM_Set_BootCount(res + 1);
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
#ifdef	DEVICE_DEBUG
	DeBugMain();
#endif
	
	if (iap_bootmode == TCFG_ENV_BOOTMODE_NORMALLY)
		goto start;
	
	if (iap_bootmode == TCFG_ENV_BOOTMODE_REUPDATE)
		goto start;
	
	if (rTRF_OK != Radio_Hal_RF_Get_Status()) {
		iap_bootmode = TCFG_ENV_BOOTMODE_NORMALLY;
		goto start;
	}
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
	Radio_Hal_RF_Init();																//SI44382A初始化
	
	iap_upgrad_state = NO_APPDOWNLOAD;
	
	iap_subsn = TCFG_EEPROM_Get_MAC_SN();
	
	memcpy(subsn, &iap_subsn, 4);
	
	while (iap_joined_state != JOIN_COMPELET)
	{
		for (loop = 200; loop != 0; loop--) {
			for (index = 1000; index != 0; index--);
		}
		
		index = 0;
		
		HC32_IWDG_Feed();
		
		Radio_RF_Xmit_Heartbeat();
		
		Delay_MS(100 * (HC32_GetMecondTick() % 3));
		
		xm_Ugrade_join();
		
		while (index < 900) {
			Delay_MS(1);
			Radio_RF_Trf_Receive_Task();
			index++;
		}
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
start:
	while (true) {
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		printf("Reset: %d Runing: %d SN: 0x%X\r\n", HC32_Reset_Flag, HC32_GetMecondTick(), TCFG_EEPROM_Get_MAC_SN());
		
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
