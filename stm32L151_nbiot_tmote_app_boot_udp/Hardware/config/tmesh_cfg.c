/*============================================================================
* Module Name: tmesh_cfg.c
* Purpose:
* Author:   Bell Zhong
* Date:        2017-6-13
* Notes:
*
*=============================================================================
*/

#include "tmesh_cfg.h"
#include "stm32l1xx_hal.h"
//#include "bsp.h"
#include "string.h"
//#include "xm_device_variable.h"


// variable declare--------------------------------------------------------------
uint32_t g_SubSn ;//sequence number
uint8_t g_magSkitNum = 0;// measure every g_magSkitNum drdys
uint16_t g_heartinterval;
// end------------------------------------------------------------------------

// function declare--------------------------------------------------------------
bool tcfg_CheckHeadFlag(char flagtype);
uint32_t TFLASH_ReadWord(uint32_t Address);
uint16_t TFLASH_ReadHalfWord(uint32_t Address);
void TFLASH_ReadBuffer(uint32_t Address,uint8_t* outbuf,uint8_t outlen);
void TFLASH_WriteBuffer(uint32_t Address,uint8_t* inbuf,uint8_t inlen);
void tcfg_ReadConfigData(void);
void tcfg_SaveConfigToEeprom(void);
// end------------------------------------------------------------------------

uint8_t FLASH_ReadByte(uint32_t Address)
{
	return *(__IO uint8_t*)(Address);//STMFLASH_ReadByte(ReadAddr++);  
}

HAL_StatusTypeDef   testStatus;
void FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{	
	testStatus = HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEERASEDATA_BYTE, Address, Data);
}

uint32_t tmesh_Generate_Random(void)
{
	return 0;
}
/*
* ----------------------------------------------------------------------------
* Function Name: tcfg_Init
* Purpose: Initialization
* Params:
* Returns:
* Note:
* ----------------------------------------------------------------------------
*/
void tcfg_Init(void)
{
	tcfg_ReadConfigData();
	//tcfg_SetBootMode(TCFG_ENV_BOOTMODE_NORMAL);
	//tcfg_SetBootCount(0);
}



/*
* ----------------------------------------------------------------------------
* Function Name: tcfg_ReadConfigData
* Purpose:
* Params:
* Returns:
* Note:
* ----------------------------------------------------------------------------
*/
void tcfg_ReadConfigData(void)
{
	if(tcfg_CheckHeadFlag(TCFG_FLAGTYPE_GENERAL) == true)
	{
		g_SubSn = TFLASH_ReadWord(EEPROM_CONFIG_OFFSET+TCFG_SN_OFFSET);
		g_heartinterval= tcfg_GetHeartinterval();
	}
	else
	{
		if(tcfg_CheckInfoBurned())//check whether brandinfo and sn has been bruned
		{
			g_SubSn = tcfg_GetSNfromBrandKey();
			tcfg_SetBrandCode(tcfg_GetFactoryBrand());
		}
		else
		{
			g_SubSn = 0x80000000 | tmesh_Generate_Random();
		}
		g_heartinterval = 10;
		tcfg_setMagFreq(10);
		tcfg_SetHeartinterval(g_heartinterval);
		tcfg_SaveConfigToEeprom();
	}
}


bool tcfg_CheckInfoBurned(void)
{
	if( 0x00 == FLASH_ReadByte(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET + 0) && \
	    0x00 == FLASH_ReadByte(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET + 1) && \
		0x00 == FLASH_ReadByte(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET + 2) && \
		0x00 == FLASH_ReadByte(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET + 3) )
	{
		return false;
	}
	else
	{
	  return true;
	}
}

uint32_t tcfg_GetSNfromBrandKey(void)
{
	return TFLASH_ReadWord(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET + 4);
}


uint32_t tcfg_GetFactoryBrand(void)
{
	return TFLASH_ReadWord(EEPROM_CONFIG_OFFSET + TCFG_FACTORY_BRAND_SN_OFFSET);
}


bool tcfg_CheckHeadFlag(char flagtype)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	if(flagtype == TCFG_FLAGTYPE_GENERAL)
	{
		if('T' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_HEADFLAG_OFFSET))
		{
			return false;
		}
		if('C' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_HEADFLAG_OFFSET+1))
		{
			return false;
		}
		if('L' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_HEADFLAG_OFFSET+2))
		{
			return false;
		}
		if('D' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_HEADFLAG_OFFSET+3))
		{
			return false;
		}
	}
	else if(flagtype == TCFG_FLAGTYPE_MAGAlGORITHM)
	{
		if('T' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_MAGFLAG_OFFSET))
		{
			return false;
		}
	}
	else if(flagtype == TCFG_FLAGTYPE_SECU)
	{
		if('T' != FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_SECUFLAG_OFFSET))
		{
			return false;
		}
	}
	return true;
}

uint32_t TFLASH_ReadWord(uint32_t Address)
{
	uint32_t val = 0;
	
	*((uint8_t*)(&val) + 0) = FLASH_ReadByte(Address+0);
	*((uint8_t*)(&val) + 1) = FLASH_ReadByte(Address+1);
	*((uint8_t*)(&val) + 2) = FLASH_ReadByte(Address+2);
	*((uint8_t*)(&val) + 3) = FLASH_ReadByte(Address+3);
	return val;
}

void TFLASH_ReadBuffer(uint32_t Address,uint8_t* outbuf,uint8_t outlen)
{
	uint8_t i;
	for(i=0; i<outlen; i++)
	{
		outbuf[i] = FLASH_ReadByte(Address+i);
	}
}

void TFLASH_WriteBuffer(uint32_t Address,uint8_t* inbuf,uint8_t inlen)
{
	uint8_t i;
	for(i=0; i<inlen; i++)
	{
		FLASH_ProgramByte(Address+i,*(inbuf+i));
	}
}

/**
* @brief  Programs one word (4 bytes) in program or data EEPROM memory
* @param  Address : The address where the data will be programmed
* @param  Data : Value to be programmed
* @retval None
*/
void TFLASH_WriteWord(uint32_t Address, uint32_t Data)
{
	char i;
	for(i=0; i<4; i++)
	{
		FLASH_ProgramByte(Address+i,*((uint8_t*)(&Data) + i));
	}
}

uint16_t TFLASH_ReadHalfWord(uint32_t Address)
{
	uint16_t val = 0;
	*((uint8_t*)(&val) + 0) = FLASH_ReadByte(Address+0);
	*((uint8_t*)(&val) + 1) = FLASH_ReadByte(Address+1);
	return val;
}

void TFLASH_WriteHalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_ProgramByte(Address, *((uint8_t*)(&Data)));

	FLASH_ProgramByte(Address+1, *((uint8_t*)(&Data) + 1));

}

void TFLASH_WriteByte(uint32_t Address,uint8_t Data)
{
	FLASH_ProgramByte(Address, Data);
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: tcfg_ReadEnvData
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void tcfg_ReadEnvData(void)
{
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: tcfg_ReadRecordData
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void tcfg_ReadRecordData(void)
{
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: tcfg_SaveConfigToEeprom
 * Purpose: 保存配置信息到eeprom  中
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void tcfg_SaveConfigToEeprom(void)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteBuffer(EEPROM_CONFIG_OFFSET+TCFG_HEADFLAG_OFFSET,(uint8_t*)"TCLD",TCFG_HEADFLAG_LENGTH);
	TFLASH_WriteWord(EEPROM_CONFIG_OFFSET+TCFG_SN_OFFSET,g_SubSn);
	HAL_FLASHEx_DATAEEPROM_Lock();
	return;
}

char tcfg_GetBootMode(void)
{
	return FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_ENV_BOOTMODE_OFFSET);
}


void tcfg_SetBootMode(char bootmode)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteBuffer(EEPROM_CONFIG_OFFSET+TCFG_ENVFLAG_OFFSET,(uint8_t*)"TCLD",TCFG_ENVFLAG_LENGTH);
	TFLASH_WriteByte(EEPROM_CONFIG_OFFSET+TCFG_ENV_BOOTMODE_OFFSET,bootmode); // TCFG_ENV_BOOTMODE_UPDATE
	HAL_FLASHEx_DATAEEPROM_Lock();
}


uint16_t tcfg_GetMagBackgroud(char axis)
{
	if(true == tcfg_CheckHeadFlag(TCFG_FLAGTYPE_MAGAlGORITHM))
	{
	    if(axis == TCFG_X_AXIS)
	    {
		return TFLASH_ReadHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_X_OFFSET);
	    }
	    else if(axis == TCFG_Y_AXIS)
	    {
		return TFLASH_ReadHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_Y_OFFSET);
	    }
	    else if(axis == TCFG_Z_AXIS)
	    {
		return TFLASH_ReadHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_Z_OFFSET);
	    }
	}
	return  0x7FFF;
}

void tcfg_SetMagBackgroud(int16_t x_axis,int16_t y_axis,int16_t z_axis)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_X_OFFSET,x_axis);
	TFLASH_WriteHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_Y_OFFSET,y_axis);
	TFLASH_WriteHalfWord(EEPROM_CONFIG_OFFSET+TCFG_MAG_BACK_Z_OFFSET,z_axis);
	TFLASH_WriteByte(EEPROM_CONFIG_OFFSET+TCFG_MAGFLAG_OFFSET,'T');
	HAL_FLASHEx_DATAEEPROM_Lock();
}

uint8_t tcfg_GetBootCount(void)
{
	return FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_RECORD_BOOTCNT_OFFSET);
}

void tcfg_SetBootCount(uint8_t count)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteByte(EEPROM_CONFIG_OFFSET+TCFG_RECORD_BOOTCNT_OFFSET,count);
	HAL_FLASHEx_DATAEEPROM_Lock();
	
}

uint8_t tcfg_GetSavedSensitivity(void)
{
	return FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_MAG_SENSITIVITY_OFFSET);
}

void tcfg_SetSavedSensitivity(uint8_t data)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteByte(EEPROM_CONFIG_OFFSET+TCFG_MAG_SENSITIVITY_OFFSET,data);
	HAL_FLASHEx_DATAEEPROM_Lock();
}

void tcfg_SetHeartinterval(uint16_t data)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteHalfWord(EEPROM_CONFIG_OFFSET+TCFG_HEARTINTERVAL_OFFSET,data);
	HAL_FLASHEx_DATAEEPROM_Lock();
}

uint16_t tcfg_GetHeartinterval(void)
{
	return TFLASH_ReadHalfWord(EEPROM_CONFIG_OFFSET+TCFG_HEARTINTERVAL_OFFSET);
}

uint8_t tcfg_getMagFreq(void)
{
	return FLASH_ReadByte(EEPROM_CONFIG_OFFSET+TCFG_MAG_FREQ_OFFSET);
}

void tcfg_setMagFreq(uint8_t data)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteByte(EEPROM_CONFIG_OFFSET + TCFG_MAG_FREQ_OFFSET,data);
	HAL_FLASHEx_DATAEEPROM_Lock();
}

void tcfg_GetSpotID(char* outbuf)
{
	TFLASH_ReadBuffer(EEPROM_CONFIG_OFFSET+TCFG_SPOTID_OFFSET,(uint8_t*)outbuf,TCFG_SPOTID_LENGTH);
	if(strlen(outbuf) >= TCFG_SPOTID_LENGTH)
	{
	    strcpy(outbuf,"unset");
	}
	return;
}

void tcfg_SetSpotID(char* inbuf)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteBuffer(EEPROM_CONFIG_OFFSET+TCFG_SPOTID_OFFSET,(uint8_t*)inbuf,TCFG_SPOTID_LENGTH);
	HAL_FLASHEx_DATAEEPROM_Lock();
	return;
}

uint32_t tcfg_GetBrandCode(void)
{
	return TFLASH_ReadWord(EEPROM_CONFIG_OFFSET+TCFG_SECU_BRAND_OFFSET);
}

void tcfg_SetBrandCode(uint32_t brand)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteWord(EEPROM_CONFIG_OFFSET+TCFG_SECU_BRAND_OFFSET,brand);
	HAL_FLASHEx_DATAEEPROM_Lock();
	return;
}

uint32_t tcfg_GetSubSN(void)
{
	return TFLASH_ReadWord(EEPROM_CONFIG_OFFSET + TCFG_SN_OFFSET);
}

void tcfg_SetSubSN(uint32_t subsn)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteWord(EEPROM_CONFIG_OFFSET+TCFG_SN_OFFSET,subsn);
	HAL_FLASHEx_DATAEEPROM_Lock();
	
	return;
}

uint8_t tcfg_ReadRfChannel(void)
{
	return TFLASH_ReadWord(EEPROM_CONFIG_OFFSET + TCFG_RFCHANNEL_OFFSET);
}

void tcfg_WriteRfChannel(uint8_t val)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	TFLASH_WriteWord(EEPROM_CONFIG_OFFSET+TCFG_RFCHANNEL_OFFSET,val);
	HAL_FLASHEx_DATAEEPROM_Lock();	
	return;
}


