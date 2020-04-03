#ifndef __RADIO_HAL_COMMON_H
#define   __RADIO_HAL_COMMON_H

#include "sys.h"

#define SIZE_INFRAME_Q			2

#define MRFI_RX_METRICS_SIZE		2

#define FI_AVAILABLE			0
#define FI_INUSE_UNTIL_DEL		1

#define TRF_MSG_VERSION			0x01

#define TRF_MSG_REBOOT			24
#define TRF_MSG_HEART			27
#define TRF_MSG_DEFAULT			49
#define TRF_MSG_SENSITIVITY		50
#define TRF_MSG_WORKMODE			51
#define TRF_MSG_INITBACKGROUND	52
#define TRF_MSG_BASICINFO		53
#define TRF_MSG_UPGRADE			54
#define TRF_MSG_STATUS			55
#define TRF_MSG_HEART_BOOTLOADER	56
#define TRF_MSG_RFHEART_INTERVAL	57
#define TRF_MSG_DEBUG_INFO		58
#define TRF_MSG_DEBUG_STATUS		58
#define TRF_MSG_REMOTE_SERVER		59
#define TRF_MSG_DYNAMICINFO		60
#define TRF_MSG_JSON			61
#define TRF_MSG_GENERAL_CMD		62

typedef enum _radio_trf_status
{
	TRF_SUCCESS				= 0U,
	TRF_NO_PAYLOAD				= 1U,
	TRF_BAD_PROTOCAL			= 2U,
	TRF_BAD_MSGTYPE			= 3U,
	TRF_NOT_FORME				= 4U,
} radio_trf_status;

typedef enum _radio_trf_protocol_type
{
	OPTIONAL_PRT				= 0U,
	SIMPLICITI_PRT				= 1U,
	XMESH_PRT					= 2U,
	XMESHLITE_PRT				= 3U,
	UPGRADE_PRT				= 4U,
	XMESHCFG_PRT				= 5U,
	RSVED6					= 6U,
	RSVED7					= 7U,
} radio_trf_protocol_type;

typedef struct _mrfiPacket_t
{
	u8						frame[255];
	u8						rxMetrics[MRFI_RX_METRICS_SIZE];
} mrfiPacket_t;

typedef struct _frameInfo_t
{
	__IO u8					fi_usage;
	__IO u32					orderStamp;
	mrfiPacket_t				mrfiPkt;
} frameInfo_t;























#endif /* __RADIO_HAL_COMMON_H */
