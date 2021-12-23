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
#ifndef _exinsteer_h
#define _exinsteer_h
#ifdef __cplusplus
extern "C"
{
#endif

#define steer_midA 4650//���x,yƽ����ֵ
#define steer_midB 4650//���y,zƽ����ֵ
typedef enum{
    steer_CHA=0,//Aͨ��
    steer_CHB,//Bͨ��
}STEERCH_enum;


extern void steer_pwm_init(STEERCH_enum CHI,int period,int duty);
extern void STEER_TEST();
extern void steer_pwm_duty(STEERCH_enum CHI,int duty);

#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
