/**
  *********************************************************************************************************
  * @file    hal_aes.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2020-03-28
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hc32l19x_config.h"
#include "platform_config.h"
#include "platform_map.h"
#include "hal_aes.h"
#include "delay.h"
#include "usart.h"

/**********************************************************************************************************
 @Function			void HC32_AES_Encrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen)
 @Description			HC32_AES_Encrypt							: AES 加密
 @Input				Cipher									: AES 密文指针
					Plaintext									: AES 明文指针
					Key										: AES 密钥指针
					KeyLen									: AES 密钥长度类型
 @Return				void
**********************************************************************************************************/
void HC32_AES_Encrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen)
{
	stc_aes_cfg_t AES_Initure;
	
	AES_Initure.pu32Plaintext	= Plaintext;
	AES_Initure.pu32Cipher		= Cipher;
	AES_Initure.pu32Key			= Key;
	AES_Initure.enKeyLen		= KeyLen;
	
	AES_Encrypt(&AES_Initure);
}

/**********************************************************************************************************
 @Function			void HC32_AES_Decrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen)
 @Description			HC32_AES_Decrypt							: AES 解密
 @Input				Cipher									: AES 密文指针
					Plaintext									: AES 明文指针
					Key										: AES 密钥指针
					KeyLen									: AES 密钥长度类型
 @Return				void
**********************************************************************************************************/
void HC32_AES_Decrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen)
{
	stc_aes_cfg_t AES_Initure;
	
	AES_Initure.pu32Plaintext	= Plaintext;
	AES_Initure.pu32Cipher		= Cipher;
	AES_Initure.pu32Key			= Key;
	AES_Initure.enKeyLen		= KeyLen;
	
	AES_Decrypt(&AES_Initure);
}

/********************************************** END OF FLEE **********************************************/
