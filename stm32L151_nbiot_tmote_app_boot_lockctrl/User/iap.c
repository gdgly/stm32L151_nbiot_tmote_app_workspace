/****************************************Copyright (c)****************************************************
**                         SHENZHEN DECARD TECHNOLOGIES Co.,LTD.                               
**                                     
**                               http://www.decard.com
**
**--------------File Info---------------------------------------------------------------------------------
** Create by:			zhangdh
** Create date:			2017-07-30
** Version:             1.0
** Descriptions:		IAP����
**--------------File Info---------------------------------------------------------------------------------
** Modify by:
** Modify date:
** Version:
** Descriptions:
*********************************************************************************************************/
#include "string.h"
#include "stdio.h"
#include "iap.h"
#include "tmesh_cfg.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Address = 0, PAGEError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;

/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;


uint32_t STMFLASH_ReadfWord(uint32_t faddr)
{
	return *(__IO uint32_t *)faddr;
}

void STMFLASH_ReadBuffer(uint32_t addr, uint8_t *buf, uint32_t length)
{
	while (length--) {
		*buf++ = *(__IO uint8_t *)addr++;
	}
}

/********************************************************************************************************

*********************************************************************************************************/
uint8_t xm_iap_program(uint32_t base_addr,uint32_t addr_offset, uint32_t len, uint8_t* buff)
{
//    uchar  iapbuff[PAGESIZE];
    uint32_t   i,wdata,rdata;
	uint16_t PageNum = 0;
	uint32_t Tmpaddr;
	HAL_StatusTypeDef FLASHStatus = HAL_OK;

	Tmpaddr = addr_offset;
#if 0
	if(len != 1024)	//zhangdh	modify	20170801
	{
		return IAP_LEN_UNSUPPORTED;
	}
#endif	
	PageNum = (Tmpaddr/PAGESIZE);  // PageNum=addr/2048;
	Tmpaddr %= PAGESIZE;
	if((addr_offset + len) > FLASH_APP_SIZE)
	{
		return IAP_LEN_UNSUPPORTED;
	}
	//if((FLASH->CR & 0x00000080) != 0)
	{
		HAL_FLASH_Unlock();
		//FLASH_SetLatency(FLASH_Latency_2);     
    	//FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	}
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR);
	//
	if(Tmpaddr == 0)
	{
		
		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = base_addr + PageNum*PAGESIZE;
		EraseInitStruct.NbPages     = 1;
		FLASHStatus = HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
		if(FLASHStatus != HAL_OK)
		{
			return IAP_ERASE_ERROR;
		}

	}
	//
	for(i=0; i<len; i+=4)
	{
		wdata = (uint32_t)(buff[i])       + (uint32_t)(buff[i+1]<<8)
		      + (uint32_t)(buff[i+2]<<16) + (uint32_t)(buff[i+3]<<24);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, base_addr + addr_offset+i, wdata);
		if(FLASHStatus != HAL_OK)
		{
			return IAP_PROGRAM_ERROR;
		}
		rdata = STMFLASH_ReadfWord(base_addr + addr_offset+i);
		if(wdata != rdata){
			return IAP_PROGRAM_ERROR;
		}
	}
//	FLASH_ReadOutProtection(ENABLE); 
	HAL_FLASH_Lock();
	return IAP_OK;
}

/*********************************************************************************************************
**                            End Of programcode_iap
********************************************************************************************************/
