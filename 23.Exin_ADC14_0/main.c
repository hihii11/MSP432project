/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月17日23:33:52
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
 /*@@   务必注意:ADC参考电压为3.3V,输入电压不能大于3.3V
ADC测试例程
ADC14_once_init()为单通道单次转换初始化
ADC14_once_recv()为单通道单次转换数据接收
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
    for(i = 0 ; i <= 127 ; i++ )//左移移入ADC值
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
    //以下均为单通道、单次采样初始化
    ADC14_init(ADC_CH0,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//初始化ADC_CH0(A0)通道 端口为P5.5
    ADC14_init(ADC_CH1,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//初始化ADC_CH1(A1)通道 端口为P5.4
    ADC14_init(ADC_CH2,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//初始化ADC_CH2(A2)通道 端口为P5.3
    ADC14_init(ADC_CH3,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//初始化ADC_CH3(A3)通道 端口为P5.2
    ADC14_init(ADC_CH4,ADC_MCLK ,ADC_DIV2,ADC14_BIT8);//初始化ADC_CH4(A4)通道 端口为P5.1
    //选用MCLK并进行2分频作为ADC14的时钟
    //此时若不计算程序延时，则每个通道的采样频率为MCLK(3Mhz)/分频(2)/(采样(4)+量化(9)+1) ≈1.07Mhz
    //但因为是单次转换，需要软件设置开始转换，所以需要算上软件时间以及用于显示的OLED软件时间，所以实际采样频率低于1.07MHz
}

void ADC14_once_recv()
{
    ADC_CH0_dat = ADC14_read_data(ADC_CH0);//触发一次对A0通道的采样
    ADC_CH1_dat = ADC14_read_data(ADC_CH1);//触发一次对A1通道的采样
    ADC_CH2_dat = ADC14_read_data(ADC_CH2);//触发一次对A2通道的采样
    ADC_CH3_dat = ADC14_read_data(ADC_CH3);//触发一次对A3通道的采样
    ADC_CH4_dat = ADC14_read_data(ADC_CH4);//触发一次对A4通道的采样
}

void ADC14_once_show()
{
    //通道名称打印
       OLED_ShowString(0,1,"CH0");
       OLED_ShowString(0,2,"CH1");
       OLED_ShowString(0,3,"CH2");
       OLED_ShowString(0,4,"CH3");
       OLED_ShowString(0,5,"CH4");
    //ADC采样原始数据打印
       OLED_ShowNum(35, 1,  ADC_CH0_dat, 5, 12);
       OLED_ShowNum(35, 2,  ADC_CH1_dat, 5, 12);
       OLED_ShowNum(35, 3,  ADC_CH2_dat, 5, 12);
       OLED_ShowNum(35, 4,  ADC_CH3_dat, 5, 12);
       OLED_ShowNum(35, 5,  ADC_CH4_dat, 5, 12);
       //转换电压后的数据打印
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
    //进行各通道的初始化，详见该函数
    ADC14_init(ADC_CH0,ADC_MCLK ,ADC_DIV1,ADC14_BIT8);//初始化ADC_CH0(A0)通道 端口为P5.5

   // OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//打印表头

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

