/**
  *********************************************************************************************************
  * @file    hal_qmc5883l.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-13
  * @brief   
  *********************************************************************************************************
  * @attention
  *          EEPROM Default All 0xFF
  *          BL24C02P : 256Byte
  *                     01Page =   8Byte
  *                     32Page = 256Byte
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_bl24cxxp.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void BL24CXX_Init(void)
 @Description			BL24CXX_Init:								: BL24CXX初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void BL24CXX_Init(void)
{
	HC32_IIC0_Init();
}

/**********************************************************************************************************
 @Function			u8 BL24CXX_WriteOneByte(u16 writeAddr, u8 dataToWrite)
 @Description			BL24CXX_WriteOneByte:						: BL24CXX指定地址写入1Byte数据
 @Input				writeAddr									: 需写入数据的目的地址
					dataToWrite								: 需写入数据
 @Return				0										: OK
					1										: Error
**********************************************************************************************************/
u8 BL24CXX_WriteOneByte(u16 writeAddr, u8 dataToWrite)
{
	if (writeAddr >= BL24CXXP_TYPE) return 1;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(BL24CXXP_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(writeAddr & 0xFF);													//发送待写入数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(dataToWrite);														//发送需写入数据数据
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	Delay_MS(10);																		//Write Cycle Time Max 5MS
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 BL24CXX_ReadOneByte(u16 readAddr)
 @Description			BL24CXX_ReadOneByte:						: BL24CXX指定地址读取1Byte数据
 @Input				readAddr									: 需读取数据的目的地址
 @Return				dataToRead
**********************************************************************************************************/
u8 BL24CXX_ReadOneByte(u16 readAddr)
{
	u8 dataToRead = 0;
	
	if (readAddr >= BL24CXXP_TYPE) return 1;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(BL24CXXP_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(readAddr & 0xFF);													//发送待读取数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(BL24CXXP_SLAVE_ADDRESS_R);											//发送I2C从机地址读
	HC32_IIC0_Wait_Ack();																//等待应答
	
	dataToRead = HC32_IIC0_Read_Byte(0);													//读取数据
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return dataToRead;
}


























/********************************************** END OF FLEE **********************************************/
