#include "ugrade.h"
#include <stdlib.h>
#include "tmesh_cfg.h"
#include <string.h>
#include "tmesh_rf_app.h"
#include "ugrade.h"
#include "hal_rf.h"
#include "iap.h"

//extern  uint8_t upgrade_type;
extern  char g_bootmode;
//u8 *ReceivedData;
uint8_t subsn[4];
uint8_t addr[4];
uint8_t overflow = 0;


extern unsigned int app_offset;

int packnum_received = 0;
int firmlen_received = 0;

#define	PACK_SIZE	128
int test_pgm_fail_cnt;
//unsigned char temp1,temp2;
unsigned int firm_offset;
uint8_t programUpdate(uint8_t *recvlong,uint8_t *sn)
{
  uint8_t packetno,rc = 0,*p = NULL,type;
  //uint16_t blockNum;
  //uint32_t Address;
  uint8_t buf_send[UPGD_FRAME_PAYLOAD_OFS+UPGD_FRAME_CRC_SIZE+UPGRADE_TYPE_SIZE];
  int rt;
  unsigned char* pData;
  

  type = (UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(recvlong),UPGD_HEAD_TYPE_OS ));

  packetno = UPGD_GET_FROM_FRAME(UPGD_P_FRAME_HEAD(recvlong),UPGD_PKTNUM_OS);

  
  if (type == UPGRADE_VALIDDATA)
  {
    if((packetno == 1)&&(!overflow))
    {
      //*(PointerAttr uint8_t*) (MemoryAddressCast)UPGRADE_TYPE_ADDR = 0x00;//表示接收数据超时，并且设置upgrade_type为0，（jump_to_app本身为0）
		tcfg_SetBootMode(TCFG_ENV_BOOTMODE_UPDATING);
		// check whether it's the right app
		pData = (unsigned char*)UPGD_P_FRAME_PAYLOAD(recvlong);
		app_offset &= 0xFFFF00FF;
		firm_offset = (pData[5]-2);
		app_offset |= (firm_offset<<8);		
		// program the address to flash
		if(app_offset >= APP_LOWEST_ADDRESS){
			xm_iap_program(APP_LOWEST_ADDRESS-256,0, 4, (unsigned char*)(&app_offset));
		}
		
    }
	if(app_offset < APP_LOWEST_ADDRESS)
		return TRANSERROR;
	if((packnum_received%256) != packetno){	// not the same packet.  
		//blockNum = packetno+39+overflow*256;
		//FLASH_ProgramBlock(blockNum, FLASH_MemType_Program, FLASH_ProgramMode_Standard,UPGD_P_FRAME_PAYLOAD(recvlong));
		rt = xm_iap_program(app_offset,packnum_received*PACK_SIZE, PACK_SIZE, (unsigned char*)UPGD_P_FRAME_PAYLOAD(recvlong));
		if ( rt == IAP_OK)
		{
			packnum_received += 1;
			firmlen_received += PACK_SIZE;
			rc =  UNCOMPLETE;
		}else{
			test_pgm_fail_cnt++;
			rc =  TRANSERROR;
		}
		if(packetno == 255)
		{
		  overflow++;
		}
		if((packnum_received%256) != packetno)	//%255
			rc = TRANSERROR;
	}	
    
  }
  else if(type == UPGRADE_END)
  {
    rc = COMPLETE;
  }
  
  xm_Upgd_buildframe(p,UPGRADE_VALIDDATA_RSP,packetno,sn,buf_send,0);//invalid data with no app msg


  tmesh_rf_send(buf_send,*buf_send);
  return rc;

}





void xm_join(void)
{

	uint8_t buf[UPGD_FRAME_PAYLOAD_OFS+UPGD_FRAME_CRC_SIZE+UPGRADE_TYPE_SIZE];

	xm_Upgd_buildframe((uint8_t *)&g_bootmode,UPGRADE_REQUEST,0,subsn,buf,UPGRADE_TYPE_SIZE);

	tmesh_rf_send(buf,*buf);

}


void xm_Upgd_buildframe(uint8_t *msg,uint8_t type,uint8_t pktnum,uint8_t *sn,uint8_t *send,uint8_t len)
{
  uint8_t i;
  uint16_t check_sum=0;

  UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_LEN(send),UPGD_LEN_OS,UPGD_FRAME_PAYLOAD_OFS+UPGD_FRAME_CRC_SIZE+len-UPGD_FRAME_LEN_SIZE);

  UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_PRE(send),UPGD_PRE_TYPE_OS,UPGRADE_PRT);//what type of protocol?

  UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_PRE(send),UPGD_PRE_VS_OS,UPGRADEVERSION);//version of protocol?

  UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_HEAD(send),UPGD_HEAD_TYPE_OS,type);//type of head?

  if(((type == UPGRADE_VALIDDATA)||(type == UPGRADE_VALIDDATA_RSP)||(type == UPGRADE_END)))
  {
    UPGD_PUT_INTO_FRAME(UPGD_P_FRAME_HEAD(send),UPGD_PKTNUM_OS,pktnum);//type of head		
  }

  if(len)			
    memcpy(UPGD_P_FRAME_PAYLOAD(send),msg,len);

  memcpy(UPGD_P_FRAME_SN(send),sn,4);


  for(i=1;i<UPGD_FRAME_PAYLOAD_OFS+len;i++)
  check_sum+=send[i];

  send[UPGD_FRAME_PAYLOAD_OFS+len] = check_sum/0x100;
  send[UPGD_FRAME_PAYLOAD_OFS+len+1] = check_sum%0x100;
  return;
}


uint8_t CheckSum(uint8_t *recv_data)
{
	uint16_t check_sum = 0 ,i,len;
	len  = *recv_data;//packet_len
		/*****calculate the check sum after build the packet*/
        check_sum=0;
	  for(i=1;i<len-1;i++)
	{
		check_sum +=recv_data[i];//the first byte of len is not used for sum
	}
	*recv_data-=2;
	if(check_sum==(recv_data[i]*0x100+recv_data[i+1]))  return 1;
	else return 0;
}

void Get_sn(void)
{
#if 1
  uint8_t i;
  for(i=0;i<4;i++)
  {
//    subsn[3-i] = *(PointerAttr uint8_t *) (MemoryAddressCast)(SUBSN_ADDR+i);//*(__IO uint8_t*) (SUBSN_ADDR+i);
  }
#endif
}



void Get_addr(void)
{
  #if 1
  uint8_t i;
  for(i=0;i<4;i++)
  {
//    addr[3-i] =  *(PointerAttr uint8_t *) (MemoryAddressCast)(PHY_ADDR_IN_FLASH+i);
  }
#endif
}
