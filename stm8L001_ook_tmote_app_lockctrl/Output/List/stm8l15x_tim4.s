///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:13:01
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim4.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW7981.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim4.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_tim4.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3

        PUBLIC TIM4_ARRPreloadConfig
        PUBLIC TIM4_ClearFlag
        PUBLIC TIM4_ClearITPendingBit
        PUBLIC TIM4_Cmd
        PUBLIC TIM4_DMACmd
        PUBLIC TIM4_DeInit
        PUBLIC TIM4_GenerateEvent
        PUBLIC TIM4_GetCounter
        PUBLIC TIM4_GetFlagStatus
        PUBLIC TIM4_GetITStatus
        PUBLIC TIM4_GetPrescaler
        PUBLIC TIM4_ITConfig
        PUBLIC TIM4_InternalClockConfig
        PUBLIC TIM4_PrescalerConfig
        PUBLIC TIM4_SelectInputTrigger
        PUBLIC TIM4_SelectMasterSlaveMode
        PUBLIC TIM4_SelectOnePulseMode
        PUBLIC TIM4_SelectOutputTrigger
        PUBLIC TIM4_SelectSlaveMode
        PUBLIC TIM4_SetAutoreload
        PUBLIC TIM4_SetCounter
        PUBLIC TIM4_TimeBaseInit
        PUBLIC TIM4_UpdateDisableConfig
        PUBLIC TIM4_UpdateRequestConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_DeInit:
        CLR       L:0x52e0
        CLR       L:0x52e1
        CLR       L:0x52e2
        CLR       L:0x52e4
        CLR       L:0x52e7
        CLR       L:0x52e8
        MOV       L:0x52e9, #0xff
        CLR       L:0x52e5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_TimeBaseInit:
        LD        S:?b1, A
        LD        A, S:?b0
        LD        L:0x52e9, A
        LD        A, S:?b1
        LD        L:0x52e8, A
        MOV       L:0x52e6, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_PrescalerConfig:
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x52e8, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM4_PrescalerConfig_0
        BSET      L:0x52e6, #0x0
        JRA       L:??TIM4_PrescalerConfig_1
??TIM4_PrescalerConfig_0:
        BRES      L:0x52e6, #0x0
??TIM4_PrescalerConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SetCounter:
        LD        L:0x52e7, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SetAutoreload:
        LD        L:0x52e9, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_GetCounter:
        CLR       A
        MOV       S:?b0, L:0x52e7
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_GetPrescaler:
        LD        A, L:0x52e8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_UpdateDisableConfig:
        TNZ       A
        JREQ      L:??TIM4_UpdateDisableConfig_0
        BSET      L:0x52e0, #0x1
        JRA       L:??TIM4_UpdateDisableConfig_1
??TIM4_UpdateDisableConfig_0:
        BRES      L:0x52e0, #0x1
??TIM4_UpdateDisableConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_UpdateRequestConfig:
        CP        A, #0x1
        JRNE      L:??TIM4_UpdateRequestConfig_0
        BSET      L:0x52e0, #0x2
        JRA       L:??TIM4_UpdateRequestConfig_1
??TIM4_UpdateRequestConfig_0:
        BRES      L:0x52e0, #0x2
??TIM4_UpdateRequestConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_ARRPreloadConfig:
        TNZ       A
        JREQ      L:??TIM4_ARRPreloadConfig_0
        BSET      L:0x52e0, #0x7
        JRA       L:??TIM4_ARRPreloadConfig_1
??TIM4_ARRPreloadConfig_0:
        BRES      L:0x52e0, #0x7
??TIM4_ARRPreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SelectOnePulseMode:
        CP        A, #0x1
        JRNE      L:??TIM4_SelectOnePulseMode_0
        BSET      L:0x52e0, #0x3
        JRA       L:??TIM4_SelectOnePulseMode_1
??TIM4_SelectOnePulseMode_0:
        BRES      L:0x52e0, #0x3
??TIM4_SelectOnePulseMode_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_Cmd:
        TNZ       A
        JREQ      L:??TIM4_Cmd_0
        BSET      L:0x52e0, #0x0
        JRA       L:??TIM4_Cmd_1
??TIM4_Cmd_0:
        BRES      L:0x52e0, #0x0
??TIM4_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM4_ITConfig_0
        LD        A, L:0x52e4
        OR        A, S:?b1
        LD        L:0x52e4, A
        JRA       L:??TIM4_ITConfig_1
??TIM4_ITConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x52e4
        LD        L:0x52e4, A
??TIM4_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_GenerateEvent:
        LD        S:?b0, A
        LD        A, L:0x52e6
        OR        A, S:?b0
        LD        L:0x52e6, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, L:0x52e5
        AND       A, S:?b1
        CP        A, #0x0
        JREQ      L:??TIM4_GetFlagStatus_0
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??TIM4_GetFlagStatus_1
??TIM4_GetFlagStatus_0:
        CLR       S:?b0
??TIM4_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_ClearFlag:
        LD        S:?b0, A
        LD        A, S:?b0
        CPL       A
        LD        L:0x52e5, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, L:0x52e5
        AND       A, S:?b3
        LD        S:?b1, A
        LD        A, L:0x52e4
        AND       A, S:?b3
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??TIM4_GetITStatus_0
        TNZ       S:?b0
        JREQ      L:??TIM4_GetITStatus_0
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??TIM4_GetITStatus_1
??TIM4_GetITStatus_0:
        CLR       S:?b2
??TIM4_GetITStatus_1:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_ClearITPendingBit:
        LD        S:?b0, A
        LD        A, S:?b0
        CPL       A
        LD        L:0x52e5, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM4_DMACmd_0
        LD        A, L:0x52e3
        OR        A, S:?b1
        LD        L:0x52e3, A
        JRA       L:??TIM4_DMACmd_1
??TIM4_DMACmd_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x52e3
        LD        L:0x52e3, A
??TIM4_DMACmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_InternalClockConfig:
        LD        A, L:0x52e2
        AND       A, #0xf8
        LD        L:0x52e2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SelectInputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x52e2
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x52e2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SelectOutputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x52e1
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x52e1, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SelectSlaveMode:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x52e2
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf8
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x52e2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM4_SelectMasterSlaveMode:
        TNZ       A
        JREQ      L:??TIM4_SelectMasterSlaveMode_0
        BSET      L:0x52e2, #0x7
        JRA       L:??TIM4_SelectMasterSlaveMode_1
??TIM4_SelectMasterSlaveMode_0:
        BRES      L:0x52e2, #0x7
??TIM4_SelectMasterSlaveMode_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 417 bytes in section .near_func.text
// 
// 417 bytes of CODE memory
//
//Errors: none
//Warnings: none
