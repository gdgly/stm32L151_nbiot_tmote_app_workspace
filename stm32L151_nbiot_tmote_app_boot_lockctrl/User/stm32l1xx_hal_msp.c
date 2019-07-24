/**
  *********************************************************************************************************
  * @file    stm32l1xx_hal_msp.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-11-01
  * @brief   回调函数
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "main.h"
#include "hal_rf.h"
#include "hal_spiflash.h"

#define	GPIOA_PIN		GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
					GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
					GPIO_PIN_12 | GPIO_PIN_15
#define	GPIOB_PIN		GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
					GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
					GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define	GPIOC_PIN		GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
					GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
					GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define	GPIOD_PIN		GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
					GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
					GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define	GPIOE_PIN		GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_3  | GPIO_PIN_4  | GPIO_PIN_5  | \
					GPIO_PIN_6  | GPIO_PIN_7  | GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 | \
					GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
#define	GPIOH_PIN		GPIO_PIN_0  | GPIO_PIN_1

/**********************************************************************************************************
 @Function			void HAL_MspInit(void)
 @Description			HAL_MspInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_MspInit(void)
{
	/* GPIO Low Power */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
//	__HAL_RCC_GPIOD_CLK_ENABLE();
//	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIOA_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_VERY_LOW;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIOB_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIOC_PIN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	GPIO_InitStructure.Pin = GPIOD_PIN;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	
//	GPIO_InitStructure.Pin = GPIOE_PIN;
//	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIOH_PIN;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_9;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOC_CLK_DISABLE();
//	__HAL_RCC_GPIOD_CLK_DISABLE();
//	__HAL_RCC_GPIOE_CLK_DISABLE();
	__HAL_RCC_GPIOH_CLK_DISABLE();
}

/**********************************************************************************************************
 @Function			void HAL_MspDeInit(void)
 @Description			HAL_MspDeInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_MspDeInit(void)
{
	
}


/**********************************************************************************************************
 @Function			void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
 @Description			定时器底层驱动, 开启时钟, 设置中断优先级
					此函数会被HAL_TIM_Base_Init()函数调用
 @Input				htim : TIM句柄
 @Return				void
**********************************************************************************************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
		__HAL_RCC_TIM2_CLK_ENABLE();										//使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);								//设置中断优先级, 强占优先级1, 次优先级0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);									//开启TIM2中断
	}
}

/**********************************************************************************************************
 @Function			void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
 @Description			定时器底层驱动, 关闭时钟
					此函数会被HAL_TIM_Base_DeInit()函数调用
 @Input				htim : TIM句柄
 @Return				void
**********************************************************************************************************/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
		__HAL_RCC_TIM2_CLK_DISABLE();										//失能TIM2时钟
		HAL_NVIC_DisableIRQ(TIM2_IRQn);									//关闭TIM2中断
	}
}


/**********************************************************************************************************
 @Function			void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
 @Description			RTC底层驱动, 时钟配置
					此函数会被HAL_RTC_Init()函数调用
 @Input				hrtc : RTC句柄
 @Return				void
**********************************************************************************************************/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
#if 0
	if (hrtc->Instance == RTC) {
		RCC_OscInitTypeDef RCC_OscInitStruct;
		RCC_PeriphCLKInitTypeDef PeriphCLKInitStruct;
		
		__HAL_RCC_PWR_CLK_ENABLE();										//使能电源时钟PWR
		HAL_PWR_EnableBkUpAccess();										//取消备份区域写保护
		
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;				//LSE配置
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;						//DISABLE PLL
		RCC_OscInitStruct.LSEState = RCC_LSE_ON;							//RTC使用LSE
		HAL_RCC_OscConfig(&RCC_OscInitStruct);
		
		PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;			//外设为RTC
		PeriphCLKInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;			//RTC时钟源为LSE
		if(HAL_OK != HAL_RCCEx_PeriphCLKConfig(&PeriphCLKInitStruct)){
			RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;				//LSE配置
			RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;						//DISABLE PLL
			RCC_OscInitStruct.LSIState = RCC_LSI_ON;							//RTC使用LSE
			HAL_RCC_OscConfig(&RCC_OscInitStruct);
			
			PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;			//外设为RTC
			PeriphCLKInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;			//RTC时钟源为LSI
			HAL_RCCEx_PeriphCLKConfig(&PeriphCLKInitStruct);
		}
		
		__HAL_RCC_RTC_ENABLE();											//RTC时钟使能
		
		HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
	}
#endif
}

/**********************************************************************************************************
 @Function			void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
 @Description			RTC底层驱动, 时钟关闭
					此函数会被HAL_RTC_DeInit()函数调用
 @Input				hrtc : RTC句柄
 @Return				void
**********************************************************************************************************/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
#if 0
	if (hrtc->Instance == RTC) {
		__HAL_RCC_PWR_CLK_DISABLE();										//失能电源时钟PWR
		__HAL_RCC_RTC_DISABLE();											//RTC时钟失能
		HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
	}
#endif
}


/**********************************************************************************************************
 @Function			void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
 @Description			ADC底层驱动
					此函数会被HAL_ADC_Init()函数调用
 @Input				hadc : ADC句柄
 @Return				void
**********************************************************************************************************/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
}

/**********************************************************************************************************
 @Function			void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
 @Description			ADC底层驱动
					此函数会被HAL_ADC_DeInit()函数调用
 @Input				hadc : ADC句柄
 @Return				void
**********************************************************************************************************/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

}


/**********************************************************************************************************
 @Function			void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
 @Description			DAC底层驱动
					此函数会被HAL_DAC_Init()函数调用
 @Input				hdac : DAC句柄
 @Return				void
**********************************************************************************************************/
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{

}

/**********************************************************************************************************
 @Function			void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
 @Description			DAC底层驱动
					此函数会被HAL_DAC_DeInit()函数调用
 @Input				hdac : DAC句柄
 @Return				void
**********************************************************************************************************/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
}

/**
  * @brief SPI MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for SPI interrupt request enable
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitTypeDef GPIO_Initure;

  if (hspi == &SpiHandle)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    SPIx_SCK_GPIO_CLK_ENABLE();
    SPIx_MISO_GPIO_CLK_ENABLE();
    SPIx_MOSI_GPIO_CLK_ENABLE();
    /* Enable SPI clock */
    SPIx_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = SPIx_SCK_AF;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MISO GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MISO_PIN;
    GPIO_InitStruct.Alternate = SPIx_MISO_AF;
    HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPIx_MOSI_AF;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

    /*##-3- Configure the NVIC for SPI #########################################*/
    /* NVIC for SPI */
	//    HAL_NVIC_SetPriority(SPIx_IRQn, 1, 0);
	//    HAL_NVIC_EnableIRQ(SPIx_IRQn);
  }
  
  if (hspi == &GD25Q_SPIFLASH_Handler)
  {
	  GD25Q_FLASH_SPIx_NSS_GPIO_CLK_ENABLE();
	  GD25Q_FLASH_SPIx_SCK_GPIO_CLK_ENABLE();
	  GD25Q_FLASH_SPIx_MOSI_GPIO_CLK_ENABLE();
	  GD25Q_FLASH_SPIx_MISO_GPIO_CLK_ENABLE();
	  
	  GD25Q_FLASH_SPIx_RCC_CLK_ENABLE();
		
	  /* GD25Q_FLASH_NSS */
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_NSS_PIN;
	  GPIO_Initure.Mode		= GPIO_MODE_OUTPUT_PP;
	  GPIO_Initure.Speed	= GPIO_SPEED_HIGH;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_NSS_GPIO_PORT, &GPIO_Initure);

	  /* GD25Q_FLASH_SCK */
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_SCK_PIN;
	  GPIO_Initure.Mode		= GPIO_MODE_AF_PP;
	  GPIO_Initure.Pull		= GPIO_PULLUP;
	  GPIO_Initure.Alternate	= GD25Q_FLASH_SPIx_SCK_AF;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_SCK_GPIO_PORT, &GPIO_Initure);

	  /* GD25Q_FLASH_MOSI */
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_MOSI_PIN;
	  GPIO_Initure.Alternate	= GD25Q_FLASH_SPIx_MOSI_AF;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_MOSI_GPIO_PORT, &GPIO_Initure);

	  /* GD25Q_FLASH_MISO */
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_MISO_PIN;
	  GPIO_Initure.Alternate	= GD25Q_FLASH_SPIx_MISO_AF;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_MISO_GPIO_PORT, &GPIO_Initure);

	  GD25Q_FLASH_SPIx_NSS_DISABLE();
  }
}

/**
  * @brief SPI MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef GPIO_Initure;
	
  if (hspi == &SpiHandle)
  {
    /*##-1- Reset peripherals ##################################################*/
    SPIx_FORCE_RESET();
    SPIx_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Configure SPI SCK as alternate function  */
    HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    /* Configure SPI MISO as alternate function  */
    HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
    /* Configure SPI MOSI as alternate function  */
    HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);

	/*##-3- Disable the NVIC for SPI ###########################################*/
    //HAL_NVIC_DisableIRQ(SPIx_IRQn);
  }
  
  if (hspi == &GD25Q_SPIFLASH_Handler)
  {
	  GD25Q_FLASH_SPIx_FORCE_RESET();
	  GD25Q_FLASH_SPIx_RELEASE_RESET();
		
	  HAL_GPIO_DeInit(GD25Q_FLASH_SPIx_SCK_GPIO_PORT, GD25Q_FLASH_SPIx_SCK_PIN);
	  HAL_GPIO_DeInit(GD25Q_FLASH_SPIx_MOSI_GPIO_PORT, GD25Q_FLASH_SPIx_MOSI_PIN);
	  HAL_GPIO_DeInit(GD25Q_FLASH_SPIx_MISO_GPIO_PORT, GD25Q_FLASH_SPIx_MISO_PIN);
		
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_SCK_PIN;
	  GPIO_Initure.Mode		= GPIO_MODE_INPUT;
	  GPIO_Initure.Pull		= GPIO_PULLDOWN;
	  GPIO_Initure.Speed	= GPIO_SPEED_HIGH;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_SCK_GPIO_PORT, &GPIO_Initure);
		
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_MOSI_PIN;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_MOSI_GPIO_PORT, &GPIO_Initure);
		
	  GPIO_Initure.Pin		= GD25Q_FLASH_SPIx_MISO_PIN;
	  GPIO_Initure.Pull		= GPIO_NOPULL;
	  HAL_GPIO_Init(GD25Q_FLASH_SPIx_MISO_GPIO_PORT, &GPIO_Initure);
  }
}



/********************************************** END OF FLEE **********************************************/
