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

#define	SYSTEM_CLOCK_XTH_24M			24000000
#define	SYSTEM_CLOCK_RCH_16M			16000000
#define	SYSTEM_CLOCK_RCH_32M			32000000
#define	SYSTEM_CLOCK_RCH_48M			48000000
#define	SYSTEM_CLOCK_TYPE				SYSTEM_CLOCK_RCH_16M								//系统时钟

#define	SYSTEM_RTCCLOCK_XTL_32768		32768
#define	SYSTEM_RTCCLOCK_RCL_32000		32000
#define	SYSTEM_RTCCLOCK_RCL_38400		38400
#define	SYSTEM_RTCCLOCK_TYPE			SYSTEM_RTCCLOCK_RCL_32000							//实时时钟

#define	SYSTEM_LOWPOWER_DISABLE			0
#define	SYSTEM_LOWPOWER_ENABLE			1
#define	SYSTEM_LOWPOWER_TYPE			SYSTEM_LOWPOWER_DISABLE								//低功耗模式

#define	SYSTEM_RESETFLAG_DISABLE			0
#define	SYSTEM_RESETFLAG_ENABLE			1
#define	SYSTEM_RESETFLAG_TYPE			SYSTEM_RESETFLAG_ENABLE								//系统复位获取



























#define	SYSTEM_PERIPHERAL_GATE_TICK		TRUE												//SysTick
#define	SYSTEM_PERIPHERAL_GATE_GPIO		TRUE												//GPIO
#define	SYSTEM_PERIPHERAL_GATE_WDT		TRUE												//Wdt
#define	SYSTEM_PERIPHERAL_GATE_RTC		TRUE												//RTC
#define	SYSTEM_PERIPHERAL_GATE_FLASH		TRUE												//Flash
#define	SYSTEM_PERIPHERAL_GATE_UART0		TRUE												//Uart0
#define	SYSTEM_PERIPHERAL_GATE_UART1		TRUE												//Uart1
#define	SYSTEM_PERIPHERAL_GATE_I2C0		FALSE											//I2C0
#define	SYSTEM_PERIPHERAL_GATE_I2C1		FALSE											//I2C1
#define	SYSTEM_PERIPHERAL_GATE_SPI0		TRUE												//SPI0
#define	SYSTEM_PERIPHERAL_GATE_SPI1		TRUE												//SPI1
#define	SYSTEM_PERIPHERAL_GATE_ADC		FALSE											//ADC
#define	SYSTEM_PERIPHERAL_GATE_AES		FALSE											//AES
#define	SYSTEM_PERIPHERAL_GATE_CRC		FALSE											//CRC






















#define	FLASH_HC32NOR																	//定义开启 FLASH_HC32NOR
#define	EPROM_BL24CXX																	//定义开启 EPROM BL24CXX
#define	FLASH_P25QXXH																	//定义开启 FLASH P25QXXH
#define	RADIO_SI4438A																	//定义开启 RADIO SI4438A

#define	RADIO_RF_CHANNEL1				36												//小无线默认通道















#define	MVB_BOOT_SOFTWARE_MAJOR			0												//Boot 主固件版本
#define	MVB_BOOT_SOFTWARE_SUB			40												//Boot 从固件版本
#define	MVB_BOOT_HARDWARE_V1			2												//Boot 主硬件版本
#define	MVB_BOOT_HARDWARE_V2			12												//Boot 主硬件版本

#define	MVB_APPL_SOFTWARE_MAJOR			20												//App  主固件版本
#define	MVB_APPL_SOFTWARE_SUB			100												//App  从固件版本
#define	MVB_APPL_HARDWARE_V1			2												//App  主硬件版本
#define	MVB_APPL_HARDWARE_V2			12												//App  主硬件版本




















#define	USART0_DISABLE					0
#define	USART0_ENABLE					1
#define	USART0_TYPE					USART0_ENABLE										//串口0状态

#define	USART1_DISABLE					0
#define	USART1_ENABLE					1
#define	USART1_TYPE					USART1_ENABLE										//串口1状态


































#endif /* __PLATFORM_CONFIG_H */
