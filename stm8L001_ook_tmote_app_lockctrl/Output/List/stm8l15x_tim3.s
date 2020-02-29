///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:26
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim3.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWD292.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim3.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_tim3.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b10
        EXTERN ?b11
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?b7
        EXTERN ?b8
        EXTERN ?b9
        EXTERN ?epilogue_l2
        EXTERN ?epilogue_w4
        EXTERN ?push_l2
        EXTERN ?push_w4
        EXTERN ?w1

        PUBLIC TIM3_ARRPreloadConfig
        PUBLIC TIM3_BKRConfig
        PUBLIC TIM3_CCxCmd
        PUBLIC TIM3_ClearFlag
        PUBLIC TIM3_ClearITPendingBit
        PUBLIC TIM3_Cmd
        PUBLIC TIM3_CounterModeConfig
        PUBLIC TIM3_CtrlPWMOutputs
        PUBLIC TIM3_DMACmd
        PUBLIC TIM3_DeInit
        PUBLIC TIM3_ETRClockMode1Config
        PUBLIC TIM3_ETRClockMode2Config
        PUBLIC TIM3_ETRConfig
        PUBLIC TIM3_EncoderInterfaceConfig
        PUBLIC TIM3_ForcedOC1Config
        PUBLIC TIM3_ForcedOC2Config
        PUBLIC TIM3_GenerateEvent
        PUBLIC TIM3_GetCapture1
        PUBLIC TIM3_GetCapture2
        PUBLIC TIM3_GetCounter
        PUBLIC TIM3_GetFlagStatus
        PUBLIC TIM3_GetITStatus
        PUBLIC TIM3_GetPrescaler
        PUBLIC TIM3_ICInit
        PUBLIC TIM3_ITConfig
        PUBLIC TIM3_InternalClockConfig
        PUBLIC TIM3_OC1FastConfig
        PUBLIC TIM3_OC1Init
        PUBLIC TIM3_OC1PolarityConfig
        PUBLIC TIM3_OC1PreloadConfig
        PUBLIC TIM3_OC2FastConfig
        PUBLIC TIM3_OC2Init
        PUBLIC TIM3_OC2PolarityConfig
        PUBLIC TIM3_OC2PreloadConfig
        PUBLIC TIM3_PWMIConfig
        PUBLIC TIM3_PrescalerConfig
        PUBLIC TIM3_SelectCCDMA
        PUBLIC TIM3_SelectHallSensor
        PUBLIC TIM3_SelectInputTrigger
        PUBLIC TIM3_SelectMasterSlaveMode
        PUBLIC TIM3_SelectOCxM
        PUBLIC TIM3_SelectOnePulseMode
        PUBLIC TIM3_SelectOutputTrigger
        PUBLIC TIM3_SelectSlaveMode
        PUBLIC TIM3_SetAutoreload
        PUBLIC TIM3_SetCompare1
        PUBLIC TIM3_SetCompare2
        PUBLIC TIM3_SetCounter
        PUBLIC TIM3_SetIC1Prescaler
        PUBLIC TIM3_SetIC2Prescaler
        PUBLIC TIM3_TIxExternalClockConfig
        PUBLIC TIM3_TimeBaseInit
        PUBLIC TIM3_UpdateDisableConfig
        PUBLIC TIM3_UpdateRequestConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_DeInit:
        CLR       L:0x5280
        CLR       L:0x5281
        CLR       L:0x5282
        CLR       L:0x5283
        CLR       L:0x5285
        CLR       L:0x5287
        CLR       L:0x528b
        MOV       L:0x5289, #0x1
        MOV       L:0x528a, #0x1
        CLR       L:0x528b
        CLR       L:0x5289
        CLR       L:0x528a
        CLR       L:0x528c
        CLR       L:0x528d
        CLR       L:0x528e
        MOV       L:0x528f, #0xff
        MOV       L:0x5290, #0xff
        CLR       L:0x5291
        CLR       L:0x5292
        CLR       L:0x5293
        CLR       L:0x5294
        CLR       L:0x5296
        MOV       L:0x5288, #0x1
        CLR       L:0x5295
        CLR       L:0x5286
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_TimeBaseInit:
        LD        S:?b1, A
        LD        A, XH
        LD        L:0x528f, A
        LD        A, XL
        LD        L:0x5290, A
        LD        A, S:?b1
        LD        L:0x528e, A
        LD        A, L:0x5280
        AND       A, #0x8f
        LD        L:0x5280, A
        LD        A, L:0x5280
        OR        A, S:?b0
        LD        L:0x5280, A
        MOV       L:0x5288, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_PrescalerConfig:
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x528e, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM3_PrescalerConfig_0
        BSET      L:0x5288, #0x0
        JRA       L:??TIM3_PrescalerConfig_1
??TIM3_PrescalerConfig_0:
        BRES      L:0x5288, #0x0
??TIM3_PrescalerConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_CounterModeConfig:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5280
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5280, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetCounter:
        LD        A, XH
        LD        L:0x528c, A
        LD        A, XL
        LD        L:0x528d, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetAutoreload:
        LD        A, XH
        LD        L:0x528f, A
        LD        A, XL
        LD        L:0x5290, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetCounter:
        CLRW      Y
        LD        A, L:0x528c
        LD        S:?b0, A
        LD        A, L:0x528d
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w1, X
        RRWA      Y, A
        OR        A, S:?b3
        RRWA      Y, A
        OR        A, S:?b2
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetPrescaler:
        LD        A, L:0x528e
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_UpdateDisableConfig:
        TNZ       A
        JREQ      L:??TIM3_UpdateDisableConfig_0
        BSET      L:0x5280, #0x1
        JRA       L:??TIM3_UpdateDisableConfig_1
??TIM3_UpdateDisableConfig_0:
        BRES      L:0x5280, #0x1
??TIM3_UpdateDisableConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_UpdateRequestConfig:
        CP        A, #0x1
        JRNE      L:??TIM3_UpdateRequestConfig_0
        BSET      L:0x5280, #0x2
        JRA       L:??TIM3_UpdateRequestConfig_1
??TIM3_UpdateRequestConfig_0:
        BRES      L:0x5280, #0x2
??TIM3_UpdateRequestConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ARRPreloadConfig:
        TNZ       A
        JREQ      L:??TIM3_ARRPreloadConfig_0
        BSET      L:0x5280, #0x7
        JRA       L:??TIM3_ARRPreloadConfig_1
??TIM3_ARRPreloadConfig_0:
        BRES      L:0x5280, #0x7
??TIM3_ARRPreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectOnePulseMode:
        CP        A, #0x1
        JRNE      L:??TIM3_SelectOnePulseMode_0
        BSET      L:0x5280, #0x3
        JRA       L:??TIM3_SelectOnePulseMode_1
??TIM3_SelectOnePulseMode_0:
        BRES      L:0x5280, #0x3
??TIM3_SelectOnePulseMode_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_Cmd:
        TNZ       A
        JREQ      L:??TIM3_Cmd_0
        BSET      L:0x5280, #0x0
        JRA       L:??TIM3_Cmd_1
??TIM3_Cmd_0:
        BRES      L:0x5280, #0x0
??TIM3_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC1Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x5289
        LD        S:?b4, A
        BRES      L:0x528b, #0x0
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x5289, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM3_OC1Init_0
        BSET      L:0x528b, #0x0
        JRA       L:??TIM3_OC1Init_1
??TIM3_OC1Init_0:
        BRES      L:0x528b, #0x0
??TIM3_OC1Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM3_OC1Init_2
        BSET      L:0x528b, #0x1
        JRA       L:??TIM3_OC1Init_3
??TIM3_OC1Init_2:
        BRES      L:0x528b, #0x1
??TIM3_OC1Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM3_OC1Init_4
        BSET      L:0x5296, #0x0
        JRA       L:??TIM3_OC1Init_5
??TIM3_OC1Init_4:
        BRES      L:0x5296, #0x0
??TIM3_OC1Init_5:
        LD        A, XH
        LD        L:0x5291, A
        LD        A, XL
        LD        L:0x5292, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC2Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x528a
        LD        S:?b4, A
        BRES      L:0x528b, #0x4
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x528a, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM3_OC2Init_0
        BSET      L:0x528b, #0x4
        JRA       L:??TIM3_OC2Init_1
??TIM3_OC2Init_0:
        BRES      L:0x528b, #0x4
??TIM3_OC2Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM3_OC2Init_2
        BSET      L:0x528b, #0x5
        JRA       L:??TIM3_OC2Init_3
??TIM3_OC2Init_2:
        BRES      L:0x528b, #0x5
??TIM3_OC2Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM3_OC2Init_4
        BSET      L:0x5296, #0x2
        JRA       L:??TIM3_OC2Init_5
??TIM3_OC2Init_4:
        BRES      L:0x5296, #0x2
??TIM3_OC2Init_5:
        LD        A, XH
        LD        L:0x5293, A
        LD        A, XL
        LD        L:0x5294, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_BKRConfig:
        LD        S:?b5, A
        LD        A, S:?b2
        OR        A, S:?b1
        PUSH      A
        LD        A, S:?b0
        OR        A, S:?b5
        LD        S:?b6, A
        POP       A
        OR        A, S:?b6
        OR        A, S:?b3
        LD        L:0x5295, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_CtrlPWMOutputs:
        TNZ       A
        JREQ      L:??TIM3_CtrlPWMOutputs_0
        BSET      L:0x5295, #0x7
        JRA       L:??TIM3_CtrlPWMOutputs_1
??TIM3_CtrlPWMOutputs_0:
        BRES      L:0x5295, #0x7
??TIM3_CtrlPWMOutputs_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectOCxM:
        LD        S:?b1, A
        TNZ       S:?b1
        JRNE      L:??TIM3_SelectOCxM_0
        BRES      L:0x528b, #0x0
        LD        A, L:0x5289
        AND       A, #0x8f
        LD        L:0x5289, A
        LD        A, L:0x5289
        OR        A, S:?b0
        LD        L:0x5289, A
        JRA       L:??TIM3_SelectOCxM_1
??TIM3_SelectOCxM_0:
        BRES      L:0x528b, #0x4
        LD        A, L:0x528a
        AND       A, #0x8f
        LD        L:0x528a, A
        LD        A, L:0x528a
        OR        A, S:?b0
        LD        L:0x528a, A
??TIM3_SelectOCxM_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetCompare1:
        LD        A, XH
        LD        L:0x5291, A
        LD        A, XL
        LD        L:0x5292, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetCompare2:
        LD        A, XH
        LD        L:0x5293, A
        LD        A, XL
        LD        L:0x5294, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ForcedOC1Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5289
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5289, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ForcedOC2Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x528a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x528a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC1PreloadConfig:
        TNZ       A
        JREQ      L:??TIM3_OC1PreloadConfig_0
        BSET      L:0x5289, #0x3
        JRA       L:??TIM3_OC1PreloadConfig_1
??TIM3_OC1PreloadConfig_0:
        BRES      L:0x5289, #0x3
??TIM3_OC1PreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC2PreloadConfig:
        TNZ       A
        JREQ      L:??TIM3_OC2PreloadConfig_0
        BSET      L:0x528a, #0x3
        JRA       L:??TIM3_OC2PreloadConfig_1
??TIM3_OC2PreloadConfig_0:
        BRES      L:0x528a, #0x3
??TIM3_OC2PreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC1FastConfig:
        TNZ       A
        JREQ      L:??TIM3_OC1FastConfig_0
        BSET      L:0x5289, #0x2
        JRA       L:??TIM3_OC1FastConfig_1
??TIM3_OC1FastConfig_0:
        BRES      L:0x5289, #0x2
??TIM3_OC1FastConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC2FastConfig:
        TNZ       A
        JREQ      L:??TIM3_OC2FastConfig_0
        BSET      L:0x528a, #0x2
        JRA       L:??TIM3_OC2FastConfig_1
??TIM3_OC2FastConfig_0:
        BRES      L:0x528a, #0x2
??TIM3_OC2FastConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC1PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM3_OC1PolarityConfig_0
        BSET      L:0x528b, #0x1
        JRA       L:??TIM3_OC1PolarityConfig_1
??TIM3_OC1PolarityConfig_0:
        BRES      L:0x528b, #0x1
??TIM3_OC1PolarityConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_OC2PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM3_OC2PolarityConfig_0
        BSET      L:0x528b, #0x5
        JRA       L:??TIM3_OC2PolarityConfig_1
??TIM3_OC2PolarityConfig_0:
        BRES      L:0x528b, #0x5
??TIM3_OC2PolarityConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_CCxCmd:
        TNZ       A
        JRNE      L:??TIM3_CCxCmd_0
        TNZ       S:?b0
        JREQ      L:??TIM3_CCxCmd_1
        BSET      L:0x528b, #0x0
        JRA       L:??TIM3_CCxCmd_2
??TIM3_CCxCmd_1:
        BRES      L:0x528b, #0x0
        JRA       L:??TIM3_CCxCmd_2
??TIM3_CCxCmd_0:
        TNZ       S:?b0
        JREQ      L:??TIM3_CCxCmd_3
        BSET      L:0x528b, #0x4
        JRA       L:??TIM3_CCxCmd_2
??TIM3_CCxCmd_3:
        BRES      L:0x528b, #0x4
??TIM3_CCxCmd_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ICInit:
        CALL      L:?push_w4
        LD        S:?b5, A
        MOV       S:?b6, S:?b0
        MOV       S:?b7, S:?b1
        MOV       S:?b8, S:?b2
        MOV       S:?b9, S:?b3
        TNZ       S:?b5
        JRNE      L:??TIM3_ICInit_0
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b7
        LD        A, S:?b6
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM3_SetIC1Prescaler
        JRA       L:??TIM3_ICInit_1
??TIM3_ICInit_0:
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b7
        LD        A, S:?b6
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM3_SetIC2Prescaler
??TIM3_ICInit_1:
        JP        L:?epilogue_w4

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_PWMIConfig:
        CALL      L:?push_l2
        LD        S:?b6, A
        MOV       S:?b7, S:?b0
        MOV       S:?b9, S:?b1
        MOV       S:?b10, S:?b2
        MOV       S:?b11, S:?b3
        CLR       S:?b5
        MOV       S:?b8, #0x1
        TNZ       S:?b7
        JRNE      L:??TIM3_PWMIConfig_0
        LD        A, #0x1
        LD        S:?b5, A
        JRA       L:??TIM3_PWMIConfig_1
??TIM3_PWMIConfig_0:
        CLR       S:?b5
??TIM3_PWMIConfig_1:
        LD        A, S:?b9
        CP        A, #0x1
        JRNE      L:??TIM3_PWMIConfig_2
        LD        A, #0x2
        LD        S:?b8, A
        JRA       L:??TIM3_PWMIConfig_3
??TIM3_PWMIConfig_2:
        LD        A, #0x1
        LD        S:?b8, A
??TIM3_PWMIConfig_3:
        TNZ       S:?b6
        JRNE      L:??TIM3_PWMIConfig_4
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b9
        LD        A, S:?b7
        CALL      L:TI1_Config
        LD        A, S:?b10
        CALL      L:TIM3_SetIC1Prescaler
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b8
        LD        A, S:?b5
        CALL      L:TI2_Config
        LD        A, S:?b10
        CALL      L:TIM3_SetIC2Prescaler
        JRA       L:??TIM3_PWMIConfig_5
??TIM3_PWMIConfig_4:
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b9
        LD        A, S:?b7
        CALL      L:TI2_Config
        LD        A, S:?b10
        CALL      L:TIM3_SetIC2Prescaler
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b8
        LD        A, S:?b5
        CALL      L:TI1_Config
        LD        A, S:?b10
        CALL      L:TIM3_SetIC1Prescaler
??TIM3_PWMIConfig_5:
        JP        L:?epilogue_l2

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetCapture1:
        CLRW      Y
        LD        A, L:0x5291
        LD        S:?b0, A
        LD        A, L:0x5292
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w1, X
        RRWA      Y, A
        OR        A, S:?b3
        RRWA      Y, A
        OR        A, S:?b2
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetCapture2:
        CLRW      Y
        LD        A, L:0x5293
        LD        S:?b0, A
        LD        A, L:0x5294
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w1, X
        RRWA      Y, A
        OR        A, S:?b3
        RRWA      Y, A
        OR        A, S:?b2
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetIC1Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5289
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5289, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SetIC2Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x528a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x528a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM3_ITConfig_0
        LD        A, L:0x5285
        OR        A, S:?b1
        LD        L:0x5285, A
        JRA       L:??TIM3_ITConfig_1
??TIM3_ITConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x5285
        LD        L:0x5285, A
??TIM3_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GenerateEvent:
        LD        S:?b0, A
        LD        A, L:0x5288
        OR        A, S:?b0
        LD        L:0x5288, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetFlagStatus:
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, XL
        AND       A, L:0x5286
        LD        S:?b2, A
        LD        A, XH
        AND       A, L:0x5287
        LD        S:?b1, A
        LD        A, S:?b1
        OR        A, S:?b2
        CP        A, #0x0
        JREQ      L:??TIM3_GetFlagStatus_0
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??TIM3_GetFlagStatus_1
??TIM3_GetFlagStatus_0:
        CLR       S:?b0
??TIM3_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ClearFlag:
        LD        A, XL
        CPL       A
        LD        L:0x5286, A
        LD        A, XH
        CPL       A
        LD        L:0x5287, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, L:0x5286
        AND       A, S:?b3
        LD        S:?b1, A
        LD        A, L:0x5285
        AND       A, S:?b3
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??TIM3_GetITStatus_0
        TNZ       S:?b0
        JREQ      L:??TIM3_GetITStatus_0
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??TIM3_GetITStatus_1
??TIM3_GetITStatus_0:
        CLR       S:?b2
??TIM3_GetITStatus_1:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ClearITPendingBit:
        LD        S:?b0, A
        LD        A, S:?b0
        CPL       A
        LD        L:0x5286, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM3_DMACmd_0
        LD        A, L:0x5284
        OR        A, S:?b1
        LD        L:0x5284, A
        JRA       L:??TIM3_DMACmd_1
??TIM3_DMACmd_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x5284
        LD        L:0x5284, A
??TIM3_DMACmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectCCDMA:
        TNZ       A
        JREQ      L:??TIM3_SelectCCDMA_0
        BSET      L:0x5281, #0x3
        JRA       L:??TIM3_SelectCCDMA_1
??TIM3_SelectCCDMA_0:
        BRES      L:0x5281, #0x3
??TIM3_SelectCCDMA_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_InternalClockConfig:
        LD        A, L:0x5282
        AND       A, #0xf8
        LD        L:0x5282, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_TIxExternalClockConfig:
        LD        S:?b5, A
        MOV       S:?b6, S:?b0
        MOV       S:?b7, S:?b1
        LD        A, S:?b5
        CP        A, #0x60
        JRNE      L:??TIM3_TIxExternalClockConfig_0
        MOV       S:?b1, S:?b7
        MOV       S:?b0, #0x1
        LD        A, S:?b6
        CALL      L:TI2_Config
        JRA       L:??TIM3_TIxExternalClockConfig_1
??TIM3_TIxExternalClockConfig_0:
        MOV       S:?b1, S:?b7
        MOV       S:?b0, #0x1
        LD        A, S:?b6
        CALL      L:TI1_Config
??TIM3_TIxExternalClockConfig_1:
        LD        A, S:?b5
        CALL      L:TIM3_SelectInputTrigger
        LD        A, L:0x5282
        OR        A, #0x7
        LD        L:0x5282, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ETRClockMode1Config:
        LD        S:?b3, A
        MOV       S:?b4, S:?b0
        MOV       S:?b5, S:?b1
        MOV       S:?b1, S:?b5
        MOV       S:?b0, S:?b4
        LD        A, S:?b3
        CALL      L:TIM3_ETRConfig
        LD        A, L:0x5282
        AND       A, #0xf8
        LD        L:0x5282, A
        LD        A, L:0x5282
        OR        A, #0x7
        LD        L:0x5282, A
        LD        A, L:0x5282
        AND       A, #0x8f
        LD        L:0x5282, A
        LD        A, L:0x5282
        OR        A, #0x70
        LD        L:0x5282, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ETRClockMode2Config:
        LD        S:?b3, A
        MOV       S:?b4, S:?b0
        MOV       S:?b5, S:?b1
        MOV       S:?b1, S:?b5
        MOV       S:?b0, S:?b4
        LD        A, S:?b3
        CALL      L:TIM3_ETRConfig
        BSET      L:0x5283, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectInputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5282
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5282, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectOutputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5281
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5281, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectSlaveMode:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5282
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf8
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5282, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectMasterSlaveMode:
        TNZ       A
        JREQ      L:??TIM3_SelectMasterSlaveMode_0
        BSET      L:0x5282, #0x7
        JRA       L:??TIM3_SelectMasterSlaveMode_1
??TIM3_SelectMasterSlaveMode_0:
        BRES      L:0x5282, #0x7
??TIM3_SelectMasterSlaveMode_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_ETRConfig:
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
        OR        A, S:?b1
        OR        A, L:0x5283
        LD        L:0x5283, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_EncoderInterfaceConfig:
        LD        S:?b4, A
        CLR       S:?b5
        CLR       S:?b3
        CLR       S:?b2
        LD        A, L:0x5282
        LD        S:?b5, A
        LD        A, L:0x5289
        LD        S:?b3, A
        LD        A, L:0x528a
        LD        S:?b2, A
        LD        A, S:?b5
        AND       A, #0xf0
        LD        S:?b5, A
        LD        A, S:?b4
        OR        A, S:?b5
        LD        S:?b5, A
        LD        A, S:?b3
        AND       A, #0xfc
        LD        S:?b3, A
        LD        A, S:?b2
        AND       A, #0xfc
        LD        S:?b2, A
        LD        A, S:?b3
        OR        A, #0x1
        LD        S:?b3, A
        LD        A, S:?b2
        OR        A, #0x1
        LD        S:?b2, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM3_EncoderInterfaceConfig_0
        BSET      L:0x528b, #0x1
        JRA       L:??TIM3_EncoderInterfaceConfig_1
??TIM3_EncoderInterfaceConfig_0:
        BRES      L:0x528b, #0x1
??TIM3_EncoderInterfaceConfig_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM3_EncoderInterfaceConfig_2
        BSET      L:0x528b, #0x5
        JRA       L:??TIM3_EncoderInterfaceConfig_3
??TIM3_EncoderInterfaceConfig_2:
        BRES      L:0x528b, #0x5
??TIM3_EncoderInterfaceConfig_3:
        LD        A, S:?b5
        LD        L:0x5282, A
        LD        A, S:?b3
        LD        L:0x5289, A
        LD        A, S:?b2
        LD        L:0x528a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM3_SelectHallSensor:
        TNZ       A
        JREQ      L:??TIM3_SelectHallSensor_0
        BSET      L:0x5281, #0x7
        JRA       L:??TIM3_SelectHallSensor_1
??TIM3_SelectHallSensor_0:
        BRES      L:0x5281, #0x7
??TIM3_SelectHallSensor_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TI1_Config:
        LD        S:?b2, A
        CLR       S:?b4
        MOV       S:?b3, S:?b2
        LD        A, L:0x5289
        LD        S:?b4, A
        BRES      L:0x528b, #0x0
        LD        A, S:?b4
        AND       A, #0xc
        LD        S:?b4, A
        LD        A, S:?b1
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x5289, A
        LD        A, S:?b3
        CP        A, #0x1
        JRNE      L:??TI1_Config_0
        BSET      L:0x528b, #0x1
        JRA       L:??TI1_Config_1
??TI1_Config_0:
        BRES      L:0x528b, #0x1
??TI1_Config_1:
        BSET      L:0x528b, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TI2_Config:
        LD        S:?b2, A
        CLR       S:?b4
        MOV       S:?b3, S:?b2
        LD        A, L:0x528a
        LD        S:?b4, A
        BRES      L:0x528b, #0x4
        LD        A, S:?b4
        AND       A, #0xc
        LD        S:?b4, A
        LD        A, S:?b1
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x528a, A
        LD        A, S:?b3
        CP        A, #0x1
        JRNE      L:??TI2_Config_0
        BSET      L:0x528b, #0x5
        JRA       L:??TI2_Config_1
??TI2_Config_0:
        BRES      L:0x528b, #0x5
??TI2_Config_1:
        BSET      L:0x528b, #0x4
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 1 746 bytes in section .near_func.text
// 
// 1 746 bytes of CODE memory
//
//Errors: none
//Warnings: none
