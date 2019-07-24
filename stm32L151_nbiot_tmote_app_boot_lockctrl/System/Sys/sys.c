/**
  *********************************************************************************************************
  * @file    sys.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "sys.h"


/**********************************************************************************************************
 @Function			void Stm32_Clock_Init(u32 pllmul, u32 plldiv)
 @Description			时钟设置函数(MAX32MHz)
 @Input				pllmul	: 主PLL倍频系数(PLL倍频),取值范围:0 ~ 48
					plldiv	: 系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,3,4.(仅限这3个值!)
 @Return				void
 @attention			Fsys = Fs*(pllmul/plldiv);

					Fsys : 系统时钟频率
					Fs	: PLL输入时钟频率,可以是HSI,HSE等
**********************************************************************************************************/
void Stm32_Clock_Init(u32 pllmul, u32 plldiv)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStructure;
	RCC_ClkInitTypeDef RCC_ClkInitStructure;
	HAL_RCC_DeInit();

	RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI;				//时钟源为HSI
	RCC_OscInitStructure.HSIState = RCC_HSI_ON;								//打开HSI
	RCC_OscInitStructure.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;							//打开PLL
	RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSI;					//PLL时钟源选择HSI
	RCC_OscInitStructure.PLL.PLLMUL = pllmul;								//主PLL倍频系数(PLL倍频)
	RCC_OscInitStructure.PLL.PLLDIV = plldiv;								//系统时钟的主PLL分频系数(PLL之后的分频)
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructure);							//初始化
	if (ret != HAL_OK) while(1);
	
	__HAL_RCC_PWR_CLK_ENABLE();											//使能PWR时钟
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);				//设置调压器输出电压级别, 以便在器件未以最大频率工作
	while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

	/* 选中PLL作为系统时钟源并且配置HCLK, PCLK1 和 PCLK2 */
	RCC_ClkInitStructure.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;				//设置系统时钟时钟源为PLL
	RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;						//AHB分频系数为1
	RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV1;						//APB1分频系数为1
	RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV1;						//APB2分频系数为1

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_1);			//同时设置FLASH延时周期为1WS, 也就是2个CPU周期
	if (ret != HAL_OK) while(1);
}


#ifdef  USE_FULL_ASSERT
/**********************************************************************************************************
 @Function			void assert_failed(uint8_t* file, uint32_t line)
 @Description			当编译提示出错的时候此函数用来报告错误的文件和所在行
 @Input				file		: 指向源文件
					line		: 指向在文件中的行数
 @Return				void
**********************************************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
	while (1)
	{
	}
}
#endif

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

/********************************************** END OF FLEE **********************************************/
