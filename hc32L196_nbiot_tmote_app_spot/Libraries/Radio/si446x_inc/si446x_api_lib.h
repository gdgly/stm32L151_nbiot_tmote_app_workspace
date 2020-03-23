#ifndef __SI446X_API_LIB_H
#define   __SI446X_API_LIB_H

#include "platform_config.h"
#include "radio_compiler_defs.h"

#define SI466X_FIFO_SIZE			64

typedef enum _si446x_errcode
{
	SI446X_SUCCESS				= 0U,
	SI446X_NO_PATCH			= 1U,
	SI446X_CTS_TIMEOUT			= 2U,
	SI446X_PATCH_FAIL			= 3U,
	SI446X_COMMAND_ERROR		= 4U
} si446x_errcode;

extern union si446x_cmd_reply_union Si446xCmd;

void si446x_reset(void);

void si446x_power_up(u8 BOOT_OPTIONS, u8 XTAL_OPTIONS, u32 XO_FREQ);

u8   si446x_configuration_init(const u8* pSetPropCmd);

void si446x_part_info(void);

void si446x_start_tx(u8 CHANNEL, u8 CONDITION, u16 TX_LEN);

void si446x_start_rx(u8 CHANNEL, u8 CONDITION, u16 RX_LEN, u8 NEXT_STATE1, u8 NEXT_STATE2, u8 NEXT_STATE3);

void si446x_get_int_status(u8 PH_CLR_PEND, u8 MODEM_CLR_PEND, u8 CHIP_CLR_PEND);

void si446x_gpio_pin_cfg(u8 GPIO0, u8 GPIO1, u8 GPIO2, u8 GPIO3, u8 NIRQ, u8 SDO, u8 GEN_CONFIG);

void si446x_set_property(u8 GROUP, u8 NUM_PROPS, u32 START_PROP, ...);

void si446x_change_state(u8 NEXT_STATE1);

void si446x_nop(void);

void si446x_fifo_info(u8 FIFO);

void si446x_write_tx_fifo(u8 numBytes, u8* pTxData);

void si446x_read_rx_fifo(u8 numBytes, u8* pRxData);

void si446x_get_property(u8 GROUP, u8 NUM_PROPS, u8 START_PROP);

void si446x_func_info(void);

void si446x_frr_a_read(u8 respByteCount);
void si446x_frr_b_read(u8 respByteCount);
void si446x_frr_c_read(u8 respByteCount);
void si446x_frr_d_read(u8 respByteCount);

void si446x_get_adc_reading(u8 ADC_EN);

void si446x_get_packet_info(u8 FIELD_NUMBER_MASK, u16 LEN, s16 DIFF_LEN);

void si446x_get_ph_status(u8 PH_CLR_PEND);

void si446x_get_modem_status(u8 MODEM_CLR_PEND);

void si446x_get_chip_status(u8 CHIP_CLR_PEND);

void si446x_ircal(u8 SEARCHING_STEP_SIZE, u8 SEARCHING_RSSI_AVG, u8 RX_CHAIN_SETTING1, u8 RX_CHAIN_SETTING2);

void si446x_ircal_manual(u8 IRCAL_AMP, u8 IRCAL_PH);

void si446x_request_device_state(void);

void si446x_tx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0, u8 PLL_SETTLE_TIME1, u8 PLL_SETTLE_TIME0);
void si446x_rx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0);

void si446x_start_tx_fast(void);
void si446x_start_rx_fast(void);

void si446x_get_int_status_fast_clear(void);
void si446x_get_int_status_fast_clear_read(void);

void si446x_gpio_pin_cfg_fast(void);

void si446x_get_ph_status_fast_clear(void);
void si446x_get_ph_status_fast_clear_read(void);

void si446x_get_modem_status_fast_clear(void);
void si446x_get_modem_status_fast_clear_read(void);

void si446x_get_chip_status_fast_clear(void);
void si446x_get_chip_status_fast_clear_read(void);

void si446x_fifo_info_fast_reset(U8 FIFO);

void si446x_fifo_info_fast_read(void);

#endif /* __SI446X_API_LIB_H */
