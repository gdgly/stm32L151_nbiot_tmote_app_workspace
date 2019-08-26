///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  13:23:55
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_exti.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW4FE0.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_exti.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_exti.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?sll16_x_x_a
        EXTERN ?sra16_x_x_a
        EXTERN ?srl8_a_a_6
        EXTERN ?w0

        PUBLIC EXTI_ClearITPendingBit
        PUBLIC EXTI_DeInit
        PUBLIC EXTI_GetITStatus
        PUBLIC EXTI_GetPinSensitivity
        PUBLIC EXTI_GetPortSensitivity
        PUBLIC EXTI_SelectPort
        PUBLIC EXTI_SetHalfPortSelection
        PUBLIC EXTI_SetPinSensitivity
        PUBLIC EXTI_SetPortSensitivity


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_DeInit:
        CLR       L:0x50a0
        CLR       L:0x50a1
        CLR       L:0x50a2
        CLR       L:0x50aa
        MOV       L:0x50a3, #0xff
        MOV       L:0x50a4, #0xff
        CLR       L:0x50a5
        CLR       L:0x50ab
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SetPinSensitivity:
        LD        S:?b1, A
        LD        A, S:?b1
        TNZ       A
        JREQ      L:??EXTI_SetPinSensitivity_0
        SUB       A, #0x2
        JREQ      L:??EXTI_SetPinSensitivity_1
        SUB       A, #0x2
        JREQ      L:??EXTI_SetPinSensitivity_2
        SUB       A, #0x2
        JREQ      L:??EXTI_SetPinSensitivity_3
        SUB       A, #0xa
        JRNE      ??lb_0
        JP        L:??EXTI_SetPinSensitivity_4
??lb_0:
        SUB       A, #0x2
        JRNE      ??lb_1
        JP        L:??EXTI_SetPinSensitivity_5
??lb_1:
        SUB       A, #0x2
        JRNE      ??lb_2
        JP        L:??EXTI_SetPinSensitivity_6
??lb_2:
        SUB       A, #0x2
        JRNE      ??lb_3
        JP        L:??EXTI_SetPinSensitivity_7
??lb_3:
        JP        L:??EXTI_SetPinSensitivity_8
??EXTI_SetPinSensitivity_0:
        LD        A, L:0x50a0
        AND       A, #0xfc
        LD        L:0x50a0, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a0
        LD        L:0x50a0, A
        JP        L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_1:
        LD        A, L:0x50a0
        AND       A, #0xf3
        LD        L:0x50a0, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a0
        LD        L:0x50a0, A
        JP        L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_2:
        LD        A, L:0x50a0
        AND       A, #0xcf
        LD        L:0x50a0, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a0
        LD        L:0x50a0, A
        JP        L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_3:
        LD        A, L:0x50a0
        AND       A, #0x3f
        LD        L:0x50a0, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a0
        LD        L:0x50a0, A
        JP        L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_4:
        LD        A, L:0x50a1
        AND       A, #0xfc
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        JRA       L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_5:
        LD        A, L:0x50a1
        AND       A, #0xf3
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        JRA       L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_6:
        LD        A, L:0x50a1
        AND       A, #0xcf
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        JRA       L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_7:
        LD        A, L:0x50a1
        AND       A, #0x3f
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        JRA       L:??EXTI_SetPinSensitivity_9
??EXTI_SetPinSensitivity_8:
??EXTI_SetPinSensitivity_9:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SelectPort:
        TNZ       A
        JRNE      L:??EXTI_SelectPort_0
        BRES      L:0x50ab, #0x5
        JRA       L:??EXTI_SelectPort_1
??EXTI_SelectPort_0:
        CP        A, #0x2
        JRNE      L:??EXTI_SelectPort_2
        BRES      L:0x50ab, #0x6
        JRA       L:??EXTI_SelectPort_1
??EXTI_SelectPort_2:
        CP        A, #0x4
        JRNE      L:??EXTI_SelectPort_3
        BRES      L:0x50a5, #0x7
        JRA       L:??EXTI_SelectPort_1
??EXTI_SelectPort_3:
        CP        A, #0x6
        JRNE      L:??EXTI_SelectPort_4
        BSET      L:0x50a5, #0x7
        JRA       L:??EXTI_SelectPort_1
??EXTI_SelectPort_4:
        CP        A, #0x10
        JRNE      L:??EXTI_SelectPort_5
        BSET      L:0x50ab, #0x5
        JRA       L:??EXTI_SelectPort_1
??EXTI_SelectPort_5:
        BSET      L:0x50ab, #0x6
??EXTI_SelectPort_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SetHalfPortSelection:
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0x80
        CP        A, #0x0
        JRNE      L:??EXTI_SetHalfPortSelection_0
        TNZ       S:?b0
        JREQ      L:??EXTI_SetHalfPortSelection_1
        LD        A, L:0x50a5
        OR        A, S:?b1
        LD        L:0x50a5, A
        JRA       L:??EXTI_SetHalfPortSelection_2
??EXTI_SetHalfPortSelection_1:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x50a5
        LD        L:0x50a5, A
        JRA       L:??EXTI_SetHalfPortSelection_2
??EXTI_SetHalfPortSelection_0:
        TNZ       S:?b0
        JREQ      L:??EXTI_SetHalfPortSelection_3
        LD        A, S:?b1
        AND       A, #0x7f
        OR        A, L:0x50ab
        LD        L:0x50ab, A
        JRA       L:??EXTI_SetHalfPortSelection_2
??EXTI_SetHalfPortSelection_3:
        LD        A, S:?b1
        AND       A, #0x7f
        CPL       A
        AND       A, L:0x50ab
        LD        L:0x50ab, A
??EXTI_SetHalfPortSelection_2:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SetPortSensitivity:
        LD        S:?b2, A
        LD        A, S:?b2
        AND       A, #0xf0
        CP        A, #0x0
        JRNE      L:??EXTI_SetPortSensitivity_0
        LDW       X, #0x3
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50a2
        LD        L:0x50a2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a2
        LD        L:0x50a2, A
        JRA       L:??EXTI_SetPortSensitivity_1
??EXTI_SetPortSensitivity_0:
        LD        A, S:?b2
        AND       A, #0xf
        LDW       X, #0x3
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50aa
        LD        L:0x50aa, A
        LD        A, S:?b2
        AND       A, #0xf
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50aa
        LD        L:0x50aa, A
??EXTI_SetPortSensitivity_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_GetPinSensitivity:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, S:?b1
        TNZ       A
        JREQ      L:??EXTI_GetPinSensitivity_0
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_1
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_2
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_3
        SUB       A, #0xa
        JREQ      L:??EXTI_GetPinSensitivity_4
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_5
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_6
        SUB       A, #0x2
        JREQ      L:??EXTI_GetPinSensitivity_7
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_0:
        LD        A, L:0x50a0
        AND       A, #0x3
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_1:
        LD        A, L:0x50a0
        AND       A, #0xc
        SRL       A
        SRL       A
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_2:
        LD        A, L:0x50a0
        AND       A, #0x30
        SWAP      A
        AND       A, #0xf
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_3:
        LD        A, L:0x50a0
        CALL      L:?srl8_a_a_6
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_4:
        LD        A, L:0x50a1
        AND       A, #0x3
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_5:
        LD        A, L:0x50a1
        AND       A, #0xc
        SRL       A
        SRL       A
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_6:
        LD        A, L:0x50a1
        AND       A, #0x30
        SWAP      A
        AND       A, #0xf
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_7:
        LD        A, L:0x50a1
        CALL      L:?srl8_a_a_6
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_9
??EXTI_GetPinSensitivity_8:
??EXTI_GetPinSensitivity_9:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_GetPortSensitivity:
        LD        S:?b2, A
        CLR       S:?b1
        LD        A, S:?b2
        AND       A, #0xf0
        CP        A, #0x0
        JRNE      L:??EXTI_GetPortSensitivity_0
        LD        A, L:0x50a2
        CLRW      X
        LD        XL, A
        LD        A, S:?b2
        CALL      L:?sra16_x_x_a
        LD        A, XL
        AND       A, #0x3
        LD        S:?b1, A
        JRA       L:??EXTI_GetPortSensitivity_1
??EXTI_GetPortSensitivity_0:
        LD        A, S:?b2
        AND       A, #0xf
        LD        S:?b0, A
        LD        A, L:0x50aa
        CLRW      X
        LD        XL, A
        LD        A, S:?b0
        CALL      L:?sra16_x_x_a
        LD        A, XL
        AND       A, #0x3
        LD        S:?b1, A
??EXTI_GetPortSensitivity_1:
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_GetITStatus:
        CLR       S:?b0
        LDW       Y, X
        RLWA      Y, A
        AND       A, #0xff
        RLWA      Y, A
        AND       A, #0x0
        RLWA      Y, A
        CPW       Y, #0x100
        JRNE      L:??EXTI_GetITStatus_0
        LD        A, XL
        AND       A, L:0x50a4
        LD        S:?b0, A
        JRA       L:??EXTI_GetITStatus_1
??EXTI_GetITStatus_0:
        LD        A, XL
        AND       A, L:0x50a3
        LD        S:?b0, A
??EXTI_GetITStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_ClearITPendingBit:
        LDW       S:?w0, X
        CLRW      Y
        LDW       X, S:?w0
        RLWA      X, A
        AND       A, #0xff
        RLWA      X, A
        AND       A, #0x0
        RLWA      X, A
        LDW       Y, X
        CPW       Y, #0x100
        JRNE      L:??EXTI_ClearITPendingBit_0
        LD        A, S:?b1
        LD        L:0x50a4, A
        JRA       L:??EXTI_ClearITPendingBit_1
??EXTI_ClearITPendingBit_0:
        LD        A, S:?b1
        LD        L:0x50a3, A
??EXTI_ClearITPendingBit_1:
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 772 bytes in section .near_func.text
// 
// 772 bytes of CODE memory
//
//Errors: none
//Warnings: none
