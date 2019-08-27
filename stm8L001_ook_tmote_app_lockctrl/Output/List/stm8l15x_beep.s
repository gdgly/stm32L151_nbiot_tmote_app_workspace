///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                27/Aug/2019  13:26:09
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_beep.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW4E5D.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_beep.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_beep.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b13
        EXTERN ?epilogue_l2_l3
        EXTERN ?mov_l0_l2
        EXTERN ?mov_l2_l0
        EXTERN ?mov_w7_w1
        EXTERN ?mul16_x_x_w0
        EXTERN ?push_l2
        EXTERN ?push_l3
        EXTERN ?udiv32_l0_l0_dl
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w6
        EXTERN ?w7

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
        JRA       L:??BEEP_Cmd_1
??BEEP_Cmd_0:
        BRES      L:0x50f3, #0x5
??BEEP_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_LSClockToTIMConnectCmd:
        TNZ       A
        JREQ      L:??BEEP_LSClockToTIMConnectCmd_0
        BSET      L:0x50f0, #0x0
        JRA       L:??BEEP_LSClockToTIMConnectCmd_1
??BEEP_LSClockToTIMConnectCmd_0:
        BRES      L:0x50f0, #0x0
??BEEP_LSClockToTIMConnectCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
BEEP_LSICalibrationConfig:
        CALL      L:?push_l2
        CALL      L:?push_l3
        CALL      L:?mov_l2_l0
        CALL      L:?mov_l0_l2
        CALL      L:?udiv32_l0_l0_dl
        DATA
        DC32      0x3e8
        CODE
        CALL      L:?mov_w7_w1
        LD        A, L:0x50f3
        AND       A, #0xe0
        LD        L:0x50f3, A
        LDW       X, S:?w7
        SRLW      X
        SRLW      X
        SRLW      X
        LDW       S:?w6, X
        LDW       X, #0x8
        LDW       S:?w0, X
        LDW       X, S:?w6
        CALL      L:?mul16_x_x_w0
        LDW       S:?w1, X
        LDW       X, S:?w7
        SUBW      X, S:?w1
        LDW       Y, X
        LDW       X, S:?w6
        SLLW      X
        LDW       S:?w0, X
        LDW       X, S:?w0
        INCW      X
        LDW       S:?w0, X
        LDW       X, Y
        CALL      L:?mul16_x_x_w0
        LDW       S:?w1, X
        LDW       X, #0x8
        LDW       S:?w0, X
        LDW       X, S:?w6
        CALL      L:?mul16_x_x_w0
        CPW       X, S:?w1
        JRC       L:??BEEP_LSICalibrationConfig_0
        LD        A, S:?b13
        DEC       A
        DEC       A
        OR        A, L:0x50f3
        LD        L:0x50f3, A
        JRA       L:??BEEP_LSICalibrationConfig_1
??BEEP_LSICalibrationConfig_0:
        LD        A, S:?b13
        DEC       A
        OR        A, L:0x50f3
        LD        L:0x50f3, A
??BEEP_LSICalibrationConfig_1:
        JP        L:?epilogue_l2_l3

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 188 bytes in section .near_func.text
// 
// 188 bytes of CODE memory
//
//Errors: none
//Warnings: none
