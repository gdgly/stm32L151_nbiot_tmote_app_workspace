/*! @file spi.h
 * @brief This file is the interface file for SPI0 and SPI1 routines.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef RADIO_SPI_H
#define RADIO_SPI_H
#include "compiler_defs.h"

/*------------------------------------------------------------------------*/
/*                          Global typedefs & definitions                 */
/*------------------------------------------------------------------------*/

/*! SPI device select enum */
  
typedef enum
{
  eSpi_Nsel_RF,
  eSpi_Nsel_LCD
} eSpi_Nsel;

/*------------------------------------------------------------------------*/
/*                          External variables                            */
/*------------------------------------------------------------------------*/
  U8 bSpi_ReadWriteSpi1(U8 biDataIn);
  void vSpi_WriteDataSpi1(U8 biDataInLength, U8 *pabiDataIn);
  void vSpi_ReadDataSpi1(U8 biDataOutLength, U8 *paboDataOut);

#endif //SPI_H

