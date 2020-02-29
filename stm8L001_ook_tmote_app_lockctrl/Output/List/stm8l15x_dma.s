///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:21
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dma.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC13B.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dma.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_dma.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?b7
        EXTERN ?b8
        EXTERN ?b9
        EXTERN ?epilogue_l2
        EXTERN ?push_l2
        EXTERN ?w0
        EXTERN ?w5

        PUBLIC DMA_ClearFlag
        PUBLIC DMA_ClearITPendingBit
        PUBLIC DMA_Cmd
        PUBLIC DMA_DeInit
        PUBLIC DMA_GetCurrDataCounter
        PUBLIC DMA_GetFlagStatus
        PUBLIC DMA_GetITStatus
        PUBLIC DMA_GlobalCmd
        PUBLIC DMA_GlobalDeInit
        PUBLIC DMA_ITConfig
        PUBLIC DMA_Init
        PUBLIC DMA_SetCurrDataCounter
        PUBLIC DMA_SetTimeOut


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GlobalDeInit:
        BRES      L:0x5070, #0x0
        MOV       L:0x5070, #0xfc
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_DeInit:
        LDW       Y, X
        LD        A, (Y)
        AND       A, #0xfe
        LD        (Y), A
        CLR       (Y)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        CPW       Y, #0x5093
        JRNE      L:??DMA_DeInit_0
        LD        A, #0x40
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        LDW       X, Y
        ADDW      X, #0x5
        CLR       (X)
        JRA       L:??DMA_DeInit_1
??DMA_DeInit_0:
        LD        A, #0x52
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
??DMA_DeInit_1:
        LDW       X, Y
        ADDW      X, #0x4
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x6
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x7
        CLR       (X)
        LDW       X, Y
        INCW      X
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_Init:
        CALL      L:?push_l2
        LD        S:?b8, A
        MOV       S:?b9, S:?b4
        LD        A, (0x7,SP)
        LD        S:?b4, A
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        CLR       (X)
        LD        A, S:?b5
        OR        A, S:?b9
        OR        A, S:?b6
        OR        A, (X)
        LD        (X), A
        LDW       S:?w5, X
        PUSHW     X
        LDW       X, S:?w5
        INCW      X
        LDW       S:?w5, X
        POPW      X
        LD        A, [S:?w5.w]
        AND       A, #0xc7
        LDW       S:?w5, X
        PUSHW     X
        LDW       X, S:?w5
        INCW      X
        LDW       S:?w5, X
        POPW      X
        LD        [S:?w5.w], A
        LD        A, S:?b4
        OR        A, S:?b7
        LDW       S:?w5, X
        PUSHW     X
        LDW       X, S:?w5
        INCW      X
        LDW       S:?w5, X
        POPW      X
        OR        A, [S:?w5.w]
        LDW       S:?w5, X
        PUSHW     X
        LDW       X, S:?w5
        INCW      X
        LDW       S:?w5, X
        POPW      X
        LD        [S:?w5.w], A
        LDW       S:?w5, X
        PUSHW     X
        LDW       X, S:?w5
        INCW      X
        INCW      X
        LDW       S:?w5, X
        POPW      X
        LD        A, S:?b8
        LD        [S:?w5.w], A
        LD        A, YH
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
        LD        A, YL
        ADDW      X, #0x4
        LD        (X), A
        SUBW      X, #0x4
        CPW       X, #0x5093
        JRNE      L:??DMA_Init_0
        LD        A, S:?b1
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
??DMA_Init_0:
        LD        A, S:?b2
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        LD        A, S:?b3
        ADDW      X, #0x7
        LD        (X), A
        SUBW      X, #0x7
        JP        L:?epilogue_l2

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GlobalCmd:
        TNZ       A
        JREQ      L:??DMA_GlobalCmd_0
        BSET      L:0x5070, #0x0
        JRA       L:??DMA_GlobalCmd_1
??DMA_GlobalCmd_0:
        BRES      L:0x5070, #0x0
??DMA_GlobalCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_Cmd:
        LD        S:?b0, A
        TNZ       S:?b0
        JREQ      L:??DMA_Cmd_0
        LD        A, (X)
        OR        A, #0x1
        LD        (X), A
        JRA       L:??DMA_Cmd_1
??DMA_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
??DMA_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_SetTimeOut:
        LD        S:?b0, A
        CLR       L:0x5070
        LD        A, S:?b0
        SLL       A
        SLL       A
        LD        L:0x5070, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_SetCurrDataCounter:
        LDW       Y, X
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GetCurrDataCounter:
        INCW      X
        INCW      X
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??DMA_ITConfig_0
        LD        A, (X)
        OR        A, S:?b1
        LD        (X), A
        JRA       L:??DMA_ITConfig_1
??DMA_ITConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, (X)
        LD        (X), A
??DMA_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GetFlagStatus:
        LDW       Y, X
        CLR       S:?b3
        LDW       X, #0x5075
        LDW       S:?w0, X
        CLR       S:?b4
        CLR       S:?b2
        LD        A, L:0x5070
        LD        S:?b2, A
        LD        A, L:0x5071
        LD        S:?b4, A
        LDW       X, Y
        RLWA      X, A
        AND       A, #0xf
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_0
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_1
        LDW       X, #0x5075
        LDW       S:?w0, X
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_1:
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x2
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_3
        LDW       X, #0x507f
        LDW       S:?w0, X
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_3:
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x4
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_4
        LDW       X, #0x5089
        LDW       S:?w0, X
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_4:
        LDW       X, #0x5093
        LDW       S:?w0, X
??DMA_GetFlagStatus_2:
        LDW       X, S:?w0
        INCW      X
        LD        A, YL
        AND       A, (X)
        LD        S:?b3, A
        JRA       L:??DMA_GetFlagStatus_5
??DMA_GetFlagStatus_0:
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x10
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_6
        LD        A, YL
        AND       A, S:?b4
        LD        S:?b3, A
        JRA       L:??DMA_GetFlagStatus_5
??DMA_GetFlagStatus_6:
        LD        A, S:?b2
        AND       A, #0x2
        LD        S:?b3, A
??DMA_GetFlagStatus_5:
        LD        A, S:?b3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_ClearFlag:
        LDW       Y, X
        LDW       X, #0x5075
        LDW       S:?w0, X
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_0
        LDW       X, #0x5075
        LDW       S:?w0, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_0:
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x2
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_2
        LDW       X, #0x507f
        LDW       S:?w0, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_2:
        LDW       X, Y
        RLWA      X, A
        AND       A, #0x4
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_3
        LDW       X, #0x5089
        LDW       S:?w0, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_3:
        LDW       X, #0x5093
        LDW       S:?w0, X
??DMA_ClearFlag_1:
        LD        A, YL
        AND       A, #0x6
        CPL       A
        LDW       X, S:?w0
        INCW      X
        AND       A, (X)
        LDW       X, S:?w0
        INCW      X
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GetITStatus:
        LD        S:?b2, A
        CLR       S:?b1
        CLR       S:?b3
        CLR       S:?b0
        LDW       Y, #0x5075
        LD        A, S:?b2
        AND       A, #0x10
        CP        A, #0x0
        JREQ      L:??DMA_GetITStatus_0
        LDW       X, #0x5075
        LDW       Y, X
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_0:
        LD        A, S:?b2
        AND       A, #0x20
        CP        A, #0x0
        JREQ      L:??DMA_GetITStatus_2
        LDW       X, #0x507f
        LDW       Y, X
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_2:
        LD        A, S:?b2
        AND       A, #0x40
        CP        A, #0x0
        JREQ      L:??DMA_GetITStatus_3
        LDW       X, #0x5089
        LDW       Y, X
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_3:
        LDW       X, #0x5093
        LDW       Y, X
??DMA_GetITStatus_1:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        LD        S:?b3, A
        LD        A, (Y)
        AND       A, S:?b3
        LD        S:?b3, A
        LD        A, S:?b2
        AND       A, #0x6
        LD        S:?b0, A
        LD        A, S:?b0
        AND       A, S:?b3
        LD        S:?b1, A
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_ClearITPendingBit:
        LD        S:?b0, A
        LDW       X, #0x5075
        LDW       Y, X
        LD        A, S:?b0
        AND       A, #0x10
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_0
        LDW       X, #0x5075
        LDW       Y, X
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_0:
        LD        A, S:?b0
        AND       A, #0x20
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_2
        LDW       X, #0x507f
        LDW       Y, X
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_2:
        LD        A, S:?b0
        AND       A, #0x40
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_3
        LDW       X, #0x5089
        LDW       Y, X
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_3:
        LDW       X, #0x5093
        LDW       Y, X
??DMA_ClearITPendingBit_1:
        LD        A, S:?b0
        AND       A, #0x6
        CPL       A
        LDW       X, Y
        INCW      X
        AND       A, (X)
        LDW       X, Y
        INCW      X
        LD        (X), A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 658 bytes in section .near_func.text
// 
// 658 bytes of CODE memory
//
//Errors: none
//Warnings: none
