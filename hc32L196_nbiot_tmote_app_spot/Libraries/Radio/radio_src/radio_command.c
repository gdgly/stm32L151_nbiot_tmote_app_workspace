/**
  *********************************************************************************************************
  * @file    radio_command.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-21
  * @brief   
  *********************************************************************************************************
  * @attention
  *
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
#include "hal_ist8310m.h"
#include "hal_spi.h"
#include "hal_p25qxxh.h"
#include "hal_norflash.h"
#include "hal_attitude.h"
#include "hal_products.h"
#include "hal_base_tim0.h"
#include "hal_base_tim1.h"
#include "hal_base_tim2.h"
#include "fifo.h"
#include "message.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
#include "radio_command.h"
#include "tmesh_xtea.h"

#define RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
#define RADIO_COMMAND_DEBUG_LOG_PRINTF		Radio_RF_Trf_Printf

/**********************************************************************************************************
 @Function			void Radio_Command_Upgrade(void)
 @Description			Radio_Command_Upgrade						: 配置器升级命令
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Command_Upgrade(void)
{
	TCFG_Utility_Set_BootMode(TCFG_ENV_BOOTMODE_TOUPDATE);
	Radio_RF_Xmit_Default_Resp(100, TRF_MSG_UPGRADE);
	HC32_BEEP_Repeat(5, 35, 25);
	HC32_System_Software_Reboot(REBOOT_MODE_UPGRADE_RADIO);
}

/**********************************************************************************************************
 @Function			void Radio_Command_Sensitivity(u8 sens)
 @Description			Radio_Command_Sensitivity					: 传感器灵敏度配置指令
 @Input				sens
 @Return				void
**********************************************************************************************************/
void Radio_Command_Sensitivity(u8 sens)
{
	TCFG_Utility_Set_Sensitivity(sens);
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] Sensitivity: %d", TCFG_Utility_Get_Sensitivity());
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_WorkMode(u8 workmode)
 @Description			Radio_Command_WorkMode						: 工作模式配置指令
 @Input				workmode
 @Return				void
**********************************************************************************************************/
void Radio_Command_WorkMode(u8 workmode)
{
	TCFG_Utility_Set_WorkMode(workmode);
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] WorkMode: %d", TCFG_Utility_Get_WorkMode());
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_Heartval(u16 hearttime)
 @Description			Radio_Command_Heartval						: 无线心跳间隔时间配置指令
 @Input				hearttime
 @Return				void
**********************************************************************************************************/
void Radio_Command_Heartval(u16 hearttime)
{
	TCFG_Utility_Set_RadioHeartval(hearttime);
	Radio_Hal_RF_Set_Heartval(TCFG_Utility_Get_RadioHeartval());
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] HeartInterval: %d", TCFG_Utility_Get_RadioHeartval());
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_InitBackground(void)
 @Description			Radio_Command_InitBackground					: 初始化传感器指令
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Command_InitBackground(void)
{
	
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] InitSensorBackground");
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_Reboot(void)
 @Description			Radio_Command_Reboot						: Reboot
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Command_Reboot(void)
{
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] reboot");
#endif
	
	HC32_BEEP_Repeat(1, 500, 0);
	HC32_System_Software_Reboot(REBOOT_MODE_CMD_RADIO);
}

/**********************************************************************************************************
 @Function			void Radio_Command_Restore(void)
 @Description			Radio_Command_Restore						: Restore
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Command_Restore(void)
{
	TCFG_EEPROM_SystemConfigInfo_Restore();
	HC32_BEEP_Repeat(5, 60, 25);
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] restore");
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_Newsn(u32 sn)
 @Description			Radio_Command_Newsn							: Newsn
 @Input				sn
 @Return				void
**********************************************************************************************************/
void Radio_Command_Newsn(u32 sn)
{
	TCFG_Utility_Set_Factory_MacSN(sn);
	TCFG_EEPROM_SystemConfigInfo_Restore();
	HC32_BEEP_Repeat(5, 60, 25);
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] newsn: %08x", TCFG_Utility_Get_Factory_MacSN());
#endif
}

/**********************************************************************************************************
 @Function			void Radio_Command_RFDPrintfLevel(u16 level)
 @Description			Radio_Command_RFDPrintfLevel					: RFDPrintfLevel
 @Input				sn
 @Return				void
**********************************************************************************************************/
void Radio_Command_RFDPrintfLevel(u16 level)
{
	TCFG_Utility_Set_RFDPrintfLevel(level + 1);
	
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] rfdplv: %d", TCFG_Utility_Get_RFDPrintfLevel() - 1);
#endif
}










































/**********************************************************************************************************
 @Function			void Radio_Command_NotSupport(void)
 @Description			Radio_Command_NotSupport						: Not Support
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radio_Command_NotSupport(void)
{
#ifdef RADIO_COMMAND_DEBUG_LOG_RF_PRINTF
	RADIO_COMMAND_DEBUG_LOG_PRINTF("[RadioCmd] Not Support");
#endif
}



















/********************************************** END OF FLEE **********************************************/
