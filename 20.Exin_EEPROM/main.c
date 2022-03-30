/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��15��23:31:48
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
EEPROM ��д����
оƬΪat24c04  ����ҳ   ÿҳ��д��256�ֽ�
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

unsigned char txt_eprom[12]={};


//�������������������������������������������������ݶε�ַ��������������������������������������������
//...addr:��ʼ��ַ   ..._len:����(�ֽ�)
#define    data0_addr      0x00
#define    data0_len       12  //�ַ���

#define    data1_addr      data0_addr + data0_len
#define    data1_len       4  //����

#define    data2_addr      data1_addr + data1_len
#define    data2_len       2  //������

#define    data3_addr      data2_addr + data2_len
#define    data3_len       1  //�ַ���

#define    data4_addr      data3_addr + data3_len
#define    data4_len       4  //������

#define    data5_addr      data4_addr + data4_len
#define    data5_len       8  //˫���ȸ�����
//��������������������������������������������������������������������������������������������������������������������


//�洢���ݶ���
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
    OLED_init();//OLED��ʼ��
    OLED_clr();//����
    EEPROM_init();
    EEPROM_reset();//����IIC���������λ


    //�ڵ�0ҳ�洢����
    EEPROM_write_len(0 , data0_addr , data0 , data0_len);//�洢�ַ���
    EEPROM_write_int(0 , data1_addr , data1);            //�洢һ������
    EEPROM_write_short(0 , data2_addr , data2);          //�洢һ��������
    EEPROM_write_Byte(0 , data3_addr , data3);           //�洢һ���ַ�
    EEPROM_write_float(0 , data4_addr , data4);          //�洢һ��������
    EEPROM_write_double(0 , data5_addr , data5);         //�洢һ��˫���ȸ�����

    while(1)
    {
        EEPROM_read_len(0 ,data0_addr, txt_eprom , data0_len);           //���ַ���
        OLED_Show_String(0,1,txt_eprom,8);

        sprintf(txt_eprom,"data1:%d ",EEPROM_read_int(0 , data1_addr));   //������
        OLED_Show_String(0,2,txt_eprom,8);

        sprintf(txt_eprom,"data2:%d ",EEPROM_read_short(0 , data2_addr));  //��������
        OLED_Show_String(0,3,txt_eprom,8);

        sprintf(txt_eprom,"data3:%c",EEPROM_read_Byte(0 , data3_addr));    //���ַ�
        OLED_Show_String(0,4,txt_eprom,8);

        sprintf(txt_eprom,"data4:%.4f ",EEPROM_read_float(0 , data4_addr)); //��������
        OLED_Show_String(0,5,txt_eprom,8);

        sprintf(txt_eprom,"data5:%.7f ",EEPROM_read_double(0 , data5_addr));//��˫���ȸ�����
        OLED_Show_String(0,6,txt_eprom,8);
    }
}
