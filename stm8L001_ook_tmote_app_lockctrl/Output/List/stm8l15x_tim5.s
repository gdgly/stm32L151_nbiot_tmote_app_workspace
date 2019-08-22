///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  13:09:16
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim5.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW8B5A.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim5.c
//        -e -Ol --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_cross_call --debug --code_model small --data_model medium -o
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\Obj
//        --dlib_config "F:\IAR Systems\Embedded Workbench
//        8.3\stm8\LIB\dlstm8smf.h" -D STM8L05X_LD_VL -lcN
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
//        --vregs 16)
//    Locale       =  Chinese (Simplified)_CHN.936
//    List file    =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_tim5.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?b7
        EXTERN ?b8
        EXTERN ?b9
        EXTERN ?epilogue_w4
        EXTERN ?push_w4
        EXTERN ?w0

        PUBLIC TIM5_ARRPreloadConfig
        PUBLIC TIM5_BKRConfig
        PUBLIC TIM5_CCxCmd
        PUBLIC TIM5_ClearFlag
        PUBLIC TIM5_ClearITPendingBit
        PUBLIC TIM5_Cmd
        PUBLIC TIM5_CounterModeConfig
        PUBLIC TIM5_CtrlPWMOutputs
        PUBLIC TIM5_DMACmd
        PUBLIC TIM5_DeInit
        PUBLIC TIM5_ETRClockMode1Config
        PUBLIC TIM5_ETRClockMode2Config
        PUBLIC TIM5_ETRConfig
        PUBLIC TIM5_EncoderInterfaceConfig
        PUBLIC TIM5_ForcedOC1Config
        PUBLIC TIM5_ForcedOC2Config
        PUBLIC TIM5_GenerateEvent
        PUBLIC TIM5_GetCapture1
        PUBLIC TIM5_GetCapture2
        PUBLIC TIM5_GetCounter
        PUBLIC TIM5_GetFlagStatus
        PUBLIC TIM5_GetITStatus
        PUBLIC TIM5_GetPrescaler
        PUBLIC TIM5_ICInit
        PUBLIC TIM5_ITConfig
        PUBLIC TIM5_InternalClockConfig
        PUBLIC TIM5_OC1FastConfig
        PUBLIC TIM5_OC1Init
        PUBLIC TIM5_OC1PolarityConfig
        PUBLIC TIM5_OC1PreloadConfig
        PUBLIC TIM5_OC2FastConfig
        PUBLIC TIM5_OC2Init
        PUBLIC TIM5_OC2PolarityConfig
        PUBLIC TIM5_OC2PreloadConfig
        PUBLIC TIM5_PWMIConfig
        PUBLIC TIM5_PrescalerConfig
        PUBLIC TIM5_SelectCCDMA
        PUBLIC TIM5_SelectHallSensor
        PUBLIC TIM5_SelectInputTrigger
        PUBLIC TIM5_SelectMasterSlaveMode
        PUBLIC TIM5_SelectOCxM
        PUBLIC TIM5_SelectOnePulseMode
        PUBLIC TIM5_SelectOutputTrigger
        PUBLIC TIM5_SelectSlaveMode
        PUBLIC TIM5_SetAutoreload
        PUBLIC TIM5_SetCompare1
        PUBLIC TIM5_SetCompare2
        PUBLIC TIM5_SetCounter
        PUBLIC TIM5_SetIC1Prescaler
        PUBLIC TIM5_SetIC2Prescaler
        PUBLIC TIM5_TIxExternalClockConfig
        PUBLIC TIM5_TimeBaseInit
        PUBLIC TIM5_UpdateDisableConfig
        PUBLIC TIM5_UpdateRequestConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_DeInit:
        CLR       L:0x5300
        CLR       L:0x5301
        CLR       L:0x5302
        CLR       L:0x5303
        CLR       L:0x5305
        CLR       L:0x5307
        CLR       L:0x530b
        MOV       L:0x5309, #0x1
        MOV       L:0x530a, #0x1
        CLR       L:0x530b
        CLR       L:0x5309
        CLR       L:0x530a
        CLR       L:0x530c
        CLR       L:0x530d
        CLR       L:0x530e
        MOV       L:0x530f, #0xff
        MOV       L:0x5310, #0xff
        CLR       L:0x5311
        CLR       L:0x5312
        CLR       L:0x5313
        CLR       L:0x5314
        CLR       L:0x5316
        MOV       L:0x5308, #0x1
        CLR       L:0x5315
        CLR       L:0x5306
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_TimeBaseInit:
        LD        S:?b1, A
        LD        A, XH
        LD        L:0x530f, A
        LD        A, XL
        LD        L:0x5310, A
        LD        A, S:?b1
        LD        L:0x530e, A
        LD        A, L:0x5300
        AND       A, #0x8f
        LD        L:0x5300, A
        LD        A, L:0x5300
        OR        A, S:?b0
        LD        L:0x5300, A
        MOV       L:0x5308, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_PrescalerConfig:
        LD        L:0x530e, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM5_PrescalerConfig_0
        BSET      L:0x5308, #0x0
        RET
??TIM5_PrescalerConfig_0:
        BRES      L:0x5308, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_CounterModeConfig:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5300
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5300, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SetCounter:
        LD        A, XH
        LD        L:0x530c, A
        LD        A, XL
        LD        L:0x530d, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SetAutoreload:
        LD        A, XH
        LD        L:0x530f, A
        LD        A, XL
        LD        L:0x5310, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetCounter:
        CLRW      Y
        MOV       S:?b0, L:0x530c
        LD        A, L:0x530d
        CLRW      X
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w0, X
        RRWA      Y, A
        OR        A, S:?b1
        RRWA      Y, A
        OR        A, S:?b0
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetPrescaler:
        LD        A, L:0x530e
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_UpdateDisableConfig:
        TNZ       A
        JREQ      L:??TIM5_UpdateDisableConfig_0
        BSET      L:0x5300, #0x1
        RET
??TIM5_UpdateDisableConfig_0:
        BRES      L:0x5300, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_UpdateRequestConfig:
        CP        A, #0x1
        JRNE      L:??TIM5_UpdateRequestConfig_0
        BSET      L:0x5300, #0x2
        RET
??TIM5_UpdateRequestConfig_0:
        BRES      L:0x5300, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ARRPreloadConfig:
        TNZ       A
        JREQ      L:??TIM5_ARRPreloadConfig_0
        BSET      L:0x5300, #0x7
        RET
??TIM5_ARRPreloadConfig_0:
        BRES      L:0x5300, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectOnePulseMode:
        CP        A, #0x1
        JRNE      L:??TIM5_SelectOnePulseMode_0
        BSET      L:0x5300, #0x3
        RET
??TIM5_SelectOnePulseMode_0:
        BRES      L:0x5300, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_Cmd:
        TNZ       A
        JREQ      L:??TIM5_Cmd_0
        BSET      L:0x5300, #0x0
        RET
??TIM5_Cmd_0:
        BRES      L:0x5300, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC1Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x5309
        LD        S:?b4, A
        BRES      L:0x530b, #0x0
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x5309, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM5_OC1Init_0
        BSET      L:0x530b, #0x0
        JRA       L:??TIM5_OC1Init_1
??TIM5_OC1Init_0:
        BRES      L:0x530b, #0x0
??TIM5_OC1Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM5_OC1Init_2
        BSET      L:0x530b, #0x1
        JRA       L:??TIM5_OC1Init_3
??TIM5_OC1Init_2:
        BRES      L:0x530b, #0x1
??TIM5_OC1Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM5_OC1Init_4
        BSET      L:0x5316, #0x0
        JRA       L:??TIM5_OC1Init_5
??TIM5_OC1Init_4:
        BRES      L:0x5316, #0x0
??TIM5_OC1Init_5:
        LD        A, XH
        LD        L:0x5311, A
        LD        A, XL
        LD        L:0x5312, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC2Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x530a
        LD        S:?b4, A
        BRES      L:0x530b, #0x4
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x530a, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM5_OC2Init_0
        BSET      L:0x530b, #0x4
        JRA       L:??TIM5_OC2Init_1
??TIM5_OC2Init_0:
        BRES      L:0x530b, #0x4
??TIM5_OC2Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM5_OC2Init_2
        BSET      L:0x530b, #0x5
        JRA       L:??TIM5_OC2Init_3
??TIM5_OC2Init_2:
        BRES      L:0x530b, #0x5
??TIM5_OC2Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM5_OC2Init_4
        BSET      L:0x5316, #0x2
        JRA       L:??TIM5_OC2Init_5
??TIM5_OC2Init_4:
        BRES      L:0x5316, #0x2
??TIM5_OC2Init_5:
        LD        A, XH
        LD        L:0x5313, A
        LD        A, XL
        LD        L:0x5314, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_BKRConfig:
        LD        S:?b4, A
        LD        A, S:?b2
        OR        A, S:?b1
        PUSH      A
        LD        A, S:?b0
        OR        A, S:?b4
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        OR        A, S:?b3
        LD        L:0x5315, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_CtrlPWMOutputs:
        TNZ       A
        JREQ      L:??TIM5_CtrlPWMOutputs_0
        BSET      L:0x5315, #0x7
        RET
??TIM5_CtrlPWMOutputs_0:
        BRES      L:0x5315, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectOCxM:
        TNZ       A
        JRNE      L:??TIM5_SelectOCxM_0
        BRES      L:0x530b, #0x0
        LD        A, L:0x5309
        AND       A, #0x8f
        LD        L:0x5309, A
        LD        A, L:0x5309
        OR        A, S:?b0
        LD        L:0x5309, A
        RET
??TIM5_SelectOCxM_0:
        BRES      L:0x530b, #0x4
        LD        A, L:0x530a
        AND       A, #0x8f
        LD        L:0x530a, A
        LD        A, L:0x530a
        OR        A, S:?b0
        LD        L:0x530a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SetCompare1:
        LD        A, XH
        LD        L:0x5311, A
        LD        A, XL
        LD        L:0x5312, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SetCompare2:
        LD        A, XH
        LD        L:0x5313, A
        LD        A, XL
        LD        L:0x5314, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ForcedOC1Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5309
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5309, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ForcedOC2Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x530a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x530a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC1PreloadConfig:
        TNZ       A
        JREQ      L:??TIM5_OC1PreloadConfig_0
        BSET      L:0x5309, #0x3
        RET
??TIM5_OC1PreloadConfig_0:
        BRES      L:0x5309, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC2PreloadConfig:
        TNZ       A
        JREQ      L:??TIM5_OC2PreloadConfig_0
        BSET      L:0x530a, #0x3
        RET
??TIM5_OC2PreloadConfig_0:
        BRES      L:0x530a, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC1FastConfig:
        TNZ       A
        JREQ      L:??TIM5_OC1FastConfig_0
        BSET      L:0x5309, #0x2
        RET
??TIM5_OC1FastConfig_0:
        BRES      L:0x5309, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC2FastConfig:
        TNZ       A
        JREQ      L:??TIM5_OC2FastConfig_0
        BSET      L:0x530a, #0x2
        RET
??TIM5_OC2FastConfig_0:
        BRES      L:0x530a, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC1PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM5_OC1PolarityConfig_0
        BSET      L:0x530b, #0x1
        RET
??TIM5_OC1PolarityConfig_0:
        BRES      L:0x530b, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_OC2PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM5_OC2PolarityConfig_0
        BSET      L:0x530b, #0x5
        RET
??TIM5_OC2PolarityConfig_0:
        BRES      L:0x530b, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_CCxCmd:
        TNZ       A
        JRNE      L:??TIM5_CCxCmd_0
        TNZ       S:?b0
        JREQ      L:??TIM5_CCxCmd_1
        BSET      L:0x530b, #0x0
        RET
??TIM5_CCxCmd_1:
        BRES      L:0x530b, #0x0
        RET
??TIM5_CCxCmd_0:
        TNZ       S:?b0
        JREQ      L:??TIM5_CCxCmd_2
        BSET      L:0x530b, #0x4
        RET
??TIM5_CCxCmd_2:
        BRES      L:0x530b, #0x4
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM5_SetIC2Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x530a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x530a, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI2_Config:
        LD        S:?b2, A
        CLR       S:?b3
        LD        A, L:0x530a
        LD        S:?b3, A
        BRES      L:0x530b, #0x4
        LD        A, S:?b3
        AND       A, #0xc
        LD        S:?b3, A
        LD        A, S:?b1
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        OR        A, S:?b3
        LD        S:?b3, A
        LD        A, S:?b3
        LD        L:0x530a, A
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TI2_Config_0
        BSET      L:0x530b, #0x5
        JRA       L:??TI2_Config_1
??TI2_Config_0:
        BRES      L:0x530b, #0x5
??TI2_Config_1:
        BSET      L:0x530b, #0x4
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM5_SetIC1Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5309
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5309, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI1_Config:
        LD        S:?b2, A
        CLR       S:?b3
        LD        A, L:0x5309
        LD        S:?b3, A
        BRES      L:0x530b, #0x0
        LD        A, S:?b3
        AND       A, #0xc
        LD        S:?b3, A
        LD        A, S:?b1
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        OR        A, S:?b3
        LD        S:?b3, A
        LD        A, S:?b3
        LD        L:0x5309, A
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TI1_Config_0
        BSET      L:0x530b, #0x1
        JRA       L:??TI1_Config_1
??TI1_Config_0:
        BRES      L:0x530b, #0x1
??TI1_Config_1:
        BSET      L:0x530b, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ICInit:
        MOV       S:?b4, S:?b0
        MOV       S:?b0, S:?b1
        MOV       S:?b5, S:?b2
        MOV       S:?b1, S:?b3
        TNZ       A
        JRNE      L:??TIM5_ICInit_0
        LD        A, S:?b4
        CALL      L:TI1_Config
        LD        A, S:?b5
        JP        L:TIM5_SetIC1Prescaler
??TIM5_ICInit_0:
        LD        A, S:?b4
        CALL      L:TI2_Config
        LD        A, S:?b5
        JP        L:TIM5_SetIC2Prescaler

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_PWMIConfig:
        CALL      L:?push_w4
        LD        S:?b7, A
        MOV       S:?b6, S:?b0
        MOV       S:?b0, S:?b1
        MOV       S:?b8, S:?b2
        MOV       S:?b9, S:?b3
        CLR       S:?b4
        MOV       S:?b5, #0x1
        TNZ       S:?b6
        JRNE      L:??TIM5_PWMIConfig_0
        MOV       S:?b4, #0x1
        JRA       L:??TIM5_PWMIConfig_1
??TIM5_PWMIConfig_0:
        CLR       S:?b4
??TIM5_PWMIConfig_1:
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM5_PWMIConfig_2
        MOV       S:?b5, #0x2
        JRA       L:??TIM5_PWMIConfig_3
??TIM5_PWMIConfig_2:
        MOV       S:?b5, #0x1
??TIM5_PWMIConfig_3:
        TNZ       S:?b7
        JRNE      L:??TIM5_PWMIConfig_4
        MOV       S:?b1, S:?b9
        LD        A, S:?b6
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM5_SetIC1Prescaler
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b5
        LD        A, S:?b4
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM5_SetIC2Prescaler
        JP        L:?epilogue_w4
??TIM5_PWMIConfig_4:
        MOV       S:?b1, S:?b9
        LD        A, S:?b6
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM5_SetIC2Prescaler
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b5
        LD        A, S:?b4
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM5_SetIC1Prescaler
        JP        L:?epilogue_w4

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetCapture1:
        CLRW      Y
        MOV       S:?b0, L:0x5311
        LD        A, L:0x5312
        CLRW      X
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w0, X
        RRWA      Y, A
        OR        A, S:?b1
        RRWA      Y, A
        OR        A, S:?b0
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetCapture2:
        CLRW      Y
        MOV       S:?b0, L:0x5313
        LD        A, L:0x5314
        CLRW      X
        LD        XL, A
        LDW       Y, X
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w0, X
        RRWA      Y, A
        OR        A, S:?b1
        RRWA      Y, A
        OR        A, S:?b0
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM5_ITConfig_0
        LD        A, L:0x5305
        OR        A, S:?b1
        LD        L:0x5305, A
        RET
??TIM5_ITConfig_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, L:0x5305
        LD        L:0x5305, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GenerateEvent:
        LD        S:?b0, A
        LD        A, L:0x5308
        OR        A, S:?b0
        LD        L:0x5308, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetFlagStatus:
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, XL
        AND       A, L:0x5306
        LD        S:?b2, A
        LD        A, XH
        AND       A, L:0x5307
        LD        S:?b1, A
        LD        A, S:?b1
        OR        A, S:?b2
        CP        A, #0x0
        JREQ      L:??TIM5_GetFlagStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??TIM5_GetFlagStatus_1
??TIM5_GetFlagStatus_0:
        CLR       S:?b0
??TIM5_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ClearFlag:
        LD        A, XL
        CPL       A
        LD        L:0x5306, A
        LD        A, XH
        CPL       A
        LD        L:0x5307, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, L:0x5306
        AND       A, S:?b3
        LD        S:?b2, A
        LD        A, L:0x5305
        AND       A, S:?b3
        LD        S:?b1, A
        TNZ       S:?b2
        JREQ      L:??TIM5_GetITStatus_0
        TNZ       S:?b1
        JREQ      L:??TIM5_GetITStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??TIM5_GetITStatus_1
??TIM5_GetITStatus_0:
        CLR       S:?b0
??TIM5_GetITStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ClearITPendingBit:
        CPL       A
        LD        L:0x5306, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM5_DMACmd_0
        LD        A, L:0x5304
        OR        A, S:?b1
        LD        L:0x5304, A
        RET
??TIM5_DMACmd_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, L:0x5304
        LD        L:0x5304, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectCCDMA:
        TNZ       A
        JREQ      L:??TIM5_SelectCCDMA_0
        BSET      L:0x5301, #0x3
        RET
??TIM5_SelectCCDMA_0:
        BRES      L:0x5301, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_InternalClockConfig:
        LD        A, L:0x5302
        AND       A, #0xf8
        LD        L:0x5302, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_TIxExternalClockConfig:
        LD        S:?b4, A
        MOV       S:?b2, S:?b0
        LD        A, S:?b4
        CP        A, #0x60
        JRNE      L:??TIM5_TIxExternalClockConfig_0
        MOV       S:?b0, #0x1
        LD        A, S:?b2
        CALL      L:TI2_Config
        JRA       L:??TIM5_TIxExternalClockConfig_1
??TIM5_TIxExternalClockConfig_0:
        MOV       S:?b0, #0x1
        LD        A, S:?b2
        CALL      L:TI1_Config
??TIM5_TIxExternalClockConfig_1:
        LD        A, S:?b4
        CALL      L:TIM5_SelectInputTrigger
        LD        A, L:0x5302
        OR        A, #0x7
        LD        L:0x5302, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ETRClockMode1Config:
        CALL      L:TIM5_ETRConfig
        LD        A, L:0x5302
        AND       A, #0xf8
        LD        L:0x5302, A
        LD        A, L:0x5302
        OR        A, #0x7
        LD        L:0x5302, A
        LD        A, L:0x5302
        AND       A, #0x8f
        LD        L:0x5302, A
        LD        A, L:0x5302
        OR        A, #0x70
        LD        L:0x5302, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ETRClockMode2Config:
        CALL      L:TIM5_ETRConfig
        BSET      L:0x5303, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectInputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5302
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5302, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectOutputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5301
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5301, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectSlaveMode:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5302
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf8
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5302, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectMasterSlaveMode:
        TNZ       A
        JREQ      L:??TIM5_SelectMasterSlaveMode_0
        BSET      L:0x5302, #0x7
        RET
??TIM5_SelectMasterSlaveMode_0:
        BRES      L:0x5302, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_ETRConfig:
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
        OR        A, S:?b1
        OR        A, L:0x5303
        LD        L:0x5303, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_EncoderInterfaceConfig:
        LD        S:?b4, A
        CLR       S:?b5
        CLR       S:?b2
        CLR       S:?b3
        LD        A, L:0x5302
        LD        S:?b5, A
        LD        A, L:0x5309
        LD        S:?b2, A
        LD        A, L:0x530a
        LD        S:?b3, A
        LD        A, S:?b5
        AND       A, #0xf0
        LD        S:?b5, A
        LD        A, S:?b4
        OR        A, S:?b5
        LD        S:?b5, A
        LD        A, S:?b2
        AND       A, #0xfc
        LD        S:?b2, A
        LD        A, S:?b3
        AND       A, #0xfc
        LD        S:?b3, A
        LD        A, S:?b2
        OR        A, #0x1
        LD        S:?b2, A
        LD        A, S:?b3
        OR        A, #0x1
        LD        S:?b3, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM5_EncoderInterfaceConfig_0
        BSET      L:0x530b, #0x1
        JRA       L:??TIM5_EncoderInterfaceConfig_1
??TIM5_EncoderInterfaceConfig_0:
        BRES      L:0x530b, #0x1
??TIM5_EncoderInterfaceConfig_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM5_EncoderInterfaceConfig_2
        BSET      L:0x530b, #0x5
        JRA       L:??TIM5_EncoderInterfaceConfig_3
??TIM5_EncoderInterfaceConfig_2:
        BRES      L:0x530b, #0x5
??TIM5_EncoderInterfaceConfig_3:
        LD        A, S:?b5
        LD        L:0x5302, A
        LD        A, S:?b2
        LD        L:0x5309, A
        LD        A, S:?b3
        LD        L:0x530a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM5_SelectHallSensor:
        TNZ       A
        JREQ      L:??TIM5_SelectHallSensor_0
        BSET      L:0x5301, #0x7
        RET
??TIM5_SelectHallSensor_0:
        BRES      L:0x5301, #0x7
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 1 628 bytes in section .near_func.text
// 
// 1 628 bytes of CODE memory
//
//Errors: none
//Warnings: none
