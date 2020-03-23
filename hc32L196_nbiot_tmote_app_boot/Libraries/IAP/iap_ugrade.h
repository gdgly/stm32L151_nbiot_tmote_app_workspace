#ifndef __IAP_UGRADE_H
#define   __IAP_UGRADE_H

#include "sys.h"




#define READY_TO_JUMP			0x00
#define NO_APPDOWNLOAD			0x01
#define DOWNLOADING				0x02
#define TIME_OUT				0x03
#define DOWNLOAD_ERROR			0x04

#define JOIN_COMPELET			0x00
#define JOINING				0X01













typedef struct _upgrad_client
{
	__IO u8					ug_boot_mode;
	__IO u8					ug_upgrad_state;
	__IO u8					ug_join_state;
	__IO u32					ug_mac_sn;
	
	
	
	
	
	
} upgradClientsTypeDef;

extern upgradClientsTypeDef upgradClient;









#endif /* __IAP_UGRADE_H */
