#ifndef __IAP_UGRADE_H
#define   __IAP_UGRADE_H

#include "sys.h"


#define OVERTIME				900



#define UNCOMPLETE				0x00
#define COMPLETE				0x02
#define TRANSERROR				0x01
#define PASS					0x03





#define NO_APPDOWNLOAD			0x01
#define DOWNLOADING				0x02
#define READY_TO_JUMP			0x00
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
	UPGRADE_END				= 4U,
} upgrad_status;












extern u32 app_offset;
extern u32 firm_offset;

extern u32 iap_subsn;
extern u8  iap_bootmode;
extern u8  iap_upgrad_state;
extern u8  iap_progrm_state;
extern u8  iap_joined_state;

extern u8  subsn[4];















void xm_Ugrade_buildframe(u8 *msg, u8 type, u8 pktnum, u8 *sn, u8 *send, u8 len);

void xm_Ugrade_join(void);

u8   xm_Ugrade_programUpdate(u8 *recvlong, u8 *sn);















#endif /* __IAP_UGRADE_H */
