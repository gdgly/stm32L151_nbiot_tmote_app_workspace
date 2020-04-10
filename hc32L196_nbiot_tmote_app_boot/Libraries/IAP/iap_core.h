#ifndef __IAP_CORE_H
#define   __IAP_CORE_H

#include "sys.h"

#define IAP_OK					0
#define IAP_LEN_UNSUPPORTED		1
#define IAP_ERASE_ERROR			3
#define IAP_PROGRAM_ERROR		4

u8   xm_iap_program(u32 base_addr, u32 addr_offset, u32 len, u8* buff);

#endif /* __IAP_CORE_H */
