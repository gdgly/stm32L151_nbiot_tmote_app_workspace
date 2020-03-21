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

#include "platform_config.h"
#include "platform_map.h"
#include "delay.h"
#include "usart.h"
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



























































/**********************************************************************************************************
 @Function			void TCFG_EEPROM_Set_MAC_SN(u32 macSN)
 @Description			TCFG_EEPROM_Set_MAC_SN						: 保存MAC-SN
 @Input				macSN
 @Return				void
**********************************************************************************************************/
void TCFG_EEPROM_Set_MAC_SN(u32 macSN)
{
	FLASH_EEPROM_WriteWord(TCFG_FACTORY_MAC_SN_OFFSET, macSN);
}

/**********************************************************************************************************
 @Function			u32  TCFG_EEPROM_Get_MAC_SN(void)
 @Description			TCFG_EEPROM_Get_MAC_SN						: 读取MAC-SN
 @Input				void
 @Return				macSN
**********************************************************************************************************/
u32  TCFG_EEPROM_Get_MAC_SN(void)
{
	return FLASH_EEPROM_ReadWord(TCFG_FACTORY_MAC_SN_OFFSET);
}

/**********************************************************************************************************
 @Function			void TCFG_EEPROM_Set_Vender(char* vender)
 @Description			TCFG_EEPROM_Set_Vender						: 保存Vender
 @Input				vender
 @Return				void
**********************************************************************************************************/
void TCFG_EEPROM_Set_Vender(char* vender)
{
	FLASH_EEPROM_WriteBuffer(TCFG_FACTORY_VENDER_OFFSET, (u8*)vender, TCFG_FACTORY_VENDER_LENGTH);
}

/**********************************************************************************************************
 @Function			void TCFG_EEPROM_Set_Vender(char* vender)
 @Description			TCFG_EEPROM_Set_Vender						: 读取Vender
 @Input				vender
 @Return				void
**********************************************************************************************************/
void TCFG_EEPROM_Get_Vender(char* vender)
{
	FLASH_EEPROM_ReadBuffer(TCFG_FACTORY_VENDER_OFFSET, (u8*)vender, TCFG_FACTORY_VENDER_LENGTH);
}

/**********************************************************************************************************
 @Function			void TCFG_EEPROM_Set_BootVersion(u8 bootVer)
 @Description			TCFG_EEPROM_Set_BootVersion					: 保存BootVersion
 @Input				bootVer
 @Return				void
**********************************************************************************************************/
void TCFG_EEPROM_Set_BootVersion(u8 bootVer)
{
	FLASH_EEPROM_WriteByte(TCFG_BOOT_VERSION_OFFSET, bootVer);
}

/**********************************************************************************************************
 @Function			u8   TCFG_EEPROM_Get_BootVersion(void)
 @Description			TCFG_EEPROM_Get_BootVersion					: 读取BootVersion
 @Input				void
 @Return				bootVer
**********************************************************************************************************/
u8   TCFG_EEPROM_Get_BootVersion(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_BOOT_VERSION_OFFSET);
}

/**********************************************************************************************************
 @Function			void TCFG_EEPROM_Set_BootMode(u8 bootVer)
 @Description			TCFG_EEPROM_Set_BootMode						: 保存BootMode
 @Input				bootMode
 @Return				void
**********************************************************************************************************/
void TCFG_EEPROM_Set_BootMode(u8 bootMode)
{
	FLASH_EEPROM_WriteByte(TCFG_BOOT_RUNMODE_OFFSET, bootMode);
}

/**********************************************************************************************************
 @Function			u8   TCFG_EEPROM_Get_BootMode(void)
 @Description			TCFG_EEPROM_Get_BootMode						: 读取BootMode
 @Input				void
 @Return				bootMode
**********************************************************************************************************/
u8   TCFG_EEPROM_Get_BootMode(void)
{
	return FLASH_EEPROM_ReadByte(TCFG_BOOT_RUNMODE_OFFSET);
}














































/********************************************** END OF FLEE **********************************************/
