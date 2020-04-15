#ifndef __FOTA_H
#define   __FOTA_H

#include "sys.h"
#include "hal_flash.h"
#include "hal_norflash.h"

#define FOTA_CHIPFLASH2NORFLASH_ENABLE				0
#define FOTA_NORFLASH2CHIPFLASH_ENABLE				1

/* Map:
 *      APP1 => (0 ~ 4095) is Info + (4096 ~ [256K - 1]) is Data: 4K + (512Byte x 504Block) = 4K + 252K = 256K
 *      APP2 => (0 ~ 4095) is Info + (4096 ~ [256K - 1]) is Data: 4K + (512Byte x 504Block) = 4K + 252K = 256K
 */

#define FOTA_APP_PACKSLICE_SIZE					(512u)															//APP分片大小 512Byte
#define FOTA_APP_PACKSLICE_BLOCK					(504u)															//APP分片个数 504Block
#define FOTA_APP_INFORMATION_SIZE					(4096u)															//APP信息数据 4096Byte

/************************************* APP1 In NorFlash Address Table *************************************/
#define FOTA_APP1_BASE_ADDR						((NOR_BASE_ADDR) + 0x00000000U)										//0x00000000U (000K ~ 256K)
#define FOTA_APP1_BYTE_SIZE						((NOR_BLOCK64K_BYTE_SIZE) * 4U)										//0x00040000U
#define FOTA_APP1_INFO_ADDR						(FOTA_APP1_BASE_ADDR)												//0x00000000U
#define FOTA_APP1_INFO_SIZE						(FOTA_APP_INFORMATION_SIZE)											//0x00001000U
#define FOTA_APP1_DATA_ADDR						(FOTA_APP1_BASE_ADDR + FOTA_APP1_INFO_SIZE)								//0x00001000U
#define FOTA_APP1_DATA_SIZE						(FOTA_APP1_BYTE_SIZE - FOTA_APP1_INFO_SIZE)								//0x0003F000U

#define FOTA_APP1_INFO_UPGRADE_STATUS_OFFSET			FOTA_APP1_INFO_ADDR													//0x00000000U
#define FOTA_APP1_INFO_UPGRADE_STATUS_LENGTH			1																//升级标志 高4位0x5(0101)有升级包 低4位0x5(0101)可升级
#define FOTA_APP1_INFO_UPGRADE_BASEADDR_OFFSET		FOTA_APP1_INFO_UPGRADE_STATUS_OFFSET + FOTA_APP1_INFO_UPGRADE_STATUS_LENGTH	//0x00000001U
#define FOTA_APP1_INFO_UPGRADE_BASEADDR_LENGTH		4																//升级APP起始地址
#define FOTA_APP1_INFO_UPGRADE_BLOCKNUM_OFFSET		FOTA_APP1_INFO_UPGRADE_BASEADDR_OFFSET + FOTA_APP1_INFO_UPGRADE_BASEADDR_LENGTH	//0x00000005U
#define FOTA_APP1_INFO_UPGRADE_BLOCKNUM_LENGTH		2																//升级APP存放块数
#define FOTA_APP1_INFO_UPGRADE_BLOCKLEN_OFFSET		FOTA_APP1_INFO_UPGRADE_BLOCKNUM_OFFSET + FOTA_APP1_INFO_UPGRADE_BLOCKNUM_LENGTH	//0x00000007U
#define FOTA_APP1_INFO_UPGRADE_BLOCKLEN_LENGTH		2																//升级APP块占用长度
#define FOTA_APP1_INFO_UPGRADE_DATALEN_OFFSET		FOTA_APP1_INFO_UPGRADE_BLOCKLEN_OFFSET + FOTA_APP1_INFO_UPGRADE_BLOCKLEN_LENGTH	//0x00000009U
#define FOTA_APP1_INFO_UPGRADE_DATALEN_LENGTH		2																//升级APP块有效长度
#define FOTA_APP1_INFO_UPGRADE_INDEX_OFFSET			FOTA_APP1_INFO_UPGRADE_DATALEN_OFFSET + FOTA_APP1_INFO_UPGRADE_DATALEN_LENGTH	//0x0000000BU
#define FOTA_APP1_INFO_UPGRADE_INDEX_LENGTH			4																//升级APP序号
#define FOTA_APP1_INFO_UPGRADE_SOFTVER_OFFSET		FOTA_APP1_INFO_UPGRADE_INDEX_OFFSET + FOTA_APP1_INFO_UPGRADE_INDEX_LENGTH		//0x0000000FU
#define FOTA_APP1_INFO_UPGRADE_SOFTVER_LENGTH		4																//升级包版本号 高2字节主版本号 低2字节从版本号
#define FOTA_APP1_INFO_DOWNLOAD_TIME_OFFSET			FOTA_APP1_INFO_UPGRADE_SOFTVER_OFFSET + FOTA_APP1_INFO_UPGRADE_SOFTVER_LENGTH	//0x00000013U
#define FOTA_APP1_INFO_DOWNLOAD_TIME_LENGTH			4																//升级包下载时间
#define FOTA_APP1_INFO_DATA_CHECK_CODE_OFFSET		FOTA_APP1_INFO_DOWNLOAD_TIME_OFFSET + FOTA_APP1_INFO_DOWNLOAD_TIME_LENGTH		//0x00000017U
#define FOTA_APP1_INFO_DATA_CHECK_CODE_LENGTH		4																//升级包校验码
#define FOTA_APP1_INFO_PACKSLICE_STATUS_OFFSET		FOTA_APP1_INFO_DATA_CHECK_CODE_OFFSET + FOTA_APP1_INFO_DATA_CHECK_CODE_LENGTH	//0x0000001BU
#define FOTA_APP1_INFO_PACKSLICE_STATUS_LENGTH		FOTA_APP_PACKSLICE_BLOCK												//升级包分片下载状态(0x00有 0xFF无)
/**********************************************************************************************************/

/************************************* APP2 In NorFlash Address Table *************************************/
#define FOTA_APP2_BASE_ADDR						((NOR_BASE_ADDR) + 0x00040000U)										//0x00040000U (256K ~ 512K)
#define FOTA_APP2_BYTE_SIZE						((NOR_BLOCK64K_BYTE_SIZE) * 4U)										//0x00040000U
#define FOTA_APP2_INFO_ADDR						(FOTA_APP2_BASE_ADDR)												//0x00040000U
#define FOTA_APP2_INFO_SIZE						(FOTA_APP_INFORMATION_SIZE)											//0x00001000U
#define FOTA_APP2_DATA_ADDR						(FOTA_APP2_BASE_ADDR + FOTA_APP2_INFO_SIZE)								//0x00041000U
#define FOTA_APP2_DATA_SIZE						(FOTA_APP2_BYTE_SIZE - FOTA_APP2_INFO_SIZE)								//0x0003F000U

#define FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET			FOTA_APP2_INFO_ADDR													//0x00040000U
#define FOTA_APP2_INFO_UPGRADE_STATUS_LENGTH			1																//升级标志 高4位0x5(0101)有升级包 低4位0x5(0101)可升级
#define FOTA_APP2_INFO_UPGRADE_BASEADDR_OFFSET		FOTA_APP2_INFO_UPGRADE_STATUS_OFFSET + FOTA_APP2_INFO_UPGRADE_STATUS_LENGTH	//0x00040001U
#define FOTA_APP2_INFO_UPGRADE_BASEADDR_LENGTH		4																//升级APP起始地址
#define FOTA_APP2_INFO_UPGRADE_BLOCKNUM_OFFSET		FOTA_APP2_INFO_UPGRADE_BASEADDR_OFFSET + FOTA_APP2_INFO_UPGRADE_BASEADDR_LENGTH	//0x00040005U
#define FOTA_APP2_INFO_UPGRADE_BLOCKNUM_LENGTH		2																//升级APP存放块数
#define FOTA_APP2_INFO_UPGRADE_BLOCKLEN_OFFSET		FOTA_APP2_INFO_UPGRADE_BLOCKNUM_OFFSET + FOTA_APP2_INFO_UPGRADE_BLOCKNUM_LENGTH	//0x00040007U
#define FOTA_APP2_INFO_UPGRADE_BLOCKLEN_LENGTH		2																//升级APP块占用长度
#define FOTA_APP2_INFO_UPGRADE_DATALEN_OFFSET		FOTA_APP2_INFO_UPGRADE_BLOCKLEN_OFFSET + FOTA_APP2_INFO_UPGRADE_BLOCKLEN_LENGTH	//0x00040009U
#define FOTA_APP2_INFO_UPGRADE_DATALEN_LENGTH		2																//升级APP块有效长度
#define FOTA_APP2_INFO_UPGRADE_INDEX_OFFSET			FOTA_APP2_INFO_UPGRADE_DATALEN_OFFSET + FOTA_APP2_INFO_UPGRADE_DATALEN_LENGTH	//0x0004000BU
#define FOTA_APP2_INFO_UPGRADE_INDEX_LENGTH			4																//升级APP序号
#define FOTA_APP2_INFO_UPGRADE_SOFTVER_OFFSET		FOTA_APP2_INFO_UPGRADE_INDEX_OFFSET + FOTA_APP2_INFO_UPGRADE_INDEX_LENGTH		//0x0004000FU
#define FOTA_APP2_INFO_UPGRADE_SOFTVER_LENGTH		4																//升级包版本号 高2字节主版本号 低2字节从版本号
#define FOTA_APP2_INFO_DOWNLOAD_TIME_OFFSET			FOTA_APP2_INFO_UPGRADE_SOFTVER_OFFSET + FOTA_APP2_INFO_UPGRADE_SOFTVER_LENGTH	//0x00040013U
#define FOTA_APP2_INFO_DOWNLOAD_TIME_LENGTH			4																//升级包下载时间
#define FOTA_APP2_INFO_DATA_CHECK_CODE_OFFSET		FOTA_APP2_INFO_DOWNLOAD_TIME_OFFSET + FOTA_APP2_INFO_DOWNLOAD_TIME_LENGTH		//0x00040017U
#define FOTA_APP2_INFO_DATA_CHECK_CODE_LENGTH		4																//升级包校验码
#define FOTA_APP2_INFO_PACKSLICE_STATUS_OFFSET		FOTA_APP2_INFO_DATA_CHECK_CODE_OFFSET + FOTA_APP2_INFO_DATA_CHECK_CODE_LENGTH	//0x0004001BU
#define FOTA_APP2_INFO_PACKSLICE_STATUS_LENGTH		FOTA_APP_PACKSLICE_BLOCK												//升级包分片下载状态(0x00有 0xFF无)
/**********************************************************************************************************/

typedef enum _fota_result_errcode
{
	Fota_OK					= 0U,																			//Fota正常
	Fota_ERROR				= 1U,																			//Fota异常
	Fota_SWAPFAIL				= 2U,																			//Fota交换内存异常
	Fota_CHANGEMODEFAIL			= 3U,																			//Fota转换模式异常
	Fota_BACKUPMODEFAIL			= 4U,																			//Fota备份模式异常
	Fota_DEVICEFLASHFAIL		= 5U,																			//Fota设备驱动异常
	Fota_BUFFERSPACEFAIL		= 6U,																			//Fota内存空间异常
	Fota_FIRMWAREFAIL			= 7U,																			//Fota备份固件异常
} FotaResultCode;

typedef enum _fota_change_mode
{
	Fota_ChipToNor				= 0U,																			//Fota片上Flash写入外接NorFlash
	Fota_NorToChip				= 1U,																			//Fota外接NorFlash写入片上Flash
} FotaChangeMode;

typedef enum _fota_backup_mode
{
	Fota_Backup_Normal			= 0U,																			//Fota备份模式普通
	Fota_Backup_Always			= 1U,																			//Fota备份模式总是
} FotaBackupMode;

typedef struct
{
	unsigned char*				FirmwareBuf;																		//Fota固件内存
	unsigned char*				PackSliceBuf;																		//Fota分片内存
	unsigned char*				SwapBuf;																			//Fota交换内存
	size_t					FirmwareBuf_size;																	//Fota固件内存大小
	size_t					PackSliceBuf_size;																	//Fota分片内存大小
	size_t					SwapBuf_size;																		//Fota交换内存大小
	
	FotaChangeMode				ChangeMode;																		//Fota转换模式
	FotaBackupMode				BackupMode;																		//Fota备份模式
	
	unsigned short				SoftwareMajor;																		//Fota固件主版本
	unsigned short				SoftwareSub;																		//Fota固件次版本
	
	unsigned int				FirmwareBaseAddr;																	//Fota固件基地址
	unsigned int				PackSliceBaseAddr;																	//Fota分片基地址
	unsigned short				PackSliceNum;																		//Fota分片数
	unsigned short				PackSliceSize;																		//Fota分片占用大小
	unsigned short				PackSliceLen;																		//Fota分片数据长度
	
	unsigned int				FirmwareTime;																		//Fota固件时间
	unsigned int				FirmwareCheckCode;																	//Fota固件校验码
	
	unsigned int				app_offset;																		//Fota固件跳转地址
	unsigned int				firm_offset;																		//Fota固件读取地址
	
	unsigned short				firm_writelen;																		//Fota固件一次写入长度
	
	unsigned int				PackSlice_Index;
	unsigned int				FirmSlice_Index;
} FotaClientsTypeDef;

FotaResultCode FOTA_ConvertFirmware(FotaClientsTypeDef* pClient);

#endif /* __FOTA_H */
