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
#ifndef _exinpwm_h
#define _exinpwm_h
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    pwm_CHA=0,//Aͨ��
    pwm_CHB,//Bͨ��
    pwm_CHC,//Cͨ��
    pwm_CHD,//Dͨ��
    pwm_CHE,//Eͨ��
    pwm_CHF,//Fͨ��
    //pwm_CHG//Gͨ��
}PWMCH_enum;
extern void pwm_duty(PWMCH_enum CHI,int duty);
extern void pwm_init(PWMCH_enum CHI,int FRE,int duty);
extern void PWM_TEST();
extern void pwm_pin_init(PWMCH_enum CHI);
extern void pwm_period_set(PWMCH_enum CHI,uint16 FRE);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
