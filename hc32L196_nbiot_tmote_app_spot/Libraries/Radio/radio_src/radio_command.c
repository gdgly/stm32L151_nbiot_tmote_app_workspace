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
#include "hal_spi.h"
#include "hal_p25qxxh.h"
#include "hal_norflash.h"
#include "fifo.h"
#include "message.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"
#include "radio_command.h"
#include "tmesh_xtea.h"

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
























































/********************************************** END OF FLEE **********************************************/
