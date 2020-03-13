/**
  *********************************************************************************************************
  * @file    hal_iic.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-12
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
#include "hal_iic.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void HC32_IIC0_Init(void)
 @Description			HC32_IIC0_Init								: HC32 IIC0初始化
 @Input				void
 @Return				void
 @attention			I2C0_SCL => PB06
					I2C0_SDA => PB07
**********************************************************************************************************/
void HC32_IIC0_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdEnable;
	
	Gpio_Init(IIC0_SCL_GPIOx, IIC0_SCL_PIN, &GPIO_Initure);
	Gpio_Init(IIC0_SDA_GPIOx, IIC0_SDA_PIN, &GPIO_Initure);
	
	Gpio_SetAfMode(IIC0_SCL_GPIOx, IIC0_SCL_PIN, IIC0_SCL_AF);
	Gpio_SetAfMode(IIC0_SDA_GPIOx, IIC0_SDA_PIN, IIC0_SDA_AF);
	
	IIC0_SCL_SET(HIGH);
	IIC0_SDA_SET(HIGH);
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_Init(void)
 @Description			HC32_IIC1_Init								: HC32 IIC1初始化
 @Input				void
 @Return				void
 @attention			I2C1_SCL => PA11
					I2C1_SDA => PA12
**********************************************************************************************************/
void HC32_IIC1_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdEnable;
	
	Gpio_Init(IIC1_SCL_GPIOx, IIC1_SCL_PIN, &GPIO_Initure);
	Gpio_Init(IIC1_SDA_GPIOx, IIC1_SDA_PIN, &GPIO_Initure);
	
	Gpio_SetAfMode(IIC1_SCL_GPIOx, IIC1_SCL_PIN, IIC1_SCL_AF);
	Gpio_SetAfMode(IIC1_SDA_GPIOx, IIC1_SDA_PIN, IIC1_SDA_AF);
	
	IIC1_SCL_SET(HIGH);
	IIC1_SDA_SET(HIGH);
}

/**********************************************************************************************************
 @Function			void HC32_IIC0_Start(void)
 @Description			HC32_IIC0_Start							: HC32 IIC0起始信号
 @Input				void
 @Return				void
 @attention			SCL : HIGH
					SDA : HIGH -> LOW
**********************************************************************************************************/
void HC32_IIC0_Start(void)
{
	IIC0_SDA_OUT();
	
	IIC0_SDA_SET(HIGH);
	IIC0_SCL_SET(HIGH);
	
	Delay_US(4);
	
	IIC0_SDA_SET(LOW);
	
	Delay_US(4);
	
	IIC0_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_Start(void)
 @Description			HC32_IIC1_Start							: HC32 IIC1起始信号
 @Input				void
 @Return				void
 @attention			SCL : HIGH
					SDA : HIGH -> LOW
**********************************************************************************************************/
void HC32_IIC1_Start(void)
{
	IIC1_SDA_OUT();
	
	IIC1_SDA_SET(HIGH);
	IIC1_SCL_SET(HIGH);
	
	Delay_US(4);
	
	IIC1_SDA_SET(LOW);
	
	Delay_US(4);
	
	IIC1_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC0_Stop(void)
 @Description			HC32_IIC0_Stop								: HC32 IIC0停止信号
 @Input				void
 @Return				void
 @attention			SCL : HIGH
					SDA : LOW -> HIGH
**********************************************************************************************************/
void HC32_IIC0_Stop(void)
{
	IIC0_SDA_OUT();
	
	IIC0_SDA_SET(LOW);
	IIC0_SCL_SET(LOW);
	
	Delay_US(4);
	
	IIC0_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC0_SDA_SET(HIGH);
	
	Delay_US(4);
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_Stop(void)
 @Description			HC32_IIC1_Stop								: HC32 IIC1停止信号
 @Input				void
 @Return				void
 @attention			SCL : HIGH
					SDA : LOW -> HIGH
**********************************************************************************************************/
void HC32_IIC1_Stop(void)
{
	IIC1_SDA_OUT();
	
	IIC1_SDA_SET(LOW);
	IIC1_SCL_SET(LOW);
	
	Delay_US(4);
	
	IIC1_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC1_SDA_SET(HIGH);
	
	Delay_US(4);
}

/**********************************************************************************************************
 @Function			u8 HC32_IIC0_Wait_Ack(void)
 @Description			HC32_IIC0_Wait_Ack							: HC32 IIC0等待ACK信号到来
 @Input				void
 @Return				1 : 接收应答失败
					0 : 接收应答成功
**********************************************************************************************************/
u8 HC32_IIC0_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	
	IIC0_SDA_IN();
	IIC0_SDA_SET(HIGH); __NOP();
	IIC0_SCL_SET(HIGH); __NOP();
	while (IIC0_SDA_GET()) {
		ucErrTime++;
		if (ucErrTime > 250) {
			HC32_IIC0_Stop();
			return 1;
		}
	}
	IIC0_SCL_SET(LOW);
	
	return 0;
}

/**********************************************************************************************************
 @Function			u8 HC32_IIC1_Wait_Ack(void)
 @Description			HC32_IIC1_Wait_Ack							: HC32 IIC1等待ACK信号到来
 @Input				void
 @Return				1 : 接收应答失败
					0 : 接收应答成功
**********************************************************************************************************/
u8 HC32_IIC1_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	
	IIC1_SDA_IN();
	IIC1_SDA_SET(HIGH); __NOP();
	IIC1_SCL_SET(HIGH); __NOP();
	while (IIC1_SDA_GET()) {
		ucErrTime++;
		if (ucErrTime > 250) {
			HC32_IIC1_Stop();
			return 1;
		}
	}
	IIC1_SCL_SET(LOW);
	
	return 0;
}

/**********************************************************************************************************
 @Function			void HC32_IIC0_Ack(void)
 @Description			HC32_IIC0_Ack								: HC32 IIC0产生ACK应答
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_IIC0_Ack(void)
{
	IIC0_SCL_SET(LOW);
	IIC0_SDA_OUT();
	IIC0_SDA_SET(LOW);
	
	Delay_US(2);
	
	IIC0_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC0_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_Ack(void)
 @Description			HC32_IIC1_Ack								: HC32 IIC1产生ACK应答
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_IIC1_Ack(void)
{
	IIC1_SCL_SET(LOW);
	IIC1_SDA_OUT();
	IIC1_SDA_SET(LOW);
	
	Delay_US(2);
	
	IIC1_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC1_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC0_NAck(void)
 @Description			HC32_IIC0_NAck								: HC32 IIC0不产生ACK应答
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_IIC0_NAck(void)
{
	IIC0_SCL_SET(LOW);
	IIC0_SDA_OUT();
	IIC0_SDA_SET(HIGH);
	
	Delay_US(2);
	
	IIC0_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC0_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_NAck(void)
 @Description			HC32_IIC1_NAck								: HC32 IIC1不产生ACK应答
 @Input				void
 @Return				void
**********************************************************************************************************/
void HC32_IIC1_NAck(void)
{
	IIC1_SCL_SET(LOW);
	IIC1_SDA_OUT();
	IIC1_SDA_SET(HIGH);
	
	Delay_US(2);
	
	IIC1_SCL_SET(HIGH);
	
	Delay_US(2);
	
	IIC1_SCL_SET(LOW);
}

/**********************************************************************************************************
 @Function			void HC32_IIC0_Send_Byte(u8 txd)
 @Description			HC32_IIC0_Send_Byte							: HC32 IIC0发送一个字节
 @Input				txd										: 发送数据
 @Return				void
**********************************************************************************************************/
void HC32_IIC0_Send_Byte(u8 txd)
{
	IIC0_SDA_OUT();
	IIC0_SCL_SET(LOW);
	
	for (u8 i = 0; i < 8; i++) {
		IIC0_SDA_SET((txd & 0x80) >> 7);
		txd <<= 1;
		
		Delay_US(2);
		
		IIC0_SCL_SET(HIGH);
		
		Delay_US(2);
		
		IIC0_SCL_SET(LOW);
		
		Delay_US(2);
	}
}

/**********************************************************************************************************
 @Function			void HC32_IIC1_Send_Byte(u8 txd)
 @Description			HC32_IIC1_Send_Byte							: HC32 IIC1发送一个字节
 @Input				txd										: 发送数据
 @Return				void
**********************************************************************************************************/
void HC32_IIC1_Send_Byte(u8 txd)
{
	IIC1_SDA_OUT();
	IIC1_SCL_SET(LOW);
	
	for (u8 i = 0; i < 8; i++) {
		IIC1_SDA_SET((txd & 0x80) >> 7);
		txd <<= 1;
		
		Delay_US(2);
		
		IIC1_SCL_SET(HIGH);
		
		Delay_US(2);
		
		IIC1_SCL_SET(LOW);
		
		Delay_US(2);
	}
}

/**********************************************************************************************************
 @Function			u8 HC32_IIC0_Read_Byte(u8 ack)
 @Description			HC32_IIC0_Read_Byte							: HC32 IIC0读取一个字节
 @Input				ack
 @Return				所读数据
**********************************************************************************************************/
u8 HC32_IIC0_Read_Byte(u8 ack)
{
	unsigned char receive = 0;
	
	IIC0_SDA_IN();
	
	for (u8 i = 0; i < 8; i++) {
		IIC0_SCL_SET(LOW);
		
		Delay_US(2);
		
		IIC0_SCL_SET(HIGH);
		
		receive <<= 1;
		if (IIC0_SDA_GET()) receive++;
		
		Delay_US(1);
	}
	
	if (!ack)
		HC32_IIC0_NAck();
	else
		HC32_IIC0_Ack();
	
	return receive;
}

/**********************************************************************************************************
 @Function			u8 HC32_IIC1_Read_Byte(u8 ack)
 @Description			HC32_IIC1_Read_Byte							: HC32 IIC1读取一个字节
 @Input				ack
 @Return				所读数据
**********************************************************************************************************/
u8 HC32_IIC1_Read_Byte(u8 ack)
{
	unsigned char receive = 0;
	
	IIC1_SDA_IN();
	
	for (u8 i = 0; i < 8; i++) {
		IIC1_SCL_SET(LOW);
		
		Delay_US(2);
		
		IIC1_SCL_SET(HIGH);
		
		receive <<= 1;
		if (IIC1_SDA_GET()) receive++;
		
		Delay_US(1);
	}
	
	if (!ack)
		HC32_IIC1_NAck();
	else
		HC32_IIC1_Ack();
	
	return receive;
}

/********************************************** END OF FLEE **********************************************/
