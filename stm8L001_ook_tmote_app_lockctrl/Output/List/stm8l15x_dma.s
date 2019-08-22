///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:18
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dma.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC41D.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dma.c
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
        EXTERN ?w0
        EXTERN ?w2

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
        INCW      Y
        CLR       (Y)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_Init:
        PUSH      S:?b8
        LD        S:?b8, A
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        CLR       (X)
        LD        A, S:?b5
        OR        A, S:?b4
        OR        A, S:?b6
        OR        A, (X)
        LD        (X), A
        LDW       S:?w2, X
        PUSHW     X
        LDW       X, S:?w2
        INCW      X
        LDW       S:?w2, X
        POPW      X
        LD        A, [S:?w2.w]
        AND       A, #0xc7
        LDW       S:?w2, X
        PUSHW     X
        LDW       X, S:?w2
        INCW      X
        LDW       S:?w2, X
        POPW      X
        LD        [S:?w2.w], A
        LD        A, (0x4,SP)
        OR        A, S:?b7
        LDW       S:?w2, X
        PUSHW     X
        LDW       X, S:?w2
        INCW      X
        LDW       S:?w2, X
        POPW      X
        OR        A, [S:?w2.w]
        LDW       S:?w2, X
        PUSHW     X
        LDW       X, S:?w2
        INCW      X
        LDW       S:?w2, X
        POPW      X
        LD        [S:?w2.w], A
        LDW       S:?w2, X
        PUSHW     X
        LDW       X, S:?w2
        INCW      X
        INCW      X
        LDW       S:?w2, X
        POPW      X
        LD        A, S:?b8
        LD        [S:?w2.w], A
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
        POP       S:?b8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GlobalCmd:
        TNZ       A
        JREQ      L:??DMA_GlobalCmd_0
        BSET      L:0x5070, #0x0
        RET
??DMA_GlobalCmd_0:
        BRES      L:0x5070, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_Cmd:
        TNZ       A
        JREQ      L:??DMA_Cmd_0
        LD        A, (X)
        OR        A, #0x1
        LD        (X), A
        RET
??DMA_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_SetTimeOut:
        CLR       L:0x5070
        SLL       A
        SLL       A
        LD        L:0x5070, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_SetCurrDataCounter:
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
        RET
??DMA_ITConfig_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, (X)
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_GetFlagStatus:
        LDW       S:?w0, X
        CLR       A
        LDW       X, #0x5075
        CLR       S:?b4
        CLR       S:?b2
        MOV       S:?b3, L:0x5070
        MOV       S:?b2, S:?b3
        MOV       S:?b3, L:0x5071
        MOV       S:?b4, S:?b3
        LDW       Y, S:?w0
        RLWA      Y, A
        AND       A, #0xf
        RLWA      Y, A
        AND       A, #0x0
        RLWA      Y, A
        TNZW      Y
        JREQ      L:??DMA_GetFlagStatus_0
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_1
        LDW       X, #0x5075
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_1:
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x2
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_3
        LDW       X, #0x507f
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_3:
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x4
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_4
        LDW       X, #0x5089
        JRA       L:??DMA_GetFlagStatus_2
??DMA_GetFlagStatus_4:
        LDW       X, #0x5093
??DMA_GetFlagStatus_2:
        INCW      X
        LD        A, S:?b1
        AND       A, (X)
        RET
??DMA_GetFlagStatus_0:
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x10
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_GetFlagStatus_5
        LD        A, S:?b1
        AND       A, S:?b4
        RET
??DMA_GetFlagStatus_5:
        LD        A, S:?b2
        AND       A, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DMA_ClearFlag:
        LDW       S:?w0, X
        LDW       X, #0x5075
        LDW       Y, X
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_0
        LDW       X, #0x5075
        LDW       Y, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_0:
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x2
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_2
        LDW       X, #0x507f
        LDW       Y, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_2:
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0x4
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        TNZW      X
        JREQ      L:??DMA_ClearFlag_3
        LDW       X, #0x5089
        LDW       Y, X
        JRA       L:??DMA_ClearFlag_1
??DMA_ClearFlag_3:
        LDW       X, #0x5093
        LDW       Y, X
??DMA_ClearFlag_1:
        LD        A, S:?b1
        AND       A, #0x6
        CPL       A
        LDW       X, Y
        INCW      X
        AND       A, (X)
        INCW      Y
        LD        (Y), A
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
        LDW       Y, #0x5075
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_0:
        LD        A, S:?b2
        AND       A, #0x20
        CP        A, #0x0
        JREQ      L:??DMA_GetITStatus_2
        LDW       Y, #0x507f
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_2:
        LD        A, S:?b2
        AND       A, #0x40
        CP        A, #0x0
        JREQ      L:??DMA_GetITStatus_3
        LDW       Y, #0x5089
        JRA       L:??DMA_GetITStatus_1
??DMA_GetITStatus_3:
        LDW       Y, #0x5093
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
        LDW       Y, #0x5075
        LD        A, S:?b0
        AND       A, #0x10
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_0
        LDW       Y, #0x5075
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_0:
        LD        A, S:?b0
        AND       A, #0x20
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_2
        LDW       Y, #0x507f
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_2:
        LD        A, S:?b0
        AND       A, #0x40
        CP        A, #0x0
        JREQ      L:??DMA_ClearITPendingBit_3
        LDW       Y, #0x5089
        JRA       L:??DMA_ClearITPendingBit_1
??DMA_ClearITPendingBit_3:
        LDW       Y, #0x5093
??DMA_ClearITPendingBit_1:
        LD        A, S:?b0
        AND       A, #0x6
        CPL       A
        LDW       X, Y
        INCW      X
        AND       A, (X)
        INCW      Y
        LD        (Y), A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 628 bytes in section .near_func.text
// 
// 628 bytes of CODE memory
//
//Errors: none
//Warnings: none
