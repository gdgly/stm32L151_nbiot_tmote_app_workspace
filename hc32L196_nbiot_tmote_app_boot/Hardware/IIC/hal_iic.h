#ifndef __HAL_IIC_H
#define   __HAL_IIC_H

#include "sys.h"
#include "gpio.h"

#define IIC0_SCL_GPIOx			GpioPortB
#define IIC0_SCL_PIN			GpioPin6
#define IIC0_SCL_AF				GpioAf0

#define IIC0_SDA_GPIOx			GpioPortB
#define IIC0_SDA_PIN			GpioPin7
#define IIC0_SDA_AF				GpioAf0

#define IIC1_SCL_GPIOx			GpioPortA
#define IIC1_SCL_PIN			GpioPin11
#define IIC1_SCL_AF				GpioAf0

#define IIC1_SDA_GPIOx			GpioPortA
#define IIC1_SDA_PIN			GpioPin12
#define IIC1_SDA_AF				GpioAf0

#define IIC0_SDA_IN()			SetBit(((u32)&M0P_GPIO->PADIR + IIC0_SDA_GPIOx), IIC0_SDA_PIN, (boolean_t)(GpioDirIn))
#define IIC0_SDA_OUT()			SetBit(((u32)&M0P_GPIO->PADIR + IIC0_SDA_GPIOx), IIC0_SDA_PIN, (boolean_t)(GpioDirOut))
#define IIC0_SCL_SET(n)			(n ? (Gpio_SetIO(IIC0_SCL_GPIOx, IIC0_SCL_PIN)) : (Gpio_ClrIO(IIC0_SCL_GPIOx, IIC0_SCL_PIN)))
#define IIC0_SDA_SET(n)			(n ? (Gpio_SetIO(IIC0_SDA_GPIOx, IIC0_SDA_PIN)) : (Gpio_ClrIO(IIC0_SDA_GPIOx, IIC0_SDA_PIN)))
#define IIC0_SDA_GET()			(Gpio_GetInputIO(IIC0_SDA_GPIOx, IIC0_SDA_PIN))

#define IIC1_SDA_IN()			SetBit(((u32)&M0P_GPIO->PADIR + IIC1_SDA_GPIOx), IIC1_SDA_PIN, (boolean_t)(GpioDirIn))
#define IIC1_SDA_OUT()			SetBit(((u32)&M0P_GPIO->PADIR + IIC1_SDA_GPIOx), IIC1_SDA_PIN, (boolean_t)(GpioDirOut))
#define IIC1_SCL_SET(n)			(n ? (Gpio_SetIO(IIC1_SCL_GPIOx, IIC1_SCL_PIN)) : (Gpio_ClrIO(IIC1_SCL_GPIOx, IIC1_SCL_PIN)))
#define IIC1_SDA_SET(n)			(n ? (Gpio_SetIO(IIC1_SDA_GPIOx, IIC1_SDA_PIN)) : (Gpio_ClrIO(IIC1_SDA_GPIOx, IIC1_SDA_PIN)))
#define IIC1_SDA_GET()			(Gpio_GetInputIO(IIC1_SDA_GPIOx, IIC1_SDA_PIN))

void HC32_IIC0_Init(void);																//HC32 IIC0初始化
void HC32_IIC0_Start(void);																//HC32 IIC0起始信号
void HC32_IIC0_Stop(void);																//HC32 IIC0停止信号
u8   HC32_IIC0_Wait_Ack(void);															//HC32 IIC0等待ACK信号到来
void HC32_IIC0_Ack(void);																//HC32 IIC0产生ACK应答
void HC32_IIC0_NAck(void);																//HC32 IIC0不产生ACK应答
void HC32_IIC0_Send_Byte(u8 txd);															//HC32 IIC0发送一个字节
u8   HC32_IIC0_Read_Byte(u8 ack);															//HC32 IIC0读取一个字节

void HC32_IIC1_Init(void);																//HC32 IIC1初始化
void HC32_IIC1_Start(void);																//HC32 IIC1起始信号
void HC32_IIC1_Stop(void);																//HC32 IIC1停止信号
u8   HC32_IIC1_Wait_Ack(void);															//HC32 IIC1等待ACK信号到来
void HC32_IIC1_Ack(void);																//HC32 IIC1产生ACK应答
void HC32_IIC1_NAck(void);																//HC32 IIC1不产生ACK应答
void HC32_IIC1_Send_Byte(u8 txd);															//HC32 IIC1发送一个字节
u8   HC32_IIC1_Read_Byte(u8 ack);															//HC32 IIC1读取一个字节

#endif
