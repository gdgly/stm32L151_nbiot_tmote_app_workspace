#ifndef __PLATFORM_CONFIG_H
#define   __PLATFORM_CONFIG_H

#include "sys.h"

//#define	MVB_SUBSN						0x81011000										//设备号
//#define	MVB_BRAND						"mvb"											//厂牌

#define	CPUVERSION					"HC32L196JC"										//处理器型号

#define	MVB_STATICMAGNETIC_MODEL			51
#define	MVB_FLOWMAGNETIC_MODEL			52
#define	MVB_SPOT_LOCKER_MODEL			53
#define	MVB_BARRIER_MODEL				54
#define	MVB_MODEL_TYPE					MVB_STATICMAGNETIC_MODEL								//设备类型

#define	SYSTEM_CLOCK_XTH				32000000
#define	SYSTEM_CLOCK_RCH				48000000
#define	SYSTEM_CLOCK_TYPE				SYSTEM_CLOCK_RCH									//系统时钟
























#endif /* __PLATFORM_CONFIG_H */
