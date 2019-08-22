///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:24
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wwdg.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWD99F.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wwdg.c
//        -e -Ol --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
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
//        --vregs 16)
//    Locale       =  Chinese (Simplified)_CHN.936
//    List file    =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_wwdg.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0

        PUBLIC WWDG_Enable
        PUBLIC WWDG_GetCounter
        PUBLIC WWDG_Init
        PUBLIC WWDG_SWReset
        PUBLIC WWDG_SetCounter
        PUBLIC WWDG_SetWindowValue


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_Init:
        MOV       L:0x50d4, #0x7f
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
        CLR       (0x1,SP)
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
        AND       A, #0x7f
        LD        L:0x50d3, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WWDG_Enable:
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
// 56 bytes in section .near_func.text
// 
// 56 bytes of CODE memory
//
//Errors: none
//Warnings: none
