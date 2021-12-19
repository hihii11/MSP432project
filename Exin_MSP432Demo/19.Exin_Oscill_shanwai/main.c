/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日21:10:17
-------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------
山外上位机测试例程
向山外上位机发送正弦波
串口：UART0
-------------------------------------------------------------------------------------------------------*/


#include "exinlibs\headfile.h"

#define datalen  5  //两位首包 一位数据 两位尾包

char buf[5]={0};
unsigned char sindata[10]={128,218,255,218,128,37,5,37};

void Oscill_send(unsigned char data)
{
    buf[0] = 0x03;
    buf[1] = 0xfc;
    buf[2] = data;
    buf[3] = 0xfc;
    buf[4] = 0x03;
    UART_send_string(EUSCI_A0_BASE,buf);
}

void main()
{
    system_init(1);//初始化滴答计时器
    set_DCO_48MH();

    UART0_init();
    int i=0;
    while(1)
    {
        if(i==8)
            i=0;

        Oscill_send(sindata[i++]);
        delay_ms(100);
    }
}
