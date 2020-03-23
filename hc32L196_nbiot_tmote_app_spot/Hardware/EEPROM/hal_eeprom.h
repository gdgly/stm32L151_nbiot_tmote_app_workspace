#ifndef __HAL_EEPROM_H
#define   __HAL_EEPROM_H

#include "sys.h"
#include "hal_bl24cxxp.h"

#define EEPROM_BASE_ADDR			0x00000000
#define EEPROM_BYTE_SIZE			0x00000100

#define EEPROM_DUPLICATION_COUNT	5

void FLASH_EEPROM_Init(void);
u8   FLASH_EEPROM_Status(void);

u8   FLASH_EEPROM_ReadByte(u32 addr);
u16  FLASH_EEPROM_ReadHalfWord(u32 addr);
u32  FLASH_EEPROM_ReadWord(u32 addr);

u8   FLASH_EEPROM_WriteByte(u32 addr, u8 data);
u16  FLASH_EEPROM_WriteHalfWord(u32 addr, u16 data);
u32  FLASH_EEPROM_WriteWord(u32 addr, u32 data);

u8   FLASH_EEPROM_ReadBuffer(u32 addr, u8* buf, u16 len);
u8   FLASH_EEPROM_WriteBuffer(u32 addr, u8* buf, u16 len);

#endif /* __HAL_EEPROM_H */
