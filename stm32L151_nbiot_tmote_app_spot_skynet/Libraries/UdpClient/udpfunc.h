#ifndef __UDP_FUNC_H
#define   __UDP_FUNC_H

#include "sys.h"
#include "udpconfig.h"
#include "udpprotocol.h"

#define	UDP_MSGID_STATUS_DISABLE			0
#define	UDP_MSGID_STATUS_ENABLE			1
#define	UDP_MSGID_STATUS_TYPE			UDP_MSGID_STATUS_ENABLE

unsigned int UDP_AUTOControl_GetNextStatusNumber(UDP_ClientsTypeDef* pClient);
unsigned int UDP_AUTOControl_GetNowsStatusNumber(UDP_ClientsTypeDef* pClient);

/* Application Programming Interface */
UDP_StatusTypeDef UDP_AUTOControl_Connect(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Connect_option* options);

UDP_StatusTypeDef UDP_AUTOControl_Status(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Status_option* options);

UDP_StatusTypeDef UDP_AUTOControl_Heart(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Heart_option* options);

#endif /* __UDP_FUNC_H */
