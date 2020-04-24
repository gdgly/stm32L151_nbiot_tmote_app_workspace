#ifndef __PLATFORM_MAP_H
#define   __PLATFORM_MAP_H

#include "sys.h"





#define APP_LOWEST_ADDRESS						0x00007800														// APP 基地址
#define APP_LOWEST_SIZE							0x00038800														// APP 空间大小




#define TCFG_ENV_BOOTMODE_TOUPDATE					1
#define TCFG_ENV_BOOTMODE_NORMALLY					2
#define TCFG_ENV_BOOTMODE_UPDATING					3
#define TCFG_ENV_BOOTMODE_REUPDATE					4






/*****************************************************************************************************************************************************/

#define TCFG_EEPROM_BASE_ADDR						0x00000000														// EEPROM基地址
#define TCFG_EEPROM_BYTE_SIZE						0x00000100														// EEPROM总大小

#define TCFG_FACTORY_MAC_SN_OFFSET					TCFG_EEPROM_BYTE_SIZE - 4 - 1											// 0x000000FB
#define TCFG_FACTORY_MAC_SN_LENGTH					4																// SN

#define TCFG_FACTORY_VENDER_OFFSET					TCFG_EEPROM_BYTE_SIZE - 8 - 1											// 0x000000F7
#define TCFG_FACTORY_VENDER_LENGTH					4																// Vender

/****************************************************** Environment Variable *************************************************************************/
#define TCFG_EEPROM_CONFIG_PAGE1_ADDR				TCFG_EEPROM_BASE_ADDR												// 配置页1起始地址		(0x00000000)
#define TCFG_EEPROM_CONFIG_PAGE1_SIZE				0x00000080														// 配置页1大小			(128Byte)

#define TCFG_BOOT_VERSION_OFFSET					TCFG_EEPROM_CONFIG_PAGE1_ADDR											// 0x00000000
#define TCFG_BOOT_VERSION_LENGTH					1																// BootVersion			BOOT版本号
#define TCFG_BOOT_RUNMODE_OFFSET					TCFG_BOOT_VERSION_OFFSET + TCFG_BOOT_VERSION_LENGTH						// 0x00000001
#define TCFG_BOOT_RUNMODE_LENGTH					1																// BootRunMode			BOOT运行模式
#define TCFG_BOOT_RECOUNT_OFFSET					TCFG_BOOT_RUNMODE_OFFSET + TCFG_BOOT_RUNMODE_LENGTH						// 0x00000002
#define TCFG_BOOT_RECOUNT_LENGTH					1																// BootCount			BOOT重启次数

#define TCFG_FACTORYBACKUP_MAC_SN_OFFSET			TCFG_BOOT_RECOUNT_OFFSET + TCFG_BOOT_RECOUNT_LENGTH						// 0x00000003
#define TCFG_FACTORYBACKUP_MAC_SN_LENGTH			4																// SN BackUp			SN备份比对
#define TCFG_FACTORYBACKUP_VENDER_OFFSET			TCFG_FACTORYBACKUP_MAC_SN_OFFSET + TCFG_FACTORYBACKUP_MAC_SN_LENGTH			// 0x00000007
#define TCFG_FACTORYBACKUP_VENDER_LENGTH			4																// Vender BackUp		VD备份比对

#define TCFG_SOFTWAREBACKUP_MAJOR_OFFSET			TCFG_FACTORYBACKUP_VENDER_OFFSET + TCFG_FACTORYBACKUP_VENDER_LENGTH			// 0x0000000B
#define TCFG_SOFTWAREBACKUP_MAJOR_LENGTH			1																// SoftwareMajor BackUp	SoftwareMajor备份比对
#define TCFG_SOFTWAREBACKUP_MINOR_OFFSET			TCFG_SOFTWAREBACKUP_MAJOR_OFFSET + TCFG_SOFTWAREBACKUP_MAJOR_LENGTH			// 0x0000000C
#define TCFG_SOFTWAREBACKUP_MINOR_LENGTH			1																// SoftwareMinor BackUp	SoftwareMinor备份比对

#define TCFG_RADIO_CHANNEL_OFFSET					TCFG_SOFTWAREBACKUP_MINOR_OFFSET + TCFG_SOFTWAREBACKUP_MINOR_LENGTH			// 0x0000000D
#define TCFG_RADIO_CHANNEL_LENGTH					1																// Radio Channel		Radio RF 通道
#define TCFG_RADIO_HEARTVL_OFFSET					TCFG_RADIO_CHANNEL_OFFSET + TCFG_RADIO_CHANNEL_LENGTH						// 0x0000000E
#define TCFG_RADIO_HEARTVL_LENGTH					1																// Radio Heartval		Radio RF 心跳

#define TCFG_DEVICE_RBTMODE_OFFSET					TCFG_RADIO_HEARTVL_OFFSET + TCFG_RADIO_HEARTVL_LENGTH						// 0x0000000F
#define TCFG_DEVICE_RBTMODE_LENGTH					1																// Device Reboot Mode	设备重启方式

#define TCFG_SENSITIVITY_OFFSET					TCFG_DEVICE_RBTMODE_OFFSET + TCFG_DEVICE_RBTMODE_LENGTH					// 0x00000010
#define TCFG_SENSITIVITY_LENGTH					1																// Sensitivity			传感器灵敏度

#define TCFG_WORKMODE_OFFSET						TCFG_SENSITIVITY_OFFSET + TCFG_SENSITIVITY_LENGTH							// 0x00000011
#define TCFG_WORKMODE_LENGTH						1																// WorkMode			工作模式
#define TCFG_IDLEMODE_OFFSET						TCFG_WORKMODE_OFFSET + TCFG_WORKMODE_LENGTH								// 0x00000012
#define TCFG_IDLEMODE_LENGTH						1																// IdleMode			休眠模式
#define TCFG_ACTIVEMODE_OFFSET					TCFG_IDLEMODE_OFFSET + TCFG_IDLEMODE_LENGTH								// 0x00000013
#define TCFG_ACTIVEMODE_LENGTH					1																// ActiveMode			运行模式

#define TCFG_RF_DPRINT_LEVEL_OFFSET				TCFG_ACTIVEMODE_OFFSET + TCFG_ACTIVEMODE_LENGTH							// 0x00000014
#define TCFG_RF_DPRINT_LEVEL_LENGTH				1																// RFDPrintfLevel		调试信息输出等级


























/*****************************************************************************************************************************************************/








typedef struct
{
	u8		FactoryMacsn[9];
	u8		FactoryVender[4];
	u32		MacSN;
	u32		Vender;
	u8		BootVersion;
	u8		BootRunmode;
	u8		BootRecount;
	u8		RadioChannel;
	u8		RadioHeartval;
	u8		DevRebootMode;
	u8		Sensitivity;
	u8		WorkMode;
	u8		IdleMode;
	u8		ActiveMode;
	u8		DeviceMode;
	u8		DeviceModeInfo[8];
	u8		RFDPrintfLevel;
	
	
	
	
	
	
	
	
	
	
	
	
} TCFG_SystemDataTypeDef;

extern TCFG_SystemDataTypeDef TCFG_SystemData;












void  TCFG_EEPROM_SystemConfigInfo_Init(void);																		// 系统配置信息初始化

void  TCFG_EEPROM_WriteSystemConfigData(void);																		// 写入系统配置信息
void  TCFG_EEPROM_WriteSystemParamtData(void);																		// 写入系统参数信息
void  TCFG_EEPROM_ReadSystemConfigData(void);																		// 读取系统配置信息

void  TCFG_EEPROM_SystemConfigInfo_Restore(void);																		// 恢复出厂配置信息
























/********************** Check if the SN & Vender and the Backup space are the same ***********************/
bool  TCFG_EEPROM_CheckNewSerialInfomation(void);																		// 检测新的设备厂牌信息

u32   TCFG_EEPROM_Get_Source_MAC_SN(void);
u32   TCFG_EEPROM_Get_Source_Vender(void);

void  TCFG_EEPROM_Set_Backup_MAC_SN(u32 val);
u32   TCFG_EEPROM_Get_Backup_MAC_SN(void);
void  TCFG_EEPROM_Set_Backup_Vender(u32 val);
u32   TCFG_EEPROM_Get_Backup_Vender(void);
/*********************************************************************************************************/

/********************** Check if the SoftwareVer and the Backup space are the same ***********************/
bool  TCFG_EEPROM_CheckNewSoftwareEditions(void);																		// 检测新的固件版本信息

u8    TCFG_EEPROM_Get_Source_SoftwareMajor(void);
u8    TCFG_EEPROM_Get_Source_SoftwareMinor(void);

void  TCFG_EEPROM_Set_Backup_SoftwareMajor(u8 val);
u8    TCFG_EEPROM_Get_Backup_SoftwareMajor(void);
void  TCFG_EEPROM_Set_Backup_SoftwareMinor(u8 val);
u8    TCFG_EEPROM_Get_Backup_SoftwareMinor(void);
/*********************************************************************************************************/

void  TCFG_EEPROM_Set_MAC_SN(u32 sn);																				// 保存MAC_SN
u32   TCFG_EEPROM_Get_MAC_SN(void);																				// 读取MAC_SN
char* TCFG_EEPROM_Get_MAC_SN_String(void);																			// 读取MAC SN字符串

void  TCFG_EEPROM_Set_Vender(char* vender);																			// 保存Vender
void  TCFG_EEPROM_Get_Vender(char* vender);																			// 读取Vender
char* TCFG_EEPROM_Get_Vender_String(void);																			// 读取vender字符串


















void  TCFG_EEPROM_Set_BootVersion(u8 bootVer);																		// 保存BootVersion
u8    TCFG_EEPROM_Get_BootVersion(void);																			// 读取BootVersion

void  TCFG_EEPROM_Set_BootMode(u8 bootMode);																			// 保存BootMode
u8    TCFG_EEPROM_Get_BootMode(void);																				// 读取BootMode

void  TCFG_EEPROM_Set_BootCount(u8 bootCount);																		// 保存BootCount
u8    TCFG_EEPROM_Get_BootCount(void);																				// 读取BootCount

void  TCFG_EEPROM_Set_RadioChannel(u8 channel);																		// 保存RadioChannel
u8    TCFG_EEPROM_Get_RadioChannel(void);																			// 读取RadioChannel

void  TCFG_EEPROM_Set_RadioHeartval(u8 heartval);																		// 保存RadioHeartval
u8    TCFG_EEPROM_Get_RadioHeartval(void);																			// 读取RadioHeartval

void  TCFG_EEPROM_Set_DeviceRebootMode(u8 rebootmode);																	// 保存DeviceRebootMode
u8    TCFG_EEPROM_Get_DeviceRebootMode(void);																		// 读取DeviceRebootMode

void  TCFG_EEPROM_Set_Sensitivity(u8 sens);																			// 保存Sensitivity
u8    TCFG_EEPROM_Get_Sensitivity(void);																			// 读取Sensitivity

void  TCFG_EEPROM_Set_WorkMode(u8 workmode);																			// 保存WorkMode
u8    TCFG_EEPROM_Get_WorkMode(void);																				// 读取WorkMode

void  TCFG_EEPROM_Set_IdleMode(u8 idlemode);																			// 保存IdleMode
u8    TCFG_EEPROM_Get_IdleMode(void);																				// 读取IdleMode

void  TCFG_EEPROM_Set_ActiveMode(u8 active);																			// 保存ActiveMode
u8    TCFG_EEPROM_Get_ActiveMode(void);																				// 读取ActiveMode

void  TCFG_EEPROM_Set_RFDPrintfLevel(u8 level);																		// 保存RFDPrintfLevel
u8    TCFG_EEPROM_Get_RFDPrintfLevel(void);																			// 读取RFDPrintfLevel



































/*****************************************************************************************************************************************************/

void  TCFG_Utility_Set_Factory_MacSN(u32 sn);																		// 设置Factory MacSN
void  TCFG_Utility_Set_Factory_Vender(u32 vender);																	// 设置Factory Vender

void  TCFG_Utility_Set_BootVersion(u8 bootVer);																		// 设置BootVersion
void  TCFG_Utility_Set_BootMode(u8 bootMode);																		// 设置BootMode
void  TCFG_Utility_Set_BootCount(u8 bootCount);																		// 设置BootCount

void  TCFG_Utility_Set_RadioChannel(u8 channel);																		// 设置RadioChannel
void  TCFG_Utility_Set_RadioHeartval(u8 heartval);																	// 设置RadioHeartval

void  TCFG_Utility_Set_DeviceRebootMode(u8 rebootmode);																// 设置DeviceRebootMode

void  TCFG_Utility_Set_Sensitivity(u8 sens);																			// 设置Sensitivity

void  TCFG_Utility_Set_WorkMode(u8 workmode);																		// 设置WorkMode
void  TCFG_Utility_Set_IdleMode(u8 idlemode);																		// 设置IdleMode
void  TCFG_Utility_Set_ActiveMode(u8 activemode);																		// 设置ActiveMode

void  TCFG_Utility_Set_RFDPrintfLevel(u8 level);																		// 设置RFDPrintfLevel






















/*****************************************************************************************************************************************************/

/*****************************************************************************************************************************************************/

u32   TCFG_Utility_Get_Factory_MacSN(void);																			// 读取Factory MacSN
u32   TCFG_Utility_Get_Factory_Vender(void);																			// 读取Factory Vender
char* TCFG_Utility_Get_Factory_MacSN_String(void);																	// 读取Factory MacSN字符串
char* TCFG_Utility_Get_Factory_Vender_String(void);																	// 读取Factory Vender字符串

u8    TCFG_Utility_Get_BootVersion(void);																			// 读取BootVersion
u8    TCFG_Utility_Get_BootMode(void);																				// 读取BootMode
u8    TCFG_Utility_Get_BootCount(void);																				// 读取BootCount

u8    TCFG_Utility_Get_RadioChannel(void);																			// 读取RadioChannel
u8    TCFG_Utility_Get_RadioHeartval(void);																			// 读取RadioHeartval

u8    TCFG_Utility_Get_DeviceRebootMode(void);																		// 读取DeviceRebootMode

u8    TCFG_Utility_Get_Sensitivity(void);																			// 读取Sensitivity

u8    TCFG_Utility_Get_WorkMode(void);																				// 读取WorkMode
u8    TCFG_Utility_Get_IdleMode(void);																				// 读取IdleMode
u8    TCFG_Utility_Get_ActiveMode(void);																			// 读取ActiveMode

u8    TCFG_Utility_Get_RFDPrintfLevel(void);																			// 读取RFDPrintfLevel






















u8    TCFG_Utility_Get_DeviceMode(void);																			// 读取DeviceMode
char* TCFG_Utility_Get_DeviceModeInfo(void);																			// 读取DeviceModeInfo

u8    TCFG_Utility_Get_Major_SoftwareNumber(void);																	// 读取Major Software Number
u8    TCFG_Utility_Get_Minor_SoftwareNumber(void);																	// 读取Minor Software Number
u8    TCFG_Utility_Get_Minor_HardwareNumber(void);																	// 读取Minor Hardware Number

u8    TCFG_Utility_Get_DeviceType(void);																			// 读取Device Type
u8    TCFG_Utility_Get_DeviceResetFlag(void);																		// 读取Device Reset Flag

/*****************************************************************************************************************************************************/







#endif /* __PLATFORM_MAP_H */
