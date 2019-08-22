///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:24
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_usart.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWD894.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_usart.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_usart.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b10
        EXTERN ?b11
        EXTERN ?b14
        EXTERN ?b15
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?b7
        EXTERN ?epilogue_l2_l3
        EXTERN ?load32_l1_dbsp
        EXTERN ?mov_l3_l0
        EXTERN ?push_l0
        EXTERN ?push_l2
        EXTERN ?push_l3
        EXTERN ?sll16_x_x_a
        EXTERN ?srl16_x_x_4
        EXTERN ?udiv32_l0_l0_l1
        EXTERN ?w0
        EXTERN ?w4
        EXTERN ?w6
        EXTERN ?w7
        EXTERN CLK_GetClockFreq

        PUBLIC USART_ClearFlag
        PUBLIC USART_ClearITPendingBit
        PUBLIC USART_ClockInit
        PUBLIC USART_Cmd
        PUBLIC USART_DMACmd
        PUBLIC USART_DeInit
        PUBLIC USART_GetFlagStatus
        PUBLIC USART_GetITStatus
        PUBLIC USART_HalfDuplexCmd
        PUBLIC USART_ITConfig
        PUBLIC USART_Init
        PUBLIC USART_IrDACmd
        PUBLIC USART_IrDAConfig
        PUBLIC USART_ReceiveData8
        PUBLIC USART_ReceiveData9
        PUBLIC USART_ReceiverWakeUpCmd
        PUBLIC USART_SendBreak
        PUBLIC USART_SendData8
        PUBLIC USART_SendData9
        PUBLIC USART_SetAddress
        PUBLIC USART_SetGuardTime
        PUBLIC USART_SetPrescaler
        PUBLIC USART_SmartCardCmd
        PUBLIC USART_SmartCardNACKCmd
        PUBLIC USART_WakeUpConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_DeInit:
        LDW       Y, X
        LD        A, (Y)
        LD        S:?b0, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x4
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x5
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x6
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x7
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_Init:
        CALL      L:?push_l2
        CALL      L:?push_l3
        CALL      L:?push_l0
        LDW       S:?w4, X
        LD        S:?b0, A
        MOV       S:?b11, S:?b6
        CLRW      X
        LDW       S:?w7, X
        LDW       S:?w6, X
        LDW       X, S:?w4
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, #0xe9
        LDW       X, S:?w4
        ADDW      X, #0x4
        LD        (X), A
        LD        A, S:?b5
        OR        A, S:?b0
        LDW       X, S:?w4
        ADDW      X, #0x4
        OR        A, (X)
        LDW       X, S:?w4
        ADDW      X, #0x4
        LD        (X), A
        LDW       X, S:?w4
        ADDW      X, #0x6
        LD        A, (X)
        AND       A, #0xcf
        LDW       X, S:?w4
        ADDW      X, #0x6
        LD        (X), A
        LDW       X, S:?w4
        ADDW      X, #0x6
        LD        A, (X)
        OR        A, S:?b4
        LDW       X, S:?w4
        ADDW      X, #0x6
        LD        (X), A
        LDW       X, S:?w4
        INCW      X
        INCW      X
        LD        A, (X)
        LD        S:?b10, A
        LDW       X, S:?w4
        INCW      X
        INCW      X
        CLR       (X)
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        A, (X)
        AND       A, #0xf
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        (X), A
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        A, (X)
        AND       A, #0xf0
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        (X), A
        CALL      L:CLK_GetClockFreq
        CALL      L:?load32_l1_dbsp
        DATA
        DC8       0x1
        CODE
        CALL      L:?udiv32_l0_l0_l1
        CALL      L:?mov_l3_l0
        LD        A, S:?b14
        AND       A, #0xf0
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        (X), A
        LD        A, S:?b15
        AND       A, #0xf
        LDW       X, S:?w4
        ADDW      X, #0x3
        OR        A, (X)
        LDW       X, S:?w4
        ADDW      X, #0x3
        LD        (X), A
        LDW       X, S:?w7
        CALL      L:?srl16_x_x_4
        LD        A, XL
        LDW       X, S:?w4
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, S:?w4
        ADDW      X, #0x5
        LD        A, (X)
        AND       A, #0xf3
        LDW       X, S:?w4
        ADDW      X, #0x5
        LD        (X), A
        LDW       X, S:?w4
        ADDW      X, #0x5
        LD        A, (X)
        OR        A, S:?b11
        LDW       X, S:?w4
        ADDW      X, #0x5
        LD        (X), A
        ADD       SP, #0x4
        JP        L:?epilogue_l2_l3

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ClockInit:
        LD        S:?b3, A
        LDW       Y, X
        ADDW      Y, #0x6
        LD        A, (Y)
        AND       A, #0xf8
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        LD        A, S:?b1
        OR        A, S:?b0
        OR        A, S:?b2
        LDW       Y, X
        ADDW      Y, #0x6
        OR        A, (Y)
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        TNZ       S:?b3
        JREQ      L:??USART_ClockInit_0
        LDW       Y, X
        ADDW      Y, #0x6
        LD        A, (Y)
        OR        A, #0x8
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        RET
??USART_ClockInit_0:
        LDW       Y, X
        ADDW      Y, #0x6
        LD        A, (Y)
        AND       A, #0xf7
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_Cmd:
        TNZ       A
        JREQ      L:??USART_Cmd_0
        LDW       Y, X
        ADDW      Y, #0x4
        LD        A, (Y)
        AND       A, #0xdf
        ADDW      X, #0x4
        LD        (X), A
        SUBW      X, #0x4
        RET
??USART_Cmd_0:
        LDW       Y, X
        ADDW      Y, #0x4
        LD        A, (Y)
        OR        A, #0x20
        ADDW      X, #0x4
        LD        (X), A
        SUBW      X, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SetPrescaler:
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SendBreak:
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        OR        A, #0x1
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ReceiveData8:
        INCW      X
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ReceiveData9:
        LDW       Y, X
        CLR       S:?b1
        CLR       S:?b0
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        CLRW      X
        LD        XL, A
        SLLW      X
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        LDW       S:?w0, X
        INCW      Y
        LD        A, (Y)
        CLRW      X
        LD        XL, A
        RRWA      X, A
        OR        A, S:?b1
        RRWA      X, A
        OR        A, S:?b0
        RRWA      X, A
        RLWA      X, A
        AND       A, #0x1
        RLWA      X, A
        AND       A, #0xff
        RLWA      X, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SendData8:
        INCW      X
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SendData9:
        LDW       S:?w0, X
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, #0xbf
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        (X), A
        LDW       X, Y
        SRLW      X
        SRLW      X
        LD        A, XL
        AND       A, #0x40
        LDW       X, S:?w0
        ADDW      X, #0x4
        OR        A, (X)
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        (X), A
        LDW       X, S:?w0
        INCW      X
        LDW       S:?w0, X
        LD        A, YL
        LD        [S:?w0.w], A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ReceiverWakeUpCmd:
        TNZ       A
        JREQ      L:??USART_ReceiverWakeUpCmd_0
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        OR        A, #0x2
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET
??USART_ReceiverWakeUpCmd_0:
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        AND       A, #0xfd
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SetAddress:
        LD        S:?b0, A
        LDW       Y, X
        ADDW      Y, #0x7
        LD        A, (Y)
        AND       A, #0xf0
        ADDW      X, #0x7
        LD        (X), A
        SUBW      X, #0x7
        LDW       Y, X
        ADDW      Y, #0x7
        LD        A, (Y)
        OR        A, S:?b0
        ADDW      X, #0x7
        LD        (X), A
        SUBW      X, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_WakeUpConfig:
        LD        S:?b0, A
        LDW       Y, X
        ADDW      Y, #0x4
        LD        A, (Y)
        AND       A, #0xf7
        ADDW      X, #0x4
        LD        (X), A
        SUBW      X, #0x4
        LDW       Y, X
        ADDW      Y, #0x4
        LD        A, (Y)
        OR        A, S:?b0
        ADDW      X, #0x4
        LD        (X), A
        SUBW      X, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_HalfDuplexCmd:
        TNZ       A
        JREQ      L:??USART_HalfDuplexCmd_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, #0x8
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_HalfDuplexCmd_0:
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0xf7
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SmartCardCmd:
        TNZ       A
        JREQ      L:??USART_SmartCardCmd_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, #0x20
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_SmartCardCmd_0:
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0xdf
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SmartCardNACKCmd:
        TNZ       A
        JREQ      L:??USART_SmartCardNACKCmd_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, #0x10
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_SmartCardNACKCmd_0:
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0xef
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_SetGuardTime:
        ADDW      X, #0x9
        LD        (X), A
        SUBW      X, #0x9
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_IrDAConfig:
        TNZ       A
        JREQ      L:??USART_IrDAConfig_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, #0x4
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_IrDAConfig_0:
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0xfb
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_IrDACmd:
        TNZ       A
        JREQ      L:??USART_IrDACmd_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, #0x2
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_IrDACmd_0:
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0xfd
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_DMACmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??USART_DMACmd_0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        OR        A, S:?b1
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET
??USART_DMACmd_0:
        LDW       Y, X
        ADDW      Y, #0x8
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, (Y)
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ITConfig:
        LDW       S:?w0, X
        LD        S:?b3, A
        CLR       S:?b4
        RLWA      Y, A
        LD        S:?b2, A
        RRWA      Y, A
        LD        A, YL
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b4, A
        TNZ       S:?b3
        JREQ      L:??USART_ITConfig_0
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??USART_ITConfig_1
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        A, (X)
        OR        A, S:?b4
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        (X), A
        RET
??USART_ITConfig_1:
        LD        A, S:?b2
        CP        A, #0x5
        JRNE      L:??USART_ITConfig_2
        LDW       X, S:?w0
        ADDW      X, #0x8
        LD        A, (X)
        OR        A, S:?b4
        LDW       X, S:?w0
        ADDW      X, #0x8
        LD        (X), A
        RET
??USART_ITConfig_2:
        LDW       X, S:?w0
        ADDW      X, #0x5
        LD        A, (X)
        OR        A, S:?b4
        LDW       X, S:?w0
        ADDW      X, #0x5
        LD        (X), A
        RET
??USART_ITConfig_0:
        LD        A, S:?b2
        CP        A, #0x1
        JRNE      L:??USART_ITConfig_3
        LDW       X, S:?w0
        ADDW      X, #0x4
        CPL       S:?b4
        LD        A, S:?b4
        AND       A, (X)
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        (X), A
        RET
??USART_ITConfig_3:
        LD        A, S:?b2
        CP        A, #0x5
        JRNE      L:??USART_ITConfig_4
        LDW       X, S:?w0
        ADDW      X, #0x8
        CPL       S:?b4
        LD        A, S:?b4
        AND       A, (X)
        LDW       X, S:?w0
        ADDW      X, #0x8
        LD        (X), A
        RET
??USART_ITConfig_4:
        LDW       X, S:?w0
        ADDW      X, #0x5
        CPL       S:?b4
        LD        A, S:?b4
        AND       A, (X)
        LDW       X, S:?w0
        ADDW      X, #0x5
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_GetFlagStatus:
        CLR       A
        CPW       Y, #0x101
        JRNE      L:??USART_GetFlagStatus_0
        ADDW      X, #0x5
        LD        A, YL
        AND       A, (X)
        CP        A, #0x0
        JREQ      L:??USART_GetFlagStatus_1
        LD        A, #0x1
        RET
??USART_GetFlagStatus_1:
        CLR       A
        RET
??USART_GetFlagStatus_0:
        LD        A, YL
        AND       A, (X)
        CP        A, #0x0
        JREQ      L:??USART_GetFlagStatus_2
        LD        A, #0x1
        RET
??USART_GetFlagStatus_2:
        CLR       A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ClearFlag:
        LD        A, YL
        CPL       A
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_GetITStatus:
        LDW       S:?w0, X
        CLR       S:?b2
        CLR       S:?b4
        CLR       S:?b7
        CLR       S:?b5
        CLR       S:?b6
        CLR       S:?b3
        LD        A, YL
        AND       A, #0xf
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b7, A
        LD        A, YL
        SWAP      A
        AND       A, #0xf
        LD        S:?b5, A
        CLRW      X
        INCW      X
        LD        A, S:?b5
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b6, A
        CPW       Y, #0x100
        JRNE      L:??USART_GetITStatus_0
        LDW       X, S:?w0
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, S:?b6
        LD        S:?b3, A
        LD        A, [S:?w0.w]
        AND       A, S:?b7
        CP        A, #0x0
        JREQ      L:??USART_GetITStatus_1
        TNZ       S:?b3
        JREQ      L:??USART_GetITStatus_1
        MOV       S:?b2, #0x1
        JRA       L:??USART_GetITStatus_2
??USART_GetITStatus_1:
        CLR       S:?b2
        JRA       L:??USART_GetITStatus_2
??USART_GetITStatus_0:
        CPW       Y, #0x235
        JRNE      L:??USART_GetITStatus_3
        LDW       X, S:?w0
        ADDW      X, #0x5
        LD        A, (X)
        AND       A, S:?b6
        LD        S:?b3, A
        LDW       X, S:?w0
        ADDW      X, #0x8
        LD        A, (X)
        AND       A, #0x1
        LD        S:?b4, A
        LD        A, [S:?w0.w]
        AND       A, S:?b7
        CP        A, #0x0
        JREQ      L:??USART_GetITStatus_4
        TNZ       S:?b3
        JRNE      L:??USART_GetITStatus_5
        TNZ       S:?b4
        JREQ      L:??USART_GetITStatus_4
??USART_GetITStatus_5:
        MOV       S:?b2, #0x1
        JRA       L:??USART_GetITStatus_2
??USART_GetITStatus_4:
        CLR       S:?b2
        JRA       L:??USART_GetITStatus_2
??USART_GetITStatus_3:
        LDW       X, S:?w0
        ADDW      X, #0x5
        LD        A, (X)
        AND       A, S:?b6
        LD        S:?b3, A
        LD        A, [S:?w0.w]
        AND       A, S:?b7
        CP        A, #0x0
        JREQ      L:??USART_GetITStatus_6
        TNZ       S:?b3
        JREQ      L:??USART_GetITStatus_6
        MOV       S:?b2, #0x1
        JRA       L:??USART_GetITStatus_2
??USART_GetITStatus_6:
        CLR       S:?b2
??USART_GetITStatus_2:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
USART_ClearITPendingBit:
        LD        A, (X)
        AND       A, #0xbf
        LD        (X), A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 1 202 bytes in section .near_func.text
// 
// 1 202 bytes of CODE memory
//
//Errors: none
//Warnings: none
