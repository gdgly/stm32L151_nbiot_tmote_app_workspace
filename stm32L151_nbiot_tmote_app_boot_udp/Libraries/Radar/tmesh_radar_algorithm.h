/**
  *********************************************************************************************************
  * @file    tmesh_rader_algorithm.h
  * @author  Movebroad -- Bell Zhong
  * @version V0.2.1
  * @date    2017-11-14
  * @brief   
  *********************************************************************************************************
  * @attention
  *	171114:根据3.3V供电mcu进行调整,对应运放(R23,R25) = (10K,100R),旧款雷达模块,VPTAT没有接到VTUNE,对应DAC输出值变化为: 50->(50+304*6)
  *
  *
  *********************************************************************************************************
  */
#ifndef __TMESH_RADER_ALGORITHM_H
#define   __TMESH_RADER_ALGORITHM_H


#include "sys.h"


#define	BE_COVERED	1
#define	NOT_COVERED	0
#define	MAY_COVERED	2



#define	STATUS_COVER_WATER	1
#define	STATUS_COVER_SOLID	2
#define	STATUS_HAS_TARGET	3
#define	STATUS_NO_TARGET	0



#define TRADAR_SAMPLE_NUM		(256+48)//(256+64)	//
#define TRADAR_BACKGROUND_NUM		15

enum TRADAR_DETECT_STATUS
{
	TRADAR_NO_TARGET = 0,
	TRADAR_BE_COVERED,
	TRADAR_HAS_TARGET,
};

enum TRADAR_ERRCODE
{
	TRADAR_OK = 0,
	TRADAR_ERROR,
	TRADAR_NO_BACKGROUND,
};

typedef struct{	
	u32 signal_strength;
	u8 distance_cm;
	u8 status;
	u16 strenth_total_diff;
}tradar_targetinfo_s;

/*
 * ----------------------------------------------------------------------------
 * Function Name: tradar_background_transform
 * Purpose: get the backgroud frequency spectrum
 * Params: 
 *		datain_t: input, the amplitude in time domain
 *		in_num: input, the number of datain_t,it must the same with TRADAR_SAMPLE_NUM
 *		fre_strenth_out: output, the amplitude in frequency domain
 *		out_num: output, the number of fre_strenth_out,it must be the same with TRADAR_BACKGROUND_NUM
 * Returns:TRADAR_ERROR or TRADAR_OK
 * Note:
 * ----------------------------------------------------------------------------
 */
char tradar_background_transform(u32 datain_t[],u16 in_num,u16 fre_strenth_out[],u8 out_num);// __attribute((section(".ARM.__at_0x8010000")));

/*
 * ----------------------------------------------------------------------------
 * Function Name: tradar_background_set
 * Purpose: set the background frequency spectrum
 * Params:
 *		fre_magBG: input, the amplitude in time domain
 *		in_num: input, the number of fre_magBG,it must the same with TRADAR_SAMPLE_NUM
 * Returns:TRADAR_ERROR or TRADAR_OK
 * Note:
 * ----------------------------------------------------------------------------
 */
char tradar_background_set(u16* fre_magBG,u8 in_num);// __attribute((section(".ARM.__at_0x8010030")));


/*
 * ----------------------------------------------------------------------------
 * Function Name: tradar_target_detect
 * Purpose: detect the target info
 * Params:
 *		datain_t: input, the amplitude in time domain
 *		in_num: input, the number of datain_t,it must the same with TRADAR_SAMPLE_NUM
 *		targetinfo: output, the target info
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
char tradar_target_detect(u32 datain_t[],u16 in_mum,tradar_targetinfo_s* targetinfo);// __attribute((section(".ARM.__at_0x8010060")));
	

#endif
