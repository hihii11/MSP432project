/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月18日19:17:51
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
 /*@@   务必注意:ADC参考电压为3.3V,输入电压不能大于3.3V
ADC测试例程
ADC14_repeatmod_init()为重复转换初始化
ADC14_repeat_recv()为单通道重复转换模式下数据接收
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

char ADC_txt[20]={};

int ADC_CH0_dat,ADC_CH1_dat,ADC_CH2_dat,ADC_CH3_dat,ADC_CH4_dat;


void KEY1_CTL()//放在ADC14中断中用于暂停ADC14转换
{
    if(!key_get(KEY1))
    {
        delay_ms(10);
        if(!key_get(KEY1))
        {
            ADC14_convert_disable();
            ADC14_convert_end();//结束AD转换
        }
        while(!key_get(KEY1));
    }
}


void KEY2_CTL()//放在while(1)中用于开始ADC转换
{
    if(!key_get(KEY2))
    {
        delay_ms(10);
        if(!key_get(KEY2))
        {
            ADC14_convert_enable();
            ADC14_convert_start();//开始ADC转换
        }
        while(!key_get(KEY2));
    }
}

void ADC14_repeat_recv()//进行一次ADC数据读取
{
    ADC_CH0_dat = ADC14_STRUCT.repeat_convert_CH[0];//对A0通道数据读取
    ADC_CH1_dat = ADC14_STRUCT.repeat_convert_CH[1];//对A1通道数据读取
    ADC_CH2_dat = ADC14_STRUCT.repeat_convert_CH[2];//对A2通道数据读取
    ADC_CH3_dat = ADC14_STRUCT.repeat_convert_CH[3];//对A3通道数据读取
    ADC_CH4_dat = ADC14_STRUCT.repeat_convert_CH[4];//对A4通道数据读取
}

void ADC14_repeat_show()//进行一次数据打印
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
       OLED_Showfloat(90, 1,  get_voltage(ADC_CH0_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 2,  get_voltage(ADC_CH1_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 3,  get_voltage(ADC_CH2_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 4,  get_voltage(ADC_CH3_dat , ADC14_REF , 256));
       OLED_Showfloat(90, 5,  get_voltage(ADC_CH4_dat , ADC14_REF , 256));

}

void ADC14_repeat_test()//重复转换模式测试程序，此函数放在exinADC.c的ADC14中断服务函数中
{
    KEY1_CTL();//按键控制ADC14转换
    ADC14_repeat_recv();//进行一次数据接收
    ADC14_repeat_show();//进行一次数据打印
}

void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    OLED_Clear();

    OLED_ShowString(0,0,"CHA");OLED_ShowString(50,0,"val");OLED_ShowString(90,0,"u(v)");//打印表头

    key_init(KEY1|KEY2);//初始化KEY1 KEY2用于暂停和启动转换

    //进行截止通道的配置，转换通道为A0~A4，使用MCLK进行2分频作为时钟源，8比特(256)分辨率
    ADC14_repeatmod_init(ADC_CH4,ADC_MCLK,ADC_DIV2,ADC14_BIT8);
    ADC14_convert_start();//软件设置开始转换

    while(1)
    {
        KEY2_CTL();
    }
}

