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

void delay_us(void)
{
     asm("nop");
     asm("nop");
     asm("nop");
     asm("nop");
}

void delay_ms(u32 nCount)
{
     while (nCount--) {
          for (unsigned int i = 900; i > 0; i--) delay_us();
     }
}












/**********************************************************************************************************
 @Function			void main(void)
 @Description			Main
 @Input				void
 @Return				int
**********************************************************************************************************/
void main(void)
{
     Stm8_HSIClock_Init(CLK_SYSCLKDiv_1);
     
     GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_High_Fast);
     
     GPIO_SetBits(GPIOB, GPIO_Pin_5);
     
     while (1) {
          
          GPIO_ToggleBits(GPIOB, GPIO_Pin_5);
          
          delay_ms(1000);
          
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
