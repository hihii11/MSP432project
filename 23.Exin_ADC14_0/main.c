/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��17��23:33:52
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
 /*@@   ���ע��:ADC�ο���ѹΪ3.3V,�����ѹ���ܴ���3.3V
ADC��������
ADC14_once_init()Ϊ��ͨ������ת����ʼ��
ADC14_once_recv()Ϊ��ͨ������ת�����ݽ���
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

char ADC_txt[20]={};

int ADC_CH0_dat,ADC_CH1_dat,ADC_CH2_dat,ADC_CH3_dat,ADC_CH4_dat;
int index_rec = 0;
uint8 Heart_val[129] = {0};
extern uint8_t screen_buf[128][64];


void Heart_val_updata(uint8 data)
{
    int i;
    for(i = 0 ; i <= 127 ; i++ )//��������ADCֵ
    {
        Heart_val[i] = Heart_val[i+1];
    }
    Heart_val[128] = data;
}
void screen_buf_updat(uint8 * buf)
{
    int i;
    for(i = 0; i < 128 ; i++)
    {
        screen_buf[i][buf[i]] = 0;
    }
    for(i = 1; i < 129 ; i++)
    {
          screen_buf[i-1][buf[i]] = 1;
    }
}


void ADC14_once_init()
{
    //���¾�Ϊ��ͨ�������β�����ʼ��
    ADC14_init(ADC_CH0,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//��ʼ��ADC_CH0(A0)ͨ�� �˿�ΪP5.5
    ADC14_init(ADC_CH1,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//��ʼ��ADC_CH1(A1)ͨ�� �˿�ΪP5.4
    ADC14_init(ADC_CH2,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//��ʼ��ADC_CH2(A2)ͨ�� �˿�ΪP5.3
    ADC14_init(ADC_CH3,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//��ʼ��ADC_CH3(A3)ͨ�� �˿�ΪP5.2
    ADC14_init(ADC_CH4,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//��ʼ��ADC_CH4(A4)ͨ�� �˿�ΪP5.1
    //ѡ��MCLK������2��Ƶ��ΪADC14��ʱ��
    //��ʱ�������������ʱ����ÿ��ͨ���Ĳ���Ƶ��ΪMCLK(3Mhz)/��Ƶ(2)/(����(4)+����(9)+1) ��1.07Mhz
    //����Ϊ�ǵ���ת������Ҫ������ÿ�ʼת����������Ҫ�������ʱ���Լ�������ʾ��OLED���ʱ�䣬����ʵ�ʲ���Ƶ�ʵ���1.07MHz
}

void ADC14_once_recv()
{
    ADC_CH0_dat = ADC14_read_data(ADC_CH0);//����һ�ζ�A0ͨ���Ĳ���
    ADC_CH1_dat = ADC14_read_data(ADC_CH1);//����һ�ζ�A1ͨ���Ĳ���
    ADC_CH2_dat = ADC14_read_data(ADC_CH2);//����һ�ζ�A2ͨ���Ĳ���
    ADC_CH3_dat = ADC14_read_data(ADC_CH3);//����һ�ζ�A3ͨ���Ĳ���
    ADC_CH4_dat = ADC14_read_data(ADC_CH4);//����һ�ζ�A4ͨ���Ĳ���
}

void ADC14_once_show()
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
       OLED_Showfloat(90, 1,  get_voltage(ADC_CH0_dat , 3.3 , 256));
       OLED_Showfloat(90, 2,  get_voltage(ADC_CH1_dat , 3.3 , 256));
       OLED_Showfloat(90, 3,  get_voltage(ADC_CH2_dat , 3.3 , 256));
       OLED_Showfloat(90, 4,  get_voltage(ADC_CH3_dat , 3.3 , 256));
       OLED_Showfloat(90, 5,  get_voltage(ADC_CH4_dat , 3.3 , 256));

}
uint8 clr_cnt = 0;
void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    OLED_Clear();
    //���и�ͨ���ĳ�ʼ��������ú���
    ADC14_init(ADC_CH0,ADC_MCLK ,ADC_DIV1,ADC14_BIT8);//��ʼ��ADC_CH0(A0)ͨ�� �˿�ΪP5.5

   // OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//��ӡ��ͷ

    while(1)
    {
        ADC_CH0_dat = ADC14_read_data(ADC_CH0);
        ADC_CH0_dat = ((float)(ADC_CH0_dat-120)/100.0)*63;
        Heart_val_updata(ADC_CH0_dat);
        int i;
        clr_cnt++;

        if(clr_cnt == 20)
        {
            OLED_Clear();
            for(i = 0;i<128;i++)
           {
               int data = 64-Heart_val[i]-25;
               OLED_PutPixel(i,data);
           }
            clr_cnt = 0;
        }
        delay_ms(4);
    }
}

