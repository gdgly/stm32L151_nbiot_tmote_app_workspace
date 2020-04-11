#ifndef __HAL_CRC_H
#define   __HAL_CRC_H

#include "sys.h"
#include "crc.h"

typedef enum _crc_type
{
	crcByte					= 0U,
	crcHalfWord				= 1U,
	crcWord					= 2U,
} crc_data_type_t;

u16 HC32_CRC16_Encrypt(u8* data, u32 len, crc_data_type_t type);									// CRC16 编码
u32 HC32_CRC32_Encrypt(u8* data, u32 len, crc_data_type_t type);									// CRC32 编码

en_result_t HC32_CRC16_Check(u8* data, u32 len, u32 result, crc_data_type_t type);					// CRC16 校验
en_result_t HC32_CRC32_Check(u8* data, u32 len, u32 result, crc_data_type_t type);					// CRC32 校验

#endif /* __HAL_CRC_H */
