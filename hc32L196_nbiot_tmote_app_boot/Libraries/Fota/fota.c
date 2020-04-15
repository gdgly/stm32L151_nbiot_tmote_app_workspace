/**
  *********************************************************************************************************
  * @file    fota.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-13
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "fota.h"
#include "fifo.h"
#include "delay.h"
#include "usart.h"
#include "hal_iwdg.h"
#include "iap_boot.h"
#include "iap_core.h"
#include "iap_ugrade.h"
#include "radio_hal_rf.h"
#include "radio_hal_app.h"

#define FOTA_DEBUG_LOG_RF_PRINTF
#define FOTA_DEBUG_LOG_PRINTF				Radio_RF_Trf_Printf

static void FOTA_ChokeHandle(void)
{
	HC32_IWDG_Feed();
}

#if FOTA_CHIPFLASH2NORFLASH_ENABLE
static u8 CalculateSumCheckCode(u32 regCode, uint8_t* buf, uint32_t length)
{
	u32 sumCheckCode = regCode;
	
	while (length--) {
		sumCheckCode += *buf++;
	}
	
	sumCheckCode %= 0xFF;
	
	return sumCheckCode;
}
#endif

#if FOTA_CHIPFLASH2NORFLASH_ENABLE
/**********************************************************************************************************
 @Function			static FotaResultCode FOTA_ChipFlash2NorFlash(FotaClientsTypeDef* pClient)
 @Description			FOTA_ChipFlash2NorFlash						: ChipFlash 写入 NorFlash
 @Input				pClient
 @Return				FotaResultCode
**********************************************************************************************************/
static FotaResultCode FOTA_ChipFlash2NorFlash(FotaClientsTypeDef* pClient)
{
	u8 ChipFlashCheckCode = 0;
	u8 NorFlashCheckCode = 0;
	u8 RebackupTimer = 3;
	
	/* 转换模式检查 */
	if (pClient->ChangeMode != Fota_ChipToNor) return Fota_CHANGEMODEFAIL;
	
	/* 交换内存检查 */
	if ((pClient->SwapBuf_size < FOTA_APP_PACKSLICE_SIZE) || (pClient->SwapBuf == NULL)) return Fota_SWAPFAIL;
	
	/* 存储区设备检查 */
	if ((HC32_FLASH_Status() != Ok) || (FLASH_NOR_Status() != Ok)) return Fota_DEVICEFLASHFAIL;
	
	/* 备份区固件版本检查 */
	if ((pClient->BackupMode != Fota_Backup_Always) && (FLASH_NOR_ReadByte(FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET) == 0x55)) {
		if (FLASH_NOR_ReadWord(FOTA_APP2_INFO_UPGRADE_SOFTVER_OFFSET) == (((u32)pClient->SoftwareMajor << 16) | ((u32)pClient->SoftwareSub << 0))) {
			return Fota_BACKUPMODEFAIL;
		}
	}
	
	/* 备份固件 */
	do {
		FOTA_ChokeHandle();
		
		/* 1step: 擦除备份区 */
		FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(0)));
		FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(1)));
		FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(2)));
		FLASH_NOR_Erase(mErase_Mode_Block64K, (FOTA_APP2_BASE_ADDR + NOR_BLOCK64K_ADDR(3)));
		
		/* 2step: 写入固件到备份区 */
		for (int packIndex = 0; packIndex < pClient->PackSliceNum; packIndex++) {
			HC32_FLASH_ReadBuffer((pClient->FirmwareBaseAddr + (packIndex * pClient->PackSliceLen)), pClient->SwapBuf, pClient->PackSliceLen);
			FLASH_NOR_WriteBuffer(pClient->SwapBuf, (pClient->PackSliceBaseAddr + (packIndex * pClient->PackSliceSize)), pClient->PackSliceSize);
			ChipFlashCheckCode = CalculateSumCheckCode(ChipFlashCheckCode, pClient->SwapBuf, pClient->PackSliceLen);
		}
		
		/* 3step: 校验备份区中固件 */
		for (int packIndex = 0; packIndex < pClient->PackSliceNum; packIndex++) {
			FLASH_NOR_ReadBuffer(pClient->SwapBuf, (pClient->PackSliceBaseAddr + (packIndex * pClient->PackSliceSize)), pClient->PackSliceSize);
			NorFlashCheckCode = CalculateSumCheckCode(NorFlashCheckCode, pClient->SwapBuf, pClient->PackSliceLen);
		}
		
		RebackupTimer--;
	} while ((ChipFlashCheckCode != NorFlashCheckCode) && (RebackupTimer > 0));
	
	/* 备份状态检查 */
	if (ChipFlashCheckCode != NorFlashCheckCode) return Fota_ERROR;
	
	/* 写入备份固件信息 */
	FLASH_NOR_WriteWord(FOTA_APP2_INFO_UPGRADE_BASEADDR_OFFSET, pClient->PackSliceBaseAddr);
	FLASH_NOR_WriteHalfWord(FOTA_APP2_INFO_UPGRADE_BLOCKNUM_OFFSET, pClient->PackSliceNum);
	FLASH_NOR_WriteHalfWord(FOTA_APP2_INFO_UPGRADE_BLOCKLEN_OFFSET, pClient->PackSliceSize);
	FLASH_NOR_WriteHalfWord(FOTA_APP2_INFO_UPGRADE_DATALEN_OFFSET, pClient->PackSliceLen);
	
	FLASH_NOR_WriteWord(FOTA_APP2_INFO_UPGRADE_SOFTVER_OFFSET, (((u32)pClient->SoftwareMajor << 16) | ((u32)pClient->SoftwareSub << 0)));
	FLASH_NOR_WriteWord(FOTA_APP2_INFO_DOWNLOAD_TIME_OFFSET, pClient->FirmwareTime);
	FLASH_NOR_WriteWord(FOTA_APP2_INFO_DATA_CHECK_CODE_OFFSET, NorFlashCheckCode);
	
	FLASH_NOR_WriteByte(FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET, 0x55);
	
	pClient->FirmwareCheckCode = NorFlashCheckCode;
	
	return Fota_OK;
}
#endif

#if FOTA_NORFLASH2CHIPFLASH_ENABLE
void programUpdateFlashPrint(FotaClientsTypeDef* pClient)
{
	int UpgradeState = 0;
	
	UpgradeState = (pClient->FirmSlice_Index * pClient->firm_writelen * 100) / (pClient->PackSliceNum * pClient->PackSliceLen);
	
#ifdef FOTA_DEBUG_LOG_RF_PRINTF
	FOTA_DEBUG_LOG_PRINTF("SPI FLASH Upgrade : %03d%%", UpgradeState);
#endif
}
#endif

#if FOTA_NORFLASH2CHIPFLASH_ENABLE
/**********************************************************************************************************
 @Function			static FotaResultCode FOTA_NorFlash2ChipFlash(FotaClientsTypeDef* pClient)
 @Description			FOTA_NorFlash2ChipFlash						: NorFlash 写入 ChipFlash
 @Input				pClient
 @Return				FotaResultCode
**********************************************************************************************************/
static FotaResultCode FOTA_NorFlash2ChipFlash(FotaClientsTypeDef* pClient)
{
	struct data_fifo_s fotaFifo;
	
	u32 NorFlashPackSliceNum = pClient->PackSliceNum;
	u32 FifoRemainderLen = 0;
	
	pClient->PackSlice_Index = 0;
	pClient->FirmSlice_Index = 0;
	
	/* 转换模式检查 */
	if (pClient->ChangeMode != Fota_NorToChip) return Fota_CHANGEMODEFAIL;
	
	/* 交换内存检查 */
	if ((pClient->SwapBuf_size < FOTA_APP_PACKSLICE_SIZE) || (pClient->SwapBuf == NULL)) return Fota_SWAPFAIL;
	
	/* 内存空间检查 */
	if ((pClient->FirmwareBuf == NULL) || (pClient->PackSliceBuf == NULL)) return Fota_BUFFERSPACEFAIL;
	
	/* 存储区设备检查 */
	if ((HC32_FLASH_Status() != Ok) || (FLASH_NOR_Status() != Ok)) return Fota_DEVICEFLASHFAIL;
	
	Fifo_init(&fotaFifo, pClient->SwapBuf_size, pClient->SwapBuf);
	
	/* 获取固件起始地址信息 */
	FLASH_NOR_ReadBuffer(pClient->PackSliceBuf, pClient->PackSliceBaseAddr, 6);
	pClient->app_offset &= 0xFFFF00FF;
	pClient->firm_offset = (pClient->PackSliceBuf[5]);
	pClient->app_offset |= (pClient->firm_offset << 8);
	if (pClient->app_offset >= APP_LOWEST_ADDRESS) {
		xm_iap_program(APP_LOWEST_ADDRESS - HC32_FLASH_SECTOR_BLOCK, 0, 4, (unsigned char*)(&pClient->app_offset));
	}
	
	if (pClient->app_offset < APP_LOWEST_ADDRESS) return Fota_FIRMWAREFAIL;
	
	while ((NorFlashPackSliceNum != 0) || (Fifo_status(&fotaFifo) >= pClient->firm_writelen)) {
		
		if ((NorFlashPackSliceNum != 0) && (Fifo_free(&fotaFifo) >= pClient->PackSliceLen)) {
			FLASH_NOR_ReadBuffer(pClient->PackSliceBuf, (pClient->PackSliceBaseAddr + (pClient->PackSlice_Index * pClient->PackSliceSize)), pClient->PackSliceLen);
			pClient->PackSlice_Index++;
			NorFlashPackSliceNum--;
			Fifo_WriteBuffer(&fotaFifo, pClient->PackSliceBuf, pClient->PackSliceLen);
		}
		
		if (Fifo_status(&fotaFifo) >= pClient->firm_writelen) {
			Fifo_ReadBuffer(&fotaFifo, pClient->FirmwareBuf, pClient->firm_writelen);
			xm_iap_program(pClient->app_offset, (pClient->FirmSlice_Index * pClient->firm_writelen), pClient->firm_writelen, pClient->FirmwareBuf);
			pClient->FirmSlice_Index++;
			programUpdateFlashPrint(pClient);
		}
		
		FOTA_ChokeHandle();
	}
	
	FifoRemainderLen = Fifo_status(&fotaFifo);
	if (FifoRemainderLen > 0) {
		Fifo_ReadBuffer(&fotaFifo, pClient->FirmwareBuf, FifoRemainderLen);
		for (int i = FifoRemainderLen; i < pClient->firm_writelen; i++) {
			pClient->FirmwareBuf[i] = 0xFF;
		}
		xm_iap_program(pClient->app_offset, (pClient->FirmSlice_Index * pClient->firm_writelen), pClient->firm_writelen, pClient->FirmwareBuf);
		pClient->FirmSlice_Index++;
		programUpdateFlashPrint(pClient);
	}
	
	return Fota_OK;
}
#endif

/**********************************************************************************************************
 @Function			FotaResultCode FOTA_ConvertFirmware(FotaClientsTypeDef* pClient)
 @Description			FOTA_ConvertFirmware
 @Input				pClient
 @Return				FotaResultCode
**********************************************************************************************************/
FotaResultCode FOTA_ConvertFirmware(FotaClientsTypeDef* pClient)
{
	FotaResultCode res;
	
#if FOTA_CHIPFLASH2NORFLASH_ENABLE
	if (pClient->ChangeMode == Fota_ChipToNor) {
		res = FOTA_ChipFlash2NorFlash(pClient);
	}
#endif
	
#if FOTA_NORFLASH2CHIPFLASH_ENABLE
	if (pClient->ChangeMode == Fota_NorToChip) {
		res = FOTA_NorFlash2ChipFlash(pClient);
	}
#endif
	
	return res;
}

/********************************************** END OF FLEE **********************************************/
