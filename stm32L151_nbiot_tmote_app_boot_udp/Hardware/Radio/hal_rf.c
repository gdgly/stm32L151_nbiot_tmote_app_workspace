/*! @file hal_rf.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n movebroad tech Confidential
 * @n Copyright 2017 movebroad, Inc.
 * @n http://www.movebroad.com
 */
#include "string.h"
#include "hal_rf.h"
#include "radio.h"
#include "si446x_defs.h"
#include "si446x_api_lib.h"
#ifdef	SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#else
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif
#include "tmesh_rf_app.h"
#include "tmesh_cfg.h"
#include "delay.h"
// PB4  :SDN	,used to reset the mcu
// PB10:nIRQ
// PA15:SPI1_NSS
// PA5  :SPI1_SCK
// PA7  :SPI1_MOSI
// PA6  :SPI1_MISO


enum
{
	SEND_OVER,
	SENDING
};
enum Sendtype
{
 NO_WAIT,
 WAIT_OVER
};

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* ------------------------------------------------------------------------------------------------
 *                                       Local Variables
 * ------------------------------------------------------------------------------------------------
 */
U8 Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;
uint8_t g_Pakcet_len;	 //the len of the packet to be send
uint8_t g_Datasending = SENDING;
uint8_t  CHANNEL1 = 36;
//#define CHANNEL2 36
uint8_t g_Wait_enable  = WAIT_OVER;           
uint8_t  *g_P_frame;                  
volatile uint8_t  g_Send_num;
volatile uint8_t  g_Rest_num;

char trf_status = TRF_OK;

void tmesh_rf_TxCB(void);
void tmesh_rf_TxOverCB(void);

/**********************************************************************************************************
 @Function		void tmesh_spi_init(void)
 @Description 		initialize the mcu's spi interface 
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void tmesh_rf_interface_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*##-1- Configure the SPI peripheral #######################################*/
	/* Set the SPI parameters */
	SpiHandle.Instance               = SPIx;
	SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	SpiHandle.Init.CRCPolynomial     = 7;
	SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiHandle.Init.NSS               = SPI_NSS_SOFT;
	SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
	SpiHandle.Init.Mode = SPI_MODE_MASTER;

	if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
	{
		/* Initialization Error */
		//Error_Handler();
	}

	
	
	RF_SDN_GPIO_CLK_ENABLE();
	RF_nIRQ_GPIO_CLK_ENABLE();
	RF_NSS_GPIO_CLK_ENABLE();

	
	GPIO_InitStructure.Pin = SPIx_NSS_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;				
	HAL_GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.Pin = RF_SDN_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;	
	HAL_GPIO_Init(RF_SDN_GPIO_PORT, &GPIO_InitStructure);	

	
	
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Pin = RF_nIRQ_PIN;
	HAL_GPIO_Init(RF_nIRQ_GPIO_PORT, &GPIO_InitStructure);
	
	/* Enable and set EXTI lines 15 to 10 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(RF_IRQn, 2, 0);
	HAL_NVIC_DisableIRQ(RF_IRQn);

	
}

/**********************************************************************************************************
 @Function 		 tmesh_rf_get_status
 @Description			get the radio error status 
 @Input			 void
 @Return		 char TRF_OK TRF_ERROR
**********************************************************************************************************/
char tmesh_rf_get_status(void)
{
	return trf_status;
}

/**********************************************************************************************************
 @Function 		 void tmesh_rf_init(void)
 @Description			initialize the radio chip 
 @Input			 void
 @Return		 void
**********************************************************************************************************/
char tmesh_rf_init(void)
{
	__IO u32 nCountTimeout = HAL_GetTick();
	
	if(36 == tcfg_ReadRfChannel())
		CHANNEL1 = 36;
	else if(4 == tcfg_ReadRfChannel())
		CHANNEL1 = 4;
//	else if(6 == tcfg_ReadRfChannel())
//		CHANNEL1 = 6;
//	else if(16 == tcfg_ReadRfChannel())
//		CHANNEL1 = 16;
//	else if(26 == tcfg_ReadRfChannel())
//		CHANNEL1 = 26;
	else
		CHANNEL1 = 36;
	// step 0 :
	tmesh_rf_interface_init();	
 	// step 1: reset chip
 	vRadio_PowerUp();
	// 												
	// step 2: set up the rf chip
	/******get the version of radio********/
	si446x_part_info();
	if(Si446xCmd.PART_INFO.PART != 0x4438){
		trf_status = TRF_ERROR;
		return TRF_ERROR;
	}else{
		trf_status = TRF_OK;
	}

	/******set up the radio********/
	while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array))
	{
		vRadio_PowerUp();
		if (HAL_GetTick() > nCountTimeout + 10000) {
			trf_status = TRF_ERROR;
			return TRF_ERROR;
		}
	}
	
	// step 3: Get the chip's Interrupt status/pending flags form the radio and clear flags if requested
	si446x_get_int_status(0u, 0u, 0u);
	// step 4: set the rf chip to rx state
	vRadio_StartRX(CHANNEL1, 0);
	HAL_NVIC_EnableIRQ(RF_IRQn);
	return TRF_OK;
 }



/***************************无线数据发送**********************/
/*************name：		 MRFI_PrepareToTx		 ********************************************/
/************function: 		 send a wireless packet *********************************/
/************parameters:	 pPacket: pointer of pPacket to be sent   *************************/
/************					 len: length of  pPacket to be sent  *************************/
/************return:			 none	 **********************************************************/
/******************author: 	 xht **************************************************************/
void tmesh_rf_PrepareToTx(uint8_t * pPacket, uint8_t len)
{
	uint32_t s_count = 80000;
//	uint8_t rc;
	g_P_frame = pPacket;
	g_Datasending = SENDING;
 	g_Pakcet_len = len + 1; //lenth (1byte)+ payload(len)
 	g_Send_num = 0;
 	
	if(g_Pakcet_len > g_Send_num){
		g_Send_num += vRadio_StartTx_Variable_Packet(CHANNEL1, g_P_frame+g_Send_num, g_Pakcet_len-g_Send_num);
	}	 
	 /****if send wireless pkt in interrupt,dont wait,else wait for the pkt to be sent******/
	if(g_Wait_enable)
		while ((g_Datasending == SENDING) && (s_count--));
 
}

void tmesh_rf_TxISR(void)
{
//	uint8_t rc;
	if(g_Pakcet_len > g_Send_num){
		g_Send_num += vRadio_StartTx_Variable_Packet(CHANNEL1, g_P_frame+g_Send_num, g_Pakcet_len-g_Send_num);
	}
}

void tmesh_rf_TxOverISR(void)
{
	
	//g_Rest_num = 0;
	if(g_Datasending != SEND_OVER){
		g_Send_num = 0;
		g_Datasending = SEND_OVER;
		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		vRadio_StartRX(CHANNEL1, 0);
	}
}

/**************************************************************************************/
/*************name：       	xm_CheckSum        ****************************************/
/************function:        	check sum(2bytes) of the rf receive packet ***************************/
/************parameters:    	recv_data: point of receive data   ************************************/
/************return:           	none   *********************************************************/ 
/************author: 	     	xht	**************************************************************/

check_t xm_CheckSum(uint8_t *recv_data)
{
	uint16_t check_sum=0 ,i,len;
	len  = *recv_data;//packet_len
	/*****calculate the check sum after build the packet*/
	for(i=1;i<len-1;i++)
	{
		check_sum +=recv_data[i];//the first byte of len is not used for sum
	}
	*recv_data-=2;
	if(check_sum==(recv_data[i]*0x100+recv_data[i+1]))  return CHECK_SUCESS;
	else return CHECK_FAIL;
}


uint8_t Recv_len;
/***first almost full interrupt flag,g_LT_int = 1 indicates it is first almost full interrupt ,g_LT_int = 0 indicates it is not first almost full interrupt**/
uint8_t g_LT_int;
/*recv buffer*/
//uint8_t g_Recvlong[256];
mrfiPacket_t mrfiIncomingPacket;
uint8_t current_num;
//mrfiPacket_t mrfiIncomingPacket;

void tmesh_rf_ISR(void)
{
	/***** number of bytes to be received from cache of si4438*****/
	uint8_t s_numOfRecvBytes = 0;	 //ramining number of receive data
	//uint8_t *p_recvlong;
	uint8_t tmp;
	uint8_t framelen;
	uint8_t* g_Recvlong = mrfiIncomingPacket.frame;
	
	tmp = bRadio_Check();
	if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT)
	{
		tmesh_rf_TxOverISR();
	}else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_TX_FIFO_ALMOST_EMPTY_PEND_BIT)
	{
		tmesh_rf_TxISR();
	}else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT)
	{
		s_numOfRecvBytes = Recv_len + 1 - current_num;

		if (!g_LT_int)
		{
			/*如果是第一次接收，先读一个Byte，这个Byte是表示数据包的长度，
				这个Recv_len居然也用全局变量，陶醉*/
			si446x_read_rx_fifo(1, &Recv_len);
			
			si446x_read_rx_fifo(Recv_len, &g_Recvlong[1]);

			g_Recvlong[0] = Recv_len;
		}
		else
		{
			si446x_read_rx_fifo(s_numOfRecvBytes, &g_Recvlong[current_num]);
			current_num += s_numOfRecvBytes;
		}
		g_Wait_enable = NO_WAIT;
		
		framelen = g_Recvlong[0] - MMESH_CHECKSUM_SIZE; // 这个 2  又是什么鬼?	checksumsize
		current_num = 0;
		g_LT_int = 0;

		si446x_set_property(0x12, 0x02, 0x11, 0x00, 255);
		vRadio_StartRX(CHANNEL1, 0);

		if (xm_CheckSum(g_Recvlong))
		{
			// TODO: handle the data received
			tmesh_rf_data_handle_isr(&mrfiIncomingPacket);
			
		}
		memset(g_Recvlong, 0x00, sizeof(mrfiIncomingPacket.frame));

		g_Wait_enable = WAIT_OVER;
	}else if (tmp == SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_RX_FIFO_ALMOST_FULL_BIT)
	{
		if (!g_LT_int)
		{

			/*****first byte of 48B packet is len****/
			si446x_read_rx_fifo(1, g_Recvlong);
			Recv_len = g_Recvlong[0];
			current_num = 0;
		}

		s_numOfRecvBytes = Recv_len + 1 - current_num;
		if (s_numOfRecvBytes >= RADIO_RX_ALMOST_FULL_THRESHOLD)
		{
			if (!g_LT_int)
			/**********receive msg of 48B bytes from fifo ********/
				si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD - 1, &g_Recvlong[1]);
			/**********not first 48B packet*****************/
			else si446x_read_rx_fifo(RADIO_RX_ALMOST_FULL_THRESHOLD, &g_Recvlong[current_num]);
				current_num += RADIO_RX_ALMOST_FULL_THRESHOLD;

			if (!g_LT_int) g_LT_int++;
		}
		/***if it is first 48B packet,we has already get the len ,change it*****/
	}
}

