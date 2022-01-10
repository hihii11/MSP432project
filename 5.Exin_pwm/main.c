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
    pwm_init(pwm_CHC,1000,0);//��  ����SMCLK_FRE = 24000_000 ����ռ�ձȿɵ���ΧΪ 0~24000

    while(1)
    {
        if(status==0)
        {
            dutyA = 12000;
            dutyB += 80;
            if(dutyB>=12000)
            {
                status=1;
            }
        }
        if(status==1)
        {
            dutyA = 12000;
            dutyB -= 80;
            dutyC += 80;
            if(dutyC>=12000)
            {
                status=2;
                dutyB=0;
            }
        }
        if(status==2)
       {
           dutyA -= 80;
           dutyB += 80;
           dutyC = 12000;
           if(dutyB>=12000||dutyA<=0)
           {
               status=3;
               dutyA=0;
           }
       }
        if(status==3)
        {
           dutyA += 80;
           dutyB = 12000;
           dutyC -= 80;
           if(dutyA>=12000||dutyC<=0)
           {
               status=4;
               dutyC=0;
           }
       }
        if(status==4)
        {
           dutyA = 12000;
           dutyB -= 80;
           dutyC -= 80;
           if(dutyA>=12000||dutyC<=0)
           {
               status=0;
               dutyB=0;
               dutyC=0;
           }
       }
        pwm_duty(pwm_CHA,dutyA);
        pwm_duty(pwm_CHB,dutyB);
        pwm_duty(pwm_CHC,dutyC);//��������ͨ��ռ�ձ�
        delay_ms(20);
    }
}
