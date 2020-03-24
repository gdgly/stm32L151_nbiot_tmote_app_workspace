#ifndef __IAP_UGRADE_H
#define   __IAP_UGRADE_H

#include "sys.h"



#define OVERTIME				900


#define UNCOMPLETE				0x00
#define COMPLETE				0x02
#define TRANSERROR				0x01
#define PASS					0x03





#define READY_TO_JUMP			0x00
#define NO_APPDOWNLOAD			0x01
#define DOWNLOADING				0x02
#define TIME_OUT				0x03
#define DOWNLOAD_ERROR			0x04

#define JOIN_COMPELET			0x00
#define JOINING				0X01






#define UPGRADEVERSION			0
#define UPGRADE_TYPE_SIZE		1
#define ALLOW_SIZE				1

#define UPGD_LEN_OS				0
#define UPGD_LEN_OS_MSK			0xFF
#define UPGD_LEN_OS_SFT			0

#define UPGD_PRE_TYPE_OS			0
#define UPGD_PRE_TYPE_OS_MSK		0x07
#define UPGD_PRE_TYPE_OS_SFT		0

#define UPGD_PRE_VS_OS			0
#define UPGD_PRE_VS_OS_MSK		0xE0
#define UPGD_PRE_VS_OS_SFT		5

#define UPGD_HEAD_TYPE_OS		0
#define UPGD_HEAD_TYPE_OS_MSK		0xF0
#define UPGD_HEAD_TYPE_OS_SFT		4

#define UPGD_PKTNUM_OS			1
#define UPGD_PKTNUM_OS_MSK		0xFF
#define UPGD_PKTNUM_OS_SFT		0

#define UPGD_FRAME_CRC_SIZE		2

#define UPGD_FRAME_LEN_SIZE		1
#define UPGD_FRAME_PRE_SIZE		1
#define UPGD_FRAME_HEAD_SIZE		2

#define UPGD_FRAME_SN_SIZE		4

#define UPGD_FRAME_LEN_OFS		0
#define UPGD_FRAME_PRE_OFS		UPGD_FRAME_LEN_OFS + UPGD_FRAME_LEN_SIZE
#define UPGD_FRAME_HEAD_OFS		UPGD_FRAME_PRE_OFS + UPGD_FRAME_PRE_SIZE
#define UPGD_FRAME_SN_OFS		UPGD_FRAME_HEAD_OFS + UPGD_FRAME_HEAD_SIZE
#define UPGD_FRAME_PAYLOAD_OFS	UPGD_FRAME_SN_OFS + UPGD_FRAME_SN_SIZE

#define UPGD_P_FRAME_LEN(P)		(&((P)[UPGD_FRAME_LEN_OFS]))

#define UPGD_P_FRAME_PRE(P)		(&((P)[UPGD_FRAME_PRE_OFS]))

#define UPGD_P_FRAME_HEAD(P)		(&((P)[UPGD_FRAME_HEAD_OFS]))

#define UPGD_P_FRAME_SN(P)		(&((P)[UPGD_FRAME_SN_OFS]))

#define UPGD_P_FRAME_PAYLOAD(P)	(&((P)[UPGD_FRAME_PAYLOAD_OFS]))

#define UPGD_GET_PAYLOAD_LEN(P)	(((P)[UPGD_FRAME_LEN_OFS]) - (UPGD_FRAME_PAYLOAD_OFS))

#define UPGD_GET_FROM_FRAME(b,f)	((b)[f] & (f##_MSK))>>(f##_SFT)

#define UPGD_PUT_INTO_FRAME(b,f,v)	do {(b)[f] = ((b)[f] & ~(f##_MSK)) | ((v)<<(f##_SFT)); } while(0)








typedef enum _upgrad_status
{
	UPGRADE_REQUEST			= 0U,
	UPGRADE_VALIDDATA			= 1U,
	UPGRADE_REQUEST_RSP			= 2U,
	UPGRADE_VALIDDATA_RSP		= 3U,
	UPGRADE_END				= 4U
} upgrad_status;










typedef struct _upgrad_client
{
	__IO u8					ug_boot_mode;
	__IO u8					ug_upgrad_state;
	__IO u8					ug_update_state;
	__IO u8					ug_join_state;
	__IO u8					ug_over_flow;
	__IO u32					ug_app_offset;
	__IO u32					ug_firm_offset;
	__IO int					ug_packnum_received;
	__IO	int					ug_firmlen_received;
	__IO int					ug_test_pgm_fail_cnt;
	u8						ug_mac_sn[4];
} upgradClientsTypeDef;

extern upgradClientsTypeDef upgradClient;










u8   Ugrade_xm_ProgramUpdate(u8 *recvlong, u8 *sn);

void Ugrade_xm_Join(void);

void Ugrade_xm_Buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len);















#endif /* __IAP_UGRADE_H */
