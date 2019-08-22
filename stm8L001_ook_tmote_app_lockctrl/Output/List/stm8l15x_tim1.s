///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  13:09:15
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim1.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW86B2.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim1.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_tim1.s
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
        EXTERN ?w0

        PUBLIC TIM1_ARRPreloadConfig
        PUBLIC TIM1_BDTRConfig
        PUBLIC TIM1_CCPreloadControl
        PUBLIC TIM1_CCxCmd
        PUBLIC TIM1_CCxNCmd
        PUBLIC TIM1_ClearFlag
        PUBLIC TIM1_ClearITPendingBit
        PUBLIC TIM1_ClearOC1Ref
        PUBLIC TIM1_ClearOC2Ref
        PUBLIC TIM1_ClearOC3Ref
        PUBLIC TIM1_ClearOC4Ref
        PUBLIC TIM1_Cmd
        PUBLIC TIM1_CounterModeConfig
        PUBLIC TIM1_CtrlPWMOutputs
        PUBLIC TIM1_DMACmd
        PUBLIC TIM1_DMAConfig
        PUBLIC TIM1_DeInit
        PUBLIC TIM1_ETRClockMode1Config
        PUBLIC TIM1_ETRClockMode2Config
        PUBLIC TIM1_ETRConfig
        PUBLIC TIM1_EncoderInterfaceConfig
        PUBLIC TIM1_ForcedOC1Config
        PUBLIC TIM1_ForcedOC2Config
        PUBLIC TIM1_ForcedOC3Config
        PUBLIC TIM1_GenerateEvent
        PUBLIC TIM1_GetCapture1
        PUBLIC TIM1_GetCapture2
        PUBLIC TIM1_GetCapture3
        PUBLIC TIM1_GetCapture4
        PUBLIC TIM1_GetCounter
        PUBLIC TIM1_GetFlagStatus
        PUBLIC TIM1_GetITStatus
        PUBLIC TIM1_GetPrescaler
        PUBLIC TIM1_ICInit
        PUBLIC TIM1_ITConfig
        PUBLIC TIM1_InternalClockConfig
        PUBLIC TIM1_OC1FastConfig
        PUBLIC TIM1_OC1Init
        PUBLIC TIM1_OC1NPolarityConfig
        PUBLIC TIM1_OC1PolarityConfig
        PUBLIC TIM1_OC1PreloadConfig
        PUBLIC TIM1_OC2FastConfig
        PUBLIC TIM1_OC2Init
        PUBLIC TIM1_OC2NPolarityConfig
        PUBLIC TIM1_OC2PolarityConfig
        PUBLIC TIM1_OC2PreloadConfig
        PUBLIC TIM1_OC3FastConfig
        PUBLIC TIM1_OC3Init
        PUBLIC TIM1_OC3NPolarityConfig
        PUBLIC TIM1_OC3PolarityConfig
        PUBLIC TIM1_OC3PreloadConfig
        PUBLIC TIM1_OC4PreloadConfig
        PUBLIC TIM1_PWMIConfig
        PUBLIC TIM1_PrescalerConfig
        PUBLIC TIM1_SelectCCDMA
        PUBLIC TIM1_SelectCOM
        PUBLIC TIM1_SelectHallSensor
        PUBLIC TIM1_SelectInputTrigger
        PUBLIC TIM1_SelectMasterSlaveMode
        PUBLIC TIM1_SelectOCREFClear
        PUBLIC TIM1_SelectOCxM
        PUBLIC TIM1_SelectOnePulseMode
        PUBLIC TIM1_SelectOutputTrigger
        PUBLIC TIM1_SelectSlaveMode
        PUBLIC TIM1_SetAutoreload
        PUBLIC TIM1_SetCompare1
        PUBLIC TIM1_SetCompare2
        PUBLIC TIM1_SetCompare3
        PUBLIC TIM1_SetCompare4
        PUBLIC TIM1_SetCounter
        PUBLIC TIM1_SetIC1Prescaler
        PUBLIC TIM1_SetIC2Prescaler
        PUBLIC TIM1_SetIC3Prescaler
        PUBLIC TIM1_SetIC4Prescaler
        PUBLIC TIM1_TIxExternalClockConfig
        PUBLIC TIM1_TimeBaseInit
        PUBLIC TIM1_UpdateDisableConfig
        PUBLIC TIM1_UpdateRequestConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_DeInit:
        CLR       L:0x52b0
        CLR       L:0x52b1
        CLR       L:0x52b2
        CLR       L:0x52b3
        CLR       L:0x52b5
        CLR       L:0x52bd
        CLR       L:0x52be
        MOV       L:0x52b9, #0x1
        MOV       L:0x52ba, #0x1
        MOV       L:0x52bb, #0x1
        MOV       L:0x52bc, #0x1
        CLR       L:0x52bd
        CLR       L:0x52be
        CLR       L:0x52b9
        CLR       L:0x52ba
        CLR       L:0x52bb
        CLR       L:0x52bc
        CLR       L:0x52bf
        CLR       L:0x52c0
        CLR       L:0x52c1
        CLR       L:0x52c2
        MOV       L:0x52c3, #0xff
        MOV       L:0x52c4, #0xff
        CLR       L:0x52c6
        CLR       L:0x52c7
        CLR       L:0x52c8
        CLR       L:0x52c9
        CLR       L:0x52ca
        CLR       L:0x52cb
        CLR       L:0x52cc
        CLR       L:0x52cd
        CLR       L:0x52d0
        MOV       L:0x52b8, #0x1
        CLR       L:0x52cf
        CLR       L:0x52ce
        CLR       L:0x52c5
        CLR       L:0x52b6
        CLR       L:0x52b7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_TimeBaseInit:
        LD        S:?b1, A
        LD        A, YH
        LD        L:0x52c3, A
        LD        A, YL
        LD        L:0x52c4, A
        LD        A, XH
        LD        L:0x52c1, A
        LD        A, XL
        LD        L:0x52c2, A
        LD        A, L:0x52b0
        AND       A, #0x8f
        OR        A, S:?b1
        LD        L:0x52b0, A
        LD        A, S:?b0
        LD        L:0x52c5, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_PrescalerConfig:
        LD        S:?b0, A
        LD        A, XH
        LD        L:0x52c1, A
        LD        A, XL
        LD        L:0x52c2, A
        LD        A, S:?b0
        LD        L:0x52b8, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_CounterModeConfig:
        LD        S:?b0, A
        LD        A, L:0x52b0
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52b0, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetCounter:
        LD        A, XH
        LD        L:0x52bf, A
        LD        A, XL
        LD        L:0x52c0, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetAutoreload:
        LD        A, XH
        LD        L:0x52c3, A
        LD        A, XL
        LD        L:0x52c4, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_GetCounter:
        CLRW      Y
        CLR       A
        CLR       S:?b0
        MOV       S:?b1, L:0x52bf
        MOV       S:?b0, S:?b1
        MOV       S:?b1, L:0x52c0
        LD        A, S:?b1
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
TIM1_GetPrescaler:
        CLRW      Y
        LD        A, L:0x52c1
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       Y, X
        LD        A, L:0x52c2
        CLR       S:?b0
        LD        S:?b1, A
        LDW       X, Y
        RRWA      X, A
        OR        A, S:?b1
        RRWA      X, A
        OR        A, S:?b0
        RRWA      X, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_UpdateDisableConfig:
        TNZ       A
        JREQ      L:??TIM1_UpdateDisableConfig_0
        BSET      L:0x52b0, #0x1
        RET
??TIM1_UpdateDisableConfig_0:
        BRES      L:0x52b0, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_UpdateRequestConfig:
        TNZ       A
        JREQ      L:??TIM1_UpdateRequestConfig_0
        BSET      L:0x52b0, #0x2
        RET
??TIM1_UpdateRequestConfig_0:
        BRES      L:0x52b0, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ARRPreloadConfig:
        TNZ       A
        JREQ      L:??TIM1_ARRPreloadConfig_0
        BSET      L:0x52b0, #0x7
        RET
??TIM1_ARRPreloadConfig_0:
        BRES      L:0x52b0, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectOnePulseMode:
        TNZ       A
        JREQ      L:??TIM1_SelectOnePulseMode_0
        BSET      L:0x52b0, #0x3
        RET
??TIM1_SelectOnePulseMode_0:
        BRES      L:0x52b0, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_Cmd:
        TNZ       A
        JREQ      L:??TIM1_Cmd_0
        BSET      L:0x52b0, #0x0
        RET
??TIM1_Cmd_0:
        BRES      L:0x52b0, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC1Init:
        LD        S:?b6, A
        LD        A, L:0x52bd
        AND       A, #0xf0
        LD        L:0x52bd, A
        LD        A, S:?b3
        AND       A, #0x8
        PUSH      A
        LD        A, S:?b2
        AND       A, #0x2
        LD        S:?b2, A
        POP       A
        OR        A, S:?b2
        PUSH      A
        LD        A, S:?b1
        AND       A, #0x4
        PUSH      A
        LD        A, S:?b0
        AND       A, #0x1
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        OR        A, L:0x52bd
        LD        L:0x52bd, A
        LD        A, L:0x52b9
        AND       A, #0x8f
        OR        A, S:?b6
        LD        L:0x52b9, A
        LD        A, L:0x52d0
        AND       A, #0xfc
        LD        L:0x52d0, A
        LD        A, S:?b5
        AND       A, #0x2
        PUSH      A
        LD        A, S:?b4
        AND       A, #0x1
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        OR        A, L:0x52d0
        LD        L:0x52d0, A
        LD        A, XH
        LD        L:0x52c6, A
        LD        A, XL
        LD        L:0x52c7, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC2Init:
        LD        S:?b6, A
        LD        A, L:0x52bd
        AND       A, #0xf
        LD        L:0x52bd, A
        LD        A, S:?b3
        AND       A, #0x80
        PUSH      A
        LD        A, S:?b2
        AND       A, #0x20
        LD        S:?b2, A
        POP       A
        OR        A, S:?b2
        PUSH      A
        LD        A, S:?b1
        AND       A, #0x40
        PUSH      A
        LD        A, S:?b0
        AND       A, #0x10
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        OR        A, L:0x52bd
        LD        L:0x52bd, A
        LD        A, L:0x52ba
        AND       A, #0x8f
        OR        A, S:?b6
        LD        L:0x52ba, A
        LD        A, L:0x52d0
        AND       A, #0xf3
        LD        L:0x52d0, A
        LD        A, S:?b5
        AND       A, #0x8
        PUSH      A
        LD        A, S:?b4
        AND       A, #0x4
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        OR        A, L:0x52d0
        LD        L:0x52d0, A
        LD        A, XH
        LD        L:0x52c8, A
        LD        A, XL
        LD        L:0x52c9, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC3Init:
        LD        S:?b6, A
        LD        A, L:0x52be
        AND       A, #0xf0
        LD        L:0x52be, A
        LD        A, S:?b3
        AND       A, #0x8
        PUSH      A
        LD        A, S:?b2
        AND       A, #0x2
        LD        S:?b2, A
        POP       A
        OR        A, S:?b2
        PUSH      A
        LD        A, S:?b1
        AND       A, #0x4
        PUSH      A
        LD        A, S:?b0
        AND       A, #0x1
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        OR        A, L:0x52be
        LD        L:0x52be, A
        LD        A, L:0x52bb
        AND       A, #0x8f
        OR        A, S:?b6
        LD        L:0x52bb, A
        LD        A, L:0x52d0
        AND       A, #0xcf
        LD        L:0x52d0, A
        LD        A, S:?b5
        AND       A, #0x20
        PUSH      A
        LD        A, S:?b4
        AND       A, #0x10
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        OR        A, L:0x52d0
        LD        L:0x52d0, A
        LD        A, XH
        LD        L:0x52ca, A
        LD        A, XL
        LD        L:0x52cb, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_BDTRConfig:
        LD        S:?b5, A
        LD        A, S:?b1
        LD        L:0x52cf, A
        LD        A, S:?b3
        OR        A, S:?b2
        OR        A, S:?b4
        PUSH      A
        LD        A, S:?b0
        OR        A, S:?b5
        LD        S:?b0, A
        POP       A
        OR        A, S:?b0
        LD        L:0x52ce, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_CtrlPWMOutputs:
        TNZ       A
        JREQ      L:??TIM1_CtrlPWMOutputs_0
        BSET      L:0x52ce, #0x7
        RET
??TIM1_CtrlPWMOutputs_0:
        BRES      L:0x52ce, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectOCxM:
        TNZ       A
        JRNE      L:??TIM1_SelectOCxM_0
        BRES      L:0x52bd, #0x0
        LD        A, L:0x52b9
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52b9, A
        RET
??TIM1_SelectOCxM_0:
        CP        A, #0x1
        JRNE      L:??TIM1_SelectOCxM_1
        BRES      L:0x52bd, #0x4
        LD        A, L:0x52ba
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52ba, A
        RET
??TIM1_SelectOCxM_1:
        BRES      L:0x52be, #0x0
        LD        A, L:0x52bb
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52bb, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetCompare1:
        LD        A, XH
        LD        L:0x52c6, A
        LD        A, XL
        LD        L:0x52c7, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetCompare2:
        LD        A, XH
        LD        L:0x52c8, A
        LD        A, XL
        LD        L:0x52c9, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetCompare3:
        LD        A, XH
        LD        L:0x52ca, A
        LD        A, XL
        LD        L:0x52cb, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SetCompare4:
        LD        A, XH
        LD        L:0x52cc, A
        LD        A, XL
        LD        L:0x52cd, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_CCPreloadControl:
        TNZ       A
        JREQ      L:??TIM1_CCPreloadControl_0
        BSET      L:0x52b1, #0x0
        RET
??TIM1_CCPreloadControl_0:
        BRES      L:0x52b1, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ForcedOC1Config:
        LD        S:?b0, A
        LD        A, L:0x52b9
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52b9, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ForcedOC2Config:
        LD        S:?b0, A
        LD        A, L:0x52ba
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52ba, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ForcedOC3Config:
        LD        S:?b0, A
        LD        A, L:0x52bb
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52bb, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC1PreloadConfig:
        TNZ       A
        JREQ      L:??TIM1_OC1PreloadConfig_0
        BSET      L:0x52b9, #0x3
        RET
??TIM1_OC1PreloadConfig_0:
        BRES      L:0x52b9, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC2PreloadConfig:
        TNZ       A
        JREQ      L:??TIM1_OC2PreloadConfig_0
        BSET      L:0x52ba, #0x3
        RET
??TIM1_OC2PreloadConfig_0:
        BRES      L:0x52ba, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC3PreloadConfig:
        TNZ       A
        JREQ      L:??TIM1_OC3PreloadConfig_0
        BSET      L:0x52bb, #0x3
        RET
??TIM1_OC3PreloadConfig_0:
        BRES      L:0x52bb, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC4PreloadConfig:
        TNZ       A
        JREQ      L:??TIM1_OC4PreloadConfig_0
        BSET      L:0x52bc, #0x3
        RET
??TIM1_OC4PreloadConfig_0:
        BRES      L:0x52bc, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC1FastConfig:
        TNZ       A
        JREQ      L:??TIM1_OC1FastConfig_0
        BSET      L:0x52b9, #0x2
        RET
??TIM1_OC1FastConfig_0:
        BRES      L:0x52b9, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC2FastConfig:
        TNZ       A
        JREQ      L:??TIM1_OC2FastConfig_0
        BSET      L:0x52ba, #0x2
        RET
??TIM1_OC2FastConfig_0:
        BRES      L:0x52ba, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC3FastConfig:
        TNZ       A
        JREQ      L:??TIM1_OC3FastConfig_0
        BSET      L:0x52bb, #0x2
        RET
??TIM1_OC3FastConfig_0:
        BRES      L:0x52bb, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearOC1Ref:
        TNZ       A
        JREQ      L:??TIM1_ClearOC1Ref_0
        BSET      L:0x52b9, #0x7
        RET
??TIM1_ClearOC1Ref_0:
        BRES      L:0x52b9, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearOC2Ref:
        TNZ       A
        JREQ      L:??TIM1_ClearOC2Ref_0
        BSET      L:0x52ba, #0x7
        RET
??TIM1_ClearOC2Ref_0:
        BRES      L:0x52ba, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearOC3Ref:
        TNZ       A
        JREQ      L:??TIM1_ClearOC3Ref_0
        BSET      L:0x52bb, #0x7
        RET
??TIM1_ClearOC3Ref_0:
        BRES      L:0x52bb, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearOC4Ref:
        TNZ       A
        JREQ      L:??TIM1_ClearOC4Ref_0
        BSET      L:0x52bc, #0x7
        RET
??TIM1_ClearOC4Ref_0:
        BRES      L:0x52bc, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC1PolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC1PolarityConfig_0
        BSET      L:0x52bd, #0x1
        RET
??TIM1_OC1PolarityConfig_0:
        BRES      L:0x52bd, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC1NPolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC1NPolarityConfig_0
        BSET      L:0x52bd, #0x3
        RET
??TIM1_OC1NPolarityConfig_0:
        BRES      L:0x52bd, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC2PolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC2PolarityConfig_0
        BSET      L:0x52bd, #0x5
        RET
??TIM1_OC2PolarityConfig_0:
        BRES      L:0x52bd, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC2NPolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC2NPolarityConfig_0
        BSET      L:0x52bd, #0x7
        RET
??TIM1_OC2NPolarityConfig_0:
        BRES      L:0x52bd, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC3PolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC3PolarityConfig_0
        BSET      L:0x52be, #0x1
        RET
??TIM1_OC3PolarityConfig_0:
        BRES      L:0x52be, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_OC3NPolarityConfig:
        TNZ       A
        JREQ      L:??TIM1_OC3NPolarityConfig_0
        BSET      L:0x52be, #0x3
        RET
??TIM1_OC3NPolarityConfig_0:
        BRES      L:0x52be, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectOCREFClear:
        LD        S:?b0, A
        BRES      L:0x52b2, #0x3
        LD        A, L:0x52b2
        OR        A, S:?b0
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectCOM:
        TNZ       A
        JREQ      L:??TIM1_SelectCOM_0
        BSET      L:0x52b1, #0x2
        RET
??TIM1_SelectCOM_0:
        BRES      L:0x52b1, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_CCxCmd:
        TNZ       A
        JRNE      L:??TIM1_CCxCmd_0
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxCmd_1
        BSET      L:0x52bd, #0x0
        RET
??TIM1_CCxCmd_1:
        BRES      L:0x52bd, #0x0
        RET
??TIM1_CCxCmd_0:
        CP        A, #0x1
        JRNE      L:??TIM1_CCxCmd_2
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxCmd_3
        BSET      L:0x52bd, #0x4
        RET
??TIM1_CCxCmd_3:
        BRES      L:0x52bd, #0x4
        RET
??TIM1_CCxCmd_2:
        CP        A, #0x2
        JRNE      L:??TIM1_CCxCmd_4
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxCmd_5
        BSET      L:0x52be, #0x0
        RET
??TIM1_CCxCmd_5:
        BRES      L:0x52be, #0x0
        RET
??TIM1_CCxCmd_4:
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxCmd_6
        BSET      L:0x52be, #0x4
        RET
??TIM1_CCxCmd_6:
        BRES      L:0x52be, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_CCxNCmd:
        TNZ       A
        JRNE      L:??TIM1_CCxNCmd_0
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxNCmd_1
        BSET      L:0x52bd, #0x2
        RET
??TIM1_CCxNCmd_1:
        BRES      L:0x52bd, #0x2
        RET
??TIM1_CCxNCmd_0:
        CP        A, #0x1
        JRNE      L:??TIM1_CCxNCmd_2
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxNCmd_3
        BSET      L:0x52bd, #0x6
        RET
??TIM1_CCxNCmd_3:
        BRES      L:0x52bd, #0x6
        RET
??TIM1_CCxNCmd_2:
        TNZ       S:?b0
        JREQ      L:??TIM1_CCxNCmd_4
        BSET      L:0x52be, #0x2
        RET
??TIM1_CCxNCmd_4:
        BRES      L:0x52be, #0x2
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM1_SetIC4Prescaler:
        LD        S:?b0, A
        LD        A, L:0x52bc
        AND       A, #0xf3
        OR        A, S:?b0
        LD        L:0x52bc, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI4_Config:
        LD        S:?b2, A
        LD        A, S:?b1
        BRES      L:0x52be, #0x4
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        PUSH      A
        LD        A, L:0x52bc
        AND       A, #0xc
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        L:0x52bc, A
        TNZ       S:?b2
        JREQ      L:??TI4_Config_0
        BSET      L:0x52be, #0x5
        JRA       L:??TI4_Config_1
??TI4_Config_0:
        BRES      L:0x52be, #0x5
??TI4_Config_1:
        BSET      L:0x52be, #0x4
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM1_SetIC3Prescaler:
        LD        S:?b0, A
        LD        A, L:0x52bb
        AND       A, #0xf3
        OR        A, S:?b0
        LD        L:0x52bb, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI3_Config:
        LD        S:?b2, A
        LD        A, S:?b1
        BRES      L:0x52be, #0x0
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        PUSH      A
        LD        A, L:0x52bb
        AND       A, #0xc
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        L:0x52bb, A
        TNZ       S:?b2
        JREQ      L:??TI3_Config_0
        BSET      L:0x52be, #0x1
        JRA       L:??TI3_Config_1
??TI3_Config_0:
        BRES      L:0x52be, #0x1
??TI3_Config_1:
        BSET      L:0x52be, #0x0
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM1_SetIC2Prescaler:
        LD        S:?b0, A
        LD        A, L:0x52ba
        AND       A, #0xf3
        OR        A, S:?b0
        LD        L:0x52ba, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI2_Config:
        LD        S:?b2, A
        LD        A, S:?b1
        BRES      L:0x52bd, #0x4
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        PUSH      A
        LD        A, L:0x52ba
        AND       A, #0xc
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        L:0x52ba, A
        TNZ       S:?b2
        JREQ      L:??TI2_Config_0
        BSET      L:0x52bd, #0x5
        JRA       L:??TI2_Config_1
??TI2_Config_0:
        BRES      L:0x52bd, #0x5
??TI2_Config_1:
        BSET      L:0x52bd, #0x4
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TIM1_SetIC1Prescaler:
        LD        S:?b0, A
        LD        A, L:0x52b9
        AND       A, #0xf3
        OR        A, S:?b0
        LD        L:0x52b9, A
        RET

        SECTION `.near_func.text`:CODE:NOROOT(0)
        CODE
TI1_Config:
        LD        S:?b2, A
        LD        A, S:?b1
        BRES      L:0x52bd, #0x0
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b0
        PUSH      A
        LD        A, L:0x52b9
        AND       A, #0xc
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        L:0x52b9, A
        TNZ       S:?b2
        JREQ      L:??TI1_Config_0
        BSET      L:0x52bd, #0x1
        JRA       L:??TI1_Config_1
??TI1_Config_0:
        BRES      L:0x52bd, #0x1
??TI1_Config_1:
        BSET      L:0x52bd, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ICInit:
        MOV       S:?b4, S:?b0
        MOV       S:?b0, S:?b1
        MOV       S:?b5, S:?b2
        MOV       S:?b1, S:?b3
        TNZ       A
        JRNE      L:??TIM1_ICInit_0
        LD        A, S:?b4
        CALL      L:TI1_Config
        LD        A, S:?b5
        JP        L:TIM1_SetIC1Prescaler
??TIM1_ICInit_0:
        CP        A, #0x1
        JRNE      L:??TIM1_ICInit_1
        LD        A, S:?b4
        CALL      L:TI2_Config
        LD        A, S:?b5
        JP        L:TIM1_SetIC2Prescaler
??TIM1_ICInit_1:
        CP        A, #0x2
        JRNE      L:??TIM1_ICInit_2
        LD        A, S:?b4
        CALL      L:TI3_Config
        LD        A, S:?b5
        JP        L:TIM1_SetIC3Prescaler
??TIM1_ICInit_2:
        LD        A, S:?b4
        CALL      L:TI4_Config
        LD        A, S:?b5
        JP        L:TIM1_SetIC4Prescaler

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_PWMIConfig:
        PUSH      S:?b8
        LD        S:?b6, A
        MOV       S:?b7, S:?b0
        MOV       S:?b0, S:?b1
        MOV       S:?b8, S:?b2
        CLR       S:?b4
        MOV       S:?b5, #0x1
        LD        A, S:?b7
        CP        A, #0x1
        JREQ      L:??TIM1_PWMIConfig_0
        MOV       S:?b4, #0x1
        JRA       L:??TIM1_PWMIConfig_1
??TIM1_PWMIConfig_0:
        CLR       S:?b4
??TIM1_PWMIConfig_1:
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM1_PWMIConfig_2
        MOV       S:?b5, #0x2
        JRA       L:??TIM1_PWMIConfig_3
??TIM1_PWMIConfig_2:
        MOV       S:?b5, #0x1
??TIM1_PWMIConfig_3:
        TNZ       S:?b6
        JRNE      L:??TIM1_PWMIConfig_4
        MOV       S:?b1, S:?b3
        LD        A, S:?b7
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM1_SetIC1Prescaler
        MOV       S:?b1, S:?b3
        MOV       S:?b0, S:?b5
        LD        A, S:?b4
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM1_SetIC2Prescaler
        JRA       L:??TIM1_PWMIConfig_5
??TIM1_PWMIConfig_4:
        MOV       S:?b1, S:?b3
        LD        A, S:?b7
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM1_SetIC2Prescaler
        MOV       S:?b1, S:?b3
        MOV       S:?b0, S:?b5
        LD        A, S:?b4
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM1_SetIC1Prescaler
??TIM1_PWMIConfig_5:
        POP       S:?b8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_GetCapture1:
        CLRW      Y
        CLR       A
        CLR       S:?b0
        MOV       S:?b1, L:0x52c6
        MOV       S:?b0, S:?b1
        MOV       S:?b1, L:0x52c7
        LD        A, S:?b1
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
TIM1_GetCapture2:
        CLRW      Y
        CLR       A
        CLR       S:?b0
        MOV       S:?b1, L:0x52c8
        MOV       S:?b0, S:?b1
        MOV       S:?b1, L:0x52c9
        LD        A, S:?b1
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
TIM1_GetCapture3:
        CLRW      Y
        CLR       A
        CLR       S:?b0
        MOV       S:?b1, L:0x52ca
        MOV       S:?b0, S:?b1
        MOV       S:?b1, L:0x52cb
        LD        A, S:?b1
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
TIM1_GetCapture4:
        CLRW      Y
        CLR       A
        CLR       S:?b0
        MOV       S:?b1, L:0x52cc
        MOV       S:?b0, S:?b1
        MOV       S:?b1, L:0x52cd
        LD        A, S:?b1
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
TIM1_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM1_ITConfig_0
        LD        A, L:0x52b5
        OR        A, S:?b1
        LD        L:0x52b5, A
        RET
??TIM1_ITConfig_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, L:0x52b5
        LD        L:0x52b5, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_GenerateEvent:
        LD        L:0x52b8, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_GetFlagStatus:
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, XL
        AND       A, L:0x52b6
        LD        S:?b2, A
        LD        A, XH
        AND       A, L:0x52b7
        LD        S:?b1, A
        LD        A, S:?b1
        OR        A, S:?b2
        CP        A, #0x0
        JREQ      L:??TIM1_GetFlagStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??TIM1_GetFlagStatus_1
??TIM1_GetFlagStatus_0:
        CLR       S:?b0
??TIM1_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearFlag:
        LD        A, XL
        CPL       A
        LD        L:0x52b6, A
        LD        A, XH
        CPL       A
        AND       A, #0x1e
        LD        L:0x52b7, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, L:0x52b6
        AND       A, S:?b3
        LD        S:?b2, A
        LD        A, L:0x52b5
        AND       A, S:?b3
        LD        S:?b1, A
        TNZ       S:?b2
        JREQ      L:??TIM1_GetITStatus_0
        TNZ       S:?b1
        JREQ      L:??TIM1_GetITStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??TIM1_GetITStatus_1
??TIM1_GetITStatus_0:
        CLR       S:?b0
??TIM1_GetITStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ClearITPendingBit:
        CPL       A
        LD        L:0x52b6, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_DMAConfig:
        LD        L:0x52d1, A
        LD        A, S:?b0
        LD        L:0x52d2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM1_DMACmd_0
        LD        A, L:0x52b4
        OR        A, S:?b1
        LD        L:0x52b4, A
        RET
??TIM1_DMACmd_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, L:0x52b4
        LD        L:0x52b4, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectCCDMA:
        TNZ       A
        JREQ      L:??TIM1_SelectCCDMA_0
        BSET      L:0x52b1, #0x3
        RET
??TIM1_SelectCCDMA_0:
        BRES      L:0x52b1, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_InternalClockConfig:
        LD        A, L:0x52b2
        AND       A, #0xf8
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_TIxExternalClockConfig:
        LD        S:?b3, A
        MOV       S:?b2, S:?b0
        LD        A, S:?b3
        CP        A, #0x60
        JRNE      L:??TIM1_TIxExternalClockConfig_0
        MOV       S:?b0, #0x1
        LD        A, S:?b2
        CALL      L:TI2_Config
        JRA       L:??TIM1_TIxExternalClockConfig_1
??TIM1_TIxExternalClockConfig_0:
        MOV       S:?b0, #0x1
        LD        A, S:?b2
        CALL      L:TI1_Config
??TIM1_TIxExternalClockConfig_1:
        LD        A, S:?b3
        CALL      L:TIM1_SelectInputTrigger
        LD        A, L:0x52b2
        OR        A, #0x7
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ETRClockMode1Config:
        CALL      L:TIM1_ETRConfig
        LD        A, L:0x52b2
        OR        A, #0x77
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ETRClockMode2Config:
        CALL      L:TIM1_ETRConfig
        BSET      L:0x52b3, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectInputTrigger:
        LD        S:?b0, A
        LD        A, L:0x52b2
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectOutputTrigger:
        LD        S:?b0, A
        LD        A, L:0x52b1
        AND       A, #0x8f
        OR        A, S:?b0
        LD        L:0x52b1, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectSlaveMode:
        LD        S:?b0, A
        LD        A, L:0x52b2
        AND       A, #0xf8
        OR        A, S:?b0
        LD        L:0x52b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectMasterSlaveMode:
        TNZ       A
        JREQ      L:??TIM1_SelectMasterSlaveMode_0
        BSET      L:0x52b2, #0x7
        RET
??TIM1_SelectMasterSlaveMode_0:
        BRES      L:0x52b2, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_ETRConfig:
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
        OR        A, S:?b1
        OR        A, L:0x52b3
        LD        L:0x52b3, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_EncoderInterfaceConfig:
        LD        S:?b2, A
        TNZ       S:?b0
        JREQ      L:??TIM1_EncoderInterfaceConfig_0
        BSET      L:0x52bd, #0x1
        JRA       L:??TIM1_EncoderInterfaceConfig_1
??TIM1_EncoderInterfaceConfig_0:
        BRES      L:0x52bd, #0x1
??TIM1_EncoderInterfaceConfig_1:
        TNZ       S:?b1
        JREQ      L:??TIM1_EncoderInterfaceConfig_2
        BSET      L:0x52bd, #0x5
        JRA       L:??TIM1_EncoderInterfaceConfig_3
??TIM1_EncoderInterfaceConfig_2:
        BRES      L:0x52bd, #0x5
??TIM1_EncoderInterfaceConfig_3:
        LD        A, L:0x52b2
        AND       A, #0xf0
        OR        A, S:?b2
        LD        L:0x52b2, A
        LD        A, L:0x52b9
        AND       A, #0xfc
        OR        A, #0x1
        LD        L:0x52b9, A
        LD        A, L:0x52ba
        AND       A, #0xfc
        OR        A, #0x1
        LD        L:0x52ba, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM1_SelectHallSensor:
        TNZ       A
        JREQ      L:??TIM1_SelectHallSensor_0
        BSET      L:0x52b1, #0x7
        RET
??TIM1_SelectHallSensor_0:
        BRES      L:0x52b1, #0x7
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 2 190 bytes in section .near_func.text
// 
// 2 190 bytes of CODE memory
//
//Errors: none
//Warnings: none
