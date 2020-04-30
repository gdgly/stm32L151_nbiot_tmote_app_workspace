/**
  *********************************************************************************************************
  * @file    hal_qmc5883l.c
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
#include "hal_qmc5883l.h"
#include "delay.h"
#include "usart.h"
#include <stdlib.h>

/**********************************************************************************************************
 @Function			static u8 QMC5883L_WriteByte(u8 ucRegAddr, u8 ucRegData)
 @Description			QMC5883L写入1Byte数据( 内部调用 )
 @Input				ucRegAddr : 写入地址
					ucRegData : 写入数据
 @Return				0
					Err
**********************************************************************************************************/
static u8 QMC5883L_WriteByte(u8 ucRegAddr, u8 ucRegData)
{
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(QMC5883L_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待写入数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegData);														//发送需写入数据数据
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return 0;
}

/**********************************************************************************************************
 @Function			static u8 QMC5883L_ReadByte(u8 ucRegAddr)
 @Description			QMC5883L读取1Byte数据( 内部调用 )
 @Input				ucRegAddr : 读取数据地址
 @Return				ucRegAddr : 读取数据
**********************************************************************************************************/
static u8 QMC5883L_ReadByte(u8 ucRegAddr)
{
	u8 ucData;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(QMC5883L_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待读取数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(QMC5883L_SLAVE_ADDRESS_R);											//发送I2C从机地址读
	HC32_IIC0_Wait_Ack();																//等待应答
	
	ucData = HC32_IIC0_Read_Byte(0);														//读取数据
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return ucData;
}

/**********************************************************************************************************
 @Function			static u8 QMC5883L_MultiRead(u8 ucRegAddr, u8 nByte, u8* outbuf)
 @Description			QMC5883L读取nByte数据( 内部调用 )
 @Input				ucRegAddr : 读取数据地址
					nByte	: 字节个数
					outbuf	: 存储地址
 @Return				0
					Err
**********************************************************************************************************/
static u8 QMC5883L_MultiRead(u8 ucRegAddr, u8 nByte, u8* outbuf)
{
	if (nByte == 0) return 1;
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(QMC5883L_SLAVE_ADDRESS_W);											//发送I2C从机地址写
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Send_Byte(ucRegAddr);														//发送待读取数据地址
	HC32_IIC0_Wait_Ack();																//等待应答
	
	HC32_IIC0_Start();																	//发送起始信号
	
	HC32_IIC0_Send_Byte(QMC5883L_SLAVE_ADDRESS_R);											//发送I2C从机地址读
	HC32_IIC0_Wait_Ack();																//等待应答
	
	for (u8 index = 0; index < (nByte - 1); index++) {										//读取数据
		outbuf[index] = HC32_IIC0_Read_Byte(1);
	}
	outbuf[nByte - 1] = HC32_IIC0_Read_Byte(0);
	
	HC32_IIC0_Stop();																	//发送停止信号
	
	return 0;
}

/**********************************************************************************************************
 @Function			void QMC5883L_Drdy_Init(void)
 @Description			QMC5883L引脚配置PA11高电平读取
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Drdy_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdEnable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(QMC_DRDY_GPIOx, QMC_DRDY_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void QMC5883L_Drdy_DeInit(void)
 @Description			QMC5883L引脚配置PA11反初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Drdy_DeInit(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuDisable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioFastIO;
	Gpio_Init(QMC_DRDY_GPIOx, QMC_DRDY_PIN, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			void QMC5883L_Discharge(void)
 @Description			QMC5883L硬复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Discharge(void)
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
 @Function			void QMC5883L_Init(void)
 @Description			QMC5883L初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Init(void)
{
	HC32_IIC0_Init();
	
	QMC5883L_WriteByte(QMC5883L_CR2, QMC_SOFT_REST);
	
	Delay_MS(60);
	
	QMC5883L_WriteByte(QMC5883L_ADDR_PERIORC, QMC_PERIORC_VALUE);
	
	QMC5883L_WriteByte(QMC5883L_ADDR_CFGC, QMC_CFGC_VALUE);
	QMC5883L_WriteByte(QMC5883L_ADDR_CFGD, QMC_CFGD_VALUE);
	
	/* 64滤波, 8高斯范围, 200Hz输出, 初始化为StandBy */
	QMC5883L_WriteByte(QMC5883L_CR1, QMC_OSR_64 | QMC_RANGE_8G | QMC_RATES_200HZ | QMC_MODE_STANDBY);
	/* 引脚中断使能, 数据读取完指针自动偏转失能 */
	QMC5883L_WriteByte(QMC5883L_CR2, QMC_INT_ENABLE | QMC_POINT_ROLL_DISABLE);
	
	QMC5883L_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void QMC5883L_ReadData_Simplify(short* x, short* y, short* z)
 @Description			QMC5883L读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void QMC5883L_ReadData_Simplify(short* x, short* y, short* z)
{
	u8 ucReadBuf[QMC_REG_MAG];
	
	timeMeterTypeDef qmcTimer;
	
	QMC5883L_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&qmcTimer, 100);
	
	QMC5883L_Mode_Selection(QMC_MODE_CONTINOUS);
	
	while (HC32_TimeMeter_IsExpiredMS(&qmcTimer) != true) {
		if (QMC_DRDY_READ() == HIGH) {
			QMC5883L_MultiRead(QMC_DATA_OUT_X_L, QMC_REG_MAG, ucReadBuf);
			break;
		}
	}
	
	*x = (int16_t)(ucReadBuf[1] << 8) | ucReadBuf[0];
	*y = (int16_t)(ucReadBuf[3] << 8) | ucReadBuf[2];
	*z = (int16_t)(ucReadBuf[5] << 8) | ucReadBuf[4];
	
	QMC5883L_Mode_Selection(QMC_MODE_STANDBY);
	
	QMC5883L_ClearInsideData();
	
	QMC5883L_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void QMC5883L_ReadData_Extended(short* x, short* y, short* z)
 @Description			QMC5883L读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void QMC5883L_ReadData_Extended(short* x, short* y, short* z)
{
	u8  ucReadBuf[QMC_SAMPLE_TIMES][QMC_REG_MAG];
	s16 magdata_x[QMC_SAMPLE_TIMES], magdata_y[QMC_SAMPLE_TIMES], magdata_z[QMC_SAMPLE_TIMES];
	s16 sample_times = 0;
	
	timeMeterTypeDef qmcTimer;
	
	QMC5883L_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&qmcTimer, (100 * QMC_SAMPLE_TIMES));
	
	QMC5883L_Mode_Selection(QMC_MODE_CONTINOUS);
	
	while (HC32_TimeMeter_IsExpiredMS(&qmcTimer) != true) {
		if (QMC_DRDY_READ() == HIGH) {
			QMC5883L_MultiRead(QMC_DATA_OUT_X_L, QMC_REG_MAG, ucReadBuf[sample_times]);
			sample_times++;
		}
		
		if (sample_times >= QMC_SAMPLE_TIMES) {
			for (int index = 0; index < QMC_SAMPLE_TIMES; index++) {
				magdata_x[index] = (int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0];
				magdata_y[index] = (int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2];
				magdata_z[index] = (int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4];
			}
			
			for (int index = 1; index < QMC_SAMPLE_TIMES; index++) {
				if (abs(magdata_x[0] - magdata_x[index]) > QMC_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_y[0] - magdata_y[index]) > QMC_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_z[0] - magdata_z[index]) > QMC_DEVIATION_MAX) {
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
	
	if (sample_times >= QMC_SAMPLE_TIMES) {
		for (int index = 0; index < QMC_SAMPLE_TIMES; index++) {
			*x += (((int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
			*y += (((int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
			*z += (((int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
		}
	}
	
	QMC5883L_Mode_Selection(QMC_MODE_STANDBY);
	
	QMC5883L_ClearInsideData();
	
	QMC5883L_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void QMC5883L_ReadData_Stronges(short* x, short* y, short* z)
 @Description			QMC5883L读取数据
 @Input				&x &y &z
 @Return				void
**********************************************************************************************************/
void QMC5883L_ReadData_Stronges(short* x, short* y, short* z)
{
	u8  ucReadBuf[QMC_SAMPLE_TIMES][QMC_REG_MAG];
	s16 magdata_x[QMC_SAMPLE_TIMES], magdata_y[QMC_SAMPLE_TIMES], magdata_z[QMC_SAMPLE_TIMES];
	s16 sample_times = 0;
	
	static s16 x_old, y_old, z_old;
	
	static s16 same_old_cnt = 0;
	
	timeMeterTypeDef qmcTimer;
	
	QMC5883L_Drdy_Init();
	
	HC32_TimeMeter_CountdownMS(&qmcTimer, (100 * QMC_SAMPLE_TIMES));
	
	QMC5883L_Mode_Selection(QMC_MODE_CONTINOUS);
	
	while (HC32_TimeMeter_IsExpiredMS(&qmcTimer) != true) {
		if (QMC_DRDY_READ() == HIGH) {
			QMC5883L_MultiRead(QMC_DATA_OUT_X_L, QMC_REG_MAG, ucReadBuf[sample_times]);
			sample_times++;
		}
		
		if (sample_times >= QMC_SAMPLE_TIMES) {
			for (int index = 0; index < QMC_SAMPLE_TIMES; index++) {
				magdata_x[index] = (int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0];
				magdata_y[index] = (int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2];
				magdata_z[index] = (int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4];
			}
			
			for (int index = 1; index < QMC_SAMPLE_TIMES; index++) {
				if (abs(magdata_x[0] - magdata_x[index]) > QMC_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_y[0] - magdata_y[index]) > QMC_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
				if (abs(magdata_z[0] - magdata_z[index]) > QMC_DEVIATION_MAX) {
					sample_times = 0;
					break;
				}
			}
			
			if (sample_times != 0) break;
		}
	}
	
	if (sample_times >= QMC_SAMPLE_TIMES) {
		*x = 0; *y = 0; *z = 0;
		
		for (int index = 0; index < QMC_SAMPLE_TIMES; index++) {
			*x += (((int16_t)(ucReadBuf[index][1] << 8) | ucReadBuf[index][0]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
			*y += (((int16_t)(ucReadBuf[index][3] << 8) | ucReadBuf[index][2]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
			*z += (((int16_t)(ucReadBuf[index][5] << 8) | ucReadBuf[index][4]) + QMC_SAMPLE_TIMES/2) / QMC_SAMPLE_TIMES;
		}
		
		if ((*x == x_old) && (*y == y_old) && (*z == z_old)) same_old_cnt++;
		
		x_old = *x; y_old = *y; z_old = *z;
		
		if (same_old_cnt > QMC_SAMEERR_COUNT) {
			same_old_cnt = 0;
			HC32_AutomaticModule_ReInit();
		}
	}
	else {
		HC32_AutomaticModule_ReInit();
	}
	
	QMC5883L_Mode_Selection(QMC_MODE_STANDBY);
	
	QMC5883L_ClearInsideData();
	
	QMC5883L_Drdy_DeInit();
}

/**********************************************************************************************************
 @Function			void QMC5883L_ClearInsideData(void)
 @Description			QMC5883L清除内部待读取数据缓存
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_ClearInsideData(void)
{
	u8 ucReadBuf[QMC_REG_MAG];
	
	if (QMC_DRDY_READ() == HIGH) {
		QMC5883L_MultiRead(QMC_DATA_OUT_X_L, QMC_REG_MAG, ucReadBuf);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Mode_Selection(u8 mode)
 @Description			QMC5883L工作模式选择
 @Input				mode : QMC_MODE_STANDBY/QMC_MODE_CONTINOUS
 @Return				void
**********************************************************************************************************/
void QMC5883L_Mode_Selection(u8 mode)
{
	u8 reg = 0;
	
	reg = QMC5883L_ReadByte(QMC5883L_CR1);
	if (mode == QMC_MODE_STANDBY) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xFC) | QMC_MODE_STANDBY);
	}
	else if (mode == QMC_MODE_CONTINOUS) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xFC) | QMC_MODE_CONTINOUS);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Rates_Selection(u8 rates)
 @Description			QMC5883L数据输出速率选择
 @Input				rates : QMC_RATES_10HZ/QMC_RATES_50HZ/QMC_RATES_100HZ/QMC_RATES_200HZ
 @Return				void
**********************************************************************************************************/
void QMC5883L_Rates_Selection(u8 rates)
{
	u8 reg = 0;
	
	reg = QMC5883L_ReadByte(QMC5883L_CR1);
	if (rates == QMC_RATES_10HZ) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xF3) | QMC_RATES_10HZ);
	}
	else if (rates == QMC_RATES_50HZ) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xF3) | QMC_RATES_50HZ);
	}
	else if (rates == QMC_RATES_100HZ) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xF3) | QMC_RATES_100HZ);
	}
	else if (rates == QMC_RATES_200HZ) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xF3) | QMC_RATES_200HZ);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Rates_Selection_Freq(u8 Freq)
 @Description			QMC5883L数据输出速率选择
 @Input				0, 1, 2, 3 : QMC_RATES_10HZ/QMC_RATES_50HZ/QMC_RATES_100HZ/QMC_RATES_200HZ
 @Return				void
**********************************************************************************************************/
void QMC5883L_Rates_Selection_Freq(u8 Freq)
{
	if (Freq == 0) {
		QMC5883L_Rates_Selection(QMC_RATES_10HZ);
	}
	else if (Freq == 1) {
		QMC5883L_Rates_Selection(QMC_RATES_50HZ);
	}
	else if (Freq == 2) {
		QMC5883L_Rates_Selection(QMC_RATES_100HZ);
	}
	else if (Freq == 3) {
		QMC5883L_Rates_Selection(QMC_RATES_200HZ);
	}
	else {
		QMC5883L_Rates_Selection(QMC_RATES_50HZ);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Range_Selection(u8 range)
 @Description			QMC5883L测量范围选择
 @Input				range : QMC_RANGE_2G/QMC_RANGE_8G
 @Return				void
**********************************************************************************************************/
void QMC5883L_Range_Selection(u8 range)
{
	u8 reg = 0;
	
	reg = QMC5883L_ReadByte(QMC5883L_CR1);
	if (range == QMC_RANGE_2G) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xCF) | QMC_RANGE_2G);
	}
	else if (range == QMC_RANGE_8G) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0xCF) | QMC_RANGE_8G);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Osr_Selection(u8 osr)
 @Description			QMC5883L内置滤波器带宽选择
 @Input				osr : QMC_OSR_512/QMC_OSR_256/QMC_OSR_128/QMC_OSR_64
 @Return				void
**********************************************************************************************************/
void QMC5883L_Osr_Selection(u8 osr)
{
	u8 reg = 0;
	
	reg = QMC5883L_ReadByte(QMC5883L_CR1);
	if (osr == QMC_OSR_512) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0x3F) | QMC_OSR_512);
	}
	else if (osr == QMC_OSR_256) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0x3F) | QMC_OSR_256);
	}
	else if (osr == QMC_OSR_128) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0x3F) | QMC_OSR_128);
	}
	else if (osr == QMC_OSR_64) {
		QMC5883L_WriteByte(QMC5883L_CR1, (reg & 0x3F) | QMC_OSR_64);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Interrupt_Selection(u8 interrupt)
 @Description			QMC5883L引脚中断选择
 @Input				interrupt : QMC_INT_ENABLE/QMC_INT_DISABLE
 @Return				void
**********************************************************************************************************/
void QMC5883L_Interrupt_Selection(u8 interrupt)
{
	u8 reg = 0;
	
	reg = QMC5883L_ReadByte(QMC5883L_CR2);
	if (interrupt == QMC_INT_ENABLE) {
		QMC5883L_WriteByte(QMC5883L_CR2, (reg & 0xFE) | QMC_INT_ENABLE);
	}
	else if (interrupt == QMC_INT_DISABLE) {
		QMC5883L_WriteByte(QMC5883L_CR2, (reg & 0xFE) | QMC_INT_DISABLE);
	}
}

/**********************************************************************************************************
 @Function			void QMC5883L_Softwart_Reset(void)
 @Description			QMC5883L软复位
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Softwart_Reset(void)
{
	QMC5883L_WriteByte(QMC5883L_CR2, QMC_SOFT_REST);
	
	Delay_MS(60);
	
	QMC5883L_WriteByte(QMC5883L_ADDR_PERIORC, QMC_PERIORC_VALUE);
	
	QMC5883L_WriteByte(QMC5883L_ADDR_CFGC, QMC_CFGC_VALUE);
	QMC5883L_WriteByte(QMC5883L_ADDR_CFGD, QMC_CFGD_VALUE);
	
	/* 64滤波, 8高斯范围, 200Hz输出, 初始化为StandBy */
	QMC5883L_WriteByte(QMC5883L_CR1, QMC_OSR_64 | QMC_RANGE_8G | QMC_RATES_200HZ | QMC_MODE_STANDBY);
	/* 引脚中断使能, 数据读取完指针自动偏转失能 */
	QMC5883L_WriteByte(QMC5883L_CR2, QMC_INT_ENABLE | QMC_POINT_ROLL_DISABLE);
}

/**********************************************************************************************************
 @Function			void QMC5883L_ReadData_Temperature(u16* vtemp)
 @Description			QMC5883L读取温度
 @Input				vtemp
 @Return				void
**********************************************************************************************************/
void QMC5883L_ReadData_Temperature(u16* vtemp)
{
	u8 temp_l = 0, temp_h = 0;
	
	temp_l = QMC5883L_ReadByte(QMC_TEMPERATURE_L);
	temp_h = QMC5883L_ReadByte(QMC_TEMPERATURE_H);
	
	*vtemp = ((u16)(temp_h << 8) | (u16)(temp_l << 0));
}

/********************************************** END OF FLEE **********************************************/
