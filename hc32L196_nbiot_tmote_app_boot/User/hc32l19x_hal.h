#ifndef __HC32L19X_HAL_H
#define   __HC32L19X_HAL_H

#include "hc32l19x_cc.h"

#define STC_RESET_FLAG_POR5V_Pos	(0U)
#define STC_RESET_FLAG_POR5V_Msk	(0x1U << STC_RESET_FLAG_POR5V_Pos)
#define STC_RESET_FLAG_POR5V		STC_RESET_FLAG_POR5V_Msk										/*!<POR5V reset flag > */
#define STC_RESET_FLAG_POR15V_Pos	(1U)
#define STC_RESET_FLAG_POR15V_Msk	(0x1U << STC_RESET_FLAG_POR15V_Pos)
#define STC_RESET_FLAG_POR15V		STC_RESET_FLAG_POR15V_Msk									/*!<POR15V reset flag > */
#define STC_RESET_FLAG_LVD_Pos	(2U)
#define STC_RESET_FLAG_LVD_Msk	(0x1U << STC_RESET_FLAG_LVD_Pos)
#define STC_RESET_FLAG_LVD		STC_RESET_FLAG_LVD_Msk										/*!<LVD reset flag > */
#define STC_RESET_FLAG_WDT_Pos	(3U)
#define STC_RESET_FLAG_WDT_Msk	(0x1U << STC_RESET_FLAG_WDT_Pos)
#define STC_RESET_FLAG_WDT		STC_RESET_FLAG_WDT_Msk										/*!<WDT reset flag > */
#define STC_RESET_FLAG_PCA_Pos	(4U)
#define STC_RESET_FLAG_PCA_Msk	(0x1U << STC_RESET_FLAG_PCA_Pos)
#define STC_RESET_FLAG_PCA		STC_RESET_FLAG_PCA_Msk										/*!<PCA reset flag > */
#define STC_RESET_FLAG_LOCKUP_Pos	(5U)
#define STC_RESET_FLAG_LOCKUP_Msk	(0x1U << STC_RESET_FLAG_LOCKUP_Pos)
#define STC_RESET_FLAG_LOCKUP		STC_RESET_FLAG_LOCKUP_Msk									/*!<LOCKUP reset flag > */
#define STC_RESET_FLAG_SYSREQ_Pos	(6U)
#define STC_RESET_FLAG_SYSREQ_Msk	(0x1U << STC_RESET_FLAG_SYSREQ_Pos)
#define STC_RESET_FLAG_SYSREQ		STC_RESET_FLAG_SYSREQ_Msk									/*!<SYSREQ reset flag > */
#define STC_RESET_FLAG_RSTB_Pos	(7U)
#define STC_RESET_FLAG_RSTB_Msk	(0x1U << STC_RESET_FLAG_RSTB_Pos)
#define STC_RESET_FLAG_RSTB		STC_RESET_FLAG_RSTB_Msk										/*!<RSTB reset flag > */

#define __HAL_RESET_GET_FLAG(__FLAG__)		(M0P_RESET->RESET_FLAG &   (__FLAG__))
#define __HAL_RESET_CLR_FLAG(__FLAG__)		(M0P_RESET->RESET_FLAG &= ~(__FLAG__))

u32  HAL_IncTick(void);																	//HAL Inc Tick++
u32  HAL_GetTick(void);																	//HAL Get Tick

u32  HAL_IncSecTick(void);																//HAL Inc Sec Tick++
u32  HAL_GetSecTick(void);																//HAL Get Sec Tick

void HAL_Delay(__IO u32 Delay);															//HAL Delay Tick

#endif /* __HC32L19X_HAL_H */
