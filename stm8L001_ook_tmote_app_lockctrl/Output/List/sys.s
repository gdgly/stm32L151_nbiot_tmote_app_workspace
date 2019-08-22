///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  14:27:57
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Sys\sys.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW991C.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\System\Sys\sys.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\sys.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b8
        EXTERN CLK_HSICmd
        EXTERN CLK_LSICmd
        EXTERN CLK_SYSCLKDivConfig
        EXTERN CLK_SYSCLKSourceConfig
        EXTERN CLK_SYSCLKSourceSwitchCmd

        PUBLIC Stm8_HSIClock_Init
        PUBLIC Stm8_LSIClock_Init


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Stm8_HSIClock_Init:
        PUSH      S:?b8
        LD        S:?b8, A
        LD        A, #0x1
        CALL      L:CLK_HSICmd
        LD        A, #0x1
        CALL      L:CLK_SYSCLKSourceSwitchCmd
        LD        A, #0x1
        CALL      L:CLK_SYSCLKSourceConfig
        LD        A, S:?b8
        CALL      L:CLK_SYSCLKDivConfig
        POP       S:?b8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Stm8_LSIClock_Init:
        PUSH      S:?b8
        LD        S:?b8, A
        LD        A, #0x1
        CALL      L:CLK_LSICmd
        LD        A, #0x1
        CALL      L:CLK_SYSCLKSourceSwitchCmd
        LD        A, #0x2
        CALL      L:CLK_SYSCLKSourceConfig
        LD        A, S:?b8
        CALL      L:CLK_SYSCLKDivConfig
        POP       S:?b8
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 58 bytes in section .near_func.text
// 
// 58 bytes of CODE memory
//
//Errors: none
//Warnings: none
