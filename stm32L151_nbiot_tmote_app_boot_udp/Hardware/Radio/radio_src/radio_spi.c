
//#include "bsp.h"
#include "compiler_defs.h"
#include "si446x_defs.h"
#include "compiler_defs.h"

#include "hal_rf.h"



uint8_t bSpi_ReadWriteSpi1(uint8_t biDataIn)
{
	uint8_t bValue = 0;
	uint8_t rc;

	rc = HAL_SPI_TransmitReceive(&SpiHandle, &biDataIn, &bValue, 1, 100);	

	return bValue;
}

/*!
 * This function is used to send data over SPI1 no response expected.
 *
 *  @param[in] biDataInLength  The length of the data.
 *  @param[in] *pabiDataIn     Pointer to the first element of the data.
 *
 *  @return None
 */
void vSpi_WriteDataSpi1(U8 biDataInLength, U8 *pabiDataIn)
{
  while (biDataInLength--) {
    bSpi_ReadWriteSpi1(*pabiDataIn++);
  }
}

/*!
 * This function is used to read data from SPI1.
 *
 *  \param[in] biDataOutLength  The length of the data.
 *  \param[out] *paboDataOut    Pointer to the first element of the response.
 *
 *  \return None
 */
void vSpi_ReadDataSpi1(U8 biDataOutLength, U8 *paboDataOut)
{
  // send command and get response from the radio IC
  while (biDataOutLength--) {
    *paboDataOut++ = bSpi_ReadWriteSpi1(0xFF);
  }
}



