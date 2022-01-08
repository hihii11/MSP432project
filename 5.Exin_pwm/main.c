/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2020��10��23��22:29:47
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
PWM���Գ���
�߲ʵ�
��ɫLED���߰�����������
RED:  P2.6
GREEN:P2.7
BLUE: P2.5
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

#define duty_max SMCLK_FRE/1000


void RGB_565(uint16 RGB,uint16 * pwmR,uint16 * pwmG,uint16 * pwmB)//��RGB565ת��ΪPWM��ռ�ձ�
{
    uint16 RED   = (RGB>>11) & 0x1f;
    uint16 BLUE  = RGB & 0x1f;
    uint16 GREEN = (RGB>>5) & 0x3f;
    *pwmR = ((float)RED/31.0)*duty_max;
    *pwmG = ((float)GREEN/63.0)*duty_max;
    *pwmB = ((float)BLUE/31.0)*duty_max;
}

int i=0;
uint16 dutyA = 0;//Aͨ��ռ�ձ�
uint16 dutyB = 0;//Bͨ��ռ�ձ�
uint16 dutyC = 0;//Cͨ��ռ�ձ�
uint8  status = 0;
void main()
{
    system_init(1);
    set_DCO_48MH();

    pwm_init(pwm_CHA,1000,0);//��
    pwm_init(pwm_CHB,1000,0);//��
    pwm_init(pwm_CHC,1000,0);//��

    while(1)
    {
        if(status==0)
        {
            dutyA = 1500;
            dutyB += 10;
            if(dutyB>=1500)
            {
                status=1;
            }
        }
        if(status==1)
        {
            dutyA = 1500;
            dutyB -= 10;
            dutyC += 10;
            if(dutyC>=1500)
            {
                status=2;
            }
        }
        if(status==2)
       {
           dutyA -= 10;
           dutyB += 10;
           dutyC = 1500;
           if(dutyB>=1500||dutyC<=0)
           {
               status=3;
           }
       }
        if(status==3)
        {
           dutyA += 10;
           dutyB = 1500;
           dutyC -= 10;
           if(dutyA>=1500||dutyC<=0)
           {
               status=4;
           }
       }
        if(status==4)
        {
           dutyA = 1500;
           dutyB -= 10;
           dutyC -= 10;
           if(dutyA>=1500||dutyC<=0)
           {
               status=0;
           }
       }
        pwm_duty(pwm_CHA,dutyA);
        pwm_duty(pwm_CHB,dutyB);
        pwm_duty(pwm_CHC,dutyC);//��������ͨ��ռ�ձ�
        delay_ms(20);
    }
}
