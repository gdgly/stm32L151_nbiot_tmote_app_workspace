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
#include "fifo.h"
#include "message.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
#include "fota.h"
#include "tmesh_xtea.h"

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
	HC32_PeripheralAll_Reset();															//HC32外设模块复位
	
	HC32_PeripheralClockGate_Init();														//HC32外设时钟门控初始化
	
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_48M)
	HC32_RCHClock48M_Init();																//HC32RCH时钟初始化48MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_32M)
	HC32_RCHClock32M_Init();																//HC32RCH时钟初始化32MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_16M)
	HC32_RCHClock16M_Init();																//HC32RCH时钟初始化16MHz
#endif
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_XTH_24M)
	HC32_XTHClock24M_Init();																//HC32XTH时钟初始化24MHz
#endif
	
	HC32_HPClock_Init(SysctrlClkPLL, SysctrlHclkDiv4, SysctrlPclkDiv1);							//HC32时钟HCLK/PCLK初始化
	
#if SYSTEM_RESETFLAG_TYPE
	HC32_Reset_Flag = HC32_SystemReset_GetStatus();											//HC32获取复位标志位
#endif
	
	HC32_IWDG_Init(WdtT52s4);															//HC32看门狗初始化
	
	HC32_Delay_Init(Sysctrl_GetHClkFreq());													//HC32系统延时初始化
	
	HC32_SysTick_Init();																//HC32系统嘀嗒定时器初始化
	
	HC32_RTC_Init();																	//HC32实时时钟初始化
	
	HC32_BEEP_Repeat(5, 60, 25);															//HC32蜂鸣器
	HC32_IWDG_Feed();																	//HC32喂狗
	
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
	
	Delay_MS(10);																		//HC32供电稳定
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
	HC32_FLASH_Init(flashHCLK_32MHz, TRUE);													//FLASH初始化
	
	FLASH_EEPROM_Init();																//EEPROM初始化
	
	FLASH_NOR_Init();																	//NOR初始化
	
	HC32_IWDG_Feed();																	//HC32喂狗
	
	/* Todo: 雷达初始化 */
	
	
	
	
	
	
#ifdef MVB_SUBSN
	TCFG_EEPROM_Set_MAC_SN(MVB_SUBSN);
	TCFG_EEPROM_Set_Vender(MVB_BRAND);
	TCFG_EEPROM_WriteSystemConfigData();													//写入系统配置信息
	TCFG_EEPROM_WriteSystemParamtData();													//写入系统参数信息
#endif
	
	if (TCFG_EEPROM_CheckNewSerialInfomation()) {											//检测新的设备厂牌信息
		TCFG_EEPROM_WriteSystemConfigData();												//写入系统配置信息
	}
	if (TCFG_EEPROM_CheckNewSoftwareEditions()) {											//检测新的固件版本信息
		TCFG_EEPROM_WriteSystemParamtData();												//写入系统参数信息
	}
	
	TCFG_EEPROM_SystemConfigInfo_Init();													//系统配置信息初始化
	
	tmesh_securityInit();																//XTEA加密初始化
	
	Radio_Hal_RF_Init();																//SI4438初始化
	
	Radio_Trf_Do_Heartbeat();															//SI4438发送心跳包
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	HC32_BEEP_Repeat(10, 60, 25);															//HC32蜂鸣器
	HC32_IWDG_Feed();																	//HC32喂狗
	
	Radio_RF_Trf_Printf("Device Reboot:%d Cause:%d Radar:%d Nor:%s", 0, 0, 0, "Ok");
	Radio_RF_Trf_Printf("Copyright (C) 2020 Movebroad Version:%d.%d", TCFG_Utility_Get_Major_SoftwareNumber(), TCFG_Utility_Get_Minor_SoftwareNumber());
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	printf("SN: %x\r\n", TCFG_Utility_Get_Factory_MacSN());
	printf("Vender: %x\r\n", TCFG_Utility_Get_Factory_Vender());
	printf("SN Str: %s\r\n", TCFG_Utility_Get_Factory_MacSN_String());
	printf("Vender Str: %s\r\n", TCFG_Utility_Get_Factory_Vender_String());
	
	printf("BV : %d\r\n", TCFG_Utility_Get_BootVersion());
	printf("BM : %d\r\n", TCFG_Utility_Get_BootMode());
	printf("BC : %d\r\n", TCFG_Utility_Get_BootCount());
	
	printf("TCFG_Utility_Get_RadioChannel : %d\r\n", TCFG_Utility_Get_RadioChannel());
	printf("TCFG_Utility_Get_RadioHeartval : %d\r\n", TCFG_Utility_Get_RadioHeartval());
	
	struct tm date;
	
	HC32_RTC_SetTime(20, 04, 16, 10, 00, 00);
	
	while (true)
	{
		
		date = HC32_RTC_GetUnixTimeToCalendar();
		
		printf("*******************************************************************************************\r\n");
		printf("This is Upgrade to Jump Application\r\n");
		printf("Reset: %d Runing: %8d HCLK: %d PCLK: %d SystemCoreClock: %d\r\n", HC32_Reset_Flag, HC32_GetMecondTick(), Sysctrl_GetHClkFreq(), Sysctrl_GetPClkFreq(), SystemCoreClock);
		printf("Date:  %02d-%02d-%02d %02d:%02d:%02d week %d\r\n", date.tm_year, date.tm_mon, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec, date.tm_wday);
		printf("*******************************************************************************************\r\n\r\n");
		
		Delay_MS(1000);
		
		HC32_IWDG_Feed();
		
		
		
		
		
		Radio_RF_Trf_App_Task();
		
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
