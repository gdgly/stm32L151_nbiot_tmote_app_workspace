///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:23
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_gpio.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC4B8.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_gpio.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_gpio.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1

        PUBLIC GPIO_DeInit
        PUBLIC GPIO_ExternalPullUpConfig
        PUBLIC GPIO_Init
        PUBLIC GPIO_ReadInputData
        PUBLIC GPIO_ReadInputDataBit
        PUBLIC GPIO_ReadOutputData
        PUBLIC GPIO_ReadOutputDataBit
        PUBLIC GPIO_ResetBits
        PUBLIC GPIO_SetBits
        PUBLIC GPIO_ToggleBits
        PUBLIC GPIO_Write
        PUBLIC GPIO_WriteBit


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_DeInit:
        LDW       Y, X
        LDW       X, Y
        ADDW      X, #0x4
        CLR       (X)
        CLR       (Y)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_Init:
        LDW       Y, X
        LD        S:?b1, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LDW       X, Y
        ADDW      X, #0x4
        LD        (X), A
        LD        A, S:?b0
        AND       A, #0x80
        CP        A, #0x0
        JREQ      L:??GPIO_Init_0
        LD        A, S:?b0
        AND       A, #0x10
        CP        A, #0x0
        JREQ      L:??GPIO_Init_1
        LD        A, (Y)
        OR        A, S:?b1
        LD        (Y), A
        JRA       L:??GPIO_Init_2
??GPIO_Init_1:
        LD        A, S:?b1
        CPL       A
        AND       A, (Y)
        LD        (Y), A
??GPIO_Init_2:
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        OR        A, S:?b1
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        JRA       L:??GPIO_Init_3
??GPIO_Init_0:
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
??GPIO_Init_3:
        LD        A, S:?b0
        AND       A, #0x40
        CP        A, #0x0
        JREQ      L:??GPIO_Init_4
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        OR        A, S:?b1
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        JRA       L:??GPIO_Init_5
??GPIO_Init_4:
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
??GPIO_Init_5:
        LD        A, S:?b0
        AND       A, #0x20
        CP        A, #0x0
        JREQ      L:??GPIO_Init_6
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        OR        A, S:?b1
        LDW       X, Y
        ADDW      X, #0x4
        LD        (X), A
        JRA       L:??GPIO_Init_7
??GPIO_Init_6:
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LDW       X, Y
        ADDW      X, #0x4
        LD        (X), A
??GPIO_Init_7:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ExternalPullUpConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??GPIO_ExternalPullUpConfig_0
        LDW       Y, X
        ADDW      Y, #0x3
        LD        A, (Y)
        OR        A, S:?b1
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
        JRA       L:??GPIO_ExternalPullUpConfig_1
??GPIO_ExternalPullUpConfig_0:
        LDW       Y, X
        ADDW      Y, #0x3
        LD        A, S:?b1
        CPL       A
        AND       A, (Y)
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
??GPIO_ExternalPullUpConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_Write:
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_WriteBit:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??GPIO_WriteBit_0
        LD        A, (X)
        OR        A, S:?b1
        LD        (X), A
        JRA       L:??GPIO_WriteBit_1
??GPIO_WriteBit_0:
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LD        (X), A
??GPIO_WriteBit_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_SetBits:
        LD        S:?b0, A
        LD        A, (X)
        OR        A, S:?b0
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ResetBits:
        LD        S:?b0, A
        LD        A, S:?b0
        CPL       A
        AND       A, (X)
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ToggleBits:
        LD        S:?b0, A
        LD        A, (X)
        XOR       A, S:?b0
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ReadInputData:
        INCW      X
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ReadOutputData:
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ReadInputDataBit:
        LD        S:?b0, A
        INCW      X
        LD        A, (X)
        AND       A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
GPIO_ReadOutputDataBit:
        LD        S:?b0, A
        LD        A, (X)
        AND       A, S:?b0
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 265 bytes in section .near_func.text
// 
// 265 bytes of CODE memory
//
//Errors: none
//Warnings: none
