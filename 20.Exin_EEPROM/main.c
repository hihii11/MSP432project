/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月15日23:31:48
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
EEPROM 读写例程
芯片为at24c04  共两页   每页可写入256字节
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

unsigned char txt_eprom[12]={};


//—————————————————————定义数据段地址——————————————————————
//...addr:起始地址   ..._len:长度(字节)
#define    data0_addr      0x00
#define    data0_len       12  //字符串

#define    data1_addr      data0_addr + data0_len
#define    data1_len       4  //整型

#define    data2_addr      data1_addr + data1_len
#define    data2_len       2  //短整型

#define    data3_addr      data2_addr + data2_len
#define    data3_len       1  //字符型

#define    data4_addr      data3_addr + data3_len
#define    data4_len       4  //浮点型

#define    data5_addr      data4_addr + data4_len
#define    data5_len       8  //双精度浮点型
//——————————————————————————————————————————————————————————


//存储数据定义
unsigned char * data0 = "Hello Exin!";
int             data1 = 115200;
short           data2 = 4800;
unsigned char   data3 = 'E';
float           data4 = 3.14;
double          data5 = 3.1415926;



void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_init();//OLED初始化
    OLED_clr();//清屏
    EEPROM_init();
    EEPROM_reset();//进行IIC总线软件复位


    //在第0页存储数据
    EEPROM_write_len(0 , data0_addr , data0 , data0_len);//存储字符串
    EEPROM_write_int(0 , data1_addr , data1);            //存储一个整型
    EEPROM_write_short(0 , data2_addr , data2);          //存储一个短整型
    EEPROM_write_Byte(0 , data3_addr , data3);           //存储一个字符
    EEPROM_write_float(0 , data4_addr , data4);          //存储一个浮点型
    EEPROM_write_double(0 , data5_addr , data5);         //存储一个双精度浮点型

    while(1)
    {
        EEPROM_read_len(0 ,data0_addr, txt_eprom , data0_len);           //读字符串
        OLED_Show_String(0,1,txt_eprom,8);

        sprintf(txt_eprom,"data1:%d ",EEPROM_read_int(0 , data1_addr));   //读整形
        OLED_Show_String(0,2,txt_eprom,8);

        sprintf(txt_eprom,"data2:%d ",EEPROM_read_short(0 , data2_addr));  //读短整形
        OLED_Show_String(0,3,txt_eprom,8);

        sprintf(txt_eprom,"data3:%c",EEPROM_read_Byte(0 , data3_addr));    //读字符
        OLED_Show_String(0,4,txt_eprom,8);

        sprintf(txt_eprom,"data4:%.4f ",EEPROM_read_float(0 , data4_addr)); //读浮点数
        OLED_Show_String(0,5,txt_eprom,8);

        sprintf(txt_eprom,"data5:%.7f ",EEPROM_read_double(0 , data5_addr));//读双精度浮点数
        OLED_Show_String(0,6,txt_eprom,8);
    }
}
