////////////////////////////////////////////////////////////////////////////////
// LMT70's temperature with seekfree's/exin's codes designed for RT1064/MSP432//
// Lastest : 2020.9.24                                                        //
//                                                                            //
//*VCC -- 3.3V                                                                //
////////////////////////////////////////////////////////////////////////////////
#ifndef __LMT70RD_H__
#define __LMT70RD_H__

#ifndef MSP432_ENABLE
#define MSP432_ENABLE   1
#endif

#if !MSP432_ENABLE
#include "common.h"
#include "fsl_adc.h"
#include "zf_adc.h"

#else
#include "headfile.h"
#include "exinADC.h"
#endif

/*
 *0：30-50°  一阶传递函数分段计算
 *1：-10~110°二阶传递函数拟合计算
 *2：-10~110°三阶传递函数拟合计算
*/
#define LMT_TRANSMOD	0	//0,1,2 :three methods for selection

#if !MSP432_ENABLE
#define LMT_M		ADC_1
#define LMT_CH		ADC1_CH7_B18

#else
#define LMT_CH      ADC_CH0

#endif

typedef enum
{
	ERROR,	
	STATE_20,
	STATE_30,
	STATE_40,
	STATE_50,
	
}LMT_SELECT;


//初始化
void LMT_Init(void);
//获取毫伏值
float LMT_ADC_GetMV(void);
//数据处理及输出
float LMT_DataHandle(void);



#if	LMT_TRANSMOD == 0
#define	LMT_MOD0	1
#define LMT_MOD1	0
#define LMT_MOD2	0

#elif	LMT_TRANSMOD == 1
#define	LMT_MOD0	0
#define LMT_MOD1	1
#define LMT_MOD2	0

#elif	LMT_TRANSMOD == 2
#define	LMT_MOD0	0
#define LMT_MOD1	0
#define LMT_MOD2	1

#endif

#if     LMT_MOD0
#define LMT_COE_M	0
#define LMT_COE_B	1

uint8 LMT_DataSelect(float LMT_GETMV);

#elif   LMT_MOD1
#define LMT_COE_A	-7.857923E-06
#define LMT_COE_B	-1.777501E-01
#define LMT_COE_C	2.046398E+02

#elif   LMT_MOD2
#define	LMT_COE_A	-1.809628E-09
#define LMT_COE_B	-3.325395E-06
#define LMT_COE_C	-1.814103E-01
#define LMT_COE_D	2.055894E+02	

#endif

#endif
