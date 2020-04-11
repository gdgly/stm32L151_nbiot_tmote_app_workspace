/**
  *********************************************************************************************************
  * @file    hal_crc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-28
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_crc.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			u16 HC32_CRC16_Encrypt(u8* data, u32 len, crc_data_type_t type)
 @Description			HC32_CRC16_Encrypt							: CRC16 编码
 @Input				data										: 编码数据
					len										: 编码长度
					type										: 位宽选择
 @Return				crc16
**********************************************************************************************************/
u16 HC32_CRC16_Encrypt(u8* data, u32 len, crc_data_type_t type)
{
	if (type == crcByte)
		return CRC16_Get8(data, len);
	
	if (type == crcHalfWord)
		return CRC16_Get16((u16*)data, len / 2);
	
	if (type == crcWord)
		return CRC16_Get32((u32*)data, len / 4);
	
	return 0;
}

/**********************************************************************************************************
 @Function			u32 HC32_CRC32_Encrypt(u8* data, u32 len, crc_data_type_t type)
 @Description			HC32_CRC32_Encrypt							: CRC32 编码
 @Input				data										: 编码数据
					len										: 编码长度
					type										: 位宽选择
 @Return				crc32
**********************************************************************************************************/
u32 HC32_CRC32_Encrypt(u8* data, u32 len, crc_data_type_t type)
{
	if (type == crcByte)
		return CRC32_Get8(data, len);
	
	if (type == crcHalfWord)
		return CRC32_Get16((u16*)data, len / 2);
	
	if (type == crcWord)
		return CRC32_Get32((u32*)data, len / 4);
	
	return 0;
}

/**********************************************************************************************************
 @Function			en_result_t HC32_CRC16_Check(u8* data, u32 len, u32 result, crc_data_type_t type)
 @Description			HC32_CRC16_Check							: CRC16 校验
 @Input				data										: 编码数据
					len										: 编码长度
					result									: 校验数据
					type										: 位宽选择
 @Return				en_result_t								: 校验结果
**********************************************************************************************************/
en_result_t HC32_CRC16_Check(u8* data, u32 len, u32 result, crc_data_type_t type)
{
	if (type == crcByte)
		return CRC16_Check8(data, len, result);
	
	if (type == crcHalfWord)
		return CRC16_Check16((u16*)data, len / 2, result);
	
	if (type == crcWord)
		return CRC16_Check32((u32*)data, len / 4, result);
	
	return Error;
}

/**********************************************************************************************************
 @Function			en_result_t HC32_CRC32_Check(u8* data, u32 len, u32 result, crc_data_type_t type)
 @Description			HC32_CRC32_Check							: CRC32 校验
 @Input				data										: 编码数据
					len										: 编码长度
					result									: 校验数据
					type										: 位宽选择
 @Return				en_result_t								: 校验结果
**********************************************************************************************************/
en_result_t HC32_CRC32_Check(u8* data, u32 len, u32 result, crc_data_type_t type)
{
	if (type == crcByte)
		return CRC32_Check8(data, len, result);
	
	if (type == crcHalfWord)
		return CRC32_Check16((u16*)data, len / 2, result);
	
	if (type == crcWord)
		return CRC32_Check32((u32*)data, len / 4, result);
	
	return Error;
}

/********************************************** END OF FLEE **********************************************/
