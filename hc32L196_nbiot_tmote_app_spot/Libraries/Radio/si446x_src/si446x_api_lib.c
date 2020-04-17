/**
  *********************************************************************************************************
  * @file    si446x_api_lib.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-04-02
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "si446x_api_lib.h"
#include "radio_comm.h"
#include "radio_hal_wrap.h"
#include "radio_hal_rf.h"
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

union si446x_cmd_reply_union Si446xCmd;

static u8 Pro2Cmd[16];

/**********************************************************************************************************
 @Function			void si446x_reset(void)
 @Description			si446x_reset
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_reset(void)
{
	Radio_Hal_Wrapper_ShutdownAssert();
	Delay_MS(15);
	
	Radio_Hal_Wrapper_ShutdownDeassert();
	Delay_MS(15);
	
	radio_comm_ClearCTS();
}

/**********************************************************************************************************
 @Function			void si446x_power_up(u8 BOOT_OPTIONS, u8 XTAL_OPTIONS, u32 XO_FREQ)
 @Description			si446x_power_up
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_power_up(u8 BOOT_OPTIONS, u8 XTAL_OPTIONS, u32 XO_FREQ)
{
	Pro2Cmd[0] = SI446X_CMD_ID_POWER_UP;
	Pro2Cmd[1] = BOOT_OPTIONS;
	Pro2Cmd[2] = XTAL_OPTIONS;
	Pro2Cmd[3] = (u8)(XO_FREQ >> 24);
	Pro2Cmd[4] = (u8)(XO_FREQ >> 16);
	Pro2Cmd[5] = (u8)(XO_FREQ >> 8);
	Pro2Cmd[6] = (u8)(XO_FREQ);
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_POWER_UP, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			u8 si446x_configuration_init(const u8* pSetPropCmd)
 @Description			si446x_configuration_init
 @Input				void
 @Return				void
**********************************************************************************************************/
u8 si446x_configuration_init(const u8* pSetPropCmd)
{
	u8 col;
	u8 numOfBytes;
	
	while (*pSetPropCmd != 0x00) {
		
		numOfBytes = *pSetPropCmd++;
		
		if (numOfBytes > 16u) {
			return SI446X_COMMAND_ERROR;
		}
		
		for (col = 0u; col < numOfBytes; col++) {
			Pro2Cmd[col] = *pSetPropCmd;
			pSetPropCmd++;
		}
		
		if (radio_comm_SendCmdGetResp(numOfBytes, Pro2Cmd, 0, 0) != 0xFF) {
			return SI446X_CTS_TIMEOUT;
		}
		
		if (Radio_Hal_Wrapper_nIRQLevel() == 0) {
			si446x_get_int_status(0, 0, 0);
			if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_MASK) {
				return SI446X_COMMAND_ERROR;
			}
		}
	}
	
	return SI446X_SUCCESS;
}

/**********************************************************************************************************
 @Function			void si446x_part_info(void)
 @Description			si446x_part_info
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_part_info(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_PART_INFO;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_PART_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_PART_INFO, Pro2Cmd );
	
	Si446xCmd.PART_INFO.CHIPREV = Pro2Cmd[0];
	Si446xCmd.PART_INFO.PART = ((uint16_t) Pro2Cmd[1] << 8) & 0xFF00;
	Si446xCmd.PART_INFO.PART |= (uint16_t) Pro2Cmd[2] & 0x00FF;
	Si446xCmd.PART_INFO.PBUILD = Pro2Cmd[3];
	Si446xCmd.PART_INFO.ID = ((uint16_t) Pro2Cmd[4] << 8) & 0xFF00;
	Si446xCmd.PART_INFO.ID |= (uint16_t) Pro2Cmd[5] & 0x00FF;
	Si446xCmd.PART_INFO.CUSTOMER = Pro2Cmd[6];
	Si446xCmd.PART_INFO.ROMID = Pro2Cmd[7];
}

/**********************************************************************************************************
 @Function			void si446x_start_tx(u8 CHANNEL, u8 CONDITION, u16 TX_LEN)
 @Description			si446x_start_tx
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_start_tx(u8 CHANNEL, u8 CONDITION, u16 TX_LEN)
{
	Pro2Cmd[0] = SI446X_CMD_ID_START_TX;
	Pro2Cmd[1] = CHANNEL;
	Pro2Cmd[2] = CONDITION;
	Pro2Cmd[3] = (uint8_t) (TX_LEN >> 8);
	Pro2Cmd[4] = (uint8_t) (TX_LEN);
	Pro2Cmd[5] = 0x00;
	
	Pro2Cmd[6] = 0x00;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_TX, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_start_rx(u8 CHANNEL, u8 CONDITION, u16 RX_LEN, u8 NEXT_STATE1, u8 NEXT_STATE2, u8 NEXT_STATE3)
 @Description			si446x_start_rx
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_start_rx(u8 CHANNEL, u8 CONDITION, u16 RX_LEN, u8 NEXT_STATE1, u8 NEXT_STATE2, u8 NEXT_STATE3)
{
	Pro2Cmd[0] = SI446X_CMD_ID_START_RX;
	Pro2Cmd[1] = CHANNEL;
	Pro2Cmd[2] = CONDITION;
	Pro2Cmd[3] = (uint8_t) (RX_LEN >> 8);
	Pro2Cmd[4] = (uint8_t) (RX_LEN);
	Pro2Cmd[5] = NEXT_STATE1;
	Pro2Cmd[6] = NEXT_STATE2;
	Pro2Cmd[7] = NEXT_STATE3;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_RX, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_int_status(u8 PH_CLR_PEND, u8 MODEM_CLR_PEND, u8 CHIP_CLR_PEND)
 @Description			si446x_get_int_status
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_int_status(u8 PH_CLR_PEND, u8 MODEM_CLR_PEND, u8 CHIP_CLR_PEND)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_INT_STATUS;
	Pro2Cmd[1] = PH_CLR_PEND;
	Pro2Cmd[2] = MODEM_CLR_PEND;
	Pro2Cmd[3] = CHIP_CLR_PEND;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_INT_STATUS, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_INT_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_INT_STATUS.INT_PEND = Pro2Cmd[0];
	Si446xCmd.GET_INT_STATUS.INT_STATUS = Pro2Cmd[1];
	Si446xCmd.GET_INT_STATUS.PH_PEND = Pro2Cmd[2];
	Si446xCmd.GET_INT_STATUS.PH_STATUS = Pro2Cmd[3];
	Si446xCmd.GET_INT_STATUS.MODEM_PEND = Pro2Cmd[4];
	Si446xCmd.GET_INT_STATUS.MODEM_STATUS = Pro2Cmd[5];
	Si446xCmd.GET_INT_STATUS.CHIP_PEND = Pro2Cmd[6];
	Si446xCmd.GET_INT_STATUS.CHIP_STATUS = Pro2Cmd[7];
}

/**********************************************************************************************************
 @Function			void si446x_gpio_pin_cfg(u8 GPIO0, u8 GPIO1, u8 GPIO2, u8 GPIO3, u8 NIRQ, u8 SDO, u8 GEN_CONFIG)
 @Description			si446x_gpio_pin_cfg
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_gpio_pin_cfg(u8 GPIO0, u8 GPIO1, u8 GPIO2, u8 GPIO3, u8 NIRQ, u8 SDO, u8 GEN_CONFIG)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GPIO_PIN_CFG;
	Pro2Cmd[1] = GPIO0;
	Pro2Cmd[2] = GPIO1;
	Pro2Cmd[3] = GPIO2;
	Pro2Cmd[4] = GPIO3;
	Pro2Cmd[5] = NIRQ;
	Pro2Cmd[6] = SDO;
	Pro2Cmd[7] = GEN_CONFIG;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GPIO_PIN_CFG, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GPIO_PIN_CFG, Pro2Cmd );
	
	Si446xCmd.GPIO_PIN_CFG.GPIO[0] = Pro2Cmd[0];
	Si446xCmd.GPIO_PIN_CFG.GPIO[1] = Pro2Cmd[1];
	Si446xCmd.GPIO_PIN_CFG.GPIO[2] = Pro2Cmd[2];
	Si446xCmd.GPIO_PIN_CFG.GPIO[3] = Pro2Cmd[3];
	Si446xCmd.GPIO_PIN_CFG.NIRQ = Pro2Cmd[4];
	Si446xCmd.GPIO_PIN_CFG.SDO = Pro2Cmd[5];
	Si446xCmd.GPIO_PIN_CFG.GEN_CONFIG = Pro2Cmd[6];
}

/**********************************************************************************************************
 @Function			void si446x_set_property(u8 GROUP, u8 NUM_PROPS, u8 START_PROP, ...)
 @Description			si446x_set_property
 @Input				void
 @Return				void
**********************************************************************************************************/
#ifdef __C51__
#pragma maxargs (13)
#endif
void si446x_set_property(u8 GROUP, u8 NUM_PROPS, u8 START_PROP, ...)
{
	va_list argList;
	uint8_t cmdIndex;
	
	Pro2Cmd[0] = SI446X_CMD_ID_SET_PROPERTY;
	Pro2Cmd[1] = GROUP;
	Pro2Cmd[2] = NUM_PROPS;
	Pro2Cmd[3] = START_PROP;
	
	va_start(argList, START_PROP);
	cmdIndex = 4;
	while (NUM_PROPS--)
	{
		Pro2Cmd[cmdIndex] = va_arg(argList, int);
		cmdIndex++;
	}
	va_end(argList);
	
	radio_comm_SendCmd( cmdIndex, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_change_state(u8 NEXT_STATE1)
 @Description			si446x_change_state
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_change_state(u8 NEXT_STATE1)
{
	Pro2Cmd[0] = SI446X_CMD_ID_CHANGE_STATE;
	Pro2Cmd[1] = NEXT_STATE1;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_CHANGE_STATE, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_nop(void)
 @Description			si446x_nop
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_nop(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_NOP;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_NOP, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_fifo_info(u8 FIFO)
 @Description			si446x_fifo_info
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_fifo_info(u8 FIFO)
{
	Pro2Cmd[0] = SI446X_CMD_ID_FIFO_INFO;
	Pro2Cmd[1] = FIFO;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_FIFO_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_FIFO_INFO, Pro2Cmd );
	
	Si446xCmd.FIFO_INFO.RX_FIFO_COUNT = Pro2Cmd[0];
	Si446xCmd.FIFO_INFO.TX_FIFO_SPACE = Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_write_tx_fifo(u8 numBytes, u8* pTxData)
 @Description			si446x_write_tx_fifo
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_write_tx_fifo(u8 numBytes, u8* pTxData)
{
	radio_comm_WriteData( SI446X_CMD_ID_WRITE_TX_FIFO, 0, numBytes, pTxData );
}

/**********************************************************************************************************
 @Function			void si446x_read_rx_fifo(u8 numBytes, u8* pRxData)
 @Description			si446x_read_rx_fifo
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_read_rx_fifo(u8 numBytes, u8* pRxData)
{
	radio_comm_ReadData( SI446X_CMD_ID_READ_RX_FIFO, 0, numBytes, pRxData );
}

/**********************************************************************************************************
 @Function			void si446x_get_property(u8 GROUP, u8 NUM_PROPS, u8 START_PROP)
 @Description			si446x_get_property
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_property(u8 GROUP, u8 NUM_PROPS, u8 START_PROP)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_PROPERTY;
	Pro2Cmd[1] = GROUP;
	Pro2Cmd[2] = NUM_PROPS;
	Pro2Cmd[3] = START_PROP;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_PROPERTY, Pro2Cmd, Pro2Cmd[2], Pro2Cmd );
	
	Si446xCmd.GET_PROPERTY.DATA[0 ]   = Pro2Cmd[0];
	Si446xCmd.GET_PROPERTY.DATA[1 ]   = Pro2Cmd[1];
	Si446xCmd.GET_PROPERTY.DATA[2 ]   = Pro2Cmd[2];
	Si446xCmd.GET_PROPERTY.DATA[3 ]   = Pro2Cmd[3];
	Si446xCmd.GET_PROPERTY.DATA[4 ]   = Pro2Cmd[4];
	Si446xCmd.GET_PROPERTY.DATA[5 ]   = Pro2Cmd[5];
	Si446xCmd.GET_PROPERTY.DATA[6 ]   = Pro2Cmd[6];
	Si446xCmd.GET_PROPERTY.DATA[7 ]   = Pro2Cmd[7];
	Si446xCmd.GET_PROPERTY.DATA[8 ]   = Pro2Cmd[8];
	Si446xCmd.GET_PROPERTY.DATA[9 ]   = Pro2Cmd[9];
	Si446xCmd.GET_PROPERTY.DATA[10]   = Pro2Cmd[10];
	Si446xCmd.GET_PROPERTY.DATA[11]   = Pro2Cmd[11];
	Si446xCmd.GET_PROPERTY.DATA[12]   = Pro2Cmd[12];
	Si446xCmd.GET_PROPERTY.DATA[13]   = Pro2Cmd[13];
	Si446xCmd.GET_PROPERTY.DATA[14]   = Pro2Cmd[14];
	Si446xCmd.GET_PROPERTY.DATA[15]   = Pro2Cmd[15];
}

/**********************************************************************************************************
 @Function			void si446x_func_info(void)
 @Description			si446x_func_info
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_func_info(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_FUNC_INFO;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_FUNC_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_FUNC_INFO, Pro2Cmd );
	
	Si446xCmd.FUNC_INFO.REVEXT        = Pro2Cmd[0];
	Si446xCmd.FUNC_INFO.REVBRANCH     = Pro2Cmd[1];
	Si446xCmd.FUNC_INFO.REVINT        = Pro2Cmd[2];
	Si446xCmd.FUNC_INFO.FUNC          = Pro2Cmd[5];
}

/**********************************************************************************************************
 @Function			void si446x_frr_a_read(u8 respByteCount)
 @Description			si446x_frr_a_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_frr_a_read(u8 respByteCount)
{
	radio_comm_ReadData( SI446X_CMD_ID_FRR_A_READ, 0, respByteCount, Pro2Cmd );
	
	Si446xCmd.FRR_A_READ.FRR_A_VALUE = Pro2Cmd[0];
	Si446xCmd.FRR_A_READ.FRR_B_VALUE = Pro2Cmd[1];
	Si446xCmd.FRR_A_READ.FRR_C_VALUE = Pro2Cmd[2];
	Si446xCmd.FRR_A_READ.FRR_D_VALUE = Pro2Cmd[3];
}

/**********************************************************************************************************
 @Function			void si446x_frr_b_read(u8 respByteCount)
 @Description			si446x_frr_b_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_frr_b_read(u8 respByteCount)
{
	radio_comm_ReadData( SI446X_CMD_ID_FRR_B_READ, 0, respByteCount, Pro2Cmd );
	
	Si446xCmd.FRR_B_READ.FRR_B_VALUE = Pro2Cmd[0];
	Si446xCmd.FRR_B_READ.FRR_C_VALUE = Pro2Cmd[1];
	Si446xCmd.FRR_B_READ.FRR_D_VALUE = Pro2Cmd[2];
	Si446xCmd.FRR_B_READ.FRR_A_VALUE = Pro2Cmd[3];
}

/**********************************************************************************************************
 @Function			void si446x_frr_c_read(u8 respByteCount)
 @Description			si446x_frr_c_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_frr_c_read(u8 respByteCount)
{
	radio_comm_ReadData( SI446X_CMD_ID_FRR_C_READ, 0, respByteCount, Pro2Cmd );
	
	Si446xCmd.FRR_C_READ.FRR_C_VALUE = Pro2Cmd[0];
	Si446xCmd.FRR_C_READ.FRR_D_VALUE = Pro2Cmd[1];
	Si446xCmd.FRR_C_READ.FRR_A_VALUE = Pro2Cmd[2];
	Si446xCmd.FRR_C_READ.FRR_B_VALUE = Pro2Cmd[3];
}

/**********************************************************************************************************
 @Function			void si446x_frr_d_read(u8 respByteCount)
 @Description			si446x_frr_d_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_frr_d_read(u8 respByteCount)
{
	radio_comm_ReadData( SI446X_CMD_ID_FRR_D_READ, 0, respByteCount, Pro2Cmd );
	
	Si446xCmd.FRR_D_READ.FRR_D_VALUE = Pro2Cmd[0];
	Si446xCmd.FRR_D_READ.FRR_A_VALUE = Pro2Cmd[1];
	Si446xCmd.FRR_D_READ.FRR_B_VALUE = Pro2Cmd[2];
	Si446xCmd.FRR_D_READ.FRR_C_VALUE = Pro2Cmd[3];
}

/**********************************************************************************************************
 @Function			void si446x_get_adc_reading(u8 ADC_EN)
 @Description			si446x_get_adc_reading
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_adc_reading(u8 ADC_EN)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_ADC_READING;
	Pro2Cmd[1] = ADC_EN;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_ADC_READING, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_ADC_READING, Pro2Cmd );
	
	Si446xCmd.GET_ADC_READING.GPIO_ADC         = ((u16)Pro2Cmd[0] << 8) & 0xFF00;
	Si446xCmd.GET_ADC_READING.GPIO_ADC        |=  (u16)Pro2Cmd[1] & 0x00FF;
	Si446xCmd.GET_ADC_READING.BATTERY_ADC      = ((u16)Pro2Cmd[2] << 8) & 0xFF00;
	Si446xCmd.GET_ADC_READING.BATTERY_ADC     |=  (u16)Pro2Cmd[3] & 0x00FF;
	Si446xCmd.GET_ADC_READING.TEMP_ADC         = ((u16)Pro2Cmd[4] << 8) & 0xFF00;
	Si446xCmd.GET_ADC_READING.TEMP_ADC        |=  (u16)Pro2Cmd[5] & 0x00FF;
}

/**********************************************************************************************************
 @Function			void si446x_get_packet_info(u8 FIELD_NUMBER_MASK, u16 LEN, s16 DIFF_LEN)
 @Description			si446x_get_packet_info
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_packet_info(u8 FIELD_NUMBER_MASK, u16 LEN, s16 DIFF_LEN)
{
	Pro2Cmd[0] = SI446X_CMD_ID_PACKET_INFO;
	Pro2Cmd[1] = FIELD_NUMBER_MASK;
	Pro2Cmd[2] = (u8)(LEN >> 8);
	Pro2Cmd[3] = (u8)(LEN);
	Pro2Cmd[4] = (u8)((u16)DIFF_LEN >> 8);
	Pro2Cmd[5] = (u8)(DIFF_LEN);
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_PACKET_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_PACKET_INFO, Pro2Cmd );
	
	Si446xCmd.PACKET_INFO.LENGTH               = ((u16)Pro2Cmd[0] << 8) & 0xFF00;
	Si446xCmd.PACKET_INFO.LENGTH              |=  (u16)Pro2Cmd[1] & 0x00FF;
}

/**********************************************************************************************************
 @Function			void si446x_get_ph_status(u8 PH_CLR_PEND)
 @Description			si446x_get_ph_status
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_ph_status(u8 PH_CLR_PEND)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_PH_STATUS;
	Pro2Cmd[1] = PH_CLR_PEND;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_PH_STATUS, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_PH_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_PH_STATUS.PH_PEND            = Pro2Cmd[0];
	Si446xCmd.GET_PH_STATUS.PH_STATUS          = Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_get_modem_status(u8 MODEM_CLR_PEND)
 @Description			si446x_get_modem_status
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_modem_status(u8 MODEM_CLR_PEND)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_MODEM_STATUS;
	Pro2Cmd[1] = MODEM_CLR_PEND;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_MODEM_STATUS, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_MODEM_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_MODEM_STATUS.MODEM_PEND = Pro2Cmd[0];
	Si446xCmd.GET_MODEM_STATUS.MODEM_STATUS = Pro2Cmd[1];
	Si446xCmd.GET_MODEM_STATUS.CURR_RSSI = Pro2Cmd[2];
	Si446xCmd.GET_MODEM_STATUS.LATCH_RSSI = Pro2Cmd[3];
	Si446xCmd.GET_MODEM_STATUS.ANT1_RSSI = Pro2Cmd[4];
	Si446xCmd.GET_MODEM_STATUS.ANT2_RSSI = Pro2Cmd[5];
	Si446xCmd.GET_MODEM_STATUS.AFC_FREQ_OFFSET = ((uint16_t) Pro2Cmd[6] << 8) & 0xFF00;
	Si446xCmd.GET_MODEM_STATUS.AFC_FREQ_OFFSET |= (uint16_t) Pro2Cmd[7] & 0x00FF;
}

/**********************************************************************************************************
 @Function			void si446x_get_chip_status(u8 CHIP_CLR_PEND)
 @Description			si446x_get_chip_status
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_chip_status(u8 CHIP_CLR_PEND)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_CHIP_STATUS;
	Pro2Cmd[1] = CHIP_CLR_PEND;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_CHIP_STATUS, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_CHIP_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_CHIP_STATUS.CHIP_PEND        = Pro2Cmd[0];
	Si446xCmd.GET_CHIP_STATUS.CHIP_STATUS      = Pro2Cmd[1];
	Si446xCmd.GET_CHIP_STATUS.CMD_ERR_STATUS   = Pro2Cmd[2];
}

/**********************************************************************************************************
 @Function			void si446x_ircal(u8 SEARCHING_STEP_SIZE, u8 SEARCHING_RSSI_AVG, u8 RX_CHAIN_SETTING1, u8 RX_CHAIN_SETTING2)
 @Description			si446x_ircal
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_ircal(u8 SEARCHING_STEP_SIZE, u8 SEARCHING_RSSI_AVG, u8 RX_CHAIN_SETTING1, u8 RX_CHAIN_SETTING2)
{
	Pro2Cmd[0] = SI446X_CMD_ID_IRCAL;
	Pro2Cmd[1] = SEARCHING_STEP_SIZE;
	Pro2Cmd[2] = SEARCHING_RSSI_AVG;
	Pro2Cmd[3] = RX_CHAIN_SETTING1;
	Pro2Cmd[4] = RX_CHAIN_SETTING2;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_IRCAL, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_ircal_manual(u8 IRCAL_AMP, u8 IRCAL_PH)
 @Description			si446x_ircal_manual
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_ircal_manual(u8 IRCAL_AMP, u8 IRCAL_PH)
{
	Pro2Cmd[0] = SI446X_CMD_ID_IRCAL_MANUAL;
	Pro2Cmd[1] = IRCAL_AMP;
	Pro2Cmd[2] = IRCAL_PH;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_IRCAL_MANUAL, Pro2Cmd, SI446X_CMD_REPLY_COUNT_IRCAL_MANUAL, Pro2Cmd );
	
	Si446xCmd.IRCAL_MANUAL.IRCAL_AMP_REPLY     = Pro2Cmd[0];
	Si446xCmd.IRCAL_MANUAL.IRCAL_PH_REPLY      = Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_request_device_state(void)
 @Description			si446x_request_device_state
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_request_device_state(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_REQUEST_DEVICE_STATE;
	
	radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_REQUEST_DEVICE_STATE, Pro2Cmd, SI446X_CMD_REPLY_COUNT_REQUEST_DEVICE_STATE, Pro2Cmd );
	
	Si446xCmd.REQUEST_DEVICE_STATE.CURR_STATE       = Pro2Cmd[0];
	Si446xCmd.REQUEST_DEVICE_STATE.CURRENT_CHANNEL  = Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_tx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0, u8 PLL_SETTLE_TIME1, u8 PLL_SETTLE_TIME0)
 @Description			si446x_tx_hop
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_tx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0, u8 PLL_SETTLE_TIME1, u8 PLL_SETTLE_TIME0)
{
	Pro2Cmd[0] = SI446X_CMD_ID_TX_HOP;
	Pro2Cmd[1] = INTE;
	Pro2Cmd[2] = FRAC2;
	Pro2Cmd[3] = FRAC1;
	Pro2Cmd[4] = FRAC0;
	Pro2Cmd[5] = VCO_CNT1;
	Pro2Cmd[6] = VCO_CNT0;
	Pro2Cmd[7] = PLL_SETTLE_TIME1;
	Pro2Cmd[8] = PLL_SETTLE_TIME0;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_TX_HOP, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_rx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0)
 @Description			si446x_rx_hop
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_rx_hop(u8 INTE, u8 FRAC2, u8 FRAC1, u8 FRAC0, u8 VCO_CNT1, u8 VCO_CNT0)
{
	Pro2Cmd[0] = SI446X_CMD_ID_RX_HOP;
	Pro2Cmd[1] = INTE;
	Pro2Cmd[2] = FRAC2;
	Pro2Cmd[3] = FRAC1;
	Pro2Cmd[4] = FRAC0;
	Pro2Cmd[5] = VCO_CNT1;
	Pro2Cmd[6] = VCO_CNT0;
	
	radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_RX_HOP, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_start_tx_fast(void)
 @Description			si446x_start_tx_fast
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_start_tx_fast(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_START_TX;
	
	radio_comm_SendCmd( 1, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_start_rx_fast(void)
 @Description			si446x_start_rx_fast
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_start_rx_fast(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_START_RX;
	
	radio_comm_SendCmd( 1, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_int_status_fast_clear(void)
 @Description			si446x_get_int_status_fast_clear
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_int_status_fast_clear(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_INT_STATUS;
	
	radio_comm_SendCmd( 1, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_int_status_fast_clear_read(void)
 @Description			si446x_get_int_status_fast_clear_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_int_status_fast_clear_read(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_INT_STATUS;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_INT_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_INT_STATUS.INT_PEND       = Pro2Cmd[0];
	Si446xCmd.GET_INT_STATUS.INT_STATUS     = Pro2Cmd[1];
	Si446xCmd.GET_INT_STATUS.PH_PEND        = Pro2Cmd[2];
	Si446xCmd.GET_INT_STATUS.PH_STATUS      = Pro2Cmd[3];
	Si446xCmd.GET_INT_STATUS.MODEM_PEND     = Pro2Cmd[4];
	Si446xCmd.GET_INT_STATUS.MODEM_STATUS   = Pro2Cmd[5];
	Si446xCmd.GET_INT_STATUS.CHIP_PEND      = Pro2Cmd[6];
	Si446xCmd.GET_INT_STATUS.CHIP_STATUS    = Pro2Cmd[7];
}

/**********************************************************************************************************
 @Function			void si446x_gpio_pin_cfg_fast(void)
 @Description			si446x_gpio_pin_cfg_fast
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_gpio_pin_cfg_fast(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GPIO_PIN_CFG;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GPIO_PIN_CFG, Pro2Cmd );
	
	Si446xCmd.GPIO_PIN_CFG.GPIO[0]          = Pro2Cmd[0];
	Si446xCmd.GPIO_PIN_CFG.GPIO[1]          = Pro2Cmd[1];
	Si446xCmd.GPIO_PIN_CFG.GPIO[2]          = Pro2Cmd[2];
	Si446xCmd.GPIO_PIN_CFG.GPIO[3]          = Pro2Cmd[3];
	Si446xCmd.GPIO_PIN_CFG.NIRQ             = Pro2Cmd[4];
	Si446xCmd.GPIO_PIN_CFG.SDO              = Pro2Cmd[5];
	Si446xCmd.GPIO_PIN_CFG.GEN_CONFIG       = Pro2Cmd[6];
}

/**********************************************************************************************************
 @Function			void si446x_get_ph_status_fast_clear(void)
 @Description			si446x_get_ph_status_fast_clear
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_ph_status_fast_clear(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_PH_STATUS;
	Pro2Cmd[1] = 0;
	
	radio_comm_SendCmd( 2, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_ph_status_fast_clear_read(void)
 @Description			si446x_get_ph_status_fast_clear_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_ph_status_fast_clear_read(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_PH_STATUS;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_PH_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_PH_STATUS.PH_PEND         = Pro2Cmd[0];
	Si446xCmd.GET_PH_STATUS.PH_STATUS       = Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_get_modem_status_fast_clear(void)
 @Description			si446x_get_modem_status_fast_clear
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_modem_status_fast_clear(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_MODEM_STATUS;
	Pro2Cmd[1] = 0;
	
	radio_comm_SendCmd( 2, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_modem_status_fast_clear_read(void)
 @Description			si446x_get_modem_status_fast_clear_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_modem_status_fast_clear_read(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_MODEM_STATUS;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_MODEM_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_MODEM_STATUS.MODEM_PEND   = Pro2Cmd[0];
	Si446xCmd.GET_MODEM_STATUS.MODEM_STATUS = Pro2Cmd[1];
	Si446xCmd.GET_MODEM_STATUS.CURR_RSSI    = Pro2Cmd[2];
	Si446xCmd.GET_MODEM_STATUS.LATCH_RSSI   = Pro2Cmd[3];
	Si446xCmd.GET_MODEM_STATUS.ANT1_RSSI    = Pro2Cmd[4];
	Si446xCmd.GET_MODEM_STATUS.ANT2_RSSI    = Pro2Cmd[5];
	Si446xCmd.GET_MODEM_STATUS.AFC_FREQ_OFFSET = ((U16)Pro2Cmd[6] << 8) & 0xFF00;
	Si446xCmd.GET_MODEM_STATUS.AFC_FREQ_OFFSET |= (U16)Pro2Cmd[7] & 0x00FF;
}

/**********************************************************************************************************
 @Function			void si446x_get_chip_status_fast_clear(void)
 @Description			si446x_get_chip_status_fast_clear
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_chip_status_fast_clear(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_CHIP_STATUS;
	Pro2Cmd[1] = 0;
	
	radio_comm_SendCmd( 2, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_get_chip_status_fast_clear_read(void)
 @Description			si446x_get_chip_status_fast_clear_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_get_chip_status_fast_clear_read(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_GET_CHIP_STATUS;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_CHIP_STATUS, Pro2Cmd );
	
	Si446xCmd.GET_CHIP_STATUS.CHIP_PEND         = Pro2Cmd[0];
	Si446xCmd.GET_CHIP_STATUS.CHIP_STATUS       = Pro2Cmd[1];
	Si446xCmd.GET_CHIP_STATUS.CMD_ERR_STATUS    = Pro2Cmd[2];
}

/**********************************************************************************************************
 @Function			void si446x_fifo_info_fast_reset(u8 FIFO)
 @Description			si446x_fifo_info_fast_reset
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_fifo_info_fast_reset(u8 FIFO)
{
	Pro2Cmd[0] = SI446X_CMD_ID_FIFO_INFO;
	Pro2Cmd[1] = FIFO;
	
	radio_comm_SendCmd( 2, Pro2Cmd );
}

/**********************************************************************************************************
 @Function			void si446x_fifo_info_fast_read(void)
 @Description			si446x_fifo_info_fast_read
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_fifo_info_fast_read(void)
{
	Pro2Cmd[0] = SI446X_CMD_ID_FIFO_INFO;
	
	radio_comm_SendCmdGetResp( 1, Pro2Cmd, SI446X_CMD_REPLY_COUNT_FIFO_INFO, Pro2Cmd );
	
	Si446xCmd.FIFO_INFO.RX_FIFO_COUNT           = Pro2Cmd[0];
	Si446xCmd.FIFO_INFO.TX_FIFO_SPACE           = Pro2Cmd[1];
}

/********************************************** END OF FLEE **********************************************/
