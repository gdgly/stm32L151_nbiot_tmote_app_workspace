///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:20
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Delay\delay.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWB80C.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Delay\delay.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\delay.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?w0

        PUBLIC Delay_MS_Normal
        PUBLIC Delay_US_FuncType1
        PUBLIC Delay_US_Normal


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Delay_US_Normal:
        nop
        nop
        nop
        nop
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Delay_MS_Normal:
        LDW       S:?w0, X
??Delay_MS_Normal_0:
        LDW       Y, S:?w0
        LDW       S:?w0, Y
        LDW       X, S:?w0
        DECW      X
        LDW       S:?w0, X
        TNZW      Y
        JREQ      L:??Delay_MS_Normal_1
        LDW       X, #0x384
??Delay_MS_Normal_2:
        TNZW      X
        JREQ      L:??Delay_MS_Normal_0
        CALL      L:Delay_US_Normal
        DECW      X
        JRA       L:??Delay_MS_Normal_2
??Delay_MS_Normal_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Delay_US_FuncType1:
        LDW       S:?w0, X
??Delay_US_FuncType1_0:
        LDW       Y, S:?w0
        LDW       S:?w0, Y
        LDW       X, S:?w0
        DECW      X
        LDW       S:?w0, X
        TNZW      Y
        JREQ      L:??Delay_US_FuncType1_1
        LDW       X, #0x32
??Delay_US_FuncType1_2:
        TNZW      X
        JREQ      L:??Delay_US_FuncType1_0
        CALL      L:Delay_US_Normal
        DECW      X
        JRA       L:??Delay_US_FuncType1_2
??Delay_US_FuncType1_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 65 bytes in section .near_func.text
// 
// 65 bytes of CODE memory
//
//Errors: none
//Warnings: none
