///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  14:41:57
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\User\main.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW6AA3.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\User\main.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\main.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?dec32_l0_l0
        EXTERN ?mov_l0_l1
        EXTERN ?mov_l1_l0
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w3
        EXTERN GPIO_Init
        EXTERN GPIO_SetBits
        EXTERN GPIO_ToggleBits
        EXTERN Stm8_HSIClock_Init

        PUBLIC delay_ms
        PUBLIC delay_us
        PUBLIC main


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
delay_us:
        nop
        nop
        nop
        nop
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
delay_ms:
??delay_ms_0:
        CALL      L:?mov_l1_l0
        CALL      L:?mov_l0_l1
        CALL      L:?dec32_l0_l0
        LDW       X, S:?w2
        CPW       X, #0x0
        JRNE      L:??delay_ms_1
        LDW       X, S:?w3
        CPW       X, #0x0
??delay_ms_1:
        JREQ      L:??delay_ms_2
        LDW       X, #0x384
??delay_ms_3:
        TNZW      X
        JREQ      L:??delay_ms_0
        CALL      L:delay_us
        DECW      X
        JRA       L:??delay_ms_3
??delay_ms_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
main:
        CLR       A
        CALL      L:Stm8_HSIClock_Init
        MOV       S:?b0, #0xf0
        LD        A, #0x20
        LDW       X, #0x5005
        CALL      L:GPIO_Init
        LD        A, #0x20
        LDW       X, #0x5005
        CALL      L:GPIO_SetBits
??main_0:
        LD        A, #0x20
        LDW       X, #0x5005
        CALL      L:GPIO_ToggleBits
        LDW       X, #0x3e8
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:delay_ms
        JRA       L:??main_0

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 86 bytes in section .near_func.text
// 
// 86 bytes of CODE memory
//
//Errors: none
//Warnings: none
