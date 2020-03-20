#ifndef __RADIO_HAL_RF_H
#define   __RADIO_HAL_RF_H

#include "sys.h"
#include "gpio.h"
#include "radio_hal_wrap.h"
#include "radio_rfa_common.h"

#define RADIO_SI4438_SDN_GPIOx	GpioPortB
#define RADIO_SI4438_SDN_PIN		GpioPin4
#define RADIO_SI4438_SDN_AF		GpioAf0

#define RADIO_SI4438_NSS_GPIOx	GpioPortA
#define RADIO_SI4438_NSS_PIN		GpioPin15
#define RADIO_SI4438_NSS_AF		GpioAf0

#define RADIO_SI4438_IRQ_GPIOx	GpioPortB
#define RADIO_SI4438_IRQ_PIN		GpioPin10
#define RADIO_SI4438_IRQ_AF		GpioAf0

#define RADIO_SI4438_IRQn		PORTB_IRQn
#define RADIO_SI4438_IRQMode		GpioIrqFalling
#define RADIO_SI4438_IRQLevel		IrqLevel3

#define RADIO_NRESET_COUNT		3
#define RADIO_CONFIG_TIMER		10000

#define MMESH_CHECKSUM_SIZE		2

typedef enum _radio_trf_errcode
{
	rTRF_OK					= 0U,
	rTRF_ERROR				= 1U
} radio_trf_errcode;

typedef enum _radio_trf_initede
{
	rTRF_Uninited				= 0U,
	rTRF_Isinited				= 1U
} radio_trf_initede;

typedef enum _radio_trf_sendcode
{
	rTRF_Sendover				= 0U,
	rTRF_Sending				= 1U
} radio_trf_sendcode;

typedef enum _radio_trf_sendtype
{
	rTRF_WaitNo				= 0U,
	rTRF_WaitOver				= 1U
} radio_trf_sendtype;

typedef enum _radio_trf_check
{
	rTRF_Check_Fail			= 0U,
	rTRF_Check_Success			= 1U
} radio_trf_check;

typedef enum _radio_trf_protocol_type
{
	OPTIONAL_PRT				= 0U,
	SIMPLICITI_PRT				= 1U,
	XMESH_PRT					= 2U,
	XMESHLITE_PRT				= 3U,
	UPGRADE_PRT				= 4U,
	XMESHCFG_PRT				= 5U,
	RSVED6					= 6U,
	RSVED7					= 7U
} radio_trf_protocol_type;

typedef struct _radio_client
{
	__IO s8					rf_status;
	__IO s8					rf_inited;
	__IO u8					rf_channel1;
	__IO s8					rf_corestate;
	__IO u8					rf_ctsWentHigh;
	
	u8*						rf_g_Poin_frame;
	__IO u8					rf_g_Send_Num;
	__IO u8					rf_g_Rest_Num;
	__IO u8					rf_g_Pack_Len;
	
	__IO u8					rf_g_Data_sending;
	__IO u8					rf_g_Wait_enable;
	
	__IO u8					rf_recv_len;
	__IO u8					rf_current_num;
	__IO u8					rf_LT_int;
	
	mrfiPacket_t				mrfiIncomingPacket;
} radioClientsTypeDef;

extern radioClientsTypeDef si4438Client;






radio_trf_errcode Radio_Hal_RF_Init(radioClientsTypeDef* pClient);								//Radio RF 初始化

radio_trf_errcode Radio_Hal_RF_ResetChip(radioClientsTypeDef* pClient);							//Radio RF 复位检查芯片

void Radio_Hal_RF_Interface_Init(void);														//Radio RF 接口初始化

void Radio_Hal_RF_Interrupt_Enable(void);													//Radio RF 中断引脚使能

void Radio_Hal_RF_Interrupt_Disable(void);													//Radio RF 中断引脚失能

void Radio_Hal_RF_Set_Sleep(void);															//Radio RF 设置Sleep模式

char Radio_Hal_RF_Get_Sleep(void);															//Radio RF 获取Sleep模式





radio_trf_errcode Radio_Hal_RF_PrepareToTx(u8* pPacket, u8 len);									//Radio RF 发送数据包

void Radio_Hal_RF_TxISR(void);															//Radio RF 发送数据中断

void Radio_Hal_RF_TxOverISR(void);															//Radio RF 发送结束中断

void Radio_Hal_RF_ISR(void);																//Radio RF 中断处理

#endif /* __RADIO_HAL_RF_H */
