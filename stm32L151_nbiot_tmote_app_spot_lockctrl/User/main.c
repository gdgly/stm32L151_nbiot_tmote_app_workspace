/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
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
#include "stm32l1xx_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_rtc.h"
#include "hal_eeprom.h"
#include "hal_iwdg.h"
#include "hal_beep.h"
#include "hal_switch.h"
#include "hal_vbat.h"
#include "hal_temperature.h"
#include "hal_iic.h"
#include "hal_qmc5883l.h"
#include "hal_bm1422agmv.h"
#include "hal_spiflash.h"
#include "hal_testbench.h"
#include "hal_infraredtube.h"
#include "hal_buzzer.h"
#include "hal_motor.h"
#include "hal_ook.h"
#include "net_nbiot_app.h"
#include "net_coap_app.h"
#include "net_pcp_app.h"
#include "net_dns_app.h"
#include "net_mqttsn_app.h"
#include "net_mqttsn_pcp_app.h"
#include "net_onenet_app.h"
#include "net_ctwing_app.h"
#include "radar_api.h"
#include "radio_hal_rf.h"
#include "radio_rf_app.h"
#include "rollingover.h"
#include "tmesh_xtea.h"
#include "inspectconfig.h"
#include "inspectmessageoperate.h"
#include "spotlockconfig.h"
#include "spotlockapp.h"

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
	HAL_Init();																		//HAL库初始化
	
#ifndef SYSTEMCLOCK
	#error No Define SYSTEMCLOCK!
#else
#if (SYSTEMCLOCK == SYSTEMCLOCKMSI)
	Stm32_MSIClock_Init(RCC_MSIRANGE_6);													//设置时钟MSI->4.194MHz
	Delay_Init(4194);																	//延时初始化4.194MHz系统时钟
#elif (SYSTEMCLOCK == SYSTEMCLOCKHSI)
	Stm32_HSIClock_Init(RCC_PLLMUL_6, RCC_PLLDIV_3);											//设置时钟HSI->32MHz
	Delay_Init(32000);																	//延时初始化32MHz系统时钟
#elif (SYSTEMCLOCK == SYSTEMCLOCKHSE)
	Stm32_HSEClock_Init(RCC_PLLMUL_6, RCC_PLLDIV_3);											//设置时钟HSE->32MHz
	Delay_Init(32000);																	//延时初始化32MHz系统时钟
#else
	#error SYSTEMCLOCK Define Error
#endif
#endif
	
	SoftResetFlag = RCC_ResetFlag_GetStatus();												//获取复位标志位
	
	IWDG_Init(IWDG_PRESCALER_256, 0x0FFF);													//看门狗初始化,溢出时间28s
	RTC_Init();																		//RTC初始化
	
	BEEP_CtrlRepeat_Extend(5, 50, 25);														//蜂鸣器
	IWDG_Feed();																		//喂狗
	
	LowPowerCtrlIO_Init();																//低功耗控制IO初始化
	ModulePowerReset_Init();																//模块电源复位
	PowerCtrlIO_Init();																	//电源控制IO初始化
	
	Radar_Init();																		//雷达初始化
	
#ifdef MVB_SUBSN
	TCFG_EEPROM_Set_MAC_SN(MVB_SUBSN);														//写入MACSN
	TCFG_EEPROM_SetVender(MVB_BRAND);														//写入Verder
	TCFG_EEPROM_WriteConfigData();														//写入系统配置信息
#endif
	
#if TESTBENCH_TYPE
	if (TestBench_FLASH_CheckSubSN() == true) {												//测试架写入SN到FLASH
		TestBench_FLASH_WriteSubSN();														//写入MACSN
	}
#endif
	
	if (TCFG_EEPROM_CheckNewSNorBrand() == true) {											//检测新设备号或厂牌
		TCFG_EEPROM_WriteConfigData();													//写入系统配置信息
	}
	if (TCFG_EEPROM_CheckNewSoftware() == true) {											//检测新软件版本号
		TCFG_EEPROM_WriteParameterData();													//写入系统参数信息
	}
	TCFG_EEPROM_SystemInfo_Init();														//系统运行信息初始化
	
#if USART1_TYPE
	Uart1_Init(9700);																	//串口1初始化
#endif
#if USART2_TYPE
	Uart2_Init(115200);																	//串口2初始化
#endif
	
#ifdef GD25Q_80CSIG
	GD25Q_SPIFLASH_Init();																//SPI FLASH初始化
	GD25Q_SPIFLASH_PowerDown();															//SPI FLASH休眠
#endif
	
#ifdef RADIO_SI4438
	tmesh_securityInit();																//XTEA加密初始化
	Radio_Rf_Init();																	//SI4438初始化
	Radio_Trf_Xmit_Heartbeat();															//SI4438发送心跳包
#endif
	
	QMC5883L_Init();																	//地磁初始化
	
	Inspect_Spot_Init();																//车位检测算法初始化
	
#if DEVICE_BOOT_START_MAGINIT_TYPE
	if (SoftResetFlag == RCC_RESET_FLAG_PORRST) {
		Radar_InitBackground(TO_SAVE_RADAR_BACKGROUND);										//雷达背景初始化
		QMC5883L_InitBackgroud();														//地磁背景初始化
	}
#endif
	
	NET_NBIOT_Initialization();															//NBIOT初始化
	
	BEEP_CtrlRepeat_Extend(10, 50, 25);													//蜂鸣器
	IWDG_Feed();																		//喂狗
	
	Radio_Trf_Printf(" Device Reboot:%d Cause:%d Radar:%d Nor:%s", TCFG_SystemData.DeviceBootCount, SoftResetFlag, radar_vcc, GD25Q_SPIFLASH_Get_Status()?"None":"Ok");
	Radio_Trf_Printf(" Copyright (C) 2020 Movebroad Version:%d.%d", TCFG_Utility_Get_Major_Softnumber(), TCFG_Utility_Get_Sub_Softnumber());
	
	SPOT_Lock_Initialization();															//SpotLock初始化
	IWDG_Feed();
	
	OOK_EXTI_Initialization();															//SpotLock遥控器初始化
	IWDG_Feed();
	
	while (true) {
		
#ifdef	DEVICE_DEBUG
		DeBugMain();
#endif
		
		/* 翻转检测处理 */
		RollingOverPollExecution();
		
		/* 喂狗 */
		IWDG_Feed();
		
#if LOWPOWERMODE == LOWPOWERENABLE
		LowPowerBeforeSleepInit();
		LowPowerEnterStop();
		LowPowerAfterSleepInit();
#elif LOWPOWERMODE == LOWPOWERDISABLE
		Delay_MS(1000);
#endif
		
		/* 喂狗 */
		IWDG_Feed();
		
		/* 软重启计数器清0 */
		SystemSoftResetTime = 0;
		
		/* 运行正常BootCount清0 */
		if ((BootUp == true) && (Stm32_GetSecondTick() > RUNNING_SUCCESS_BOOT_COUNT_SEC)) {
			TCFG_EEPROM_SetBootCount(0);
			if (TCFG_EEPROM_GetBootCount() == 0) {
				BootUp = false;
			}
		}
		
		/* 运行正常BackupApp */
		if ((BackUp == true) && (Stm32_GetSecondTick() > RUNNING_SUCCESS_BACKUP_APP_SEC)) {
			NET_NBIOT_BackupCurrentApp_Task();
			BackUp = false;
		}
	}
}

/**********************************************************************************************************
 @Function			void MainMajorCycleMqttSN(void)
 @Description			MainMajorCycleMqttSN
 @Input				void
 @Return				void
 @attention			MqttSN等待数据接收中需处理程序
**********************************************************************************************************/
void MainMajorCycleMqttSN(void)
{
	/* 小无线处理 */
	Radio_Trf_App_Task();
	
	/* 车辆检测 */
	Inspect_Spot_ExistenceDetect();
	
	/* 检测是否需要初始化传感器背景 */
	RollingOverInitSensorBackground();
	
	/* 日常处理 */
	MainHandleRoutine();
	
	/* NBIOT Data Processing */
	NET_NBIOT_DataProcessing(&NetNbiotClientHandler);
	
	/* 喂狗 */
	IWDG_Feed();
	
#if LOWPOWERMODE == LOWPOWERENABLE
	LowPowerBeforeSleepInit();
	LowPowerEnterStop();
	LowPowerAfterSleepInit();
#elif LOWPOWERMODE == LOWPOWERDISABLE
	Delay_MS(1000);
#endif
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 软重启计数器清0 */
	SystemSoftResetTime = 0;
}

/**********************************************************************************************************
 @Function			void MainMajorCycleOneNET(void)
 @Description			MainMajorCycleOneNET
 @Input				void
 @Return				void
 @attention			OneNET等待数据接收中需处理程序
**********************************************************************************************************/
void MainMajorCycleOneNET(void)
{
	/* 小无线处理 */
	Radio_Trf_App_Task();
	
	/* 检测是否需要初始化传感器背景 */
	RollingOverInitSensorBackground();
	
	/* 日常处理 */
	MainHandleRoutine();
	
	/* NBIOT Data Processing */
	NET_NBIOT_DataProcessing(&NetNbiotClientHandler);
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 软重启计数器清0 */
	SystemSoftResetTime = 0;
}

/* ============================================ 正放处理 =============================================== */

/**********************************************************************************************************
 @Function			void MainRollingEnteredUpWork(void)
 @Description			MainRollingEnteredUpWork					: 已进入正放工作状态
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteredUpWork(void)
{
	Radio_Trf_Printf("Entered Up Work");
	BEEP_CtrlRepeat_Extend(3, 30, 70);
#if NETPROTOCAL == NETCOAP
	NETCoapNeedSendCode.WorkInfoWait = 3;
#elif NETPROTOCAL == NETMQTTSN
	NETMqttSNNeedSendCode.InfoWorkWait = 3;
#elif NETPROTOCAL == NETONENET
	NETOneNETNeedSendCode.WorkInfoWait = 3;
#elif NETPROTOCAL == NETCTWING
	NETCTWingNeedSendCode.WorkInfoWait = 3;
#endif
	
	if (TCFG_SystemData.NBIotSentCountDay != 0) TCFG_SystemData.NBIotSentCountDay = 0;
	if (TCFG_EEPROM_GetNBIotSentCountDay() != 0) TCFG_EEPROM_SetNBIotSentCountDay(TCFG_SystemData.NBIotSentCountDay);
}

/**********************************************************************************************************
 @Function			void MainRollingEnteringUpWork(void)
 @Description			MainRollingEnteringUpWork				: 将进入正放工作状态
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteringUpWork(void)
{
	Radio_Trf_Printf("Entering Up Work");
	BEEP_CtrlRepeat_Extend(1, 500, 0);
}

/**********************************************************************************************************
 @Function			void MainRollingUpwardsActived(void)
 @Description			MainRollingUpwardsActived				: 正放工作中
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingUpwardsActived(void)
{
	/* 车辆检测 */
	Inspect_Spot_ExistenceDetect();
	
	/* 日常处理 */
	MainHandleRoutine();
	
	if (!((NETCoapNeedSendCode.WorkInfoWait > 0) || (NETMqttSNNeedSendCode.InfoWorkWait > 0) || (NETOneNETNeedSendCode.WorkInfoWait > 0) || (NETCTWingNeedSendCode.WorkInfoWait > 0))) {
#if PRODUCTTEST_READ_TYPE
		if (ProductTest_Read() || (TCFG_Utility_Get_Device_BootCount() > PRODUCTTEST_OVER_BOOTCNT)) {
		#if NBIOT_SNEDCOUNTDAY_LIMIT_TYPE
			if (TCFG_Utility_Get_NBIot_SentCountDay() == TCFG_EEPROM_GetNBIotSentCountLimit()) {
			#if NETPROTOCAL == NETCOAP
				NETCoapNeedSendCode.DynamicInfo = 1;
			#elif NETPROTOCAL == NETMQTTSN
				NETMqttSNNeedSendCode.InfoDynamic = 1;
			#elif NETPROTOCAL == NETONENET
				NETOneNETNeedSendCode.DynamicInfo = 1;
			#elif NETPROTOCAL == NETCTWING
				NETCTWingNeedSendCode.DynamicInfo = 1;
			#endif
			}
			if (TCFG_Utility_Get_NBIot_SentCountDay() > TCFG_EEPROM_GetNBIotSentCountLimit() + 1) {
				if (NBIOTPOWER_IO_READ()) {
					NET_NBIOT_Initialization();
					NBIOTPOWER(OFF);
				}
			}
			else {
				/* NBIOT APP Task */
				NET_NBIOT_App_Task();
			}
		#else
			/* NBIOT APP Task */
			NET_NBIOT_App_Task();
		#endif
		}
		else {
			/* NBIOT Power OFF */
			if (NBIOTPOWER_IO_READ()) {
				NBIOT_Neul_NBxx_CheckReadIMEI(&NbiotClientHandler);
				NBIOT_Neul_NBxx_TestSupportedBands(&NbiotClientHandler, NBIOT_MODULE_BAND_SUPPORT);
				NET_NBIOT_Initialization();
				NBIOTPOWER(OFF);
			}
			if (NbiotClientHandler.Parameter.bandsupport != true) {
				Radio_Trf_Printf("imei:null or band:no support");
				BEEP_CtrlRepeat_Extend(3, 50, 25);
			}
			else {
				Radio_Trf_Printf("imei:%s", TCFG_Utility_Get_Nbiot_Imei_String());
			}
		}
#else
	#if NBIOT_SNEDCOUNTDAY_LIMIT_TYPE
		if (TCFG_Utility_Get_NBIot_SentCountDay() == TCFG_EEPROM_GetNBIotSentCountLimit()) {
		#if NETPROTOCAL == NETCOAP
			NETCoapNeedSendCode.DynamicInfo = 1;
		#elif NETPROTOCAL == NETMQTTSN
			NETMqttSNNeedSendCode.InfoDynamic = 1;
		#elif NETPROTOCAL == NETONENET
			NETOneNETNeedSendCode.DynamicInfo = 1;
		#elif NETPROTOCAL == NETCTWING
			NETCTWingNeedSendCode.DynamicInfo = 1;
		#endif
		}
		if (TCFG_Utility_Get_NBIot_SentCountDay() > TCFG_EEPROM_GetNBIotSentCountLimit() + 1) {
			if (NBIOTPOWER_IO_READ()) {
				NET_NBIOT_Initialization();
				NBIOTPOWER(OFF);
			}
		}
		else {
			/* NBIOT APP Task */
			NET_NBIOT_App_Task();
		}
	#else
		/* NBIOT APP Task */
		NET_NBIOT_App_Task();
	#endif
#endif
	}
	
	/* 遥控器编码处理 */
	OOK_EXTI_PollExecution(false);
	
	/* 车锁控制 */
	SPOT_Lock_App_Task();
	
	/* 小无线处理 */
	Radio_Trf_App_Task();
}

/**********************************************************************************************************
 @Function			void MainRollingEnteringUpWork(void)
 @Description			MainRollingEnteringUpWork				: 正放休眠中
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingUpwardsSleep(void)
{
#if NBIOT_UPWARDSSLEEP_TYPE
	/* 日常处理 */
	MainHandleRoutine();
	
	if (TCFG_Utility_Get_Nbiot_IdleLifetime() > 0) {
		/* NBIOT APP Task */
		NET_NBIOT_App_Task();
	}
	else {
#endif
		/* NBIOT Power OFF */
		if (NBIOTPOWER_IO_READ()) {
			NET_NBIOT_Initialization();
			NBIOTPOWER(OFF);
		}
#if NBIOT_UPWARDSSLEEP_TYPE
	}
	
	/* 小无线处理 */
	Radio_Trf_App_Task();
#endif
}

/* ============================================ 倒放处理 =============================================== */

/**********************************************************************************************************
 @Function			void MainRollingEnteredDownSleep(void)
 @Description			MainRollingEnteredDownSleep				: 已进入倒放休眠状态
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteredDownSleep(void)
{
	BEEP_CtrlRepeat_Extend(1, 500, 0);
}

/**********************************************************************************************************
 @Function			void MainRollingEnteredDownWork(void)
 @Description			MainRollingEnteredDownWork				: 已进入倒放工作状态
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteredDownWork(void)
{
#if NETPROTOCAL == NETCOAP
	NETCoapNeedSendCode.WorkInfoWait = 3;
#elif NETPROTOCAL == NETMQTTSN
	NETMqttSNNeedSendCode.InfoWorkWait = 3;
#elif NETPROTOCAL == NETONENET
	NETOneNETNeedSendCode.WorkInfoWait = 3;
#elif NETPROTOCAL == NETCTWING
	NETCTWingNeedSendCode.WorkInfoWait = 3;
#endif
}

/**********************************************************************************************************
 @Function			void MainRollingEnteredDownSleepKeepActived(void)
 @Description			MainRollingEnteredDownSleepKeepActived		: 将进入倒放休眠状态前保持工作
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteredDownSleepKeepActived(void)
{
	/* 日常处理 */
	MainHandleRoutine();
	
	if (!((NETCoapNeedSendCode.WorkInfoWait > 0) || (NETMqttSNNeedSendCode.InfoWorkWait > 0) || (NETOneNETNeedSendCode.WorkInfoWait > 0) || (NETCTWingNeedSendCode.WorkInfoWait > 0))) {
#if PRODUCTTEST_READ_TYPE
		if (ProductTest_Read() || (TCFG_Utility_Get_Device_BootCount() > PRODUCTTEST_OVER_BOOTCNT)) {
			/* NBIOT APP Task */
			NET_NBIOT_App_Task();
		}
		else {
			/* NBIOT Power OFF */
			if (NBIOTPOWER_IO_READ()) {
				NET_NBIOT_Initialization();
				NBIOTPOWER(OFF);
			}
		}
#else
		/* NBIOT APP Task */
		NET_NBIOT_App_Task();
#endif
	}
}

/**********************************************************************************************************
 @Function			void MainRollingEnteringDownSleep(void)
 @Description			MainRollingEnteringDownSleep				: 将进入倒放休眠
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingEnteringDownSleep(void)
{
	/* NBIOT Power OFF */
	if (NBIOTPOWER_IO_READ()) {
		NET_NBIOT_Initialization();
		NBIOTPOWER(OFF);
	}
}

/**********************************************************************************************************
 @Function			void MainRollingDownSleep(void)
 @Description			MainRollingDownSleep					: 倒放休眠中
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainRollingDownSleep(void)
{
#if NBIOT_DNWARDSSLEEP_TYPE
	/* 日常处理 */
	MainHandleRoutine();
	
	if (TCFG_Utility_Get_Nbiot_IdleLifetime() > 0) {
		/* NBIOT APP Task */
		NET_NBIOT_App_Task();
	}
	else {
#endif
		/* NBIOT Power OFF */
		if (NBIOTPOWER_IO_READ()) {
			NET_NBIOT_Initialization();
			NBIOTPOWER(OFF);
		}
#if NBIOT_DNWARDSSLEEP_TYPE
	}
#endif
}

/* ============================================ 日常处理 =============================================== */

/**********************************************************************************************************
 @Function			void MainHandleRoutine(void)
 @Description			MainHandleRoutine
 @Input				void
 @Return				void
**********************************************************************************************************/
void MainHandleRoutine(void)
{
	uint8_t val8;
	
	/* Every Second Running */
	if (Stm32_GetSecondTick() != SystemRunningTime.seconds) {
		SystemRunningTime.seconds = Stm32_GetSecondTick();
		
	}
	/* Every Ten Secound Running */
	if ((Stm32_GetSecondTick() / 10) != SystemRunningTime.tenseconds) {
		SystemRunningTime.tenseconds = Stm32_GetSecondTick() / 10;
		
#if NETPROTOCAL == NETCOAP
		if (NETCoapNeedSendCode.WorkInfoWait > 0) {
			if (NETCoapNeedSendCode.WorkInfoWait > 1) {
				__NOP();
			}
			else if (NETCoapNeedSendCode.WorkInfoWait > 0) {
		#if ROLLINGOVER_WORKINFO_TYPE
			#if NBCOAP_SENDCODE_WORK_INFO
				NETCoapNeedSendCode.WorkInfo = 1;
			#endif
		#endif
			}
			NETCoapNeedSendCode.WorkInfoWait--;
		}
#endif
#if NETPROTOCAL == NETMQTTSN
		if (NETMqttSNNeedSendCode.InfoWorkWait > 0) {
			if (NETMqttSNNeedSendCode.InfoWorkWait > 1) {
				__NOP();
			}
			else if (NETMqttSNNeedSendCode.InfoWorkWait > 0) {
		#if ROLLINGOVER_WORKINFO_TYPE
			#if NBMQTTSN_SENDCODE_WORK_INFO
				NETMqttSNNeedSendCode.InfoWork = 1;
			#endif
		#endif
			}
			NETMqttSNNeedSendCode.InfoWorkWait--;
		}
#endif
#if NETPROTOCAL == NETONENET
		if (NETOneNETNeedSendCode.WorkInfoWait > 0) {
			if (NETOneNETNeedSendCode.WorkInfoWait > 1) {
				__NOP();
			}
			else if (NETOneNETNeedSendCode.WorkInfoWait > 0) {
		#if ROLLINGOVER_WORKINFO_TYPE
			#if NBONENET_SENDCODE_WORK_INFO
				NETOneNETNeedSendCode.WorkInfo = 1;
			#endif
		#endif
			}
			NETOneNETNeedSendCode.WorkInfoWait--;
		}
#endif
#if NETPROTOCAL == NETCTWING
		if (NETCTWingNeedSendCode.WorkInfoWait > 0) {
			if (NETCTWingNeedSendCode.WorkInfoWait > 1) {
				__NOP();
			}
			else if (NETCTWingNeedSendCode.WorkInfoWait > 0) {
		#if ROLLINGOVER_WORKINFO_TYPE
			#if NBCTWING_SENDCODE_WORK_INFO
				NETCTWingNeedSendCode.WorkInfo = 1;
			#endif
		#endif
			}
			NETCTWingNeedSendCode.WorkInfoWait--;
		}
#endif
		TCFG_Utility_Sub_Nbiot_IdleLifetime();
	}
	/* Every Minutes Running */
	if ((Stm32_GetSecondTick() / 60) != SystemRunningTime.minutes) {
		SystemRunningTime.minutes = Stm32_GetSecondTick() / 60;
		
#if NETDATACONNECT_TIMEOUT_TYPE
		if ((DeviceIdleMode == false) && (DeviceActivedMode == true)) {
			NetDataConnectTimeout++;
			if (NetDataConnectTimeout >= NETDATACONNECT_TIMEOUT_TIME) {
				Stm32_System_Software_Reboot(RBTMODE_NETCONNECT_OVERTIME);
			}
		}
		else {
			NetDataConnectTimeout = 0;
		}
#endif
	}
	/* Every FifteenMinutes Running */
	if ((Stm32_GetSecondTick() / 900) != SystemRunningTime.fifteenMinutes) {
		SystemRunningTime.fifteenMinutes = Stm32_GetSecondTick() / 900;
		
	}
	/* Every FortyMinutes Running */
	if ((Stm32_GetSecondTick() / 2400) != SystemRunningTime.fortyMinutes) {
		SystemRunningTime.fortyMinutes = Stm32_GetSecondTick() / 2400;
		
		if (RTC_Time_GetCurrentHour() == 7) {
			if (Inspect_Message_SpotStatusisEmpty() != false) {
				NET_NBIOT_Initialization();
			}
			
			if ((TCFG_EEPROM_GetNBIotSentCountDay() != 0) || (TCFG_SystemData.NBIotSentCountDay != 0)) {
				TCFG_SystemData.NBIotSentCountDay = 0;
				TCFG_EEPROM_SetNBIotSentCountDay(TCFG_SystemData.NBIotSentCountDay);
			}
		}
	}
	/* Every Hours Running */
	if ((Stm32_GetSecondTick() / 3600) != SystemRunningTime.hours) {
		SystemRunningTime.hours = Stm32_GetSecondTick() / 3600;
		
		val8 = TCFG_EEPROM_GetCoapRATimeHour();
		if ((val8 != 0) && (SystemRunningTime.hours % val8 == 0)) {
			NBIOT_COAP_RA_NORMAL_SET_STATE(&NbiotClientHandler, true);
		}
	}
	/* Every TwoHours Running */
	if ((Stm32_GetSecondTick() / 7200) != SystemRunningTime.twoHours) {
		SystemRunningTime.twoHours = Stm32_GetSecondTick() / 7200;
		
		if (TCFG_GetRadarCount() != TCFG_EEPROM_GetRadarCount()) {
			TCFG_EEPROM_SetRadarCount(TCFG_GetRadarCount());
		}
		
		TCFG_SystemData.MagBackgroundX = Qmc5883lData.X_Back;
		TCFG_SystemData.MagBackgroundY = Qmc5883lData.Y_Back;
		TCFG_SystemData.MagBackgroundZ = Qmc5883lData.Z_Back;
		TCFG_EEPROM_SetMagBackgroud(TCFG_SystemData.MagBackgroundX, TCFG_SystemData.MagBackgroundY, TCFG_SystemData.MagBackgroundZ);
		
		TCFG_SystemData.MagBackgroudTemp = Qmc5883lData.temp_back;
		TCFG_EEPROM_SetMagBackgroudTemp(TCFG_SystemData.MagBackgroudTemp);
	}
	/* Every FourHours Running */
	if ((Stm32_GetSecondTick() / (4*3600)) != SystemRunningTime.fourHours) {
		SystemRunningTime.fourHours = Stm32_GetSecondTick() / (4*3600);
		
	}
	/* Every Day Running */
	if ((Stm32_GetSecondTick() / (24*3600)) != SystemRunningTime.days) {
		SystemRunningTime.days = Stm32_GetSecondTick() / (24*3600);
		
#if NETPROTOCAL == NETCOAP
	#if NBCOAP_SENDCODE_WORK_INFO
		NETCoapNeedSendCode.WorkInfo = 1;
	#endif
	#if NBCOAP_SENDCODE_DYNAMIC_INFO
		NETCoapNeedSendCode.DynamicInfo = 1;
	#endif
#elif NETPROTOCAL == NETMQTTSN
	#if NBMQTTSN_SENDCODE_WORK_INFO
		NETMqttSNNeedSendCode.InfoWork = 1;
	#endif
	#if NBMQTTSN_SENDCODE_DYNAMIC_INFO
		NETMqttSNNeedSendCode.InfoDynamic = 1;
	#endif
#elif NETPROTOCAL == NETONENET
	#if NBONENET_SENDCODE_WORK_INFO
		NETOneNETNeedSendCode.WorkInfo = 1;
	#endif
	#if NBONENET_SENDCODE_DYNAMIC_INFO
		NETOneNETNeedSendCode.DynamicInfo = 1;
	#endif
#elif NETPROTOCAL == NETCTWING
	#if NBCTWING_SENDCODE_WORK_INFO
		NETCTWingNeedSendCode.WorkInfo = 1;
	#endif
	#if NBCTWING_SENDCODE_DYNAMIC_INFO
		NETCTWingNeedSendCode.DynamicInfo = 1;
	#endif
#endif
		
		TCFG_SystemData.CoapConnectTime = TCFG_Utility_GetCoapConnectTime();
		TCFG_EEPROM_SetCoapConnectTime(TCFG_SystemData.CoapConnectTime);
		
		TCFG_SystemData.CoapIdleTime = TCFG_Utility_GetCoapIdleTime();
		TCFG_EEPROM_SetCoapIdleTime(TCFG_SystemData.CoapIdleTime);
		
		NBIOT_COAP_RA_NORMAL_SET_STATE(&NbiotClientHandler, true);
		TCFG_Utility_Set_Nbiot_IdleLifetime(NBIOT_MAX_LIFETIME);
		
#if NETPROTOCAL == NETMQTTSN
	#if MQTTSN_DNS_SERVER_TYPE == MQTTSN_DNS_SERVER_ENABLE
		DNS_Analysis_Set_CtrlState(&DNSClientHandler, true);
	#endif
#endif
	}
	/* Every Week Running */
	if ((Stm32_GetSecondTick() / (24*3600*7)) != SystemRunningTime.weeks) {
		SystemRunningTime.weeks = Stm32_GetSecondTick() / (24*3600*7);
		
#if NETPROTOCAL == NETCOAP
	#if NBCOAP_SENDCODE_BASIC_INFO
		NETCoapNeedSendCode.BasicInfo = 1;
	#endif
#elif NETPROTOCAL == NETMQTTSN
	#if NBMQTTSN_SENDCODE_BASIC_INFO
		NETMqttSNNeedSendCode.InfoBasic = 1;
	#endif
#elif NETPROTOCAL == NETONENET
	#if NBONENET_SENDCODE_BASIC_INFO
		NETOneNETNeedSendCode.BasicInfo = 1;
	#endif
#elif NETPROTOCAL == NETCTWING
	#if NBCTWING_SENDCODE_BASIC_INFO
		NETCTWingNeedSendCode.BasicInfo = 1;
	#endif
#endif
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
	TCFG_EEPROM_SetBootCount(0);
	
#if 0
	NBIOT_Neul_NBxx_HardwareReboot(&NbiotClientHandler, 8000);
#endif
	
#if 0
	INFRARED_TUBE_TRANSMIT_ENABLE();
#endif
	
#if 0
	SPOT_Lock_Initialization();
#endif
	
	while (true) {
		
#if 0
		Radio_Trf_Printf("Infr : %d", INFRARED_TUBE_RECEIVE_STATE());
#endif
		
#if 0
		SPOT_Lock_App_Task();
#endif
		
#if DEBUGLOWPOWERMODE == DEBUGLOWPOWERENABLE
		LowPowerBeforeSleepInit();
		LowPowerEnterStop();
		LowPowerAfterSleepInit();
#elif DEBUGLOWPOWERMODE == DEBUGLOWPOWERDISABLE
		/* 小无线处理 */
		Radio_Trf_App_Task();
		
		Delay_MS(1000);
#endif
		
		/* 喂狗 */
		IWDG_Feed();
		
		/* 软重启计数器清0 */
		SystemSoftResetTime = 0;
		
		/* 运行正常BootCount清0 */
		if ((BootUp == true) && (Stm32_GetSecondTick() > RUNNING_SUCCESS_BOOT_COUNT_SEC)) {
			TCFG_EEPROM_SetBootCount(0);
			if (TCFG_EEPROM_GetBootCount() == 0) {
				BootUp = false;
			}
		}
		
		/* 运行正常BackupApp */
		if ((BackUp == true) && (Stm32_GetSecondTick() > RUNNING_SUCCESS_BACKUP_APP_SEC)) {
			NET_NBIOT_BackupCurrentApp_Task();
			BackUp = false;
		}
	}
}
#endif

/********************************************** END OF FLEE **********************************************/
