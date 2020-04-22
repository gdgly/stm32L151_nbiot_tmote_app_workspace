#ifndef __RADIO_COMMAND_H
#define   __RADIO_COMMAND_H

#include "sys.h"

void Radio_Command_Upgrade(void);															//配置器升级命令

void Radio_Command_Sensitivity(u8 sens);													//传感器灵敏度配置指令

void Radio_Command_WorkMode(u8 workmode);													//工作模式配置指令

void Radio_Command_Heartval(u16 hearttime);													//无线心跳间隔时间配置指令

void Radio_Command_InitBackground(void);													//初始化传感器指令

void Radio_Command_Reboot(void);															//Reboot






















void Radio_Command_NotSupport(void);														//Not Support




#endif /* __RADIO_COMMAND_H */
