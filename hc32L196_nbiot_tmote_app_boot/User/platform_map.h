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

/*****************************************************************************************************************************************************/

void TCFG_EEPROM_Set_MAC_SN(u32 macSN);																				// 保存MAC_SN
u32  TCFG_EEPROM_Get_MAC_SN(void);																					// 读取MAC_SN

void TCFG_EEPROM_Set_Vender(char* vender);																			// 保存Vender
void TCFG_EEPROM_Get_Vender(char* vender);																			// 读取Vender

void TCFG_EEPROM_Set_BootVersion(u8 bootVer);																		// 保存BootVersion
u8   TCFG_EEPROM_Get_BootVersion(void);																				// 读取BootVersion

void TCFG_EEPROM_Set_BootMode(u8 bootMode);																			// 保存BootMode
u8   TCFG_EEPROM_Get_BootMode(void);																				// 读取BootMode

void TCFG_EEPROM_Set_BootCount(u8 bootCount);																		// 保存BootCount
u8   TCFG_EEPROM_Get_BootCount(void);																				// 读取BootCount

#endif /* __PLATFORM_MAP_H */
