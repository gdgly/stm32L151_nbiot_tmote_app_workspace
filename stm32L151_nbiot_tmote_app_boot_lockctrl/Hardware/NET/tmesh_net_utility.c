/*============================================================================
* Module Name: tmesh_net_utility.c
* Purpose: the net utility functions
* Author:   Bell Zhong
* Date: 	   2017-7-9
* Notes:
*
*=============================================================================
*/
#include "tmesh_net_utility.h"
#include "hal_eeprom.h"
#include "string.h"





uint32_t tnet_utility_get_mac_sn()
{
     uint8_t buf[4];
     EEPROM_ReadBytes(EEPROM_ADDR_BASE_MACSN,buf, EEPROM_ADDR_SIZE_MACSN);
     return buf[3] << 0*8 | buf[2] << 1*8 | buf[1] << 2*8 | buf[0] << 3*8;
}


