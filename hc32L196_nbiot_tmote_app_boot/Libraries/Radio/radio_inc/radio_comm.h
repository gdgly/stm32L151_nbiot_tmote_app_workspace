#ifndef __RADIO_COMM_H
#define   __RADIO_COMM_H

#include "sys.h"

void radio_comm_ClearCTS(void);

u8   radio_comm_PollCTS(void);

u8   radio_comm_GetResp(u8 byteCount, u8* pData);

void radio_comm_SendCmd(u8 byteCount, u8* pData);

void radio_comm_ReadData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData);

void radio_comm_WriteData(u8 cmd, u8 pollCts, u8 byteCount, u8* pData);

u8   radio_comm_SendCmdGetResp(u8 cmdByteCount, u8* pCmdData, u8 respByteCount, u8* pRespData);

#endif /* __RADIO_COMM_H */
