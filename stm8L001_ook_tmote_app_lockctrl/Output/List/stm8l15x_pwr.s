///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  13:23:58
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_pwr.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW5AE5.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_pwr.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_pwr.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2

        PUBLIC PWR_DeInit
        PUBLIC PWR_FastWakeUpCmd
        PUBLIC PWR_GetFlagStatus
        PUBLIC PWR_PVDClearFlag
        PUBLIC PWR_PVDClearITPendingBit
        PUBLIC PWR_PVDCmd
        PUBLIC PWR_PVDGetITStatus
        PUBLIC PWR_PVDITConfig
        PUBLIC PWR_PVDLevelConfig
        PUBLIC PWR_UltraLowPowerCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_DeInit:
        MOV       L:0x50b2, #0x20
        CLR       L:0x50b3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDLevelConfig:
        LD        S:?b0, A
        LD        A, L:0x50b2
        AND       A, #0xf1
        LD        L:0x50b2, A
        LD        A, L:0x50b2
        OR        A, S:?b0
        LD        L:0x50b2, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDCmd:
        TNZ       A
        JREQ      L:??PWR_PVDCmd_0
        BSET      L:0x50b2, #0x0
        JRA       L:??PWR_PVDCmd_1
??PWR_PVDCmd_0:
        BRES      L:0x50b2, #0x0
??PWR_PVDCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_FastWakeUpCmd:
        TNZ       A
        JREQ      L:??PWR_FastWakeUpCmd_0
        BSET      L:0x50b3, #0x2
        JRA       L:??PWR_FastWakeUpCmd_1
??PWR_FastWakeUpCmd_0:
        BRES      L:0x50b3, #0x2
??PWR_FastWakeUpCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_UltraLowPowerCmd:
        TNZ       A
        JREQ      L:??PWR_UltraLowPowerCmd_0
        BSET      L:0x50b3, #0x1
        JRA       L:??PWR_UltraLowPowerCmd_1
??PWR_UltraLowPowerCmd_0:
        BRES      L:0x50b3, #0x1
??PWR_UltraLowPowerCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDITConfig:
        TNZ       A
        JREQ      L:??PWR_PVDITConfig_0
        BSET      L:0x50b2, #0x4
        JRA       L:??PWR_PVDITConfig_1
??PWR_PVDITConfig_0:
        BRES      L:0x50b2, #0x4
??PWR_PVDITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, S:?b1
        AND       A, #0x1
        CP        A, #0x0
        JREQ      L:??PWR_GetFlagStatus_0
        BTJF      L:0x50b3, #0x0, L:??PWR_GetFlagStatus_1
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??PWR_GetFlagStatus_2
??PWR_GetFlagStatus_1:
        CLR       S:?b0
        JRA       L:??PWR_GetFlagStatus_2
??PWR_GetFlagStatus_0:
        LD        A, L:0x50b2
        AND       A, S:?b1
        CP        A, #0x0
        JREQ      L:??PWR_GetFlagStatus_3
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??PWR_GetFlagStatus_2
??PWR_GetFlagStatus_3:
        CLR       S:?b0
??PWR_GetFlagStatus_2:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDClearFlag:
        BSET      L:0x50b2, #0x5
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDGetITStatus:
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, L:0x50b2
        AND       A, #0x20
        LD        S:?b1, A
        LD        A, L:0x50b2
        AND       A, #0x10
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??PWR_PVDGetITStatus_0
        TNZ       S:?b0
        JREQ      L:??PWR_PVDGetITStatus_0
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??PWR_PVDGetITStatus_1
??PWR_PVDGetITStatus_0:
        CLR       S:?b2
??PWR_PVDGetITStatus_1:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
PWR_PVDClearITPendingBit:
        BSET      L:0x50b2, #0x5
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 180 bytes in section .near_func.text
// 
// 180 bytes of CODE memory
//
//Errors: none
//Warnings: none
