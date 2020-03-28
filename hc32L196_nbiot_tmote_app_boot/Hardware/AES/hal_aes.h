#ifndef __HAL_AES_H
#define   __HAL_AES_H

#include "sys.h"
#include "aes.h"

void HC32_AES_Encrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen);				// AES 加密
void HC32_AES_Decrypt(u32* Cipher, u32* Plaintext, u32* Key, en_aes_key_type_t KeyLen);				// AES 解密

#endif /* __HAL_AES_H */
