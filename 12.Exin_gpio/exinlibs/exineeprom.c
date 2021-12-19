/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��15��21:11:33
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exineeprom.h"

#define EEPROM_ADDR            0x28  //EEPROM������ַ(0010 1000)<<2 = 1010 0000
#define WR_DELAY                 10  //EEPROM�����ȶ�����ı�Ҫʱ�䣬����ֵ̫С�����ܵ���EEPROM���ݴ洢����

/*************************************************
 * ��  ��  ��:EROM_IIC_init
 * ��       ��:EEPROM IIC���߳�ʼ��
 * ��       ��:��
 * ע������:��
 *************************************************/
void EROM_IIC_init()
{
    EROM_SCL_OUT;
    EROM_SDA_OUT;
    EROM_SCL_HIGH;
    EROM_SDA_HIGH;
}
/*************************************************
 * ��  ��  ��:EROM_IIC_start
 * ��       ��:IIC������ʼ�ź�
 * ��       ��:��
 * ע������:��
 *************************************************/
//IIC��ʼ�ź�
void EROM_IIC_start()
{
    EROM_SDA_OUT;
    EROM_SDA_HIGH;//��ʼ��Ϊ�ߵ�ƽ
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SDA_LOW;//�Ȱ�SDA����
    EROM_delay;
    EROM_SCL_LOW;//�ٰ�SCL����
}
/*************************************************
 * ��  ��  ��:EROM_IIC_stop
 * ��       ��:IIC���߷��������ź�
 * ��       ��:��
 * ע������:��
 *************************************************/
//IICֹͣ�ź�
void EROM_IIC_stop()
{
    EROM_SDA_OUT;//����SDA����Ϊ���
    EROM_SCL_LOW;
    EROM_SDA_LOW;
    EROM_delay;
    EROM_SCL_HIGH;
    EROM_delay;
    EROM_SDA_HIGH;
    EROM_delay;
}
/*************************************************
 * ��  ��  ��:EROM_IIC_ACK
 * ��       ��:IIC���߷���Ӧ���ź�
 * ��       ��:��
 * ע������:��
 *************************************************/
//����Ӧ��ӻ�
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
 * ��  ��  ��:EROM_IIC_NACK
 * ��       ��:IIC���߲�����Ӧ���ź�
 * ��       ��:��
 * ע������:��
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
 * ��  ��  ��:EROM_Check_ACK
 * ��       ��:�������ӻ��Ƿ�Ӧ��
 * ��       ��:��
 * ע������:��
 *************************************************/
//�������ӻ��Ƿ�Ӧ��
unsigned char EROM_Check_ACK()
{
    uint8 error_time=0;
    EROM_SDA_IN;

    EROM_SDA_HIGH;EROM_delay;//������ʱ
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
 * ��  ��  ��:EROM_IIC_Send_Byte
 * ��       ��:IIC����һ�ֽ�����
 * ��       ��:Data(Ϊһ�ֽ�����)
 * ע������:��
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
 * ��  ��  ��:EROM_IIC_Read_Byte
 * ��       ��:IIC��ȡһ�ֽ�����
 * ��       ��:ack
 *          ack=0 ������Ӧ��  ack=1����Ӧ��
 * ע������:��
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
 * ��  ��  ��:EEPROM_init
 * ��       ��:EEPROM��ʼ������
 * ��       ��:��
 * ע������:��
 *************************************************/
void EEPROM_init()
{
    EROM_IIC_init();//��ʼ��IIC����
}
/*************************************************
 * ��  ��  ��:EEPROM_reset
 * ��       ��:EEPROM IIC���ߵ������λ
 * ��       ��:��
 * ע������:��ϵͳ�ϵ縴λ������ʱ���Ե��øú�����IIC
 *          ���߽��и�λ
 *************************************************/
void EEPROM_reset()//�����λ
{
    uint8 i;
    EROM_IIC_start();

    EROM_SCL_LOW;
    EROM_SDA_HIGH;

    for(i=0;i<9;i++)//����9��ʱ��
    {
        EROM_SCL_LOW;//����ʱ����
        EROM_delay;
        EROM_SCL_HIGH;//����ʱ����
        EROM_delay;
        EROM_SCL_LOW;//����ʱ����
        EROM_delay;
    }
    EROM_IIC_start();
    EROM_IIC_stop();
}
/*********************************************************************
 * ��  ��  ��:EEPROM_write_Byte
 * ��       ��:EEPROMд��һ�ֽ�����
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ     addrֵ��0~255֮��
 *         data:��Ҫ�洢��һ�ֽ�����
 * ע������:��ŵ�ַ���ܳ�����Χ
 ********************************************************************/
uint8 EEPROM_write_Byte(uint8 page , uint8 addr , uint8 data)
{
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//����������ַ ѡ��ҳ д
    if(!EROM_Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       return 1;//����1����
    }
    EROM_IIC_Send_Byte(addr);//�����ֽڵ�ַ
    if(!EROM_Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       return 1;//����1����
    }
    EROM_IIC_Send_Byte(data);//����д������
    if(!EROM_Check_ACK())
    {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
    }
    EROM_IIC_stop();
    delay_ms(WR_DELAY);
    return 0;
}
/*********************************************************************
 * ��  ��  ��:EEPROM_write_int
 * ��       ��:EEPROMд��һ���������ݣ�4�ֽڣ�
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ
 *         data:��Ҫ�洢����������
 * ע������:
            �ڵ��øú����洢��������ʱ����Ҫע���ڴ洢�����У����ݴ�Ÿ�ʽ����
       int:�ɵ͵��߽��д洢��ռ���ĸ��ֽڴ洢�ռ�
       _______________________________
��ַ->| addr  |addr+1 | addr+2|addr+3 |
      |_______|_______|_______|_______|
      |       |       |       |       |
      | ��8λ  | ��8λ  | ��8λ   | ��8λ  |
      |_______|_______|_______|_______|
      |    ��16λ         |     ��16λ        |
      |_______________|_______________|

      **(addr+3)��Ҫ�ж��Ƿ�ᳬ��0-255�ķ�Χ�����򳬳����ֽ���
         0x00��ʼ������������
 ********************************************************************/
uint8 EEPROM_write_int(uint8 page , uint8 addr , int32 data)//����������������
{
    uint8 error_flag;
    int_chr_convertor.data = data;
    error_flag = EEPROM_write_len(page , addr , int_chr_convertor.data_buf , 4);
    delay_ms(WR_DELAY);
    return error_flag;
}
//uint8 EEPROM_write_int(uint8 page , uint8 addr , int32 data)//����λ�����������
//{
//    uint8  data_buf[4]={};
//    uint8 error_flag;
//    data_buf[3] = (data>>24) & 0xff;
//    data_buf[2] = (data>>16) & 0xff;//������ݸ�16λ
//    data_buf[1] = (data>>8)  & 0xff;
//    data_buf[0] = (data)     & 0xff;//������ݵ�16λ
//
//    error_flag = EEPROM_write_len(page , addr , data_buf , 4);
//    return error_flag;
//}
/*********************************************************************
 * ��  ��  ��:EEPROM_write_short
 * ��       ��:EEPROMд��һ�����������ݣ�2�ֽڣ�
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ
 *         data:��Ҫ�洢�Ķ���������
 * ע������:
            �ڵ��øú����洢��������ʱ����Ҫע���ڴ洢�����У����ݴ�Ÿ�ʽ����
       short:�ɵ͵��߽��д洢��ռ�������ֽڴ洢�ռ�
       _______________
��ַ->| addr  |addr+1 |
      |_______|_______|
      |       |       |
      | ��8λ  | ��8λ  |
      |_______|_______|
      |    16λ����      |
      |_______________|

      **(addr+1)��Ҫ�ж��Ƿ�ᳬ��0-255�ķ�Χ�����򳬳����ֽ���
         0x00��ʼ������������
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
//    data_buf[1] = (data>>8)  & 0xff;//������ݸ�8λ
//    data_buf[0] = (data)     & 0xff;//������ݵ�8λ
//
//    error_flag = EEPROM_write_len(page , addr , data_buf , 2);
//    return error_flag;
//}
/*********************************************************************
 * ��  ��  ��:EEPROM_write_float
 * ��       ��:EEPROMд��һ������������(4�ֽ�)
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ
 *         data:��Ҫ�洢�Ķ���������
 * ע������:
            �˺����洢��ʽ���Բο�IEEE�����ʽ,�洢һ��float����������Ҫռ
            �ĸ��ֽڿռ�
       _______________________________________________________
      **(addr+3)��Ҫ�ж��Ƿ�ᳬ��0-255�ķ�Χ�����򳬳����ֽ���
         0x00��ʼ������������
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
 * ��  ��  ��:EEPROM_write_double
 * ��       ��:EEPROMд��һ��˫���ȸ���������(8�ֽ�)
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ
 *         data:��Ҫ�洢�Ķ���������
 * ע������:
            �˺����洢��ʽ���Բο�IEEE�����ʽ,�洢һ��double����������Ҫռ
            �˸��ֽڿռ�
       _______________________________________________________
      **(addr+7)��Ҫ�ж��Ƿ�ᳬ��0-255�ķ�Χ�����򳬳����ֽ���
         0x00��ʼ������������
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
 * ��  ��  ��:EEPROM_write_len
 * ��       ��:EEPROM����д���ֽ�
 * ��       ��:page:ҳѡ��                         page=0д���0ҳ    page=1д���һҳ
 *         addr:������ݵ�Ŀ���ַ
 *         data:��Ҫ�����������ָ��
 *          len:����������
 * ע������:
           ���øú���ʱ���Ὣ�������������addrΪ��ʼ��ַ�������δ��룬ֱ����ַ
           Ϊaddr+len-1��Ž�����
           �ܹ�����д��ĳ���(len <= 16)
       _______________________________________________________
      **(addr+len-1)��Ҫ�ж��Ƿ�ᳬ��0-255�ķ�Χ�����򳬳����ֽ���
         0x00��ʼ������������
 ********************************************************************/
uint8 EEPROM_write_len(uint8 page , uint8 addr , uint8 * data , uint8 len)//����д��
{
    uint8 i;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//����������ַ ѡ��ҳ д
    if(!EROM_Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       return 1;//����1����
    }
    EROM_IIC_Send_Byte(addr);//�����ֽڵ�ַ
    if(!EROM_Check_ACK())
    {
       IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
       return 1;//����1����
    }

    for(i = 0 ; i < len ; i++)
    {
       EROM_IIC_Send_Byte(*data);//����д������
       if(!EROM_Check_ACK())
       {
         IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
         return 1;//����1����
       }
       data++;
    }
    EROM_IIC_stop();
    delay_ms(WR_DELAY);
    return 0;
}
/*********************************************************************
 * ��  ��  ��:EEPROM_read_Byte
 * ��       ��:EEPROM����һ���ֽ�
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 * ע������:
           ���øú���ʱ���Ὣָ����ַaddr��һ�ֽ����ݷ���
 ********************************************************************/
uint8 EEPROM_read_Byte(uint8 page , uint8 addr)
{
    uint8 tmp;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//����������ַ ѡ��ҳ д
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
    EROM_IIC_Send_Byte(addr);//�����ֽڵ�ַ
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x01);//����������ַ ѡ��ҳ ��
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
    tmp = EROM_IIC_Read_Byte(0);//����������Ӧ���ź�
    IIC_stop();
    return tmp;
}
/*********************************************************************
 * ��  ��  ��:EEPROM_read_len
 * ��       ��:EEPROM������ȡ
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 *         data_buf:�������ݻ�����
 *         len:������ȡ����
 * ע������:
           ���øú���ʱ���Ὣָ����ַ(addr-addr+len-1)���ֽ����ݷ���
 ********************************************************************/
uint8 EEPROM_read_len(uint8 page , uint8 addr , uint8 * data_buf , uint8 len)//������
{
    uint8 i;
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x00);//����������ַ ѡ��ҳ д
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
    EROM_IIC_Send_Byte(addr);//�����ֽڵ�ַ
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
    EROM_IIC_start();
    EROM_IIC_Send_Byte((EEPROM_ADDR<<2)|(page<<1)|0x01);//����������ַ ѡ��ҳ ��
    if(!EROM_Check_ACK())
   {
      IIC_stop();//û�м�⵽Ӧ���źžͷ��ͽ����ź�
      return 1;//����1����
   }
   for(i = 0 ; i < len ; i++)
   {
       if( i != len-1)
           data_buf[i] = EROM_IIC_Read_Byte(1);//����Ӧ���ź�
       else
           data_buf[i] = EROM_IIC_Read_Byte(0);//������Ӧ���ź�
   }
   IIC_stop();
   return 0;
}

/*********************************************************************
 * ��  ��  ��:EEPROM_read_int
 * ��       ��:EEPROM��ȡһ������
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 * ע������:
           ���øú���ʱ���Ὣָ����ַaddrΪ��ʼ��ַ���ĸ��ֽ��������������ݷ���
 ********************************************************************/
int EEPROM_read_int(uint8 page , uint8 addr)//������������������
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
//int EEPROM_read_int(uint8 page , uint8 addr)//����λ������������
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
 * ��  ��  ��:EEPROM_read_short
 * ��       ��:EEPROM��ȡһ��������
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 * ע������:
           ���øú���ʱ���Ὣָ����ַaddrΪ��ʼ��ַ�������ֽ������Զ��������ݷ���
 ********************************************************************/
int16 EEPROM_read_short(uint8 page , uint8 addr)//������������������
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
//int16 EEPROM_read_short(uint8 page , uint8 addr)//����λ������������
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
 * ��  ��  ��:EEPROM_read_float
 * ��       ��:EEPROM��ȡһ������������
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 * ע������:
           ���øú���ʱ���Ὣָ����ַaddrΪ��ʼ��ַ���ĸ��ֽ������Ը��������ݷ���
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
 * ��  ��  ��:EEPROM_read_double
 * ��       ��:EEPROM��ȡһ��˫���ȸ���������
 * ��       ��:page:ҳѡ��
 *         addr:���ݵ�Ŀ���ַ
 * ע������:
           ���øú���ʱ���Ὣָ����ַaddrΪ��ʼ��ַ�İ��ĸ��ֽ�������˫���ȸ��������ݷ���
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
