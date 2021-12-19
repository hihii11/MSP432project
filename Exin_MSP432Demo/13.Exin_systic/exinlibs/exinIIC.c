/*
 * exinIIC.c
 *
 *  Created on: 2021��9��27��
 *      Author: 93793
 */

#include "headfile.h"
#include "exinIIC.h"


void IIC_init()
{
    IIC_SCL_OUT;
    IIC_SDA_OUT;
    IIC_SCL_HIGH;
    IIC_SDA_HIGH;
}
//IIC��ʼ�ź�
void IIC_start()
{
    IIC_SDA_OUT;
    IIC_SDA_HIGH;//��ʼ��Ϊ�ߵ�ƽ
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SDA_LOW;//�Ȱ�SDA����
    IIC_delay;
    IIC_SCL_LOW;//�ٰ�SCL����
}
//IICֹͣ�ź�
void IIC_stop()
{
    IIC_SDA_OUT;//����SDA����Ϊ���
    IIC_SCL_LOW;
    IIC_SDA_LOW;
    IIC_delay;
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SDA_HIGH;
    IIC_delay;
 //   IIC_SCL_LOW;
 //   IIC_SDA_LOW;
}

//����Ӧ��ӻ�
void IIC_ACK()
{
    IIC_SCL_LOW;
    IIC_SDA_OUT;
    IIC_SDA_LOW;
    IIC_delay;
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SCL_LOW;
}
void IIC_NACK()
{
    IIC_SCL_LOW;
    IIC_SDA_OUT;
    IIC_SDA_HIGH;
    IIC_delay;
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SCL_LOW;
}
/*
void IIC_ACK(uint8 ACK_FLAG)
{
    IIC_SDA_OUT;
    IIC_SCL_LOW;
    IIC_delay;
    if(ACK_FLAG==1)//����Ӧ��
    {
        IIC_SDA_LOW;IIC_delay;
    }

    else if(ACK_FLAG==0)//������Ӧ��
    {
        IIC_SDA_HIGH;IIC_delay;
    }
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SCL_LOW;
}*/
//�������ӻ��Ƿ�Ӧ��
unsigned char Check_ACK()
{
    uint8 error_time=0;
    IIC_SDA_IN;

    IIC_SDA_HIGH;IIC_delay;//������ʱ
    IIC_SCL_HIGH;IIC_delay;

    while(IIC_SDA_READ)
    {
        error_time=error_time+1;
        if(error_time>250)
        {
            IIC_stop();
            return 0;
        }
    }
    IIC_SCL_LOW;
    return 1;
}

void IIC_Send_Byte(uint8 Data)
{
    IIC_SDA_OUT;
    IIC_SCL_LOW;
    IIC_delay;
    uint8 i;
    for(i=0;i<8;i++)
    {
        if((Data&0x80)>>7==1)
        {
            IIC_SDA_HIGH;
        }
        else
        {
            IIC_SDA_LOW;
        }
        Data<<=1;
            IIC_SCL_HIGH;
            IIC_delay;
            IIC_SCL_LOW;
            IIC_delay;
    }
}

unsigned char IIC_Read_Byte(uint8 ack)
{
    uint8 i,temp=0;
    IIC_SDA_IN;

    for(i=0;i<8;i++)
    {
        IIC_SCL_LOW;
        IIC_delay;
        IIC_SCL_HIGH;
        temp = temp <<1;
        if(IIC_SDA_READ==1) temp ++;
    }
    if(!ack)
        IIC_NACK();
    else
        IIC_ACK();
    return temp;
}
