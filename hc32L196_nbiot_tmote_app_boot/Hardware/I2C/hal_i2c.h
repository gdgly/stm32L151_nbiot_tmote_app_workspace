#ifndef __HAL_I2C_H
#define   __HAL_I2C_H

#include "sys.h"
#include "i2c.h"
#include "gpio.h"

#define I2C0_SCL_GPIOx			GpioPortB
#define I2C0_SCL_PIN			GpioPin6
#define I2C0_SCL_AF				GpioAf1

#define I2C0_SDA_GPIOx			GpioPortB
#define I2C0_SDA_PIN			GpioPin7
#define I2C0_SDA_AF				GpioAf1

#define I2C1_SCL_GPIOx			GpioPortA
#define I2C1_SCL_PIN			GpioPin11
#define I2C1_SCL_AF				GpioAf3

#define I2C1_SDA_GPIOx			GpioPortA
#define I2C1_SDA_PIN			GpioPin12
#define I2C1_SDA_AF				GpioAf3

void HC32_I2C0_Init(u32 bound);															//HC32 I2C0初始化
void HC32_I2C1_Init(u32 bound);															//HC32 I2C1初始化

en_result_t HC32_I2C_MasterWriteData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS);			//HC32 I2C主机发送数据
en_result_t HC32_I2C_MasterReadData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS);			//HC32 I2C主机读取数据

#endif /* __HAL_I2C_H */
