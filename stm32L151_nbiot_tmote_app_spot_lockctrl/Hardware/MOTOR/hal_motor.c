/**
  *********************************************************************************************************
  * @file    hal_motor.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2019-08-06
  * @brief   
  *********************************************************************************************************
  * @attention
  *		  MOTOR_BI ---> PB9
  *		  MOTOR_FI ---> PB8
  *
  *
  *********************************************************************************************************
  */

#include "hal_motor.h"
#include "hal_infraredtube.h"
#include "hal_buzzer.h"
#include "hal_beep.h"
#include "hal_iwdg.h"
#include "delay.h"
#include "usart.h"
#include "radio_hal_rf.h"
#include "radio_rf_app.h"
#include "platform_config.h"
#include "platform_map.h"

ADC_HandleTypeDef		MOTOR_SNS_Handler;

/**********************************************************************************************************
 @Function			void MOTOR_SNS_Init(void)
 @Description			MOTOR_SNS_Init
 @Input				void
 @Return				void
**********************************************************************************************************/
void MOTOR_SNS_Init(void)
{
	ADC_ChannelConfTypeDef ADC_ChanelConfig;
	
	// ADC Function Configuration
	MOTOR_SNS_Handler.Instance = ADC1;
	MOTOR_SNS_Handler.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	MOTOR_SNS_Handler.Init.Resolution = ADC_RESOLUTION_12B;
	MOTOR_SNS_Handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	MOTOR_SNS_Handler.Init.ScanConvMode = ADC_SCAN_DISABLE;
	MOTOR_SNS_Handler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	MOTOR_SNS_Handler.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
	MOTOR_SNS_Handler.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
	MOTOR_SNS_Handler.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
	MOTOR_SNS_Handler.Init.ContinuousConvMode = DISABLE;
	MOTOR_SNS_Handler.Init.NbrOfConversion = 1;
	MOTOR_SNS_Handler.Init.DiscontinuousConvMode = DISABLE;
	MOTOR_SNS_Handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	MOTOR_SNS_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	MOTOR_SNS_Handler.Init.DMAContinuousRequests = DISABLE;
	if (HAL_ADC_Init(&MOTOR_SNS_Handler) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
		return ;
	}
	
	// ADC Channel Configuration
	ADC_ChanelConfig.Channel = ADC_CHANNEL_8;
	ADC_ChanelConfig.Rank = ADC_REGULAR_RANK_1;
	ADC_ChanelConfig.SamplingTime = ADC_SAMPLETIME_384CYCLES;
	if (HAL_ADC_ConfigChannel(&MOTOR_SNS_Handler, &ADC_ChanelConfig) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
		return ;
	}
}

/**********************************************************************************************************
 @Function			u16 MOTOR_SNS_Read(u32 timeout)
 @Description			MOTOR_SNS_Read
 @Input				
 @Return				
**********************************************************************************************************/
u16 MOTOR_SNS_Read(u32 timeout)
{
	u32 pwr_vol = 0;
	GPIO_InitTypeDef GPIO_Initure;
	
	MOTOR_SNS_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = MOTOR_SNS_PIN;
	GPIO_Initure.Mode = GPIO_MODE_ANALOG;
	GPIO_Initure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(MOTOR_SNS_GPIOx, &GPIO_Initure);
	
	MOTOR_SNS_Init();
	
	HAL_ADC_Start(&MOTOR_SNS_Handler);
	
	HAL_ADC_PollForConversion(&MOTOR_SNS_Handler, timeout);
	
	pwr_vol = HAL_ADC_GetValue(&MOTOR_SNS_Handler);
	
	HAL_ADC_Stop(&MOTOR_SNS_Handler);
	
	MOTOR_SNS_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = MOTOR_SNS_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_Initure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(MOTOR_SNS_GPIOx, &GPIO_Initure);
	HAL_GPIO_WritePin(MOTOR_SNS_GPIOx, MOTOR_SNS_PIN, GPIO_PIN_RESET);
	
	HAL_ADC_DeInit(&MOTOR_SNS_Handler);
	
	return pwr_vol * 280 / 4096.0;
}

/**********************************************************************************************************
 @Function			void MOTOR_BI_OUT(u8 val)
 @Description			MOTOR_BI_OUT
 @Input				ON or OFF
 @Return				void
**********************************************************************************************************/
void MOTOR_BI_OUT(u8 val)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	MOTOR_BI_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = MOTOR_BI_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(MOTOR_BI_GPIOx, &GPIO_Initure);
	
	MOTOR_BI(val);
}

/**********************************************************************************************************
 @Function			void MOTOR_FI_OUT(u8 val)
 @Description			MOTOR_FI_OUT
 @Input				ON or OFF
 @Return				void
**********************************************************************************************************/
void MOTOR_FI_OUT(u8 val)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	MOTOR_FI_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = MOTOR_FI_PIN;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_NOPULL;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(MOTOR_FI_GPIOx, &GPIO_Initure);
	
	MOTOR_FI(val);
}

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE1
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Initialization
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	Stm32_CalculagraphTypeDef motorTimer;
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	IWDG_Feed();
	
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	while (true) {
		IWDG_Feed();
		
		if ((ctrl != SPOTLOCK_CTRL_RISE) && (ctrl != SPOTLOCK_CTRL_FALL)) break;
		
		if (ctrl == SPOTLOCK_CTRL_RISE) {
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_FALL();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_RISE();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_RISE();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
			Delay_MS(100);
#endif
			break;
		}
		
		if (ctrl == SPOTLOCK_CTRL_FALL) {
			if (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_FALL();
				while (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_RISE;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
			Delay_MS(100);
#endif
			break;
		}
exit:
		continue;
	}
	
error:
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	IWDG_Feed();
	
	MOTOR_OPEN();
}
#endif

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE1
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Control
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	Stm32_CalculagraphTypeDef motorTimer;
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	IWDG_Feed();
	
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	while (true) {
		if ((ctrl != SPOTLOCK_CTRL_RISE) && (ctrl != SPOTLOCK_CTRL_FALL)) break;
		
		if (ctrl == SPOTLOCK_CTRL_RISE) {
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_FALL();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_RISE();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_RISE();
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
			Delay_MS(100);
#endif
			break;
		}
		
		if (ctrl == SPOTLOCK_CTRL_FALL) {
			if (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
				Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				MOTOR_FALL();
				while (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_RISE;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
			Delay_MS(100);
#endif
			break;
		}
exit:
		continue;
	}
	
error:
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	IWDG_Feed();
	
	MOTOR_OPEN();
}
#endif

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE1
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Keep(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Keep
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Keep(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	bool BeepON = false;
	
	static unsigned char SpotLockKeepErr;
	
	Stm32_CalculagraphTypeDef motorTimer;
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	IWDG_Feed();
	
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	if ((SpotLockKeepErr > MOTOR_CTRL_KEEP_ERR_CNT) && (INFRARED_TUBE_SPOTLOCK_STATE() != INFRARED_TUBE_ERROR) && (INFRARED_TUBE_SPOTLOCK_STATE() != INFRARED_TUBE_FALL)) {
#if MOTOR_BUZZER_ERR
		BUZZERCtrlIO(ON);
#else
		BEEP_CtrlRepeat_Extend(1, 50, 15);
#endif
		goto error;
	}
	
	if ((SpotLockKeepErr > MOTOR_CTRL_KEEP_ERR_CNT) && (MOTOR_SPOTLOCK_STATE() != ctrl)) {
#if MOTOR_BUZZER_ERR
		BUZZERCtrlIO(ON);
#else
		BEEP_CtrlRepeat_Extend(1, 50, 15);
#endif
		goto error;
	}
	
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	if (ctrl == SPOTLOCK_CTRL_RISE) {
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
			Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			MOTOR_FALL();
			while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE)) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErr += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
			Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			MOTOR_RISE();
			while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErr += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
			Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			MOTOR_RISE();
			while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErr += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
#if MOTOR_BEEP_CTRL
		if (BeepON) BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
		if (BeepON) Delay_MS(100);
#endif
	}
	
	if (ctrl == SPOTLOCK_CTRL_FALL) {
		if (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
			Stm32_Calculagraph_CountdownMS(&motorTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			MOTOR_FALL();
			while (!(INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL)) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErr += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
#if MOTOR_BEEP_CTRL
		if (BeepON) BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
		if (BeepON) Delay_MS(100);
#endif
	}
	
	SpotLockKeepErr = 0;
	
#if MOTOR_BUZZER_ERR
	BUZZERCtrlIO(OFF);
#endif
	
error:
	if (SpotLockKeepErr < 100) SpotLockKeepErr++;
	
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	IWDG_Feed();
	
	MOTOR_OPEN();
}
#endif

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE2
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Initialization
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Initialization(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	/* 电机SNS电流过大超时时间定时器 */
	Stm32_CalculagraphTypeDef motorSNSTimer;
	/* 间隔MS超时退出电机控制定时器 */
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	/* 单次摇臂控制时间注入 */
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 红外发射管使能开启 */
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	while (true) {
		
		/* 喂狗 */
		IWDG_Feed();
		
		/* 控制类型判断 */
		if ((ctrl != SPOTLOCK_CTRL_RISE) && (ctrl != SPOTLOCK_CTRL_FALL)) break;
		
		/* 控制锁摇臂升起 */
		if (ctrl == SPOTLOCK_CTRL_RISE) {
			
			/* 90° <= 摇臂 <= 180°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机反转 */
				MOTOR_FALL();
				/* 等待摇臂 <= 90° */
				while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
			/* 00° <= 摇臂 <= 05°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机正转 */
				MOTOR_RISE();
				/* 等待摇臂 >= 05° */
				while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
			/* 05° <= 摇臂 <= 80°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机正转 */
				MOTOR_RISE();
				/* 等待摇臂 >= 80° */
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_OPEN();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
			Delay_MS(100);
#endif
			break;
		}
		
		/* 控制锁摇臂降下 */
		if (ctrl == SPOTLOCK_CTRL_FALL) {
			
			/* 摇臂 != 00°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机反转 */
				MOTOR_FALL();
				/* 等待摇臂 == 00° */
				while (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_RISE;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
			Delay_MS(100);
#endif
			break;
		}
		
exit:
		continue;
	}
	
error:
	/* 红外发射管失能关闭 */
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 电机释放 */
	MOTOR_OPEN();
}
#endif

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE2
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Control
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Control(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	/* 电机SNS电流过大超时时间定时器 */
	Stm32_CalculagraphTypeDef motorSNSTimer;
	/* 间隔MS超时退出电机控制定时器 */
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	/* 单次摇臂控制时间注入 */
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 红外发射管使能开启 */
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	while (true) {
		
		/* 喂狗 */
		IWDG_Feed();
		
		/* 控制类型判断 */
		if ((ctrl != SPOTLOCK_CTRL_RISE) && (ctrl != SPOTLOCK_CTRL_FALL)) break;
		
		/* 控制锁摇臂升起 */
		if (ctrl == SPOTLOCK_CTRL_RISE) {
			
			/* 90° <= 摇臂 <= 180°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机反转 */
				MOTOR_FALL();
				/* 等待摇臂 <= 90° */
				while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
			/* 00° <= 摇臂 <= 05°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机正转 */
				MOTOR_RISE();
				/* 等待摇臂 >= 05° */
				while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
			/* 05° <= 摇臂 <= 80°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机正转 */
				MOTOR_RISE();
				/* 等待摇臂 >= 80° */
				while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_FALL;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_OPEN();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
			Delay_MS(100);
#endif
			break;
		}
		
		/* 控制锁摇臂降下 */
		if (ctrl == SPOTLOCK_CTRL_FALL) {
			
			/* 摇臂 != 00°状态 */
			if (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
				/* 电机SNS电流过大超时时间注入 */
				Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
				/* 电机反转 */
				MOTOR_FALL();
				/* 等待摇臂 == 00° */
				while (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
					if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) {
						ctrl = SPOTLOCK_CTRL_RISE;
						goto exit;
					}
					if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) goto error;
				}
				/* 电机锁定 */
				MOTOR_LOCK();
			}
			
#if MOTOR_BEEP_CTRL
			BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
			Delay_MS(100);
#endif
			break;
		}
		
exit:
		continue;
	}
	
error:
	/* 红外发射管失能关闭 */
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 电机释放 */
	MOTOR_OPEN();
}
#endif

#if MOTOR_DEVICE_TYPE == MOTOR_DEVICE_TYPE2
/**********************************************************************************************************
 @Function			void MOTOR_SPOTLOCK_Keep(MOTOR_SpotLockCtrlTypeDef ctrl)
 @Description			MOTOR_SPOTLOCK_Keep
 @Input				SPOTLOCK_CTRL_FALL or SPOTLOCK_CTRL_RISE
 @Return				void
**********************************************************************************************************/
void MOTOR_SPOTLOCK_Keep(MOTOR_SpotLockCtrlTypeDef ctrl)
{
	bool BeepON = false;
	
	/* 电机控制摇臂异常计数器 */
	static unsigned char SpotLockKeepErrCnt = 0;
	
	/* 电机SNS电流过大超时时间定时器 */
	Stm32_CalculagraphTypeDef motorSNSTimer;
	/* 间隔MS超时退出电机控制定时器 */
	Stm32_CalculagraphTypeDef motorErrTimer;
	
	/* 单次摇臂控制时间注入 */
	Stm32_Calculagraph_CountdownMS(&motorErrTimer, MOTOR_ERROR_DELAY_MS);
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 红外发射管使能开启 */
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	/* 判断电机控制摇臂是否异常, 异常警报 */
	if ((SpotLockKeepErrCnt >= MOTOR_CTRL_KEEP_ERR_CNT) && (INFRARED_TUBE_SPOTLOCK_STATE() != INFRARED_TUBE_RISE) && (INFRARED_TUBE_SPOTLOCK_STATE() != INFRARED_TUBE_FALL)) {
#if MOTOR_BUZZER_ERR
		BUZZERCtrlIO(ON);
#else
		BEEP_CtrlRepeat_Extend(1, 50, 15);
#endif
		goto error;
	}
	
	/* 判断电机控制摇臂是否为所要控制的状态, 异常警报 */
	if ((SpotLockKeepErrCnt >= MOTOR_CTRL_KEEP_ERR_CNT) && (MOTOR_SPOTLOCK_STATE() != ctrl)) {
#if MOTOR_BUZZER_ERR
		BUZZERCtrlIO(ON);
#else
		BEEP_CtrlRepeat_Extend(1, 50, 15);
#endif
		goto error;
	}
	
	/* 红外发射管使能开启 */
	INFRARED_TUBE_TRANSMIT_ENABLE();
	
	/* 控制锁摇臂升起 */
	if (ctrl == SPOTLOCK_CTRL_RISE) {
		
		/* 90° <= 摇臂 <= 180°状态 */
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
			/* 电机SNS电流过大超时时间注入 */
			Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			/* 电机反转 */
			MOTOR_FALL();
			/* 等待摇臂 <= 90° */
			while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_RISE) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErrCnt += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			/* 电机锁定 */
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
		/* 00° <= 摇臂 <= 05°状态 */
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
			/* 电机SNS电流过大超时时间注入 */
			Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			/* 电机正转 */
			MOTOR_RISE();
			/* 等待摇臂 >= 05° */
			while (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_FALL) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErrCnt += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			/* 电机锁定 */
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
		/* 05° <= 摇臂 <= 80°状态 */
		if (INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS) {
			/* 电机SNS电流过大超时时间注入 */
			Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			/* 电机正转 */
			MOTOR_RISE();
			/* 等待摇臂 >= 80° */
			while ((INFRARED_TUBE_RECEIVE_STATE() == INFRARED_TUBE_PROCESS)) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErrCnt += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			/* 电机锁定 */
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
#if MOTOR_BEEP_CTRL
		if (BeepON) BEEP_CtrlRepeat_Extend(3, 50, 15);
#else
		if (BeepON) Delay_MS(100);
#endif
	}
	
	/* 控制锁摇臂降下 */
	if (ctrl == SPOTLOCK_CTRL_FALL) {
		
		/* 摇臂 != 00°状态 */
		if (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
			/* 电机SNS电流过大超时时间注入 */
			Stm32_Calculagraph_CountdownMS(&motorSNSTimer, MOTOR_SNS_THRESHOLD_DELAY_MS);
			/* 电机反转 */
			MOTOR_FALL();
			/* 等待摇臂 == 00° */
			while (INFRARED_TUBE_RECEIVE_STATE() != INFRARED_TUBE_FALL) {
				if (Stm32_Calculagraph_IsExpiredMS(&motorErrTimer) == true) {
					SpotLockKeepErrCnt += MOTOR_CTRL_KEEP_ERR_CNT;
					goto error;
				}
			#if MOTOR_CTRL_KEEP_MODE == MOTOR_CTRL_KEEP_MODE2
				if ((Stm32_Calculagraph_IsExpiredMS(&motorSNSTimer) == true) && (MOTOR_SNS_Read(MOTOR_SNS_READ_VOLTAGE_DELAY_MS) > MOTOR_SNS_THRESHOLD_VOLTAGE)) goto error;
			#endif
			}
			/* 电机锁定 */
			MOTOR_LOCK();
			
			BeepON = true;
		}
		
#if MOTOR_BEEP_CTRL
		if (BeepON) BEEP_CtrlRepeat_Extend(1, 50, 25);
#else
		if (BeepON) Delay_MS(100);
#endif
	}
	
	SpotLockKeepErrCnt = 0;
	
#if MOTOR_BUZZER_ERR
	BUZZERCtrlIO(OFF);
#endif
	
error:
	if (SpotLockKeepErrCnt < 100) SpotLockKeepErrCnt++;
	
	/* 红外发射管失能关闭 */
	INFRARED_TUBE_TRANSMIT_DISABLE();
	
	/* 喂狗 */
	IWDG_Feed();
	
	/* 电机释放 */
	MOTOR_OPEN();
}
#endif

/********************************************** END OF FLEE **********************************************/
