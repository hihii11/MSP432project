/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月16日19:12:14
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
ADC0832读写例程
需要将开发板上J1跳线端接至H，来访问ADC0832

此例程将采集CH0-CH3的AD值，并在OLED上显示
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

unsigned char txt_ADC0832[20]={};



uint8  CH0_dat,CH1_dat,CH2_dat,CH3_dat;//存放4个通道的AD转换值
float  CH0_vol,CH1_vol,CH2_vol,CH3_vol;//存放计算得到的电压值


void ADC_run()
{
           //接收原始数据
           CH0_dat =ADC0832_read_Byte(CH0 , SINGLE , 0);   //CH0采样通道  单通道采样   不进行数据校验
           CH1_dat =ADC0832_read_Byte(CH1 , SINGLE , 0);   //CH1采样通道  单通道采样   不进行数据校验
           CH2_dat =ADC0832_read_Byte(CH2 , SINGLE , 0);   //CH0采样通道  单通道采样   不进行数据校验
           CH3_dat =ADC0832_read_Byte(CH3 , SINGLE , 0);   //CH0采样通道  单通道采样   不进行数据校验

           //换算电压
           CH0_vol = get_voltage(CH0_dat , ADC0832_VREF , ADC0832_PREC);//通道0转换   参考电压5V 分辨率256
           CH1_vol = get_voltage(CH1_dat , ADC0832_VREF , ADC0832_PREC);//通道0转换   参考电压5V 分辨率256
           CH2_vol = get_voltage(CH2_dat , ADC0832_VREF , ADC0832_PREC);//通道0转换   参考电压5V 分辨率256
           CH3_vol = get_voltage(CH3_dat , ADC0832_VREF , ADC0832_PREC);//通道0转换   参考电压5V 分辨率256

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
    OLED_Init();//OLED初始化
    OLED_Clear();//清屏

   //ADC引脚初始化
    ADC0832_init(CH0);
    ADC0832_init(CH1);
    ADC0832_init(CH2);
    ADC0832_init(CH3);

    OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//打印表头
    while(1)
    {
        ADC_run();ADC0832_show();
    }
}


