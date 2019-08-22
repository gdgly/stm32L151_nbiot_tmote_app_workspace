///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:18
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_comp.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC39E.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_comp.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_comp.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2

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
        RET
??COMP_VrefintToCOMP1Connect_0:
        BRES      L:0x5442, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_EdgeConfig:
        CP        A, #0x1
        JRNE      L:??COMP_EdgeConfig_0
        LD        A, L:0x5440
        AND       A, #0xfc
        LD        L:0x5440, A
        LD        A, L:0x5440
        OR        A, S:?b0
        LD        L:0x5440, A
        RET
??COMP_EdgeConfig_0:
        LD        A, L:0x5441
        AND       A, #0xfc
        LD        L:0x5441, A
        LD        A, L:0x5441
        OR        A, S:?b0
        LD        L:0x5441, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetOutputLevel:
        CP        A, #0x1
        JRNE      L:??COMP_GetOutputLevel_0
        BTJF      L:0x5440, #0x3, L:??COMP_GetOutputLevel_1
        LD        A, #0x1
        RET
??COMP_GetOutputLevel_1:
        CLR       A
        RET
??COMP_GetOutputLevel_0:
        BTJF      L:0x5441, #0x3, L:??COMP_GetOutputLevel_2
        LD        A, #0x1
        RET
??COMP_GetOutputLevel_2:
        CLR       A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_WindowCmd:
        TNZ       A
        JREQ      L:??COMP_WindowCmd_0
        BSET      L:0x5442, #0x1
        RET
??COMP_WindowCmd_0:
        BRES      L:0x5442, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_VrefintOutputCmd:
        TNZ       A
        JREQ      L:??COMP_VrefintOutputCmd_0
        BSET      L:0x5442, #0x0
        RET
??COMP_VrefintOutputCmd_0:
        BRES      L:0x5442, #0x0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_SchmittTriggerCmd:
        TNZ       A
        JREQ      L:??COMP_SchmittTriggerCmd_0
        BSET      L:0x5440, #0x2
        RET
??COMP_SchmittTriggerCmd_0:
        BRES      L:0x5440, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_TriggerConfig:
        DEC       A
        JREQ      L:??COMP_TriggerConfig_0
        DEC       A
        JREQ      L:??COMP_TriggerConfig_1
        DEC       A
        JREQ      L:??COMP_TriggerConfig_2
        DEC       A
        JREQ      L:??COMP_TriggerConfig_3
        RET
??COMP_TriggerConfig_0:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_4
        CPL       S:?b0
        LD        A, S:?b0
        AND       A, L:0x5443
        LD        L:0x5443, A
        RET
??COMP_TriggerConfig_4:
        LD        A, L:0x5443
        OR        A, S:?b0
        LD        L:0x5443, A
        RET
??COMP_TriggerConfig_1:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_5
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        CPL       A
        AND       A, L:0x5443
        LD        L:0x5443, A
        RET
??COMP_TriggerConfig_5:
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        OR        A, L:0x5443
        LD        L:0x5443, A
        RET
??COMP_TriggerConfig_2:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_6
        CPL       S:?b0
        LD        A, S:?b0
        AND       A, L:0x5444
        LD        L:0x5444, A
        RET
??COMP_TriggerConfig_6:
        LD        A, L:0x5444
        OR        A, S:?b0
        LD        L:0x5444, A
        RET
??COMP_TriggerConfig_3:
        TNZ       S:?b1
        JREQ      L:??COMP_TriggerConfig_7
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        CPL       A
        AND       A, L:0x5444
        LD        L:0x5444, A
        RET
??COMP_TriggerConfig_7:
        LD        A, S:?b0
        SLL       A
        SLL       A
        SLL       A
        OR        A, L:0x5444
        LD        L:0x5444, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_ITConfig:
        CP        A, #0x1
        JRNE      L:??COMP_ITConfig_0
        TNZ       S:?b0
        JREQ      L:??COMP_ITConfig_1
        BSET      L:0x5440, #0x5
        RET
??COMP_ITConfig_1:
        BRES      L:0x5440, #0x5
        RET
??COMP_ITConfig_0:
        TNZ       S:?b0
        JREQ      L:??COMP_ITConfig_2
        BSET      L:0x5441, #0x5
        RET
??COMP_ITConfig_2:
        BRES      L:0x5441, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetFlagStatus:
        CLR       S:?b0
        CP        A, #0x1
        JRNE      L:??COMP_GetFlagStatus_0
        BTJF      L:0x5440, #0x4, L:??COMP_GetFlagStatus_1
        MOV       S:?b0, #0x1
        JRA       L:??COMP_GetFlagStatus_2
??COMP_GetFlagStatus_1:
        CLR       S:?b0
        JRA       L:??COMP_GetFlagStatus_2
??COMP_GetFlagStatus_0:
        BTJF      L:0x5441, #0x4, L:??COMP_GetFlagStatus_3
        MOV       S:?b0, #0x1
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
        RET
??COMP_ClearFlag_0:
        BRES      L:0x5441, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_GetITStatus:
        CLR       S:?b0
        CLR       S:?b2
        CLR       S:?b1
        CP        A, #0x1
        JRNE      L:??COMP_GetITStatus_0
        LD        A, L:0x5440
        AND       A, #0x10
        LD        S:?b2, A
        LD        A, L:0x5440
        AND       A, #0x20
        LD        S:?b1, A
        TNZ       S:?b2
        JREQ      L:??COMP_GetITStatus_1
        TNZ       S:?b1
        JREQ      L:??COMP_GetITStatus_1
        MOV       S:?b0, #0x1
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_1:
        CLR       S:?b0
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_0:
        LD        A, L:0x5441
        AND       A, #0x10
        LD        S:?b2, A
        LD        A, L:0x5441
        AND       A, #0x20
        LD        S:?b1, A
        TNZ       S:?b2
        JREQ      L:??COMP_GetITStatus_3
        TNZ       S:?b1
        JREQ      L:??COMP_GetITStatus_3
        MOV       S:?b0, #0x1
        JRA       L:??COMP_GetITStatus_2
??COMP_GetITStatus_3:
        CLR       S:?b0
??COMP_GetITStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
COMP_ClearITPendingBit:
        CP        A, #0x1
        JRNE      L:??COMP_ClearITPendingBit_0
        BRES      L:0x5440, #0x4
        RET
??COMP_ClearITPendingBit_0:
        BRES      L:0x5441, #0x4
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 473 bytes in section .near_func.text
// 
// 473 bytes of CODE memory
//
//Errors: none
//Warnings: none
