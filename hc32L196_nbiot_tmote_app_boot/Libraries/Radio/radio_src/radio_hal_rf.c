/**
  *********************************************************************************************************
  * @file    radio_hal_rf.c
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
#include "radio_hal_rf.h"
#include "radio_hal_wrap.h"
#include "radio_core.h"
#include "radio_comm.h"
#include "si446x_api_lib.h"
#include "delay.h"
#include "usart.h"

#if SI4438_TYPE == SI4438_B1
#include "radio_config_Si4438_475_100k_B1_10dbm.h"
#endif
#if SI4438_TYPE == SI4438_C2
#include "radio_config_Si4438_475_100k_C2_10dbm.h"
#endif
















static const u8 Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;



/**********************************************************************************************************
 @Function		static void Radio_Hal_RF_Port_Init(void)
 @Description 		Radio_Hal_RF_Port_Init							: Radio RF 引脚初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
static void Radio_Hal_RF_Port_Init(void)
{
	stc_gpio_cfg_t GPIO_Initure;
	
	DDL_ZERO_STRUCT(GPIO_Initure);
	
	/* Radio RF SDN => PB04 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_SDN_GPIOx, RADIO_SI4438_SDN_PIN, RADIO_SI4438_SDN_AF);
	
	/* Radio RF NSS => PA15 */
	GPIO_Initure.enDir			= GpioDirOut;
	GPIO_Initure.enDrv			= GpioDrvH;
	Gpio_Init(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_NSS_GPIOx, RADIO_SI4438_NSS_PIN, RADIO_SI4438_NSS_AF);
	
	/* Radio RF IRQ => PB10 */
	GPIO_Initure.enDir			= GpioDirIn;
	GPIO_Initure.enDrv			= GpioDrvH;
	GPIO_Initure.enPu			= GpioPuEnable;
	GPIO_Initure.enPd			= GpioPdDisable;
	GPIO_Initure.enOD			= GpioOdDisable;
	GPIO_Initure.enCtrlMode		= GpioAHB;
	Gpio_Init(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, &GPIO_Initure);
	Gpio_SetAfMode(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_AF);
	
	/* Radio RF Enable IRQn */
	EnableNvic(RADIO_SI4438_IRQ_Channel, RADIO_SI4438_IRQ_Level, TRUE);
	
	Radio_Hal_RF_Interrupt_Disable();
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interface_Init(void)
 @Description 		Radio_Hal_RF_Interface_Init						: Radio RF 接口初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interface_Init(void)
{
	/* Radio Port (SDN/NSS/IRQ) Init */
	Radio_Hal_RF_Port_Init();
	
	/* Radio NSS = 1 SPIx Disable */
	Radio_Hal_Wrapper_nSELAssert();
	
	/* Radio SDN = 0 SI4438 Working */
	Radio_Hal_Wrapper_ShutdownDeassert();
	
	/* Radio SPIx Init */
	Radio_Hal_Wrapper_Init();
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Enable(void)
 @Description 		Radio_Hal_RF_Interrupt_Enable						: Radio RF 中断引脚使能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Enable(void)
{
	Gpio_EnableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_Mode);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Interrupt_Disable(void)
 @Description 		Radio_Hal_RF_Interrupt_Disable					: Radio RF 中断引脚失能
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Interrupt_Disable(void)
{
	Gpio_DisableIrq(RADIO_SI4438_IRQ_GPIOx, RADIO_SI4438_IRQ_PIN, RADIO_SI4438_IRQ_Mode);
}

/**********************************************************************************************************
 @Function		void Radio_Hal_RF_Init(void)
 @Description 		Radio_Hal_RF_Init								: Radio RF 初始化
 @Input			void
 @Return		  	void
**********************************************************************************************************/
void Radio_Hal_RF_Init(void)
{
	
	
	/* step 0: radio interface init */
	Radio_Hal_RF_Interface_Init();
	
	/* step 1: radio reset chip */
	radio_core_PowerUp();
	
	/* step 2: radio check chip */
	si446x_part_info();
	
	if (Si446xCmd.PART_INFO.PART != 0x4438) {
		
	}
	else {
		
	}
	
	/* step 3: radio set up */
	while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array)) {
		
		
		
		
	}
	
	
	
	
	
	
}




































































/********************************************** END OF FLEE **********************************************/
