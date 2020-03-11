/**
  *********************************************************************************************************
  * @file    hal_i2c.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-11
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
#include "hal_i2c.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			static void I2C0_Port_Init(void)
 @Description			I2C0_Port_Init								: HC32 I2C0引脚初始化
 @Input				void
 @Return				void
 @attention			I2C0_SCL => PB06
					I2C0_SDA => PB07
**********************************************************************************************************/
static void I2C0_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdEnable;
	
	Gpio_Init(I2C0_SCL_GPIOx, I2C0_SCL_PIN, &GPIO_Initure);
	Gpio_Init(I2C0_SDA_GPIOx, I2C0_SDA_PIN, &GPIO_Initure);
	
	Gpio_SetAfMode(I2C0_SCL_GPIOx, I2C0_SCL_PIN, I2C0_SCL_AF);
	Gpio_SetAfMode(I2C0_SDA_GPIOx, I2C0_SDA_PIN, I2C0_SDA_AF);
}

/**********************************************************************************************************
 @Function			static void I2C1_Port_Init(void)
 @Description			I2C1_Port_Init								: HC32 I2C1引脚初始化
 @Input				void
 @Return				void
 @attention			I2C1_SCL => PA11
					I2C1_SDA => PA12
**********************************************************************************************************/
static void I2C1_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdEnable;
	
	Gpio_Init(I2C1_SCL_GPIOx, I2C1_SCL_PIN, &GPIO_Initure);
	Gpio_Init(I2C1_SDA_GPIOx, I2C1_SDA_PIN, &GPIO_Initure);
	
	Gpio_SetAfMode(I2C1_SCL_GPIOx, I2C1_SCL_PIN, I2C1_SCL_AF);
	Gpio_SetAfMode(I2C1_SDA_GPIOx, I2C1_SDA_PIN, I2C1_SDA_AF);
}

/**********************************************************************************************************
 @Function			void HC32_I2C0_Init(u32 bound)
 @Description			HC32_I2C0_Init								: HC32 I2C0初始化
 @Input				bound									: 波特率
 @Return				void
**********************************************************************************************************/
void HC32_I2C0_Init(u32 bound)
{
	stc_i2c_cfg_t I2C_Initure;
	
	I2C0_Port_Init();
	
	DDL_ZERO_STRUCT(I2C_Initure);
	
	I2C_Initure.u32Pclk			= Sysctrl_GetPClkFreq();
	I2C_Initure.u32Baud			= bound;
	I2C_Initure.enMode			= I2cMasterMode;
	I2C_Initure.bGc			= FALSE;
	I2C_Initure.u8SlaveAddr		= 0x55;
	I2C_Init(M0P_I2C0, &I2C_Initure);
}

/**********************************************************************************************************
 @Function			void HC32_I2C1_Init(u32 bound)
 @Description			HC32_I2C1_Init								: HC32 I2C1初始化
 @Input				bound									: 波特率
 @Return				void
**********************************************************************************************************/
void HC32_I2C1_Init(u32 bound)
{
	stc_i2c_cfg_t I2C_Initure;
	
	I2C1_Port_Init();
	
	DDL_ZERO_STRUCT(I2C_Initure);
	
	I2C_Initure.u32Pclk			= Sysctrl_GetPClkFreq();
	I2C_Initure.u32Baud			= bound;
	I2C_Initure.enMode			= I2cMasterMode;
	I2C_Initure.bGc			= FALSE;
	I2C_Initure.u8SlaveAddr		= 0x55;
	I2C_Init(M0P_I2C1, &I2C_Initure);
}

/**********************************************************************************************************
 @Function			en_result_t HC32_I2C_MasterWriteData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS)
 @Description			HC32_I2C_MasterWriteData						: HC32 I2C主机发送数据
 @Input				I2CX										: I2C接口
					u8Sladdr									: 从机地址
					u8Addr									: 从机内存地址
					pu8Data									: 写入数据
					u32Len									: 写入数据长度
					timeoutMS									: 超时时间
 @Return				void
**********************************************************************************************************/
en_result_t HC32_I2C_MasterWriteData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS)
{
	en_result_t enRet = Error;
	timeMeterTypeDef I2Ctimer;
	u8 u8i = 0, u8State;
	
	HC32_TimeMeter_CountdownMS(&I2Ctimer, timeoutMS);
	
	/* Send Start Signal */
	I2C_SetFunc(I2CX, I2cStart_En);
	
	while (1) {
		/* Wait SI => 1 */
		while (0 == I2C_GetIrq(I2CX)) {
			if (HC32_TimeMeter_IsExpiredMS(&I2Ctimer) != false) {
				enRet = ErrorTimeout;
				goto exit;
			}
		}
		/* Check Stat */
		u8State = I2C_GetState(I2CX);
		switch (u8State)
		{
		case 0x08:
			I2C_ClearFunc(I2CX, I2cStart_En);
			I2C_WriteByte(I2CX, u8Sladdr);
			break;
		
		case 0x18:
			I2C_WriteByte(I2CX, u8Addr);
			break;
		
		case 0x28:
			I2C_WriteByte(I2CX, pu8Data[u8i++]);
			break;
		
		case 0x20:
		case 0x38:
			I2C_SetFunc(I2CX, I2cStart_En);
			break;
		
		case 0x30:
			I2C_SetFunc(I2CX, I2cStop_En);
			break;
		
		default:
			break;
		}
		/* Send Data Over */
		if (u8i > u32Len) {
			I2C_SetFunc(I2CX, I2cStop_En);
			I2C_ClearIrq(I2CX);
			break;
		}
		/* Clear Go run */
		I2C_ClearIrq(I2CX);
	}
	
	enRet = Ok;
	
exit:
	return enRet;
}

/**********************************************************************************************************
 @Function			en_result_t HC32_I2C_MasterReadData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS)
 @Description			HC32_I2C_MasterReadData						: HC32 I2C主机读取数据
 @Input				I2CX										: I2C接口
					u8Sladdr									: 从机地址
					u8Addr									: 从机内存地址
					pu8Data									: 读取数据
					u32Len									: 读取数据长度
					timeoutMS									: 超时时间
 @Return				void
**********************************************************************************************************/
en_result_t HC32_I2C_MasterReadData(M0P_I2C_TypeDef* I2CX, u8 u8Sladdr, u8 u8Addr, u8 *pu8Data, u32 u32Len, u32 timeoutMS)
{
	en_result_t enRet = Error;
	timeMeterTypeDef I2Ctimer;
	u8 u8i = 0, u8State;
	
	HC32_TimeMeter_CountdownMS(&I2Ctimer, timeoutMS);
	
	/* Send Start Signal */
	I2C_SetFunc(I2CX, I2cStart_En);
	
	while (1) {
		/* Wait SI => 1 */
		while (0 == I2C_GetIrq(I2CX)) {
			if (HC32_TimeMeter_IsExpiredMS(&I2Ctimer) != false) {
				enRet = ErrorTimeout;
				goto exit;
			}
		}
		/* Check Stat */
		u8State = I2C_GetState(I2CX);
		switch (u8State)
		{
		case 0x08:
			I2C_ClearFunc(I2CX, I2cStart_En);
			I2C_WriteByte(I2CX, u8Sladdr);
			break;
		
		case 0x18:
			I2C_WriteByte(I2CX, u8Addr);
			break;
		
		case 0x28:
			I2C_SetFunc(I2CX, I2cStart_En);
			break;
		
		case 0x10:
			I2C_ClearFunc(I2CX, I2cStart_En);
			I2C_WriteByte(I2CX, u8Sladdr | 0x01);
			break;
		
		case 0x40:
			if (u32Len > 1) {
				I2C_SetFunc(I2CX, I2cAck_En);
			}
			break;
		
		case 0x50:
			pu8Data[u8i++] = I2C_ReadByte(I2CX);
			if (u8i == u32Len - 1) {
				I2C_ClearFunc(I2CX, I2cAck_En);
			}
			break;
		
		case 0x58:
			pu8Data[u8i++] = I2C_ReadByte(I2CX);
			I2C_SetFunc(I2CX, I2cStop_En);
			break;
		
		case 0x38:
			I2C_SetFunc(I2CX, I2cStart_En);
			break;
		
		case 0x48:
			I2C_SetFunc(I2CX, I2cStop_En);
			I2C_SetFunc(I2CX, I2cStart_En);
			break;
		
		default:
			I2C_SetFunc(I2CX,I2cStart_En);
			break;
		}
		/* Clear Go run */
		I2C_ClearIrq(I2CX);
		/* Recv Data Over */
		if (u8i == u32Len) break;
	}
	
	enRet = Ok;
	
exit:
	return enRet;
}

/********************************************** END OF FLEE **********************************************/
