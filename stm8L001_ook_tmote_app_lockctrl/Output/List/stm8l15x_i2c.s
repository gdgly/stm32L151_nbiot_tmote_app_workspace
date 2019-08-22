///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:20
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_i2c.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC74D.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_i2c.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_i2c.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b11
        EXTERN ?b14
        EXTERN ?b15
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?epilogue_l2_l3
        EXTERN ?load32_l0_dbsp
        EXTERN ?mov_l1_l2
        EXTERN ?mov_l2_l0
        EXTERN ?mul16_x_x_w0
        EXTERN ?mul32_l0_l0_dl
        EXTERN ?push_l0
        EXTERN ?push_l2
        EXTERN ?push_l3
        EXTERN ?sdiv16_x_x_y
        EXTERN ?sll32_l0_l0_a
        EXTERN ?srl16_x_x_7
        EXTERN ?udiv32_l0_l0_dl
        EXTERN ?udiv32_l0_l0_l1
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w4
        EXTERN ?w5
        EXTERN ?w6
        EXTERN ?w7
        EXTERN CLK_GetClockFreq

        PUBLIC I2C_ARPCmd
        PUBLIC I2C_AckPositionConfig
        PUBLIC I2C_AcknowledgeConfig
        PUBLIC I2C_CalculatePEC
        PUBLIC I2C_CheckEvent
        PUBLIC I2C_ClearFlag
        PUBLIC I2C_ClearITPendingBit
        PUBLIC I2C_Cmd
        PUBLIC I2C_DMACmd
        PUBLIC I2C_DMALastTransferCmd
        PUBLIC I2C_DeInit
        PUBLIC I2C_DualAddressCmd
        PUBLIC I2C_FastModeDutyCycleConfig
        PUBLIC I2C_GeneralCallCmd
        PUBLIC I2C_GenerateSTART
        PUBLIC I2C_GenerateSTOP
        PUBLIC I2C_GetFlagStatus
        PUBLIC I2C_GetITStatus
        PUBLIC I2C_GetLastEvent
        PUBLIC I2C_GetPEC
        PUBLIC I2C_ITConfig
        PUBLIC I2C_Init
        PUBLIC I2C_OwnAddress2Config
        PUBLIC I2C_PECPositionConfig
        PUBLIC I2C_ReadRegister
        PUBLIC I2C_ReceiveData
        PUBLIC I2C_SMBusAlertConfig
        PUBLIC I2C_Send7bitAddress
        PUBLIC I2C_SendData
        PUBLIC I2C_SoftwareResetCmd
        PUBLIC I2C_StretchClockCmd
        PUBLIC I2C_TransmitPEC


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_DeInit:
        LDW       Y, X
        CLR       (Y)
        LDW       X, Y
        INCW      X
        CLR       (X)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x4
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x5
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0xa
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0xb
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0xc
        CLR       (X)
        LD        A, #0x2
        LDW       X, Y
        ADDW      X, #0xd
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_Init:
        CALL      L:?push_l2
        CALL      L:?push_l3
        CALL      L:?push_l0
        PUSHW     Y
        PUSH      A
        PUSH      S:?b5
        PUSH      S:?b6
        SUB       SP, #0x3
        LDW       S:?w6, X
        MOV       S:?b14, S:?b4
        LDW       X, #0x4
        LDW       S:?w5, X
        CLRW      X
        LDW       S:?w4, X
        CLRW      X
        LDW       (0x2,SP), X
        CLR       (0x1,SP)
        CLR       S:?b15
        CALL      L:CLK_GetClockFreq
        CALL      L:?udiv32_l0_l0_dl
        DATA
        DC32      0xf4240
        CODE
        MOV       S:?b15, S:?b3
        LDW       X, S:?w6
        INCW      X
        INCW      X
        LD        A, (X)
        AND       A, #0xc0
        LDW       X, S:?w6
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, S:?w6
        INCW      X
        INCW      X
        LD        A, (X)
        OR        A, S:?b15
        LDW       X, S:?w6
        INCW      X
        INCW      X
        LD        (X), A
        LD        A, [S:?w6.w]
        AND       A, #0xfe
        LD        [S:?w6.w], A
        LDW       X, S:?w6
        ADDW      X, #0xc
        LD        A, (X)
        AND       A, #0x30
        LDW       X, S:?w6
        ADDW      X, #0xc
        LD        (X), A
        LDW       X, S:?w6
        ADDW      X, #0xb
        LD        A, (X)
        LD        S:?b4, A
        LDW       X, S:?w6
        ADDW      X, #0xb
        CLR       (X)
        CALL      L:?load32_l0_dbsp
        DATA
        DC8       0x9
        CODE
        LDW       X, S:?w0
        CPW       X, #0x1
        JRNE      L:??I2C_Init_0
        LDW       X, S:?w1
        CPW       X, #0x86a1
??I2C_Init_0:
        JRNC      ??lb_0
        JP        L:??I2C_Init_1
??lb_0:
        LD        A, #0x80
        LD        (0x1,SP), A
        TNZ       S:?b14
        JRNE      L:??I2C_Init_2
        CALL      L:?load32_l0_dbsp
        DATA
        DC8       0x9
        CODE
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0x3
        CODE
        CALL      L:?mov_l2_l0
        CLRW      X
        LD        A, S:?b15
        LD        XL, A
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0xf4240
        CODE
        CALL      L:?mov_l1_l2
        CALL      L:?udiv32_l0_l0_l1
        CALL      L:?mov_l2_l0
        JRA       L:??I2C_Init_3
??I2C_Init_2:
        CALL      L:?load32_l0_dbsp
        DATA
        DC8       0x9
        CODE
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0x19
        CODE
        CALL      L:?mov_l2_l0
        CLRW      X
        LD        A, S:?b15
        LD        XL, A
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0xf4240
        CODE
        CALL      L:?mov_l1_l2
        CALL      L:?udiv32_l0_l0_l1
        CALL      L:?mov_l2_l0
        LD        A, (0x1,SP)
        OR        A, #0x40
        LD        (0x1,SP), A
??I2C_Init_3:
        LDW       X, S:?w4
        CPW       X, #0x0
        JRNE      L:??I2C_Init_4
        LDW       X, S:?w5
        CPW       X, #0x0
??I2C_Init_4:
        JRNE      L:??I2C_Init_5
        CLRW      X
        LDW       S:?w4, X
        INCW      X
        LDW       S:?w5, X
??I2C_Init_5:
        CLR       S:?b14
        LDW       X, #0x3
        LDW       S:?w0, X
        LDW       X, S:?w7
        CALL      L:?mul16_x_x_w0
        LDW       Y, #0xa
        CALL      L:?sdiv16_x_x_y
        INCW      X
        LDW       (0x2,SP), X
        LD        A, (0x3,SP)
        LDW       X, S:?w6
        ADDW      X, #0xd
        LD        (X), A
        JRA       L:??I2C_Init_6
??I2C_Init_1:
        CALL      L:?load32_l0_dbsp
        DATA
        DC8       0x9
        CODE
        LD        A, #0x1
        CALL      L:?sll32_l0_l0_a
        CALL      L:?mov_l2_l0
        CLRW      X
        LD        A, S:?b15
        LD        XL, A
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0xf4240
        CODE
        CALL      L:?mov_l1_l2
        CALL      L:?udiv32_l0_l0_l1
        LDW       X, S:?w1
        LDW       S:?w5, X
        CLRW      X
        LDW       S:?w4, X
        LDW       X, S:?w4
        CPW       X, #0x0
        JRNE      L:??I2C_Init_7
        LDW       X, S:?w5
        CPW       X, #0x4
??I2C_Init_7:
        JRNC      L:??I2C_Init_8
        LDW       X, #0x4
        LDW       S:?w5, X
        CLRW      X
        LDW       S:?w4, X
??I2C_Init_8:
        INC       S:?b15
        LD        A, S:?b15
        LDW       X, S:?w6
        ADDW      X, #0xd
        LD        (X), A
??I2C_Init_6:
        LD        A, S:?b11
        LDW       X, S:?w6
        ADDW      X, #0xb
        LD        (X), A
        LD        A, (0x1,SP)
        LDW       X, S:?w6
        ADDW      X, #0xc
        LD        (X), A
        LD        A, (0x6,SP)
        OR        A, #0x1
        OR        A, [S:?w6.w]
        LD        [S:?w6.w], A
        LDW       X, S:?w6
        INCW      X
        LD        A, (0x5,SP)
        OR        A, (X)
        LDW       X, S:?w6
        INCW      X
        LD        (X), A
        LD        A, (0x8,SP)
        LDW       X, S:?w6
        ADDW      X, #0x3
        LD        (X), A
        LDW       X, (0x7,SP)
        CALL      L:?srl16_x_x_7
        LD        A, XL
        AND       A, #0x6
        PUSH      A
        LD        A, (0x5,SP)
        OR        A, #0x40
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LDW       X, S:?w6
        ADDW      X, #0x4
        LD        (X), A
        ADD       SP, #0xc
        JP        L:?epilogue_l2_l3

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_Cmd:
        TNZ       A
        JREQ      L:??I2C_Cmd_0
        LD        A, (X)
        OR        A, #0x1
        LD        (X), A
        RET
??I2C_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GeneralCallCmd:
        TNZ       A
        JREQ      L:??I2C_GeneralCallCmd_0
        LD        A, (X)
        OR        A, #0x40
        LD        (X), A
        RET
??I2C_GeneralCallCmd_0:
        LD        A, (X)
        AND       A, #0xbf
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GenerateSTART:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_GenerateSTART_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x1
        INCW      Y
        LD        (Y), A
        RET
??I2C_GenerateSTART_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xfe
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GenerateSTOP:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_GenerateSTOP_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x2
        INCW      Y
        LD        (Y), A
        RET
??I2C_GenerateSTOP_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xfd
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_SoftwareResetCmd:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_SoftwareResetCmd_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x80
        INCW      Y
        LD        (Y), A
        RET
??I2C_SoftwareResetCmd_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0x7f
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_StretchClockCmd:
        TNZ       A
        JREQ      L:??I2C_StretchClockCmd_0
        LD        A, (X)
        AND       A, #0x7f
        LD        (X), A
        RET
??I2C_StretchClockCmd_0:
        LD        A, (X)
        OR        A, #0x80
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ARPCmd:
        TNZ       A
        JREQ      L:??I2C_ARPCmd_0
        LD        A, (X)
        OR        A, #0x10
        LD        (X), A
        RET
??I2C_ARPCmd_0:
        LD        A, (X)
        AND       A, #0xef
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_AcknowledgeConfig:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_AcknowledgeConfig_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x4
        INCW      Y
        LD        (Y), A
        RET
??I2C_AcknowledgeConfig_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xfb
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_OwnAddress2Config:
        LD        S:?b0, A
        CLR       S:?b1
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x1
        LD        S:?b1, A
        LD        A, S:?b0
        AND       A, #0xfe
        OR        A, S:?b1
        LD        S:?b1, A
        LD        A, S:?b1
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_DualAddressCmd:
        TNZ       A
        JREQ      L:??I2C_DualAddressCmd_0
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        OR        A, #0x1
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET
??I2C_DualAddressCmd_0:
        LDW       Y, X
        ADDW      Y, #0x5
        LD        A, (Y)
        AND       A, #0xfe
        ADDW      X, #0x5
        LD        (X), A
        SUBW      X, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_AckPositionConfig:
        LDW       Y, X
        LD        S:?b0, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xf7
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, S:?b0
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_SMBusAlertConfig:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_SMBusAlertConfig_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x20
        INCW      Y
        LD        (Y), A
        RET
??I2C_SMBusAlertConfig_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xdf
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_FastModeDutyCycleConfig:
        CP        A, #0x40
        JRNE      L:??I2C_FastModeDutyCycleConfig_0
        LDW       Y, X
        ADDW      Y, #0xc
        LD        A, (Y)
        OR        A, #0x40
        ADDW      X, #0xc
        LD        (X), A
        SUBW      X, #0xc
        RET
??I2C_FastModeDutyCycleConfig_0:
        LDW       Y, X
        ADDW      Y, #0xc
        LD        A, (Y)
        AND       A, #0xbf
        ADDW      X, #0xc
        LD        (X), A
        SUBW      X, #0xc
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_Send7bitAddress:
        TNZ       S:?b0
        JREQ      L:??I2C_Send7bitAddress_0
        OR        A, #0x1
        JRA       L:??I2C_Send7bitAddress_1
??I2C_Send7bitAddress_0:
        AND       A, #0xfe
??I2C_Send7bitAddress_1:
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_SendData:
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ReceiveData:
        ADDW      X, #0x6
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_TransmitPEC:
        LDW       Y, X
        TNZ       A
        JREQ      L:??I2C_TransmitPEC_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, #0x10
        INCW      Y
        LD        (Y), A
        RET
??I2C_TransmitPEC_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xef
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_CalculatePEC:
        TNZ       A
        JREQ      L:??I2C_CalculatePEC_0
        LD        A, (X)
        OR        A, #0x20
        LD        (X), A
        RET
??I2C_CalculatePEC_0:
        LD        A, (X)
        AND       A, #0xdf
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_PECPositionConfig:
        LDW       Y, X
        LD        S:?b0, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xf7
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, S:?b0
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GetPEC:
        ADDW      X, #0xe
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_DMACmd:
        TNZ       A
        JREQ      L:??I2C_DMACmd_0
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        OR        A, #0x8
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET
??I2C_DMACmd_0:
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        AND       A, #0xf7
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_DMALastTransferCmd:
        TNZ       A
        JREQ      L:??I2C_DMALastTransferCmd_0
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        OR        A, #0x10
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET
??I2C_DMALastTransferCmd_0:
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        AND       A, #0xef
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ITConfig:
        LDW       S:?w0, X
        LDW       X, Y
        TNZ       A
        JREQ      L:??I2C_ITConfig_0
        LDW       Y, S:?w0
        ADDW      Y, #0xa
        LD        A, XL
        OR        A, (Y)
        LDW       X, S:?w0
        ADDW      X, #0xa
        LD        (X), A
        RET
??I2C_ITConfig_0:
        LDW       Y, S:?w0
        ADDW      Y, #0xa
        LD        A, XL
        CPL       A
        AND       A, (Y)
        LDW       X, S:?w0
        ADDW      X, #0xa
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ReadRegister:
        SUB       SP, #0x2
        CLRW      Y
        LDW       (0x1,SP), Y
        LDW       (0x1,SP), X
        CLRW      X
        LD        XL, A
        ADDW      X, (0x1,SP)
        LDW       (0x1,SP), X
        LDW       X, (0x1,SP)
        LD        A, (X)
        ADD       SP, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_CheckEvent:
        SUB       SP, #0x2
        LDW       S:?w0, X
        LDW       S:?w2, Y
        CLRW      X
        LDW       (0x1,SP), X
        CLR       S:?b3
        CLR       A
        CLR       S:?b2
        LDW       X, S:?w2
        CPW       X, #0x4
        JRNE      L:??I2C_CheckEvent_0
        LDW       X, S:?w0
        ADDW      X, #0x8
        LD        A, (X)
        AND       A, #0x4
        CLRW      X
        LD        XL, A
        LDW       (0x1,SP), X
        JRA       L:??I2C_CheckEvent_1
??I2C_CheckEvent_0:
        LDW       X, S:?w0
        ADDW      X, #0x7
        LD        A, (X)
        LD        S:?b3, A
        LDW       X, S:?w0
        ADDW      X, #0x9
        LD        A, (X)
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        CLR       S:?b2
        RRWA      X, A
        OR        A, S:?b3
        RRWA      X, A
        OR        A, S:?b2
        RRWA      X, A
        LDW       (0x1,SP), X
??I2C_CheckEvent_1:
        LDW       X, (0x1,SP)
        RRWA      X, A
        AND       A, S:?b5
        RRWA      X, A
        AND       A, S:?b4
        RRWA      X, A
        CPW       X, S:?w2
        JRNE      L:??I2C_CheckEvent_2
        MOV       S:?b2, #0x1
        JRA       L:??I2C_CheckEvent_3
??I2C_CheckEvent_2:
        CLR       S:?b2
??I2C_CheckEvent_3:
        LD        A, S:?b2
        ADD       SP, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GetLastEvent:
        SUB       SP, #0x2
        CLRW      Y
        LDW       (0x1,SP), Y
        CLR       S:?b3
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LDW       Y, X
        ADDW      Y, #0x8
        LD        A, (Y)
        AND       A, #0x4
        CP        A, #0x0
        JREQ      L:??I2C_GetLastEvent_0
        LDW       X, #0x4
        LDW       (0x1,SP), X
        JRA       L:??I2C_GetLastEvent_1
??I2C_GetLastEvent_0:
        LDW       Y, X
        ADDW      Y, #0x7
        LD        A, (Y)
        CLR       S:?b2
        LD        S:?b3, A
        ADDW      X, #0x9
        LD        A, (X)
        CLR       S:?b0
        LD        S:?b1, A
        LDW       X, S:?w0
        CLR       A
        RLWA      X, A
        RRWA      X, A
        OR        A, S:?b3
        RRWA      X, A
        OR        A, S:?b2
        RRWA      X, A
        LDW       (0x1,SP), X
??I2C_GetLastEvent_1:
        LDW       X, (0x1,SP)
        ADD       SP, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GetFlagStatus:
        CLR       S:?b2
        CLR       A
        CLR       S:?b1
        RLWA      Y, A
        LD        S:?b0, A
        RRWA      Y, A
        LD        A, S:?b0
        DEC       A
        JREQ      L:??I2C_GetFlagStatus_0
        DEC       A
        JREQ      L:??I2C_GetFlagStatus_1
        DEC       A
        JREQ      L:??I2C_GetFlagStatus_2
        JRA       L:??I2C_GetFlagStatus_3
??I2C_GetFlagStatus_0:
        ADDW      X, #0x7
        LD        A, (X)
        LD        S:?b2, A
        JRA       L:??I2C_GetFlagStatus_3
??I2C_GetFlagStatus_1:
        ADDW      X, #0x8
        LD        A, (X)
        LD        S:?b2, A
        JRA       L:??I2C_GetFlagStatus_3
??I2C_GetFlagStatus_2:
        ADDW      X, #0x9
        LD        A, (X)
        LD        S:?b2, A
??I2C_GetFlagStatus_3:
        LD        A, YL
        AND       A, S:?b2
        CP        A, #0x0
        JREQ      L:??I2C_GetFlagStatus_4
        MOV       S:?b1, #0x1
        JRA       L:??I2C_GetFlagStatus_5
??I2C_GetFlagStatus_4:
        CLR       S:?b1
??I2C_GetFlagStatus_5:
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ClearFlag:
        CLR       S:?b1
        CLR       S:?b0
        RLWA      Y, A
        AND       A, #0x0
        RLWA      Y, A
        AND       A, #0xff
        RLWA      Y, A
        LDW       S:?w0, Y
        LD        A, S:?b1
        CPL       A
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_GetITStatus:
        SUB       SP, #0x1
        LDW       S:?w1, X
        LDW       X, Y
        CLR       S:?b4
        CLR       (0x1,SP)
        CLR       S:?b1
        CLR       S:?b0
        LD        A, XH
        AND       A, #0x7
        CLRW      Y
        LD        YL, A
        LDW       S:?w0, Y
        LDW       Y, S:?w1
        ADDW      Y, #0xa
        LD        A, S:?b1
        AND       A, (Y)
        LD        (0x1,SP), A
        LDW       Y, S:?w1
        ADDW      Y, #0x8
        LD        A, XL
        AND       A, (Y)
        CP        A, #0x0
        JREQ      L:??I2C_GetITStatus_0
        TNZ       (0x1,SP)
        JREQ      L:??I2C_GetITStatus_0
        MOV       S:?b4, #0x1
        JRA       L:??I2C_GetITStatus_1
??I2C_GetITStatus_0:
        CLR       S:?b4
??I2C_GetITStatus_1:
        LD        A, S:?b4
        ADD       SP, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
I2C_ClearITPendingBit:
        CLR       S:?b1
        CLR       S:?b0
        RLWA      Y, A
        AND       A, #0x0
        RLWA      Y, A
        AND       A, #0xff
        RLWA      Y, A
        LDW       S:?w0, Y
        LD        A, S:?b1
        CPL       A
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 1 379 bytes in section .near_func.text
// 
// 1 379 bytes of CODE memory
//
//Errors: none
//Warnings: none
