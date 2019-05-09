#ifndef __HAL_TEST_BENCH_H
#define   __HAL_TEST_BENCH_H

#include "sys.h"

typedef __packed struct
{
	u16				StartCode;
	
	u16				RF4438ID;
	u8				CheckNum;
}TESTBenchDataBuf;

typedef struct
{
	u8				TestState;										// [0] --> All, [1] -->RF4438, 
	u8				SendTimes;
	TESTBenchDataBuf	Data;
}TESTBenchClientTypeDef;

extern TESTBenchClientTypeDef TestBenchClient;

bool TestBench_FLASH_CheckSubSN(void);
void TestBench_FLASH_WriteSubSN(void);

void TestBench_StateCtrl_ALL_ENBALE(void);
void TestBench_StateCtrl_ALL_DISABLE(void);
bool TestBench_StateCtrl_ALL_STATE(void);











#endif /* __HAL_TEST_BENCH_H */
