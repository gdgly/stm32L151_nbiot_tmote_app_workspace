
#include "radio_spi.h"

/*!
 * File:
 *  radio_hal.c
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */
#include "radio_spi.h"
#include "compiler_defs.h"
#include "radio_hal.h"
#include "hal_rf.h"


                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */
//这几个引脚需要分配MCU的引脚，为了解决编译报错，这里用变量来变通处理
//请务必分配MCU的引脚 RF_PWRDN, RF_NSEL, RF_NIRQ

// SDN = 1;

void radio_hal_AssertShutdown(void)
{
	HAL_GPIO_WritePin(RF_SDN_GPIO_PORT, RF_SDN_PIN, GPIO_PIN_SET);
}

void radio_hal_DeassertShutdown(void)
{
	HAL_GPIO_WritePin(RF_SDN_GPIO_PORT, RF_SDN_PIN, GPIO_PIN_RESET);

}

void radio_hal_ClearNsel(void)
{
	HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_RESET);

}

void radio_hal_SetNsel(void)
{
	HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_SET);

}

uint8_t radio_hal_NirqLevel(void)
{
	return HAL_GPIO_ReadPin(RF_nIRQ_GPIO_PORT, RF_nIRQ_PIN);

}

void radio_hal_SpiWriteByte(uint8_t byteToWrite)
{
	bSpi_ReadWriteSpi1(byteToWrite);

}

uint8_t radio_hal_SpiReadByte(void)
{
	return bSpi_ReadWriteSpi1(0xFF);
}

void radio_hal_SpiWriteData(uint8_t biDataInLength, uint8_t *pabiDataIn)
{
	while (biDataInLength--)
	{
		bSpi_ReadWriteSpi1(*pabiDataIn++);
	}
}

void radio_hal_SpiReadData(uint8_t biDataOutLength, uint8_t *paboDataOut)
{
	// send command and get response from the radio IC
	while (biDataOutLength--)
	{
		*paboDataOut++ = bSpi_ReadWriteSpi1(0xFF);
	}
}

