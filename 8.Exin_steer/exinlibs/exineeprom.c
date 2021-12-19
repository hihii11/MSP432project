/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月15日21:11:33
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exineeprom.h"

#define EEPROM_ADDR            0x28  //EEPROM器件地址(0010 1000)<<2 = 1010 0000
#define WR_DELAY                 10  //EEPROM数据稳定所需的必要时间，若此值太小，可能导致EEPROM数据存储错误

/*************************************************
 * 函  数  名:EROM_IIC_init
 * 功       能:EEPROM IIC总线初始化
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EROM_IIC_init()
{
    EROM_SCL_OUT;
    EROM_SDA_OUT;
    EROM_SCL_HIGH;
    EROM_SDA_HIGH;
}
/*************************************************
 * 函  数  名:EROM_IIC_start
 * 功       能:IIC发出起始信号
 * 参       数:无
 * 注意事项:无
 *************************************************/
//IIC起始信号
void EROM_IIC_start()
{
    EROM_SDA_OUT;
    EROM_SDA_HIGH;//起始均为高电平
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SDA_LOW;//先把SDA拉低
    EROM_delay;
    EROM_SCL_LOW;//再把SCL拉低
}
/*************************************************
 * 函  数  名:EROM_IIC_stop
 * 功       能:IIC总线发出结束信号
 * 参       数:无
 * 注意事项:无
 *************************************************/
//IIC停止信号
void EROM_IIC_stop()
{
    EROM_SDA_OUT;//设置SDA方向为输出
    EROM_SCL_LOW;
    EROM_SDA_LOW;
    EROM_delay;
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SDA_HIGH;
    EROM_delay;
}
/*************************************************
 * 函  数  名:EROM_IIC_ACK
 * 功       能:IIC总线发出应答信号
 * 参       数:无
 * 注意事项:无
 *************************************************/
//主机应答从机
void EROM_IIC_ACK()
{
    EROM_SCL_LOW;
    EROM_SDA_OUT;
    EROM_SDA_LOW;
    EROM_delay;
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SCL_LOW;
}
/*************************************************
 * 函  数  名:EROM_IIC_NACK
 * 功       能:IIC总线不发出应答信号
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EROM_IIC_NACK()
{
    EROM_SCL_LOW;
    EROM_SDA_OUT;
    EROM_SDA_HIGH;
    EROM_delay;
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SCL_LOW;
}
/*************************************************
 * 函  数  名:EROM_Check_ACK
 * 功       能:主机检查从机是否应答
 * 参       数:无
 * 注意事项:无
 *************************************************/
//主机检查从机是否应答
unsigned char EROM_Check_ACK()
{
    uint8 error_time=0;
    EROM_SDA_IN;

    EROM_SDA_HIGH;EROM_delay;//进行延时
    EROM_SCL_HIGH;EROM_delay;

    while(EROM_SDA_READ)
    {
        error_time=error_time+1;
        if(error_time>250)
        {
            EROM_IIC_stop();
            return 0;
        }
    }
    EROM_SCL_LOW;
    return 1;
}
/*************************************************
 * 函  数  名:EROM_IIC_Send_Byte
 * 功       能:IIC发送一字节数据
 * 参       数:Data(为一字节数据)
 * 注意事项:无
 *************************************************/
void EROM_IIC_Send_Byte(uint8 Data)
{
    EROM_SDA_OUT;
    EROM_SCL_LOW;
    EROM_delay;
    uint8 i;
    for(i=0;i<8;i++)
    {
        if((Data&0x80)>>7==1)
        {
            EROM_SDA_HIGH;
        }
        else
        {
            EROM_SDA_LOW;
        }
        Data<<=1;
        EROM_SCL_HIGH;
        EROM_delay;
        EROM_SCL_LOW;
        EROM_delay;
    }
}
/*************************************************
 * 函  数  名:EROM_IIC_Read_Byte
 * 功       能:IIC读取一字节数据
 * 参       数:ack
 *          ack=0 主机不应答  ack=1主机应答
 * 注意事项:无
 *************************************************/
unsigned char EROM_IIC_Read_Byte(uint8 ack)
{
    uint8 i,temp=0;
    EROM_SDA_IN;

    for(i=0;i<8;i++)
    {
        EROM_SCL_LOW;
        EROM_delay;
        EROM_SCL_HIGH;
        temp = temp <<1;
        if(EROM_SDA_READ==1) temp ++;
    }
    if(!ack)
        EROM_IIC_NACK();
    else
        EROM_IIC_ACK();
    return temp;
}
/*************************************************
 * 函  数  名:EEPROM_init
 * 功       能:EEPROM初始化函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EEPROM_init()
{
    EROM_IIC_init();//初始化IIC总线
}
/*************************************************
 * 函  数  名:EEPROM_reset
 * 功       能:EEPROM IIC总线的软件复位
 * 参       数:无
 * 注意事项:当系统断电复位或重启时可以调用该函数对IIC
 *          总线进行复位
 *************************************************/
void EEPROM_reset()//软件复位
{
    uint8 i;
    EROM_IIC_start();

    EROM_SCL_LOW;
    EROM_SDA_HIGH;

    for(i=0;i<9;i++)//送入9个时钟
    {
        EROM_SCL_LOW;//拉低时钟线
        EROM_delay;
        EROM_SCL_HIGH;//拉高时钟线
        EROM_delay;
        EROM_SCL_LOW;//拉低时钟线
        EROM_delay;
    }
    EROM_IIC_start();
    EROM_IIC_stop();
}
/*********************************************************************
 * 函  数  名:EEPROM_write_Byte
 * 功       能:EEPROM写入一字节数据
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址     addr值在0~255之间
 *         data:需要存储的一字节数据
 * 注意事项:存放地址不能超出范围
 ********************************************************************/
uint8 EEPROM_write_Byte(uint8 page , uint8 addr , uint8 data)
{
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//发送器件地址 选择页 写
    if(!EROM_Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
       return 1;//发送1错误
    }
    EROM_IIC_Send_Byte(addr);//发送字节地址
    if(!EROM_Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
       return 1;//发送1错误
    }
    EROM_IIC_Send_Byte(data);//发送写入数据
    if(!EROM_Check_ACK())
    {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
    }
    EROM_IIC_stop();
    delay_ms(WR_DELAY);
    return 0;
}
/*********************************************************************
 * 函  数  名:EEPROM_write_int
 * 功       能:EEPROM写入一个整型数据（4字节）
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址
 *         data:需要存储的整形数据
 * 注意事项:
            在调用该函数存储整形数据时，需要注意在存储过程中，数据存放格式如下
       int:由低到高进行存储，占用四个字节存储空间
       _______________________________
地址->| addr  |addr+1 | addr+2|addr+3 |
      |_______|_______|_______|_______|
      |       |       |       |       |
      | 低8位  | 高8位  | 低8位   | 高8位  |
      |_______|_______|_______|_______|
      |    低16位         |     高16位        |
      |_______________|_______________|

      **(addr+3)需要判断是否会超出0-255的范围，否则超出部分将从
         0x00开始覆盖其他数据
 ********************************************************************/
uint8 EEPROM_write_int(uint8 page , uint8 addr , int32 data)//利用联合体拆分整形
{
    uint8 error_flag;
    int_chr_convertor.data = data;
    error_flag = EEPROM_write_len(page , addr , int_chr_convertor.data_buf , 4);
    delay_ms(WR_DELAY);
    return error_flag;
}
//uint8 EEPROM_write_int(uint8 page , uint8 addr , int32 data)//利用位操作拆分整形
//{
//    uint8  data_buf[4]={};
//    uint8 error_flag;
//    data_buf[3] = (data>>24) & 0xff;
//    data_buf[2] = (data>>16) & 0xff;//存放数据高16位
//    data_buf[1] = (data>>8)  & 0xff;
//    data_buf[0] = (data)     & 0xff;//存放数据低16位
//
//    error_flag = EEPROM_write_len(page , addr , data_buf , 4);
//    return error_flag;
//}
/*********************************************************************
 * 函  数  名:EEPROM_write_short
 * 功       能:EEPROM写入一个短整型数据（2字节）
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址
 *         data:需要存储的短整形数据
 * 注意事项:
            在调用该函数存储整形数据时，需要注意在存储过程中，数据存放格式如下
       short:由低到高进行存储，占用两个字节存储空间
       _______________
地址->| addr  |addr+1 |
      |_______|_______|
      |       |       |
      | 低8位  | 高8位  |
      |_______|_______|
      |    16位数据      |
      |_______________|

      **(addr+1)需要判断是否会超出0-255的范围，否则超出部分将从
         0x00开始覆盖其他数据
 ********************************************************************/
uint8 EEPROM_write_short(uint8 page , uint8 addr , int16 data)
{
    uint8 error_flag;
    short_chr_convertor.data = data;
    error_flag = EEPROM_write_len(page , addr , short_chr_convertor.data_buf , 2);
    delay_ms(WR_DELAY);
    return error_flag;
}
//uint8 EEPROM_write_short(uint8 page , uint8 addr , int16 data)
//{
//    uint8  data_buf[2]={};
//    uint8 error_flag;
//    data_buf[1] = (data>>8)  & 0xff;//存放数据高8位
//    data_buf[0] = (data)     & 0xff;//存放数据低8位
//
//    error_flag = EEPROM_write_len(page , addr , data_buf , 2);
//    return error_flag;
//}
/*********************************************************************
 * 函  数  名:EEPROM_write_float
 * 功       能:EEPROM写入一个浮点型数据(4字节)
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址
 *         data:需要存储的短整形数据
 * 注意事项:
            此函数存储格式可以参考IEEE定义格式,存储一个float类型数据需要占
            四个字节空间
       _______________________________________________________
      **(addr+3)需要判断是否会超出0-255的范围，否则超出部分将从
         0x00开始覆盖其他数据
 ********************************************************************/
uint8 EEPROM_write_float(uint8 page , uint8 addr , float data )
{
    uint8 error_flag;
    flt_chr_convertor.data = data;
    error_flag = EEPROM_write_len(page , addr , flt_chr_convertor.data_buf , 4);
    delay_ms(WR_DELAY);
    return error_flag;
}

/*********************************************************************
 * 函  数  名:EEPROM_write_double
 * 功       能:EEPROM写入一个双精度浮点型数据(8字节)
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址
 *         data:需要存储的短整形数据
 * 注意事项:
            此函数存储格式可以参考IEEE定义格式,存储一个double类型数据需要占
            八个字节空间
       _______________________________________________________
      **(addr+7)需要判断是否会超出0-255的范围，否则超出部分将从
         0x00开始覆盖其他数据
 ********************************************************************/
uint8 EEPROM_write_double(uint8 page , uint8 addr , double data)
{
    uint8 error_flag;
    dub_chr_convertor.data = data;
    error_flag = EEPROM_write_len(page , addr , dub_chr_convertor.data_buf , 8);
    delay_ms(WR_DELAY);
    return error_flag;
}

/*********************************************************************
 * 函  数  名:EEPROM_write_len
 * 功       能:EEPROM连续写入字节
 * 参       数:page:页选择                         page=0写入第0页    page=1写入第一页
 *         addr:存放数据的目标地址
 *         data:需要存入的数组首指针
 *          len:数据流长度
 * 注意事项:
           调用该函数时，会将送入的数据流以addr为起始地址往后依次存入，直到地址
           为addr+len-1存放结束。
           能够连续写入的长度(len <= 16)
       _______________________________________________________
      **(addr+len-1)需要判断是否会超出0-255的范围，否则超出部分将从
         0x00开始覆盖其他数据
 ********************************************************************/
uint8 EEPROM_write_len(uint8 page , uint8 addr , uint8 * data , uint8 len)//连续写入
{
    uint8 i;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//发送器件地址 选择页 写
    if(!EROM_Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
       return 1;//发送1错误
    }
    EROM_IIC_Send_Byte(addr);//发送字节地址
    if(!EROM_Check_ACK())
    {
       IIC_stop();//没有检测到应答信号就发送结束信号
       return 1;//发送1错误
    }

    for(i = 0 ; i < len ; i++)
    {
       EROM_IIC_Send_Byte(*data);//发送写入数据
       if(!EROM_Check_ACK())
       {
         IIC_stop();//没有检测到应答信号就发送结束信号
         return 1;//发送1错误
       }
       data++;
    }
    EROM_IIC_stop();
    delay_ms(WR_DELAY);
    return 0;
}
/*********************************************************************
 * 函  数  名:EEPROM_read_Byte
 * 功       能:EEPROM读出一个字节
 * 参       数:page:页选择
 *         addr:数据的目标地址
 * 注意事项:
           调用该函数时，会将指定地址addr的一字节数据返回
 ********************************************************************/
uint8 EEPROM_read_Byte(uint8 page , uint8 addr)
{
    uint8 tmp;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//发送器件地址 选择页 写
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
    EROM_IIC_Send_Byte(addr);//发送字节地址
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x01);//发送器件地址 选择页 读
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
    tmp = EROM_IIC_Read_Byte(0);//主机不发送应答信号
    IIC_stop();
    return tmp;
}
/*********************************************************************
 * 函  数  名:EEPROM_read_len
 * 功       能:EEPROM连续读取
 * 参       数:page:页选择
 *         addr:数据的目标地址
 *         data_buf:读出数据缓冲区
 *         len:连续读取长度
 * 注意事项:
           调用该函数时，会将指定地址(addr-addr+len-1)的字节数据返回
 ********************************************************************/
uint8 EEPROM_read_len(uint8 page , uint8 addr , uint8 * data_buf , uint8 len)//连续读
{
    uint8 i;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//发送器件地址 选择页 写
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
    EROM_IIC_Send_Byte(addr);//发送字节地址
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x01);//发送器件地址 选择页 读
    if(!EROM_Check_ACK())
   {
      IIC_stop();//没有检测到应答信号就发送结束信号
      return 1;//发送1错误
   }
   for(i = 0 ; i < len ; i++)
   {
       if( i != len-1)
           data_buf[i] = EROM_IIC_Read_Byte(1);//发送应答信号
       else
           data_buf[i] = EROM_IIC_Read_Byte(0);//不发送应答信号
   }
   IIC_stop();
   return 0;
}

/*********************************************************************
 * 函  数  名:EEPROM_read_int
 * 功       能:EEPROM读取一个整型
 * 参       数:page:页选择
 *         addr:数据的目标地址
 * 注意事项:
           调用该函数时，会将指定地址addr为起始地址的四个字节数据以整型数据返回
 ********************************************************************/
int EEPROM_read_int(uint8 page , uint8 addr)//利用联合体整合数据
{
    uint8 error_flag;
    int data;
    error_flag = EEPROM_read_len(page , addr , int_chr_convertor.data_buf , 4);
    if(!error_flag )
    {
        data = int_chr_convertor.data ;
    }
    else
    {
        data = 999;
    }

    return data;
}
//int EEPROM_read_int(uint8 page , uint8 addr)//利用位操作整合数据
//{
//    uint8 data_buf[4] = {};
//    uint8 error_flag;
//    int data=0;
//    error_flag = EEPROM_read_len(page , addr , data_buf , 4);
//    if(!error_flag )
//    {
//        data = ((int)(data_buf[3])<<24) |
//                ((int)(data_buf[2])<<16) |
//                ((int)(data_buf[1])<<8) |
//                (int)data_buf[0] ;
//    }
//    else
//    {
//        data = 999;
//    }
//
//    return data;
//}
/*********************************************************************
 * 函  数  名:EEPROM_read_short
 * 功       能:EEPROM读取一个短整型
 * 参       数:page:页选择
 *         addr:数据的目标地址
 * 注意事项:
           调用该函数时，会将指定地址addr为起始地址的两个字节数据以短整型数据返回
 ********************************************************************/
int16 EEPROM_read_short(uint8 page , uint8 addr)//利用联合体整合数据
{
    uint8 error_flag;
    short data;
    error_flag = EEPROM_read_len(page , addr , short_chr_convertor.data_buf , 2);
    if(!error_flag)
    {
        data = short_chr_convertor.data ;
    }
    else
    {
        data = 999 ;
    }
    return data;
}
//int16 EEPROM_read_short(uint8 page , uint8 addr)//利用位操作整合数据
//{
//    uint8 data_buf[4] = {};
//    uint8 error_flag;
//    short data;
//    error_flag = EEPROM_read_len(page , addr , data_buf , 2);
//    if(!error_flag)
//    {
//        data = ((short)(data_buf[1])<<8) | (short)(data_buf[0]) ;
//    }
//    else
//    {
//        data = 999 ;
//    }
//    return data;
//}

/*********************************************************************
 * 函  数  名:EEPROM_read_float
 * 功       能:EEPROM读取一个浮点型数据
 * 参       数:page:页选择
 *         addr:数据的目标地址
 * 注意事项:
           调用该函数时，会将指定地址addr为起始地址的四个字节数据以浮点型数据返回
 ********************************************************************/
float EEPROM_read_float(uint8 page , uint8 addr)
{
       uint8 error_flag;
       float data;
       error_flag = EEPROM_read_len(page , addr , flt_chr_convertor.data_buf , 4);

       if(!error_flag )
       {
           data = flt_chr_convertor.data;
       }
       else
       {
           data = 999;
       }
       return data;
}

/*********************************************************************
 * 函  数  名:EEPROM_read_double
 * 功       能:EEPROM读取一个双精度浮点型数据
 * 参       数:page:页选择
 *         addr:数据的目标地址
 * 注意事项:
           调用该函数时，会将指定地址addr为起始地址的八四个字节数据以双精度浮点型数据返回
 ********************************************************************/
double EEPROM_read_double(uint8 page , uint8 addr)
{
       uint8 error_flag;
       double data;
       error_flag = EEPROM_read_len(page , addr , dub_chr_convertor.data_buf , 8);

       if(!error_flag )
       {
           data = dub_chr_convertor.data;
       }
       else
       {
           data = 999;
       }
       return data;
}
