///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                27/Aug/2019  13:26:10
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dac.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW514E.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_dac.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_dac.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?sll16_x_x_a
        EXTERN ?sra16_x_x_a
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2

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
        LD        S:?b2, A
        CLR       S:?b3
        CLRW      Y
        LD        A, S:?b2
        SLL       A
        CLRW      X
        LD        XL, A
        LDW       Y, X
        LDW       X, Y
        ADDW      X, #0x5380
        LD        A, (X)
        LD        S:?b3, A
        LD        A, S:?b3
        AND       A, #0xc1
        LD        S:?b3, A
        LD        A, S:?b1
        OR        A, S:?b3
        LD        S:?b3, A
        LD        A, S:?b0
        CP        A, #0x30
        JREQ      L:??DAC_Init_0
        LD        A, S:?b0
        OR        A, #0x4
        OR        A, S:?b3
        LD        S:?b3, A
??DAC_Init_0:
        LDW       X, Y
        ADDW      X, #0x5380
        LD        A, S:?b3
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_Cmd:
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
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
        JRA       L:??DAC_Cmd_1
??DAC_Cmd_0:
        LD        A, (X)
        AND       A, #0xfe
        LD        (X), A
??DAC_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SoftwareTriggerCmd:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??DAC_SoftwareTriggerCmd_0
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x5384
        LD        L:0x5384, A
        JRA       L:??DAC_SoftwareTriggerCmd_1
??DAC_SoftwareTriggerCmd_0:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x5384
        LD        L:0x5384, A
??DAC_SoftwareTriggerCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_DualSoftwareTriggerCmd:
        LD        S:?b0, A
        TNZ       S:?b0
        JREQ      L:??DAC_DualSoftwareTriggerCmd_0
        LD        A, L:0x5384
        OR        A, #0x3
        LD        L:0x5384, A
        JRA       L:??DAC_DualSoftwareTriggerCmd_1
??DAC_DualSoftwareTriggerCmd_0:
        LD        A, L:0x5384
        AND       A, #0xfc
        LD        L:0x5384, A
??DAC_DualSoftwareTriggerCmd_1:
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
        LD        S:?b1, A
        CLR       S:?b2
        CLRW      X
        LD        A, S:?b1
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        LD        A, (X)
        AND       A, #0xf0
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetTriangleWaveAmplitude:
        LD        S:?b1, A
        CLR       S:?b2
        CLRW      X
        LD        A, S:?b1
        SLL       A
        CLRW      Y
        LD        YL, A
        ADDW      Y, #0x5381
        LDW       X, Y
        LD        A, (X)
        AND       A, #0xf0
        LD        S:?b2, A
        LD        A, S:?b0
        OR        A, S:?b2
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
        JRA       L:??DAC_SetChannel1Data_1
??DAC_SetChannel1Data_0:
        LD        A, XL
        LD        L:0x5390, A
??DAC_SetChannel1Data_1:
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
        JRA       L:??DAC_SetChannel2Data_1
??DAC_SetChannel2Data_0:
        LD        A, XL
        LD        L:0x539c, A
??DAC_SetChannel2Data_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_SetDualChannelData:
        LD        S:?b0, A
        LDW       S:?w1, X
        LDW       S:?w2, Y
        CLRW      Y
        LD        A, S:?b0
        CP        A, #0x8
        JREQ      L:??DAC_SetDualChannelData_0
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        ADDW      X, #0x53a0
        LDW       Y, X
        LD        A, S:?b4
        LD        (Y), A
        LDW       X, Y
        INCW      X
        LD        A, S:?b5
        LD        (X), A
        LD        A, S:?b2
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, S:?b3
        LD        (X), A
        JRA       L:??DAC_SetDualChannelData_1
??DAC_SetDualChannelData_0:
        LD        A, S:?b5
        LD        L:0x53a8, A
        LD        A, S:?b3
        LD        L:0x53a9, A
??DAC_SetDualChannelData_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_GetDataOutputValue:
        LD        S:?b2, A
        CLRW      Y
        CLR       S:?b1
        CLR       S:?b0
        TNZ       S:?b2
        JRNE      L:??DAC_GetDataOutputValue_0
        LD        A, L:0x53ac
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w0, X
        LD        A, L:0x53ad
        CLR       S:?b4
        LD        S:?b5, A
        LDW       X, S:?w0
        RRWA      X, A
        OR        A, S:?b5
        RRWA      X, A
        OR        A, S:?b4
        RRWA      X, A
        LDW       Y, X
        JRA       L:??DAC_GetDataOutputValue_1
??DAC_GetDataOutputValue_0:
        LD        A, L:0x53b0
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w0, X
        LD        A, L:0x53b1
        CLR       S:?b4
        LD        S:?b5, A
        LDW       X, S:?w0
        RRWA      X, A
        OR        A, S:?b5
        RRWA      X, A
        OR        A, S:?b4
        RRWA      X, A
        LDW       Y, X
??DAC_GetDataOutputValue_1:
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_DMACmd:
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
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
        JRA       L:??DAC_DMACmd_1
??DAC_DMACmd_0:
        LD        A, (X)
        AND       A, #0xef
        LD        (X), A
??DAC_DMACmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_ITConfig:
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b2
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
        JRA       L:??DAC_ITConfig_1
??DAC_ITConfig_0:
        LD        A, S:?b0
        CPL       A
        AND       A, (X)
        LD        (X), A
??DAC_ITConfig_1:
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
        LD        A, #0x1
        LD        S:?b1, A
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
        LD        A, S:?b2
        CPL       A
        LD        L:0x5385, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_GetITStatus:
        LD        S:?b6, A
        CLR       S:?b4
        CLR       S:?b3
        CLR       S:?b2
        CLR       S:?b5
        LD        A, S:?b6
        SLL       A
        SLL       A
        CLRW      X
        LD        XL, A
        ADDW      X, #0x5381
        LD        A, (X)
        LD        S:?b5, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b6
        CALL      L:?sll16_x_x_a
        LD        A, XL
        AND       A, S:?b5
        LD        S:?b3, A
        LD        A, #0x5
        SUB       A, S:?b6
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sra16_x_x_a
        LD        A, XL
        AND       A, L:0x5385
        LD        S:?b2, A
        TNZ       S:?b2
        JREQ      L:??DAC_GetITStatus_0
        TNZ       S:?b3
        JREQ      L:??DAC_GetITStatus_0
        LD        A, #0x1
        LD        S:?b4, A
        JRA       L:??DAC_GetITStatus_1
??DAC_GetITStatus_0:
        CLR       S:?b4
??DAC_GetITStatus_1:
        LD        A, S:?b4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
DAC_ClearITPendingBit:
        LD        S:?b2, A
        LD        A, #0x5
        SUB       A, S:?b2
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
// 779 bytes in section .near_func.text
// 
// 779 bytes of CODE memory
//
//Errors: none
//Warnings: none
