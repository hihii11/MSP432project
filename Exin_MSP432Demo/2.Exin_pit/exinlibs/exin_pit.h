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
#ifndef _exin_pit_h
#define _exin_pit_h
#ifdef __cplusplus
extern "C"
{
#endif
typedef enum{
    PIT_CHA,
    PIT_CHB,
    PIT_CHC,
    PIT_CHD,
}PIT_enum;//PWM(���)˫ͨ�����ö��A,BΪ˫ͨ����,CΪ��ͨ��

extern void  PIT_init(PIT_enum CHI,float time);

#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
