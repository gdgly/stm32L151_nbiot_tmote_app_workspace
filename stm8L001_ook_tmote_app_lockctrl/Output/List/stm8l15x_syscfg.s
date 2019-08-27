///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                27/Aug/2019  13:26:13
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_syscfg.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW5E8C.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_syscfg.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_syscfg.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?sll16_x_x_a

        PUBLIC SYSCFG_REMAPDMAChannelConfig
        PUBLIC SYSCFG_REMAPDeInit
        PUBLIC SYSCFG_REMAPPinConfig
        PUBLIC SYSCFG_RIAnalogSwitchConfig
        PUBLIC SYSCFG_RIDeInit
        PUBLIC SYSCFG_RIIOSwitchConfig
        PUBLIC SYSCFG_RIResistorConfig
        PUBLIC SYSCFG_RITIMInputCaptureConfig


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_RIDeInit:
        CLR       L:0x5431
        CLR       L:0x5432
        CLR       L:0x5439
        CLR       L:0x543a
        CLR       L:0x543b
        CLR       L:0x5457
        CLR       L:0x543d
        CLR       L:0x543e
        CLR       L:0x543f
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_RITIMInputCaptureConfig:
        LD        S:?b1, A
        LD        A, S:?b1
        CP        A, #0x2
        JRNE      L:??SYSCFG_RITIMInputCaptureConfig_0
        LD        A, S:?b0
        LD        L:0x5431, A
        JRA       L:??SYSCFG_RITIMInputCaptureConfig_1
??SYSCFG_RITIMInputCaptureConfig_0:
        LD        A, S:?b0
        LD        L:0x5432, A
??SYSCFG_RITIMInputCaptureConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_RIAnalogSwitchConfig:
        LD        S:?b2, A
        CLR       S:?b1
        LD        A, S:?b2
        AND       A, #0xf0
        LD        S:?b3, A
        LD        A, S:?b2
        AND       A, #0xf
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIAnalogSwitchConfig_0
        LD        A, S:?b3
        CP        A, #0x10
        JRNE      L:??SYSCFG_RIAnalogSwitchConfig_1
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x543d
        LD        L:0x543d, A
        JRA       L:??SYSCFG_RIAnalogSwitchConfig_2
??SYSCFG_RIAnalogSwitchConfig_1:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x543e
        LD        L:0x543e, A
        JRA       L:??SYSCFG_RIAnalogSwitchConfig_2
??SYSCFG_RIAnalogSwitchConfig_0:
        LD        A, S:?b3
        CP        A, #0x10
        JRNE      L:??SYSCFG_RIAnalogSwitchConfig_3
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x543d
        LD        L:0x543d, A
        JRA       L:??SYSCFG_RIAnalogSwitchConfig_2
??SYSCFG_RIAnalogSwitchConfig_3:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x543e
        LD        L:0x543e, A
??SYSCFG_RIAnalogSwitchConfig_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_RIIOSwitchConfig:
        LD        S:?b2, A
        CLR       S:?b1
        LD        A, S:?b2
        AND       A, #0xf
        LD        S:?b1, A
        LD        A, S:?b2
        AND       A, #0xf0
        LD        S:?b3, A
        LD        A, S:?b3
        CP        A, #0x10
        JRNE      L:??SYSCFG_RIIOSwitchConfig_0
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIIOSwitchConfig_1
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x5439
        LD        L:0x5439, A
        JP        L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_1:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x5439
        LD        L:0x5439, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_0:
        LD        A, S:?b3
        CP        A, #0x20
        JRNE      L:??SYSCFG_RIIOSwitchConfig_3
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIIOSwitchConfig_4
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x543a
        LD        L:0x543a, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_4:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x543a
        LD        L:0x543a, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_3:
        LD        A, S:?b3
        CP        A, #0x30
        JRNE      L:??SYSCFG_RIIOSwitchConfig_5
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIIOSwitchConfig_6
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x543b
        LD        L:0x543b, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_6:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x543b
        LD        L:0x543b, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_5:
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIIOSwitchConfig_7
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x5457
        LD        L:0x5457, A
        JRA       L:??SYSCFG_RIIOSwitchConfig_2
??SYSCFG_RIIOSwitchConfig_7:
        CLRW      X
        INCW      X
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x5457
        LD        L:0x5457, A
??SYSCFG_RIIOSwitchConfig_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_RIResistorConfig:
        LD        S:?b1, A
        TNZ       S:?b0
        JREQ      L:??SYSCFG_RIResistorConfig_0
        LD        A, L:0x543f
        OR        A, S:?b1
        LD        L:0x543f, A
        JRA       L:??SYSCFG_RIResistorConfig_1
??SYSCFG_RIResistorConfig_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x543f
        LD        L:0x543f, A
??SYSCFG_RIResistorConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_REMAPDeInit:
        MOV       L:0x509e, #0xc
        CLR       L:0x509f
        CLR       L:0x509d
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_REMAPPinConfig:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, XH
        LD        S:?b1, A
        LD        A, S:?b1
        CP        A, #0x1
        JRNE      L:??SYSCFG_REMAPPinConfig_0
        LD        A, XL
        SWAP      A
        AND       A, #0xf0
        OR        A, #0xf
        AND       A, L:0x509e
        LD        L:0x509e, A
        TNZ       S:?b0
        JREQ      L:??SYSCFG_REMAPPinConfig_1
        LD        A, XL
        AND       A, #0xf0
        OR        A, L:0x509e
        LD        L:0x509e, A
        JRA       L:??SYSCFG_REMAPPinConfig_1
??SYSCFG_REMAPPinConfig_0:
        LD        A, S:?b1
        CP        A, #0x2
        JRNE      L:??SYSCFG_REMAPPinConfig_2
        TNZ       S:?b0
        JREQ      L:??SYSCFG_REMAPPinConfig_3
        LD        A, XL
        OR        A, L:0x509f
        LD        L:0x509f, A
        JRA       L:??SYSCFG_REMAPPinConfig_1
??SYSCFG_REMAPPinConfig_3:
        LD        A, XL
        CPL       A
        AND       A, L:0x509f
        LD        L:0x509f, A
        JRA       L:??SYSCFG_REMAPPinConfig_1
??SYSCFG_REMAPPinConfig_2:
        TNZ       S:?b0
        JREQ      L:??SYSCFG_REMAPPinConfig_4
        LD        A, XL
        OR        A, L:0x509d
        LD        L:0x509d, A
        JRA       L:??SYSCFG_REMAPPinConfig_1
??SYSCFG_REMAPPinConfig_4:
        LD        A, XL
        CPL       A
        AND       A, L:0x509d
        LD        L:0x509d, A
??SYSCFG_REMAPPinConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
SYSCFG_REMAPDMAChannelConfig:
        LD        S:?b0, A
        LD        A, S:?b0
        AND       A, #0xf0
        CP        A, #0x0
        JREQ      L:??SYSCFG_REMAPDMAChannelConfig_0
        LD        A, L:0x509e
        AND       A, #0xf3
        LD        L:0x509e, A
        JRA       L:??SYSCFG_REMAPDMAChannelConfig_1
??SYSCFG_REMAPDMAChannelConfig_0:
        LD        A, L:0x509e
        AND       A, #0xfc
        LD        L:0x509e, A
??SYSCFG_REMAPDMAChannelConfig_1:
        LD        A, S:?b0
        AND       A, #0xf
        OR        A, L:0x509e
        LD        L:0x509e, A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 506 bytes in section .near_func.text
// 
// 506 bytes of CODE memory
//
//Errors: none
//Warnings: none
