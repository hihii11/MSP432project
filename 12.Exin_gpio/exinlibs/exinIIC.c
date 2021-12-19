/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��11��5��20:42:07
-------------------------------------------------------------------------------------------------------*/

#include "headfile.h"
#include "exinIIC.h"

/********************************************************
 * ��  ��  ��:IIC_init
 * ��       ��:IIC���ų�ʼ���������������exinIIC.h�ļ����г�
 * ��       ��:��
 * ע������:��ʹ��IIC��������ʱ������ȵ��ô˺������г�ʼ��
 ********************************************************/
void IIC_init()
{
    IIC_SCL_OUT;
    IIC_SDA_OUT;
    IIC_SCL_HIGH;
    IIC_SDA_HIGH;
}
/********************************************************
 * ��  ��  ��:IIC_reset
 * ��       ��:IIC����������λ����ϵͳ�ϵ����������øú�����λIIC
 * ��       ��:��
 * ע������:��
 ********************************************************/
void IIC_reset()//IIC������λ
{
    uint8 i;
    IIC_start();

    IIC_SCL_LOW;
    IIC_SDA_HIGH;

    for(i=0;i<9;i++)//����9��ʱ��
    {
        IIC_SCL_LOW;//����ʱ����
        IIC_delay;
        IIC_SCL_HIGH;//����ʱ����
        IIC_delay;
        IIC_SCL_LOW;//����ʱ����
        IIC_delay;
    }
    IIC_start();
    IIC_stop();
}
/********************************************************
 * ��  ��  ��:IIC_start
 * ��       ��:IIC���߷�����ʼ�ź�
 *          SCL:_______
 *                     |________
 *          SDA:__
 *                |_________
 * ��       ��:��
 * ע������:��
 ********************************************************/
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
/********************************************************
 * ��  ��  ��:IIC_stop
 * ��       ��:IIC���߷��ͽ����ź�
 *          SCL:         ______
 *              ________|
 *          SDA:             _______
 *              ____________|
 * ��       ��:��
 * ע������:��
 ********************************************************/
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
/********************************************************
 * ��  ��  ��:IIC_ACK
 * ��       ��:IIC��������Ӧ���ź�
 * ��       ��:��
 * ע������:��
 ********************************************************/
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
/********************************************************
 * ��  ��  ��:IIC_NACK
 * ��       ��:IIC����������Ӧ���ź�
 * ��       ��:��
 * ע������:��
 ********************************************************/
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

/********************************************************
 * ��  ��  ��:Check_ACK
 * ��       ��:IIC�������ӻ��Ƿ�Ӧ��
 * ��       ��:��
 * ע������:��
 ********************************************************/
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

/********************************************************
 * ��  ��  ��:IIC_Send_Byte
 * ��       ��:����һ��8λ����
 * ��       ��:Data
 * ע������:һ�η���Ϊ8λ��Ϊunsigned char����
 ********************************************************/
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
/********************************************************
 * ��  ��  ��:IIC_Read_Byte
 * ��       ��:������ȡһ������
 * ��       ��:ack
 * ע������:
 *      ��������ȡ��1�ֽ�������Ϊ����ֵ����
            ��ȡ��Ϻ������Ƿ�Ӧ��ͨ��ack��������
            ack = 1�����ڶ�ȡ��1�ֽ����ݺ����һ��Ӧ��
            ack = 0�����ڶ�ȡ��1�ֽ����ݺ󲻲���Ӧ���ź�
 ********************************************************/
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