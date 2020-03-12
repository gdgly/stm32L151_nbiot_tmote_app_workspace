/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */
  // 2017-12-13 : zbd 在升级是也会发送心跳,而且升级时或者等待升级时超时了都会重启.
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hal_rtc.h"
#include "hal_iwdg.h"
#include "hal_eeprom.h"
#include "stm32l1xx_config.h"
#include "string.h"
#include "tmesh_net_utility.h"
#include "tmesh_misc.h"
#include "hal_rf.h"
#include "tmesh_rf_app.h"
#include "boot.h"
#include "iap.h"
#include "ugrade.h"
#include "tmesh_cfg.h"
#include "tmesh_rf_app.h"
#include "hal_eeprom.h"
#include "hal_spiflash.h"

#define	SOFTIWDGENABLE		

#define IIC_SCL_GPIOx				GPIOB
#define IIC_SDA_GPIOx				GPIOB
#define IIC_SCL_PIN					GPIO_PIN_6
#define IIC_SDA_PIN					GPIO_PIN_7
#define IIC_SCL_RCC_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define IIC_SCL_RCC_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()
#define IIC_SDA_RCC_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define IIC_SDA_RCC_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()

#if 0
#define BEEPPOWER(n)			(n?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET))
#endif
#define BEEPPOWER(n)			(n?HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET))

#define SN_WRITE	0
#if SN_WRITE
u32 snbuf = 0x7b010014;//0x81020003;
u8 snbuf1[4];
#endif

/**********************************************************************************************************
 @Function			void QMC5883L_Discharge(void)
 @Description			IIC引脚输出低,以充分放电
 @Input				void
 @Return				void
**********************************************************************************************************/
void QMC5883L_Discharge(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIO_PIN_8;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;							//推挽输出
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;								//高速
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);								//初始化GPIO
	
	MODELPOWER(OFF);													//关闭模块总电源		
	
	IIC_SCL_RCC_GPIO_CLK_ENABLE();										//使能GPIOB时钟
	IIC_SDA_RCC_GPIO_CLK_ENABLE();
	
	/* PB6,7初始化设置 */
	GPIO_Initure.Pin = IIC_SCL_PIN;										//PB6
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;//GPIO_MODE_OUTPUT_PP;								//推挽输出
	HAL_GPIO_Init(IIC_SCL_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin = IIC_SDA_PIN;										//PB7
	HAL_GPIO_Init(IIC_SDA_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(IIC_SCL_GPIOx, IIC_SCL_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IIC_SDA_GPIOx, IIC_SDA_PIN, GPIO_PIN_RESET);
	Delay_MS(3000);
	MODELPOWER(ON);													//开启模块总电源	
	HAL_GPIO_WritePin(IIC_SCL_GPIOx, IIC_SCL_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(IIC_SDA_GPIOx, IIC_SDA_PIN, GPIO_PIN_SET);
}
//extern uint32_t STMFLASH_ReadfWord(uint32_t faddr);
uint32_t app_real_address;
uint32_t app_jump_address;
void x_jump_to_application(unsigned int app_addr)
{
#if 1
	
	app_real_address = *(__IO uint32_t *)(APP_LOWEST_ADDRESS-256);
	//app_real_address = 0x08003000;
	__NOP();
	//HAL_FLASH_Unlock();
	//__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR);
	//app_real_address = STMFLASH_ReadfWord(APP_LOWEST_ADDRESS-256);
	if((app_real_address>=app_addr)&&(app_real_address<0x08020000)){
		app_jump_address = app_real_address;
	}else{
		app_jump_address = app_addr;
	}
	SCB->VTOR = app_jump_address; /* Vector Table Relocation in Internal FLASH. */
	__enable_irq();
	boot_from_flash(app_jump_address); // boot the backup app
#endif
}

/**********************************************************************************************************
 @Function			Radar_OFF
 @Description			make the beep work
 @Input				times  how many times to beep
 @Return				void
**********************************************************************************************************/
void Radar_OFF(void)	//
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIO_PIN_3;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;							//推挽输出
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;								//高速
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);								//初始化GPIO
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}
/**********************************************************************************************************
 @Function			beep_on
 @Description			make the beep work
 @Input				xms  how many ms to beep
 @Return				void
**********************************************************************************************************/
void beep_on(uint16_t xms)
{
#if 0
	while(xms--){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		Delay_US(230);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		Delay_US(230);
	}
#endif
	
	while(xms--){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		Delay_US(230);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		Delay_US(230);
	}
}
/**********************************************************************************************************
 @Function			Beep_OUT
 @Description			make the beep work
 @Input				times  how many times to beep
 @Return				void
**********************************************************************************************************/
void Beep_OUT(uint8_t times,uint8_t length)	//
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();											//PC13 lockctrl
	
	if(length>= 100)
		length = 99;
	
#if 0
	GPIO_InitStructure.Pin = GPIO_PIN_8;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;							//推挽输出
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;								//高速
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);								//初始化GPIO
#endif
	
	GPIO_InitStructure.Pin = GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;							//推挽输出
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;								//高速
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);								//初始化GPIO
	
	while(times--){
//		BEEPPOWER(ON);
//		Delay_MS(length); //wait for response
		beep_on(length*5);
		BEEPPOWER(OFF);
		Delay_MS(100-length); //wait for response		
	}
	
#if 0
	GPIO_InitStructure.Pin = GPIO_PIN_8;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);								//初始化GPIO
#endif
	
	GPIO_InitStructure.Pin = GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);								//初始化GPIO
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

/********************************************************************************************************/
struct UpdateFIFO
{
	unsigned char *buf;
	int putP, getP, size, free, flags;
};

void Fifo_init(struct UpdateFIFO *fifo, int size, unsigned char *buf)
{
	fifo->buf = buf;
	fifo->flags = 0;
	fifo->free = size;
	fifo->size = size;
	fifo->putP = 0;
	fifo->getP = 0;
	
	return;
}

int Fifo_putPut(struct UpdateFIFO *fifo, unsigned char data)
{
	if (fifo->free == 0) {
		fifo->flags |= 0x0001;
		return -1;
	}
	
	fifo->buf[fifo->putP] = data;
	fifo->putP++;
	if (fifo->putP == fifo->size) {
		fifo->putP = 0;
	}
	fifo->free--;
	
	return 0;
}

int Fifo_get(struct UpdateFIFO *fifo)
{
	unsigned char data;
	
	if (fifo->free == fifo->size) {
		return -1;
	}
	
	data = fifo->buf[fifo->getP];
	fifo->getP++;
	if (fifo->getP == fifo->size) {
		fifo->getP = 0;
	}
	fifo->free++;
	
	return data;
}

void Fifo_WriteBuffer(struct UpdateFIFO *fifo, unsigned char* buf, unsigned int len)
{
	while (len--) {
		Fifo_putPut(fifo, *buf++);
	}
}

void Fifo_ReadBuffer(struct UpdateFIFO *fifo, unsigned char* buf, unsigned int len)
{
	while (len--) {
		*buf++ = Fifo_get(fifo);
	}
}

int Fifo_status(struct UpdateFIFO *fifo)
{
	return fifo->size-fifo->free;
}

int Fifo_free(struct UpdateFIFO *fifo)
{
	return fifo->free;
}

#define SPIFLASH_ONCE_READLEN				512
#define SPIFLASH_ONEC_READLEN_EFFECTIVE		500
#define SPIFLASH_BLOCK_NUM				150
#define STMFLASH_ONCE_WRITELEN			128

#define UPDATE_BUFFER_LEN				2048
#define UPDATE_STACK_BUFFER_LEN			1024

struct UpdateFIFO	UpdateFifoStruct;
__IO unsigned char UpdateFifoBuffer[UPDATE_BUFFER_LEN];
__IO unsigned char UpdateSPIFlashRead[UPDATE_STACK_BUFFER_LEN];
__IO unsigned char UpdateSTMFlashWrite[UPDATE_STACK_BUFFER_LEN];

__IO u32 SpiFlashblockIndex = 0;
__IO u32 StmFlashblockIndex = 0;
__IO u32 SpiFlashBlockAll = 0;
__IO u32 FifoRemainderLen = 0;

__IO uint32_t UpgradeSpiFlashBaseAddr = GD25Q80_BASE_ADDR;
__IO uint16_t UpgradeBlockNum = SPIFLASH_BLOCK_NUM;
__IO uint16_t UpgradeBlockLen = SPIFLASH_ONCE_READLEN;
__IO uint16_t UpgradeDataLen = SPIFLASH_ONEC_READLEN_EFFECTIVE;

unsigned char SpiFlashUpgradeString[25] = "SPI FLASH Upgrade : ---%";

void programUpdateSpiFlashPrint(void)
{
#if 1
	SpiFlashUpgradeString[20] = 0x30 + (StmFlashblockIndex*STMFLASH_ONCE_WRITELEN*100)/(SpiFlashBlockAll*UpgradeDataLen)/100;
	SpiFlashUpgradeString[21] = 0x30 + (StmFlashblockIndex*STMFLASH_ONCE_WRITELEN*100)/(SpiFlashBlockAll*UpgradeDataLen)/10%10;
	SpiFlashUpgradeString[22] = 0x30 + (StmFlashblockIndex*STMFLASH_ONCE_WRITELEN*100)/(SpiFlashBlockAll*UpgradeDataLen)%10;
	trf_do_rfpintf((char*)SpiFlashUpgradeString);
#endif
}

void programUpdateSpiFlash(u32 SpiReadAddr, u32 StmWriteAddr, u32 SpiFlashBlock)
{
	SpiFlashblockIndex = 0;
	StmFlashblockIndex = 0;
	SpiFlashBlockAll = SpiFlashBlock;
	FifoRemainderLen = 0;
	
	Fifo_init(&UpdateFifoStruct, sizeof(UpdateFifoBuffer), (u8*)UpdateFifoBuffer);
	
	while ((SpiFlashBlock != 0) || (Fifo_status(&UpdateFifoStruct) >= STMFLASH_ONCE_WRITELEN)) {
		
		if ((SpiFlashBlock != 0) && (Fifo_free(&UpdateFifoStruct) >= UpgradeDataLen)) {
			GD25Q_SPIFLASH_Init();
			GD25Q_SPIFLASH_ReadBuffer((u8*)UpdateSPIFlashRead, SpiReadAddr + (SpiFlashblockIndex * UpgradeBlockLen), UpgradeDataLen);
			SpiFlashblockIndex++;
			SpiFlashBlock--;
			Fifo_WriteBuffer(&UpdateFifoStruct, (u8*)UpdateSPIFlashRead, UpgradeDataLen);
		}
		
		if (Fifo_status(&UpdateFifoStruct) >= STMFLASH_ONCE_WRITELEN) {
			Fifo_ReadBuffer(&UpdateFifoStruct, (u8*)UpdateSTMFlashWrite, STMFLASH_ONCE_WRITELEN);
			xm_iap_program(APP_LOWEST_ADDRESS, StmFlashblockIndex * STMFLASH_ONCE_WRITELEN, STMFLASH_ONCE_WRITELEN, (u8*)UpdateSTMFlashWrite);
			StmFlashblockIndex++;
			
			programUpdateSpiFlashPrint();
		}
		
		IWDG_Feed();
	}
	
	FifoRemainderLen = Fifo_status(&UpdateFifoStruct);
	if (Fifo_status(&UpdateFifoStruct) > 0) {
		Fifo_ReadBuffer(&UpdateFifoStruct, (u8*)UpdateSTMFlashWrite, FifoRemainderLen);
		for (int i = FifoRemainderLen; i < STMFLASH_ONCE_WRITELEN; i++) {
			UpdateSTMFlashWrite[i] = 0xFF;
		}
		
		xm_iap_program(APP_LOWEST_ADDRESS, StmFlashblockIndex * STMFLASH_ONCE_WRITELEN, STMFLASH_ONCE_WRITELEN, (u8*)UpdateSTMFlashWrite);
		StmFlashblockIndex++;
		
		programUpdateSpiFlashPrint();
	}
}
/********************************************************************************************************/
/**********************************************************************************************************
 @Function			int main(void)
 @Description			Main
 @Input				void
 @Return				int
**********************************************************************************************************/
unsigned int app_offset;
extern uint8_t upgrad_state;
extern char g_bootmode;
extern uint8_t subsn[4];
extern uint8_t Join_state;
#define	OVERTIME	900
int main(void)
{
	int i,j;
	char printfbuf[30]="Boot----mode---count----nor---";
	HAL_Init();														//初始化HAL库
	Stm32_Clock_Init(RCC_PLLMUL_6, RCC_PLLDIV_3);							//设置时钟32Mhz

#ifdef SOFTIWDGENABLE
	IWDG_Init(IWDG_PRESCALER_256, 4000);									//看门狗初始化,分频数为256,重载值为4000,溢出时间为28s
	IWDG_Feed();														//喂狗
#endif
	Radar_OFF();
	Delay_Init(32);													//初始化延时
	QMC5883L_Discharge();
//	RTC_Init();														//RTC初始化
	
	GD25Q_SPIFLASH_Init();
	GD25Q_SPIFLASH_PowerDown();
	
	tmesh_rf_init();	// 根据mac地址最后一位确定工作信道,错开信道,可以两个设备同时升级.
	app_offset = APP_LOWEST_ADDRESS;										//0x08005000;  省去6KB flash
	
#if SN_WRITE
	snbuf1[0] = snbuf >> 3*8;
	snbuf1[1] = (snbuf & 0x00FF0000) >> 2*8;
	snbuf1[2] = (snbuf & 0x0000FF00) >> 1*8;
	snbuf1[3] = (snbuf & 0x000000FF) >> 0*8;
	EEPROM_WriteBytes(EEPROM_ADDR_BASE_MACSN, snbuf1, EEPROM_ADDR_SIZE_MACSN);
	EEPROM_WriteBytes(EEPROM_ADDR_BASE_VENDER, (u8 *)"mvb", EEPROM_ADDR_SIZE_VENDER);
#endif

	tcfg_setMagFreq(BOOT_VERSION);
	i = tcfg_GetBootMode();
	if(i == TCFG_ENV_BOOTMODE_TOUPDATE)
		g_bootmode = TCFG_ENV_BOOTMODE_TOUPDATE;
	else if(i == TCFG_ENV_BOOTMODE_UPDATING)
		g_bootmode = TCFG_ENV_BOOTMODE_UPDATING;
	else if (i == TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE)
		g_bootmode = TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE;
	else
		g_bootmode = TCFG_ENV_BOOTMODE_NORMAL;
	i = tcfg_GetBootCount();
	Beep_OUT(1,40);
	Delay_MS(100);
	Beep_OUT(2,20);
	Delay_MS(100);
	Beep_OUT(1,40);
	Delay_MS(100);
	Beep_OUT(2,20);
	Delay_MS(100);										//di~didi~di~didi
//	sprintf(printfbuf,"bootmode=%d,bootcnt=%d",g_bootmode,i);
	printfbuf[13]=0x30+g_bootmode;
	printfbuf[21]=0x30+i/10;
	printfbuf[22]=0x30+i%10;
	printfbuf[5] =0x30+((BOOT_VERSION/10));
	printfbuf[6] =0x30+(BOOT_VERSION%10);
	printfbuf[28] = 0x30+(GD25Q_SPIFLASH_Get_Status()?0:1);
	trf_do_rfpintf(printfbuf);
	__NOP();
	
	if(i > 29) // fail to boot app several times
	{
		if(i%2 == 0)
			g_bootmode = TCFG_ENV_BOOTMODE_UPDATING;
		else
			g_bootmode = TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE;
		if(i>100)
			i = 29;
	}
	tcfg_SetBootCount(i+1);
	IWDG_Feed();														//喂狗
	
//	g_bootmode = TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE;
	
	if(g_bootmode == TCFG_ENV_BOOTMODE_NORMAL)
		goto start;
	
	if (g_bootmode == TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE)
		goto start;
	
	if(TRF_OK != tmesh_rf_get_status()){
		g_bootmode = TCFG_ENV_BOOTMODE_NORMAL;
		goto start;
	}
	
	IWDG_Feed();														//喂狗
	tmesh_rf_init();
	upgrad_state = NO_APPDOWNLOAD;
	*(int32_t*)subsn = tnet_utility_get_mac_sn();

	while(Join_state != JOIN_COMPELET)
	{
		for(j = 200; j != 0; j--)
		{
			for(i = 1000; i != 0; i--);
		}
#ifdef SOFTIWDGENABLE
		IWDG_Feed();														//喂狗
#endif	
		
		trf_xmit_heartbeat();
		Delay_MS(100*(HAL_GetTick()%3));
		xm_join();
		while(i < 900)	// 这是一直在接收数据?
		{
			Delay_MS(1);
			trf_receive_task();
			i++;
		}
		if(Sys_GetSecond() >= 120)
		{	// reboot to reinit the rf model
			upgrad_state = TIME_OUT;
			HAL_FLASH_Lock();
			HAL_NVIC_SystemReset();
		}
		if(Sys_GetSecond()%10 == 0){
			Beep_OUT(1,20);
		}
	}

start:		
	while(1)
	{
		if(g_bootmode == TCFG_ENV_BOOTMODE_TOUPDATE)
		{
			while(1)
			{
				trf_receive_task();

				if(upgrad_state == READY_TO_JUMP)//升级成功
				{
					tcfg_SetBootMode(TCFG_ENV_BOOTMODE_NORMAL);
					x_jump_to_application(app_offset);
				}
				else if (upgrad_state == DOWNLOADING)
				{
					trf_receive_task();
					if(Sys_GetSecond() >= OVERTIME)
					{
						upgrad_state = TIME_OUT;
						HAL_FLASH_Lock();
						HAL_NVIC_SystemReset();
					}else if((Sys_GetSecond() > (30+trf_get_last_recvtime()))&&(trf_get_last_recvtime()>0)){
						__NOP();
						upgrad_state = TIME_OUT;
						HAL_FLASH_Lock();
						HAL_NVIC_SystemReset();
					}else if(Sys_GetSecond() > (10+trf_get_last_recvtime())){
						trf_xmit_heartbeat();
					}
				}
				else if(upgrad_state == NO_APPDOWNLOAD)//如果第一包都收不到，那么超时以后直接跳转
				{
					trf_xmit_heartbeat();
					for(i = 500; i != 0; i--)
					{
						Delay_MS(1);
						trf_receive_task();
					}
					Delay_MS(100*(HAL_GetTick()%3));
					xm_join();
					for(i = 500; i != 0; i--)
					{
						Delay_MS(1);
						trf_receive_task();
					}
					if(Sys_GetSecond() >= 120)
					{
					  	tcfg_SetBootMode(TCFG_ENV_BOOTMODE_NORMAL);
						x_jump_to_application(app_offset);
					}
				}
				else if(upgrad_state == DOWNLOAD_ERROR)//如果下载失败
				{
					__NOP();
					Delay_MS(10000);
					HAL_FLASH_Lock();
					HAL_NVIC_SystemReset();
				}
#ifdef SOFTIWDGENABLE
				IWDG_Feed();														//喂狗
#endif					
				if(Sys_GetSecond()%10 == 0){
					Beep_OUT(1,20);
				}
			}
		}
		else if(g_bootmode == TCFG_ENV_BOOTMODE_UPDATING)
		{
			while(1)
			{
				while(upgrad_state == NO_APPDOWNLOAD)//一直等，直到等到升级包数据到来
				{
					trf_xmit_heartbeat();
					for(i = 500; i != 0; i--)
					{
						Delay_MS(1);
						trf_receive_task();
					}
					Delay_MS(100*(HAL_GetTick()%3));
					xm_join();
					for(i = 500; i != 0; i--)
					{
						Delay_MS(1);
						trf_receive_task();
					}
					if(Sys_GetSecond() >= OVERTIME)
					{
						upgrad_state = TIME_OUT;
						HAL_FLASH_Lock();
						HAL_NVIC_SystemReset();
					}
#ifdef SOFTIWDGENABLE
					IWDG_Feed();	//喂狗
#endif	
					if(Sys_GetSecond()%10 == 0){
						Beep_OUT(1,20);
					}

				}
				if(upgrad_state == DOWNLOADING)//超时0x0800fc00置位，并且bootloader复位
				{
					trf_receive_task();
					if(Sys_GetSecond() >= OVERTIME)
					{
						upgrad_state = TIME_OUT;
						HAL_FLASH_Lock();
						HAL_NVIC_SystemReset();
					}else if((Sys_GetSecond() > (30+trf_get_last_recvtime()))&&(trf_get_last_recvtime()>0)){
						__NOP();
						upgrad_state = TIME_OUT;
						HAL_FLASH_Lock();
						HAL_NVIC_SystemReset();
					}else if(Sys_GetSecond() > (10+trf_get_last_recvtime())){
						trf_xmit_heartbeat();
					}
				}
				else if(upgrad_state == READY_TO_JUMP)//如果下载成功，那么清除0x800fc00位并跳转app
				{
				  	tcfg_SetBootMode(TCFG_ENV_BOOTMODE_NORMAL);
					x_jump_to_application(app_offset);
				}
				else if(upgrad_state == DOWNLOAD_ERROR)//如果下载失败
				{
					__NOP();
					Delay_MS(10000);
					HAL_FLASH_Lock();
					HAL_NVIC_SystemReset();
				}
#ifdef SOFTIWDGENABLE
				IWDG_Feed();	//喂狗
#endif	
				if(Sys_GetSecond() >= OVERTIME)
				{
					upgrad_state = TIME_OUT;
					HAL_FLASH_Lock();
					HAL_NVIC_SystemReset();
				}
				if(Sys_GetSecond()%10 == 0){
					Beep_OUT(1,20);
				}
			}
		}
		else if (g_bootmode == TCFG_ENV_BOOTMODE_SPIFLASH_UPGRADE)
		{
			if (GD25Q_SPIFLASH_Get_Status() != GD25Q80CSIG_ERROR) {
				
				HAL_NVIC_DisableIRQ(RF_IRQn);
				GD25Q_SPIFLASH_WakeUp();
				GD25Q_SPIFLASH_Init();
				
				if (GD25Q_SPIFLASH_GetByte(APP1_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					if (tcfg_GetBootCount() > 3) {
						GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 0 * GD25Q80_BLOCK_BYTE_SIZE);
						GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 1 * GD25Q80_BLOCK_BYTE_SIZE);
						GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 2 * GD25Q80_BLOCK_BYTE_SIZE);
						GD25Q_SPIFLASH_EraseBlock(APP1_BASE_ADDR + 3 * GD25Q80_BLOCK_BYTE_SIZE);
					}
				}
				
				if (GD25Q_SPIFLASH_GetByte(APP1_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					UpgradeSpiFlashBaseAddr = GD25Q_SPIFLASH_GetWord(APP1_INFO_UPGRADE_BASEADDR_OFFSET);		//SPI Flash App Base Address
					UpgradeBlockNum = GD25Q_SPIFLASH_GetHalfWord(APP1_INFO_UPGRADE_BLOCKNUM_OFFSET);		//SPI Flash App Block Num
					UpgradeBlockLen = GD25Q_SPIFLASH_GetHalfWord(APP1_INFO_UPGRADE_BLOCKLEN_OFFSET);		//SPI Flash Block Length
					UpgradeDataLen = GD25Q_SPIFLASH_GetHalfWord(APP1_INFO_UPGRADE_DATALEN_OFFSET);			//SPI Flash Block Effective Data Length
					
					programUpdateSpiFlash(UpgradeSpiFlashBaseAddr, app_offset, UpgradeBlockNum);
				}
				else if (GD25Q_SPIFLASH_GetByte(APP2_INFO_UPGRADE_STATUS_OFFSET) == 0x55) {
					UpgradeSpiFlashBaseAddr = GD25Q_SPIFLASH_GetWord(APP2_INFO_UPGRADE_BASEADDR_OFFSET);		//SPI Flash App Base Address
					UpgradeBlockNum = GD25Q_SPIFLASH_GetHalfWord(APP2_INFO_UPGRADE_BLOCKNUM_OFFSET);		//SPI Flash App Block Num
					UpgradeBlockLen = GD25Q_SPIFLASH_GetHalfWord(APP2_INFO_UPGRADE_BLOCKLEN_OFFSET);		//SPI Flash Block Length
					UpgradeDataLen = GD25Q_SPIFLASH_GetHalfWord(APP2_INFO_UPGRADE_DATALEN_OFFSET);			//SPI Flash Block Effective Data Length
					
					programUpdateSpiFlash(UpgradeSpiFlashBaseAddr, app_offset, UpgradeBlockNum);
				}
				else {
					upgrad_state = TIME_OUT;
					HAL_FLASH_Lock();
					HAL_NVIC_SystemReset();
				}
				Beep_OUT(20, 30);
			}
			else {
				upgrad_state = TIME_OUT;
				HAL_FLASH_Lock();
				HAL_NVIC_SystemReset();
			}
			
			x_jump_to_application(app_offset);
		}
		else
		{
			x_jump_to_application(app_offset);
		}
	}
}

/********************************************** END OF FLEE **********************************************/
