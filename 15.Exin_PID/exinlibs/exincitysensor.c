/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exincitysensor.h"

int num_ctl[10]={0};
unsigned char sensor_num[20]={0};
int numcount=19;
int rec_count=0;

void Exin_sensor_init()
{
    UART2_init();//初始化串口二
}

void Sensor_data_receive(unsigned char din)
{
    if(rec_count==numcount+1)
     {
        rec_count=0;
        num_ctl[0]=(sensor_num[2]<<4)|sensor_num[1];
        num_ctl[1]=(sensor_num[4]<<4)|sensor_num[3];
        num_ctl[2]=(sensor_num[6]<<4)|sensor_num[5];
        num_ctl[3]=(sensor_num[8]<<4)|sensor_num[7];
        num_ctl[4]=(sensor_num[10]<<4)|sensor_num[9];
        num_ctl[5]=(sensor_num[12]<<4)|sensor_num[11];
        num_ctl[6]=(sensor_num[14]<<4)|sensor_num[13];
        num_ctl[7]=(sensor_num[16]<<4)|sensor_num[15];
        num_ctl[8]=(sensor_num[18]<<4)|sensor_num[17];
        num_ctl[9]=sensor_num[19];
     }
    if(rec_count!=0)
        sensor_num[rec_count++]=din;
    if(din==0x5a&&rec_count==0)
        rec_count++;
}
