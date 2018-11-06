#ifndef __UPGRADE_H
#define __UPGRADE_H
#include "sys.h"
//#include "bsp.h"
#include "radio.h"
#include "si446x_defs.h"
#include "si446x_api_lib.h"




//#define REMOTE
//#define BUTTON
//#define GAS_SENSOR
//#define SMOKE_SENSOR
//#define DOOR_SENSOR
//#define ENVIRON_SENSOR
//#define CAR_4438_SENSOR
#define CAR_1208_SENSOR

//----------variable
extern uint8_t subsn[4];
//----------end

#if defined BUTTON
  #define SI4438
  #define LED         GPIOE    
  #define LED_PIN     GPIO_Pin_6
  #define LED_MODE    GPIO_Mode_Out_PP_High_Fast  
#elif defined REMOTE
  #define SI4438
  #define LED         GPIOD    
  #define LED_PIN     GPIO_Pin_1
  #define LED_MODE    GPIO_Mode_Out_PP_Low_Fast
#elif defined (SMOKE_SENSOR) || defined (DOOR_SENSOR) || defined (ENVIRON_SENSOR) || defined (GAS_SENSOR)
  #define SX1208
  #define LED         GPIOD    
  #define LED_PIN     GPIO_Pin_3
  #define LED_MODE    GPIO_Mode_Out_PP_Low_Fast
#elif defined CAR_1208_SENSOR
  #define SX1208
  #define STM8L151C8
  //the led is NC,just for compatible
  #define LED            GPIOD
  #define LED_PIN        GPIO_Pin_0
  #define LED_MODE    GPIO_Mode_Out_PP_Low_Fast

#else
  #error :"CHOOSE ONE TYPE OF DEVICES"
#endif



#if defined (SX1208)


/**************************SPI*******************/
#if defined(STM8L151C8)	// 170302 zbd add
  #define CLK_PERIPHERAL_SPIX CLK_Peripheral_SPI1
  #define SPIX	SPI1

  #define NSS_IO		GPIOB	 //SPI NSS PIN
  #define NSS_IO_PIN		GPIO_Pin_4	  
  #define MISO_IO 	GPIOB
  #define MISO_IO_PIN 	GPIO_Pin_7
  #define MOSI_IO 	GPIOB
  #define MOSI_IO_PIN 	GPIO_Pin_6
  #define SCK_IO		GPIOB
  #define SCK_IO_PIN			GPIO_Pin_5

  #define FIFO_LEVEL_GPIO_PIN	GPIO_Pin_1
  #define RECV_CPLT_GPIO_PIN	GPIO_Pin_0
  #define RF_IRQ_GPIO	GPIOE

  #define RXTX_FLAG_IO     GPIOF	// rf power switch
  #define TX_FLAG_IO_PIN   GPIO_Pin_0
  #define RX_FLAG_IO_PIN   GPIO_Pin_1  
#else
  #define CLK_PERIPHERAL_SPIX CLK_Peripheral_SPI2
  #define SPIX        SPI2

  #define NSS_IO      GPIOG    //SPI NSS PIN
  #define NSS_IO_PIN      GPIO_Pin_4    
  #define MISO_IO     GPIOG
  #define MISO_IO_PIN     GPIO_Pin_7
  #define MOSI_IO     GPIOG
  #define MOSI_IO_PIN     GPIO_Pin_6
  #define SCK_IO      GPIOG
  #define SCK_IO_PIN      GPIO_Pin_5

  #define FIFO_LEVEL_GPIO_PIN	GPIO_Pin_1
  #define RECV_CPLT_GPIO_PIN	GPIO_Pin_0
  #define RF_IRQ_GPIO	GPIOE

  #define RXTX_FLAG_IO     GPIOF
  #define TX_FLAG_IO_PIN   GPIO_Pin_0
  #define RX_FLAG_IO_PIN   GPIO_Pin_1
#endif

#elif defined (SI4438)
/**************************SPI********************/
  #define CLK_PERIPHERAL_SPIX CLK_Peripheral_SPI1
  #define SPIX    SPI1

  #define NSS_IO      GPIOB    //SPI NSS PIN
  #define NSS_IO_PIN      GPIO_Pin_4    
  #define MISO_IO     GPIOB
  #define MISO_IO_PIN     GPIO_Pin_7
  #define MOSI_IO     GPIOB
  #define MOSI_IO_PIN     GPIO_Pin_6
  #define SCK_IO      GPIOB
  #define SCK_IO_PIN          GPIO_Pin_5
#endif



#if defined (STM8L15X_HD)
  #define SUBSN_ADDR		  0x17ff0
  #define PHY_ADDR_IN_FLASH 0x17ff4
  //#define UPGRADE_TYPE_ADDR 0x17ffe
  //#define JUMP_TO_APP_ADDR  0x17fff
  #define UP_COUNT_ADDR	  0x17ffd

  #define APP_ADDR	 0x9400



#elif defined (STM8L15X_MD)

  #define SUBSN_ADDR 0xfff0
  #define PHY_ADDR_IN_FLASH 0xfff4
 //#define UPGRADE_TYPE_ADDR 0xfffe
 //#define JUMP_TO_APP_ADDR  0xffff
  #define APP_ADDR	 0x9400

#endif

/***show led flash or not?****/
#define SHOW_LED





#define SET_LED_ON      GPIO_ResetBits(LED, LED_PIN);
#define SET_LED_OFF     GPIO_SetBits(LED, LED_PIN);

#define	    TRF_PAGESIZE 			    1024
#define     IAP_START_ADDRESS      0x08007000
#define SOH 0x01
#define EOT 0x04

#define UNCOMPLETE 0x00
#define COMPLETE 0x02
#define TRANSERROR 0x01
#define PASS				0x03


#define NO_APPDOWNLOAD 0x01
#define DOWNLOADING	0x02
#define READY_TO_JUMP 0x00
#define TIME_OUT        0x03
#define DOWNLOAD_ERROR 0x04

#define PASS				0x03

#define JOIN_COMPELET 0x00
#define JOINING 0X01

#if defined (SI4438) && defined (SX1208)
 #error "only one type of radio is enable in stm8l15x.h!"   
#endif
    #if !defined (SX1208) && !defined (SI4438)
 #error "Please select  one type of mcu in stm8l15x.h!"   
#endif


 #define FAR  __far
 #define NEAR __near
 #define TINY __tiny
 //#define __CONST  const



#define  FLASH_START          0x008000ul
#define  TRF_FLASH_END            0x00FFFFul
#define  FLASH_BLOCKS_NUMBER  0x100 /*((FLASH_END  - FLASH_START  + 1)/BLOCK_SIZE)*/
#define  SECTORS_IN_FLASH     0x20 /*((FLASH_END  - FLASH_START  + 1)/BLOCK_SIZE/BLOCK_PER_SECTOR)*/ 
#define  FLASH_CLEAR_BYTE     0x00
#define  BLOCK_SIZE           0x80



#define  BLOCK_BYTES		  128
#define  ADDRESS_BLOCK_MASK   127
#define MAIN_USER_RESET_ADDR 0xA000ul




#define	UPGRADE_FIRMWARE	0x00
#define	LOAD_APPLICATION	0xFF


enum
{
	UPGRADE_REQUEST = 0,
	UPGRADE_VALIDDATA,	// SOH
	UPGRADE_REQUEST_RSP,
	UPGRADE_VALIDDATA_RSP,
	UPGRADE_END	// EOT
};
/*
enum
{
	OPTIONAL_PRT,
	XIMPLICITI_PRT,
	XMESH_PRT,
	XMESHILITE_PRT,
	UPGRADE_PRT
};
*/
#define UPGRADEVERSION	0
#define UPGRADE_TYPE_SIZE 1
#define ALLOW_SIZE	1


/****offset & bits of the xmeshlite protocol*/

#define UPGD_LEN_OS								0
#define UPGD_LEN_OS_MSK						0xff
#define UPGD_LEN_OS_SFT						0

#define UPGD_PRE_TYPE_OS          0//offset:first Byte of preoperate offset
#define UPGD_PRE_TYPE_OS_MSK      0x07//0-2bit
#define UPGD_PRE_TYPE_OS_SFT      0

#define UPGD_PRE_VS_OS            0//version
#define UPGD_PRE_VS_OS_MSK        0xe0//
#define UPGD_PRE_VS_OS_SFT 				5

#define UPGD_HEAD_TYPE_OS					0
#define UPGD_HEAD_TYPE_OS_MSK			0xf0
#define UPGD_HEAD_TYPE_OS_SFT			4

#define UPGD_PKTNUM_OS            1	//sequence num
#define UPGD_PKTNUM_OS_MSK            0xff//
#define UPGD_PKTNUM_OS_SFT        0//



#define UPGD_FRAME_CRC_SIZE	2

#define UPGD_FRAME_LEN_SIZE	1
#define UPGD_FRAME_PRE_SIZE	1
#define UPGD_FRAME_HEAD_SIZE	2

#define UPGD_FRAME_SN_SIZE	4

#define UPGD_FRAME_LEN_OFS			0
#define UPGD_FRAME_PRE_OFS			UPGD_FRAME_LEN_OFS+UPGD_FRAME_LEN_SIZE	//0+1
#define UPGD_FRAME_HEAD_OFS			UPGD_FRAME_PRE_OFS+UPGD_FRAME_PRE_SIZE		//1+1
#define UPGD_FRAME_SN_OFS				UPGD_FRAME_HEAD_OFS+UPGD_FRAME_HEAD_SIZE//1+1+2
#define UPGD_FRAME_PAYLOAD_OFS	UPGD_FRAME_SN_OFS+UPGD_FRAME_SN_SIZE	//1+1+2+4


/***address of the first byte in each filed*/
#define UPGD_P_FRAME_LEN(P)     (&((P)[UPGD_FRAME_LEN_OFS]))   

#define UPGD_P_FRAME_PRE(P)     (&((P)[UPGD_FRAME_PRE_OFS]))

#define UPGD_P_FRAME_HEAD(P)    (&((P)[UPGD_FRAME_HEAD_OFS]))


#define UPGD_P_FRAME_SN(P)    (&((P)[UPGD_FRAME_SN_OFS]))

#define UPGD_P_FRAME_PAYLOAD(P)    (&((P)[UPGD_FRAME_PAYLOAD_OFS]))







#define UPGD_GET_PAYLOAD_LEN(P)  (((P)[UPGD_FRAME_LEN_OFS]) - (UPGD_FRAME_PAYLOAD_OFS))



#define UPGD_GET_FROM_FRAME(b,f)  ((b)[f] & (f##_MSK))>>(f##_SFT)



#define UPGD_PUT_INTO_FRAME(b,f,v)  do {(b)[f] = ((b)[f] & ~(f##_MSK)) | ((v)<<(f##_SFT)); } while(0)





//#define SEQUNCE 1;

uint8_t programUpdate(uint8_t *recv_data,uint8_t *sn);
//uint8_t xm_iap_program(uint32_t addr, uint8_t len, uint8_t* buff);
extern uint8_t JumpToApplication(uint32_t Addr);
void xm_join(void);
uint8_t WriteBuffer(uint32_t DataAddress, uint8_t DataCount) ;
//uint8_t WriteBufferFlash(uint32_t DataAddress, uint8_t DataCount, FLASH_MemType_TypeDef MemType);
void unlock_PROG(void);
void unlock_DATA(void);
void Mem_ProgramBlock(uint16_t BlockNum,uint8_t *Buffer);
void xm_Upgd_buildframe(uint8_t *msg,uint8_t type,uint8_t pktnum,uint8_t *sn,uint8_t *send,uint8_t len);
uint8_t CheckSum(uint8_t *recv_data);
void Get_sn(void);
void Get_addr(void);

#endif
