#ifndef __HC32L19X_CONFIG_H
#define   __HC32L19X_CONFIG_H

#include "sys.h"
#include "gpio.h"
#include "reset.h"
#include "lpm.h"

#define HC32_MODEL_POWER_SET		MODEL_POWER_IO_SET
#define HC32_MODEL_POWER_GET		MODEL_POWER_IO_GET
#define HC32_RADAR_POWER_SET		RADAR_POWER_IO_SET
#define HC32_RADAR_POWER_GET		RADAR_POWER_IO_GET
#define HC32_NBIOT_POWER_SET		NBIOT_POWER_IO_SET
#define HC32_NBIOT_POWER_GET		NBIOT_POWER_IO_GET
#define HC32_VBATE_POWER_SET		VBATE_POWER_IO_SET
#define HC32_VBATE_POWER_GET		VBATE_POWER_IO_GET

#define MODEL_POWER_GPIOx		GpioPortA
#define MODEL_POWER_PIN			GpioPin8
#define MODEL_POWER_IO_SET(n)		(n ? (Gpio_ClrIO(MODEL_POWER_GPIOx, MODEL_POWER_PIN)) : (Gpio_SetIO(MODEL_POWER_GPIOx, MODEL_POWER_PIN)))
#define MODEL_POWER_IO_GET()		(Gpio_ReadOutputIO(MODEL_POWER_GPIOx, MODEL_POWER_PIN))

#define RADAR_POWER_GPIOx		GpioPortB
#define RADAR_POWER_PIN			GpioPin3
#define RADAR_POWER_IO_SET(n)		(n ? (Gpio_SetIO(RADAR_POWER_GPIOx, RADAR_POWER_PIN)) : (Gpio_ClrIO(RADAR_POWER_GPIOx, RADAR_POWER_PIN)))
#define RADAR_POWER_IO_GET()		(Gpio_ReadOutputIO(RADAR_POWER_GPIOx, RADAR_POWER_PIN))

#define NBIOT_POWER_GPIOx		GpioPortA
#define NBIOT_POWER_PIN			GpioPin0
#define NBIOT_POWER_IO_SET(n)		(n ? (Gpio_SetIO(NBIOT_POWER_GPIOx, NBIOT_POWER_PIN)) : (Gpio_ClrIO(NBIOT_POWER_GPIOx, NBIOT_POWER_PIN)))
#define NBIOT_POWER_IO_GET()		(Gpio_ReadOutputIO(NBIOT_POWER_GPIOx, NBIOT_POWER_PIN))

#define VBATE_POWER_GPIOx		GpioPortA
#define VBATE_POWER_PIN			GpioPin12
#define VBATE_POWER_IO_SET(n)		(n ? (Gpio_ClrIO(VBATE_POWER_GPIOx, VBATE_POWER_PIN)) : (Gpio_SetIO(VBATE_POWER_GPIOx, VBATE_POWER_PIN)))
#define VBATE_POWER_IO_GET()		(Gpio_ReadOutputIO(VBATE_POWER_GPIOx, VBATE_POWER_PIN))


























typedef enum
{
	WORK_MODE_NORMAL			= 0x00,
	WORK_MODE_DEBUG			= 0x01,
	WORK_MODE_STANDBY			= 0x03,
	WORK_MODE_IDLE				= 0x04,
} HC32_WORK_MODE_TypeDef;																//工作模式

typedef enum
{
	IDLE_MODE_DISABLE			= 0x01,
	IDLE_MODE_ENABLE			= 0x02,
} HC32_IDLE_MODE_TypeDef;																//休眠模式

typedef enum
{
	ACTIVE_MODE_DISABLE			= 0x01,
	ACTIVE_MODE_ENABLE			= 0x02,
} HC32_ACTIVE_MODE_TypeDef;																//运行模式

typedef enum
{
	SENSE_HIGHEST				= 0x01,
	SENSE_HIGH				= 0x02,
	SENSE_MIDDLE				= 0x03,
	SENSE_LOW					= 0x04,
	SENSE_LOWEST				= 0x05,
} HC32_SENSITIVITY_MODE_TypeDef;															//传感器灵敏度

typedef enum
{
	REBOOT_MODE_NONE			= 0x00,
	REBOOT_MODE_SYS_OVERTIME		= 0x01,
	REBOOT_MODE_CMD_RADIO		= 0x02,
	REBOOT_MODE_CMD_COAP		= 0x03,
	REBOOT_MODE_CMD_MQTT		= 0x04,
	REBOOT_MODE_UPGRADE_RADIO	= 0x05,
	REBOOT_MODE_UPGRADE_COAP		= 0x06,
	REBOOT_MODE_UPGRADE_MQTT		= 0x07,
	REBOOT_MODE_NBIOT_HDRBT		= 0x08,
	REBOOT_MODE_NBIOT_CONNECT	= 0x09,
} HC32_REBOOT_MODE_TypeDef;																//设备重启方式

typedef enum
{
	RCC_RESET_FLAG_NONE			= 0x00,													/*!< None Reset Flag				*/
	RCC_RESET_FLAG_IWDGRST		= 0x01,													/*!< Independent Watchdog Reset Flag	*/
	RCC_RESET_FLAG_SFTRST		= 0x02,													/*!< Software Reset Flag				*/
	RCC_RESET_FLAG_PORRST		= 0x04,													/*!< POR/PDR Reset Flag				*/
	RCC_RESET_FLAG_PINRST		= 0x08,													/*!< PIN Reset Flag					*/
	RCC_RESET_FLAG_LPWRRST		= 0x03,													/*!< Low-Power Reset Flag			*/
	RCC_RESET_FLAG_PCA			= 0x05,													/*!< Options Bytes Loading Reset Flag	*/
	RCC_RESET_FLAG_LOCKUP		= 0x09,													/*!< CPU Lockup Reset Flag			*/
} HC32_RESET_FLAG_TypeDef;

extern HC32_RESET_FLAG_TypeDef HC32_Reset_Flag;												//HC32系统复位标志

HC32_RESET_FLAG_TypeDef HC32_SystemReset_GetStatus(void);										//HC32获取复位标志位

void HC32_System_Software_Reboot(HC32_REBOOT_MODE_TypeDef mode);									//HC32软件重启

void HC32_PeripheralAll_Reset(void);														//HC32外设模块复位

void HC32_LowPowerIO_Init(void);															//HC32低功耗IO初始化
void HC32_RstPowerIO_Init(void);															//HC32复位电源初始化
void HC32_CtrPowerIO_Init(void);															//HC32控制电源初始化

void HC32_AutomaticSystem_Check(void);														//HC32系统自检







void HC32_LowPower_SleepBefor_Init(void);													//进入低功耗stop模式之前初始化
void HC32_LowPower_SleepEnter_Stop(void);													//进入低功耗stop模式
void HC32_LowPower_SleepAfter_Init(void);													//进入低功耗stop模式之后初始化

void HC32_LowPower_Sleep_Task(void);														//HC32低功耗处理





















#endif /* __HC32L19X_CONFIG_H */
