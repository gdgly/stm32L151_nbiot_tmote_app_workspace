///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  13:23:56
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_irtim.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW5477.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_irtim.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_irtim.s
//
///////////////////////////////////////////////////////////////////////////////

        PUBLIC IRTIM_Cmd
        PUBLIC IRTIM_DeInit
        PUBLIC IRTIM_GetHighSinkODStatus
        PUBLIC IRTIM_GetStatus
        PUBLIC IRTIM_HighSinkODCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
IRTIM_DeInit:
        CLR       L:0x52ff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
IRTIM_Cmd:
        TNZ       A
        JRNE      L:??IRTIM_Cmd_0
        BRES      L:0x52ff, #0x0
        JRA       L:??IRTIM_Cmd_1
??IRTIM_Cmd_0:
        BSET      L:0x52ff, #0x0
??IRTIM_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
IRTIM_HighSinkODCmd:
        TNZ       A
        JRNE      L:??IRTIM_HighSinkODCmd_0
        BRES      L:0x52ff, #0x1
        JRA       L:??IRTIM_HighSinkODCmd_1
??IRTIM_HighSinkODCmd_0:
        BSET      L:0x52ff, #0x1
??IRTIM_HighSinkODCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
IRTIM_GetStatus:
        LD        A, L:0x52ff
        AND       A, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
IRTIM_GetHighSinkODStatus:
        LD        A, L:0x52ff
        AND       A, #0x2
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 45 bytes in section .near_func.text
// 
// 45 bytes of CODE memory
//
//Errors: none
//Warnings: none
