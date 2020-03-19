#ifndef __RADIO_HAL_WRAP_H
#define   __RADIO_HAL_WRAP_H

#include "sys.h"
#include "gpio.h"
#include "radio_hal_spi.h"

#define RADIO_CMD_DUMMY_BYTE		0xFF														//Radio Dymmy Byte

#define RADIO_HAL_NSS_ENABLE()	{Radio_Hal_Wrapper_nSELDeassert(); RADIO_SPIx_NSS_ENABLE();}
#define RADIO_HAL_NSS_DISABLE()	{RADIO_SPIx_NSS_DISABLE(); Radio_Hal_Wrapper_nSELAssert();}

void Radio_Hal_Wrapper_ShutdownAssert(void);													//Radio Hal Wrapper Shutdown(SDN) Assert

void Radio_Hal_Wrapper_ShutdownDeassert(void);												//Radio Hal Wrapper Shutdown(SDN) Deassert

void Radio_Hal_Wrapper_nSELAssert(void);													//Radio Hal Wrapper nSEL(NSS) Assert

void Radio_Hal_Wrapper_nSELDeassert(void);													//Radio Hal Wrapper nSEL(NSS) Deassert

u8   Radio_Hal_Wrapper_nIRQLevel(void);														//Radio Hal Wrapper nIRQ(IRQ) Read

void Radio_Hal_Wrapper_Init(void);															//Radio Hal Wrapper初始化

u8   Radio_Hal_Wrapper_SendByte(u8 byte);													//Radio Hal Wrapper发送1字节数据

u8   Radio_Hal_Wrapper_ReadByte(u8 byte);													//Radio Hal Wrapper读取1字节数据

void Radio_Hal_Wrapper_SendData(u8 biDataLen, u8* pabiData);									//Radio Hal Wrapper发送数据

void Radio_Hal_Wrapper_ReadData(u8 boDataLen, u8* paboData);									//Radio Hal Wrapper读取数据

#endif /* __RADIO_HAL_WRAP_H */
