/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��16��19:12:14
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
ADC0832��д����
��Ҫ����������J1���߶˽���H��������ADC0832

�����̽��ɼ�CH0-CH3��ADֵ������OLED����ʾ
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

unsigned char txt_ADC0832[20]={};



uint8  CH0_dat,CH1_dat,CH2_dat,CH3_dat;//���4��ͨ����ADת��ֵ
float  CH0_vol,CH1_vol,CH2_vol,CH3_vol;//��ż���õ��ĵ�ѹֵ


void ADC_run()
{
           //����ԭʼ����
           CH0_dat =ADC0832_read_Byte(CH0 , SINGLE , 0);   //CH0����ͨ��  ��ͨ������   ����������У��
           CH1_dat =ADC0832_read_Byte(CH1 , SINGLE , 0);   //CH1����ͨ��  ��ͨ������   ����������У��
           CH2_dat =ADC0832_read_Byte(CH2 , SINGLE , 0);   //CH0����ͨ��  ��ͨ������   ����������У��
           CH3_dat =ADC0832_read_Byte(CH3 , SINGLE , 0);   //CH0����ͨ��  ��ͨ������   ����������У��

           //�����ѹ
           CH0_vol = get_voltage(CH0_dat , ADC0832_VREF , ADC0832_PREC);//ͨ��0ת��   �ο���ѹ5V �ֱ���256
           CH1_vol = get_voltage(CH1_dat , ADC0832_VREF , ADC0832_PREC);//ͨ��0ת��   �ο���ѹ5V �ֱ���256
           CH2_vol = get_voltage(CH2_dat , ADC0832_VREF , ADC0832_PREC);//ͨ��0ת��   �ο���ѹ5V �ֱ���256
           CH3_vol = get_voltage(CH3_dat , ADC0832_VREF , ADC0832_PREC);//ͨ��0ת��   �ο���ѹ5V �ֱ���256

}

void ADC0832_show()
{

    sprintf(txt_ADC0832,"CH0:  %d  %.2f",CH0_dat,CH0_vol);
    OLED_ShowString(0,1,txt_ADC0832);

    sprintf(txt_ADC0832,"CH1:  %d  %.2f",CH1_dat,CH1_vol);
    OLED_ShowString(0,2,txt_ADC0832);

    sprintf(txt_ADC0832,"CH2:  %d  %.2f",CH2_dat,CH2_vol);
    OLED_ShowString(0,3,txt_ADC0832);

    sprintf(txt_ADC0832,"CH3:  %d  %.2f",CH3_dat,CH3_vol);
    OLED_ShowString(0,4,txt_ADC0832);
}

void main()
{
    system_init(0);
    OLED_Init();//OLED��ʼ��
    OLED_Clear();//����

   //ADC���ų�ʼ��
    ADC0832_init(CH0);
    ADC0832_init(CH1);
    ADC0832_init(CH2);
    ADC0832_init(CH3);

    OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//��ӡ��ͷ
    while(1)
    {
        ADC_run();ADC0832_show();
    }
}


