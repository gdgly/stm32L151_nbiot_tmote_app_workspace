///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:12:55
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_comp.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW623B.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_comp.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_comp.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3

        PUBLIC COMP_ClearFlag
        PUBLIC COMP_ClearITPendingBit
        PUBLIC COMP_DeInit
        PUBLIC COMP_EdgeConfig
        PUBLIC COMP_GetFlagStatus
        PUBLIC COMP_GetITStatus
        PUBLIC COMP_GetOutputLevel
        PUBLIC COMP_ITConfig
        PUBLIC COMP_Init
        PUBLIC COMP_SchmittTriggerCmd
        PUBLIC COMP_TriggerConfig
        PUBLIC COMP_VrefintOutputCmd
        PUBLIC COMP_VrefintToCOMP1Connect
        PUBLIC COMP_WindowCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_DeInit:
        CLR       L:0x5440
        CLR       L:0x5441
        MOV       L:0x5442, #0xc0
        CLR       L:0x5443
        CLR       L:0x5444
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_Init:
        LD        S:?b2, A
        LD        A, L:0x5442
        AND       A, #0xc7
        LD        L:0x5442, A
        LD        A, L:0x5442
        OR        A, S:?b2
        LD        L:0x5442, A
        LD        A, L:0x5442
        AND       A, #0x3f
        LD        L:0x5442, A
        LD        A, L:0x5442
        OR        A, S:?b0
        LD        L:0x5442, A
        BRES      L:0x5441, #0x2
        LD        A, L:0x5441
        OR        A, S:?b1
        LD        L:0x5441, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_VrefintToCOMP1Connect:
        TNZ       A
        JREQ      L:??COMP_VrefintToCOMP1Connect_0
        BSET      L:0x5442, #0x2
        JRA       L:??COMP_VrefintToCOMP1Connect_1
??COMP_VrefintToCOMP1Connect_0:
        BRES      L:0x5442, #0x2
??COMP_VrefintToCOMP1Connect_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_EdgeConfig:
        LD        S:?b1, A
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??COMP_EdgeConfig_0
        LD        A, L:0x5440
        AND       A, #0xfc
        LD        L:0x5440, A
        LD        A, L:0x5440
        OR        A, S:?b0
        LD        L:0x5440, A
        JRA       L:??COMP_EdgeConfig_1
??COMP_EdgeConfig_0:
        LD        A, L:0x5441
        AND       A, #0xfc
        LD        L:0x5441, A
        LD        A, L:0x5441
        OR        A, S:?b0
        LD        L:0x5441, A
??COMP_EdgeConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetOutputLevel:
        LD        S:?b1, A
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??COMP_GetOutputLevel_0
        BTJF      L:0x5440, #0x3, L:??COMP_GetOutputLevel_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??COMP_GetOutputLevel_2
??COMP_GetOutputLevel_1:
        CLR       S:?b0
        JRA       L:??COMP_GetOutputLevel_2
??COMP_GetOutputLevel_0:
        BTJF      L:0x5441, #0x3, L:??COMP_GetOutputLevel_3
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??COMP_GetOutputLevel_2
??COMP_GetOutputLevel_3:
        CLR       S:?b0
??COMP_GetOutputLevel_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_WindowCmd:
        TNZ       A
        JREQ      L:??COMP_WindowCmd_0
        BSET      L:0x5442, #0x1
        JRA       L:??COMP_WindowCmd_1
??COMP_WindowCmd_0:
        BRES      L:0x5442, #0x1
??COMP_WindowCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_VrefintOutputCmd:
        TNZ       A
        JREQ      L:??COMP_VrefintOutputCmd_0
        BSET      L:0x5442, #0x0
        JRA       L:??COMP_VrefintOutputCmd_1
??COMP_VrefintOutputCmd_0:
        BRES      L:0x5442, #0x0
??COMP_VrefintOutputCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_SchmittTriggerCmd:
        TNZ       A
        JREQ      L:??COMP_SchmittTriggerCmd_0
        BSET      L:0x5440, #0x2
        JRA       L:??COMP_SchmittTriggerCmd_1
??COMP_SchmittTriggerCmd_0:
        BRES      L:0x5440, #0x2
??COMP_SchmittTriggerCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_TriggerConfig:
        LD        S:?b2, A
        LD        A, S:?b2
        DEC       A
        JREQ      L:??COMP_TriggerConfig_0
        DEC       A
        JREQ      L:??COMP_TriggerConfig_1
        DEC       A
        JREQ      L:??COMP_TriggerConfig_2
        DEC       A
        JREQ      L:??COMP_TriggerConfig_3
        JRA       L:??COMP_TriggerConfig_4
??COMP_TriggerConfig_0:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_5
        LD        A, S:?b0
        CPL       A
        AND       A, L:0x5443
        LD        L:0x5443, A
        JRA       L:??COMP_TriggerConfig_6
??COMP_TriggerConfig_5:
        LD        A, L:0x5443
        OR        A, S:?b0
        LD        L:0x5443, A
??COMP_TriggerConfig_6:
        JRA       L:??COMP_TriggerConfig_7
??COMP_TriggerConfig_1:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_8
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        CPL       A
        AND       A, L:0x5443
        LD        L:0x5443, A
        JRA       L:??COMP_TriggerConfig_9
??COMP_TriggerConfig_8:
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        OR        A, L:0x5443
        LD        L:0x5443, A
??COMP_TriggerConfig_9:
        JRA       L:??COMP_TriggerConfig_7
??COMP_TriggerConfig_2:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_10
        LD        A, S:?b0
        CPL       A
        AND       A, L:0x5444
        LD        L:0x5444, A
        JRA       L:??COMP_TriggerConfig_11
??COMP_TriggerConfig_10:
        LD        A, L:0x5444
        OR        A, S:?b0
        LD        L:0x5444, A
??COMP_TriggerConfig_11:
        JRA       L:??COMP_TriggerConfig_7
??COMP_TriggerConfig_3:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_12
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        CPL       A
        AND       A, L:0x5444
        LD        L:0x5444, A
        JRA       L:??COMP_TriggerConfig_13
??COMP_TriggerConfig_12:
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        OR        A, L:0x5444
        LD        L:0x5444, A
??COMP_TriggerConfig_13:
        JRA       L:??COMP_TriggerConfig_7
??COMP_TriggerConfig_4:
??COMP_TriggerConfig_7:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_ITConfig:
        CP        A, #0x1
        JRNE      L:??COMP_ITConfig_0
        TNZ       S:?b0
        JREQ      L:??COMP_ITConfig_1
        BSET      L:0x5440, #0x5
        JRA       L:??COMP_ITConfig_2
??COMP_ITConfig_1:
        BRES      L:0x5440, #0x5
        JRA       L:??COMP_ITConfig_2
??COMP_ITConfig_0:
        TNZ       S:?b0
        JREQ      L:??COMP_ITConfig_3
        BSET      L:0x5441, #0x5
        JRA       L:??COMP_ITConfig_2
??COMP_ITConfig_3:
        BRES      L:0x5441, #0x5
??COMP_ITConfig_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??COMP_GetFlagStatus_0
        BTJF      L:0x5440, #0x4, L:??COMP_GetFlagStatus_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??COMP_GetFlagStatus_2
??COMP_GetFlagStatus_1:
        CLR       S:?b0
        JRA       L:??COMP_GetFlagStatus_2
??COMP_GetFlagStatus_0:
        BTJF      L:0x5441, #0x4, L:??COMP_GetFlagStatus_3
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??COMP_GetFlagStatus_2
??COMP_GetFlagStatus_3:
        CLR       S:?b0
??COMP_GetFlagStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_ClearFlag:
        CP        A, #0x1
        JRNE      L:??COMP_ClearFlag_0
        BRES      L:0x5440, #0x4
        JRA       L:??COMP_ClearFlag_1
??COMP_ClearFlag_0:
        BRES      L:0x5441, #0x4
??COMP_ClearFlag_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetITStatus:
        LD        S:?b3, A
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, S:?b3
        CP        A, #0x1
        JRNE      L:??COMP_GetITStatus_0
        LD        A, L:0x5440
        AND       A, #0x10
        LD        S:?b1, A
        LD        A, L:0x5440
        AND       A, #0x20
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??COMP_GetITStatus_1
        TNZ       S:?b0
        JREQ      L:??COMP_GetITStatus_1
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_1:
        CLR       S:?b2
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_0:
        LD        A, L:0x5441
        AND       A, #0x10
        LD        S:?b1, A
        LD        A, L:0x5441
        AND       A, #0x20
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??COMP_GetITStatus_3
        TNZ       S:?b0
        JREQ      L:??COMP_GetITStatus_3
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_3:
        CLR       S:?b2
??COMP_GetITStatus_2:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_ClearITPendingBit:
        CP        A, #0x1
        JRNE      L:??COMP_ClearITPendingBit_0
        BRES      L:0x5440, #0x4
        JRA       L:??COMP_ClearITPendingBit_1
??COMP_ClearITPendingBit_0:
        BRES      L:0x5441, #0x4
??COMP_ClearITPendingBit_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 522 bytes in section .near_func.text
// 
// 522 bytes of CODE memory
//
//Errors: none
//Warnings: none
