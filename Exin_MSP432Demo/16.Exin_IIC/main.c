#include "exinlibs\headfile.h"

uint8 IIC_test_num[8]={0x01,0x31,0x00,0xff,0x5a,0xa5,0x88,0xfd};


void main()
{
    system_init(1);//初始化滴答计时器
    set_DCO_48MH();//注意这边的函数与其他例程不同，其他例程SMCLK为3MHZ，为了得到更高占空比可调范围，以及更高的电机基频率，本例程分频SMCLK为24MHZ
    IIC_init();
    while(1)
    {
        uint8 i;
        for(i=0;i<8;i++)
        {
            IIC_start();
            IIC_Send_Byte(IIC_test_num[i]);
            IIC_ACK();
            IIC_stop();
        }
    }
}
