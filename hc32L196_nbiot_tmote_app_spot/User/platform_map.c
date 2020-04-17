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















/********************************************** END OF FLEE **********************************************/
