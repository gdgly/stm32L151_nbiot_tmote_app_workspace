///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:19
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_exti.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC6AE.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_exti.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_exti.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
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
        JREQ      L:??EXTI_SetPinSensitivity_4
        SUB       A, #0x2
        JRNE      ??lb_0
        JP        L:??EXTI_SetPinSensitivity_5
??lb_0:
        SUB       A, #0x2
        JRNE      ??lb_1
        JP        L:??EXTI_SetPinSensitivity_6
??lb_1:
        SUB       A, #0x2
        JRNE      ??lb_2
        JP        L:??EXTI_SetPinSensitivity_7
??lb_2:
        RET
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
        RET
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
        RET
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
        RET
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
        RET
??EXTI_SetPinSensitivity_4:
        LD        A, L:0x50a1
        AND       A, #0xfc
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        RET
??EXTI_SetPinSensitivity_5:
        LD        A, L:0x50a1
        AND       A, #0xf3
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        RET
??EXTI_SetPinSensitivity_6:
        LD        A, L:0x50a1
        AND       A, #0xcf
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        RET
??EXTI_SetPinSensitivity_7:
        LD        A, L:0x50a1
        AND       A, #0x3f
        LD        L:0x50a1, A
        LD        A, S:?b1
        AND       A, #0xef
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a1
        LD        L:0x50a1, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SelectPort:
        TNZ       A
        JRNE      L:??EXTI_SelectPort_0
        BRES      L:0x50ab, #0x5
        RET
??EXTI_SelectPort_0:
        CP        A, #0x2
        JRNE      L:??EXTI_SelectPort_1
        BRES      L:0x50ab, #0x6
        RET
??EXTI_SelectPort_1:
        CP        A, #0x4
        JRNE      L:??EXTI_SelectPort_2
        BRES      L:0x50a5, #0x7
        RET
??EXTI_SelectPort_2:
        CP        A, #0x6
        JRNE      L:??EXTI_SelectPort_3
        BSET      L:0x50a5, #0x7
        RET
??EXTI_SelectPort_3:
        CP        A, #0x10
        JRNE      L:??EXTI_SelectPort_4
        BSET      L:0x50ab, #0x5
        RET
??EXTI_SelectPort_4:
        BSET      L:0x50ab, #0x6
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
        RET
??EXTI_SetHalfPortSelection_1:
        CPL       S:?b1
        LD        A, S:?b1
        AND       A, L:0x50a5
        LD        L:0x50a5, A
        RET
??EXTI_SetHalfPortSelection_0:
        TNZ       S:?b0
        JREQ      L:??EXTI_SetHalfPortSelection_2
        LD        A, S:?b1
        AND       A, #0x7f
        OR        A, L:0x50ab
        LD        L:0x50ab, A
        RET
??EXTI_SetHalfPortSelection_2:
        LD        A, S:?b1
        AND       A, #0x7f
        CPL       A
        AND       A, L:0x50ab
        LD        L:0x50ab, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_SetPortSensitivity:
        LD        S:?b1, A
        LD        A, S:?b1
        AND       A, #0xf0
        CP        A, #0x0
        JRNE      L:??EXTI_SetPortSensitivity_0
        LDW       X, #0x3
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50a2
        LD        L:0x50a2, A
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        LD        A, S:?b1
        CALL      L:?sll16_x_x_a
        LD        A, XL
        OR        A, L:0x50a2
        LD        L:0x50a2, A
        RET
??EXTI_SetPortSensitivity_0:
        LD        A, S:?b1
        AND       A, #0xf
        LDW       X, #0x3
        CALL      L:?sll16_x_x_a
        LD        A, XL
        CPL       A
        AND       A, L:0x50aa
        LD        L:0x50aa, A
        LD        A, S:?b1
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
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_GetPinSensitivity:
        CLR       S:?b0
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
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_1:
        LD        A, L:0x50a0
        AND       A, #0xc
        SRL       A
        SRL       A
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_2:
        LD        A, L:0x50a0
        AND       A, #0x30
        SWAP      A
        AND       A, #0xf
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_3:
        LD        A, L:0x50a0
        CALL      L:?srl8_a_a_6
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_4:
        LD        A, L:0x50a1
        AND       A, #0x3
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_5:
        LD        A, L:0x50a1
        AND       A, #0xc
        SRL       A
        SRL       A
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_6:
        LD        A, L:0x50a1
        AND       A, #0x30
        SWAP      A
        AND       A, #0xf
        LD        S:?b0, A
        JRA       L:??EXTI_GetPinSensitivity_8
??EXTI_GetPinSensitivity_7:
        LD        A, L:0x50a1
        CALL      L:?srl8_a_a_6
        LD        S:?b0, A
??EXTI_GetPinSensitivity_8:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
EXTI_GetPortSensitivity:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, S:?b0
        AND       A, #0xf0
        CP        A, #0x0
        JRNE      L:??EXTI_GetPortSensitivity_0
        LD        A, L:0x50a2
        CLRW      X
        LD        XL, A
        LD        A, S:?b0
        CALL      L:?sra16_x_x_a
        LD        A, XL
        AND       A, #0x3
        LD        S:?b1, A
        JRA       L:??EXTI_GetPortSensitivity_1
??EXTI_GetPortSensitivity_0:
        LD        A, S:?b0
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
        CLR       A
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
        RET
??EXTI_GetITStatus_0:
        LD        A, XL
        AND       A, L:0x50a3
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
        RET
??EXTI_ClearITPendingBit_0:
        LD        A, S:?b1
        LD        L:0x50a3, A
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 731 bytes in section .near_func.text
// 
// 731 bytes of CODE memory
//
//Errors: none
//Warnings: none
