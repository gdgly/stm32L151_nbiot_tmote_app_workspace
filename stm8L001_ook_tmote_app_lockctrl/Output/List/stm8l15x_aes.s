///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:12:54
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_aes.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW5F79.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_aes.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_aes.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3

        PUBLIC AES_ClearFlag
        PUBLIC AES_ClearITPendingBit
        PUBLIC AES_Cmd
        PUBLIC AES_DMAConfig
        PUBLIC AES_DeInit
        PUBLIC AES_GetFlagStatus
        PUBLIC AES_GetITStatus
        PUBLIC AES_ITConfig
        PUBLIC AES_OperationModeConfig
        PUBLIC AES_ReadSubData
        PUBLIC AES_ReadSubKey
        PUBLIC AES_WriteSubData
        PUBLIC AES_WriteSubKey


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_DeInit:
        MOV       L:0x53d0, #0x18
        CLR       L:0x53d2
        CLR       L:0x53d3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_OperationModeConfig:
        LD        S:?b0, A
        LD        A, L:0x53d0
        AND       A, #0xf9
        LD        L:0x53d0, A
        LD        A, L:0x53d0
        OR        A, S:?b0
        LD        L:0x53d0, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_Cmd:
        TNZ       A
        JREQ      L:??AES_Cmd_0
        BSET      L:0x53d0, #0x0
        JRA       L:??AES_Cmd_1
??AES_Cmd_0:
        BRES      L:0x53d0, #0x0
??AES_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_WriteSubData:
        LD        L:0x53d2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_WriteSubKey:
        LD        L:0x53d2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_ReadSubData:
        LD        A, L:0x53d3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_ReadSubKey:
        LD        A, L:0x53d3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_DMAConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??AES_DMAConfig_0
        LD        A, L:0x53d0
        OR        A, S:?b1
        LD        L:0x53d0, A
        JRA       L:??AES_DMAConfig_1
??AES_DMAConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x53d0
        LD        L:0x53d0, A
??AES_DMAConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??AES_ITConfig_0
        LD        A, L:0x53d0
        OR        A, S:?b1
        LD        L:0x53d0, A
        JRA       L:??AES_ITConfig_1
??AES_ITConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x53d0
        LD        L:0x53d0, A
??AES_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??AES_GetFlagStatus_0
        BTJF      L:0x53d1, #0x0, L:??AES_GetFlagStatus_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??AES_GetFlagStatus_2
??AES_GetFlagStatus_1:
        CLR       S:?b0
        JRA       L:??AES_GetFlagStatus_2
??AES_GetFlagStatus_0:
        LD        A, S:?b1
        CP        A, #0x2
        JRNE      L:??AES_GetFlagStatus_3
        BTJF      L:0x53d1, #0x1, L:??AES_GetFlagStatus_4
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??AES_GetFlagStatus_2
??AES_GetFlagStatus_4:
        CLR       S:?b0
        JRA       L:??AES_GetFlagStatus_2
??AES_GetFlagStatus_3:
        BTJF      L:0x53d1, #0x2, L:??AES_GetFlagStatus_5
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??AES_GetFlagStatus_2
??AES_GetFlagStatus_5:
        CLR       S:?b0
??AES_GetFlagStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_ClearFlag:
        CP        A, #0x1
        JRNE      L:??AES_ClearFlag_0
        BSET      L:0x53d0, #0x3
        JRA       L:??AES_ClearFlag_1
??AES_ClearFlag_0:
        BSET      L:0x53d0, #0x4
??AES_ClearFlag_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b0
        CLR       S:?b1
        LD        A, L:0x53d0
        AND       A, #0x20
        LD        S:?b2, A
        LD        A, L:0x53d1
        AND       A, #0x1
        LD        S:?b1, A
        LD        A, S:?b3
        CP        A, #0x20
        JRNE      L:??AES_GetITStatus_0
        TNZ       S:?b2
        JREQ      L:??AES_GetITStatus_1
        TNZ       S:?b1
        JREQ      L:??AES_GetITStatus_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??AES_GetITStatus_2
??AES_GetITStatus_1:
        CLR       S:?b0
        JRA       L:??AES_GetITStatus_2
??AES_GetITStatus_0:
        BTJF      L:0x53d0, #0x6, L:??AES_GetITStatus_3
        LD        A, L:0x53d1
        AND       A, #0x6
        CP        A, #0x0
        JREQ      L:??AES_GetITStatus_4
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??AES_GetITStatus_2
??AES_GetITStatus_4:
        CLR       S:?b0
        JRA       L:??AES_GetITStatus_2
??AES_GetITStatus_3:
        CLR       S:?b0
??AES_GetITStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
AES_ClearITPendingBit:
        CP        A, #0x20
        JRNE      L:??AES_ClearITPendingBit_0
        BSET      L:0x53d0, #0x3
        JRA       L:??AES_ClearITPendingBit_1
??AES_ClearITPendingBit_0:
        BSET      L:0x53d0, #0x4
??AES_ClearITPendingBit_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 279 bytes in section .near_func.text
// 
// 279 bytes of CODE memory
//
//Errors: none
//Warnings: none
