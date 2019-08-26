///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:12:55
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_clk.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW5FF8.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_clk.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_clk.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?epilogue_l2_l3
        EXTERN ?mov_l0_l2
        EXTERN ?mov_l0_l3
        EXTERN ?mov_l2_l0
        EXTERN ?mov_l3_l0
        EXTERN ?push_l2
        EXTERN ?push_l3
        EXTERN ?sll16_x_x_a
        EXTERN ?udiv32_l0_l0_l1
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w3
        EXTERN ?w4
        EXTERN ?w5
        EXTERN ?w6
        EXTERN ?w7

        PUBLIC CLK_AdjustHSICalibrationValue
        PUBLIC CLK_BEEPClockConfig
        PUBLIC CLK_CCOConfig
        PUBLIC CLK_ClearFlag
        PUBLIC CLK_ClearITPendingBit
        PUBLIC CLK_ClockSecuritySystemEnable
        PUBLIC CLK_ClockSecuritySytemDeglitchCmd
        PUBLIC CLK_DeInit
        PUBLIC CLK_GetClockFreq
        PUBLIC CLK_GetFlagStatus
        PUBLIC CLK_GetITStatus
        PUBLIC CLK_GetSYSCLKSource
        PUBLIC CLK_HSEConfig
        PUBLIC CLK_HSICmd
        PUBLIC CLK_HaltConfig
        PUBLIC CLK_ITConfig
        PUBLIC CLK_LSEClockSecuritySystemEnable
        PUBLIC CLK_LSEConfig
        PUBLIC CLK_LSICmd
        PUBLIC CLK_MainRegulatorCmd
        PUBLIC CLK_PeripheralClockConfig
        PUBLIC CLK_RTCCLKSwitchOnLSEFailureEnable
        PUBLIC CLK_RTCClockConfig
        PUBLIC CLK_SYSCLKDivConfig
        PUBLIC CLK_SYSCLKSourceConfig
        PUBLIC CLK_SYSCLKSourceSwitchCmd
        PUBLIC SYSDivFactor


        SECTION `.near.rodata`:CONST:REORDER:NOROOT(0)
SYSDivFactor:
        DC8 1, 2, 4, 8, 16

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_DeInit:
        MOV       L:0x50c2, #0x11
        CLR       L:0x50c6
        CLR       L:0x50c1
        CLR       L:0x50cb
        MOV       L:0x50c8, #0x1
        CLR       L:0x50c9
        MOV       L:0x50c0, #0x3
        CLR       L:0x50c3
        MOV       L:0x50c4, #0x80
        CLR       L:0x50d0
        CLR       L:0x50ca
        CLR       L:0x50c5
        CLR       L:0x50cd
        CLR       L:0x50cc
        CLR       L:0x50ce
        MOV       L:0x50cf, #0xb9
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_HSICmd:
        TNZ       A
        JREQ      L:??CLK_HSICmd_0
        BSET      L:0x50c2, #0x0
        JRA       L:??CLK_HSICmd_1
??CLK_HSICmd_0:
        BRES      L:0x50c2, #0x0
??CLK_HSICmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_AdjustHSICalibrationValue:
        MOV       L:0x50ce, #0xac
        MOV       L:0x50ce, #0x35
        LD        L:0x50cd, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_LSICmd:
        TNZ       A
        JREQ      L:??CLK_LSICmd_0
        BSET      L:0x50c2, #0x2
        JRA       L:??CLK_LSICmd_1
??CLK_LSICmd_0:
        BRES      L:0x50c2, #0x2
??CLK_LSICmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_HSEConfig:
        LD        S:?b0, A
        BRES      L:0x50c6, #0x0
        BRES      L:0x50c6, #0x4
        LD        A, L:0x50c6
        OR        A, S:?b0
        LD        L:0x50c6, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_LSEConfig:
        LD        S:?b0, A
        BRES      L:0x50c6, #0x2
        BRES      L:0x50c6, #0x5
        LD        A, L:0x50c6
        OR        A, S:?b0
        LD        L:0x50c6, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_ClockSecuritySystemEnable:
        BSET      L:0x50ca, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_ClockSecuritySytemDeglitchCmd:
        TNZ       A
        JREQ      L:??CLK_ClockSecuritySytemDeglitchCmd_0
        BSET      L:0x50ca, #0x4
        JRA       L:??CLK_ClockSecuritySytemDeglitchCmd_1
??CLK_ClockSecuritySytemDeglitchCmd_0:
        BRES      L:0x50ca, #0x4
??CLK_ClockSecuritySytemDeglitchCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_CCOConfig:
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        L:0x50c5, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_SYSCLKSourceConfig:
        LD        L:0x50c8, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_GetSYSCLKSource:
        LD        A, L:0x50c7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_GetClockFreq:
        CALL      L:?push_l2
        CALL      L:?push_l3
        SUB       SP, #0x3
        CLRW      X
        LDW       S:?w5, X
        LDW       S:?w4, X
        CLRW      X
        LDW       S:?w7, X
        LDW       S:?w6, X
        LD        A, #0x1
        LD        (0x1,SP), A
        CLR       (0x3,SP)
        CLR       (0x2,SP)
        LD        A, L:0x50c7
        LD        (0x1,SP), A
        LD        A, (0x1,SP)
        CP        A, #0x1
        JRNE      L:??CLK_GetClockFreq_0
        LDW       X, #0x2400
        LDW       S:?w1, X
        LDW       X, #0xf4
        LDW       S:?w0, X
        CALL      L:?mov_l3_l0
        JRA       L:??CLK_GetClockFreq_1
??CLK_GetClockFreq_0:
        LD        A, (0x1,SP)
        CP        A, #0x2
        JRNE      L:??CLK_GetClockFreq_2
        LDW       X, #0x9470
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mov_l3_l0
        JRA       L:??CLK_GetClockFreq_1
??CLK_GetClockFreq_2:
        LD        A, (0x1,SP)
        CP        A, #0x4
        JRNE      L:??CLK_GetClockFreq_3
        LDW       X, #0x2400
        LDW       S:?w1, X
        LDW       X, #0xf4
        LDW       S:?w0, X
        CALL      L:?mov_l3_l0
        JRA       L:??CLK_GetClockFreq_1
??CLK_GetClockFreq_3:
        LDW       X, #0x8000
        LDW       S:?w1, X
        SLLW      X
        LDW       S:?w0, X
        CALL      L:?mov_l2_l0
??CLK_GetClockFreq_1:
        LD        A, L:0x50c0
        AND       A, #0x7
        LD        (0x3,SP), A
        LD        A, (0x3,SP)
        CLRW      X
        LD        XL, A
        LD        A, (L:SYSDivFactor,X)
        LD        (0x2,SP), A
        LD        A, (0x2,SP)
        CLRW      X
        LD        XL, A
        LDW       S:?w3, X
        CLRW      X
        LDW       S:?w2, X
        CALL      L:?mov_l0_l3
        CALL      L:?udiv32_l0_l0_l1
        CALL      L:?mov_l2_l0
        CALL      L:?mov_l0_l2
        ADD       SP, #0x3
        JP        L:?epilogue_l2_l3

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_SYSCLKDivConfig:
        LD        L:0x50c0, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_SYSCLKSourceSwitchCmd:
        TNZ       A
        JREQ      L:??CLK_SYSCLKSourceSwitchCmd_0
        BSET      L:0x50c9, #0x1
        JRA       L:??CLK_SYSCLKSourceSwitchCmd_1
??CLK_SYSCLKSourceSwitchCmd_0:
        BRES      L:0x50c9, #0x1
??CLK_SYSCLKSourceSwitchCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_RTCClockConfig:
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        L:0x50c1, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_BEEPClockConfig:
        LD        L:0x50cb, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_PeripheralClockConfig:
        LD        S:?b2, A
        CLR       S:?b1
        LD        A, S:?b2
        AND       A, #0xf0
        LD        S:?b1, A
        TNZ       S:?b1
        JRNE      L:??CLK_PeripheralClockConfig_0
        TNZ       S:?b0
        JREQ      L:??CLK_PeripheralClockConfig_1
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50c3
        LD        L:0x50c3, A
        JRA       L:??CLK_PeripheralClockConfig_2
??CLK_PeripheralClockConfig_1:
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50c3
        LD        L:0x50c3, A
        JRA       L:??CLK_PeripheralClockConfig_2
??CLK_PeripheralClockConfig_0:
        LD        A, S:?b1
        CP        A, #0x10
        JRNE      L:??CLK_PeripheralClockConfig_3
        TNZ       S:?b0
        JREQ      L:??CLK_PeripheralClockConfig_4
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50c4
        LD        L:0x50c4, A
        JRA       L:??CLK_PeripheralClockConfig_2
??CLK_PeripheralClockConfig_4:
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50c4
        LD        L:0x50c4, A
        JRA       L:??CLK_PeripheralClockConfig_2
??CLK_PeripheralClockConfig_3:
        TNZ       S:?b0
        JREQ      L:??CLK_PeripheralClockConfig_5
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50d0
        LD        L:0x50d0, A
        JRA       L:??CLK_PeripheralClockConfig_2
??CLK_PeripheralClockConfig_5:
        LD        A, S:?b2
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50d0
        LD        L:0x50d0, A
??CLK_PeripheralClockConfig_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_LSEClockSecuritySystemEnable:
        BSET      L:0x5190, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_RTCCLKSwitchOnLSEFailureEnable:
        BSET      L:0x5190, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_HaltConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??CLK_HaltConfig_0
        LD        A, L:0x50c2
        OR        A, S:?b1
        LD        L:0x50c2, A
        JRA       L:??CLK_HaltConfig_1
??CLK_HaltConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x50c2
        LD        L:0x50c2, A
??CLK_HaltConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_MainRegulatorCmd:
        TNZ       A
        JREQ      L:??CLK_MainRegulatorCmd_0
        BRES      L:0x50cf, #0x1
        JRA       L:??CLK_MainRegulatorCmd_1
??CLK_MainRegulatorCmd_0:
        BSET      L:0x50cf, #0x1
??CLK_MainRegulatorCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_ITConfig:
        TNZ       S:?b0
        JREQ      L:??CLK_ITConfig_0
        CP        A, #0x1c
        JRNE      L:??CLK_ITConfig_1
        BSET      L:0x50c9, #0x2
        JRA       L:??CLK_ITConfig_2
??CLK_ITConfig_1:
        CP        A, #0x2c
        JRNE      L:??CLK_ITConfig_3
        BSET      L:0x5190, #0x2
        JRA       L:??CLK_ITConfig_2
??CLK_ITConfig_3:
        BSET      L:0x50ca, #0x2
        JRA       L:??CLK_ITConfig_2
??CLK_ITConfig_0:
        CP        A, #0x1c
        JRNE      L:??CLK_ITConfig_4
        BRES      L:0x50c9, #0x2
        JRA       L:??CLK_ITConfig_2
??CLK_ITConfig_4:
        CP        A, #0x2c
        JRNE      L:??CLK_ITConfig_5
        BRES      L:0x5190, #0x2
        JRA       L:??CLK_ITConfig_2
??CLK_ITConfig_5:
        BRES      L:0x50ca, #0x2
??CLK_ITConfig_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_GetFlagStatus:
        LD        S:?b2, A
        CLR       S:?b3
        CLR       S:?b1
        CLR       S:?b0
        LD        A, S:?b2
        AND       A, #0xf0
        LD        S:?b3, A
        LD        A, S:?b2
        AND       A, #0xf
        LD        S:?b1, A
        TNZ       S:?b3
        JRNE      L:??CLK_GetFlagStatus_0
        LD        A, L:0x50c1
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_0:
        LD        A, S:?b3
        CP        A, #0x10
        JRNE      L:??CLK_GetFlagStatus_2
        LD        A, L:0x50c2
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_2:
        LD        A, S:?b3
        CP        A, #0x20
        JRNE      L:??CLK_GetFlagStatus_3
        LD        A, L:0x50c5
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_3:
        LD        A, S:?b3
        CP        A, #0x30
        JRNE      L:??CLK_GetFlagStatus_4
        LD        A, L:0x50c6
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_4:
        LD        A, S:?b3
        CP        A, #0x40
        JRNE      L:??CLK_GetFlagStatus_5
        LD        A, L:0x50c9
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_5:
        LD        A, S:?b3
        CP        A, #0x50
        JRNE      L:??CLK_GetFlagStatus_6
        LD        A, L:0x50ca
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_6:
        LD        A, S:?b3
        CP        A, #0x70
        JRNE      L:??CLK_GetFlagStatus_7
        LD        A, L:0x50cf
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_7:
        LD        A, S:?b3
        CP        A, #0x80
        JRNE      L:??CLK_GetFlagStatus_8
        LD        A, L:0x5190
        LD        S:?b3, A
        JRA       L:??CLK_GetFlagStatus_1
??CLK_GetFlagStatus_8:
        LD        A, L:0x50cb
        LD        S:?b3, A
??CLK_GetFlagStatus_1:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        AND       A, S:?b3
        CP        A, #0x0
        JREQ      L:??CLK_GetFlagStatus_9
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??CLK_GetFlagStatus_10
??CLK_GetFlagStatus_9:
        CLR       S:?b0
??CLK_GetFlagStatus_10:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_ClearFlag:
        BRES      L:0x5190, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_GetITStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, S:?b1
        CP        A, #0x1c
        JRNE      L:??CLK_GetITStatus_0
        LD        A, L:0x50c9
        AND       A, S:?b1
        CP        A, #0xc
        JRNE      L:??CLK_GetITStatus_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??CLK_GetITStatus_2
??CLK_GetITStatus_1:
        CLR       S:?b0
        JRA       L:??CLK_GetITStatus_2
??CLK_GetITStatus_0:
        LD        A, S:?b1
        CP        A, #0x2c
        JRNE      L:??CLK_GetITStatus_3
        LD        A, L:0x5190
        AND       A, S:?b1
        CP        A, #0xc
        JRNE      L:??CLK_GetITStatus_4
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??CLK_GetITStatus_2
??CLK_GetITStatus_4:
        CLR       S:?b0
        JRA       L:??CLK_GetITStatus_2
??CLK_GetITStatus_3:
        LD        A, L:0x50ca
        AND       A, S:?b1
        CP        A, #0xc
        JRNE      L:??CLK_GetITStatus_5
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??CLK_GetITStatus_2
??CLK_GetITStatus_5:
        CLR       S:?b0
??CLK_GetITStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
CLK_ClearITPendingBit:
        LD        S:?b0, A
        LD        A, S:?b0
        AND       A, #0xf0
        CP        A, #0x20
        JRNE      L:??CLK_ClearITPendingBit_0
        BRES      L:0x5190, #0x3
        JRA       L:??CLK_ClearITPendingBit_1
??CLK_ClearITPendingBit_0:
        BRES      L:0x50c9, #0x3
??CLK_ClearITPendingBit_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
//   5 bytes in section .near.rodata
// 856 bytes in section .near_func.text
// 
// 856 bytes of CODE  memory
//   5 bytes of CONST memory
//
//Errors: none
//Warnings: none
