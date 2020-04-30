#ifndef __HAL_IST8310M_H
#define   __HAL_IST8310M_H

#include "sys.h"
#include "gpio.h"
#include "hal_iic.h"

#define IST_DRDY_GPIOx			GpioPortA
#define IST_DRDY_PIN			GpioPin11
#define IST_DRDY_READ()			(Gpio_GetInputIO(IST_DRDY_GPIOx, IST_DRDY_PIN))

#define IST8310M_SLAVE_ADDRESS_W	0x1C														//I2C从机地址写
#define IST8310M_SLAVE_ADDRESS_R	0x1D														//I2C从机地址读

#define IST8310M_REG_WIA			(0x00)													//Who I am

#define IST8310M_REG_STAT1		(0x02)													//Status Register 1
#define IST_STAT1_DRDY			(1<<0)													//R/O (0: data not ready 1: data ready)
#define IST_STAT1_DOR			(1<<1)													//R/O (0: no data overrun 1: data overrun)

#define IST8310M_REG_STAT2		(0x09)													//Status Register 2
#define IST_STAT2_INT			(1<<3)													//R/O (Interrupt bit)

#define IST8310M_DATA_OUT_X_L		(0x03)													//X轴数据低8位
#define IST8310M_DATA_OUT_X_H		(0x04)													//X轴数据高8位
#define IST8310M_DATA_OUT_Y_L		(0x05)													//Y轴数据低8位
#define IST8310M_DATA_OUT_Y_H		(0x06)													//Y轴数据高8位
#define IST8310M_DATA_OUT_Z_L		(0x07)													//Z轴数据低8位
#define IST8310M_DATA_OUT_Z_H		(0x08)													//Z轴数据高8位

#define IST8310M_REG_CNTRL1		(0x0A)													//Control Register 1
#define IST_CNTRL1_MODE_STANDBY	(0<<0)													//R/W (休眠模式)
#define IST_CNTRL1_MODE_SINGLE	(1<<0)													//R/W (单次测量模式)

#define IST8310M_REG_CNTRL2		(0x0B)													//Control Register 2
#define IST_CNTRL2_SOFT_REST		(1<<0)													//R/W (软件复位)
#define IST_CNTRL2_DRP_LOW		(0<<2)													//R/W (DRDY引脚低电平有效)
#define IST_CNTRL2_DRP_HIGH		(1<<2)													//R/W (DRDY引脚高电平有效)
#define IST_CNTRL2_DREN_DISABLE	(0<<3)													//R/W (DRDY引脚输出失能)
#define IST_CNTRL2_DREN_ENABLE	(1<<3)													//R/W (DRDY引脚输出使能)

#define IST8310M_REG_CNTRL3		(0x0D)													//Control Register 3
#define IST_CNTRL3_14BLSB_GAUSS_X	(0<<4)													//R/W (X轴输出分辨率14B)
#define IST_CNTRL3_16BLSB_GAUSS_X	(1<<4)													//R/W (X轴输出分辨率16B)
#define IST_CNTRL3_14BLSB_GAUSS_Y	(0<<5)													//R/W (Y轴输出分辨率14B)
#define IST_CNTRL3_16BLSB_GAUSS_Y	(1<<5)													//R/W (Y轴输出分辨率16B)
#define IST_CNTRL3_14BLSB_GAUSS_Z	(0<<6)													//R/W (Z轴输出分辨率14B)
#define IST_CNTRL3_16BLSB_GAUSS_Z	(1<<6)													//R/W (Z轴输出分辨率16B)

#define IST8310M_REG_STR			(0x0C)													//For Self-Test Mode
#define IST_STR_ENTER_SELFTEST	(1<<6)													//R/W (自检模式)

#define IST8310M_REG_TEMPERATURE_L	(0x1C)													//内部温度数据低8位
#define IST8310M_REG_TEMPERATURE_H	(0x1D)													//内部温度数据高8位

#define IST8310M_REG_TCCNTL		(0x40)													//To Enable/Disable Temperature
#define IST_TCCNTL_TEMPER_DISABLE	(1<<0)													//R/W (失能内部温度传感器)
#define IST_TCCNTL_TEMPER_ENABLE	(0<<0)													//R/W (使能内部温度传感器)

#define IST8310M_REG_AVGCNTL		(0x41)													//Average Control register
#define IST_AVGCNTL_2TIMES_XZ		(1<<0)
#define IST_AVGCNTL_4TIMES_XZ		(2<<0)
#define IST_AVGCNTL_8TIMES_XZ		(3<<0)
#define IST_AVGCNTL_16TIMES_XZ	(4<<0)
#define IST_AVGCNTL_2TIMES_Y		(1<<3)
#define IST_AVGCNTL_4TIMES_Y		(2<<3)
#define IST_AVGCNTL_8TIMES_Y		(3<<3)
#define IST_AVGCNTL_16TIMES_Y		(4<<3)

#define IST8310M_REG_PDCNTL		(0x42)													//Pulse Duration Control
#define IST_PDCNTL_LONG			(1<<6)													//R/W (Long)
#define IST_PDCNTL_NORMAL		(3<<6)													//R/W (Normal)

#define IST_REG_MAG				6														//地磁数据寄存器
#define IST_DEVIATION_MAX		900														//最大跳变值
#define IST_SAMPLE_TIMES			3														//采样次数
#define IST_SAMEERR_COUNT		60														//异常次数

void IST8310M_Init(void);																//IST8310M初始化

void IST8310M_Drdy_Init(void);															//IST8310M数据读取状态引脚初始化
void IST8310M_Drdy_DeInit(void);															//IST8310M数据读取状态引脚反初始化

void IST8310M_Discharge(void);															//IST8310M硬复位

void IST8310M_ClearInsideData(void);														//IST8310M清除内部待读取数据缓存
void IST8310M_Mode_Selection(u8 mode);														//IST8310M工作模式选择
void IST8310M_Drdy_Polarity(u8 polarity);													//IST8310M引脚有效电平
void IST8310M_Drdy_Enable(u8 enable);														//IST8310M引脚输出选择
void IST8310M_Temperature_Enable(u8 enable);													//IST8310M温度传感器输出选择
void IST8310M_Softwart_Reset(void);														//IST8310M软复位

void IST8310M_ReadData_Simplify(short* x, short* y, short* z);									//IST8310M读取数据
void IST8310M_ReadData_Extended(short* x, short* y, short* z);									//IST8310M读取数据
void IST8310M_ReadData_Stronges(short* x, short* y, short* z);									//IST8310M读取数据

void IST8310M_ReadData_Temperature(u16* vtemp);												//IST8310M读取温度

#endif /* __HAL_IST8310M_H */
