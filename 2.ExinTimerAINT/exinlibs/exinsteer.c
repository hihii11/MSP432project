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

//ԭ����������
int steer_dutyA=steer_midA;
int steer_dutyB=steer_midB;
int steer_flag=0;
void OLED_STEER_show()
{
    OLED_ShowString(0, 0, "A:");
    OLED_ShowNum(64, 0,  steer_dutyA, 8, 12);
    OLED_ShowString(0, 1, "B:");
    OLED_ShowNum(64, 1,  steer_dutyB, 8, 12);

     OLED_ShowNum(64, 2,  steer_flag, 8, 12);
}
/***********************************/
/* steer_pwm_duty
 *
 * ������Ժ���(��̨)
 *
 *����S1 pwm+
 *����S2 pwm�ص���ֵ
 *����S3 pwm-
 *����S4 �л���άƽ��
 */
/**********************************/
void STEER_TEST()
{
    system_init(0);
    OLED_Init();
    OLED_Clear();
    key_init(KEY1|KEY2|KEY3|KEY4);//������ʼ��
    steer_pwm_init(steer_CHA,100,steer_midA);//��̨xyƽ��               100hz
    steer_pwm_init(steer_CHB,100,steer_midB);//��̨yzƽ��20000000
    while(1)
    {
        OLED_STEER_show();
        if(!key_get(KEY4))
        {
            delay_ms(6);
            if(!key_get(KEY4))
                steer_flag=!steer_flag;
            while(!key_get(KEY4));
        }
        if(!steer_flag)
        {
                if(!key_get(KEY1))
                {
                    delay_ms(6);
                    if(!key_get(KEY1))
                        steer_dutyA+=10;
                    while(!key_get(KEY1));
                }
                if(!key_get(KEY2))
                 {
                     delay_ms(6);
                     if(!key_get(KEY2))
                         steer_dutyA=steer_midA;
                     while(!key_get(KEY2));
                 }
                if(!key_get(KEY3))
                 {
                      delay_ms(6);
                      if(!key_get(KEY3))
                          steer_dutyA-=10;
                      while(!key_get(KEY3));
                }
        }
        else
          {
                  if(!key_get(KEY1))
                  {
                      delay_ms(6);
                      if(!key_get(KEY1))
                          steer_dutyB+=10;
                      while(!key_get(KEY1));
                  }
                  if(!key_get(KEY2))
                   {
                       delay_ms(6);
                       if(!key_get(KEY2))
                           steer_dutyB=steer_midB;
                       while(!key_get(KEY2));
                   }
                  if(!key_get(KEY3))
                   {
                        delay_ms(6);
                        if(!key_get(KEY3))
                            steer_dutyB-=10;
                        while(!key_get(KEY3));
                  }
          }
        steer_dutyA=steer_limit(steer_CHA,steer_dutyA);
        steer_dutyB=steer_limit(steer_CHB,steer_dutyB);
        steer_pwm_duty(steer_CHA,steer_dutyA);
        steer_pwm_duty(steer_CHB,steer_dutyB);
    }

}
