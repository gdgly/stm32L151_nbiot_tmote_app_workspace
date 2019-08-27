///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                27/Aug/2019  13:26:15
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wfe.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW64BD.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_wfe.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_wfe.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?switch16vlt_0x_x_0y
        EXTERN ?w1

        PUBLIC WFE_DeInit
        PUBLIC WFE_GetWakeUpSourceEventStatus
        PUBLIC WFE_WakeUpSourceEventCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WFE_DeInit:
        CLR       L:0x50a6
        CLR       L:0x50a7
        CLR       L:0x50a8
        CLR       L:0x50a9
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WFE_WakeUpSourceEventCmd:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, XH
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??WFE_WakeUpSourceEventCmd_0
        LD        A, S:?b0
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_1
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_2
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_3
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_4
        JRA       L:??WFE_WakeUpSourceEventCmd_5
??WFE_WakeUpSourceEventCmd_1:
        LD        A, XL
        OR        A, L:0x50a6
        LD        L:0x50a6, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_2:
        LD        A, XL
        OR        A, L:0x50a7
        LD        L:0x50a7, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_3:
        LD        A, XL
        OR        A, L:0x50a8
        LD        L:0x50a8, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_4:
        LD        A, XL
        OR        A, L:0x50a9
        LD        L:0x50a9, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_5:
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_0:
        LD        A, S:?b0
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_7
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_8
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_9
        DEC       A
        JREQ      L:??WFE_WakeUpSourceEventCmd_10
        JRA       L:??WFE_WakeUpSourceEventCmd_11
??WFE_WakeUpSourceEventCmd_7:
        LD        A, XL
        CPL       A
        AND       A, L:0x50a6
        LD        L:0x50a6, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_8:
        LD        A, XL
        CPL       A
        AND       A, L:0x50a7
        LD        L:0x50a7, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_9:
        LD        A, XL
        CPL       A
        AND       A, L:0x50a8
        LD        L:0x50a8, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_10:
        LD        A, XL
        CPL       A
        AND       A, L:0x50a9
        LD        L:0x50a9, A
        JRA       L:??WFE_WakeUpSourceEventCmd_6
??WFE_WakeUpSourceEventCmd_11:
??WFE_WakeUpSourceEventCmd_6:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
WFE_GetWakeUpSourceEventStatus:
        LDW       S:?w1, X
        CLR       S:?b4
        LDW       X, S:?w1
        LDW       Y, #??switch_table_0
        CALL      L:?switch16vlt_0x_x_0y
        JP        (X)
??WFE_GetWakeUpSourceEventStatus_0:
        LD        A, S:?b3
        AND       A, L:0x50a6
        CP        A, #0x0
        JREQ      L:??WFE_GetWakeUpSourceEventStatus_1
        LD        A, #0x1
        LD        S:?b4, A
        JRA       L:??WFE_GetWakeUpSourceEventStatus_2
??WFE_GetWakeUpSourceEventStatus_1:
        CLR       S:?b4
??WFE_GetWakeUpSourceEventStatus_2:
        JRA       L:??WFE_GetWakeUpSourceEventStatus_3
??WFE_GetWakeUpSourceEventStatus_4:
        LD        A, S:?b3
        AND       A, L:0x50a7
        CP        A, #0x0
        JREQ      L:??WFE_GetWakeUpSourceEventStatus_5
        LD        A, #0x1
        LD        S:?b4, A
        JRA       L:??WFE_GetWakeUpSourceEventStatus_6
??WFE_GetWakeUpSourceEventStatus_5:
        CLR       S:?b4
??WFE_GetWakeUpSourceEventStatus_6:
        JRA       L:??WFE_GetWakeUpSourceEventStatus_3
??WFE_GetWakeUpSourceEventStatus_7:
        LD        A, S:?b3
        AND       A, L:0x50a8
        CP        A, #0x0
        JREQ      L:??WFE_GetWakeUpSourceEventStatus_8
        LD        A, #0x1
        LD        S:?b4, A
        JRA       L:??WFE_GetWakeUpSourceEventStatus_9
??WFE_GetWakeUpSourceEventStatus_8:
        CLR       S:?b4
??WFE_GetWakeUpSourceEventStatus_9:
        JRA       L:??WFE_GetWakeUpSourceEventStatus_3
??WFE_GetWakeUpSourceEventStatus_10:
        LD        A, S:?b3
        AND       A, L:0x50a9
        CP        A, #0x0
        JREQ      L:??WFE_GetWakeUpSourceEventStatus_11
        LD        A, #0x1
        LD        S:?b4, A
        JRA       L:??WFE_GetWakeUpSourceEventStatus_12
??WFE_GetWakeUpSourceEventStatus_11:
        CLR       S:?b4
??WFE_GetWakeUpSourceEventStatus_12:
        JRA       L:??WFE_GetWakeUpSourceEventStatus_3
??WFE_GetWakeUpSourceEventStatus_13:
??WFE_GetWakeUpSourceEventStatus_3:
        LD        A, S:?b4
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
??switch_table_0:
        DC16      0x101
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x102
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x104
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x108
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x110
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x120
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x140
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x180
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_0)
        DC16      0x201
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x202
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x204
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x208
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x210
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x220
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x240
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x280
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_4)
        DC16      0x301
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x302
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x304
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x308
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x310
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x320
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x340
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x380
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_7)
        DC16      0x401
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x402
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x404
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x408
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x410
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x420
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x440
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_10)
        DC16      0x0
        DC16      LWRD(??WFE_GetWakeUpSourceEventStatus_13)

        END
// 
// 360 bytes in section .near_func.text
// 
// 360 bytes of CODE memory
//
//Errors: none
//Warnings: none
