/**
  *********************************************************************************************************
  * @file    hc32l19x_config.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-09
  * @brief   1TAB = 5Speace
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
#include "delay.h"
#include "usart.h"
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

#define HC32_DEBUG_LOG_RF_PRINTF
#define HC32_DEBUG_LOG_PRINTF				Radio_RF_Trf_Printf

HC32_RESET_FLAG_TypeDef HC32_Reset_Flag = RCC_RESET_FLAG_NONE;

/**********************************************************************************************************
 @Function			HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
 @Description			HC32_SystemReset_GetStatus					: HC32获取复位标志位
 @Input				void
 @Return				HC32_RESET_FLAG_TypeDef						: 复位标志位
**********************************************************************************************************/
HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void)
{
	HC32_RESET_FLAG_TypeDef resetStatus = RCC_RESET_FLAG_NONE;
	
	if (Reset_GetFlag(ResetFlagMskPor5V) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (Reset_GetFlag(ResetFlagMskPor1_5V) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PORRST;
	}
	else if (Reset_GetFlag(ResetFlagMskLvd) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_LPWRRST;
	}
	else if (Reset_GetFlag(ResetFlagMskWdt) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_IWDGRST;
	}
	else if (Reset_GetFlag(ResetFlagMskPca) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PCA;
	}
	else if (Reset_GetFlag(ResetFlagMskLockup) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_LOCKUP;
	}
	else if (Reset_GetFlag(ResetFlagMskSysreq) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_SFTRST;
	}
	else if (Reset_GetFlag(ResetFlagMskRstb) != FALSE) {
		Reset_ClearFlagAll();
		resetStatus = RCC_RESET_FLAG_PINRST;
	}
	
	return resetStatus;
}

/**********************************************************************************************************
 @Function			void HC32_System_Software_Reboot(HC32_REBOOT_MODE_TypeDef mode)
 @Description			HC32_System_Software_Reboot					: HC32软件重启
 @Input				mode
 @Return				void
**********************************************************************************************************/
void HC32_System_Software_Reboot(HC32_REBOOT_MODE_TypeDef mode)
{
	TCFG_Utility_Set_DeviceRebootMode(mode);
	
	HC32_SystemReset();
}

/**********************************************************************************************************
 @Function			void HC32_PeripheralAll_Reset(void)
 @Description			HC32_PeripheralAll_Reset						: HC32外设模块复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_PeripheralAll_Reset(void)
{
	Reset_RstPeripheralAll();
}

/**********************************************************************************************************
 @Function			void HC32_LowPowerIO_Init(void)
 @Description			HC32_LowPowerIO_Init						: HC32低功耗IO初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_LowPowerIO_Init(void)
{
	M0P_GPIO->PAADS = 0xFFFF;
	M0P_GPIO->PBADS = 0xFFFF;
	M0P_GPIO->PCADS = 0xFFFF;
	M0P_GPIO->PDADS = 0xFFFF;
	M0P_GPIO->PEADS = 0xFFFF;
	M0P_GPIO->PFADS = 0xFFFF;
	
	HC32_BEEP_Init(OFF);
}

/**********************************************************************************************************
 @Function			static void Device_ModelPower_Init(void)
 @Description			Device_ModelPower_Init						: 外设模块电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_ModelPower_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(MODEL_POWER_GPIOx, MODEL_POWER_PIN, &GPIO_Initure);
	
	MODEL_POWER_IO_SET(OFF);
}

/**********************************************************************************************************
 @Function			static void Device_RadarPower_Init(void)
 @Description			Device_RadarPower_Init						: 外设雷达电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_RadarPower_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(RADAR_POWER_GPIOx, RADAR_POWER_PIN, &GPIO_Initure);
	
	RADAR_POWER_IO_SET(OFF);
}

/**********************************************************************************************************
 @Function			static void Device_NBIotPower_Init(void)
 @Description			Device_NBIotPower_Init						: 外设NBIoT电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_NBIotPower_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(NBIOT_POWER_GPIOx, NBIOT_POWER_PIN, &GPIO_Initure);
	
	NBIOT_POWER_IO_SET(OFF);
}

/**********************************************************************************************************
 @Function			static void Device_VBatePower_Init(void)
 @Description			Device_VBatePower_Init						: 外设VBate电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_VBatePower_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(VBATE_POWER_GPIOx, VBATE_POWER_PIN, &GPIO_Initure);
	
	VBATE_POWER_IO_SET(OFF);
}

/**********************************************************************************************************
 @Function			static void Device_FlashNSS_Init(void)
 @Description			Device_FlashNSS_Init						: 外设FlashNSS初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_FlashNSS_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN, GpioAf0);
	
	Gpio_SetIO(P25QXXH_SPIx_NSS_GPIOx, P25QXXH_SPIx_NSS_PIN);
}

/**********************************************************************************************************
 @Function			static void Device_RadioNSS_Init(void)
 @Description			Device_RadioNSS_Init						: 外设RadioNSS初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
static void Device_RadioNSS_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, GpioAf0);
	
	Gpio_SetIO(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN);
}

/**********************************************************************************************************
 @Function			void HC32_RstPowerIO_Init(void)
 @Description			HC32_RstPowerIO_Init						: HC32复位电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_RstPowerIO_Init(void)
{
	Device_FlashNSS_Init();																//Flash SPI NSS 未选
	Device_RadioNSS_Init();																//Radio SPI NSS 未选
	
	Device_ModelPower_Init();															//外设模块电源初始化
	Device_RadarPower_Init();															//外设雷达电源初始化
	Device_NBIotPower_Init();															//外设NBIoT电源初始化
	Device_VBatePower_Init();															//外设VBate电源初始化
	
	MODEL_POWER_IO_SET(OFF);																//外设模块电源关闭
	RADAR_POWER_IO_SET(OFF);																//外设雷达电源关闭
	NBIOT_POWER_IO_SET(OFF);																//外设NBIoT电源关闭
	VBATE_POWER_IO_SET(OFF);																//外设VBate电源关闭
	
	Delay_MS(2500);																	//外设断电2.5秒
}

/**********************************************************************************************************
 @Function			void HC32_CtrPowerIO_Init(void)
 @Description			HC32_CtrPowerIO_Init						: HC32控制电源初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_CtrPowerIO_Init(void)
{
	MODEL_POWER_IO_SET(OFF);																//外设模块电源关闭
	RADAR_POWER_IO_SET(OFF);																//外设雷达电源关闭
	NBIOT_POWER_IO_SET(OFF);																//外设NBIoT电源关闭
	VBATE_POWER_IO_SET(OFF);																//外设VBate电源关闭
}

/**********************************************************************************************************
 @Function			void HC32_AutomaticSystem_Check(void)
 @Description			HC32_AutomaticSystem_Check					: HC32系统自检
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_AutomaticSystem_Check(void)
{
	if (Radio_Hal_RF_Get_Status() != rTRF_OK) {
		HC32_BEEP_Repeat(1, 3000, 100);
#ifdef HC32_DEBUG_LOG_RF_PRINTF
		HC32_DEBUG_LOG_PRINTF("Application: SI4438 Error!!!");
		HC32_DEBUG_LOG_PRINTF("Application: SI4438 Error!!!");
#endif
		return;
	}
	
	if (HC32_FLASH_Status() != Ok) {
		HC32_BEEP_Repeat(1, 3000, 100);
#ifdef HC32_DEBUG_LOG_RF_PRINTF
		HC32_DEBUG_LOG_PRINTF("Application: CFLASH Error!!!");
		HC32_DEBUG_LOG_PRINTF("Application: CFLASH Error!!!");
#endif
		return;
	}
	
	if (FLASH_EEPROM_Status() != Ok) {
		HC32_BEEP_Repeat(1, 3000, 100);
#ifdef HC32_DEBUG_LOG_RF_PRINTF
		HC32_DEBUG_LOG_PRINTF("Application: EEPROM Error!!!");
		HC32_DEBUG_LOG_PRINTF("Application: EEPROM Error!!!");
#endif
		return;
	}
	
	if (FLASH_NOR_Status() != Ok) {
		HC32_BEEP_Repeat(1, 3000, 100);
#ifdef HC32_DEBUG_LOG_RF_PRINTF
		HC32_DEBUG_LOG_PRINTF("Application: NORFLH Error!!!");
		HC32_DEBUG_LOG_PRINTF("Application: NORFLH Error!!!");
#endif
		return;
	}
}































/**********************************************************************************************************
 @Function			void HC32_LowPower_SleepBefor_Init(void)
 @Description			HC32_LowPower_SleepBefor_Init					: 进入低功耗stop模式之前初始化
 @Input				void
 @Return				void
 @attention			不用模拟IO口
					PA0 PA2 PA3 PA5 PA6 PA7 PA8 PA9 PA10 PA11 PA12 PA15 => 9FED
					PB3 PB4 PB6 PB7 PB8 PB10 PB11 PB12                  => 1DD8
**********************************************************************************************************/
void HC32_LowPower_SleepBefor_Init(void)
{
	Radio_Hal_RF_Set_Sleep();
	Radio_Hal_RF_Interrupt_Disable();
	
	QMC5883L_Drdy_DeInit();
	
	M0P_GPIO->PAADS |= ~(0x9FED);
	M0P_GPIO->PBADS |= ~(0x1DD8);
	M0P_GPIO->PCADS |= ~(0x0000);
	M0P_GPIO->PDADS |= ~(0x0000);
	M0P_GPIO->PEADS |= ~(0x0000);
	M0P_GPIO->PFADS |= ~(0x0000);
	
	Device_FlashNSS_Init();
	Device_RadioNSS_Init();
}

/**********************************************************************************************************
 @Function			void HC32_LowPower_SleepEnter_Stop(void)
 @Description			HC32_LowPower_SleepEnter_Stop					: 进入低功耗stop模式
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_LowPower_SleepEnter_Stop(void)
{
	static timeMeterTypeDef systemWorkTimer;
	
	u32 workTimeMs = 0;
	u32 idleTimeMs = 0;
	
	workTimeMs = HC32_TimeMeter_RunTimerObtainMS(&systemWorkTimer);
	
	idleTimeMs = 1000 - (workTimeMs % 1000);
	
	HC32_AddMecondTick(idleTimeMs);
	
	HC32_IncSecondTick();
	
	Lpm_GotoDeepSleep(FALSE);
	
	HC32_TimeMeter_RunTimerStartMS(&systemWorkTimer);
}

/**********************************************************************************************************
 @Function			void HC32_LowPower_SleepAfter_Init(void)
 @Description			HC32_LowPower_SleepAfter_Init					: 进入低功耗stop模式之后初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_LowPower_SleepAfter_Init(void)
{
	Radio_Hal_RF_Interface_Init();
	Radio_Hal_RF_Interrupt_Enable();
	
	QMC5883L_Drdy_Init();
}

/**********************************************************************************************************
 @Function			void HC32_LowPower_Sleep_Task(void)
 @Description			HC32_LowPower_Sleep_Task						: HC32低功耗处理
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_LowPower_Sleep_Task(void)
{
#if SYSTEM_LOWPOWER_TYPE == SYSTEM_LOWPOWER_ENABLE
	HC32_LowPower_SleepBefor_Init();
	HC32_LowPower_SleepEnter_Stop();
	HC32_LowPower_SleepAfter_Init();
#endif
	
#if SYSTEM_LOWPOWER_TYPE == SYSTEM_LOWPOWER_DISABLE
	Delay_MS(1000);
#endif
}



























/********************************************** END OF FLEE **********************************************/
