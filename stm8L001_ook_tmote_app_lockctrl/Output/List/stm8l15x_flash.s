///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                22/Aug/2019  15:05:19
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_flash.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EWC6CE.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_flash.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_flash.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?add32_l0_l0_l1
        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?b8
        EXTERN ?load32_0x_l0
        EXTERN ?mov_l0_l3
        EXTERN ?mov_l1_l0
        EXTERN ?mov_l3_l0
        EXTERN ?mul16_x_x_w0
        EXTERN ?mul32_l0_l0_dl
        EXTERN ?pop_l3
        EXTERN ?pop_w5
        EXTERN ?push_l1
        EXTERN ?push_l3
        EXTERN ?push_w5
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w3
        EXTERN ?w5
        EXTERN ?w6
        EXTERN ?w7

        PUBLIC FLASH_DeInit
        PUBLIC FLASH_EraseBlock
        PUBLIC FLASH_EraseByte
        PUBLIC FLASH_EraseOptionByte
        PUBLIC FLASH_GetBootSize
        PUBLIC FLASH_GetCodeSize
        PUBLIC FLASH_GetFlagStatus
        PUBLIC FLASH_GetPowerStatus
        PUBLIC FLASH_GetProgrammingTime
        PUBLIC FLASH_GetReadOutProtectionStatus
        PUBLIC FLASH_ITConfig
        PUBLIC FLASH_Lock
        PUBLIC FLASH_PowerRunModeConfig
        PUBLIC FLASH_PowerWaitModeConfig
        PUBLIC FLASH_ProgramBlock
        PUBLIC FLASH_ProgramByte
        PUBLIC FLASH_ProgramOptionByte
        PUBLIC FLASH_ProgramWord
        PUBLIC FLASH_ReadByte
        PUBLIC FLASH_SetProgrammingTime
        PUBLIC FLASH_Unlock
        PUBLIC FLASH_WaitForLastOperation


        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_SetProgrammingTime:
        LD        S:?b0, A
        BRES      L:0x5050, #0x0
        LD        A, L:0x5050
        OR        A, S:?b0
        LD        L:0x5050, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetProgrammingTime:
        LD        A, L:0x5050
        AND       A, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_PowerWaitModeConfig:
        CP        A, #0x1
        JREQ      L:??FLASH_PowerWaitModeConfig_0
        BSET      L:0x5050, #0x2
        RET
??FLASH_PowerWaitModeConfig_0:
        BRES      L:0x5050, #0x2
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_DeInit:
        CLR       L:0x5050
        CLR       L:0x5051
        MOV       L:0x5054, #0x40
        LD        A, L:0x5054
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_Unlock:
        CP        A, #0xfd
        JRNE      L:??FLASH_Unlock_0
        MOV       L:0x5052, #0x56
        MOV       L:0x5052, #0xae
??FLASH_Unlock_0:
        CP        A, #0xf7
        JRNE      L:??FLASH_Unlock_1
        MOV       L:0x5053, #0xae
        MOV       L:0x5053, #0x56
??FLASH_Unlock_1:
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_Lock:
        LD        S:?b0, A
        LD        A, L:0x5054
        AND       A, S:?b0
        LD        L:0x5054, A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ProgramByte:
        LDW       X, S:?w1
        LD        (X), A
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_EraseByte:
        LDW       X, S:?w1
        CLR       (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ProgramWord:
        CALL      L:?push_l1
        BSET      L:0x5051, #0x6
        LDW       X, S:?w1
        LD        A, (0x1,SP)
        LD        (X), A
        LDW       X, S:?w1
        INCW      X
        LD        A, (0x2,SP)
        LD        (X), A
        LDW       X, S:?w1
        INCW      X
        INCW      X
        LD        A, (0x3,SP)
        LD        (X), A
        LDW       X, S:?w1
        LD        A, (0x4,SP)
        ADDW      X, #0x3
        LD        (X), A
        SUBW      X, #0x3
        ADD       SP, #0x4
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ReadByte:
        LDW       X, S:?w1
        LD        A, (X)
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ProgramOptionByte:
        BSET      L:0x5051, #0x7
        LD        (X), A
        LD        A, #0xfd
        CALL      L:FLASH_WaitForLastOperation
        BRES      L:0x5051, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_EraseOptionByte:
        BSET      L:0x5051, #0x7
        CLR       (X)
        LD        A, #0xfd
        CALL      L:FLASH_WaitForLastOperation
        BRES      L:0x5051, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetReadOutProtectionStatus:
        CLR       S:?b0
        LD        A, L:0x4800
        CP        A, #0xaa
        JRNE      L:??FLASH_GetReadOutProtectionStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??FLASH_GetReadOutProtectionStatus_1
??FLASH_GetReadOutProtectionStatus_0:
        CLR       S:?b0
??FLASH_GetReadOutProtectionStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetBootSize:
        CLRW      Y
        LD        A, L:0x4802
        CLR       S:?b2
        LD        S:?b3, A
        LDW       X, #0x80
        LDW       S:?w0, X
        LDW       X, S:?w1
        CALL      L:?mul16_x_x_w0
        LDW       Y, X
        LD        A, L:0x4802
        CP        A, #0x80
        JRC       L:??FLASH_GetBootSize_0
        LDW       X, #0x2000
        LDW       Y, X
??FLASH_GetBootSize_0:
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetCodeSize:
        CLRW      Y
        LD        A, L:0x4807
        CLR       S:?b2
        LD        S:?b3, A
        LDW       X, #0x80
        LDW       S:?w0, X
        LDW       X, S:?w1
        CALL      L:?mul16_x_x_w0
        LDW       Y, X
        LD        A, L:0x4807
        CP        A, #0x80
        JRC       L:??FLASH_GetCodeSize_0
        LDW       X, #0x2000
        LDW       Y, X
??FLASH_GetCodeSize_0:
        LDW       X, Y
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ITConfig:
        TNZ       A
        JREQ      L:??FLASH_ITConfig_0
        BSET      L:0x5050, #0x1
        RET
??FLASH_ITConfig_0:
        BRES      L:0x5050, #0x1
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetFlagStatus:
        LD        S:?b1, A
        CLR       S:?b0
        LD        A, L:0x5054
        AND       A, S:?b1
        CP        A, #0x0
        JREQ      L:??FLASH_GetFlagStatus_0
        MOV       S:?b0, #0x1
        JRA       L:??FLASH_GetFlagStatus_1
??FLASH_GetFlagStatus_0:
        CLR       S:?b0
??FLASH_GetFlagStatus_1:
        LD        A, S:?b0
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_PowerRunModeConfig:
        CP        A, #0x1
        JREQ      L:??FLASH_PowerRunModeConfig_0
        BSET      L:0x5050, #0x3
        RET
??FLASH_PowerRunModeConfig_0:
        BRES      L:0x5050, #0x3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_GetPowerStatus:
        LD        A, L:0x5050
        AND       A, #0xc
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_ProgramBlock:
        CALL      L:?push_l3
        CALL      L:?push_w5
        PUSH      S:?b8
        LDW       S:?w1, X
        MOV       S:?b8, S:?b0
        LDW       S:?w5, Y
        CLR       S:?b1
        CLR       S:?b0
        CLRW      X
        LDW       S:?w7, X
        LDW       S:?w6, X
        CP        A, #0xfd
        JRNE      L:??FLASH_ProgramBlock_0
        LDW       X, #0x8000
        LDW       S:?w7, X
        SLLW      X
        LDW       S:?w6, X
        JRA       L:??FLASH_ProgramBlock_1
??FLASH_ProgramBlock_0:
        LDW       X, #0x1000
        LDW       S:?w7, X
        CLRW      X
        LDW       S:?w6, X
??FLASH_ProgramBlock_1:
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0x40
        CODE
        CALL      L:?mov_l1_l0
        CALL      L:?mov_l0_l3
        CALL      L:?add32_l0_l0_l1
        CALL      L:?mov_l3_l0
        TNZ       S:?b8
        JRNE      L:??FLASH_ProgramBlock_2
        BSET      L:0x5051, #0x0
        JRA       L:??FLASH_ProgramBlock_3
??FLASH_ProgramBlock_2:
        BSET      L:0x5051, #0x4
??FLASH_ProgramBlock_3:
        CLR       S:?b1
        CLR       S:?b0
        JRA       L:??FLASH_ProgramBlock_4
??FLASH_ProgramBlock_5:
        LDW       X, S:?w7
        ADDW      X, S:?w0
        LDW       Y, X
        LDW       X, S:?w0
        ADDW      X, S:?w5
        LD        A, (X)
        LD        (Y), A
        LDW       X, S:?w0
        INCW      X
        LDW       S:?w0, X
??FLASH_ProgramBlock_4:
        LDW       X, S:?w0
        CPW       X, #0x40
        JRC       L:??FLASH_ProgramBlock_5
        POP       S:?b8
        CALL      L:?pop_w5
        CALL      L:?pop_l3
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_EraseBlock:
        LDW       Y, X
        CLRW      X
        LDW       S:?w3, X
        LDW       S:?w2, X
        CP        A, #0xfd
        JRNE      L:??FLASH_EraseBlock_0
        LDW       X, #0x8000
        LDW       S:?w3, X
        SLLW      X
        LDW       S:?w2, X
        JRA       L:??FLASH_EraseBlock_1
??FLASH_EraseBlock_0:
        LDW       X, #0x1000
        LDW       S:?w3, X
        CLRW      X
        LDW       S:?w2, X
??FLASH_EraseBlock_1:
        LDW       X, #0x40
        LDW       S:?w0, X
        LDW       X, Y
        CALL      L:?mul16_x_x_w0
        LDW       Y, S:?w3
        LDW       S:?w0, X
        ADDW      Y, S:?w0
        BSET      L:0x5051, #0x5
        CLRW      X
        LDW       S:?w1, X
        LDW       S:?w0, X
        LDW       X, Y
        JP        L:?load32_0x_l0

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_WaitForLastOperation:
        CLRW      X
        DECW      X
        CLR       S:?b0
        CP        A, #0xfd
        JRNE      L:??FLASH_WaitForLastOperation_0
??FLASH_WaitForLastOperation_1:
        TNZ       S:?b0
        JRNE      L:??FLASH_WaitForLastOperation_2
        TNZW      X
        JREQ      L:??FLASH_WaitForLastOperation_2
        LD        A, L:0x5054
        AND       A, #0x5
        LD        S:?b0, A
        DECW      X
        JRA       L:??FLASH_WaitForLastOperation_1
??FLASH_WaitForLastOperation_3:
        LD        A, L:0x5054
        AND       A, #0x41
        LD        S:?b0, A
        DECW      X
??FLASH_WaitForLastOperation_0:
        TNZ       S:?b0
        JRNE      L:??FLASH_WaitForLastOperation_2
        TNZW      X
        JRNE      L:??FLASH_WaitForLastOperation_3
??FLASH_WaitForLastOperation_2:
        TNZW      X
        JRNE      L:??FLASH_WaitForLastOperation_4
        MOV       S:?b0, #0x2
??FLASH_WaitForLastOperation_4:
        LD        A, S:?b0
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 554 bytes in section .near_func.text
// 
// 554 bytes of CODE memory
//
//Errors: none
//Warnings: none
