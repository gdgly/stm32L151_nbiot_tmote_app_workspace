///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  13:09:11
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_beep.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW76D1.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_beep.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_beep.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?mul16_x_x_w0
        EXTERN ?udiv32_l0_l0_dl
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2

        PUBLIC BEEP_Cmd
        PUBLIC BEEP_DeInit
        PUBLIC BEEP_Init
        PUBLIC BEEP_LSClockToTIMConnectCmd
        PUBLIC BEEP_LSICalibrationConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_DeInit:
        CLR       L:0x50f0
        MOV       L:0x50f3, #0x1f
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_Init:
        LD        S:?b0, A
        LD        A, L:0x50f3
        AND       A, #0x1f
        CP        A, #0x1f
        JRNE      L:??BEEP_Init_0
        LD        A, L:0x50f3
        AND       A, #0xe0
        LD        L:0x50f3, A
        BSET      L:0x50f3, #0x0
??BEEP_Init_0:
        LD        A, L:0x50f3
        AND       A, #0x3f
        LD        L:0x50f3, A
        LD        A, L:0x50f3
        OR        A, S:?b0
        LD        L:0x50f3, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_Cmd:
        TNZ       A
        JREQ      L:??BEEP_Cmd_0
        BSET      L:0x50f3, #0x5
        RET
??BEEP_Cmd_0:
        BRES      L:0x50f3, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_LSClockToTIMConnectCmd:
        TNZ       A
        JREQ      L:??BEEP_LSClockToTIMConnectCmd_0
        BSET      L:0x50f0, #0x0
        RET
??BEEP_LSClockToTIMConnectCmd_0:
        BRES      L:0x50f0, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_LSICalibrationConfig:
        CALL      L:?udiv32_l0_l0_dl
        DATA
        DC32      0x3e8
        CODE
        LD        A, L:0x50f3
        AND       A, #0xe0
        LD        L:0x50f3, A
        LDW       X, S:?w1
        SRLW      X
        SRLW      X
        SRLW      X
        LDW       Y, X
        LDW       X, #0x8
        LDW       S:?w0, X
        LDW       X, Y
        CALL      L:?mul16_x_x_w0
        LDW       S:?w2, X
        LDW       X, S:?w1
        SUBW      X, S:?w2
        LDW       S:?w1, X
        LDW       X, Y
        SLLW      X
        LDW       S:?w0, X
        LDW       X, S:?w0
        INCW      X
        LDW       S:?w0, X
        LDW       X, S:?w1
        CALL      L:?mul16_x_x_w0
        LDW       S:?w1, X
        LDW       X, #0x8
        LDW       S:?w0, X
        LDW       X, Y
        CALL      L:?mul16_x_x_w0
        CPW       X, S:?w1
        JRC       L:??BEEP_LSICalibrationConfig_0
        LD        A, YL
        DEC       A
        DEC       A
        OR        A, L:0x50f3
        LD        L:0x50f3, A
        RET
??BEEP_LSICalibrationConfig_0:
        LD        A, YL
        DEC       A
        OR        A, L:0x50f3
        LD        L:0x50f3, A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 166 bytes in section .near_func.text
// 
// 166 bytes of CODE memory
//
//Errors: none
//Warnings: none
