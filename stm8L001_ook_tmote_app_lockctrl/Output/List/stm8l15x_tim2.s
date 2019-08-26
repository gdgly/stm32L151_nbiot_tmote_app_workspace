///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:13:01
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim2.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW77F8.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_tim2.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_tim2.s
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

        PUBLIC TIM2_ARRPreloadConfig
        PUBLIC TIM2_BKRConfig
        PUBLIC TIM2_CCxCmd
        PUBLIC TIM2_ClearFlag
        PUBLIC TIM2_ClearITPendingBit
        PUBLIC TIM2_Cmd
        PUBLIC TIM2_CounterModeConfig
        PUBLIC TIM2_CtrlPWMOutputs
        PUBLIC TIM2_DMACmd
        PUBLIC TIM2_DeInit
        PUBLIC TIM2_ETRClockMode1Config
        PUBLIC TIM2_ETRClockMode2Config
        PUBLIC TIM2_ETRConfig
        PUBLIC TIM2_EncoderInterfaceConfig
        PUBLIC TIM2_ForcedOC1Config
        PUBLIC TIM2_ForcedOC2Config
        PUBLIC TIM2_GenerateEvent
        PUBLIC TIM2_GetCapture1
        PUBLIC TIM2_GetCapture2
        PUBLIC TIM2_GetCounter
        PUBLIC TIM2_GetFlagStatus
        PUBLIC TIM2_GetITStatus
        PUBLIC TIM2_GetPrescaler
        PUBLIC TIM2_ICInit
        PUBLIC TIM2_ITConfig
        PUBLIC TIM2_InternalClockConfig
        PUBLIC TIM2_OC1FastConfig
        PUBLIC TIM2_OC1Init
        PUBLIC TIM2_OC1PolarityConfig
        PUBLIC TIM2_OC1PreloadConfig
        PUBLIC TIM2_OC2FastConfig
        PUBLIC TIM2_OC2Init
        PUBLIC TIM2_OC2PolarityConfig
        PUBLIC TIM2_OC2PreloadConfig
        PUBLIC TIM2_PWMIConfig
        PUBLIC TIM2_PrescalerConfig
        PUBLIC TIM2_SelectCCDMA
        PUBLIC TIM2_SelectHallSensor
        PUBLIC TIM2_SelectInputTrigger
        PUBLIC TIM2_SelectMasterSlaveMode
        PUBLIC TIM2_SelectOCxM
        PUBLIC TIM2_SelectOnePulseMode
        PUBLIC TIM2_SelectOutputTrigger
        PUBLIC TIM2_SelectSlaveMode
        PUBLIC TIM2_SetAutoreload
        PUBLIC TIM2_SetCompare1
        PUBLIC TIM2_SetCompare2
        PUBLIC TIM2_SetCounter
        PUBLIC TIM2_SetIC1Prescaler
        PUBLIC TIM2_SetIC2Prescaler
        PUBLIC TIM2_TIxExternalClockConfig
        PUBLIC TIM2_TimeBaseInit
        PUBLIC TIM2_UpdateDisableConfig
        PUBLIC TIM2_UpdateRequestConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_DeInit:
        CLR       L:0x5250
        CLR       L:0x5251
        CLR       L:0x5252
        CLR       L:0x5253
        CLR       L:0x5255
        CLR       L:0x5257
        CLR       L:0x525b
        MOV       L:0x5259, #0x1
        MOV       L:0x525a, #0x1
        CLR       L:0x525b
        CLR       L:0x5259
        CLR       L:0x525a
        CLR       L:0x525c
        CLR       L:0x525d
        CLR       L:0x525e
        MOV       L:0x525f, #0xff
        MOV       L:0x5260, #0xff
        CLR       L:0x5261
        CLR       L:0x5262
        CLR       L:0x5263
        CLR       L:0x5264
        CLR       L:0x5266
        MOV       L:0x5258, #0x1
        CLR       L:0x5265
        CLR       L:0x5256
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_TimeBaseInit:
        LD        S:?b1, A
        LD        A, XH
        LD        L:0x525f, A
        LD        A, XL
        LD        L:0x5260, A
        LD        A, S:?b1
        LD        L:0x525e, A
        LD        A, L:0x5250
        AND       A, #0x8f
        LD        L:0x5250, A
        LD        A, L:0x5250
        OR        A, S:?b0
        LD        L:0x5250, A
        MOV       L:0x5258, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_PrescalerConfig:
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x525e, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM2_PrescalerConfig_0
        BSET      L:0x5258, #0x0
        JRA       L:??TIM2_PrescalerConfig_1
??TIM2_PrescalerConfig_0:
        BRES      L:0x5258, #0x0
??TIM2_PrescalerConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_CounterModeConfig:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5250
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5250, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SetCounter:
        LD        A, XH
        LD        L:0x525c, A
        LD        A, XL
        LD        L:0x525d, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SetAutoreload:
        LD        A, XH
        LD        L:0x525f, A
        LD        A, XL
        LD        L:0x5260, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_GetCounter:
        CLRW      Y
        LD        A, L:0x525c
        LD        S:?b0, A
        LD        A, L:0x525d
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
TIM2_GetPrescaler:
        LD        A, L:0x525e
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_UpdateDisableConfig:
        TNZ       A
        JREQ      L:??TIM2_UpdateDisableConfig_0
        BSET      L:0x5250, #0x1
        JRA       L:??TIM2_UpdateDisableConfig_1
??TIM2_UpdateDisableConfig_0:
        BRES      L:0x5250, #0x1
??TIM2_UpdateDisableConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_UpdateRequestConfig:
        CP        A, #0x1
        JRNE      L:??TIM2_UpdateRequestConfig_0
        BSET      L:0x5250, #0x2
        JRA       L:??TIM2_UpdateRequestConfig_1
??TIM2_UpdateRequestConfig_0:
        BRES      L:0x5250, #0x2
??TIM2_UpdateRequestConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ARRPreloadConfig:
        TNZ       A
        JREQ      L:??TIM2_ARRPreloadConfig_0
        BSET      L:0x5250, #0x7
        JRA       L:??TIM2_ARRPreloadConfig_1
??TIM2_ARRPreloadConfig_0:
        BRES      L:0x5250, #0x7
??TIM2_ARRPreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectOnePulseMode:
        CP        A, #0x1
        JRNE      L:??TIM2_SelectOnePulseMode_0
        BSET      L:0x5250, #0x3
        JRA       L:??TIM2_SelectOnePulseMode_1
??TIM2_SelectOnePulseMode_0:
        BRES      L:0x5250, #0x3
??TIM2_SelectOnePulseMode_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_Cmd:
        TNZ       A
        JREQ      L:??TIM2_Cmd_0
        BSET      L:0x5250, #0x0
        JRA       L:??TIM2_Cmd_1
??TIM2_Cmd_0:
        BRES      L:0x5250, #0x0
??TIM2_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC1Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x5259
        LD        S:?b4, A
        BRES      L:0x525b, #0x0
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x5259, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM2_OC1Init_0
        BSET      L:0x525b, #0x0
        JRA       L:??TIM2_OC1Init_1
??TIM2_OC1Init_0:
        BRES      L:0x525b, #0x0
??TIM2_OC1Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM2_OC1Init_2
        BSET      L:0x525b, #0x1
        JRA       L:??TIM2_OC1Init_3
??TIM2_OC1Init_2:
        BRES      L:0x525b, #0x1
??TIM2_OC1Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM2_OC1Init_4
        BSET      L:0x5266, #0x0
        JRA       L:??TIM2_OC1Init_5
??TIM2_OC1Init_4:
        BRES      L:0x5266, #0x0
??TIM2_OC1Init_5:
        LD        A, XH
        LD        L:0x5261, A
        LD        A, XL
        LD        L:0x5262, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC2Init:
        LD        S:?b3, A
        CLR       S:?b4
        LD        A, L:0x525a
        LD        S:?b4, A
        BRES      L:0x525b, #0x4
        LD        A, S:?b4
        AND       A, #0x8f
        LD        S:?b4, A
        LD        A, S:?b3
        OR        A, S:?b4
        LD        S:?b4, A
        LD        A, S:?b4
        LD        L:0x525a, A
        LD        A, S:?b0
        CP        A, #0x1
        JRNE      L:??TIM2_OC2Init_0
        BSET      L:0x525b, #0x4
        JRA       L:??TIM2_OC2Init_1
??TIM2_OC2Init_0:
        BRES      L:0x525b, #0x4
??TIM2_OC2Init_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM2_OC2Init_2
        BSET      L:0x525b, #0x5
        JRA       L:??TIM2_OC2Init_3
??TIM2_OC2Init_2:
        BRES      L:0x525b, #0x5
??TIM2_OC2Init_3:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??TIM2_OC2Init_4
        BSET      L:0x5266, #0x2
        JRA       L:??TIM2_OC2Init_5
??TIM2_OC2Init_4:
        BRES      L:0x5266, #0x2
??TIM2_OC2Init_5:
        LD        A, XH
        LD        L:0x5263, A
        LD        A, XL
        LD        L:0x5264, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_BKRConfig:
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
        LD        L:0x5265, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_CtrlPWMOutputs:
        TNZ       A
        JREQ      L:??TIM2_CtrlPWMOutputs_0
        BSET      L:0x5265, #0x7
        JRA       L:??TIM2_CtrlPWMOutputs_1
??TIM2_CtrlPWMOutputs_0:
        BRES      L:0x5265, #0x7
??TIM2_CtrlPWMOutputs_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectOCxM:
        LD        S:?b1, A
        TNZ       S:?b1
        JRNE      L:??TIM2_SelectOCxM_0
        BRES      L:0x525b, #0x0
        LD        A, L:0x5259
        AND       A, #0x8f
        LD        L:0x5259, A
        LD        A, L:0x5259
        OR        A, S:?b0
        LD        L:0x5259, A
        JRA       L:??TIM2_SelectOCxM_1
??TIM2_SelectOCxM_0:
        BRES      L:0x525b, #0x4
        LD        A, L:0x525a
        AND       A, #0x8f
        LD        L:0x525a, A
        LD        A, L:0x525a
        OR        A, S:?b0
        LD        L:0x525a, A
??TIM2_SelectOCxM_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SetCompare1:
        LD        A, XH
        LD        L:0x5261, A
        LD        A, XL
        LD        L:0x5262, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SetCompare2:
        LD        A, XH
        LD        L:0x5263, A
        LD        A, XL
        LD        L:0x5264, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ForcedOC1Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5259
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5259, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ForcedOC2Config:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x525a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x525a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC1PreloadConfig:
        TNZ       A
        JREQ      L:??TIM2_OC1PreloadConfig_0
        BSET      L:0x5259, #0x3
        JRA       L:??TIM2_OC1PreloadConfig_1
??TIM2_OC1PreloadConfig_0:
        BRES      L:0x5259, #0x3
??TIM2_OC1PreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC2PreloadConfig:
        TNZ       A
        JREQ      L:??TIM2_OC2PreloadConfig_0
        BSET      L:0x525a, #0x3
        JRA       L:??TIM2_OC2PreloadConfig_1
??TIM2_OC2PreloadConfig_0:
        BRES      L:0x525a, #0x3
??TIM2_OC2PreloadConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC1FastConfig:
        TNZ       A
        JREQ      L:??TIM2_OC1FastConfig_0
        BSET      L:0x5259, #0x2
        JRA       L:??TIM2_OC1FastConfig_1
??TIM2_OC1FastConfig_0:
        BRES      L:0x5259, #0x2
??TIM2_OC1FastConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC2FastConfig:
        TNZ       A
        JREQ      L:??TIM2_OC2FastConfig_0
        BSET      L:0x525a, #0x2
        JRA       L:??TIM2_OC2FastConfig_1
??TIM2_OC2FastConfig_0:
        BRES      L:0x525a, #0x2
??TIM2_OC2FastConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC1PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM2_OC1PolarityConfig_0
        BSET      L:0x525b, #0x1
        JRA       L:??TIM2_OC1PolarityConfig_1
??TIM2_OC1PolarityConfig_0:
        BRES      L:0x525b, #0x1
??TIM2_OC1PolarityConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_OC2PolarityConfig:
        CP        A, #0x1
        JRNE      L:??TIM2_OC2PolarityConfig_0
        BSET      L:0x525b, #0x5
        JRA       L:??TIM2_OC2PolarityConfig_1
??TIM2_OC2PolarityConfig_0:
        BRES      L:0x525b, #0x5
??TIM2_OC2PolarityConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_CCxCmd:
        TNZ       A
        JRNE      L:??TIM2_CCxCmd_0
        TNZ       S:?b0
        JREQ      L:??TIM2_CCxCmd_1
        BSET      L:0x525b, #0x0
        JRA       L:??TIM2_CCxCmd_2
??TIM2_CCxCmd_1:
        BRES      L:0x525b, #0x0
        JRA       L:??TIM2_CCxCmd_2
??TIM2_CCxCmd_0:
        TNZ       S:?b0
        JREQ      L:??TIM2_CCxCmd_3
        BSET      L:0x525b, #0x4
        JRA       L:??TIM2_CCxCmd_2
??TIM2_CCxCmd_3:
        BRES      L:0x525b, #0x4
??TIM2_CCxCmd_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ICInit:
        CALL      L:?push_w4
        LD        S:?b5, A
        MOV       S:?b6, S:?b0
        MOV       S:?b7, S:?b1
        MOV       S:?b8, S:?b2
        MOV       S:?b9, S:?b3
        TNZ       S:?b5
        JRNE      L:??TIM2_ICInit_0
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b7
        LD        A, S:?b6
        CALL      L:TI1_Config
        LD        A, S:?b8
        CALL      L:TIM2_SetIC1Prescaler
        JRA       L:??TIM2_ICInit_1
??TIM2_ICInit_0:
        MOV       S:?b1, S:?b9
        MOV       S:?b0, S:?b7
        LD        A, S:?b6
        CALL      L:TI2_Config
        LD        A, S:?b8
        CALL      L:TIM2_SetIC2Prescaler
??TIM2_ICInit_1:
        JP        L:?epilogue_w4

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_PWMIConfig:
        CALL      L:?push_l2
        LD        S:?b6, A
        MOV       S:?b7, S:?b0
        MOV       S:?b9, S:?b1
        MOV       S:?b10, S:?b2
        MOV       S:?b11, S:?b3
        CLR       S:?b5
        MOV       S:?b8, #0x1
        TNZ       S:?b7
        JRNE      L:??TIM2_PWMIConfig_0
        LD        A, #0x1
        LD        S:?b5, A
        JRA       L:??TIM2_PWMIConfig_1
??TIM2_PWMIConfig_0:
        CLR       S:?b5
??TIM2_PWMIConfig_1:
        LD        A, S:?b9
        CP        A, #0x1
        JRNE      L:??TIM2_PWMIConfig_2
        LD        A, #0x2
        LD        S:?b8, A
        JRA       L:??TIM2_PWMIConfig_3
??TIM2_PWMIConfig_2:
        LD        A, #0x1
        LD        S:?b8, A
??TIM2_PWMIConfig_3:
        TNZ       S:?b6
        JRNE      L:??TIM2_PWMIConfig_4
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b9
        LD        A, S:?b7
        CALL      L:TI1_Config
        LD        A, S:?b10
        CALL      L:TIM2_SetIC1Prescaler
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b8
        LD        A, S:?b5
        CALL      L:TI2_Config
        LD        A, S:?b10
        CALL      L:TIM2_SetIC2Prescaler
        JRA       L:??TIM2_PWMIConfig_5
??TIM2_PWMIConfig_4:
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b9
        LD        A, S:?b7
        CALL      L:TI2_Config
        LD        A, S:?b10
        CALL      L:TIM2_SetIC2Prescaler
        MOV       S:?b1, S:?b11
        MOV       S:?b0, S:?b8
        LD        A, S:?b5
        CALL      L:TI1_Config
        LD        A, S:?b10
        CALL      L:TIM2_SetIC1Prescaler
??TIM2_PWMIConfig_5:
        JP        L:?epilogue_l2

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_GetCapture1:
        CLRW      Y
        LD        A, L:0x5261
        LD        S:?b0, A
        LD        A, L:0x5262
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
TIM2_GetCapture2:
        CLRW      Y
        LD        A, L:0x5263
        LD        S:?b0, A
        LD        A, L:0x5264
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
TIM2_SetIC1Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5259
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5259, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SetIC2Prescaler:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x525a
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf3
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x525a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM2_ITConfig_0
        LD        A, L:0x5255
        OR        A, S:?b1
        LD        L:0x5255, A
        JRA       L:??TIM2_ITConfig_1
??TIM2_ITConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x5255
        LD        L:0x5255, A
??TIM2_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_GenerateEvent:
        LD        S:?b0, A
        LD        A, L:0x5258
        OR        A, S:?b0
        LD        L:0x5258, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_GetFlagStatus:
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        LD        A, XL
        AND       A, L:0x5256
        LD        S:?b2, A
        LD        A, XH
        AND       A, L:0x5257
        LD        S:?b1, A
        LD        A, S:?b1
        OR        A, S:?b2
        CP        A, #0x0
        JREQ      L:??TIM2_GetFlagStatus_0
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??TIM2_GetFlagStatus_1
??TIM2_GetFlagStatus_0:
        CLR       S:?b0
??TIM2_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ClearFlag:
        LD        A, XL
        CPL       A
        LD        L:0x5256, A
        LD        A, XH
        CPL       A
        LD        L:0x5257, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, L:0x5256
        AND       A, S:?b3
        LD        S:?b1, A
        LD        A, L:0x5255
        AND       A, S:?b3
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??TIM2_GetITStatus_0
        TNZ       S:?b0
        JREQ      L:??TIM2_GetITStatus_0
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??TIM2_GetITStatus_1
??TIM2_GetITStatus_0:
        CLR       S:?b2
??TIM2_GetITStatus_1:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ClearITPendingBit:
        LD        S:?b0, A
        LD        A, S:?b0
        CPL       A
        LD        L:0x5256, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??TIM2_DMACmd_0
        LD        A, L:0x5254
        OR        A, S:?b1
        LD        L:0x5254, A
        JRA       L:??TIM2_DMACmd_1
??TIM2_DMACmd_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x5254
        LD        L:0x5254, A
??TIM2_DMACmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectCCDMA:
        TNZ       A
        JREQ      L:??TIM2_SelectCCDMA_0
        BSET      L:0x5251, #0x3
        JRA       L:??TIM2_SelectCCDMA_1
??TIM2_SelectCCDMA_0:
        BRES      L:0x5251, #0x3
??TIM2_SelectCCDMA_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_InternalClockConfig:
        LD        A, L:0x5252
        AND       A, #0xf8
        LD        L:0x5252, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_TIxExternalClockConfig:
        LD        S:?b5, A
        MOV       S:?b6, S:?b0
        MOV       S:?b7, S:?b1
        LD        A, S:?b5
        CP        A, #0x60
        JRNE      L:??TIM2_TIxExternalClockConfig_0
        MOV       S:?b1, S:?b7
        MOV       S:?b0, #0x1
        LD        A, S:?b6
        CALL      L:TI2_Config
        JRA       L:??TIM2_TIxExternalClockConfig_1
??TIM2_TIxExternalClockConfig_0:
        MOV       S:?b1, S:?b7
        MOV       S:?b0, #0x1
        LD        A, S:?b6
        CALL      L:TI1_Config
??TIM2_TIxExternalClockConfig_1:
        LD        A, S:?b5
        CALL      L:TIM2_SelectInputTrigger
        LD        A, L:0x5252
        OR        A, #0x7
        LD        L:0x5252, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ETRClockMode1Config:
        LD        S:?b3, A
        MOV       S:?b4, S:?b0
        MOV       S:?b5, S:?b1
        MOV       S:?b1, S:?b5
        MOV       S:?b0, S:?b4
        LD        A, S:?b3
        CALL      L:TIM2_ETRConfig
        LD        A, L:0x5252
        AND       A, #0xf8
        LD        L:0x5252, A
        LD        A, L:0x5252
        OR        A, #0x7
        LD        L:0x5252, A
        LD        A, L:0x5252
        AND       A, #0x8f
        LD        L:0x5252, A
        LD        A, L:0x5252
        OR        A, #0x70
        LD        L:0x5252, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ETRClockMode2Config:
        LD        S:?b3, A
        MOV       S:?b4, S:?b0
        MOV       S:?b5, S:?b1
        MOV       S:?b1, S:?b5
        MOV       S:?b0, S:?b4
        LD        A, S:?b3
        CALL      L:TIM2_ETRConfig
        BSET      L:0x5253, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectInputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5252
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5252, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectOutputTrigger:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5251
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x8f
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5251, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectSlaveMode:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, L:0x5252
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf8
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        LD        L:0x5252, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectMasterSlaveMode:
        TNZ       A
        JREQ      L:??TIM2_SelectMasterSlaveMode_0
        BSET      L:0x5252, #0x7
        JRA       L:??TIM2_SelectMasterSlaveMode_1
??TIM2_SelectMasterSlaveMode_0:
        BRES      L:0x5252, #0x7
??TIM2_SelectMasterSlaveMode_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_ETRConfig:
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
        OR        A, S:?b1
        OR        A, L:0x5253
        LD        L:0x5253, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_EncoderInterfaceConfig:
        LD        S:?b4, A
        CLR       S:?b5
        CLR       S:?b3
        CLR       S:?b2
        LD        A, L:0x5252
        LD        S:?b5, A
        LD        A, L:0x5259
        LD        S:?b3, A
        LD        A, L:0x525a
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
        JRNE      L:??TIM2_EncoderInterfaceConfig_0
        BSET      L:0x525b, #0x1
        JRA       L:??TIM2_EncoderInterfaceConfig_1
??TIM2_EncoderInterfaceConfig_0:
        BRES      L:0x525b, #0x1
??TIM2_EncoderInterfaceConfig_1:
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??TIM2_EncoderInterfaceConfig_2
        BSET      L:0x525b, #0x5
        JRA       L:??TIM2_EncoderInterfaceConfig_3
??TIM2_EncoderInterfaceConfig_2:
        BRES      L:0x525b, #0x5
??TIM2_EncoderInterfaceConfig_3:
        LD        A, S:?b5
        LD        L:0x5252, A
        LD        A, S:?b3
        LD        L:0x5259, A
        LD        A, S:?b2
        LD        L:0x525a, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TIM2_SelectHallSensor:
        TNZ       A
        JREQ      L:??TIM2_SelectHallSensor_0
        BSET      L:0x5251, #0x7
        JRA       L:??TIM2_SelectHallSensor_1
??TIM2_SelectHallSensor_0:
        BRES      L:0x5251, #0x7
??TIM2_SelectHallSensor_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TI1_Config:
        LD        S:?b2, A
        CLR       S:?b4
        MOV       S:?b3, S:?b2
        LD        A, L:0x5259
        LD        S:?b4, A
        BRES      L:0x525b, #0x0
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
        LD        L:0x5259, A
        LD        A, S:?b3
        CP        A, #0x1
        JRNE      L:??TI1_Config_0
        BSET      L:0x525b, #0x1
        JRA       L:??TI1_Config_1
??TI1_Config_0:
        BRES      L:0x525b, #0x1
??TI1_Config_1:
        BSET      L:0x525b, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
TI2_Config:
        LD        S:?b2, A
        CLR       S:?b4
        MOV       S:?b3, S:?b2
        LD        A, L:0x525a
        LD        S:?b4, A
        BRES      L:0x525b, #0x4
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
        LD        L:0x525a, A
        LD        A, S:?b3
        CP        A, #0x1
        JRNE      L:??TI2_Config_0
        BSET      L:0x525b, #0x5
        JRA       L:??TI2_Config_1
??TI2_Config_0:
        BRES      L:0x525b, #0x5
??TI2_Config_1:
        BSET      L:0x525b, #0x4
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
