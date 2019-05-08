// tmesh_net_utility.h:  created at 2017-7-19 by Bell Zhong

#ifndef TMESH_NET_UTILITY_H_INCLUDED
#define TMESH_NET_UTILITY_H_INCLUDED
#include "stm32l1xx_hal.h"
#include <stdbool.h>



#define EEPROM_ADDR_BASE_VENDER    (0x0c00)
#define EEPROM_ADDR_SIZE_VENDER    (0x0004)
#define EEPROM_ADDR_BASE_MACSN     (0x0c04)
#define EEPROM_ADDR_SIZE_MACSN     (0x0004)

// only 4 bits in uart interactive protocol
typedef enum
{
	MSG_CONFIG 	= 0,			// 针对主控的一些配置命令
	MSG_PROTOBUF = 2,
	MSG_PLAIN 	= 3,
	MSG_TO_RF 	= 4,			//命令通过RF来转发
	MSG_DIRECT 	= 5,			//命令直接下达给接受设备
	MSG_NB_CMD 	= 6,			//the command sent to NB-IOT model
	MSG_NB_DATA = 7,		//the data sent to NB-IOT model
} UART_msg_type;


typedef enum tmesh_ret_code
{

	TMESH_OK = 0,
	TMESH_UNKNOWNERROR = 1,					//未知错误
	TMESH_VERSIONNOTSUPPORT = 2,			//版本不支持
	TMESH_COMMANDNOTVALID = 3,				//非法请求
	TMESH_LOGINED = 4,						//该用户已经登录
	TMESH_UNLOGINED = 5,					//该用户未登录
	TMESH_USERORPWDERROR = 6,				//用户名密码错误
	TMESH_NOAUTHORITY = 7,					//无权限
	TMESH_TIMEOUT = 8,						//超时
	//NETIP_FILENOTFOUND = 109,				//查找失败，没有找到对应文件
	//NETIP_FILEFOUND = 110,				//查找成功，返回全部文件
	//NETIP_FILEFOUNDPART = 111,			//查找成功，返回部分文件
	//NETIP_USEREXIST = 112,				//该用户已经存在
	//NETIP_USENOTEXIST = 113,				//该用户不存在
	//NETIP_GROUPEXIST = 114,				//该用户组已经存在
	//NETIP_GROUPNOTEXIST = 115,			//该用户组不存在
	TMESH_NOTLINKEDIN	= 16,				// device is not linked in the gateway.
	TMESH_OFFLINE		= 17,				// notify the device to update the firmware.
	TMESH_NOTMACHED		= 18,				// device has not matched to the gateway,but is offline.
	TMESH_CACHEDSUCCESS	= 19,
	TMESH_CACHEDFAIL	= 20,
	TMESH_NEEDUPDATE	= 21,				// device has linked in the gateway,but is offline.
	TMESH_NEEDREBOOT	= 50,				//成功，设备需要重启
	//NET_OPERATION_UPGRADE_ALAREADY_START	= 511,//重复开启
	//NET_OPERATION_UPGRADE_NOT_START		= 512,//未开始升级
	//NET_OPERATION_UPGRADE_FAILED			= 514,//操作失败
	//NET_OPERATION_UPGRADE_FAILED_BUSY		= 516,//设备忙或者服务器忙
	//NET_OPERATION_UPGRADE_NO_POWER		= 517 //该升级由其他连接开启，无法停止
} TMESH_RET_CODE;


typedef enum ret_code
{
	NETIP_OK = 100,
	NETIP_UNKNOWNERROR = 101,			//未知错误
	NETIP_NOTSUPPORT = 102,				//版本不支持
	NETIP_NOTVALID = 103,				//非法请求
	NETIP_LOGINED = 104,				//该用户已经登录
	NETIP_UNLOGINED = 105,				//该用户未登录
	NETIP_USERORPWDERROR = 106,			//用户名密码错误
	NETIP_NOPOWER = 107,				//无权限
	NETIP_TIMEOUT = 108,				//超时
	NETIP_NOTFOUND = 109,				//查找失败，没有找到对应文件
	NETIP_FOUND = 110,					//查找成功，返回全部文件
	NETIP_FOUNDPART = 111,				//查找成功，返回部分文件
	NETIP_USEREXIST = 112,				//该用户已经存在
	NETIP_USENOTEXIST = 113,			//该用户不存在
	NETIP_GROUPEXIST = 114,				//该用户组已经存在
	NETIP_GROUPNOTEXIST = 115,			//该用户组不存在
	NETIP_NOTLINKEDIN	= 116,			// device has not linked in the gateway
	NETIP_OFFLINE		= 117,			// device has linked in the gateway,but is offline.
	NETIP_NOTMACHED		= 118,			// device has linked in the gateway,but is offline.
	NETIP_CACHEDSUCCESS	= 119,
	NETIP_CACHEDFAIL	= 120,
	NETIP_NEEDUPDATE	= 121,
	NETIP_NEEDREBOOT 	= 150,			//成功，设备需要重启
	NET_OPERATION_UPGRADE_ALAREADY_START = 511,//重复开启
	NET_OPERATION_UPGRADE_NOT_START		 = 512,//未开始升级
	NET_OPERATION_UPGRADE_FAILED		 = 514,//操作失败
	NET_OPERATION_UPGRADE_FAILED_BUSY	 = 516,//设备忙或者服务器忙
	NET_OPERATION_UPGRADE_NO_POWER		 = 517 //该升级由其他连接开启，无法停止
} RET_CODE;


// 1 Byte in cloud interactive protocol
typedef enum
{
	MSG_JSON 	= '1',
	MSG_FIRMWARE = '3',		// used for upgrading
} TCLD_msg_type;

uint8_t tnet_utility_get_packetnum(void);
void delay_ms(uint16_t xms);
char* tnet_utility_get_sn_with_prefix(void);
char* tnet_utility_get_sn_without_prefix(void);
char* tnet_utility_get_sn(void);
char* tnet_utility_get_vender(void);
char* tnet_utility_get_spotid(void);
char* tnet_utility_get_hardware(void);
char* tnet_utility_get_software(void);
char* tnet_utility_get_buildtime(void);
int tnet_utility_get_runtime(void);
int tnet_utility_get_rssi(void);
char* tnet_utility_get_sim(void);
int tnet_utility_get_batt(void);
char* tnet_utility_get_imei(void);
char* tnet_utility_get_model(void);
uint32_t tnet_utility_get_mac_sn(void);

#endif

