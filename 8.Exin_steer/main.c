/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月18日19:54:45
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
舵机测试例程
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"
//原先上左下右
int steer_dutyA=steer_midA;
int steer_dutyB=steer_midA;
int steer_flag=0;
void OLED_STEER_show()
{
    OLED_Show_String(0, 0, "A:",8);
    OLED_Show_Num(64, 0,  steer_dutyA, 4,8);
    OLED_Show_String(0, 1, "B:",8);
    OLED_Show_Num(64, 1,  steer_dutyB, 4,8);

    OLED_Show_Num(64, 2,  steer_flag, 4,8);
}

void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_init();
    OLED_clr();
    UART_init(UART0,9600);
    key_init(KEY1|KEY2|KEY3|KEY4);//按键初始化
    steer_pwm_init(steer_CHB,100,steer_midB);//云台yz平面
    steer_pwm_init(steer_CHA,100,steer_midA);//云台xy平面               100hz duty = 0~30_000

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
       steer_dutyB=steer_limit(steer_CHB,steer_dutyB);//限幅
       steer_pwm_duty(steer_CHA,steer_dutyA);
       steer_pwm_duty(steer_CHB,steer_dutyB);
   }
}

