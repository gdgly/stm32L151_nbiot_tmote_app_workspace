///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:20
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\User\main.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWB7FA.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\User\main.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\main.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN ?b8
        EXTERN Delay_US_FuncType1
        EXTERN Delay_US_Normal
        EXTERN GPIO_ReadInputDataBit
        EXTERN GPIO_ResetBits
        EXTERN GPIO_SetBits
        EXTERN Stm8_HSIClock_Init
        EXTERN Stm8_OOK_Init

        PUBLIC OOKData
        PUBLIC OOKRecvData
        PUBLIC bma1
        PUBLIC bma2
        PUBLIC bma3
        PUBLIC bma4
        PUBLIC bt_auto
        PUBLIC decode_ok
        PUBLIC hh_w
        PUBLIC ll_w
        PUBLIC ma_x
        PUBLIC main
        PUBLIC mma1
        PUBLIC mma2
        PUBLIC mma3
        PUBLIC mma4
        PUBLIC mmb1
        PUBLIC mmb2
        PUBLIC mmb3
        PUBLIC mmb4
        PUBLIC old_rc5
        PUBLIC rf_data
        PUBLIC rf_ok
        PUBLIC rf_ok1
        PUBLIC rf_ok2
        PUBLIC rfkey1
        PUBLIC rfkey2
        PUBLIC rfkeyflag
        PUBLIC s
        PUBLIC s1
        PUBLIC tb_ok


        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
OOKData:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
old_rc5:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
tb_ok:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
bt_auto:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
bma1:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
bma2:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
bma3:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
bma4:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mma1:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mma2:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mma3:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mma4:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mmb1:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mmb2:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mmb3:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
mmb4:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rf_ok1:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rf_ok2:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rf_ok:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rf_data:
        DS8 4

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
ma_x:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
hh_w:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
ll_w:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
s:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
s1:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
decode_ok:
        DS8 2

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rfkeyflag:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rfkey1:
        DS8 1

        SECTION `.near.bss`:DATA:REORDER:NOROOT(0)
rfkey2:
        DS8 1

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
main:
        PUSH      S:?b8
        CLR       A
        CALL      L:Stm8_HSIClock_Init
        CALL      L:Stm8_OOK_Init
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
??main_0:
        CALL      L:OOKRecvData
        LDW       X, L:decode_ok
        CPW       X, #0x1
        JRNE      L:??main_0
        LD        A, L:rf_data + 1
        ADD       A, L:rf_data
        ADD       A, L:rf_data + 2
        LD        L:rf_data + 3, A
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x98
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        LDW       X, #0x5
        CALL      L:Delay_US_FuncType1
        CLR       S:?b8
??main_1:
        LD        A, S:?b8
        CP        A, #0x8
        JRNC      L:??main_2
        BTJF      L:rf_data, #0x7, L:??main_3
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x34
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        JRA       L:??main_4
??main_3:
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x14
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
??main_4:
        LD        A, L:rf_data
        SLL       A
        LD        L:rf_data, A
        LDW       X, #0x5
        CALL      L:Delay_US_FuncType1
        INC       S:?b8
        JRA       L:??main_1
??main_2:
        CLR       S:?b8
??main_5:
        LD        A, S:?b8
        CP        A, #0x8
        JRNC      L:??main_6
        BTJF      L:rf_data + 1, #0x7, L:??main_7
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x34
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        JRA       L:??main_8
??main_7:
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x14
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
??main_8:
        LD        A, L:rf_data + 1
        SLL       A
        LD        L:rf_data + 1, A
        LDW       X, #0x5
        CALL      L:Delay_US_FuncType1
        INC       S:?b8
        JRA       L:??main_5
??main_6:
        CLR       S:?b8
??main_9:
        LD        A, S:?b8
        CP        A, #0x8
        JRNC      L:??main_10
        BTJF      L:rf_data + 2, #0x7, L:??main_11
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x34
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        JRA       L:??main_12
??main_11:
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x14
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
??main_12:
        LD        A, L:rf_data + 2
        SLL       A
        LD        L:rf_data + 2, A
        LDW       X, #0x5
        CALL      L:Delay_US_FuncType1
        INC       S:?b8
        JRA       L:??main_9
??main_10:
        CLR       S:?b8
??main_13:
        LD        A, S:?b8
        CP        A, #0x8
        JRNC      L:??main_14
        BTJF      L:rf_data + 3, #0x7, L:??main_15
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x34
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        JRA       L:??main_16
??main_15:
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x14
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
??main_16:
        LD        A, L:rf_data + 3
        SLL       A
        LD        L:rf_data + 3, A
        LDW       X, #0x5
        CALL      L:Delay_US_FuncType1
        INC       S:?b8
        JRA       L:??main_13
??main_14:
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_SetBits
        LDW       X, #0x64
        CALL      L:Delay_US_FuncType1
        LD        A, #0x4
        LDW       X, #0x5000
        CALL      L:GPIO_ResetBits
        CLRW      X
        LDW       L:decode_ok, X
        JP        L:??main_0

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
OOKRecvData:
        PUSH      S:?b8
??OOKRecvData_0:
        LD        A, #0x2
        LDW       X, #0x500a
        CALL      L:GPIO_ReadInputDataBit
        LD        L:OOKData, A
        LD        A, L:OOKData
        TNZ       A
        JRNE      L:??OOKRecvData_1
        LDW       X, L:ll_w
        INCW      X
        LDW       L:ll_w, X
        CLR       L:old_rc5
        JP        L:??OOKRecvData_2
??OOKRecvData_1:
        LDW       X, L:hh_w
        INCW      X
        LDW       L:hh_w, X
        LD        A, L:old_rc5
        TNZ       A
        JREQ      ??lb_0
        JP        L:??OOKRecvData_3
??lb_0:
        LDW       X, L:hh_w
        CPW       X, #0x2
        JRC       L:??OOKRecvData_4
        LDW       X, L:hh_w
        CPW       X, #0x6
        JRNC      L:??OOKRecvData_4
        LDW       X, L:ll_w
        CPW       X, #0x64
        JRC       L:??OOKRecvData_4
        LDW       X, L:ll_w
        CPW       X, #0x83
        JRNC      L:??OOKRecvData_4
        MOV       L:tb_ok, #0x1
        CLRW      X
        LDW       L:ma_x, X
        CLR       L:bma1
        CLR       L:bma2
        CLR       L:bma3
        CLR       L:bma4
        JP        L:??OOKRecvData_5
??OOKRecvData_4:
        LD        A, L:tb_ok
        TNZ       A
        JREQ      L:??OOKRecvData_6
        LDW       X, L:ll_w
        CPW       X, #0x8
        JRC       L:??OOKRecvData_6
        LDW       X, L:ll_w
        CPW       X, #0xe
        JRNC      L:??OOKRecvData_6
        LDW       X, L:ma_x
        INCW      X
        LDW       L:ma_x, X
        LDW       X, L:ma_x
        CPW       X, #0x18
        JRNC      ??lb_1
        JP        L:??OOKRecvData_5
??lb_1:
        LD        A, L:rf_ok1
        TNZ       A
        JRNE      L:??OOKRecvData_7
        MOV       L:mma1, L:bma1
        MOV       L:mma2, L:bma2
        MOV       L:mma3, L:bma3
        MOV       L:mma4, L:bma4
        MOV       L:rf_ok1, #0x1
        CLR       L:tb_ok
        LDW       X, #0x2710
        LDW       L:s, X
        JP        L:??OOKRecvData_5
??OOKRecvData_7:
        MOV       L:mmb1, L:bma1
        MOV       L:mmb2, L:bma2
        MOV       L:mmb3, L:bma3
        MOV       L:mmb4, L:bma4
        MOV       L:rf_ok2, #0x1
        CLR       L:tb_ok
        JP        L:??OOKRecvData_5
??OOKRecvData_6:
        LD        A, L:tb_ok
        TNZ       A
        JRNE      ??lb_2
        JP        L:??OOKRecvData_8
??lb_2:
        LDW       X, L:ll_w
        CPW       X, #0x2
        JRNC      ??lb_3
        JP        L:??OOKRecvData_8
??lb_3:
        LDW       X, L:ll_w
        CPW       X, #0x8
        JRC       ??lb_4
        JP        L:??OOKRecvData_8
??lb_4:
        LDW       X, L:ma_x
        CPW       X, #0x18
        JRC       ??lb_5
        JP        L:LWRD(??OOKRecvData_9)
??lb_5:
        SLLW      X
        LDW       X, (L:??switch_table_0,X)
        JP        (X)
??OOKRecvData_10:
        BSET      L:bma1, #0x7
        JP        L:??OOKRecvData_9
??OOKRecvData_11:
        BSET      L:bma1, #0x6
        JP        L:??OOKRecvData_9
??OOKRecvData_12:
        BSET      L:bma1, #0x5
        JP        L:??OOKRecvData_9
??OOKRecvData_13:
        BSET      L:bma1, #0x4
        JP        L:??OOKRecvData_9
??OOKRecvData_14:
        BSET      L:bma1, #0x3
        JP        L:??OOKRecvData_9
??OOKRecvData_15:
        BSET      L:bma1, #0x2
        JP        L:??OOKRecvData_9
??OOKRecvData_16:
        BSET      L:bma1, #0x1
        JP        L:??OOKRecvData_9
??OOKRecvData_17:
        BSET      L:bma1, #0x0
        JP        L:??OOKRecvData_9
??OOKRecvData_18:
        BSET      L:bma2, #0x7
        JP        L:??OOKRecvData_9
??OOKRecvData_19:
        BSET      L:bma2, #0x6
        JP        L:??OOKRecvData_9
??OOKRecvData_20:
        BSET      L:bma2, #0x5
        JP        L:??OOKRecvData_9
??OOKRecvData_21:
        BSET      L:bma2, #0x4
        JP        L:??OOKRecvData_9
??OOKRecvData_22:
        BSET      L:bma2, #0x3
        JRA       L:??OOKRecvData_9
??OOKRecvData_23:
        BSET      L:bma2, #0x2
        JRA       L:??OOKRecvData_9
??OOKRecvData_24:
        BSET      L:bma2, #0x1
        JRA       L:??OOKRecvData_9
??OOKRecvData_25:
        BSET      L:bma2, #0x0
        JRA       L:??OOKRecvData_9
??OOKRecvData_26:
        BSET      L:bma3, #0x7
        JRA       L:??OOKRecvData_9
??OOKRecvData_27:
        BSET      L:bma3, #0x6
        JRA       L:??OOKRecvData_9
??OOKRecvData_28:
        BSET      L:bma3, #0x5
        JRA       L:??OOKRecvData_9
??OOKRecvData_29:
        BSET      L:bma3, #0x4
        JRA       L:??OOKRecvData_9
??OOKRecvData_30:
        BSET      L:bma3, #0x3
        JRA       L:??OOKRecvData_9
??OOKRecvData_31:
        BSET      L:bma3, #0x2
        JRA       L:??OOKRecvData_9
??OOKRecvData_32:
        BSET      L:bma3, #0x1
        JRA       L:??OOKRecvData_9
??OOKRecvData_33:
        BSET      L:bma3, #0x0
        LD        A, L:rf_ok1
        TNZ       A
        JRNE      L:??OOKRecvData_34
        MOV       L:mma1, L:bma1
        MOV       L:mma2, L:bma2
        MOV       L:mma3, L:bma3
        MOV       L:rf_ok1, #0x1
        CLR       L:tb_ok
        LDW       X, #0x3e8
        LDW       L:s, X
        JRA       L:??OOKRecvData_9
??OOKRecvData_34:
        MOV       L:mmb1, L:bma1
        MOV       L:mmb2, L:bma2
        MOV       L:mmb3, L:bma3
        MOV       L:rf_ok2, #0x1
        CLR       L:tb_ok
??OOKRecvData_9:
        LDW       X, L:ma_x
        INCW      X
        LDW       L:ma_x, X
        JRA       L:??OOKRecvData_5
??OOKRecvData_8:
        CLRW      X
        LDW       L:ma_x, X
        CLR       L:tb_ok
        CLR       L:bt_auto
        CLR       L:bma1
        CLR       L:bma2
        CLR       L:bma3
        CLRW      X
        INCW      X
        LDW       L:hh_w, X
        CLRW      X
        LDW       L:ll_w, X
??OOKRecvData_5:
        CLRW      X
        LDW       L:ll_w, X
        CLRW      X
        INCW      X
        LDW       L:hh_w, X
??OOKRecvData_3:
        MOV       L:old_rc5, #0x1
??OOKRecvData_2:
        LD        A, L:rf_ok1
        TNZ       A
        JREQ      L:??OOKRecvData_35
        LDW       X, L:s
        DECW      X
        LDW       L:s, X
        LDW       X, L:s
        TNZW      X
        JRNE      L:??OOKRecvData_36
        CLR       L:rf_ok1
??OOKRecvData_36:
        LD        A, L:rf_ok2
        TNZ       A
        JREQ      L:??OOKRecvData_35
        LD        A, L:mmb1
        CP        A, L:mma1
        JRNE      L:??OOKRecvData_37
        LD        A, L:mmb2
        CP        A, L:mma2
        JRNE      L:??OOKRecvData_37
        LD        A, L:mmb3
        CP        A, L:mma3
        JRNE      L:??OOKRecvData_37
        MOV       L:rf_ok, #0x1
        CLR       L:rf_ok1
        CLR       L:rf_ok2
        JRA       L:??OOKRecvData_35
??OOKRecvData_37:
        CLR       L:rf_ok
        CLR       L:rf_ok1
        CLR       L:rf_ok2
??OOKRecvData_35:
        LD        A, L:rf_ok
        TNZ       A
        JREQ      L:??OOKRecvData_38
        CLR       L:rf_ok
        MOV       L:rf_data, L:mma1
        MOV       L:rf_data + 1, L:mma2
        MOV       L:rf_data + 2, L:mma3
        CLRW      X
        INCW      X
        LDW       L:decode_ok, X
        JRA       L:??OOKRecvData_39
??OOKRecvData_38:
        CLR       S:?b8
??OOKRecvData_40:
        LD        A, S:?b8
        CP        A, #0x2a
        JRC       ??lb_6
        JP        L:??OOKRecvData_0
??lb_6:
        CALL      L:Delay_US_Normal
        INC       S:?b8
        JRA       L:??OOKRecvData_40
??OOKRecvData_39:
        POP       S:?b8
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
??switch_table_0:
        DATA
        DC16      LWRD(??OOKRecvData_10)
        DC16      LWRD(??OOKRecvData_11)
        DC16      LWRD(??OOKRecvData_12)
        DC16      LWRD(??OOKRecvData_13)
        DC16      LWRD(??OOKRecvData_14)
        DC16      LWRD(??OOKRecvData_15)
        DC16      LWRD(??OOKRecvData_16)
        DC16      LWRD(??OOKRecvData_17)
        DC16      LWRD(??OOKRecvData_18)
        DC16      LWRD(??OOKRecvData_19)
        DC16      LWRD(??OOKRecvData_20)
        DC16      LWRD(??OOKRecvData_21)
        DC16      LWRD(??OOKRecvData_22)
        DC16      LWRD(??OOKRecvData_23)
        DC16      LWRD(??OOKRecvData_24)
        DC16      LWRD(??OOKRecvData_25)
        DC16      LWRD(??OOKRecvData_26)
        DC16      LWRD(??OOKRecvData_27)
        DC16      LWRD(??OOKRecvData_28)
        DC16      LWRD(??OOKRecvData_29)
        DC16      LWRD(??OOKRecvData_30)
        DC16      LWRD(??OOKRecvData_31)
        DC16      LWRD(??OOKRecvData_32)
        DC16      LWRD(??OOKRecvData_33)

        END
// 
//    38 bytes in section .near.bss
// 1 122 bytes in section .near_func.text
// 
// 1 122 bytes of CODE memory
//    38 bytes of DATA memory
//
//Errors: none
//Warnings: none
