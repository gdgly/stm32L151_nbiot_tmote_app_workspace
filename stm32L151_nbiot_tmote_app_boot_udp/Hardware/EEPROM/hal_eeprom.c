/**
  *********************************************************************************************************
  * @file    hal_eeprom.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-11-01
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "hal_eeprom.h"


/**********************************************************************************************************
 @Function			void EEPROM_ReadBytes(u16 addr, u8 *buf, u16 length)
 @Description			从EEPROM中读出length字节数据(偏移地址需按4字节对齐)
 @Input				void
 @Return				addr   : 读出数据EEPROM偏移地址
					*buf   : 待读出数据地址
					length : 读出字节数
**********************************************************************************************************/
void EEPROM_ReadBytes(u16 addr, u8 *buf, u16 length)
{
	u8 *wAddr;
	
	wAddr = (u8 *)(EEPROM_BASE_ADDR + addr);
	while (length--) {
		*buf++ = *wAddr++;
	}
}

/**********************************************************************************************************
 @Function			void EEPROM_WriteBytes(u16 addr, u8 *buf, u16 length)
 @Description			写入EEPROM中length字节数据(偏移地址需按4字节对齐)
 @Input				void
 @Return				addr   : 写入数据EEPROM偏移地址
					*buf   : 待写入数据地址
					length : 写入字节数
**********************************************************************************************************/
void EEPROM_WriteBytes(u16 addr, u8 *buf, u16 length)
{
	u16 i = 0;
	
	EEPROM_ENTER_CRITICAL_SECTION();

	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	for (i = 0; i < length; i++) {
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, EEPROM_BASE_ADDR + addr + i, *(buf + i));
	}
	HAL_FLASHEx_DATAEEPROM_Lock();
	
	EEPROM_EXIT_CRITICAL_SECTION();
}

/**********************************************************************************************************
 @Function			void EEPROM_EnterCriticalSection(void)
 @Description			进入关键操作,关闭中断,等待中断结束返回
 @Input				void
 @Return				void
**********************************************************************************************************/
void EEPROM_EnterCriticalSection(void)
{
	__disable_irq();
}

/**********************************************************************************************************
 @Function			void EEPROM_ExitCriticalSection(void)
 @Description			退出关键操作,开启中断
 @Input				void
 @Return				void
**********************************************************************************************************/
void EEPROM_ExitCriticalSection(void)
{
	__enable_irq();
}

/********************************************** END OF FLEE **********************************************/
