/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月21日17:01:05
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
定时器中断测试例程
测试TimerA在UP模式下中断
和TImerA在CONTIUNOUS模式下的中断函数
程序功能:以1s为周期闪烁LED1 以250ms为周期闪烁LED2蓝灯
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

void TimerA0_up_INTtest()
{
        gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);//翻转LED1
}
void TimerA3_continousup_INTtest()
{
        gpio_toggle(GPIO_PORT_P2,GPIO_PIN2);//翻转LED2
}
void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,0);//使能LED1
    gpio_init(GPIO_PORT_P2,GPIO_PIN2,GPO,0);//使能LED2蓝灯
    TimerA_CCR0INT_init(TIMERA_A0 , 500);//设置TimerA0 在UP模式下的中断周期为500ms
    TimerA_CCRnINT_init(TIMERA_A3 , TIMERA_CCR1 ,125);//设置TimerA3在CONTINUOUS模式下CCR1中断周期为125ms
    while(1);
}
