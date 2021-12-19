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
按键及中断测试

端口外部中断
中断口:P1.1 （pad左边按键）

-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,1);
    gpio_interrupt_INIT(GPIO_PORT_P1,GPIO_PIN1,FALLING);//下降沿触发
    key_init(KEY1|KEY2|KEY3|KEY4);
    key_test();

}
