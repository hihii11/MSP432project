#include "headfile.h"
#include "ADS1292.h"

//115200 波特率
long int breath=0;//呼吸
long int heart_beat=0;//心跳

uint8 data[10]={0};//接收数据包 格式(AA AA <四位呼吸> <四位心跳>)
                                        //<低16位    高16位> 0000 0000 0000 0000 0000 0000 0000 0000
                                                        //    data5    data4      data3     data2
uint8 num=0;


/******************数据包解析*********************/
void ADS1292_data(uint8 UART_BUFF)
{
          if(num!=0&&num!=1)//已经检测到首包 num=2 3 4 5     6 7 8 9
          {
              data[num++]=UART_BUFF;
          }//数据包数据接收

          if(num==10)//完整数据包接收完毕,开始处理数据
          {
             num=0;
             breath=data[5]<<24|data[4]<<16|data[3]<<8|data[2];
             heart_beat=data[9]<<24|data[8]<<16|data[7]<<8|data[6];
          }

          if(UART_BUFF==0xAA && num==0)//第零位检测首包
          {
              num++;
          }//第一个起始位AA检测

          if(UART_BUFF==0xAA && num==1)//第零位检测到首包 第二位检测首包
          {
              num++;
           }//第二个起始位AA检测

}

