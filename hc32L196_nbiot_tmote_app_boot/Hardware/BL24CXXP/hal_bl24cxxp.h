#ifndef __HAL_BL24C02P_H
#define   __HAL_BL24C02P_H

#include "sys.h"
#include "gpio.h"
#include "hal_iic.h"

#define BL24C01P				128
#define BL24C02P				256
#define BL24C04P				512
#define BL24C08P				1024

#define BL24CXXP_TYPE			BL24C02P													//BL24CXX型号

#define BL24CXXP_PAGE_TYPE		8														//BL24CXX页大小

#define BL24CXXP_CHECK_ID		0x55														//BL24CXX校验值
#define BL24CXXP_CHECK_ADDR		255														//BL24CXX校验地址

#define BL24CXXP_SLAVE_ADDRESS_W	0xA0														//I2C从机地址写
#define BL24CXXP_SLAVE_ADDRESS_R	0xA1														//I2C从机地址读

void BL24CXX_Init(void);																	//BL24CXX初始化

u8   BL24CXX_Check(void);																//BL24CXX检查

u8   BL24CXX_WriteOneByte(u16 writeAddr, u8 dataToWrite);										//BL24CXX指定地址写入1Byte数据
u8   BL24CXX_ReadOneByte(u16 readAddr);														//BL24CXX指定地址读取1Byte数据

u8   BL24CXX_WriteBuffer(u16 addr, u8* buf, u16 len);											//BL24CXX指定地址写入nByte数据
u8   BL24CXX_ReadBuffer(u16 addr, u8* buf, u16 len);											//BL24CXX指定地址读取nByte数据

#endif /* __HAL_BL24C02P_H */
