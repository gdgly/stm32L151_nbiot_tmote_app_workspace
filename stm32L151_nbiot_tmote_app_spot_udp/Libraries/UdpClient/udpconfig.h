#ifndef __UDP_CONFIG_H
#define   __UDP_CONFIG_H

#include "sys.h"
#include "nbiotconfig.h"
#include "net_nbiot_app.h"

#define UDP_COMMAND_TIMEOUT_SEC			30
#define UDP_COMMAND_FAILURE_CNT			3

/* UDP 协议栈开辟缓存大小 */
#define UDP_BUFFER_SIZE					256
#define UDP_DATASTACK_SIZE				256






typedef struct UDP_SocketNetTypeDef		UDP_SocketNetTypeDef;
typedef struct UDP_ClientsTypeDef			UDP_ClientsTypeDef;





/* UDP Status */
typedef enum
{
	UDP_OK       						= 0x00,
	UDP_ERROR    						= 0x01
}UDP_StatusTypeDef;















/* UDP Socket */
struct UDP_SocketNetTypeDef
{
	int								SocketHandler;
	unsigned short						LocalPort;
	unsigned short						ServerPort;
	unsigned char						ServerHost[16];
	NBIOT_ClientsTypeDef*				NBIotStack;
	UDP_StatusTypeDef					(*Open)(UDP_SocketNetTypeDef*);
	UDP_StatusTypeDef					(*Close)(UDP_SocketNetTypeDef*);
	UDP_StatusTypeDef					(*Write)(UDP_SocketNetTypeDef*, const char*, u16);
	UDP_StatusTypeDef					(*Read)(UDP_SocketNetTypeDef*, char*, u16, int*, int*);
};

/* UDP Clients */
struct UDP_ClientsTypeDef
{
	unsigned char*						Sendbuf;
	unsigned char*						Recvbuf;
	size_t							Sendbuf_size;
	size_t							Recvbuf_size;
	short							Sendlen;
	short							Recvlen;
	unsigned char*						DataProcessStack;
	size_t							DataProcessStack_size;
	unsigned short						Command_Timeout_Sec;
	unsigned short						Command_Failure_Cnt;
	
	
	
	
	
	UDP_SocketNetTypeDef*				SocketStack;
	NET_NBIOT_ClientsTypeDef*			NetNbiotStack;
};

























#endif /* __UDP_CONFIG_H */
