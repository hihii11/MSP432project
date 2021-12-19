/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��18��19:17:51
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
 /*@@   ���ע��:ADC�ο���ѹΪ3.3V,�����ѹ���ܴ���3.3V
ADC��������
ADC14_repeatmod_init()Ϊ�ظ�ת����ʼ��
ADC14_repeat_recv()Ϊ��ͨ���ظ�ת��ģʽ�����ݽ���
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

char ADC_txt[20]={};

int ADC_CH0_dat,ADC_CH1_dat,ADC_CH2_dat,ADC_CH3_dat,ADC_CH4_dat;


void KEY1_CTL()//����ADC14�ж���������ͣADC14ת��
{
    if(!key_get(KEY1))
    {
        delay_ms(10);
        if(!key_get(KEY1))
        {
            ADC14_convert_disable();
            ADC14_convert_end();//����ADת��
        }
        while(!key_get(KEY1));
    }
}


void KEY2_CTL()//����while(1)�����ڿ�ʼADCת��
{
    if(!key_get(KEY2))
    {
        delay_ms(10);
        if(!key_get(KEY2))
        {
            ADC14_convert_enable();
            ADC14_convert_start();//��ʼADCת��
        }
        while(!key_get(KEY2));
    }
}

void ADC14_repeat_recv()//����һ��ADC���ݶ�ȡ
{
    ADC_CH0_dat = ADC14_STRUCT.repeat_convert_CH[0];//��A0ͨ�����ݶ�ȡ
    ADC_CH1_dat = ADC14_STRUCT.repeat_convert_CH[1];//��A1ͨ�����ݶ�ȡ
    ADC_CH2_dat = ADC14_STRUCT.repeat_convert_CH[2];//��A2ͨ�����ݶ�ȡ
    ADC_CH3_dat = ADC14_STRUCT.repeat_convert_CH[3];//��A3ͨ�����ݶ�ȡ
    ADC_CH4_dat = ADC14_STRUCT.repeat_convert_CH[4];//��A4ͨ�����ݶ�ȡ
}

void ADC14_repeat_show()//����һ�����ݴ�ӡ
{
    //ͨ�����ƴ�ӡ
       OLED_ShowString(0,1,"CH0");
       OLED_ShowString(0,2,"CH1");
       OLED_ShowString(0,3,"CH2");
       OLED_ShowString(0,4,"CH3");
       OLED_ShowString(0,5,"CH4");
    //ADC����ԭʼ���ݴ�ӡ
       OLED_ShowNum(35, 1,  ADC_CH0_dat, 5, 12);
       OLED_ShowNum(35, 2,  ADC_CH1_dat, 5, 12);
       OLED_ShowNum(35, 3,  ADC_CH2_dat, 5, 12);
       OLED_ShowNum(35, 4,  ADC_CH3_dat, 5, 12);
       OLED_ShowNum(35, 5,  ADC_CH4_dat, 5, 12);
       //ת����ѹ������ݴ�ӡ
       OLED_Showfloat(90, 1,  get_voltage(ADC_CH0_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 2,  get_voltage(ADC_CH1_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 3,  get_voltage(ADC_CH2_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 4,  get_voltage(ADC_CH3_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 5,  get_voltage(ADC_CH4_dat , ADC14_REF , 256));

}

void ADC14_repeat_test()//�ظ�ת��ģʽ���Գ��򣬴˺�������exinADC.c��ADC14�жϷ�������
{
    KEY1_CTL();//��������ADC14ת��
    ADC14_repeat_recv();//����һ�����ݽ���
    ADC14_repeat_show();//����һ�����ݴ�ӡ
}

void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    OLED_Clear();

    OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//��ӡ��ͷ

    key_init(KEY1|KEY2);//��ʼ��KEY1 KEY2������ͣ������ת��

    //���н�ֹͨ�������ã�ת��ͨ��ΪA0~A4��ʹ��MCLK����2��Ƶ��Ϊʱ��Դ��8����(256)�ֱ���
    ADC14_repeatmod_init(ADC_CH4,ADC_MCLK,ADC_DIV2,ADC14_BIT8);
    ADC14_convert_start();//������ÿ�ʼת��

    while(1)
    {
        KEY2_CTL();
    }
}

