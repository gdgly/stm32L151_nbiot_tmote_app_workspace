///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                29/Feb/2020  14:27:25
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_rtc.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWCDDA.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_rtc.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_rtc.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b10
        EXTERN ?b11
        EXTERN ?b12
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b4
        EXTERN ?b5
        EXTERN ?b6
        EXTERN ?b7
        EXTERN ?b8
        EXTERN ?b9
        EXTERN ?epilogue_l2
        EXTERN ?epilogue_w4
        EXTERN ?push_l2
        EXTERN ?push_w4
        EXTERN ?sll8_a_a_5
        EXTERN ?srl16_x_x_4
        EXTERN ?srl8_a_a_5
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w4
        EXTERN ?w5

        PUBLIC RTC_AlarmCmd
        PUBLIC RTC_AlarmStructInit
        PUBLIC RTC_AlarmSubSecondConfig
        PUBLIC RTC_BypassShadowCmd
        PUBLIC RTC_CalibOutputCmd
        PUBLIC RTC_CalibOutputConfig
        PUBLIC RTC_ClearFlag
        PUBLIC RTC_ClearITPendingBit
        PUBLIC RTC_DateStructInit
        PUBLIC RTC_DayLightSavingConfig
        PUBLIC RTC_DeInit
        PUBLIC RTC_EnterInitMode
        PUBLIC RTC_ExitInitMode
        PUBLIC RTC_GetAlarm
        PUBLIC RTC_GetDate
        PUBLIC RTC_GetFlagStatus
        PUBLIC RTC_GetITStatus
        PUBLIC RTC_GetStoreOperation
        PUBLIC RTC_GetSubSecond
        PUBLIC RTC_GetTime
        PUBLIC RTC_GetWakeUpCounter
        PUBLIC RTC_ITConfig
        PUBLIC RTC_Init
        PUBLIC RTC_OutputConfig
        PUBLIC RTC_RatioCmd
        PUBLIC RTC_SetAlarm
        PUBLIC RTC_SetDate
        PUBLIC RTC_SetTime
        PUBLIC RTC_SetWakeUpCounter
        PUBLIC RTC_SmoothCalibConfig
        PUBLIC RTC_StructInit
        PUBLIC RTC_SynchroShiftConfig
        PUBLIC RTC_TamperCmd
        PUBLIC RTC_TamperFilterConfig
        PUBLIC RTC_TamperLevelConfig
        PUBLIC RTC_TamperPinsPrechargeDuration
        PUBLIC RTC_TamperSamplingFreqConfig
        PUBLIC RTC_TimeStructInit
        PUBLIC RTC_WaitForSynchro
        PUBLIC RTC_WakeUpClockConfig
        PUBLIC RTC_WakeUpCmd
        PUBLIC RTC_WriteProtectionCmd


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_DeInit:
        CALL      L:?push_l2
        PUSH      S:?b12
        CLR       S:?b12
        CLR       S:?b11
        CLR       S:?b10
        CLR       S:?b9
        CLR       S:?b8
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        CALL      L:RTC_EnterInitMode
        CP        A, #0x0
        JRNE      L:??RTC_DeInit_0
        CLR       S:?b12
        MOV       L:0x5159, #0xff
        JP        L:??RTC_DeInit_1
??RTC_DeInit_0:
        CLR       L:0x5140
        CLR       L:0x5141
        CLR       L:0x5142
        MOV       L:0x5144, #0x1
        MOV       L:0x5145, #0x21
        CLR       L:0x5146
        CLR       L:0x5150
        MOV       L:0x5151, #0xff
        MOV       L:0x5152, #0x7f
        CLR       L:0x516c
        CLR       L:0x516d
        CLR       L:0x5148
        CLR       L:0x5149
        CLR       L:0x514a
??RTC_DeInit_2:
        BTJT      L:0x514c, #0x2, L:??RTC_DeInit_3
        LDW       X, S:?w5
        CPW       X, #0xffff
        JREQ      L:??RTC_DeInit_3
        LDW       X, S:?w5
        INCW      X
        LDW       S:?w5, X
        CLR       L:0x514c
        JRA       L:??RTC_DeInit_2
??RTC_DeInit_3:
        BTJT      L:0x514c, #0x2, L:??RTC_DeInit_4
        CLR       S:?b12
        MOV       L:0x5159, #0xff
        JRA       L:??RTC_DeInit_1
??RTC_DeInit_4:
        CLR       L:0x5148
        MOV       L:0x5154, #0xff
        MOV       L:0x5155, #0xff
        CLR       L:0x515c
        CLR       L:0x515d
        CLR       L:0x515e
        CLR       L:0x515f
        CLR       L:0x5164
        CLR       L:0x5165
        CLR       L:0x5166
        CLR       L:0x514c
        CLR       L:0x514d
        BTJF      L:0x514c, #0x1, L:??RTC_DeInit_5
??RTC_DeInit_6:
        BTJF      L:0x514c, #0x1, L:??RTC_DeInit_5
        LDW       X, S:?w4
        CPW       X, #0xffff
        JREQ      L:??RTC_DeInit_5
        LDW       X, S:?w4
        INCW      X
        LDW       S:?w4, X
        JRA       L:??RTC_DeInit_6
??RTC_DeInit_5:
        BTJT      L:0x514c, #0x1, L:??RTC_DeInit_7
        CLR       L:0x516a
        CLR       L:0x516b
        CALL      L:RTC_WaitForSynchro
        CP        A, #0x0
        JRNE      L:??RTC_DeInit_8
        CLR       S:?b12
        JRA       L:??RTC_DeInit_9
??RTC_DeInit_8:
        LD        A, #0x1
        LD        S:?b12, A
        JRA       L:??RTC_DeInit_9
??RTC_DeInit_7:
        CLR       S:?b12
??RTC_DeInit_9:
        MOV       L:0x5159, #0xff
??RTC_DeInit_1:
        LD        A, S:?b12
        POP       S:?b12
        JP        L:?epilogue_l2

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_Init:
        CALL      L:?push_w4
        PUSH      S:?b10
        LDW       S:?w4, X
        CLR       S:?b10
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        CALL      L:RTC_EnterInitMode
        CP        A, #0x0
        JRNE      L:??RTC_Init_0
        CLR       S:?b10
        JRA       L:??RTC_Init_1
??RTC_Init_0:
        BRES      L:0x5148, #0x6
        LD        A, [S:?w4.w]
        OR        A, L:0x5148
        LD        L:0x5148, A
        LDW       X, S:?w4
        INCW      X
        INCW      X
        LDW       X, (X)
        LD        A, XH
        LD        L:0x5150, A
        LDW       X, S:?w4
        INCW      X
        INCW      X
        LDW       X, (X)
        LD        A, XL
        LD        L:0x5151, A
        LDW       X, S:?w4
        INCW      X
        LD        A, (X)
        LD        L:0x5152, A
        BRES      L:0x514c, #0x7
        LD        A, #0x1
        LD        S:?b10, A
??RTC_Init_1:
        MOV       L:0x5159, #0xff
        LD        A, S:?b10
        POP       S:?b10
        JP        L:?epilogue_w4

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_StructInit:
        LDW       S:?w0, X
        CLR       [S:?w0.w]
        LDW       X, S:?w0
        INCW      X
        LD        A, #0x7f
        LD        (X), A
        LDW       Y, S:?w0
        INCW      Y
        INCW      Y
        LDW       X, #0xff
        LDW       (Y), X
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_WriteProtectionCmd:
        TNZ       A
        JREQ      L:??RTC_WriteProtectionCmd_0
        MOV       L:0x5159, #0xff
        JRA       L:??RTC_WriteProtectionCmd_1
??RTC_WriteProtectionCmd_0:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
??RTC_WriteProtectionCmd_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_EnterInitMode:
        CLR       S:?b0
        CLRW      X
        BTJT      L:0x514c, #0x6, L:??RTC_EnterInitMode_0
        MOV       L:0x514c, #0x80
??RTC_EnterInitMode_1:
        BTJT      L:0x514c, #0x6, L:??RTC_EnterInitMode_0
        CPW       X, #0xffff
        JREQ      L:??RTC_EnterInitMode_0
        INCW      X
        JRA       L:??RTC_EnterInitMode_1
??RTC_EnterInitMode_0:
        BTJT      L:0x514c, #0x6, L:??RTC_EnterInitMode_2
        CLR       S:?b0
        JRA       L:??RTC_EnterInitMode_3
??RTC_EnterInitMode_2:
        LD        A, #0x1
        LD        S:?b0, A
??RTC_EnterInitMode_3:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_ExitInitMode:
        BRES      L:0x514c, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_WaitForSynchro:
        CLRW      X
        CLR       S:?b0
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, L:0x514c
        AND       A, #0x5f
        LD        L:0x514c, A
??RTC_WaitForSynchro_0:
        BTJT      L:0x514c, #0x5, L:??RTC_WaitForSynchro_1
        CPW       X, #0xffff
        JREQ      L:??RTC_WaitForSynchro_1
        INCW      X
        JRA       L:??RTC_WaitForSynchro_0
??RTC_WaitForSynchro_1:
        BTJF      L:0x514c, #0x5, L:??RTC_WaitForSynchro_2
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??RTC_WaitForSynchro_3
??RTC_WaitForSynchro_2:
        CLR       S:?b0
??RTC_WaitForSynchro_3:
        MOV       L:0x5159, #0xff
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_RatioCmd:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       A
        JREQ      L:??RTC_RatioCmd_0
        BSET      L:0x5148, #0x5
        JRA       L:??RTC_RatioCmd_1
??RTC_RatioCmd_0:
        BRES      L:0x5148, #0x5
??RTC_RatioCmd_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_BypassShadowCmd:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       A
        JREQ      L:??RTC_BypassShadowCmd_0
        BSET      L:0x5148, #0x4
        JRA       L:??RTC_BypassShadowCmd_1
??RTC_BypassShadowCmd_0:
        BRES      L:0x5148, #0x4
??RTC_BypassShadowCmd_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SetTime:
        LD        S:?b3, A
        LDW       Y, X
        CLR       S:?b2
        CLR       S:?b4
        TNZ       S:?b3
        JRNE      L:??RTC_SetTime_0
        BTJF      L:0x5148, #0x6, L:??RTC_SetTime_1
        JRA       L:??RTC_SetTime_2
??RTC_SetTime_1:
??RTC_SetTime_2:
        JRA       L:??RTC_SetTime_3
??RTC_SetTime_0:
        BTJF      L:0x5148, #0x6, L:??RTC_SetTime_4
        JRA       L:??RTC_SetTime_5
??RTC_SetTime_4:
??RTC_SetTime_5:
??RTC_SetTime_3:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        CALL      L:RTC_EnterInitMode
        CP        A, #0x0
        JRNE      L:??RTC_SetTime_6
        CLR       S:?b2
        MOV       L:0x5159, #0xff
        JRA       L:??RTC_SetTime_7
??RTC_SetTime_6:
        BTJF      L:0x5148, #0x6, L:??RTC_SetTime_8
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        LD        S:?b4, A
        JRA       L:??RTC_SetTime_9
??RTC_SetTime_8:
        CLR       S:?b4
??RTC_SetTime_9:
        TNZ       S:?b3
        JREQ      L:??RTC_SetTime_10
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        LD        L:0x5140, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        LD        L:0x5141, A
        LD        A, (Y)
        OR        A, S:?b4
        LD        L:0x5142, A
        JRA       L:??RTC_SetTime_11
??RTC_SetTime_10:
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        L:0x5140, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        L:0x5141, A
        LD        A, (Y)
        CALL      L:ByteToBcd2
        OR        A, S:?b4
        LD        L:0x5142, A
??RTC_SetTime_11:
        LD        A, L:0x5146
        BRES      L:0x514c, #0x7
        MOV       L:0x5159, #0xff
        BTJT      L:0x5148, #0x4, L:??RTC_SetTime_12
        CALL      L:RTC_WaitForSynchro
        CP        A, #0x0
        JRNE      L:??RTC_SetTime_13
        CLR       S:?b2
        JRA       L:??RTC_SetTime_7
??RTC_SetTime_13:
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??RTC_SetTime_7
??RTC_SetTime_12:
        LD        A, #0x1
        LD        S:?b2, A
??RTC_SetTime_7:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TimeStructInit:
        LDW       Y, X
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        CLR       (Y)
        LDW       X, Y
        INCW      X
        CLR       (X)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetTime:
        LD        S:?b2, A
        LDW       Y, X
        CLR       S:?b3
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, L:0x5140
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, L:0x5141
        LD        (X), A
        LD        A, L:0x5142
        LD        S:?b3, A
        MOV       S:?b0, L:0x5146
        LD        A, S:?b3
        AND       A, #0xbf
        LD        (Y), A
        LD        A, S:?b3
        AND       A, #0x40
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        TNZ       S:?b2
        JRNE      L:??RTC_GetTime_0
        LD        A, (Y)
        CALL      L:Bcd2ToByte
        LD        (Y), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
??RTC_GetTime_0:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetSubSecond:
        CLR       S:?b0
        CLR       S:?b1
        CLRW      Y
        LD        A, L:0x5157
        LD        S:?b0, A
        LD        A, L:0x5158
        LD        S:?b1, A
        MOV       S:?b4, L:0x5146
        CLRW      X
        LD        A, S:?b0
        LD        XL, A
        CLR       A
        RLWA      X, A
        CLR       S:?b2
        MOV       S:?b3, S:?b1
        RRWA      X, A
        OR        A, S:?b3
        RRWA      X, A
        OR        A, S:?b2
        RRWA      X, A
        LDW       Y, X
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SetDate:
        LD        S:?b2, A
        LDW       Y, X
        CLR       S:?b3
        TNZ       S:?b2
        JRNE      L:??RTC_SetDate_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0x10
        CP        A, #0x0
        JREQ      L:??RTC_SetDate_0
        LDW       X, Y
        INCW      X
        LD        A, (X)
        AND       A, #0xef
        ADD       A, #0xa
        LDW       X, Y
        INCW      X
        LD        (X), A
??RTC_SetDate_0:
        TNZ       S:?b2
        JRNE      L:??RTC_SetDate_1
        JRA       L:??RTC_SetDate_2
??RTC_SetDate_1:
??RTC_SetDate_2:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        CALL      L:RTC_EnterInitMode
        CP        A, #0x0
        JRNE      L:??RTC_SetDate_3
        CLR       S:?b3
        MOV       L:0x5159, #0xff
        JRA       L:??RTC_SetDate_4
??RTC_SetDate_3:
        LD        A, L:0x5140
        TNZ       S:?b2
        JREQ      L:??RTC_SetDate_5
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        LD        L:0x5144, A
        LD        A, (Y)
        CALL      L:?sll8_a_a_5
        LDW       X, Y
        INCW      X
        OR        A, (X)
        LD        L:0x5145, A
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        LD        L:0x5146, A
        JRA       L:??RTC_SetDate_6
??RTC_SetDate_5:
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        L:0x5144, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        S:?b0, A
        LD        A, (Y)
        CALL      L:?sll8_a_a_5
        OR        A, S:?b0
        LD        L:0x5145, A
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        L:0x5146, A
??RTC_SetDate_6:
        BRES      L:0x514c, #0x7
        MOV       L:0x5159, #0xff
        BTJT      L:0x5148, #0x4, L:??RTC_SetDate_7
        CALL      L:RTC_WaitForSynchro
        CP        A, #0x0
        JRNE      L:??RTC_SetDate_8
        CLR       S:?b3
        JRA       L:??RTC_SetDate_4
??RTC_SetDate_8:
        LD        A, #0x1
        LD        S:?b3, A
        JRA       L:??RTC_SetDate_4
??RTC_SetDate_7:
        LD        A, #0x1
        LD        S:?b3, A
??RTC_SetDate_4:
        LD        A, S:?b3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_DateStructInit:
        LDW       Y, X
        LD        A, #0x1
        LD        (Y), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, #0x1
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, #0x1
        LD        (X), A
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetDate:
        LD        S:?b2, A
        LDW       Y, X
        CLR       S:?b3
        MOV       S:?b0, L:0x5140
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, L:0x5144
        LD        (X), A
        LD        A, L:0x5145
        LD        S:?b3, A
        LD        A, L:0x5146
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        LD        A, S:?b3
        AND       A, #0x1f
        LDW       X, Y
        INCW      X
        LD        (X), A
        LD        A, S:?b3
        CALL      L:?srl8_a_a_5
        LD        (Y), A
        TNZ       S:?b2
        JRNE      L:??RTC_GetDate_0
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
??RTC_GetDate_0:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SetAlarm:
        LD        S:?b5, A
        LDW       Y, X
        CLR       S:?b2
        CLR       S:?b3
        CLR       S:?b4
        CLR       S:?b6
        TNZ       S:?b5
        JRNE      L:??RTC_SetAlarm_0
        BTJF      L:0x5148, #0x6, L:??RTC_SetAlarm_1
        JRA       L:??RTC_SetAlarm_2
??RTC_SetAlarm_1:
??RTC_SetAlarm_2:
        JRA       L:??RTC_SetAlarm_3
??RTC_SetAlarm_0:
        BTJF      L:0x5148, #0x6, L:??RTC_SetAlarm_4
        JRA       L:??RTC_SetAlarm_5
??RTC_SetAlarm_4:
??RTC_SetAlarm_5:
??RTC_SetAlarm_3:
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, #0x10
        CP        A, #0x0
        JRNE      L:??RTC_SetAlarm_6
        LDW       X, Y
        ADDW      X, #0x5
        LD        A, (X)
        CP        A, #0x40
        JRNE      L:??RTC_SetAlarm_7
        JRA       L:??RTC_SetAlarm_6
??RTC_SetAlarm_7:
??RTC_SetAlarm_6:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b5
        JREQ      L:??RTC_SetAlarm_8
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, #0x80
        LDW       X, Y
        INCW      X
        INCW      X
        OR        A, (X)
        LD        S:?b2, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        AND       A, #0x80
        LDW       X, Y
        INCW      X
        OR        A, (X)
        LD        S:?b3, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        SLL       A
        AND       A, #0x80
        PUSH      A
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        OR        A, (Y)
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        S:?b4, A
        LDW       X, Y
        ADDW      X, #0x5
        LD        A, (X)
        LDW       X, Y
        ADDW      X, #0x6
        OR        A, (X)
        LD        S:?b0, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        SLL       A
        SLL       A
        AND       A, #0x80
        OR        A, S:?b0
        LD        S:?b6, A
        JRA       L:??RTC_SetAlarm_9
??RTC_SetAlarm_8:
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        S:?b0, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        AND       A, #0x80
        OR        A, S:?b0
        LD        S:?b2, A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        S:?b0, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        AND       A, #0x80
        OR        A, S:?b0
        LD        S:?b3, A
        LD        A, (Y)
        CALL      L:ByteToBcd2
        LD        S:?b1, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        SLL       A
        AND       A, #0x80
        PUSH      A
        LDW       X, Y
        ADDW      X, #0x3
        LD        A, (X)
        OR        A, S:?b1
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        S:?b4, A
        LDW       X, Y
        ADDW      X, #0x6
        LD        A, (X)
        CALL      L:ByteToBcd2
        LD        S:?b1, A
        LDW       X, Y
        ADDW      X, #0x4
        LD        A, (X)
        SLL       A
        SLL       A
        SLL       A
        AND       A, #0x80
        PUSH      A
        LDW       X, Y
        ADDW      X, #0x5
        LD        A, (X)
        OR        A, S:?b1
        LD        S:?b1, A
        POP       A
        OR        A, S:?b1
        LD        S:?b6, A
??RTC_SetAlarm_9:
        LD        A, S:?b2
        LD        L:0x515c, A
        LD        A, S:?b3
        LD        L:0x515d, A
        LD        A, S:?b4
        LD        L:0x515e, A
        LD        A, S:?b6
        LD        L:0x515f, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_AlarmStructInit:
        LDW       Y, X
        LDW       X, Y
        ADDW      X, #0x3
        CLR       (X)
        CLR       (Y)
        LDW       X, Y
        INCW      X
        CLR       (X)
        LDW       X, Y
        INCW      X
        INCW      X
        CLR       (X)
        LDW       X, Y
        ADDW      X, #0x5
        CLR       (X)
        LD        A, #0x1
        LDW       X, Y
        ADDW      X, #0x6
        LD        (X), A
        LD        A, #0xf0
        LDW       X, Y
        ADDW      X, #0x4
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetAlarm:
        LD        S:?b2, A
        LDW       Y, X
        CLR       S:?b3
        CLR       S:?b4
        CLR       S:?b5
        CLR       S:?b6
        CLR       S:?b7
        LD        A, L:0x515c
        LD        S:?b3, A
        LD        A, L:0x515d
        LD        S:?b4, A
        LD        A, L:0x515e
        LD        S:?b5, A
        LD        A, L:0x515f
        LD        S:?b6, A
        LD        A, S:?b3
        AND       A, #0x7f
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        LD        A, S:?b3
        AND       A, #0x80
        LD        S:?b7, A
        LD        A, S:?b4
        AND       A, #0x7f
        LDW       X, Y
        INCW      X
        LD        (X), A
        LD        A, S:?b4
        AND       A, #0x80
        SRL       A
        OR        A, S:?b7
        LD        S:?b7, A
        LD        A, S:?b5
        AND       A, #0x3f
        LD        (Y), A
        LD        A, S:?b5
        AND       A, #0x40
        LDW       X, Y
        ADDW      X, #0x3
        LD        (X), A
        LD        A, S:?b5
        AND       A, #0x80
        SRL       A
        SRL       A
        OR        A, S:?b7
        LD        S:?b7, A
        LD        A, S:?b6
        AND       A, #0x3f
        LDW       X, Y
        ADDW      X, #0x6
        LD        (X), A
        LD        A, S:?b6
        AND       A, #0x40
        LDW       X, Y
        ADDW      X, #0x5
        LD        (X), A
        LD        A, S:?b6
        AND       A, #0x80
        SRL       A
        SRL       A
        SRL       A
        OR        A, S:?b7
        LD        S:?b7, A
        LD        A, S:?b7
        LDW       X, Y
        ADDW      X, #0x4
        LD        (X), A
        TNZ       S:?b2
        JRNE      L:??RTC_GetAlarm_0
        LD        A, (Y)
        CALL      L:Bcd2ToByte
        LD        (Y), A
        LDW       X, Y
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        LD        (X), A
        LDW       X, Y
        INCW      X
        INCW      X
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        INCW      X
        INCW      X
        LD        (X), A
        LDW       X, Y
        ADDW      X, #0x6
        LD        A, (X)
        CALL      L:Bcd2ToByte
        LDW       X, Y
        ADDW      X, #0x6
        LD        (X), A
??RTC_GetAlarm_0:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_AlarmCmd:
        SUB       SP, #0x2
        LD        S:?b2, A
        CLRW      X
        LDW       (0x1,SP), X
        CLR       S:?b1
        CLR       S:?b0
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b2
        JREQ      L:??RTC_AlarmCmd_0
        BSET      L:0x5149, #0x0
        LD        A, #0x1
        LD        S:?b1, A
        JRA       L:??RTC_AlarmCmd_1
??RTC_AlarmCmd_0:
        BRES      L:0x5149, #0x0
        LD        A, L:0x514c
        AND       A, #0x1
        LD        S:?b0, A
??RTC_AlarmCmd_2:
        LDW       X, (0x1,SP)
        CPW       X, #0xffff
        JREQ      L:??RTC_AlarmCmd_3
        TNZ       S:?b0
        JRNE      L:??RTC_AlarmCmd_3
        LDW       X, (0x1,SP)
        INCW      X
        LDW       (0x1,SP), X
        JRA       L:??RTC_AlarmCmd_2
??RTC_AlarmCmd_3:
        BTJT      L:0x514c, #0x0, L:??RTC_AlarmCmd_4
        CLR       S:?b1
        JRA       L:??RTC_AlarmCmd_1
??RTC_AlarmCmd_4:
        LD        A, #0x1
        LD        S:?b1, A
??RTC_AlarmCmd_1:
        MOV       L:0x5159, #0xff
        LD        A, S:?b1
        ADD       SP, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_AlarmSubSecondConfig:
        LD        S:?b1, A
        CLR       S:?b2
        CLR       S:?b0
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        BTJT      L:0x514c, #0x6, L:??RTC_AlarmSubSecondConfig_0
        LD        A, L:0x5149
        OR        A, #0x1
        LD        S:?b2, A
        BRES      L:0x5149, #0x0
        LD        A, XH
        LD        L:0x5164, A
        LD        A, XL
        LD        L:0x5165, A
        LD        A, S:?b1
        LD        L:0x5166, A
        LD        A, L:0x5149
        OR        A, S:?b2
        LD        L:0x5149, A
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??RTC_AlarmSubSecondConfig_1
??RTC_AlarmSubSecondConfig_0:
        CLR       S:?b0
??RTC_AlarmSubSecondConfig_1:
        MOV       L:0x5159, #0xff
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_WakeUpClockConfig:
        LD        S:?b0, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        BRES      L:0x5149, #0x2
        LD        A, L:0x5148
        AND       A, #0xf8
        LD        L:0x5148, A
        LD        A, L:0x5148
        OR        A, S:?b0
        LD        L:0x5148, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SetWakeUpCounter:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, XH
        LD        L:0x5154, A
        LD        A, XL
        LD        L:0x5155, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetWakeUpCounter:
        CLRW      Y
        LD        A, L:0x5154
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       Y, X
        LD        A, L:0x5155
        CLR       S:?b0
        LD        S:?b1, A
        RRWA      Y, A
        OR        A, S:?b1
        RRWA      Y, A
        OR        A, S:?b0
        RRWA      Y, A
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_WakeUpCmd:
        LD        S:?b1, A
        CLR       S:?b0
        CLRW      X
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b1
        JREQ      L:??RTC_WakeUpCmd_0
        BSET      L:0x5149, #0x2
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??RTC_WakeUpCmd_1
??RTC_WakeUpCmd_0:
        BRES      L:0x5149, #0x2
??RTC_WakeUpCmd_2:
        BTJT      L:0x514c, #0x2, L:??RTC_WakeUpCmd_3
        CPW       X, #0xffff
        JREQ      L:??RTC_WakeUpCmd_3
        INCW      X
        JRA       L:??RTC_WakeUpCmd_2
??RTC_WakeUpCmd_3:
        BTJT      L:0x514c, #0x2, L:??RTC_WakeUpCmd_4
        CLR       S:?b0
        JRA       L:??RTC_WakeUpCmd_1
??RTC_WakeUpCmd_4:
        LD        A, #0x1
        LD        S:?b0, A
??RTC_WakeUpCmd_1:
        MOV       L:0x5159, #0xff
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_DayLightSavingConfig:
        LD        S:?b1, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        BRES      L:0x514a, #0x2
        LD        A, S:?b0
        OR        A, S:?b1
        OR        A, L:0x514a
        LD        L:0x514a, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetStoreOperation:
        LD        A, L:0x514a
        AND       A, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_OutputConfig:
        LD        S:?b1, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, L:0x514a
        AND       A, #0x8f
        LD        L:0x514a, A
        LD        A, S:?b0
        OR        A, S:?b1
        OR        A, L:0x514a
        LD        L:0x514a, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SynchroShiftConfig:
        LD        S:?b2, A
        LDW       Y, X
        CLR       S:?b0
        CLR       S:?b1
        CLRW      X
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        BTJF      L:0x514c, #0x3, L:??RTC_SynchroShiftConfig_0
??RTC_SynchroShiftConfig_1:
        BTJF      L:0x514c, #0x3, L:??RTC_SynchroShiftConfig_0
        CPW       X, #0xffff
        JREQ      L:??RTC_SynchroShiftConfig_0
        INCW      X
        JRA       L:??RTC_SynchroShiftConfig_1
??RTC_SynchroShiftConfig_0:
        BTJT      L:0x514c, #0x3, L:??RTC_SynchroShiftConfig_2
        LD        A, YH
        OR        A, S:?b2
        LD        S:?b0, A
        LD        A, S:?b0
        LD        L:0x515a, A
        LD        A, YL
        LD        L:0x515b, A
        LD        A, #0x1
        LD        S:?b1, A
        JRA       L:??RTC_SynchroShiftConfig_3
??RTC_SynchroShiftConfig_2:
        CLR       S:?b1
??RTC_SynchroShiftConfig_3:
        MOV       L:0x5159, #0xff
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_SmoothCalibConfig:
        LD        S:?b3, A
        MOV       S:?b2, S:?b0
        LDW       Y, X
        CLR       S:?b1
        CLRW      X
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        BTJF      L:0x514c, #0x1, L:??RTC_SmoothCalibConfig_0
??RTC_SmoothCalibConfig_1:
        BTJF      L:0x514c, #0x1, L:??RTC_SmoothCalibConfig_0
        CPW       X, #0xffff
        JREQ      L:??RTC_SmoothCalibConfig_0
        INCW      X
        JRA       L:??RTC_SmoothCalibConfig_1
??RTC_SmoothCalibConfig_0:
        BTJT      L:0x514c, #0x1, L:??RTC_SmoothCalibConfig_2
        RLWA      Y, A
        LD        S:?b0, A
        RRWA      Y, A
        LD        A, S:?b2
        OR        A, S:?b3
        OR        A, S:?b0
        LD        L:0x516a, A
        LD        A, YL
        LD        L:0x516b, A
        LD        A, #0x1
        LD        S:?b1, A
        JRA       L:??RTC_SmoothCalibConfig_3
??RTC_SmoothCalibConfig_2:
        CLR       S:?b1
??RTC_SmoothCalibConfig_3:
        MOV       L:0x5159, #0xff
        LD        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_CalibOutputConfig:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       A
        JREQ      L:??RTC_CalibOutputConfig_0
        BSET      L:0x514a, #0x3
        JRA       L:??RTC_CalibOutputConfig_1
??RTC_CalibOutputConfig_0:
        BRES      L:0x514a, #0x3
??RTC_CalibOutputConfig_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_CalibOutputCmd:
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       A
        JREQ      L:??RTC_CalibOutputCmd_0
        BSET      L:0x514a, #0x7
        JRA       L:??RTC_CalibOutputCmd_1
??RTC_CalibOutputCmd_0:
        BRES      L:0x514a, #0x7
??RTC_CalibOutputCmd_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TamperLevelConfig:
        LD        S:?b1, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b0
        JREQ      L:??RTC_TamperLevelConfig_0
        LD        A, S:?b1
        SLL       A
        OR        A, L:0x516c
        LD        L:0x516c, A
        JRA       L:??RTC_TamperLevelConfig_1
??RTC_TamperLevelConfig_0:
        LD        A, S:?b1
        SLL       A
        CPL       A
        AND       A, L:0x516c
        LD        L:0x516c, A
??RTC_TamperLevelConfig_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TamperFilterConfig:
        LD        S:?b0, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, L:0x516d
        AND       A, #0xe7
        LD        L:0x516d, A
        LD        A, L:0x516d
        OR        A, S:?b0
        LD        L:0x516d, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TamperSamplingFreqConfig:
        LD        S:?b0, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, L:0x516d
        AND       A, #0xf8
        LD        L:0x516d, A
        LD        A, L:0x516d
        OR        A, S:?b0
        LD        L:0x516d, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TamperPinsPrechargeDuration:
        LD        S:?b0, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        LD        A, L:0x516d
        AND       A, #0x1f
        LD        L:0x516d, A
        LD        A, L:0x516d
        OR        A, S:?b0
        LD        L:0x516d, A
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_TamperCmd:
        LD        S:?b1, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b0
        JREQ      L:??RTC_TamperCmd_0
        LD        A, L:0x516c
        OR        A, S:?b1
        LD        L:0x516c, A
        JRA       L:??RTC_TamperCmd_1
??RTC_TamperCmd_0:
        LD        A, S:?b1
        CPL       A
        AND       A, L:0x516c
        LD        L:0x516c, A
??RTC_TamperCmd_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_ITConfig:
        LD        S:?b0, A
        MOV       L:0x5159, #0xca
        MOV       L:0x5159, #0x53
        TNZ       S:?b0
        JREQ      L:??RTC_ITConfig_0
        LD        A, XL
        AND       A, #0xf0
        OR        A, L:0x5149
        LD        L:0x5149, A
        LD        A, XL
        AND       A, #0x1
        OR        A, L:0x516c
        LD        L:0x516c, A
        JRA       L:??RTC_ITConfig_1
??RTC_ITConfig_0:
        LD        A, XL
        AND       A, #0xf0
        CPL       A
        AND       A, L:0x5149
        LD        L:0x5149, A
        LD        A, XL
        AND       A, #0x1
        CPL       A
        AND       A, L:0x516c
        LD        L:0x516c, A
??RTC_ITConfig_1:
        MOV       L:0x5159, #0xff
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetFlagStatus:
        LDW       S:?w2, X
        CLR       S:?b0
        CLRW      Y
        CLR       S:?b3
        CLR       S:?b2
        LD        A, L:0x514c
        CLRW      X
        LD        XL, A
        CLR       A
        RLWA      X, A
        LDW       S:?w1, X
        LD        A, L:0x514d
        CLRW      X
        LD        XL, A
        RRWA      X, A
        OR        A, S:?b3
        RRWA      X, A
        OR        A, S:?b2
        RRWA      X, A
        LDW       Y, X
        LDW       X, Y
        RRWA      X, A
        AND       A, S:?b5
        RRWA      X, A
        AND       A, S:?b4
        RRWA      X, A
        TNZW      X
        JREQ      L:??RTC_GetFlagStatus_0
        LD        A, #0x1
        LD        S:?b0, A
        JRA       L:??RTC_GetFlagStatus_1
??RTC_GetFlagStatus_0:
        CLR       S:?b0
??RTC_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_ClearFlag:
        LD        A, XL
        CPL       A
        LD        L:0x514d, A
        LD        A, XH
        CPL       A
        AND       A, #0x7f
        LD        L:0x514c, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_GetITStatus:
        LDW       Y, X
        CLR       S:?b2
        CLR       S:?b1
        CLR       S:?b0
        LD        A, YL
        AND       A, L:0x5149
        LD        S:?b1, A
        LDW       X, Y
        CALL      L:?srl16_x_x_4
        LD        A, XL
        AND       A, L:0x514d
        LD        S:?b0, A
        TNZ       S:?b1
        JREQ      L:??RTC_GetITStatus_0
        TNZ       S:?b0
        JREQ      L:??RTC_GetITStatus_0
        LD        A, #0x1
        LD        S:?b2, A
        JRA       L:??RTC_GetITStatus_1
??RTC_GetITStatus_0:
        CLR       S:?b2
??RTC_GetITStatus_1:
        LD        A, S:?b2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
RTC_ClearITPendingBit:
        LDW       Y, X
        LDW       X, Y
        CALL      L:?srl16_x_x_4
        LD        A, XL
        CPL       A
        LD        L:0x514d, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
ByteToBcd2:
        LD        S:?b1, A
        CLR       S:?b0
??ByteToBcd2_0:
        LD        A, S:?b1
        CP        A, #0xa
        JRC       L:??ByteToBcd2_1
        INC       S:?b0
        LD        A, S:?b1
        ADD       A, #0xf6
        LD        S:?b1, A
        JRA       L:??ByteToBcd2_0
??ByteToBcd2_1:
        LD        A, S:?b0
        SWAP      A
        AND       A, #0xf0
        OR        A, S:?b1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
Bcd2ToByte:
        LD        S:?b0, A
        CLR       S:?b1
        LD        A, S:?b0
        SWAP      A
        AND       A, #0xf
        LDW       X, #0xa
        MUL       X, A
        LD        A, XL
        LD        S:?b1, A
        LD        A, S:?b0
        AND       A, #0xf
        ADD       A, S:?b1
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 2 553 bytes in section .near_func.text
// 
// 2 553 bytes of CODE memory
//
//Errors: none
//Warnings: none
