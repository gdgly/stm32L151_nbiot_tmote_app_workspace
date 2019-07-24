#ifndef __HAL_RF_H
#define __HAL_RF_H
#include "sys.h"
#include "stm32l1xx_hal_spi.h"
extern SPI_HandleTypeDef SpiHandle;


/* Definition for SPIx clock resources */
#define SPIx                             SPI1
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_5
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_AF                      GPIO_AF5_SPI1
#define SPIx_MISO_PIN                    GPIO_PIN_6
#define SPIx_MISO_GPIO_PORT              GPIOA
#define SPIx_MISO_AF                     GPIO_AF5_SPI1
#define SPIx_MOSI_PIN                    GPIO_PIN_7
#define SPIx_MOSI_GPIO_PORT              GPIOA
#define SPIx_MOSI_AF                     GPIO_AF5_SPI1

// PB4  :SDN	,used to reset the mcu
// PB10:nIRQ
// PA15:SPI1_NSS
// PA5  :SPI1_SCK
// PA7  :SPI1_MOSI
// PA6  :SPI1_MISO

#define SPIx_NSS_PIN                   GPIO_PIN_15
#define SPIx_NSS_GPIO_PORT             GPIOA

#define RF_SDN_PIN                     GPIO_PIN_4
#define RF_SDN_GPIO_PORT               GPIOB

#define RF_nIRQ_PIN                    GPIO_PIN_10
#define RF_nIRQ_GPIO_PORT              GPIOB

#define RF_SDN_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOB_CLK_ENABLE()
#define RF_nIRQ_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOB_CLK_ENABLE()
#define RF_NSS_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOA_CLK_ENABLE()



/* Definition for SPIx's NVIC */
#define RF_IRQn                        EXTI15_10_IRQn
//#define SPIx_IRQHandler                  SPI2_IRQHandler

enum TRF_ERRCODE
{
	TRF_OK = 0,
	TRF_ERROR,
};


/* ------------------------------------------------------------------------------------------------
 *                                          Typdefs
 * ------------------------------------------------------------------------------------------------
 */
/*****PROTOCOL TYPE****/
enum Protocol_type
{
	OPTIONAL_PRT,		//000
	SIMPLICITI_PRT, 	//001
	XMESH_PRT,			//010
	XMESHLITE_PRT,		//011
	UPGRADE_PRT,		//100
	XMESHCFG_PRT,		//101		//terry add for config gate 	with protobuf
	RSVED6, 			//110		//
	RSVED7				//111		//
};

typedef enum{
	CHECK_FAIL,
	CHECK_SUCESS
}check_t;  
/*typedef struct
{
  uint8_t frame[MRFI_MAX_FRAME_SIZE];//242+3+1+2*4
  uint8_t rxMetrics[MRFI_RX_METRICS_SIZE];
} mrfiPacket_t;
*/
#define MMESH_CHECKSUM_SIZE	2

char tmesh_rf_init(void);
void tmesh_rf_PrepareToTx(uint8_t * pPacket, uint8_t len);
void tmesh_rf_ISR(void);
char tmesh_rf_get_status(void);
void tmesh_rf_interface_init(void);
#endif
