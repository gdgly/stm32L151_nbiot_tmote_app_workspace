#ifndef __UDP_FUNC_H
#define   __UDP_FUNC_H

#include "sys.h"
#include "udpconfig.h"
#include "udpprotocol.h"

/* Application Programming Interface */
UDP_StatusTypeDef UDP_AUTOControl_Connect(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Connect_option* options);

UDP_StatusTypeDef UDP_AUTOControl_Status(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Status_option* options);

UDP_StatusTypeDef UDP_AUTOControl_Heart(UDP_ClientsTypeDef* pClient, UDP_AUTOCTRL_message_Heart_option* options);

#endif /* __UDP_FUNC_H */
