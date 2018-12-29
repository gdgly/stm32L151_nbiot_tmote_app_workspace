// tmesh_cfg.h:  created at 2017-6-13 by Bell Zhong
//                zbd-note:
#ifndef TMESH_CFG_H_INCLUDED
#define TMESH_CFG_H_INCLUDED

#include "stm32l1xx_hal.h"
#include <stdbool.h>

#define	SYSTEMCLOCKMSI					4194000
#define	SYSTEMCLOCKHSI					32000000
#define	SYSTEMCLOCK					SYSTEMCLOCKHSI

#define APP_LOWEST_ADDRESS		0x08003800

#define BOOT_VERSION	31

#define EEPROM_BASE_ADDRESS		0x08080000
#define EEPROM_CONFIG_OFFSET	0x08080000
#define EEPROM_CONFIG_SIZE				0x0100



#define TCFG_FACTORY_BRAND_SN_OFFSET	0x400
#define TCFG_FACTORY_BRAND_SN_LENGTH	8

/* the environment parameters are used both by bootLoader and application */
#define TCFG_ENVFLAG_OFFSET				TCFG_FACTORY_BRAND_SN_OFFSET + TCFG_FACTORY_BRAND_SN_LENGTH
#define TCFG_ENVFLAG_LENGTH				4	//"TCLD"
#define TCFG_ENV_BOOTMODE_OFFSET		TCFG_ENVFLAG_OFFSET + TCFG_ENVFLAG_LENGTH
#define TCFG_ENV_BOOTMODE_LENGTH		1	//boot app from flash or load app from air
// end---------------------------------------------------------------------

#define TCFG_HEADFLAG_OFFSET			TCFG_ENV_BOOTMODE_OFFSET + TCFG_ENV_BOOTMODE_LENGTH
#define TCFG_HEADFLAG_LENGTH			4	//"TCLD"
#define TCFG_SN_OFFSET					TCFG_HEADFLAG_OFFSET + TCFG_HEADFLAG_LENGTH
#define TCFG_SN_LENGTH					4
#define TCFG_SPOTID_OFFSET				TCFG_SN_OFFSET + TCFG_SN_LENGTH
#define TCFG_SPOTID_LENGTH				16
#define TCFG_HEARTINTERVAL_OFFSET		TCFG_SPOTID_OFFSET + TCFG_SPOTID_LENGTH
#define TCFG_HEARTINTERVAL_LENGTH		2
#define TCFG_MAG_SENSITIVITY_OFFSET		TCFG_HEARTINTERVAL_OFFSET + TCFG_HEARTINTERVAL_LENGTH
#define TCFG_MAG_SENSITIVITY_LENGTH		1
#define TCFG_MAG_FREQ_OFFSET			TCFG_MAG_SENSITIVITY_OFFSET + TCFG_MAG_SENSITIVITY_LENGTH
#define TCFG_MAG_FREQ_LENGTH			1

#define TCFG_MAGFLAG_OFFSET				TCFG_MAG_FREQ_OFFSET+TCFG_MAG_FREQ_LENGTH
#define TCFG_MAGFLAG_LENGTH				1	//"T" = 0x54
#define TCFG_MAG_BACK_X_OFFSET			TCFG_MAGFLAG_OFFSET+TCFG_MAGFLAG_LENGTH
#define TCFG_MAG_BACK_X_LENGTH			2
#define TCFG_MAG_BACK_Y_OFFSET			TCFG_MAG_BACK_X_OFFSET + TCFG_MAG_BACK_X_LENGTH
#define TCFG_MAG_BACK_Y_LENGTH			2
#define TCFG_MAG_BACK_Z_OFFSET			TCFG_MAG_BACK_Y_OFFSET + TCFG_MAG_BACK_Y_LENGTH
#define TCFG_MAG_BACK_Z_LENGTH			2

#define TCFG_SECUFLAG_OFFSET			TCFG_MAG_BACK_Z_OFFSET + TCFG_MAG_BACK_Z_LENGTH
#define TCFG_SECUFLAG_LENGTH			1	//"T" = 0x54
#define TCFG_SECU_BRAND_OFFSET			TCFG_SECUFLAG_OFFSET+TCFG_SECUFLAG_LENGTH
#define TCFG_SECU_BRAND_LENGTH			6
#define TCFG_SECU_BRANDKEY_OFFSET		TCFG_SECU_BRAND_OFFSET + TCFG_SECU_BRAND_LENGTH
#define TCFG_SECU_BRANDKEY_LENGTH		32
#define TCFG_SECU_BRANCHKEY_OFFSET		TCFG_SECU_BRANDKEY_OFFSET + TCFG_SECU_BRANDKEY_LENGTH
#define TCFG_SECU_BRANCHKEY_LENGTH		32

#define TCFG_RECORD_RUNTIME_OFFSET		TCFG_SECU_BRANCHKEY_OFFSET + TCFG_SECU_BRANCHKEY_LENGTH
#define TCFG_RECORD_RUNTIME_LENGTH		4

#define TCFG_RECORD_BOOTCNT_OFFSET      TCFG_RECORD_RUNTIME_OFFSET + TCFG_RECORD_RUNTIME_LENGTH
#define TCFG_RECORD_BOOTCNT_LENGTH      1

#define	TCFG_APP_ENV0_OFFSET		(TCFG_RECORD_BOOTCNT_OFFSET+TCFG_RECORD_BOOTCNT_LENGTH)
//#define	TCFG_APP_ENV0_OFFSET		0x80
#define TCFG_APP_ENV0_ADDRESS		(EEPROM_BASE_ADDRESS + TCFG_APP_ENV0_OFFSET)	//参数区域0	0x6800
#define TCFG_APP_ENV0_SIZE   		24
#define	TCFG_APP_ENV1_OFFSET		(TCFG_APP_ENV0_OFFSET+TCFG_APP_ENV0_SIZE)
#define TCFG_APP_ENV1_ADDRESS		(EEPROM_BASE_ADDRESS + TCFG_APP_ENV1_OFFSET)	//参数区域0
#define TCFG_APP_ENV1_SIZE   		24

#define TCFG_RECORD_SERVER_OFFSET		TCFG_APP_ENV1_OFFSET+TCFG_APP_ENV1_SIZE
#define TCFG_RECORD_SERVER_LENGTH		6
#define TCFG_WORKMODE_OFFSET		TCFG_RECORD_SERVER_OFFSET+TCFG_RECORD_SERVER_LENGTH
#define TCFG_WORKMODE_LENGTH		1
#define TCFG_RADARCOUNT_OFFSET		TCFG_WORKMODE_OFFSET+TCFG_WORKMODE_LENGTH
#define TCFG_RADARCOUNT_LENGTH		4
#define TCFG_RADARDBG_OFFSET		TCFG_RADARCOUNT_OFFSET+TCFG_RADARCOUNT_LENGTH
#define TCFG_RADARDBG_LENGTH		1
#define TCFG_STATUSCNT_OFFSET		TCFG_RADARDBG_OFFSET+TCFG_RADARDBG_LENGTH
#define TCFG_STATUSCNT_LENGTH		1
#define TCFG_RFCHANNEL_OFFSET		TCFG_STATUSCNT_OFFSET+TCFG_STATUSCNT_LENGTH
#define TCFG_RFCHANNEL_LENGTH		1




#define FLASH_APP_OFFSET    0x08002000
#define FLASH_APP_SIZE      128*1024//0x100000
#define FLASH_APP0_OFFSET   FLASH_APP_OFFSET
#define FLASH_APP0_SIZE     FLASH_APP_SIZE
#define FLASH_APP1_OFFSET   (FLASH_APP0_OFFSET + FLASH_APP0_SIZE)
#define FLASH_APP1_SIZE     (FLASH_APP0_SIZE)


#define TCFG_FLAGTYPE_GENERAL		0
#define TCFG_FLAGTYPE_MAGAlGORITHM	1
#define TCFG_FLAGTYPE_SECU		2

#define TCFG_ENV_BOOTMODE_TOUPDATE			1
#define TCFG_ENV_BOOTMODE_NORMAL			2
#define TCFG_ENV_BOOTMODE_UPDATING			3
#define TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE	4


#define SYSTEM_ENV_FLAG     0x53454E56
#define SYSTEM_ENV_VERSION  0x00000001



#define TCFG_X_AXIS						0
#define TCFG_Y_AXIS						1
#define TCFG_Z_AXIS						2




enum TCFG_SENSITIVITY
{
	SENSE_HIGHEST = 1,
	SENSE_HIGH,
	SENSE_MIDDLE,
	SENSE_LOW,
	SENSE_LOWEST,
};

//struct declare-----------------------------
typedef struct _Tcfg_Device_INFO
{
    uint32_t	sn;	//地磁检测灵敏度
    char	spotid[TCFG_SPOTID_LENGTH];	//车位编号
} Tcfg_Device_Info;

typedef struct _GCONFIG_RF_INFO
{
    uint16_t	heartinterval;	//心跳间隔,单位秒
} GCONFIG_RF_INFO;

typedef struct _Tcfg_MagSensor_Info
{
    uint8_t	sensitivity;	//地磁检测灵敏度
    uint8_t	frequency;	//地磁检测频率,单位Hz
} Tcfg_MagSensor_Info;

typedef struct _Tcfg_Algorithm_Mag
{
    uint8_t flag;	//'T' means the backgroud is set
    int16_t x_back;		//2B
    int16_t y_back;		//2B
    int16_t z_back;		//2B
    uint8_t status; //传感器状态
} Tcfg_Algorithm_Mag;

typedef struct _Tcfg_Secu
{
    char brand[6];	//2B
    char brandkey[32];	//2B
    int16_t branchkey[32];	//2B
} Tcfg_Secu;

typedef __packed struct _tcfg_server
{
	__packed union
	{
		uint8_t ip8[4];
		uint32_t ip32;
	}ip;
	uint16_t port;
} tcfg_server_s;
//end-------------------------------------



// function declare------------------------------------------
void tcfg_Init(void);
bool tcfg_CheckInfoBurned(void);
uint32_t tcfg_GetSNfromBrandKey(void);
void tcfg_SetBootMode(char bootmode);
uint16_t tcfg_GetMagBackgroud(char axis);
void tcfg_SetMagBackgroud(int16_t x_axis,int16_t y_axis,int16_t z_axis);
uint8_t tcfg_ReadSavedSensitivity(void);
void tcfg_SetSavedSensitivity(uint8_t data);
uint8_t tcfg_getMagFreq(void);
void tcfg_setMagFreq(uint8_t freq);
void tcfg_SetHeartinterval(uint16_t data);
uint16_t tcfg_GetHeartinterval(void);
void tcfg_GetSpotID(char* outbuf);
void tcfg_SetSpotID(char* inbuf);
uint32_t tcfg_GetSubSN(void);
void tcfg_SetSubSN(uint32_t subsn);
uint8_t tcfg_GetBootCount(void);
void tcfg_SetBootCount(uint8_t count);
uint32_t tcfg_GetFactoryBrand(void);

uint32_t tcfg_GetBrandCode(void);

void tcfg_SetBrandCode(uint32_t brand);

void TFLASH_ReadBuffer(uint32_t Address,uint8_t* outbuf,uint8_t outlen);
void TFLASH_WriteBuffer(uint32_t Address,uint8_t* inbuf,uint8_t inlen);
uint8_t tcfg_GetSensitivity(void);
uint8_t tcfg_utility_get_major_softnumber(void);
uint8_t tcfg_utility_get_sub_softnumber(void);
uint32_t tcfg_GetServerIP(void);
void tcfg_SetServerIP(uint32_t val);
uint16_t tcfg_GetServerPort(void);
void tcfg_SetServerPort(uint16_t val);
uint8_t tcfg_GetWorkMode(void);
void tcfg_SetWorkMode(uint8_t val);
uint32_t tcfg_ReadRadarCount(void);
void tcfg_WriteRadarCount(uint32_t val);
uint32_t tcfg_GetRadarCount(void);
void tcfg_AddRadarCount(void);
void TFLASH_WriteWord(uint32_t Address, uint32_t Data);
uint8_t tcfg_ReadRadarDbgMode(void);
void tcfg_WriteRadarDbgMode(uint8_t val);
uint32_t tcfg_ReadStatusCntDbgMode(void);
void tcfg_WriteStatusCntMode(uint32_t val);
uint8_t tcfg_ReadRfChannel(void);
void tcfg_WriteRfChannel(uint8_t val);
char tcfg_GetBootMode(void);
// end----------------------------------------------------




#endif



