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
#include "iap_boot.h"
#include "iap_core.h"
#include "iap_ugrade.h"
#include "fota.h"

/****************************************** Select DEBUG *************************************************/
//#define	DEVICE_DEBUG																	//定义开启设备调试
/********************************************* DEBUG *****************************************************/
#ifdef	DEVICE_DEBUG
void DeBugMain(void);
#endif
/****************************************** Debug Ending *************************************************/

#define FOTA_UPDATE_SWAP_BUFFER_LEN		2048
#define FOTA_UPDATE_STACK_BUFFER_LEN		1024

FotaClientsTypeDef FotaClient;

__IO u8 FotaFirmwareBuf[FOTA_UPDATE_STACK_BUFFER_LEN];
__IO u8 FotaPackSliceBuf[FOTA_UPDATE_STACK_BUFFER_LEN];
__IO u8 FotaSwapBuf[FOTA_UPDATE_SWAP_BUFFER_LEN];

void xm_Jump_to_application(unsigned int app_addr);

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
#if (SYSTEM_CLOCK_TYPE == SYSTEM_CLOCK_RCH_16M)
	HC32_RCHClock16M_Init();																//HC32RCH时钟初始化16MHz
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
	
	HC32_FLASH_Init(flashHCLK_32MHz, TRUE);													//FLASH初始化
	
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
	
#if SYSTEM_BOOTCOUNT_CNTYPE
	TCFG_EEPROM_Set_BootCount(0);															//重启次数清零
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
	
	HC32_BEEP_Repeat(1, 140, 40);															//di
	Delay_MS(70);
	HC32_BEEP_Repeat(2, 60, 55);															//didi
	Delay_MS(100);
	HC32_BEEP_Repeat(1, 140, 40);															//di
	Delay_MS(70);
	HC32_BEEP_Repeat(2, 60, 55);															//didi
	
	Radio_RF_Trf_Printf("Boot-%d-mode-%d-count-%02d-nor-%d-", MVB_BOOT_SOFTWARE_SUB, iap_bootmode, res, FLASH_NOR_Status() ? 0 : 1);
	
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
	
#if SYSTEM_BOOTUPGRADE_TYPE
	iap_bootmode = TCFG_ENV_BOOTMODE_TOUPDATE;												//启动进行升级
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
		
		if (HC32_GetSecondTick() >= 120) {
			iap_upgrad_state = TIME_OUT;
			HAL_SystemReset();
		}
		
		if (HC32_GetSecondTick() % 10 == 0) {
			HC32_BEEP_Repeat(1, 60, 140);
		}
	}
	
start:
	while (true)
	{
		if (iap_bootmode == TCFG_ENV_BOOTMODE_TOUPDATE)
		{
			while (1)
			{
				Radio_RF_Trf_Receive_Task();
				
				if (iap_upgrad_state == READY_TO_JUMP)
				{
					TCFG_EEPROM_Set_BootMode(TCFG_ENV_BOOTMODE_NORMALLY);
					xm_Jump_to_application(app_offset);
				}
				else if (iap_upgrad_state == DOWNLOADING)
				{
					Radio_RF_Trf_Receive_Task();
					if (HC32_GetSecondTick() >= OVERTIME) {
						iap_upgrad_state = TIME_OUT;
						HAL_SystemReset();
					}
					else if ((HC32_GetSecondTick() > (30 + Radio_RF_Trf_Last_Recvtime())) && (Radio_RF_Trf_Last_Recvtime() > 0)) {
						iap_upgrad_state = TIME_OUT;
						HAL_SystemReset();
					}
					else if (HC32_GetSecondTick() > (10 + Radio_RF_Trf_Last_Recvtime())) {
						Radio_RF_Xmit_Heartbeat();
					}
				}
				else if (iap_upgrad_state == NO_APPDOWNLOAD)
				{
					Radio_RF_Xmit_Heartbeat();
					for (index = 500; index != 0; index--) {
						Delay_MS(1);
						Radio_RF_Trf_Receive_Task();
					}
					Delay_MS(100 * (HC32_GetMecondTick() % 3));
					xm_Ugrade_join();
					for (index = 500; index != 0; index--) {
						Delay_MS(1);
						Radio_RF_Trf_Receive_Task();
					}
					if (HC32_GetSecondTick() >= 120) {
						TCFG_EEPROM_Set_BootMode(TCFG_ENV_BOOTMODE_NORMALLY);
						xm_Jump_to_application(app_offset);
					}
				}
				else if (iap_upgrad_state == DOWNLOAD_ERROR)
				{
					__NOP();
					Delay_MS(10000);
					HAL_SystemReset();
				}
				
				HC32_IWDG_Feed();
				
				if (HC32_GetSecondTick() % 10 == 0) {
					HC32_BEEP_Repeat(1, 60, 140);
				}
			}
		}
		else if (iap_bootmode == TCFG_ENV_BOOTMODE_UPDATING)
		{
			while (1)
			{
				while (iap_upgrad_state == NO_APPDOWNLOAD)
				{
					Radio_RF_Xmit_Heartbeat();
					for (index = 500; index != 0; index--) {
						Delay_MS(1);
						Radio_RF_Trf_Receive_Task();
					}
					Delay_MS(100 * (HC32_GetMecondTick() % 3));
					xm_Ugrade_join();
					for (index = 500; index != 0; index--) {
						Delay_MS(1);
						Radio_RF_Trf_Receive_Task();
					}
					if (HC32_GetSecondTick() >= OVERTIME) {
						iap_upgrad_state = TIME_OUT;
						HAL_SystemReset();
					}
					
					HC32_IWDG_Feed();
					
					if (HC32_GetSecondTick() % 10 == 0) {
						HC32_BEEP_Repeat(1, 60, 140);
					}
				}
				
				if (iap_upgrad_state == DOWNLOADING)
				{
					Radio_RF_Trf_Receive_Task();
					if (HC32_GetSecondTick() >= OVERTIME) {
						iap_upgrad_state = TIME_OUT;
						HAL_SystemReset();
					}
					else if ((HC32_GetSecondTick() > (30 + Radio_RF_Trf_Last_Recvtime())) && (Radio_RF_Trf_Last_Recvtime() > 0)) {
						iap_upgrad_state = TIME_OUT;
						HAL_SystemReset();
					}
					else if (HC32_GetSecondTick() > (10 + Radio_RF_Trf_Last_Recvtime())) {
						Radio_RF_Xmit_Heartbeat();
					}
				}
				else if (iap_upgrad_state == READY_TO_JUMP)
				{
					TCFG_EEPROM_Set_BootMode(TCFG_ENV_BOOTMODE_NORMALLY);
					xm_Jump_to_application(app_offset);
				}
				else if (iap_upgrad_state == DOWNLOAD_ERROR)
				{
					__NOP();
					Delay_MS(10000);
					HAL_SystemReset();
				}
				
				HC32_IWDG_Feed();
				
				if (HC32_GetSecondTick() >= OVERTIME) {
					iap_upgrad_state = TIME_OUT;
					HAL_SystemReset();
				}
				
				if (HC32_GetSecondTick() % 10 == 0) {
					HC32_BEEP_Repeat(1, 60, 140);
				}
			}
		}
		else if (iap_bootmode == TCFG_ENV_BOOTMODE_REUPDATE)
		{
			if (FLASH_NOR_Status() == Ok) {
				FotaResultCode res;
				
				Radio_RF_Trf_Printf("NorFlash Recover APP......");
				
				if (FLASH_NOR_ReadByte(FOTA_APP1_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					if (TCFG_EEPROM_Get_BootCount() > 3) {
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP1_BASE_ADDR + NOR_BLOCK64K_ADDR(0)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP1_BASE_ADDR + NOR_BLOCK64K_ADDR(1)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP1_BASE_ADDR + NOR_BLOCK64K_ADDR(2)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP1_BASE_ADDR + NOR_BLOCK64K_ADDR(3)));
					}
				}
				
				if (FLASH_NOR_ReadByte(FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					if (TCFG_EEPROM_Get_BootCount() > 30) {
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(0)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(1)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(2)));
						FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(3)));
					}
				}
				
				if (FLASH_NOR_ReadByte(FOTA_APP1_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					FotaClient.FirmwareBuf		= (u8*)FotaFirmwareBuf;
					FotaClient.PackSliceBuf		= (u8*)FotaPackSliceBuf;
					FotaClient.SwapBuf			= (u8*)FotaSwapBuf;
					FotaClient.FirmwareBuf_size	= sizeof(FotaFirmwareBuf);
					FotaClient.PackSliceBuf_size	= sizeof(FotaPackSliceBuf);
					FotaClient.SwapBuf_size		= sizeof(FotaSwapBuf);
					
					FotaClient.ChangeMode		= Fota_NorToChip;
					FotaClient.BackupMode		= Fota_Backup_Normal;
					
					FotaClient.FirmwareBaseAddr	= app_offset;
					FotaClient.PackSliceBaseAddr	= FLASH_NOR_ReadWord(FOTA_APP1_INFO_UPGRADE_BASEADDR_OFFSET);
					FotaClient.PackSliceNum		= FLASH_NOR_ReadHalfWord(FOTA_APP1_INFO_UPGRADE_BLOCKNUM_OFFSET);
					FotaClient.PackSliceSize		= FLASH_NOR_ReadHalfWord(FOTA_APP1_INFO_UPGRADE_BLOCKLEN_OFFSET);
					FotaClient.PackSliceLen		= FLASH_NOR_ReadHalfWord(FOTA_APP1_INFO_UPGRADE_DATALEN_OFFSET);
					
					FotaClient.app_offset		= app_offset;
					FotaClient.firm_writelen		= 128;
					
					res = FOTA_ConvertFirmware(&FotaClient);
					
					Radio_RF_Trf_Printf("Fota Status: %d", res);
					
					app_offset = FotaClient.app_offset;
				}
				else if (FLASH_NOR_ReadByte(FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					FotaClient.FirmwareBuf		= (u8*)FotaFirmwareBuf;
					FotaClient.PackSliceBuf		= (u8*)FotaPackSliceBuf;
					FotaClient.SwapBuf			= (u8*)FotaSwapBuf;
					FotaClient.FirmwareBuf_size	= sizeof(FotaFirmwareBuf);
					FotaClient.PackSliceBuf_size	= sizeof(FotaPackSliceBuf);
					FotaClient.SwapBuf_size		= sizeof(FotaSwapBuf);
					
					FotaClient.ChangeMode		= Fota_NorToChip;
					FotaClient.BackupMode		= Fota_Backup_Normal;
					
					FotaClient.FirmwareBaseAddr	= app_offset;
					FotaClient.PackSliceBaseAddr	= FLASH_NOR_ReadWord(FOTA_APP2_INFO_UPGRADE_BASEADDR_OFFSET);
					FotaClient.PackSliceNum		= FLASH_NOR_ReadHalfWord(FOTA_APP2_INFO_UPGRADE_BLOCKNUM_OFFSET);
					FotaClient.PackSliceSize		= FLASH_NOR_ReadHalfWord(FOTA_APP2_INFO_UPGRADE_BLOCKLEN_OFFSET);
					FotaClient.PackSliceLen		= FLASH_NOR_ReadHalfWord(FOTA_APP2_INFO_UPGRADE_DATALEN_OFFSET);
					
					FotaClient.app_offset		= app_offset;
					FotaClient.firm_writelen		= 128;
					
					res = FOTA_ConvertFirmware(&FotaClient);
					
					Radio_RF_Trf_Printf("Fota Status: %d", res);
					
					app_offset = FotaClient.app_offset;
				}
				else {
					iap_upgrad_state = TIME_OUT;
					HAL_SystemReset();
				}
				HC32_BEEP_Repeat(20, 60, 60);
			}
			else {
				iap_upgrad_state = TIME_OUT;
				HAL_SystemReset();
			}
			
			xm_Jump_to_application(app_offset);
		}
		else {
			xm_Jump_to_application(app_offset);
		}
	}
}

/**********************************************************************************************************
 @Function			void xm_Jump_to_application(unsigned int app_addr)
 @Description			xm_Jump_to_application
 @Input				app_addr
 @Return				void
**********************************************************************************************************/
void xm_Jump_to_application(unsigned int app_addr)
{
#if SYSTEM_JUMPTOAPP_TYPE
	
	u32 app_real_address;
	u32 app_jump_address;
	
	app_real_address = HC32_FLASH_ReadWord(APP_LOWEST_ADDRESS - HC32_FLASH_SECTOR_BLOCK);
	
	if ((app_real_address >= app_addr) && (app_real_address < (HC32_FLASH_BASE + HC32_FLASH_SIZE))) {
		app_jump_address = app_real_address;
	}
	else {
		app_jump_address = app_addr;
	}
	
	IAP_Boot_form_flash(app_jump_address);
	
	while (1) {
		HC32_IWDG_Feed();
		
		Delay_MS(1000);
		
		HAL_SystemReset();
	}
	
#else
	
	while (1) {
		HC32_IWDG_Feed();
		
		Delay_MS(1000);
	}
	
#endif
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
