/**
  *********************************************************************************************************
  * @file    si446x_api_lib.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-18
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
#include "si446x_cmd.h"
#include "radio_hal_wrap.h"
#include "radio_hal_rf.h"
#include "radio_comm.h"
#include "delay.h"
#include "usart.h"
#include <stdarg.h>

union si446x_cmd_reply_union Si446xCmd;

static unsigned char Pro2Cmd[16];

/**********************************************************************************************************
 @Function			void si446x_reset(void)
 @Description			si446x_reset
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_reset(void)
{
	/* Radio SDN = 1 SI44XX Shutdown */
	Radio_Hal_Wrapper_ShutdownAssert();
	Delay_MS(15);
	
	/* Radio SDN = 0 SI44XX Working */
	Radio_Hal_Wrapper_ShutdownDeassert();
	Delay_MS(15);
	
	Radio_Comm_ClearsCTS();
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
	Pro2Cmd[5] = (u8)(XO_FREQ >>  8);
	Pro2Cmd[6] = (u8)(XO_FREQ >>  0);
	
	Radio_Comm_SendCmd(SI446X_CMD_ARG_COUNT_POWER_UP, Pro2Cmd);
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
		
		if (Radio_Comm_SendCmdGetResp(numOfBytes, Pro2Cmd, 0, 0) != 0xFF) {
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
	
	Radio_Comm_SendCmdGetResp(SI446X_CMD_ARG_COUNT_PART_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_PART_INFO, Pro2Cmd);
	
	Si446xCmd.PART_INFO.CHIPREV			= Pro2Cmd[0];
	Si446xCmd.PART_INFO.PART				=  ((u16) Pro2Cmd[1] << 8) & 0xFF00;
	Si446xCmd.PART_INFO.PART				|= ((u16) Pro2Cmd[2] << 0) & 0x00FF;
	Si446xCmd.PART_INFO.PBUILD			= Pro2Cmd[3];
	Si446xCmd.PART_INFO.ID				=  ((u16) Pro2Cmd[4] << 8) & 0xFF00;
	Si446xCmd.PART_INFO.ID				|= ((u16) Pro2Cmd[5] << 0) & 0x00FF;
	Si446xCmd.PART_INFO.CUSTOMER			= Pro2Cmd[6];
	Si446xCmd.PART_INFO.ROMID			= Pro2Cmd[7];
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
	Pro2Cmd[3] = (u8) (TX_LEN >> 8);
	Pro2Cmd[4] = (u8) (TX_LEN >> 0);
	Pro2Cmd[5] = 0x00;
	Pro2Cmd[6] = 0x00;
	
	Radio_Comm_SendCmd(SI446X_CMD_ARG_COUNT_START_TX, Pro2Cmd);
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
	Pro2Cmd[3] = (u8) (RX_LEN >> 8);
	Pro2Cmd[4] = (u8) (RX_LEN >> 0);
	Pro2Cmd[5] = NEXT_STATE1;
	Pro2Cmd[6] = NEXT_STATE2;
	Pro2Cmd[7] = NEXT_STATE3;
	
	Radio_Comm_SendCmd(SI446X_CMD_ARG_COUNT_START_RX, Pro2Cmd);
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
	
	Radio_Comm_SendCmdGetResp(SI446X_CMD_ARG_COUNT_GET_INT_STATUS, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GET_INT_STATUS, Pro2Cmd);
	
	Si446xCmd.GET_INT_STATUS.INT_PEND		= Pro2Cmd[0];
	Si446xCmd.GET_INT_STATUS.INT_STATUS	= Pro2Cmd[1];
	Si446xCmd.GET_INT_STATUS.PH_PEND		= Pro2Cmd[2];
	Si446xCmd.GET_INT_STATUS.PH_STATUS		= Pro2Cmd[3];
	Si446xCmd.GET_INT_STATUS.MODEM_PEND	= Pro2Cmd[4];
	Si446xCmd.GET_INT_STATUS.MODEM_STATUS	= Pro2Cmd[5];
	Si446xCmd.GET_INT_STATUS.CHIP_PEND		= Pro2Cmd[6];
	Si446xCmd.GET_INT_STATUS.CHIP_STATUS	= Pro2Cmd[7];
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
	
	Radio_Comm_SendCmdGetResp(SI446X_CMD_ARG_COUNT_GPIO_PIN_CFG, Pro2Cmd, SI446X_CMD_REPLY_COUNT_GPIO_PIN_CFG, Pro2Cmd);
	
	Si446xCmd.GPIO_PIN_CFG.GPIO[0]		= Pro2Cmd[0];
	Si446xCmd.GPIO_PIN_CFG.GPIO[1]		= Pro2Cmd[1];
	Si446xCmd.GPIO_PIN_CFG.GPIO[2]		= Pro2Cmd[2];
	Si446xCmd.GPIO_PIN_CFG.GPIO[3]		= Pro2Cmd[3];
	Si446xCmd.GPIO_PIN_CFG.NIRQ			= Pro2Cmd[4];
	Si446xCmd.GPIO_PIN_CFG.SDO			= Pro2Cmd[5];
	Si446xCmd.GPIO_PIN_CFG.GEN_CONFIG		= Pro2Cmd[6];
}

/**********************************************************************************************************
 @Function			void si446x_set_property(u8 GROUP, u8 NUM_PROPS, u32 START_PROP, ...)
 @Description			si446x_set_property
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_set_property(u8 GROUP, u8 NUM_PROPS, u32 START_PROP, ...)
{
	va_list argList;
	u8 cmdIndex;
	
	Pro2Cmd[0] = SI446X_CMD_ID_SET_PROPERTY;
	Pro2Cmd[1] = GROUP;
	Pro2Cmd[2] = NUM_PROPS;
	Pro2Cmd[3] = START_PROP;
	
	va_start(argList, START_PROP);
	cmdIndex = 4;
	while (NUM_PROPS--) {
		Pro2Cmd[cmdIndex] = va_arg(argList, int);
		cmdIndex++;
	}
	va_end(argList);
	
	Radio_Comm_SendCmd(cmdIndex, Pro2Cmd);
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
	
	Radio_Comm_SendCmd(SI446X_CMD_ARG_COUNT_CHANGE_STATE, Pro2Cmd);
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
	
	Radio_Comm_SendCmd(SI446X_CMD_ARG_COUNT_NOP, Pro2Cmd);
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
	
	Radio_Comm_SendCmdGetResp(SI446X_CMD_ARG_COUNT_FIFO_INFO, Pro2Cmd, SI446X_CMD_REPLY_COUNT_FIFO_INFO, Pro2Cmd);
	
	Si446xCmd.FIFO_INFO.RX_FIFO_COUNT		= Pro2Cmd[0];
	Si446xCmd.FIFO_INFO.TX_FIFO_SPACE		= Pro2Cmd[1];
}

/**********************************************************************************************************
 @Function			void si446x_write_tx_fifo(u8 numBytes, u8* pTxData)
 @Description			si446x_write_tx_fifo
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_write_tx_fifo(u8 numBytes, u8* pTxData)
{
	Radio_Comm_WriteData(SI446X_CMD_ID_WRITE_TX_FIFO, 0, numBytes, pTxData);
}

/**********************************************************************************************************
 @Function			void si446x_read_rx_fifo(u8 numBytes, u8* pRxData)
 @Description			si446x_read_rx_fifo
 @Input				void
 @Return				void
**********************************************************************************************************/
void si446x_read_rx_fifo(u8 numBytes, u8* pRxData)
{
	Radio_Comm_ReadData(SI446X_CMD_ID_READ_RX_FIFO, 0, numBytes, pRxData);
}

































/********************************************** END OF FLEE **********************************************/
