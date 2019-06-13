#ifndef __UDP_CONFIG_H
#define   __UDP_CONFIG_H

#include "sys.h"
#include "nbiotconfig.h"
#include "net_nbiot_app.h"

#define UDP_MAX_MSG_ID					255

#define UDP_COMMAND_TIMEOUT_SEC			30
#define UDP_COMMAND_FAILURE_CNT			3

/* UDP 协议栈开辟缓存大小 */
#define UDP_BUFFER_SIZE					256
#define UDP_DATASTACK_SIZE				256

typedef struct UDP_SocketNetTypeDef		UDP_SocketNetTypeDef;
typedef struct UDP_ClientsTypeDef			UDP_ClientsTypeDef;

/* UDP Is ProcessState */
typedef enum
{
	UDP_PROCESS_CREAT_UDP_SOCKET			= 0x00,
	UDP_PROCESS_CONNECT_SERVER			= 0x01,
	UDP_PROCESS_SEND_DATA				= 0x02,
	UDP_PROCESS_SLEEP					= 0x03,
	UDP_PROCESS_HEART					= 0x04
}UDP_ProcessStateTypeDef;

/* UDP Status */
typedef enum
{
	UDP_OK       						= 0x00,
	UDP_ERROR    						= 0x01,
	UDP_BUFFER_OVERFLOW					= 0x02,
	UDP_RECVPACKET_NONE					= 0x03,
	UDP_CMD_TIMEOUT					= 0x04,
	UDP_MESSAGE_HANDLERS_FULL			= 0x05
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
	unsigned short						MsgIdNormal;
	unsigned short						MsgIdStatus;
	unsigned short						Command_Timeout_Sec;
	unsigned short						Command_Failure_Cnt;
	
	unsigned char						UDPRunFailFlag;
	
	struct UDPDictateRuningCtlTypeDef
	{
		bool							dictateEnable;
		unsigned int					dictateTimeoutSec;
		unsigned char					dictateCreatUDPSocketFailureCnt;
		unsigned char					dictateConnectServerFailureCnt;
		unsigned char					dictateSendDataFailureCnt;
		unsigned char					dictateSleepFailureCnt;
		unsigned char					dictateHeartFailureCnt;
		Stm32_CalculagraphTypeDef		dictateRunTime;
	}DictateRunCtl;
	
	UDP_ProcessStateTypeDef				ProcessState;
	UDP_SocketNetTypeDef*				SocketStack;
	NET_NBIOT_ClientsTypeDef*			NetNbiotStack;
	
	Stm32_CalculagraphTypeDef			HeartTimer;
};

/* Application Programming Interface */
void UDP_WaitforCallback(UDP_ClientsTypeDef* pClient);																//UDP数据等待接收回调函数
void UDP_Client_Init(UDP_ClientsTypeDef* pClient, UDP_SocketNetTypeDef* NetSock, NET_NBIOT_ClientsTypeDef* NetNbiotStack);		//UDP客户端初始化

#endif /* __UDP_CONFIG_H */
