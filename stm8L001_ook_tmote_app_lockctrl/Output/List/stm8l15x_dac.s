///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:18
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dac.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC3CE.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dac.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_dac.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?sll16_x_x_a
        EXTERN ?sra16_x_x_a
        EXTERN ?w0
        EXTERN ?w1

        PUBLIC DAC_ClearFlag
        PUBLIC DAC_ClearITPendingBit
        PUBLIC DAC_Cmd
        PUBLIC DAC_DMACmd
        PUBLIC DAC_DeInit
        PUBLIC DAC_DualSoftwareTriggerCmd
        PUBLIC DAC_GetDataOutputValue
        PUBLIC DAC_GetFlagStatus
        PUBLIC DAC_GetITStatus
        PUBLIC DAC_ITConfig
        PUBLIC DAC_Init
        PUBLIC DAC_SetChannel1Data
        PUBLIC DAC_SetChannel2Data
        PUBLIC DAC_SetDualChannelData
        PUBLIC DAC_SetNoiseWaveLFSR
        PUBLIC DAC_SetTriangleWaveAmplitude
        PUBLIC DAC_SoftwareTriggerCmd
        PUBLIC DAC_WaveGenerationCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_DeInit:
        CLR       L:0x5380
        CLR       L:0x5381
        CLR       L:0x5382
        CLR       L:0x5383
        CLR       L:0x5384
        MOV       L:0x5385, #0xff
        CLR       L:0x5388
        CLR       L:0x5389
        CLR       L:0x538c
        CLR       L:0x538d
        CLR       L:0x5390
        CLR       L:0x5394
        CLR       L:0x5395
        CLR       L:0x5398
        CLR       L:0x5399
        CLR       L:0x539c
        CLR       L:0x53a0
        CLR       L:0x53a1
        CLR       L:0x53a2
        CLR       L:0x53a3
        CLR       L:0x53a4
        CLR       L:0x53a5
        CLR       L:0x53a6
        CLR       L:0x53a7
        CLR       L:0x53a8
        CLR       L:0x53a9
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_Init:
        CLR       S:?b2
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        LDW       X, Y
        LDW       Y, X
        ADDW      Y, #0x5380
        LD        A, (Y)
        LD        S:?b2, A
        LD        A, S:?b2
        AND       A, #0xc1
        LD        S:?b2, A
        LD        A, S:?b1
        OR        A, S:?b2
        LD        S:?b2, A
        LD        A, S:?b0
        CP        A, #0x30
        JREQ      L:??DAC_Init_0
        LD        A, S:?b0
        OR        A, #0x4
        OR        A, S:?b2
        LD        S:?b2, A
??DAC_Init_0:
        ADDW      X, #0x5380
        LD        A, S:?b2
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_Cmd:
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5380
        LDW       X, Y
        TNZ       S:?b0
        JREQ      L:??DAC_Cmd_0
        LD        A, (X)
        OR        A, #0x1
        LD        (X), A
        RET
??DAC_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SoftwareTriggerCmd:
        TNZ       S:?b0
        JREQ      L:??DAC_SoftwareTriggerCmd_0
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x5384
        LD        L:0x5384, A
        RET
??DAC_SoftwareTriggerCmd_0:
        CLRW      X
        INCW      X
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x5384
        LD        L:0x5384, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_DualSoftwareTriggerCmd:
        TNZ       A
        JREQ      L:??DAC_DualSoftwareTriggerCmd_0
        LD        A, L:0x5384
        OR        A, #0x3
        LD        L:0x5384, A
        RET
??DAC_DualSoftwareTriggerCmd_0:
        LD        A, L:0x5384
        AND       A, #0xfc
        LD        L:0x5384, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_WaveGenerationCmd:
        LD        S:?b2, A
        CLR       S:?b3
        LD        A, S:?b2
        SLL       A
        CLRW      X
        LD        XL, A
        ADDW      X, #0x5380
        LD        A, (X)
        AND       A, #0x3f
        LD        S:?b3, A
        TNZ       S:?b1
        JREQ      L:??DAC_WaveGenerationCmd_0
        LD        A, S:?b0
        OR        A, S:?b3
        LD        S:?b3, A
??DAC_WaveGenerationCmd_0:
        LD        A, S:?b2
        SLL       A
        CLRW      X
        LD        XL, A
        ADDW      X, #0x5380
        LD        A, S:?b3
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetNoiseWaveLFSR:
        CLR       S:?b1
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        LD        A, (X)
        AND       A, #0xf0
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetTriangleWaveAmplitude:
        CLR       S:?b1
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        LD        A, (X)
        AND       A, #0xf0
        LD        S:?b1, A
        LD        A, S:?b0
        OR        A, S:?b1
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetChannel1Data:
        LD        S:?b0, A
        LD        A, S:?b0
        CP        A, #0x8
        JREQ      L:??DAC_SetChannel1Data_0
        CLRW      Y
        LD        A, S:?b0
        LD        YL, A
        ADDW      Y, #0x5388
        LD        A, XH
        LD        (Y), A
        CLRW      Y
        LD        A, S:?b0
        LD        YL, A
        ADDW      Y, #0x5389
        LD        A, XL
        LD        (Y), A
        RET
??DAC_SetChannel1Data_0:
        LD        A, XL
        LD        L:0x5390, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetChannel2Data:
        LD        S:?b0, A
        LD        A, S:?b0
        CP        A, #0x8
        JREQ      L:??DAC_SetChannel2Data_0
        CLRW      Y
        LD        A, S:?b0
        LD        YL, A
        ADDW      Y, #0x5394
        LD        A, XH
        LD        (Y), A
        CLRW      Y
        LD        A, S:?b0
        LD        YL, A
        ADDW      Y, #0x5395
        LD        A, XL
        LD        (Y), A
        RET
??DAC_SetChannel2Data_0:
        LD        A, XL
        LD        L:0x539c, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetDualChannelData:
        LDW       S:?w0, X
        CLR       S:?b3
        CLR       S:?b2
        CP        A, #0x8
        JREQ      L:??DAC_SetDualChannelData_0
        CLRW      X
        LD        XL, A
        ADDW      X, #0x53a0
        LDW       S:?w1, X
        LD        A, YH
        LD        [S:?w1.w], A
        LDW       X, S:?w1
        INCW      X
        LD        A, YL
        LD        (X), A
        LD        A, S:?b0
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, S:?w1
        ADDW      X, #0x3
        LD        A, S:?b1
        LD        (X), A
        RET
??DAC_SetDualChannelData_0:
        LD        A, YL
        LD        L:0x53a8, A
        LD        A, S:?b1
        LD        L:0x53a9, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_GetDataOutputValue:
        CLRW      X
        CLRW      Y
        TNZ       A
        JRNE      L:??DAC_GetDataOutputValue_0
        LD        A, L:0x53ac
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       Y, X
        LD        A, L:0x53ad
        CLR       S:?b0
        LD        S:?b1, A
        LDW       X, Y
        RRWA      X, A
        OR        A, S:?b1
        RRWA      X, A
        OR        A, S:?b0
        RRWA      X, A
        RET
??DAC_GetDataOutputValue_0:
        LD        A, L:0x53b0
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       Y, X
        LD        A, L:0x53b1
        CLR       S:?b0
        LD        S:?b1, A
        LDW       X, Y
        RRWA      X, A
        OR        A, S:?b1
        RRWA      X, A
        OR        A, S:?b0
        RRWA      X, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_DMACmd:
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        TNZ       S:?b0
        JREQ      L:??DAC_DMACmd_0
        LD        A, (X)
        OR        A, #0x10
        LD        (X), A
        RET
??DAC_DMACmd_0:
        LD        A, (X)
        AND       A, #0xef
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_ITConfig:
        CLRW      X
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        TNZ       S:?b1
        JREQ      L:??DAC_ITConfig_0
        LD        A, (X)
        OR        A, S:?b0
        LD        (X), A
        RET
??DAC_ITConfig_0:
        CPL       S:?b0
        LD        A, S:?b0
        AND       A, (X)
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_GetFlagStatus:
        LD        S:?b2, A
        CLR       S:?b1
        CLR       S:?b3
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b3, A
        LD        A, L:0x5385
        AND       A, S:?b3
        CP        A, #0x0
        JREQ      L:??DAC_GetFlagStatus_0
        MOV       S:?b1, #0x1
        JRA       L:??DAC_GetFlagStatus_1
??DAC_GetFlagStatus_0:
        CLR       S:?b1
??DAC_GetFlagStatus_1:
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_ClearFlag:
        LD        S:?b1, A
        CLR       S:?b2
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b2, A
        CPL       S:?b2
        LD        A, S:?b2
        LD        L:0x5385, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_GetITStatus:
        LD        S:?b5, A
        CLR       S:?b1
        CLR       S:?b4
        CLR       S:?b3
        CLR       S:?b2
        LD        A, S:?b5
        SLL       A
        SLL       A
        CLRW      X
        LD        XL, A
        ADDW      X, #0x5381
        LD        A, (X)
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b5
        CALL      L:?sll16_x_x_a
        LD        A, XL
        AND       A, S:?b2
        LD        S:?b4, A
        LD        A, #0x5
        SUB       A, S:?b5
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sra16_x_x_a
        LD        A, XL
        AND       A, L:0x5385
        LD        S:?b3, A
        TNZ       S:?b3
        JREQ      L:??DAC_GetITStatus_0
        TNZ       S:?b4
        JREQ      L:??DAC_GetITStatus_0
        MOV       S:?b1, #0x1
        JRA       L:??DAC_GetITStatus_1
??DAC_GetITStatus_0:
        CLR       S:?b1
??DAC_GetITStatus_1:
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_ClearITPendingBit:
        LD        S:?b1, A
        LD        A, #0x5
        SUB       A, S:?b1
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sra16_x_x_a
        LD        A, XL
        CPL       A
        LD        L:0x5385, A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 725 bytes in section .near_func.text
// 
// 725 bytes of CODE memory
//
//Errors: none
//Warnings: none
