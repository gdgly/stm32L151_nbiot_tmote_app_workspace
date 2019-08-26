#ifndef __HAL_OOK_H
#define   __HAL_OOK_H

#include "sys.h"

#define OOK_DATA_RX_PORT           (GPIOC)
#define OOK_DATA_RX_PINS           (GPIO_Pin_1)

#define OOK_DATA_TX_PORT           (GPIOA)
#define OOK_DATA_TX_PINS           (GPIO_Pin_2)

#define OOK_DATA_RX_SET(n)         (n ? GPIO_SetBits(OOK_DATA_RX_PORT, OOK_DATA_RX_PINS) : GPIO_ResetBits(OOK_DATA_RX_PORT, OOK_DATA_RX_PINS))
#define OOK_DATA_TX_SET(n)         (n ? GPIO_SetBits(OOK_DATA_TX_PORT, OOK_DATA_TX_PINS) : GPIO_ResetBits(OOK_DATA_TX_PORT, OOK_DATA_TX_PINS))

#define OOK_DATA_RX_TOGGLE()       (GPIO_ToggleBits(OOK_DATA_RX_PORT, OOK_DATA_RX_PINS))
#define OOK_DATA_TX_TOGGLE()       (GPIO_ToggleBits(OOK_DATA_TX_PORT, OOK_DATA_TX_PINS))

#define OOK_DATA_RX_READ()         (GPIO_ReadInputDataBit(OOK_DATA_RX_PORT, OOK_DATA_RX_PINS))
#define OOK_DATA_TX_READ()         (GPIO_ReadInputDataBit(OOK_DATA_TX_PORT, OOK_DATA_TX_PINS))

void Stm8_OOK_Init(void);












#endif /* __HAL_OOK_H */
