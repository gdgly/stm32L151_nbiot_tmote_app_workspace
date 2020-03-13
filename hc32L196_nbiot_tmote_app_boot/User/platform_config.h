#ifndef __PLATFORM_CONFIG_H
#define   __PLATFORM_CONFIG_H

#include "sys.h"

//#define	MVB_SUBSN						0x81011000										//设备号
//#define	MVB_BRAND						"mvb"											//厂牌名

#define	CPUVERSION					"HC32L196JC"										//处理器型号

#define	MVB_STATICMAGNETIC_MODEL			51
#define	MVB_FLOWMAGNETIC_MODEL			52
#define	MVB_SPOT_LOCKER_MODEL			53
#define	MVB_BARRIER_MODEL				54
#define	MVB_MODEL_TYPE					MVB_STATICMAGNETIC_MODEL								//设备类型

#define	SYSTEM_CLOCK_XTH				32000000
#define	SYSTEM_CLOCK_RCH				48000000
#define	SYSTEM_CLOCK_TYPE				SYSTEM_CLOCK_RCH									//系统时钟

#define	SYSTEM_RTCCLOCK_XTL_32768		32768
#define	SYSTEM_RTCCLOCK_RCL_32000		32000
#define	SYSTEM_RTCCLOCK_RCL_38400		38400
#define	SYSTEM_RTCCLOCK_TYPE			SYSTEM_RTCCLOCK_RCL_32000							//实时时钟

#define	SYSTEM_RESETFLAG_DISABLE			0
#define	SYSTEM_RESETFLAG_ENABLE			1
#define	SYSTEM_RESETFLAG_TYPE			SYSTEM_RESETFLAG_DISABLE								//系统复位获取

#define	SYSTEM_PERIPHERAL_GATE_WDT		1												//Wdt
#define	SYSTEM_PERIPHERAL_GATE_TICK		1												//SysTick
#define	SYSTEM_PERIPHERAL_GATE_FLASH		1												//Flash
#define	SYSTEM_PERIPHERAL_GATE_RTC		1												//RTC
#define	SYSTEM_PERIPHERAL_GATE_GPIO		1												//GPIO
#define	SYSTEM_PERIPHERAL_GATE_UART0		1												//Uart0
#define	SYSTEM_PERIPHERAL_GATE_UART1		1												//Uart1
#define	SYSTEM_PERIPHERAL_GATE_I2C0		0												//I2C0
#define	SYSTEM_PERIPHERAL_GATE_I2C1		0												//I2C1
#define	SYSTEM_PERIPHERAL_GATE_ADC		1												//ADC














#endif /* __PLATFORM_CONFIG_H */