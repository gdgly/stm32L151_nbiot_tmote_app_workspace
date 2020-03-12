#ifndef __HAL_QMC5883L_H
#define   __HAL_QMC5883L_H

#include "sys.h"
#include "gpio.h"
#include "hal_i2c.h"

#define QMC_DRDY_GPIOx			GpioPortA
#define QMC_DRDY_PIN			GpioPin11
#define QMC_DRDY_READ()			(Gpio_GetInputIO(QMC_DRDY_GPIOx, QMC_DRDY_PIN))

#define QMC_I2C_INTERFACE0		0
#define QMC_I2C_INTERFACE1		1
#define QMC_I2C_INTERFACE		QMC_I2C_INTERFACE0

#define QMC_I2C_0				M0P_I2C0
#define QMC_I2C_1				M0P_I2C1
#if QMC_I2C_INTERFACE == QMC_I2C_INTERFACE0
#define QMC_I2C_TYPE			QMC_I2C_0
#endif
#if QMC_I2C_INTERFACE == QMC_I2C_INTERFACE1
#define QMC_I2C_TYPE			QMC_I2C_1
#endif

#define QMC5883L_SLAVE_ADDRESS_W	0x1A														//I2C从机地址写
#define QMC5883L_SLAVE_ADDRESS_R	0x1B														//I2C从机地址读

#define QMC_DATA_OUT_X_L			0x00														//X轴数据低8位
#define QMC_DATA_OUT_X_H			0x01														//X轴数据高8位
#define QMC_DATA_OUT_Y_L			0x02														//Y轴数据低8位
#define QMC_DATA_OUT_Y_H			0x03														//Y轴数据高8位
#define QMC_DATA_OUT_Z_L			0x04														//Z轴数据低8位
#define QMC_DATA_OUT_Z_H			0x05														//Z轴数据高8位

#define QMC_READY_BIT			0x06														//bit0 = 0 : No new data; bit0 = 1 : have new data.

#define QMC_TEMPERATURE_L		0x07														//内部温度数据低8位
#define QMC_TEMPERATURE_H		0x08														//内部温度数据高8位

#define QMC5883L_CR1			0x09														//QMC5883L控制寄存器1
#define QMC_MODE_STANDBY			(0<<0)													//休眠
#define QMC_MODE_CONTINOUS		(1<<0)													//连续测量
#define QMC_RATES_10HZ			(0<<2)													//数据输出速率10Hz
#define QMC_RATES_50HZ			(1<<2)													//数据输出速率50Hz
#define QMC_RATES_100HZ			(2<<2)													//数据输出速率100Hz
#define QMC_RATES_200HZ			(3<<2)													//数据输出速率200Hz
#define QMC_RANGE_2G			(0<<4)													//测量范围 +-2高斯
#define QMC_RANGE_8G			(1<<4)													//测量范围 +-8高斯
#define QMC_OSR_512				(0<<6)													//内置滤波器带宽,大的带宽能让噪音更小,但是相应功耗更大
#define QMC_OSR_256				(1<<6)
#define QMC_OSR_128				(2<<6)
#define QMC_OSR_64				(3<<6)

#define QMC5883L_CR2			0x0A														//QMC5883L控制寄存器2
#define QMC_INT_ENABLE			(0<<0)													//引脚中断使能
#define QMC_INT_DISABLE			(1<<0)													//引脚中断失能
#define QMC_POINT_ROLL_ENABLE		(1<<6)													//数据读取完指针自动偏转使能
#define QMC_POINT_ROLL_DISABLE	(0<<6)													//数据读取完指针自动偏转失能
#define QMC_SOFT_REST			(1<<7)													//软件复位

#define QMC_REG_MAG				6														//地磁数据寄存器

void QMC5883L_Init(void);

void QMC5883L_Drdy_Init(void);
void QMC5883L_Drdy_DeInit(void);

void QMC5883L_Discharge(void);

void QMC5883L_ClearInsideData(void);														//QMC5883L清除内部待读取数据缓存
void QMC5883L_Mode_Selection(u8 mode);														//QMC5883L工作模式选择
void QMC5883L_Rates_Selection(u8 rates);													//QMC5883L数据输出速率选择
void QMC5883L_Rates_Selection_Freq(u8 Freq);													//QMC5883L数据输出速率选择
void QMC5883L_Range_Selection(u8 range);													//QMC5883L测量范围选择
void QMC5883L_Osr_Selection(u8 osr);														//QMC5883L内置滤波器带宽选择
void QMC5883L_Interrupt_Selection(u8 interrupt);												//QMC5883L引脚中断选择
void QMC5883L_Softwart_Reset(void);														//QMC5883L复位











#endif /* __HAL_QMC5883L_H */
