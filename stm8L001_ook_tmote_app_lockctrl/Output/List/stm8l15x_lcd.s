///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:12:59
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_lcd.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW71A8.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_lcd.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_lcd.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4

        PUBLIC LCD_BlinkConfig
        PUBLIC LCD_ClearFlag
        PUBLIC LCD_ClearITPendingBit
        PUBLIC LCD_Cmd
        PUBLIC LCD_ContrastConfig
        PUBLIC LCD_DeInit
        PUBLIC LCD_DeadTimeConfig
        PUBLIC LCD_GetFlagStatus
        PUBLIC LCD_GetITStatus
        PUBLIC LCD_HighDriveCmd
        PUBLIC LCD_ITConfig
        PUBLIC LCD_Init
        PUBLIC LCD_PageSelect
        PUBLIC LCD_PortMaskConfig
        PUBLIC LCD_PulseOnDurationConfig
        PUBLIC LCD_WriteRAM


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_DeInit:
        CLR       A
        CLR       L:0x5400
        CLR       L:0x5401
        CLR       L:0x5402
        CLR       L:0x5403
        CLR       A
??LCD_DeInit_0:
        CP        A, #0x5
        JRNC      L:??LCD_DeInit_1
        CLRW      X
        LD        XL, A
        ADDW      X, #0x5404
        CLR       (X)
        INC       A
        JRA       L:??LCD_DeInit_0
??LCD_DeInit_1:
        CLR       A
??LCD_DeInit_2:
        CP        A, #0x16
        JRNC      L:??LCD_DeInit_3
        CLRW      X
        LD        XL, A
        ADDW      X, #0x540c
        CLR       (X)
        INC       A
        JRA       L:??LCD_DeInit_2
??LCD_DeInit_3:
        CLR       L:0x542f
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_Init:
        LD        S:?b4, A
        LD        A, L:0x5403
        AND       A, #0xf
        LD        L:0x5403, A
        LD        A, L:0x5403
        OR        A, S:?b4
        LD        L:0x5403, A
        LD        A, L:0x5403
        AND       A, #0xf0
        LD        L:0x5403, A
        LD        A, L:0x5403
        OR        A, S:?b0
        LD        L:0x5403, A
        LD        A, L:0x5400
        AND       A, #0xf9
        LD        L:0x5400, A
        BRES      L:0x542f, #0x1
        LD        A, S:?b1
        CP        A, #0x20
        JRNE      L:??LCD_Init_0
        LD        A, S:?b1
        SWAP      A
        AND       A, #0xf
        OR        A, L:0x542f
        LD        L:0x542f, A
        JRA       L:??LCD_Init_1
??LCD_Init_0:
        LD        A, S:?b1
        AND       A, #0xf
        OR        A, L:0x5400
        LD        L:0x5400, A
??LCD_Init_1:
        BRES      L:0x5400, #0x0
        BRES      L:0x542f, #0x0
        LD        A, S:?b2
        CP        A, #0x10
        JRNE      L:??LCD_Init_2
        LD        A, S:?b2
        AND       A, #0xf
        OR        A, L:0x5400
        LD        L:0x5400, A
        LD        A, S:?b2
        SWAP      A
        AND       A, #0xf
        OR        A, L:0x542f
        LD        L:0x542f, A
        JRA       L:??LCD_Init_3
??LCD_Init_2:
        LD        A, S:?b2
        AND       A, #0xf
        OR        A, L:0x5400
        LD        L:0x5400, A
??LCD_Init_3:
        BRES      L:0x5401, #0x0
        LD        A, L:0x5401
        OR        A, S:?b3
        LD        L:0x5401, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_PortMaskConfig:
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
        LD        XL, A
        LD        A, S:?b0
        ADDW      X, #0x5404
        LD        (X), A
        SUBW      X, #0x5404
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_Cmd:
        TNZ       A
        JREQ      L:??LCD_Cmd_0
        BSET      L:0x5402, #0x6
        JRA       L:??LCD_Cmd_1
??LCD_Cmd_0:
        BRES      L:0x5402, #0x6
??LCD_Cmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_HighDriveCmd:
        TNZ       A
        JREQ      L:??LCD_HighDriveCmd_0
        BSET      L:0x5401, #0x4
        JRA       L:??LCD_HighDriveCmd_1
??LCD_HighDriveCmd_0:
        BRES      L:0x5401, #0x4
??LCD_HighDriveCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_PulseOnDurationConfig:
        LD        S:?b0, A
        LD        A, L:0x5401
        AND       A, #0x1f
        LD        L:0x5401, A
        LD        A, L:0x5401
        OR        A, S:?b0
        LD        L:0x5401, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_DeadTimeConfig:
        LD        S:?b0, A
        LD        A, L:0x5402
        AND       A, #0xf8
        LD        L:0x5402, A
        LD        A, L:0x5402
        OR        A, S:?b0
        LD        L:0x5402, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_BlinkConfig:
        LD        S:?b1, A
        LD        A, L:0x5400
        AND       A, #0x3f
        LD        L:0x5400, A
        LD        A, L:0x5400
        OR        A, S:?b1
        LD        L:0x5400, A
        LD        A, L:0x5400
        AND       A, #0xc7
        LD        L:0x5400, A
        LD        A, L:0x5400
        OR        A, S:?b0
        LD        L:0x5400, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_ContrastConfig:
        LD        S:?b0, A
        LD        A, L:0x5401
        AND       A, #0xf1
        LD        L:0x5401, A
        LD        A, L:0x5401
        OR        A, S:?b0
        LD        L:0x5401, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_WriteRAM:
        LD        S:?b1, A
        CLRW      X
        LD        A, S:?b1
        LD        XL, A
        LD        A, S:?b0
        ADDW      X, #0x540c
        LD        (X), A
        SUBW      X, #0x540c
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_PageSelect:
        LD        S:?b0, A
        BRES      L:0x542f, #0x2
        LD        A, L:0x542f
        OR        A, S:?b0
        LD        L:0x542f, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_ITConfig:
        TNZ       A
        JREQ      L:??LCD_ITConfig_0
        BSET      L:0x5402, #0x5
        JRA       L:??LCD_ITConfig_1
??LCD_ITConfig_0:
        BRES      L:0x5402, #0x5
??LCD_ITConfig_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_GetFlagStatus:
        CLR       S:?b0
        BTJF      L:0x5402, #0x4, L:??LCD_GetFlagStatus_0
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??LCD_GetFlagStatus_1
??LCD_GetFlagStatus_0:
        CLR       S:?b0
??LCD_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_ClearFlag:
        BSET      L:0x5402, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_GetITStatus:
        CLR       S:?b1
        CLR       S:?b0
        LD        A, L:0x5402
        AND       A, #0x20
        LD        S:?b0, A
        BTJF      L:0x5402, #0x4, L:??LCD_GetITStatus_0
        TNZ       S:?b0
        JREQ      L:??LCD_GetITStatus_0
        LD        A, #0x1
        LD        S:?b1, A
        JRA       L:??LCD_GetITStatus_1
??LCD_GetITStatus_0:
        CLR       S:?b1
??LCD_GetITStatus_1:
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
LCD_ClearITPendingBit:
        BSET      L:0x5402, #0x3
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 425 bytes in section .near_func.text
// 
// 425 bytes of CODE memory
//
//Errors: none
//Warnings: none
