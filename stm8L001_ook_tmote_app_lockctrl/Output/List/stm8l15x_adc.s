///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:17
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_adc.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWBF93.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_adc.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_adc.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?sll8_a_a_5
        EXTERN ?w0
        EXTERN ?w1

        PUBLIC ADC_AnalogWatchdogChannelSelect
        PUBLIC ADC_AnalogWatchdogConfig
        PUBLIC ADC_AnalogWatchdogThresholdsConfig
        PUBLIC ADC_ChannelCmd
        PUBLIC ADC_ClearFlag
        PUBLIC ADC_ClearITPendingBit
        PUBLIC ADC_Cmd
        PUBLIC ADC_DMACmd
        PUBLIC ADC_DeInit
        PUBLIC ADC_ExternalTrigConfig
        PUBLIC ADC_GetConversionValue
        PUBLIC ADC_GetFlagStatus
        PUBLIC ADC_GetITStatus
        PUBLIC ADC_ITConfig
        PUBLIC ADC_Init
        PUBLIC ADC_SamplingTimeConfig
        PUBLIC ADC_SchmittTriggerConfig
        PUBLIC ADC_SoftwareStartConv
        PUBLIC ADC_TempSensorCmd
        PUBLIC ADC_VrefintCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_DeInit:
        LDW       Y, X
        CLR       (Y)
        LDW       X, Y
        INCW      X
        CLR       (X)
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, #0x1f
        LD        (X), A
        LD        A, #0xff
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        LD        A, #0xf
        LDW       X, Y
        ADDW      X, #0x6
        LD        (X), A
        LD        A, #0xff
        LDW       X, Y
        ADDW      X, #0x7
        LD        (X), A
        LDW       X, Y
        ADDW      X, #0x8
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x9
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
        LDW       X, Y
        ADDW      X, #0xd
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0xe
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0xf
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x10
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x11
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_Init:
        LDW       Y, X
        LD        S:?b2, A
        LD        A, (Y)
        AND       A, #0x9b
        LD        (Y), A
        LD        A, S:?b0
        OR        A, S:?b2
        OR        A, (Y)
        LD        (Y), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0x7f
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        OR        A, S:?b1
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_Cmd:
        TNZ       A
        JREQ      L:??ADC_Cmd_0
        LD        A, (X)
        OR        A, #0x1
        LD        (X), A
        RET
??ADC_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_SoftwareStartConv:
        LD        A, (X)
        OR        A, #0x2
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_ExternalTrigConfig:
        LDW       Y, X
        LD        S:?b1, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0x87
        LDW       X, Y
        INCW      X
        LD        (X), A
        LD        A, S:?b1
        OR        A, S:?b0
        LDW       X, Y
        INCW      X
        OR        A, (X)
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_AnalogWatchdogChannelSelect:
        LDW       Y, X
        LD        S:?b0, A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        AND       A, #0xe0
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        OR        A, S:?b0
        INCW      Y
        INCW      Y
        LD        (Y), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_AnalogWatchdogThresholdsConfig:
        LD        A, YH
        ADDW      X, #0x6
        LD        (X), A
        SUBW      X, #0x6
        LD        A, YL
        ADDW      X, #0x7
        LD        (X), A
        SUBW      X, #0x7
        LD        A, S:?b0
        ADDW      X, #0x8
        LD        (X), A
        SUBW      X, #0x8
        LD        A, S:?b1
        ADDW      X, #0x9
        LD        (X), A
        SUBW      X, #0x9
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_AnalogWatchdogConfig:
        LDW       S:?w1, X
        LD        S:?b4, A
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        A, (X)
        AND       A, #0xe0
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        A, (X)
        OR        A, S:?b4
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        (X), A
        LD        A, YH
        LDW       X, S:?w1
        ADDW      X, #0x6
        LD        (X), A
        LD        A, YL
        LDW       X, S:?w1
        ADDW      X, #0x7
        LD        (X), A
        LD        A, S:?b0
        LDW       X, S:?w1
        ADDW      X, #0x8
        LD        (X), A
        LD        A, S:?b1
        LDW       X, S:?w1
        ADDW      X, #0x9
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_TempSensorCmd:
        TNZ       A
        JREQ      L:??ADC_TempSensorCmd_0
        BSET      L:0x534e, #0x5
        RET
??ADC_TempSensorCmd_0:
        BRES      L:0x534e, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_VrefintCmd:
        TNZ       A
        JREQ      L:??ADC_VrefintCmd_0
        BSET      L:0x534e, #0x4
        RET
??ADC_VrefintCmd_0:
        BRES      L:0x534e, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_ChannelCmd:
        LDW       S:?w1, X
        CLR       S:?b0
        RLWA      Y, A
        LD        S:?b1, A
        RRWA      Y, A
        MOV       S:?b0, S:?b1
        TNZ       A
        JREQ      L:??ADC_ChannelCmd_0
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        ADDW      X, #0xa
        LD        A, YL
        OR        A, (X)
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        LD        A, S:?b1
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET
??ADC_ChannelCmd_0:
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        ADDW      X, #0xa
        LD        A, YL
        CPL       A
        AND       A, (X)
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        LD        A, S:?b1
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_SamplingTimeConfig:
        LDW       Y, X
        TNZ       A
        JREQ      L:??ADC_SamplingTimeConfig_0
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        AND       A, #0x1f
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, S:?b0
        CALL      L:?sll8_a_a_5
        OR        A, (X)
        INCW      Y
        INCW      Y
        LD        (Y), A
        RET
??ADC_SamplingTimeConfig_0:
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xf8
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
ADC_SchmittTriggerConfig:
        LDW       S:?w1, X
        CLR       S:?b0
        RLWA      Y, A
        LD        S:?b1, A
        RRWA      Y, A
        MOV       S:?b0, S:?b1
        TNZ       A
        JREQ      L:??ADC_SchmittTriggerConfig_0
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        ADDW      X, #0xe
        LD        A, YL
        CPL       A
        AND       A, (X)
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        LD        A, S:?b1
        ADDW      X, #0xe
        LD        (X), A
        SUBW      X, #0xe
        RET
??ADC_SchmittTriggerConfig_0:
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        ADDW      X, #0xe
        LD        A, YL
        OR        A, (X)
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, S:?w1
        LD        A, S:?b1
        ADDW      X, #0xe
        LD        (X), A
        SUBW      X, #0xe
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_GetConversionValue:
        CLR       S:?b1
        CLR       S:?b0
        LDW       Y, X
        ADDW      Y, #0x4
        LD        A, (Y)
        CLRW      Y
        LD        YL, A
        LDW       S:?w0, Y
        ADDW      X, #0x5
        LD        A, (X)
        CLR       S:?b2
        LD        S:?b3, A
        LDW       X, S:?w0
        CLR       A
        RLWA      X, A
        RRWA      X, A
        OR        A, S:?b3
        RRWA      X, A
        OR        A, S:?b2
        RRWA      X, A
        LDW       S:?w0, X
        LDW       X, S:?w0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_DMACmd:
        TNZ       A
        JREQ      L:??ADC_DMACmd_0
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        AND       A, #0x7f
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET
??ADC_DMACmd_0:
        LDW       Y, X
        ADDW      Y, #0xa
        LD        A, (Y)
        OR        A, #0x80
        ADDW      X, #0xa
        LD        (X), A
        SUBW      X, #0xa
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_ITConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??ADC_ITConfig_0
        LD        A, (X)
        OR        A, S:?b1
        LD        (X), A
        RET
??ADC_ITConfig_0:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, (X)
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        ADDW      X, #0x3
        LD        A, (X)
        AND       A, S:?b1
        CP        A, #0x0
        JREQ      L:??ADC_GetFlagStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??ADC_GetFlagStatus_1
??ADC_GetFlagStatus_0:
        CLR       S:?b0
??ADC_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_ClearFlag:
        CPL       A
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b0
        CLR       S:?b4
        CLR       S:?b1
        LD        A, S:?b3
        SRL       A
        SRL       A
        SRL       A
        LD        S:?b4, A
        LD        A, S:?b4
        AND       A, #0x10
        SRL       A
        SRL       A
        LD        S:?b2, A
        LD        A, S:?b4
        AND       A, #0x3
        OR        A, S:?b2
        LD        S:?b4, A
        LD        A, (X)
        AND       A, S:?b3
        LD        S:?b1, A
        ADDW      X, #0x3
        LD        A, (X)
        AND       A, S:?b4
        CP        A, #0x0
        JREQ      L:??ADC_GetITStatus_0
        TNZ       S:?b1
        JREQ      L:??ADC_GetITStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??ADC_GetITStatus_1
??ADC_GetITStatus_0:
        CLR       S:?b0
??ADC_GetITStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ADC_ClearITPendingBit:
        CLR       S:?b0
        SRL       A
        SRL       A
        SRL       A
        LD        S:?b0, A
        LD        A, S:?b0
        AND       A, #0x10
        SRL       A
        SRL       A
        LD        S:?b1, A
        LD        A, S:?b0
        AND       A, #0x3
        OR        A, S:?b1
        LD        S:?b0, A
        CPL       S:?b0
        LD        A, S:?b0
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 763 bytes in section .near_func.text
// 
// 763 bytes of CODE memory
//
//Errors: none
//Warnings: none
