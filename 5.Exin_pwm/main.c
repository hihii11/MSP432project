/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2020年10月23日22:29:47
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
PWM测试程序：
七彩灯
三色LED跳线按照以下连接
RED:  P2.6
GREEN:P2.7
BLUE: P2.5
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

#define duty_max SMCLK_FRE/1000


void RGB_565(uint16 RGB,uint16 * pwmR,uint16 * pwmG,uint16 * pwmB)//将RGB565转换为PWM波占空比
{
    uint16 RED   = (RGB>>11) & 0x1f;
    uint16 BLUE  = RGB & 0x1f;
    uint16 GREEN = (RGB>>5) & 0x3f;
    *pwmR = ((float)RED/31.0)*duty_max;
    *pwmG = ((float)GREEN/63.0)*duty_max;
    *pwmB = ((float)BLUE/31.0)*duty_max;
}

int i=0;
uint16 dutyA = 0;//A通道占空比
uint16 dutyB = 0;//B通道占空比
uint16 dutyC = 0;//C通道占空比
uint8  status = 0;
void main()
{
    system_init(1);
    set_DCO_48MH();

    pwm_init(pwm_CHA,1000,0);//红
    pwm_init(pwm_CHB,1000,0);//绿
    pwm_init(pwm_CHC,1000,0);//蓝

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
        pwm_duty(pwm_CHC,dutyC);//调整三个通道占空比
        delay_ms(20);
    }
}
