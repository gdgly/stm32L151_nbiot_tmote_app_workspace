///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:27
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wwdg.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWD815.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wwdg.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_wwdg.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1

        PUBLIC WWDG_Enable
        PUBLIC WWDG_GetCounter
        PUBLIC WWDG_Init
        PUBLIC WWDG_SWReset
        PUBLIC WWDG_SetCounter
        PUBLIC WWDG_SetWindowValue


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_Init:
        LD        S:?b1, A
        MOV       L:0x50d4, #0x7f
        LD        A, S:?b1
        OR        A, #0x80
        LD        L:0x50d3, A
        LD        A, S:?b0
        AND       A, #0x7f
        LD        L:0x50d4, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_SetWindowValue:
        SUB       SP, #0x1
        LD        S:?b0, A
        CLR       (0x1,SP)
        LD        A, S:?b0
        AND       A, #0x7f
        OR        A, (0x1,SP)
        LD        (0x1,SP), A
        LD        A, (0x1,SP)
        LD        L:0x50d4, A
        ADD       SP, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_SetCounter:
        LD        S:?b0, A
        LD        A, S:?b0
        AND       A, #0x7f
        LD        L:0x50d3, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_Enable:
        LD        S:?b0, A
        LD        A, S:?b0
        OR        A, #0x80
        LD        L:0x50d3, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_GetCounter:
        LD        A, L:0x50d3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_SWReset:
        MOV       L:0x50d3, #0x80
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 72 bytes in section .near_func.text
// 
// 72 bytes of CODE memory
//
//Errors: none
//Warnings: none
