///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  13:23:53
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Hardware\TIMER\hal_timer.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW4601.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Hardware\TIMER\hal_timer.c
//        -e -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_cross_call --debug --code_model small --data_model medium -o
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\Obj
//        --dlib_config "F:\IAR Systems\Embedded Workbench
//        8.3\stm8\LIB\dlstm8smn.h" -D STM8L05X_LD_VL -lcN
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List
//        -lb
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Core\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\inc\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\User\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Delay\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Sys\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Usart\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Hardware\TIMER\
//        -I
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Hardware\OOK\
//        --vregs 16)
//    Locale       =  Chinese (Simplified)_CHN.936
//    List file    =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\hal_timer.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b8
        EXTERN ?b9
        EXTERN ?epilogue_w4
        EXTERN ?push_w4
        EXTERN CLK_PeripheralClockConfig
        EXTERN TIM4_ClearFlag
        EXTERN TIM4_Cmd
        EXTERN TIM4_DeInit
        EXTERN TIM4_ITConfig
        EXTERN TIM4_TimeBaseInit

        PUBLIC Stm8_TIM4_Init
        PUBLIC Stm8_TIM4_InterruptHandler


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Stm8_TIM4_Init:
        CALL      L:?push_w4
        LD        S:?b8, A
        MOV       S:?b9, S:?b0
        MOV       S:?b0, #0x1
        LD        A, #0x2
        CALL      L:CLK_PeripheralClockConfig
        CALL      L:TIM4_DeInit
        MOV       S:?b0, S:?b9
        DEC       S:?b0
        LD        A, S:?b8
        CALL      L:TIM4_TimeBaseInit
        LD        A, #0x1
        CALL      L:TIM4_ClearFlag
        MOV       S:?b0, #0x1
        LD        A, #0x1
        CALL      L:TIM4_ITConfig
        RIM
        LD        A, #0x1
        CALL      L:TIM4_Cmd
        JP        L:?epilogue_w4

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Stm8_TIM4_InterruptHandler:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 54 bytes in section .near_func.text
// 
// 54 bytes of CODE memory
//
//Errors: none
//Warnings: none
