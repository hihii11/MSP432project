/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月16日19:48:33
-------------------------------------------------------------------------------------------------------*/

#include "headfile.h"
#include "exinADC0832.h"

/*************************************************
 * 函  数  名:ADC0832_init
 * 功       能:ADC0832驱动引脚初始化
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      当选择CH0、CH1时会对第一片ADC0832进行初始化
 *      当选择CH2、CH3时会对第二片ADC0832进行初始化
 *************************************************/
void ADC0832_init(ADC0832_CH ADC0832_CHA)
{
    if(ADC0832_CHA == CH0 || ADC0832_CHA == CH1)//初始化第一片ADC0832
    {
        DI0_OUT;
        DO0_IN;
        CK0_OUT;
        CS0_OUT;
    }
    else//初始化第二片ADC0832
    {
        DI1_OUT;
        DO1_IN;
        CK1_OUT;
        CS1_OUT;
    }
}
/*************************************************
 * 函  数  名:ADC0832_enable
 * 功       能:ADC0832芯片使能
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      当选择CH0、CH1时会对第一片ADC0832进行使能CS端拉低
 *      当选择CH2、CH3时会对第二片ADC0832进行使能CS端拉低
 *************************************************/
void ADC0832_enable(ADC0832_CH ADC0832_CHA)
{
       if(ADC0832_CHA == CH0 || ADC0832_CHA == CH1)//片选第一片0832
           CS0_LOW;
       else//片选第二片ADC0832
           CS1_LOW;
}
/*************************************************
 * 函  数  名:ADC0832_disable
 * 功       能:ADC0832芯片禁能
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      当选择CH0、CH1时会对第一片ADC0832进行禁能CS端拉高
 *      当选择CH2、CH3时会对第二片ADC0832进行禁能CS端拉高
 *************************************************/
void ADC0832_disable(ADC0832_CH ADC0832_CHA)
{
      if(ADC0832_CHA == CH0 || ADC0832_CHA == CH1)//禁能第一片0832
          CS0_HIGH;
      else//禁能第二片ADC0832
          CS1_HIGH;
}
/*************************************************
 * 函  数  名:ADC0832_write_DI
 * 功       能:将DI数据端信号写入芯片
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 *          DI_data:需要写入的高低电平
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      当选择CH0、CH1时会将DI_data写入第一片ADC0832
 *      当选择CH2、CH3时会将DI_data写入第二片ADC0832
 *************************************************/
void ADC0832_write_DI(ADC0832_CH ADC0832_CHA , uint8 DI_data)
{

    if(ADC0832_CHA == CH0 || ADC0832_CHA == CH1)//向第一片0832写
    {
        CK0_LOW;//拉低CK时钟线
        if(DI_data)
        {
            DI0_HIGH;
        }
        else
        {
            DI0_LOW;
        }
        ADC0832_delay;
        CK0_HIGH;
        ADC0832_delay
        CK0_LOW;
        ADC0832_delay
    }
    else//向第二片写
    {
        CK1_LOW;//拉低CK时钟线
        if(DI_data)
        {
            DI1_HIGH;
        }
        else
        {
            DI1_LOW;
        }
        ADC0832_delay;
        CK1_HIGH;
        ADC0832_delay
        CK1_LOW;
        ADC0832_delay
    }
}

/*************************************************
 * 函  数  名:ADC0832_CHA_sel
 * 功       能:芯片通道设置
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 *          ADC0832_MODE:芯片工作方式
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      ADC0832的可选工作方式已在exinADC0832.h中列出
 *      ADC0832_MODE = SINGLE 时，则进行单通道采样
 *      此时CH0~CH4都可作为信号输入通道
 *
 *      当ADC0832_MODE = DUAL 时，则进入双通道模式，
 *      此时CH0与CH1作为一个通道
 *          CH2与CH3作为一个通道，且在这种情况下，通道
 *          的正相输入端由ADC0832_CHA参数指定
 *
 *          具体参数如下表
 *          __________________________________________________________________
 *         |   ADC0832_CHA    |   ADC0832_MODE   |  CH0  |  CH1 |  CH2 |  CH3 |
 *         |__________________|__________________|_______|______|______|______|
 *         |      CH0         |      SINGLE      |   +   |      |      |      |
 *         |      CH1         |      SINGLE      |       |   +  |      |      |
 *         |      CH2         |      SINGLE      |       |      |   +  |      |
 *         |      CH3         |      SINGLE      |       |      |      |   +  |
 *         |      CH0         |      DULE        |   +   |   -  |      |      |
 *         |      CH1         |      DULE        |   -   |   +  |      |      |
 *         |      CH2         |      DULE        |       |      |   +  |   -  |
 *         |      CH3         |      DULE        |       |      |   -  |   +  |
 *         ————————————————————————————————————————————————————————————————————
 *************************************************/
void ADC0832_CHA_sel(ADC0832_CH ADC0832_CHA , ADC0832_MOD ADC0832_MODE)
{
    ADC0832_write_DI(ADC0832_CHA , 1);//DI写入1 启动AD转换

    if(ADC0832_MODE == SINGLE)//如果是单通道
    {
        ADC0832_write_DI(ADC0832_CHA , 1);               //DI写入1 选择单通道模式
        ADC0832_write_DI(ADC0832_CHA , ADC0832_CHA % 2); //选择使能通道
    }
    else //选择双通道
    {
        ADC0832_write_DI(ADC0832_CHA , 0);              //DI写入0 选择双通道模式
        ADC0832_write_DI(ADC0832_CHA , ADC0832_CHA % 2);//选择正输入端
    }
}

/*************************************************
 * 函  数  名:ADC0832_read_Byte
 * 功       能:ADC0832芯片进行一次转换并读取转换结果
 * 参       数:ADC0832_CHA:ADC0832通道选择变量
 *          ADC0832_MODE:芯片工作方式
 *                 CHECK:校验使能端
 * 注意事项:
 *      ADC0832的可选通道已在exinADC0832.h中列出
 *      可选通道:
 *              CH0~CH3
 *      ADC0832的可选工作方式已在exinADC0832.h中列出
 *      ADC0832_MODE = SINGLE 时，则进行单通道采样
 *      此时CH0~CH4都可作为信号输入通道
 *
 *      当ADC0832_MODE = DUAL 时，则进入双通道模式，
 *      此时CH0与CH1作为一个通道
 *          CH2与CH3作为一个通道，且在这种情况下，通道
 *          的正相输入端由ADC0832_CHA参数指定
 *
 *          具体参数组合与对应的返回值如下表
 *          ________________________________________________________________________________________
 *         |   ADC0832_CHA    |   ADC0832_MODE   |  CH0  |  CH1 |  CH2 |  CH3 |  函数返回值                 |
 *         |__________________|__________________|_______|______|______|______|_____________________|
 *         |      CH0         |      SINGLE      |   +   |      |      |      |CH0单通道采样值           |
 *         |      CH1         |      SINGLE      |       |   +  |      |      |CH1单通道采样值           |
 *         |      CH2         |      SINGLE      |       |      |   +  |      |CH2单通道采样值           |
 *         |      CH3         |      SINGLE      |       |      |      |   +  |CH3单通道采样值           |
 *         |      CH0         |      DULE        |   +   |   -  |      |      |(CH0-CH1)双通道采样值|
 *         |      CH1         |      DULE        |   -   |   +  |      |      |(CH1-CH0)双通道采样值|
 *         |      CH2         |      DULE        |       |      |   +  |   -  |(CH2-CH3)双通道采样值|
 *         |      CH3         |      DULE        |       |      |   -  |   +  |(CH3-CH2)双通道采样值|
 *         —————————————————————————————————————————————————————————————————————————————————————————
 *************************************************/
uint8 ADC0832_read_Byte(ADC0832_CH ADC0832_CHA , ADC0832_MOD ADC0832_MODE , uint8 CHECK)
{
    static uint8 value;
    uint8 data0 = 0;
    uint8 data1 = 0;
    uint8 i;
    ADC0832_enable(ADC0832_CHA);//使能对应ADC0832
    ADC0832_CHA_sel(ADC0832_CHA , ADC0832_MODE);//进行通道与模式的选择
    if(ADC0832_CHA == CH0 ||ADC0832_CHA == CH1)//读第一片
    {
        for(i=0;i<8;i++)
       {
            CK0_LOW;
            ADC0832_delay;
            CK0_HIGH;
            ADC0832_delay;
            CK0_LOW;
            ADC0832_delay;
           if(DO0_READ)
               data0 = data0<<1|0x01;
           else
               data0 = data0<<1;
       }
    }
    else//读第二片
    {
        for(i=0;i<8;i++)
        {
             CK1_LOW;
             ADC0832_delay;
             CK1_HIGH;
             ADC0832_delay;
             CK1_LOW;
             ADC0832_delay;
            if(DO1_READ)
                data0 = data0<<1|0x01;
            else
                data0 = data0<<1;
        }
    }


    if(CHECK == 0)//不进行校验
    {
        value = data0;
    }
    else if(CHECK == 1)//进行校验
    {

          if(ADC0832_CHA == CH0 ||ADC0832_CHA == CH1)//读第一片
          {
              for(i=0;i<8;i++)
              {
                 if(DO0_READ)
                   data1 = data1>>1|0x80;
                 else
                   data1 = data1>>1;


                  CK0_LOW;
                  ADC0832_delay;
                  CK0_HIGH;
                  ADC0832_delay;
                  CK0_LOW;
                  ADC0832_delay;
              }
          }
          else//读第二片
          {
                for(i=0;i<8;i++)
                {
                   if(DO1_READ)
                     data1 = data1>>1|0x80;
                   else
                     data1 = data1>>1;


                    CK1_LOW;
                    ADC0832_delay;
                    CK1_HIGH;
                    ADC0832_delay;
                    CK1_LOW;
                    ADC0832_delay;
                }
          }

          if(data0 == data1)
              value = data0;
          else
              value = value;
    }
    ADC0832_disable(ADC0832_CHA);//禁能对应ADC0832
    return value;
}

/*************************************************
 * 函  数  名:get_voltage
 * 功       能:将采集到的ADC返回值换算为电压
 * 参       数:vref:参考电压
 *          prec:ADC分辨率
 * 注意事项:无
 *************************************************/
float get_voltage(int ADC_dat , float vref , int prec)
{
    return  ((float)(ADC_dat)/(prec-1))*vref;
}
