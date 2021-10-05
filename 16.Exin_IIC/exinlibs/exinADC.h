/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#ifndef _exinADC_h
#define _exinADC_h
#ifdef __cplusplus
extern "C"
{
#endif
#define   THE_MAX_NUM_OF_ADC  8
typedef enum{
  ADC_CHA,
  ADC_CHB,
  ADC_CHC,
  ADC_CHD
}ADC_CHA_eunm;


extern void ADC_TEST();
extern void ADC_INIT();
extern long int GET_ADC_VALUE(ADC_CHA_eunm CHI);
extern long int ADC_mean_filter(ADC_CHA_eunm CHI,unsigned int times);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
