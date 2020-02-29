/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-21
  * @brief   1TAB = 5Speace
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "stm8l15x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hal_ook.h"
#include "hal_timer.h"

uint8_t  OOKData;
uint8_t  old_rc5;
uint8_t  tb_ok;
uint8_t  bt_auto;
uint8_t  bma1, bma2, bma3, bma4;
uint8_t  mma1, mma2, mma3, mma4;
uint8_t  mmb1, mmb2, mmb3, mmb4;
uint8_t  rf_ok1, rf_ok2, rf_ok;
uint8_t  rf_data[4];
uint16_t ma_x;
uint16_t hh_w, ll_w;
uint16_t s, s1;
uint16_t decode_ok;

uint8_t  rfkeyflag = 0;
uint8_t  rfkey1;
uint8_t  rfkey2;

void OOKRecvData(void);

/**********************************************************************************************************
 @Function			void main(void)
 @Description			Main
 @Input				void
 @Return				void
**********************************************************************************************************/
void main(void)
{
     Stm8_HSIClock_Init(CLK_SYSCLKDiv_1);
     
     Stm8_OOK_Init();
     
     OOK_DATA_TX_SET(OFF);
     
     while (1) {
          
          OOKRecvData();
          
#if 0     /* App Control */
          if (decode_ok == 1) {
               
               if (rfkeyflag == 0) {
                    rfkeyflag = 1;
                    rfkey1 = rf_data[0];
                    rfkey2 = rf_data[1];
               }
               else {
                    if ((rfkey1 == rf_data[0]) && (rfkey2 == rf_data[1])) {
                         switch (rf_data[2])
                         {
                              case 0x21: {
                                   OOK_DATA_TX_SET(ON);
                                   break;
                              }
                              case 0x24: {
                                   OOK_DATA_TX_SET(OFF);
                                   break;
                              }
                         }
                    }
               }
               
               decode_ok = 0;
          }
#endif
          
#if 1     /* Data Send OOK */
          if (decode_ok == 1) {
               
               /* Sum Check Code */
               rf_data[3] = rf_data[0] + rf_data[1] + rf_data[2];
               
               /* Send Start Time Sequence */
               OOK_DATA_TX_SET(ON);
               Delay_US_FuncType1(152);
               OOK_DATA_TX_SET(OFF);
               
               /* Low Time Sequence */
               Delay_US_FuncType1(5);
               
               /* Send Data[0] Code Time Sequence */
               for (uint8_t index = 0; index < 8; index++) {
                    if (rf_data[0] & 0x80) {
                         /* Send 1 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(52);
                         OOK_DATA_TX_SET(OFF);
                    }
                    else {
                         /* Send 0 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(20);
                         OOK_DATA_TX_SET(OFF);
                    }
                    rf_data[0] <<= 1;
                    /* Low Time Sequence */
                    Delay_US_FuncType1(5);
               }
               
               /* Send Data[0] Code Time Sequence */
               for (uint8_t index = 0; index < 8; index++) {
                    if (rf_data[1] & 0x80) {
                         /* Send 1 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(52);
                         OOK_DATA_TX_SET(OFF);
                    }
                    else {
                         /* Send 0 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(20);
                         OOK_DATA_TX_SET(OFF);
                    }
                    rf_data[1] <<= 1;
                    /* Low Time Sequence */
                    Delay_US_FuncType1(5);
               }
               
               /* Send Data[0] Code Time Sequence */
               for (uint8_t index = 0; index < 8; index++) {
                    if (rf_data[2] & 0x80) {
                         /* Send 1 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(52);
                         OOK_DATA_TX_SET(OFF);
                    }
                    else {
                         /* Send 0 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(20);
                         OOK_DATA_TX_SET(OFF);
                    }
                    rf_data[2] <<= 1;
                    /* Low Time Sequence */
                    Delay_US_FuncType1(5);
               }
               
               /* Send Data[0] Code Time Sequence */
               for (uint8_t index = 0; index < 8; index++) {
                    if (rf_data[3] & 0x80) {
                         /* Send 1 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(52);
                         OOK_DATA_TX_SET(OFF);
                    }
                    else {
                         /* Send 0 bit */
                         OOK_DATA_TX_SET(ON);
                         Delay_US_FuncType1(20);
                         OOK_DATA_TX_SET(OFF);
                    }
                    rf_data[3] <<= 1;
                    /* Low Time Sequence */
                    Delay_US_FuncType1(5);
               }
               
               /* Send End Time Sequence */
               OOK_DATA_TX_SET(ON);
               Delay_US_FuncType1(100);
               OOK_DATA_TX_SET(OFF);
               
               decode_ok = 0;
          }
#endif
     }
}

/**********************************************************************************************************
 @Function			void OOKRecvData(void)
 @Description			OOKRecvData
 @Input				void
 @Return				void
**********************************************************************************************************/
void OOKRecvData(void)
{
     while (1) {
          OOKData = OOK_DATA_RX_READ();
          
          if (!OOKData) {
               ll_w++;
               old_rc5 = 0;
          }
          else {
               hh_w++;
               if (!old_rc5) {
                    if (((hh_w >= 2) && (hh_w <= 5)) && ((ll_w >= 100) && (ll_w <= 130))) {
                         tb_ok = 1;
                         ma_x = 0;
                         bma1 = 0; bma2 = 0; bma3 = 0; bma4 = 0;
                    }
                    else if ((tb_ok) && ((ll_w >= 8) && (ll_w <= 13))) {
                         ma_x++;
                         if (ma_x > 23) {
                              if (!rf_ok1) {
                                   mma1 = bma1;
                                   mma2 = bma2;
                                   mma3 = bma3;
                                   mma4 = bma4;
                                   rf_ok1 = 1;
                                   tb_ok = 0;
                                   s = 10000;
                              }
                              else {
                                   mmb1 = bma1;
                                   mmb2 = bma2;
                                   mmb3 = bma3;
                                   mmb4 = bma4;
                                   rf_ok2 = 1;
                                   tb_ok = 0;
                              }
                         }
                    }
                    else if ((tb_ok) && ((ll_w >= 2) && (ll_w <= 7))) {
                         switch (ma_x)
                         {
                              case 0 : {
                                   bma1 = bma1 | 0x80;
                                   break;
                              }
                              case 1 : {
                                   bma1 = bma1 | 0x40;
                                   break;
                              }
                              case 2 : {
                                   bma1 = bma1 | 0x20;
                                   break;
                              }
                              case 3 : {
                                   bma1 = bma1 | 0x10;
                                   break;
                              }
                              case 4 : {
                                   bma1 = bma1 | 0x08;
                                   break;
                              }
                              case 5 : {
                                   bma1 = bma1 | 0x04;
                                   break;
                              }
                              case 6 : {
                                   bma1 = bma1 | 0x02;
                                   break;
                              }
                              case 7 : {
                                   bma1 = bma1 | 0x01;
                                   break;
                              }
                              case 8 : {
                                   bma2 = bma2 | 0x80;
                                   break;
                              }
                              case 9 : {
                                   bma2 = bma2 | 0x40;
                                   break;
                              }
                              case 10: {
                                   bma2 = bma2 | 0x20;
                                   break;
                              }
                              case 11: {
                                   bma2 = bma2 | 0x10;
                                   break;
                              }
                              case 12: {
                                   bma2 = bma2 | 0x08;
                                   break;
                              }
                              case 13: {
                                   bma2 = bma2 | 0x04;
                                   break;
                              }
                              case 14: {
                                   bma2 = bma2 | 0x02;
                                   break;
                              }
                              case 15: {
                                   bma2 = bma2 | 0x01;
                                   break;
                              }
                              case 16: {
                                   bma3 = bma3 | 0x80;
                                   break;
                              }
                              case 17: {
                                   bma3 = bma3 | 0x40;
                                   break;
                              }
                              case 18: {
                                   bma3 = bma3 | 0x20;
                                   break;
                              }
                              case 19: {
                                   bma3 = bma3 | 0x10;
                                   break;
                              }
                              case 20: {
                                   bma3 = bma3 | 0x08;
                                   break;
                              }
                              case 21: {
                                   bma3 = bma3 | 0x04;
                                   break;
                              }
                              case 22: {
                                   bma3 = bma3 | 0x02;
                                   break;
                              }
                              case 23: {
                                   bma3 = bma3 | 0x01;
                                   if (!rf_ok1) {
                                        mma1 = bma1;
                                        mma2 = bma2;
                                        mma3 = bma3;
                                        rf_ok1 = 1;
                                        tb_ok = 0;
                                        s = 1000;
                                        break;
                                   }
                                   else {
                                        mmb1 = bma1;
                                        mmb2 = bma2;
                                        mmb3 = bma3;
                                        rf_ok2 = 1;
                                        tb_ok = 0;
                                        break;
                                   }
                              }
                         }
                         ma_x++;
                    }
                    else {
                         ma_x = 0; tb_ok = 0; bt_auto = 0; bma1 = 0; bma2 = 0; bma3 = 0; hh_w = 1; ll_w = 0;
                    }
                    ll_w = 0; hh_w = 1;
               }
               old_rc5 = 1;
          }
          
          if (rf_ok1) {
               s--;
               if (!s) rf_ok1 = 0;
               if (rf_ok2) {
                    if ((mma1 == mmb1) && (mma2 == mmb2) && (mma3 == mmb3)) {
                         rf_ok = 1;
                         rf_ok1 = 0;
                         rf_ok2 = 0;
                    }
                    else {
                         rf_ok = 0;
                         rf_ok1 = 0;
                         rf_ok2 = 0;
                    }
               }
          }
          
          if ((rf_ok)) {
               rf_ok = 0;
               rf_data[0] = mma1;
               rf_data[1] = mma2;
               rf_data[2] = mma3;
               
               decode_ok = 1;
               break;
          }
          
          for (uint8_t us = 0; us < 42; us++) {
               Delay_US_Normal();
          }
     }
}











/********************************************* DEBUG *****************************************************/
/****************************************** Debug Ending *************************************************/

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
     /* User can add his own implementation to report the file name and line number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
     
     /* Infinite loop */
     while (1) {
          
     }
}
#endif

/********************************************** END OF FLEE **********************************************/
