/****************************************Copyright (c)****************************************************
**                         SHENZHEN DECARD TECHNOLOGIES Co.,LTD.                               
**                                     
**                               http://www.decard.com
**
**--------------File Info---------------------------------------------------------------------------------
** Create by:			ck
** Create date:			2012-07-12
** Version:             0.1
** Descriptions:		bootloader³ÌÐò
*********************************************************************************************************/
#ifndef _BOOT_H_
#define _BOOT_H_
#include "stm32l1xx_hal.h"

#if 1
//#define TCFG_UPGRADE_TYPE_ADDR	0x08007800
//#define TCFG_JUMP2APP_ADDR		0x08007804
#else
#define TCFG_UPGRADE_TYPE_ADDR	0x0800f800
#define TCFG_JUMP2APP_ADDR		0x0800f804
#endif
#define TCFG_UPTYPE_SUCCESS		0xffff	
#define TCFG_UPTYPE_FAIL		0x0000

#define TCFG_JUMP2APP_TRUE		0xff
#define TCFG_JUMP2APP_FALSE		0x00


extern uint8_t JumpToApplication(uint32_t Addr);
void boot_from_flash(unsigned int app_offset);




#endif

