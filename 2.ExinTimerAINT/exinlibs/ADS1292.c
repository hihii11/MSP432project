#include "headfile.h"
#include "ADS1292.h"

//115200 ������
long int breath=0;//����
long int heart_beat=0;//����

uint8 data[10]={0};//�������ݰ� ��ʽ(AA AA <��λ����> <��λ����>)
                                        //<��16λ    ��16λ> 0000 0000 0000 0000 0000 0000 0000 0000
                                                        //    data5    data4      data3     data2
uint8 num=0;


/******************���ݰ�����*********************/
void ADS1292_data(uint8 UART_BUFF)
{
          if(num!=0&&num!=1)//�Ѿ���⵽�װ� num=2 3 4 5     6 7 8 9
          {
              data[num++]=UART_BUFF;
          }//���ݰ����ݽ���

          if(num==10)//�������ݰ��������,��ʼ��������
          {
             num=0;
             breath=data[5]<<24|data[4]<<16|data[3]<<8|data[2];
             heart_beat=data[9]<<24|data[8]<<16|data[7]<<8|data[6];
          }

          if(UART_BUFF==0xAA && num==0)//����λ����װ�
          {
              num++;
          }//��һ����ʼλAA���

          if(UART_BUFF==0xAA && num==1)//����λ��⵽�װ� �ڶ�λ����װ�
          {
              num++;
           }//�ڶ�����ʼλAA���

}

