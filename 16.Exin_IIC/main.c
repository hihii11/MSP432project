#include "exinlibs\headfile.h"

uint8 IIC_test_num[8]={0x01,0x31,0x00,0xff,0x5a,0xa5,0x88,0xfd};


void main()
{
    system_init(1);//初始化滴答计时器
    set_DCO_48MH();
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
