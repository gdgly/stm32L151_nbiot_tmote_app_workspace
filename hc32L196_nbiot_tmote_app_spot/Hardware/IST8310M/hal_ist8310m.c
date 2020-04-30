/**
  *********************************************************************************************************
  * @file    hal_ist8310m.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-29
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
#include "hal_ist8310m.h"
#include "delay.h"
#include "usart.h"
#include <stdlib.h>

/**********************************************************************************************************
 @Function			static u8 IST8310M_WriteByte(u8 ucRegAddr, u8 ucRegData)
 @Description			IST8310M写入1Byte数据( 内部调用 )
 @Input				ucRegAddr : 写入地址
					ucRegData : 写入数据
 @Return				0
					Err
**********************************************************************************************************/
static u8 IST8310M_WriteByte(u8 ucRegAddr, u8 ucRegData)
{
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(IST8310M_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待写入数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegData);														//发送需写入数据数据
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return 0;
}

/**********************************************************************************************************
 @Function			static u8 IST8310M_ReadByte(u8 ucRegAddr)
 @Description			IST8310M读取1Byte数据( 内部调用 )
 @Input				ucRegAddr : 读取数据地址
 @Return				ucRegAddr : 读取数据
**********************************************************************************************************/
static u8 IST8310M_ReadByte(u8 ucRegAddr)
{
	u8 ucData;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(IST8310M_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待读取数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(IST8310M_SLAVE_ADDRESS_R);											//发送I2C从机地址读
	HC32_IIC0_Wait_Ack();																//等待应答
	
	ucData = HC32_IIC0_Read_Byte(0);														//读取数据
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return ucData;
}

/**********************************************************************************************************
 @Function			static u8 IST8310M_MultiRead(u8 ucRegAddr, u8 nByte, u8* outbuf)
 @Description			IST8310M读取nByte数据( 内部调用 )
 @Input				ucRegAddr : 读取数据地址
					nByte	: 字节个数
					outbuf	: 存储地址
 @Return				0
					Err
**********************************************************************************************************/
static u8 IST8310M_MultiRead(u8 ucRegAddr, u8 nByte, u8* outbuf)
{
	if (nByte == 0) return 1;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(IST8310M_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待读取数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(IST8310M_SLAVE_ADDRESS_R);											//发送I2C从机地址读
	HC32_IIC0_Wait_Ack();																//等待应答
	
	for (u8 index = 0; index < (nByte - 1); index++) {										//读取数据
		outbuf[index] = HC32_IIC0_Read_Byte(1);
	}
	outbuf[nByte - 1] = HC32_IIC0_Read_Byte(0);
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return 0;
}

/**********************************************************************************************************
 @Function			void IST8310M_Drdy_Init(void)
 @Description			IST8310M引脚配置PA11高电平读取
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_Drdy_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdEnable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(IST_DRDY_GPIOx, IST_DRDY_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void IST8310M_Drdy_DeInit(void)
 @Description			IST8310M引脚配置PA11反初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_Drdy_DeInit(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(IST_DRDY_GPIOx, IST_DRDY_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void IST8310M_Discharge(void)
 @Description			IST8310M硬复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_Discharge(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	
	Gpio_Init(IIC0_SCL_GPIOx, IIC0_SCL_PIN, &GPIO_Initure);
	Gpio_Init(IIC0_SDA_GPIOx, IIC0_SDA_PIN, &GPIO_Initure);
	
	Gpio_SetAfMode(IIC0_SCL_GPIOx, IIC0_SCL_PIN, IIC0_SCL_AF);
	Gpio_SetAfMode(IIC0_SDA_GPIOx, IIC0_SDA_PIN, IIC0_SDA_AF);
	
	Gpio_ClrIO(IIC0_SCL_GPIOx, IIC0_SCL_PIN);
	Gpio_ClrIO(IIC0_SDA_GPIOx, IIC0_SDA_PIN);
	Delay_MS(3000);
	Gpio_SetIO(IIC0_SCL_GPIOx, IIC0_SCL_PIN);
	Gpio_SetIO(IIC0_SDA_GPIOx, IIC0_SDA_PIN);
}

/**********************************************************************************************************
 @Function			void IST8310M_Init(void)
 @Description			IST8310M初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_Init(void)
{
	HC32_IIC0_Init();
	
	IST8310M_WriteByte(IST8310M_REG_CNTRL2, IST_CNTRL2_SOFT_REST);
	
	Delay_MS(60);
	
	/* 休眠模式 */
	IST8310M_WriteByte(IST8310M_REG_CNTRL1, IST_CNTRL1_MODE_STANDBY);
	
	/* DRDY输出使能, 高电平有效 */
	IST8310M_WriteByte(IST8310M_REG_CNTRL2, IST_CNTRL2_DREN_ENABLE | IST_CNTRL2_DRP_HIGH);
	
	/* 输出分辨率: 16-bit (Sensitivity: 1320 LSB/Gauss) */
	IST8310M_WriteByte(IST8310M_REG_CNTRL3, IST_CNTRL3_16BLSB_GAUSS_X | IST_CNTRL3_16BLSB_GAUSS_Y | IST_CNTRL3_16BLSB_GAUSS_Z);
	
	/* 转换时间16Times */
	IST8310M_WriteByte(IST8310M_REG_AVGCNTL, IST_AVGCNTL_16TIMES_XZ | IST_AVGCNTL_16TIMES_Y);
	
	/* Normal */
	IST8310M_WriteByte(IST8310M_REG_PDCNTL, IST_PDCNTL_NORMAL);
	
	IST8310M_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void IST8310M_ReadData_Simplify(short* x, short* y, short* z)
 @Description			IST8310M读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void IST8310M_ReadData_Simplify(short* x, short* y, short* z)
{
	u8 ucReadBuf[IST_REG_MAG];
	
	timeMeterTypeDef istTimer;
	
	IST8310M_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&istTimer, 100);
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_SINGLE);
	
	while (HC32_TimeMeter_IsExpiredMS(&istTimer) != true) {
		if (IST_DRDY_READ() == HIGH) {
			IST8310M_MultiRead(IST8310M_DATA_OUT_X_L, IST_REG_MAG, ucReadBuf);
			break;
		}
	}
	
	*x = (int16_t)(ucReadBuf[1] << 8) | ucReadBuf[0];
	*y = (int16_t)(ucReadBuf[3] << 8) | ucReadBuf[2];
	*z = (int16_t)(ucReadBuf[5] << 8) | ucReadBuf[4];
	
	*x *= 2.273;
	*y *= 2.273;
	*z *= 2.273;
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_STANDBY);
	
	IST8310M_ClearInsideData();
	
	IST8310M_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void IST8310M_ReadData_Extended(short* x, short* y, short* z)
 @Description			IST8310M读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void IST8310M_ReadData_Extended(short* x, short* y, short* z)
{
	u8  ucReadBuf[IST_SAMPLE_TIMES][IST_REG_MAG];
	s16 magdata_x[IST_SAMPLE_TIMES], magdata_y[IST_SAMPLE_TIMES], magdata_z[IST_SAMPLE_TIMES];
	s16 sample_times = 0;
	
	timeMeterTypeDef istTimer;
	
	IST8310M_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&istTimer, (100 * IST_SAMPLE_TIMES));
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_SINGLE);
	
	while (HC32_TimeMeter_IsExpiredMS(&istTimer) != true) {
		if (IST_DRDY_READ() == HIGH) {
			IST8310M_MultiRead(IST8310M_DATA_OUT_X_L, IST_REG_MAG, ucReadBuf[sample_times]);
			IST8310M_Mode_Selection(IST_CNTRL1_MODE_SINGLE);
			sample_times++;
		}
		
		if (sample_times >= IST_SAMPLE_TIMES) {
			for (int index = 0; index < IST_SAMPLE_TIMES; index++) {
				magdata_x[index] = (int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0];
				magdata_y[index] = (int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2];
				magdata_z[index] = (int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4];
			}
			
			for (int index = 1; index < IST_SAMPLE_TIMES; index++) {
				if (abs(magdata_x[0] - magdata_x[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_y[0] - magdata_y[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_z[0] - magdata_z[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
			}
			
			break;
		}
	}
	
	*x = 0;
	*y = 0;
	*z = 0;
	
	if (sample_times >= IST_SAMPLE_TIMES) {
		for (int index = 0; index < IST_SAMPLE_TIMES; index++) {
			*x += (((int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
			*y += (((int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
			*z += (((int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
		}
	}
	
	*x *= 2.273;
	*y *= 2.273;
	*z *= 2.273;
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_STANDBY);
	
	IST8310M_ClearInsideData();
	
	IST8310M_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void IST8310M_ReadData_Stronges(short* x, short* y, short* z)
 @Description			IST8310M读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void IST8310M_ReadData_Stronges(short* x, short* y, short* z)
{
	u8  ucReadBuf[IST_SAMPLE_TIMES][IST_REG_MAG];
	s16 magdata_x[IST_SAMPLE_TIMES], magdata_y[IST_SAMPLE_TIMES], magdata_z[IST_SAMPLE_TIMES];
	s16 sample_times = 0;
	
	static s16 x_old, y_old, z_old;
	
	static s16 same_old_cnt = 0;
	
	timeMeterTypeDef istTimer;
	
	IST8310M_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&istTimer, (100 * IST_SAMPLE_TIMES));
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_SINGLE);
	
	while (HC32_TimeMeter_IsExpiredMS(&istTimer) != true) {
		if (IST_DRDY_READ() == HIGH) {
			IST8310M_MultiRead(IST8310M_DATA_OUT_X_L, IST_REG_MAG, ucReadBuf[sample_times]);
			IST8310M_Mode_Selection(IST_CNTRL1_MODE_SINGLE);
			sample_times++;
		}
		
		if (sample_times >= IST_SAMPLE_TIMES) {
			for (int index = 0; index < IST_SAMPLE_TIMES; index++) {
				magdata_x[index] = (int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0];
				magdata_y[index] = (int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2];
				magdata_z[index] = (int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4];
			}
			
			for (int index = 1; index < IST_SAMPLE_TIMES; index++) {
				if (abs(magdata_x[0] - magdata_x[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_y[0] - magdata_y[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_z[0] - magdata_z[index]) > IST_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
			}
			
			if (sample_times != 0) break;
		}
	}
	
	if (sample_times >= IST_SAMPLE_TIMES) {
		*x = 0; *y = 0; *z = 0;
		
		for (int index = 0; index < IST_SAMPLE_TIMES; index++) {
			*x += (((int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
			*y += (((int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
			*z += (((int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4]) + IST_SAMPLE_TIMES/2) / IST_SAMPLE_TIMES;
		}
		
		if ((*x == x_old) && (*y == y_old) && (*z == z_old)) same_old_cnt++;
		
		x_old = *x; y_old = *y; z_old = *z;
		
		if (same_old_cnt > IST_SAMEERR_COUNT) {
			same_old_cnt = 0;
			HC32_AutomaticModule_ReInit();
		}
	}
	else {
		HC32_AutomaticModule_ReInit();
	}
	
	*x *= 2.273;
	*y *= 2.273;
	*z *= 2.273;
	
	IST8310M_Mode_Selection(IST_CNTRL1_MODE_STANDBY);
	
	IST8310M_ClearInsideData();
	
	IST8310M_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void IST8310M_ClearInsideData(void)
 @Description			IST8310M清除内部待读取数据缓存
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_ClearInsideData(void)
{
	u8 ucReadBuf[IST_REG_MAG];
	
	if (IST_DRDY_READ() == HIGH) {
		IST8310M_MultiRead(IST8310M_DATA_OUT_X_L, IST_REG_MAG, ucReadBuf);
	}
}

/**********************************************************************************************************
 @Function			void IST8310M_Mode_Selection(u8 mode)
 @Description			IST8310M工作模式选择
 @Input				mode										: IST_CNTRL1_MODE_STANDBY/IST_CNTRL1_MODE_SINGLE
 @Return				void
**********************************************************************************************************/
void IST8310M_Mode_Selection(u8 mode)
{
	IST8310M_WriteByte(IST8310M_REG_CNTRL1, mode);
}

/**********************************************************************************************************
 @Function			void IST8310M_Drdy_Polarity(u8 polarity)
 @Description			IST8310M引脚有效电平
 @Input				polarity									: IST_CNTRL2_DRP_LOW/IST_CNTRL2_DRP_HIGH
 @Return				void
**********************************************************************************************************/
void IST8310M_Drdy_Polarity(u8 polarity)
{
	u8 reg = 0;
	
	reg = IST8310M_ReadByte(IST8310M_REG_CNTRL2);
	if (polarity == IST_CNTRL2_DRP_LOW) {
		IST8310M_WriteByte(IST8310M_REG_CNTRL2, (reg & 0xFB) | IST_CNTRL2_DRP_LOW);
	}
	else if (polarity == IST_CNTRL2_DRP_HIGH) {
		IST8310M_WriteByte(IST8310M_REG_CNTRL2, (reg & 0xFB) | IST_CNTRL2_DRP_HIGH);
	}
}

/**********************************************************************************************************
 @Function			void IST8310M_Drdy_Enable(u8 enable)
 @Description			IST8310M引脚输出选择
 @Input				enable									: IST_CNTRL2_DREN_DISABLE/IST_CNTRL2_DREN_ENABLE
 @Return				void
**********************************************************************************************************/
void IST8310M_Drdy_Enable(u8 enable)
{
	u8 reg = 0;
	
	reg = IST8310M_ReadByte(IST8310M_REG_CNTRL2);
	if (enable == IST_CNTRL2_DREN_DISABLE) {
		IST8310M_WriteByte(IST8310M_REG_CNTRL2, (reg & 0xF7) | IST_CNTRL2_DREN_DISABLE);
	}
	else if (enable == IST_CNTRL2_DREN_ENABLE) {
		IST8310M_WriteByte(IST8310M_REG_CNTRL2, (reg & 0xF7) | IST_CNTRL2_DREN_ENABLE);
	}
}

/**********************************************************************************************************
 @Function			void IST8310M_Temperature_Enable(u8 enable)
 @Description			IST8310M温度传感器输出选择
 @Input				enable									: IST_TCCNTL_TEMPER_DISABLE/IST_TCCNTL_TEMPER_ENABLE
 @Return				void
**********************************************************************************************************/
void IST8310M_Temperature_Enable(u8 enable)
{
	IST8310M_WriteByte(IST8310M_REG_TCCNTL, enable);
}

/**********************************************************************************************************
 @Function			void IST8310M_Softwart_Reset(void)
 @Description			IST8310M软复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void IST8310M_Softwart_Reset(void)
{
	IST8310M_WriteByte(IST8310M_REG_CNTRL2, IST_CNTRL2_SOFT_REST);
	
	Delay_MS(60);
	
	/* 休眠模式 */
	IST8310M_WriteByte(IST8310M_REG_CNTRL1, IST_CNTRL1_MODE_STANDBY);
	
	/* DRDY输出使能, 高电平有效 */
	IST8310M_WriteByte(IST8310M_REG_CNTRL2, IST_CNTRL2_DREN_ENABLE | IST_CNTRL2_DRP_HIGH);
	
	/* 输出分辨率: 16-bit (Sensitivity: 1320 LSB/Gauss) */
	IST8310M_WriteByte(IST8310M_REG_CNTRL3, IST_CNTRL3_16BLSB_GAUSS_X | IST_CNTRL3_16BLSB_GAUSS_Y | IST_CNTRL3_16BLSB_GAUSS_Z);
	
	/* 转换时间16Times */
	IST8310M_WriteByte(IST8310M_REG_AVGCNTL, IST_AVGCNTL_16TIMES_XZ | IST_AVGCNTL_16TIMES_Y);
	
	/* Normal */
	IST8310M_WriteByte(IST8310M_REG_PDCNTL, IST_PDCNTL_NORMAL);
}

/**********************************************************************************************************
 @Function			void IST8310M_ReadData_Temperature(u16* vtemp)
 @Description			IST8310M读取温度
 @Input				vtemp
 @Return				void
**********************************************************************************************************/
void IST8310M_ReadData_Temperature(u16* vtemp)
{
	u8 temp_l = 0, temp_h = 0;
	
	temp_l = IST8310M_ReadByte(IST8310M_REG_TEMPERATURE_L);
	temp_h = IST8310M_ReadByte(IST8310M_REG_TEMPERATURE_H);
	
	*vtemp = ((u16)(temp_h << 8) | (u16)(temp_l << 0));
}

/********************************************** END OF FLEE **********************************************/
