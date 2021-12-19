////////////////////////////////////////////////////////////////////////////////
// LMT70's temperature with seekfree's/exin's codes designed for RT1064/MSP432//
// Lastest : 2020.9.24                                                        //
////////////////////////////////////////////////////////////////////////////////
#include "LMT70RD.h"

#if LMT_MOD0
float COE[2] = {0};
uint8 LMT_DataSelect(float LMT_GETMV)
{
	if(LMT_GETMV >= 942.547 && LMT_GETMV <= 995.734)
		return STATE_20;
	else if(LMT_GETMV >= 890.423 && LMT_GETMV <= 943.907)
		return STATE_30;
	else if(LMT_GETMV >= 838.097 && LMT_GETMV <= 891.934)
		return STATE_40;
//	else if(LMT_GETMV >= 838.097 && LMT_GETMV <= 839.668)
//		return STATE_50;
	else 
		return ERROR;
}
#endif

void LMT_Init()
{
#if MSP432_ENABLE
    ADC14_init(ADC_CH0,ADC_MCLK ,ADC_DIV2,ADC14_BIT14);

#else
	adc_init(LMT_M, LMT_CH, ADC_12BIT);

#endif
}

float LMT_ADC_GetMV()
{
	float LMT_temp = 0;
#if MSP432_ENABLE
	LMT_temp = ADC14_read_data(ADC_CH0);
	return ((3300 * LMT_temp)/16384);
#else
	LMT_temp = adc_mean_filter(LMT_M, LMT_CH, 10);
	return ((3300 * LMT_temp)/4096);
#endif
}


float LMT_DataHandle()
{
	float LMT_ADCMV;
	
	LMT_ADCMV = LMT_ADC_GetMV();
#if	LMT_MOD0
        uint8 SEL = LMT_DataSelect(LMT_ADCMV);
	switch(SEL)
	{
		case STATE_20:
		{
			COE[LMT_COE_M] = -0.193;
			COE[LMT_COE_B] = 212.009;
			break;
		}
		
		case STATE_30:
		{
			COE[LMT_COE_M] = -0.192;
			COE[LMT_COE_B] = 211.100;
			break;
		}
		
		case STATE_40:
		{
			COE[LMT_COE_M] = -0.191;
			COE[LMT_COE_B] = 210.215;
			break;
		}
		default:
			return ERROR;
	}

	return (COE[LMT_COE_M] * LMT_ADCMV + COE[LMT_COE_B]);

#elif	LMT_MOD1
	return (LMT_COE_A * LMT_ADCMV * LMT_ADCMV + LMT_COE_B * LMT_ADCMV + LMT_COE_C);

#elif	LMT_MOD2
	return (LMT_COE_A * LMT_ADCMV * LMT_ADCMV * LMT_ADCMV + LMT_COE_B * LMT_ADCMV * LMT_ADCMV + LMT_COE_C * LMT_ADCMV + LMT_COE_D);
	
#endif
	return ERROR;
}
	
	
