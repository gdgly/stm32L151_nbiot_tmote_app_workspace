///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  13:09:13
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_itc.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW813C.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_itc.c
//        -e -Ol --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_cross_call --debug --code_model small --data_model medium -o
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\Obj
//        --dlib_config "F:\IAR Systems\Embedded Workbench
//        8.3\stm8\LIB\dlstm8smf.h" -D STM8L05X_LD_VL -lcN
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_itc.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?sll16_x_x_a
        EXTERN ?srl8_a_a_b0

        PUBLIC ITC_DeInit
        PUBLIC ITC_GetCPUCC
        PUBLIC ITC_GetSoftIntStatus
        PUBLIC ITC_GetSoftwarePriority
        PUBLIC ITC_SetSoftwarePriority


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ITC_GetCPUCC:
        push cc
        pop a
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ITC_DeInit:
        MOV       L:0x7f70, #0xff
        MOV       L:0x7f71, #0xff
        MOV       L:0x7f72, #0xff
        MOV       L:0x7f73, #0xff
        MOV       L:0x7f74, #0xff
        MOV       L:0x7f75, #0xff
        MOV       L:0x7f76, #0xff
        MOV       L:0x7f77, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ITC_GetSoftIntStatus:
        CALL      L:ITC_GetCPUCC
        AND       A, #0x28
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ITC_GetSoftwarePriority:
        LD        S:?b0, A
        CLR       S:?b1
        CLR       S:?b2
        LD        A, S:?b0
        AND       A, #0x3
        LDW       X, #0x2
        MUL       X, A
        LD        A, XL
        LDW       X, #0x3
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b2, A
        LD        A, S:?b0
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_3
        SUB       A, #0x2
        JREQ      L:??ITC_GetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_5
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_5
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_5
        SUB       A, #0x3
        JREQ      L:??ITC_GetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_7
        DEC       A
        JREQ      L:??ITC_GetSoftwarePriority_7
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_0:
        LD        A, L:0x7f70
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_1:
        LD        A, L:0x7f71
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_2:
        LD        A, L:0x7f72
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_3:
        LD        A, L:0x7f73
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_4:
        LD        A, L:0x7f74
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_5:
        LD        A, L:0x7f75
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_6:
        LD        A, L:0x7f76
        AND       A, S:?b2
        LD        S:?b1, A
        JRA       L:??ITC_GetSoftwarePriority_8
??ITC_GetSoftwarePriority_7:
        LD        A, L:0x7f77
        AND       A, S:?b2
        LD        S:?b1, A
??ITC_GetSoftwarePriority_8:
        LD        A, S:?b0
        AND       A, #0x3
        LDW       X, #0x2
        MUL       X, A
        EXG       A, XL
        LD        S:?b0, A
        EXG       A, XL
        LD        A, S:?b1
        CALL      L:?srl8_a_a_b0
        LD        S:?b1, A
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ITC_SetSoftwarePriority:
        LD        S:?b2, A
        CLR       S:?b3
        CLR       S:?b4
        LD        A, S:?b2
        AND       A, #0x3
        LDW       X, #0x2
        MUL       X, A
        LD        A, XL
        LDW       X, #0x3
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        LD        S:?b3, A
        LD        A, S:?b2
        AND       A, #0x3
        LDW       X, #0x2
        MUL       X, A
        EXG       A, XL
        LD        S:?b1, A
        EXG       A, XL
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        LD        S:?b4, A
        LD        A, S:?b2
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_0
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_1
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_2
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_3
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_3
        SUB       A, #0x2
        JREQ      L:??ITC_SetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_4
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_5
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_5
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_5
        SUB       A, #0x3
        JREQ      L:??ITC_SetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_6
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_7
        DEC       A
        JREQ      L:??ITC_SetSoftwarePriority_7
        RET
??ITC_SetSoftwarePriority_0:
        LD        A, L:0x7f70
        AND       A, S:?b3
        LD        L:0x7f70, A
        LD        A, L:0x7f70
        OR        A, S:?b4
        LD        L:0x7f70, A
        RET
??ITC_SetSoftwarePriority_1:
        LD        A, L:0x7f71
        AND       A, S:?b3
        LD        L:0x7f71, A
        LD        A, L:0x7f71
        OR        A, S:?b4
        LD        L:0x7f71, A
        RET
??ITC_SetSoftwarePriority_2:
        LD        A, L:0x7f72
        AND       A, S:?b3
        LD        L:0x7f72, A
        LD        A, L:0x7f72
        OR        A, S:?b4
        LD        L:0x7f72, A
        RET
??ITC_SetSoftwarePriority_3:
        LD        A, L:0x7f73
        AND       A, S:?b3
        LD        L:0x7f73, A
        LD        A, L:0x7f73
        OR        A, S:?b4
        LD        L:0x7f73, A
        RET
??ITC_SetSoftwarePriority_4:
        LD        A, L:0x7f74
        AND       A, S:?b3
        LD        L:0x7f74, A
        LD        A, L:0x7f74
        OR        A, S:?b4
        LD        L:0x7f74, A
        RET
??ITC_SetSoftwarePriority_5:
        LD        A, L:0x7f75
        AND       A, S:?b3
        LD        L:0x7f75, A
        LD        A, L:0x7f75
        OR        A, S:?b4
        LD        L:0x7f75, A
        RET
??ITC_SetSoftwarePriority_6:
        LD        A, L:0x7f76
        AND       A, S:?b3
        LD        L:0x7f76, A
        LD        A, L:0x7f76
        OR        A, S:?b4
        LD        L:0x7f76, A
        RET
??ITC_SetSoftwarePriority_7:
        LD        A, L:0x7f77
        AND       A, S:?b3
        LD        L:0x7f77, A
        LD        A, L:0x7f77
        OR        A, S:?b4
        LD        L:0x7f77, A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 510 bytes in section .near_func.text
// 
// 510 bytes of CODE memory
//
//Errors: none
//Warnings: 1
