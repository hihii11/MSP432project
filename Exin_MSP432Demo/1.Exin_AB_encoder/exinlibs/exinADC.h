/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2019��1��23��22:29:47
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
