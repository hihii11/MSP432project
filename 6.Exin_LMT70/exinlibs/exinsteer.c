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
#include "headfile.h"
#include "exinsteer.h"

/***********************************/
/* steer_pwm_init
 *
 * ���pwm
 *
 *
 *
 * ��ѡ�˿�
 * 5.6(steer_CHA) 5.7(steer_CHB)
 *
 */
/**********************************/
void steer_pwm_init(STEERCH_enum CHI,int period,int duty)
{
    switch(CHI)
    {
        case(steer_CHA):
                    pwm_init(pwm_CHE,period,duty);
                    break;
        case(steer_CHB):
                    pwm_init(pwm_CHF,period,duty);
                    break;
    }
}
/***********************************/
/* steer_limit
 *
 * ����޷�
 *
 *
 */
/**********************************/
int steer_limit(STEERCH_enum CHI,int duty)
{
    if(CHI==steer_CHA)
    {
        if(duty>5100)
            return 5100;
        else if(duty<4190)
            return 4190;
        else
            return duty;
    }
    if(CHI==steer_CHB)
      {
          if(duty>5100)
              return 5100;
          if(duty<4190)
              return 4190;
          else
             return duty;
      }
    return 0;
}

/***********************************/
/* steer_pwm_duty
 *
 * ���ռ�ձ�����
 *
 *
 */
/**********************************/
void steer_pwm_duty(STEERCH_enum CHI,int duty)
{
    switch(CHI)
    {
    case(steer_CHA):pwm_duty(pwm_CHE,duty);break;
    case(steer_CHB):pwm_duty(pwm_CHF,duty);break;
    }
}
