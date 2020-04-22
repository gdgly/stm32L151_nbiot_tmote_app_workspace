/**
  *********************************************************************************************************
  * @file    platform_map.c
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

TCFG_SystemDataTypeDef TCFG_SystemData;





















/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_SystemConfigInfo_Init(void)
 @Description			TCFG_EEPROM_SystemConfigInfo_Init				: 系统配置信息初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_SystemConfigInfo_Init(void)
{
	TCFG_EEPROM_ReadSystemConfigData();
	
	TCFG_EEPROM_Set_BootMode(TCFG_ENV_BOOTMODE_NORMALLY);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_WriteSystemConfigData(void)
 @Description			TCFG_EEPROM_WriteSystemConfigData				: 写入系统配置信息
 @Input				void
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_WriteSystemConfigData(void)
{
	/* 写入Radio RF 通道 */
	TCFG_SystemData.RadioChannel = RADIO_RF_CHANNEL1;
	TCFG_EEPROM_Set_RadioChannel(TCFG_SystemData.RadioChannel);
	
	/* 写入Radio RF 心跳 */
	TCFG_SystemData.RadioHeartval = RADIO_RF_HEARTVAL;
	TCFG_EEPROM_Set_RadioHeartval(TCFG_SystemData.RadioHeartval);
	
	/* 写入Device Reboot Mode重启方式 */
	TCFG_SystemData.DevRebootMode = REBOOT_MODE_NONE;
	TCFG_EEPROM_Set_DeviceRebootMode(TCFG_SystemData.DevRebootMode);
	
	/* 写入传感器灵敏度值 */
	TCFG_SystemData.Sensitivity = SENSE_MIDDLE;
	TCFG_EEPROM_Set_Sensitivity(TCFG_SystemData.Sensitivity);
	
	/* 写入工作模式 */
	TCFG_SystemData.WorkMode = WORK_MODE_NORMAL;
	TCFG_EEPROM_Set_WorkMode(TCFG_SystemData.WorkMode);
	
	/* 写入休眠模式 */
	TCFG_SystemData.IdleMode = IDLE_MODE_DISABLE;
	TCFG_EEPROM_Set_IdleMode(TCFG_SystemData.IdleMode);
	
	/* 写入运行模式 */
	TCFG_SystemData.ActiveMode = ACTIVE_MODE_ENABLE;
	TCFG_EEPROM_Set_ActiveMode(TCFG_SystemData.ActiveMode);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/* SN & Vender Write to Backup space */
	TCFG_EEPROM_Set_Backup_MAC_SN(TCFG_EEPROM_Get_Source_MAC_SN());
	TCFG_EEPROM_Set_Backup_Vender(TCFG_EEPROM_Get_Source_Vender());
}

/**********************************************************************************************************
 @Function			void TCFG_EEPROM_WriteParameterData(void)
 @Description			TCFG_EEPROM_WriteParameterData				: 写入系统参数信息
 @Input				void
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_WriteSystemParamtData(void)
{
	
	
	
	
	
	
	
	
	
	
	/* Software Write to Backup space */
	TCFG_EEPROM_Set_Backup_SoftwareMajor(TCFG_EEPROM_Get_Source_SoftwareMajor());
	TCFG_EEPROM_Set_Backup_SoftwareMinor(TCFG_EEPROM_Get_Source_SoftwareMinor());
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_ReadSystemConfigData(void)
 @Description			TCFG_EEPROM_ReadSystemConfigData				: 读取系统配置信息
 @Input				void
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_ReadSystemConfigData(void)
{
	/* 获取MacSN */
	TCFG_SystemData.MacSN = TCFG_EEPROM_Get_MAC_SN();
	
	/* 获取Vender */
	TCFG_SystemData.Vender = TCFG_EEPROM_Get_Source_Vender();
	
	/* 获取MacSN String */
	TCFG_EEPROM_Get_MAC_SN_String();
	
	/* 获取Vender String */
	TCFG_EEPROM_Get_Vender_String();
	
	/* 获取BOOT版本号 */
	TCFG_SystemData.BootVersion = TCFG_EEPROM_Get_BootVersion();
	
	/* 获取BOOT运行模式 */
	TCFG_SystemData.BootRunmode = TCFG_EEPROM_Get_BootMode();
	
	/* 获取BOOT重启次数 */
	TCFG_SystemData.BootRecount = TCFG_EEPROM_Get_BootCount();
	
	/* 获取Radio RF 通道 */
	TCFG_SystemData.RadioChannel = TCFG_EEPROM_Get_RadioChannel();
	if ((TCFG_SystemData.RadioChannel != 36) && (TCFG_SystemData.RadioChannel != 4) && (TCFG_SystemData.RadioChannel != 6) && (TCFG_SystemData.RadioChannel != 16) && (TCFG_SystemData.RadioChannel != 26)) {
		TCFG_SystemData.RadioChannel = RADIO_RF_CHANNEL1;
		TCFG_EEPROM_Set_RadioChannel(TCFG_SystemData.RadioChannel);
	}
	
	/* 获取Radio RF 心跳 */
	TCFG_SystemData.RadioHeartval = TCFG_EEPROM_Get_RadioHeartval();
	if ((TCFG_SystemData.RadioHeartval < 1) || (TCFG_SystemData.RadioHeartval > 120)) {
		TCFG_SystemData.RadioHeartval = RADIO_RF_HEARTVAL;
		TCFG_EEPROM_Set_RadioHeartval(TCFG_SystemData.RadioHeartval);
	}
	
	/* 获取Device Reboot Mode重启方式 */
	TCFG_SystemData.DevRebootMode = TCFG_EEPROM_Get_DeviceRebootMode();
	
	/* 获取传感器灵敏度值 */
	TCFG_SystemData.Sensitivity = TCFG_EEPROM_Get_Sensitivity();
	if ((TCFG_SystemData.Sensitivity < SENSE_HIGHEST) || (TCFG_SystemData.Sensitivity > SENSE_LOWEST)) {
		TCFG_SystemData.Sensitivity = SENSE_MIDDLE;
		TCFG_EEPROM_Set_Sensitivity(TCFG_SystemData.Sensitivity);
	}
	
	/* 获取工作模式 */
	TCFG_SystemData.WorkMode = TCFG_EEPROM_Get_WorkMode();
	if ((TCFG_SystemData.WorkMode != WORK_MODE_NORMAL) && (TCFG_SystemData.WorkMode != WORK_MODE_DEBUG)) {
		TCFG_SystemData.WorkMode = WORK_MODE_NORMAL;
		TCFG_EEPROM_Set_WorkMode(TCFG_SystemData.WorkMode);
	}
	
	/* 获取休眠模式 */
	TCFG_SystemData.IdleMode = TCFG_EEPROM_Get_IdleMode();
	if ((TCFG_SystemData.IdleMode != IDLE_MODE_DISABLE) && (TCFG_SystemData.IdleMode != IDLE_MODE_ENABLE)) {
		TCFG_SystemData.IdleMode = IDLE_MODE_DISABLE;
		TCFG_EEPROM_Set_IdleMode(TCFG_SystemData.IdleMode);
	}
	
	/* 获取运行模式 */
	TCFG_SystemData.ActiveMode = TCFG_EEPROM_Get_ActiveMode();
	if ((TCFG_SystemData.ActiveMode != ACTIVE_MODE_DISABLE) && (TCFG_SystemData.ActiveMode != ACTIVE_MODE_ENABLE)) {
		TCFG_SystemData.ActiveMode = ACTIVE_MODE_ENABLE;
		TCFG_EEPROM_Set_ActiveMode(TCFG_SystemData.ActiveMode);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
























/********************** Check if the SN & Vender and the Backup space are the same ***********************/
/**********************************************************************************************************
 @Function			bool  TCFG_EEPROM_CheckNewSerialInfomation(void)
 @Description			TCFG_EEPROM_CheckNewSerialInfomation			: 检测新的设备厂牌信息
 @Input				void
 @Return				bool
**********************************************************************************************************/
bool  TCFG_EEPROM_CheckNewSerialInfomation(void)
{
	if ((TCFG_EEPROM_Get_Backup_MAC_SN() == 0) && (TCFG_EEPROM_Get_Backup_Vender() == 0)) {
		return true;
	}
	
	if ((TCFG_EEPROM_Get_Backup_MAC_SN() != TCFG_EEPROM_Get_Source_MAC_SN()) || (TCFG_EEPROM_Get_Backup_Vender() != TCFG_EEPROM_Get_Source_Vender())) {
		return true;
	}
	
	return false;
}

u32   TCFG_EEPROM_Get_Source_MAC_SN(void)
{
	return FLASH_EEPROM_ReadWord(TCFG_FACTORY_MAC_SN_OFFSET);
}

u32   TCFG_EEPROM_Get_Source_Vender(void)
{
	return FLASH_EEPROM_ReadWord(TCFG_FACTORY_VENDER_OFFSET);
}

void  TCFG_EEPROM_Set_Backup_MAC_SN(u32 val)
{
	FLASH_EEPROM_WriteWord(TCFG_FACTORYBACKUP_MAC_SN_OFFSET, val);
}

u32   TCFG_EEPROM_Get_Backup_MAC_SN(void)
{
	return FLASH_EEPROM_ReadWord(TCFG_FACTORYBACKUP_MAC_SN_OFFSET);
}

void  TCFG_EEPROM_Set_Backup_Vender(u32 val)
{
	FLASH_EEPROM_WriteWord(TCFG_FACTORYBACKUP_VENDER_OFFSET, val);
}

u32   TCFG_EEPROM_Get_Backup_Vender(void)
{
	return FLASH_EEPROM_ReadWord(TCFG_FACTORYBACKUP_VENDER_OFFSET);
}
/*********************************************************************************************************/

/********************** Check if the SoftwareVer and the Backup space are the same ***********************/
/**********************************************************************************************************
 @Function			bool  TCFG_EEPROM_CheckNewSoftwareEditions(void)
 @Description			TCFG_EEPROM_CheckNewSoftwareEditions			: 检测新的固件版本信息
 @Input				void
 @Return				bool
**********************************************************************************************************/
bool  TCFG_EEPROM_CheckNewSoftwareEditions(void)
{
	if ((TCFG_EEPROM_Get_Backup_SoftwareMajor() == 0) && (TCFG_EEPROM_Get_Backup_SoftwareMinor() == 0)) {
		return true;
	}
	
	if ((TCFG_EEPROM_Get_Backup_SoftwareMajor() != TCFG_EEPROM_Get_Source_SoftwareMajor()) || (TCFG_EEPROM_Get_Backup_SoftwareMinor() != TCFG_EEPROM_Get_Source_SoftwareMinor())) {
		return true;
	}
	
	return false;
}

u8    TCFG_EEPROM_Get_Source_SoftwareMajor(void)
{
	return TCFG_Utility_Get_Major_SoftwareNumber();
}

u8    TCFG_EEPROM_Get_Source_SoftwareMinor(void)
{
	return TCFG_Utility_Get_Minor_SoftwareNumber();
}

void  TCFG_EEPROM_Set_Backup_SoftwareMajor(u8 val)
{
	FLASH_EEPROM_WriteByte(TCFG_SOFTWAREBACKUP_MAJOR_OFFSET, val);
}

u8    TCFG_EEPROM_Get_Backup_SoftwareMajor(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_SOFTWAREBACKUP_MAJOR_OFFSET);
}

void  TCFG_EEPROM_Set_Backup_SoftwareMinor(u8 val)
{
	FLASH_EEPROM_WriteByte(TCFG_SOFTWAREBACKUP_MINOR_OFFSET, val);
}

u8    TCFG_EEPROM_Get_Backup_SoftwareMinor(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_SOFTWAREBACKUP_MINOR_OFFSET);
}
/*********************************************************************************************************/

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_MAC_SN(u32 sn)
 @Description			TCFG_EEPROM_Set_MAC_SN						: 保存MAC_SN
 @Input				sn
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_MAC_SN(u32 sn)
{
	FLASH_EEPROM_WriteWord(TCFG_FACTORY_MAC_SN_OFFSET, sn);
}

/**********************************************************************************************************
 @Function			u32   TCFG_EEPROM_Get_MAC_SN(void)
 @Description			TCFG_EEPROM_Get_MAC_SN						: 读取MAC_SN
 @Input				void
 @Return				sn
**********************************************************************************************************/
u32   TCFG_EEPROM_Get_MAC_SN(void)
{
	u32 sn = 0;
	
	sn = FLASH_EEPROM_ReadWord(TCFG_FACTORY_MAC_SN_OFFSET);
	
	sn = (sn == 0) ? 1 : sn;
	
	return sn;
}

/**********************************************************************************************************
 @Function			char* TCFG_EEPROM_Get_MAC_SN_String(void)
 @Description			TCFG_EEPROM_Get_MAC_SN_String					: 读取MAC SN字符串
 @Input				void
 @Return				sn_string
**********************************************************************************************************/
char* TCFG_EEPROM_Get_MAC_SN_String(void)
{
	memset((void *)TCFG_SystemData.FactoryMacsn, 0x00, sizeof(TCFG_SystemData.FactoryMacsn));
	
	sprintf((char *)TCFG_SystemData.FactoryMacsn, "%08x", TCFG_EEPROM_Get_MAC_SN());
	
	return (char *)TCFG_SystemData.FactoryMacsn;
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_Vender(char* vender)
 @Description			TCFG_EEPROM_Set_Vender						: 保存Vender
 @Input				vender
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_Vender(char* vender)
{
	vender[TCFG_FACTORY_VENDER_LENGTH - 1] = '\0';
	FLASH_EEPROM_WriteBuffer(TCFG_FACTORY_VENDER_OFFSET, (u8*)vender, TCFG_FACTORY_VENDER_LENGTH);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_Vender(char* vender)
 @Description			TCFG_EEPROM_Set_Vender						: 读取Vender
 @Input				vender
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Get_Vender(char* vender)
{
	FLASH_EEPROM_ReadBuffer(TCFG_FACTORY_VENDER_OFFSET, (u8*)vender, TCFG_FACTORY_VENDER_LENGTH);
	vender[TCFG_FACTORY_VENDER_LENGTH - 1] = '\0';
}

/**********************************************************************************************************
 @Function			char* TCFG_EEPROM_Get_Vender_String(void)
 @Description			TCFG_EEPROM_Get_Vender_String					: 读取vender字符串
 @Input				void
 @Return				vender_string
**********************************************************************************************************/
char* TCFG_EEPROM_Get_Vender_String(void)
{
	memset((void *)TCFG_SystemData.FactoryVender, 0x00, sizeof(TCFG_SystemData.FactoryVender));
	
	TCFG_EEPROM_Get_Vender((char *)TCFG_SystemData.FactoryVender);
	
	return (char *)TCFG_SystemData.FactoryVender;
}




























/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_BootVersion(u8 bootVer)
 @Description			TCFG_EEPROM_Set_BootVersion					: 保存BootVersion
 @Input				bootVer
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_BootVersion(u8 bootVer)
{
	FLASH_EEPROM_WriteByte(TCFG_BOOT_VERSION_OFFSET, bootVer);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_BootVersion(void)
 @Description			TCFG_EEPROM_Get_BootVersion					: 读取BootVersion
 @Input				void
 @Return				bootVer
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_BootVersion(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_BOOT_VERSION_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_BootMode(u8 bootMode)
 @Description			TCFG_EEPROM_Set_BootMode						: 保存BootMode
 @Input				bootMode
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_BootMode(u8 bootMode)
{
	FLASH_EEPROM_WriteByte(TCFG_BOOT_RUNMODE_OFFSET, bootMode);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_BootMode(void)
 @Description			TCFG_EEPROM_Get_BootMode						: 读取BootMode
 @Input				void
 @Return				bootMode
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_BootMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_BOOT_RUNMODE_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_BootCount(u8 bootCount)
 @Description			TCFG_EEPROM_Set_BootCount					: 保存BootCount
 @Input				bootCount
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_BootCount(u8 bootCount)
{
	FLASH_EEPROM_WriteByte(TCFG_BOOT_RECOUNT_OFFSET, bootCount);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_BootCount(void)
 @Description			TCFG_EEPROM_Get_BootCount					: 读取BootCount
 @Input				void
 @Return				bootCount
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_BootCount(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_BOOT_RECOUNT_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_RadioChannel(u8 channel)
 @Description			TCFG_EEPROM_Set_RadioChannel					: 保存RadioChannel
 @Input				channel
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_RadioChannel(u8 channel)
{
	FLASH_EEPROM_WriteByte(TCFG_RADIO_CHANNEL_OFFSET, channel);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_RadioChannel(void)
 @Description			TCFG_EEPROM_Get_RadioChannel					: 读取RadioChannel
 @Input				void
 @Return				channel
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_RadioChannel(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_RADIO_CHANNEL_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_RadioHeartval(u8 heartval)
 @Description			TCFG_EEPROM_Set_RadioHeartval					: 保存RadioHeartval
 @Input				heartval
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_RadioHeartval(u8 heartval)
{
	FLASH_EEPROM_WriteByte(TCFG_RADIO_HEARTVL_OFFSET, heartval);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_RadioHeartval(void)
 @Description			TCFG_EEPROM_Get_RadioHeartval					: 读取RadioHeartval
 @Input				void
 @Return				heartval
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_RadioHeartval(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_RADIO_HEARTVL_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_DeviceRebootMode(u8 rebootmode)
 @Description			TCFG_EEPROM_Set_DeviceRebootMode				: 保存DeviceRebootMode
 @Input				rebootmode
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_DeviceRebootMode(u8 rebootmode)
{
	FLASH_EEPROM_WriteByte(TCFG_DEVICE_RBTMODE_OFFSET, rebootmode);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_DeviceRebootMode(void)
 @Description			TCFG_EEPROM_Get_DeviceRebootMode				: 读取DeviceRebootMode
 @Input				void
 @Return				rebootmode
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_DeviceRebootMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_DEVICE_RBTMODE_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_Sensitivity(u8 sens)
 @Description			TCFG_EEPROM_Set_Sensitivity					: 保存Sensitivity
 @Input				sens
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_Sensitivity(u8 sens)
{
	FLASH_EEPROM_WriteByte(TCFG_SENSITIVITY_OFFSET, sens);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_Sensitivity(void)
 @Description			TCFG_EEPROM_Get_Sensitivity					: 读取Sensitivity
 @Input				void
 @Return				sens
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_Sensitivity(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_SENSITIVITY_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_WorkMode(u8 workmode)
 @Description			TCFG_EEPROM_Set_WorkMode						: 保存WorkMode
 @Input				workmode
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_WorkMode(u8 workmode)
{
	FLASH_EEPROM_WriteByte(TCFG_WORKMODE_OFFSET, workmode);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_WorkMode(void)
 @Description			TCFG_EEPROM_Get_WorkMode						: 读取WorkMode
 @Input				void
 @Return				workmode
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_WorkMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_WORKMODE_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_IdleMode(u8 idlemode)
 @Description			TCFG_EEPROM_Set_IdleMode						: 保存IdleMode
 @Input				idlemode
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_IdleMode(u8 idlemode)
{
	FLASH_EEPROM_WriteByte(TCFG_IDLEMODE_OFFSET, idlemode);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_IdleMode(void)
 @Description			TCFG_EEPROM_Get_IdleMode						: 读取IdleMode
 @Input				void
 @Return				idlemode
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_IdleMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_IDLEMODE_OFFSET);
}

/**********************************************************************************************************
 @Function			void  TCFG_EEPROM_Set_ActiveMode(u8 active)
 @Description			TCFG_EEPROM_Set_ActiveMode					: 保存ActiveMode
 @Input				active
 @Return				void
**********************************************************************************************************/
void  TCFG_EEPROM_Set_ActiveMode(u8 active)
{
	FLASH_EEPROM_WriteByte(TCFG_ACTIVEMODE_OFFSET, active);
}

/**********************************************************************************************************
 @Function			u8    TCFG_EEPROM_Get_ActiveMode(void)
 @Description			TCFG_EEPROM_Get_ActiveMode					: 读取ActiveMode
 @Input				void
 @Return				active
**********************************************************************************************************/
u8    TCFG_EEPROM_Get_ActiveMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_ACTIVEMODE_OFFSET);
}









































/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_BootVersion(u8 bootVer)
 @Description			TCFG_Utility_Set_BootVersion					: 设置BootVersion
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_BootVersion(u8 bootVer)
{
	TCFG_SystemData.BootVersion = bootVer;
	TCFG_EEPROM_Set_BootVersion(TCFG_SystemData.BootVersion);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_BootMode(u8 bootMode)
 @Description			TCFG_Utility_Set_BootMode					: 设置BootMode
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_BootMode(u8 bootMode)
{
	TCFG_SystemData.BootRunmode = bootMode;
	TCFG_EEPROM_Set_BootMode(TCFG_SystemData.BootRunmode);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_BootCount(u8 bootCount)
 @Description			TCFG_Utility_Set_BootCount					: 设置BootCount
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_BootCount(u8 bootCount)
{
	TCFG_SystemData.BootRecount = bootCount;
	TCFG_EEPROM_Set_BootCount(TCFG_SystemData.BootRecount);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_RadioChannel(u8 channel)
 @Description			TCFG_Utility_Set_RadioChannel					: 设置RadioChannel
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_RadioChannel(u8 channel)
{
	TCFG_SystemData.RadioChannel = channel;
	if ((TCFG_SystemData.RadioChannel != 36) && (TCFG_SystemData.RadioChannel != 4) && (TCFG_SystemData.RadioChannel != 6) && (TCFG_SystemData.RadioChannel != 16) && (TCFG_SystemData.RadioChannel != 26)) {
		TCFG_SystemData.RadioChannel = RADIO_RF_CHANNEL1;
	}
	TCFG_EEPROM_Set_RadioChannel(TCFG_SystemData.RadioChannel);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_RadioHeartval(u8 heartval)
 @Description			TCFG_Utility_Set_RadioHeartval				: 设置RadioHeartval
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_RadioHeartval(u8 heartval)
{
	TCFG_SystemData.RadioHeartval = heartval;
	if ((TCFG_SystemData.RadioHeartval < 1) || (TCFG_SystemData.RadioHeartval > 120)) {
		TCFG_SystemData.RadioHeartval = RADIO_RF_HEARTVAL;
	}
	TCFG_EEPROM_Set_RadioHeartval(TCFG_SystemData.RadioHeartval);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_DeviceRebootMode(u8 rebootmode)
 @Description			TCFG_Utility_Set_DeviceRebootMode				: 设置DeviceRebootMode
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_DeviceRebootMode(u8 rebootmode)
{
	TCFG_SystemData.DevRebootMode = rebootmode;
	TCFG_EEPROM_Set_DeviceRebootMode(TCFG_SystemData.DevRebootMode);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_Sensitivity(u8 sens)
 @Description			TCFG_Utility_Set_Sensitivity					: 设置Sensitivity
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_Sensitivity(u8 sens)
{
	TCFG_SystemData.Sensitivity = sens;
	if ((TCFG_SystemData.Sensitivity < SENSE_HIGHEST) || (TCFG_SystemData.Sensitivity > SENSE_LOWEST)) {
		TCFG_SystemData.Sensitivity = SENSE_MIDDLE;
	}
	TCFG_EEPROM_Set_Sensitivity(TCFG_SystemData.Sensitivity);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_WorkMode(u8 workmode)
 @Description			TCFG_Utility_Set_WorkMode					: 设置WorkMode
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_WorkMode(u8 workmode)
{
	TCFG_SystemData.WorkMode = workmode;
	if ((TCFG_SystemData.WorkMode != WORK_MODE_NORMAL) && (TCFG_SystemData.WorkMode != WORK_MODE_DEBUG)) {
		TCFG_SystemData.WorkMode = WORK_MODE_NORMAL;
	}
	TCFG_EEPROM_Set_WorkMode(TCFG_SystemData.WorkMode);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_IdleMode(u8 idlemode)
 @Description			TCFG_Utility_Set_IdleMode					: 设置IdleMode
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_IdleMode(u8 idlemode)
{
	TCFG_SystemData.IdleMode = idlemode;
	if ((TCFG_SystemData.IdleMode != IDLE_MODE_DISABLE) && (TCFG_SystemData.IdleMode != IDLE_MODE_ENABLE)) {
		TCFG_SystemData.IdleMode = IDLE_MODE_DISABLE;
	}
	TCFG_EEPROM_Set_IdleMode(TCFG_SystemData.IdleMode);
}

/**********************************************************************************************************
 @Function			void  TCFG_Utility_Set_ActiveMode(u8 activemode)
 @Description			TCFG_Utility_Set_ActiveMode					: 设置ActiveMode
 @Input				val
 @Return				void
**********************************************************************************************************/
void  TCFG_Utility_Set_ActiveMode(u8 activemode)
{
	TCFG_SystemData.ActiveMode = activemode;
	if ((TCFG_SystemData.ActiveMode != ACTIVE_MODE_DISABLE) && (TCFG_SystemData.ActiveMode != ACTIVE_MODE_ENABLE)) {
		TCFG_SystemData.ActiveMode = ACTIVE_MODE_ENABLE;
	}
	TCFG_EEPROM_Set_ActiveMode(TCFG_SystemData.ActiveMode);
}






































/**********************************************************************************************************
 @Function			u32   TCFG_Utility_Get_Factory_MacSN(void)
 @Description			TCFG_Utility_Get_Factory_MacSN				: 读取Factory MacSN
 @Input				void
 @Return				val
**********************************************************************************************************/
u32   TCFG_Utility_Get_Factory_MacSN(void)
{
	return TCFG_SystemData.MacSN;
}

/**********************************************************************************************************
 @Function			u32   TCFG_Utility_Get_Factory_Vender(void)
 @Description			TCFG_Utility_Get_Factory_Vender				: 读取Factory Vender
 @Input				void
 @Return				val
**********************************************************************************************************/
u32   TCFG_Utility_Get_Factory_Vender(void)
{
	return TCFG_SystemData.Vender;
}

/**********************************************************************************************************
 @Function			char* TCFG_Utility_Get_Factory_MacSN_String(void)
 @Description			TCFG_Utility_Get_Factory_MacSN_String			: 读取Factory MacSN字符串
 @Input				void
 @Return				sn_string
**********************************************************************************************************/
char* TCFG_Utility_Get_Factory_MacSN_String(void)
{
	return (char *)TCFG_SystemData.FactoryMacsn;
}

/**********************************************************************************************************
 @Function			char* TCFG_Utility_Get_Factory_Vender_String(void)
 @Description			TCFG_Utility_Get_Factory_Vender_String			: 读取Factory Vender字符串
 @Input				void
 @Return				vender_string
**********************************************************************************************************/
char* TCFG_Utility_Get_Factory_Vender_String(void)
{
	return (char *)TCFG_SystemData.FactoryVender;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_BootVersion(void)
 @Description			TCFG_Utility_Get_BootVersion					: 读取BootVersion
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_BootVersion(void)
{
	return TCFG_SystemData.BootVersion;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_BootMode(void)
 @Description			TCFG_Utility_Get_BootMode					: 读取BootMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_BootMode(void)
{
	return TCFG_SystemData.BootRunmode;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_BootCount(void)
 @Description			TCFG_Utility_Get_BootCount					: 读取BootCount
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_BootCount(void)
{
	return TCFG_SystemData.BootRecount;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_RadioChannel(void)
 @Description			TCFG_Utility_Get_RadioChannel					: 读取RadioChannel
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_RadioChannel(void)
{
	return TCFG_SystemData.RadioChannel;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_RadioHeartval(void)
 @Description			TCFG_Utility_Get_RadioHeartval				: 读取RadioHeartval
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_RadioHeartval(void)
{
	return TCFG_SystemData.RadioHeartval;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_DeviceRebootMode(void)
 @Description			TCFG_Utility_Get_DeviceRebootMode				: 读取DeviceRebootMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_DeviceRebootMode(void)
{
	return TCFG_SystemData.DevRebootMode;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_Sensitivity(void)
 @Description			TCFG_Utility_Get_Sensitivity					: 读取Sensitivity
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_Sensitivity(void)
{
	return TCFG_SystemData.Sensitivity;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_WorkMode(void)
 @Description			TCFG_Utility_Get_WorkMode					: 读取WorkMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_WorkMode(void)
{
	return TCFG_SystemData.WorkMode;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_IdleMode(void)
 @Description			TCFG_Utility_Get_IdleMode					: 读取IdleMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_IdleMode(void)
{
	return TCFG_SystemData.IdleMode;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_ActiveMode(void)
 @Description			TCFG_Utility_Get_ActiveMode					: 读取ActiveMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_ActiveMode(void)
{
	return TCFG_SystemData.ActiveMode;
}












































































/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_DeviceMode(void)
 @Description			TCFG_Utility_Get_DeviceMode					: 读取DeviceMode
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_DeviceMode(void)
{
	if (TCFG_Utility_Get_IdleMode() == IDLE_MODE_ENABLE) {
		return WORK_MODE_IDLE;
	}
	else if (TCFG_Utility_Get_ActiveMode() != ACTIVE_MODE_ENABLE) {
		return WORK_MODE_STANDBY;
	}
	else if (Radio_RF_Get_Gateway_nearby() == 0) {
		return WORK_MODE_NORMAL;
	}
	else {
		return TCFG_Utility_Get_WorkMode();
	}
}

/**********************************************************************************************************
 @Function			char* TCFG_Utility_Get_DeviceModeInfo(void)
 @Description			TCFG_Utility_Get_DeviceModeInfo				: 读取DeviceModeInfo
 @Input				void
 @Return				devicemodeinfo
**********************************************************************************************************/
char* TCFG_Utility_Get_DeviceModeInfo(void)
{
	if (TCFG_Utility_Get_IdleMode() == IDLE_MODE_ENABLE) {
		memset((void *)TCFG_SystemData.DeviceModeInfo, 0x00, sizeof(TCFG_SystemData.DeviceModeInfo));
		strncpy((char *)TCFG_SystemData.DeviceModeInfo, "idle", strlen("idle"));
	}
	else if (TCFG_Utility_Get_ActiveMode() != ACTIVE_MODE_ENABLE) {
		memset((void *)TCFG_SystemData.DeviceModeInfo, 0x00, sizeof(TCFG_SystemData.DeviceModeInfo));
		strncpy((char *)TCFG_SystemData.DeviceModeInfo, "notact", strlen("notact"));
	}
	else if (TCFG_Utility_Get_WorkMode() == WORK_MODE_NORMAL) {
		memset((void *)TCFG_SystemData.DeviceModeInfo, 0x00, sizeof(TCFG_SystemData.DeviceModeInfo));
		strncpy((char *)TCFG_SystemData.DeviceModeInfo, "norm", strlen("norm"));
	}
	else if (TCFG_Utility_Get_WorkMode() == WORK_MODE_DEBUG) {
		memset((void *)TCFG_SystemData.DeviceModeInfo, 0x00, sizeof(TCFG_SystemData.DeviceModeInfo));
		strncpy((char *)TCFG_SystemData.DeviceModeInfo, "debug", strlen("debug"));
	}
	else {
		memset((void *)TCFG_SystemData.DeviceModeInfo, 0x00, sizeof(TCFG_SystemData.DeviceModeInfo));
		strncpy((char *)TCFG_SystemData.DeviceModeInfo, "unknown", strlen("unknown"));
	}
	
	return (char *)TCFG_SystemData.DeviceModeInfo;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_Major_SoftwareNumber(void)
 @Description			TCFG_Utility_Get_Major_SoftwareNumber			: 读取Major Software Number
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_Major_SoftwareNumber(void)
{
	return MVB_APPL_SOFTWARE_MAJOR;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_Minor_SoftwareNumber(void)
 @Description			TCFG_Utility_Get_Minor_SoftwareNumber			: 读取Minor Software Number
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_Minor_SoftwareNumber(void)
{
	return MVB_APPL_SOFTWARE_MINOR;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_Minor_HardwareNumber(void)
 @Description			TCFG_Utility_Get_Minor_HardwareNumber			: 读取Minor Hardware Number
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_Minor_HardwareNumber(void)
{
	return MVB_APPL_HARDWARE_V2;
}

/**********************************************************************************************************
 @Function			u8    TCFG_Utility_Get_DeviceType(void)
 @Description			TCFG_Utility_Get_DeviceType					: 读取Device Type
 @Input				void
 @Return				val
**********************************************************************************************************/
u8    TCFG_Utility_Get_DeviceType(void)
{
	return MVB_MODEL_TYPE;
}

































/********************************************** END OF FLEE **********************************************/
