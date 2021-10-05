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
串口测试
引脚:launch pad USB
开始后将从电脑接收到的数据传回电脑
电脑波特率选择115200
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

void main()
{
    system_init(0);
    set_DCO_48MH();
    UART0_init();//初始化串口1，对应launchpad usb接口 波特率115200
    gpio_init(GPIO_PORT_P1,GPIO_PIN1,GPO,1);
    delay_ms(1000);
    UART_send_string(EUSCI_A0_BASE,"HELLO_EXIN\n");
    //UART_send_Num(EUSCI_A0_BASE,80);
    while(1);
}
