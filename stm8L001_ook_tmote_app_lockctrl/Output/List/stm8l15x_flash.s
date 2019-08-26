///////////////////////////////////////////////////////////////////////////////
//
// IAR C/C++ Compiler V3.11.1.207 for STM8                26/Aug/2019  11:12:56
// Copyright 2010-2019 IAR Systems AB.
// PC-locked license - IAR Embedded Workbench for STMicroelectronics STM8
//
//    Source file  =  
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_flash.c
//    Command line =  
//        -f C:\Users\kyjapple\AppData\Local\Temp\EW65CA.tmp
//        (F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Libraries\src\stm8l15x_flash.c
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
//        F:\Movebroad\stm32L151_nbiot\workspace\stm32L151_nbiot_tmote_app_workspace\stm8L001_ook_tmote_app_lockctrl\Output\List\stm8l15x_flash.s
//
///////////////////////////////////////////////////////////////////////////////

        EXTERN ?add32_l0_l0_l1
        EXTERN ?b0
        EXTERN ?b1
        EXTERN ?b12
        EXTERN ?b13
        EXTERN ?b2
        EXTERN ?b3
        EXTERN ?epilogue_l2
        EXTERN ?epilogue_l2_l3
        EXTERN ?load32_0x_l2
        EXTERN ?mov_l0_l2
        EXTERN ?mov_l1_l0
        EXTERN ?mov_l1_l2
        EXTERN ?mov_l2_l0
        EXTERN ?mov_w1_w7
        EXTERN ?mul16_x_x_w0
        EXTERN ?mul32_l0_l0_dl
        EXTERN ?push_l1
        EXTERN ?push_l2
        EXTERN ?push_l3
        EXTERN ?w0
        EXTERN ?w1
        EXTERN ?w2
        EXTERN ?w3
        EXTERN ?w4
        EXTERN ?w5
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
        JRA       L:??FLASH_PowerWaitModeConfig_1
??FLASH_PowerWaitModeConfig_0:
        BRES      L:0x5050, #0x2
??FLASH_PowerWaitModeConfig_1:
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
        LDW       Y, X
        LD        S:?b2, A
        BSET      L:0x5051, #0x7
        LD        A, S:?b2
        LD        (Y), A
        LD        A, #0xfd
        CALL      L:FLASH_WaitForLastOperation
        BRES      L:0x5051, #0x7
        RET

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_EraseOptionByte:
        LDW       Y, X
        BSET      L:0x5051, #0x7
        CLR       (Y)
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
        LD        A, #0x1
        LD        S:?b0, A
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
        JRA       L:??FLASH_ITConfig_1
??FLASH_ITConfig_0:
        BRES      L:0x5050, #0x1
??FLASH_ITConfig_1:
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
        LD        A, #0x1
        LD        S:?b0, A
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
        JRA       L:??FLASH_PowerRunModeConfig_1
??FLASH_PowerRunModeConfig_0:
        BRES      L:0x5050, #0x3
??FLASH_PowerRunModeConfig_1:
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
        CALL      L:?push_l2
        CALL      L:?push_l3
        PUSHW     Y
        LDW       S:?w7, X
        LD        S:?b13, A
        MOV       S:?b12, S:?b0
        CLRW      Y
        CLRW      X
        LDW       S:?w5, X
        LDW       S:?w4, X
        LD        A, S:?b13
        CP        A, #0xfd
        JRNE      L:??FLASH_ProgramBlock_0
        LDW       X, #0x8000
        LDW       S:?w1, X
        SLLW      X
        LDW       S:?w0, X
        CALL      L:?mov_l2_l0
        JRA       L:??FLASH_ProgramBlock_1
??FLASH_ProgramBlock_0:
        LDW       X, #0x1000
        LDW       S:?w1, X
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mov_l2_l0
??FLASH_ProgramBlock_1:
        CALL      L:?mov_w1_w7
        CLRW      X
        LDW       S:?w0, X
        CALL      L:?mul32_l0_l0_dl
        DATA
        DC32      0x40
        CODE
        CALL      L:?mov_l1_l0
        CALL      L:?mov_l0_l2
        CALL      L:?add32_l0_l0_l1
        CALL      L:?mov_l2_l0
        TNZ       S:?b12
        JRNE      L:??FLASH_ProgramBlock_2
        BSET      L:0x5051, #0x0
        JRA       L:??FLASH_ProgramBlock_3
??FLASH_ProgramBlock_2:
        BSET      L:0x5051, #0x4
??FLASH_ProgramBlock_3:
        CLRW      X
        LDW       Y, X
??FLASH_ProgramBlock_4:
        CPW       Y, #0x40
        JRNC      L:??FLASH_ProgramBlock_5
        LDW       X, S:?w5
        LDW       S:?w0, Y
        ADDW      X, S:?w0
        LDW       S:?w0, X
        LDW       X, Y
        ADDW      X, (0x1,SP)
        LD        A, (X)
        LD        [S:?w0.w], A
        INCW      Y
        JRA       L:??FLASH_ProgramBlock_4
??FLASH_ProgramBlock_5:
        ADD       SP, #0x2
        JP        L:?epilogue_l2_l3

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_EraseBlock:
        CALL      L:?push_l2
        LDW       Y, X
        CLRW      X
        LDW       S:?w3, X
        LDW       S:?w2, X
        CP        A, #0xfd
        JRNE      L:??FLASH_EraseBlock_0
        LDW       X, #0x8000
        LDW       S:?w5, X
        SLLW      X
        LDW       S:?w4, X
        CALL      L:?mov_l1_l2
        JRA       L:??FLASH_EraseBlock_1
??FLASH_EraseBlock_0:
        LDW       X, #0x1000
        LDW       S:?w5, X
        CLRW      X
        LDW       S:?w4, X
        CALL      L:?mov_l1_l2
??FLASH_EraseBlock_1:
        LDW       X, #0x40
        LDW       S:?w0, X
        LDW       X, Y
        CALL      L:?mul16_x_x_w0
        LDW       S:?w4, X
        LDW       X, S:?w3
        ADDW      X, S:?w4
        LDW       S:?w1, X
        BSET      L:0x5051, #0x5
        CLRW      X
        LDW       S:?w5, X
        LDW       S:?w4, X
        LDW       X, S:?w1
        CALL      L:?load32_0x_l2
        JP        L:?epilogue_l2

        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
FLASH_WaitForLastOperation:
        LD        S:?b1, A
        CLRW      X
        DECW      X
        CLR       S:?b0
        LD        A, S:?b1
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
??FLASH_WaitForLastOperation_0:
        TNZ       S:?b0
        JRNE      L:??FLASH_WaitForLastOperation_2
        TNZW      X
        JREQ      L:??FLASH_WaitForLastOperation_2
        LD        A, L:0x5054
        AND       A, #0x41
        LD        S:?b0, A
        DECW      X
        JRA       L:??FLASH_WaitForLastOperation_0
??FLASH_WaitForLastOperation_2:
        TNZW      X
        JRNE      L:??FLASH_WaitForLastOperation_3
        LD        A, #0x2
        LD        S:?b0, A
??FLASH_WaitForLastOperation_3:
        LD        A, S:?b0
        RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END
// 
// 586 bytes in section .near_func.text
// 
// 586 bytes of CODE memory
//
//Errors: none
//Warnings: none
