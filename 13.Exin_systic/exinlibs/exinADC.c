/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月17日23:31:16
-------------------------------------------------------------------------------------------------------*/
#include"headfile.h"
#include "exinADC.h"

/*************************************************
 * 函  数  名:ADC14_convert_enable
 * 功       能:使能ADC14转换
 * 参       数:无
 * 注意事项:无
 *************************************************/
void ADC14_convert_enable()//使能AD14转换
{
    ADC14->CTL0 |= ADC14_CTL0_ENC;//设置ENC标志位
}
/*************************************************
 * 函  数  名:ADC14_convert_enable
 * 功       能:禁能ADC14转换
 * 参       数:无
 * 注意事项:无
 *************************************************/
void ADC14_convert_disable()//禁能AD14转换
{
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;//清除ENC标志位
}
/*************************************************
 * 函  数  名:ADC14_convert_start
 * 功       能:开始一次ADC14转换
 * 参       数:无
 * 注意事项:无
 *************************************************/
void ADC14_convert_start()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;//设置SC标志位
}
/*************************************************
 * 函  数  名:ADC14_convert_end
 * 功       能:结束一次ADC14转换
 * 参       数:无
 * 注意事项:无
 *************************************************/
void ADC14_convert_end()
{
    ADC14->CTL0 &= ~ADC14_CTL0_SC;//清除SC标志位
}
/*************************************************
 * 函  数  名:ADC14_start
 * 功       能:对指定通道进行一次采样和转换
 * 参       数:ADC14_CHA:ADC14可选通道，已在exinADC.h文件
 *                    中枚举
 * 注意事项:无
 *************************************************/
void ADC14_start(ADC14_CHA_eunm ADC14_CHA)//ADC14开始一次转换
{
    ADC14_convert_disable();//禁能ADC14
    ADC14_convert_end();
    ADC14->MCTL[0] &= 0x00;//清零MCTL控制器
    switch(ADC14_CHA)
    {
           case(ADC_CH0): ADC14->MCTL[0] = ADC14_MCTLN_INCH_0|ADC14_MCTLN_EOS;  break;//P5.5 MEM0存储A0
           case(ADC_CH1): ADC14->MCTL[0] = ADC14_MCTLN_INCH_1|ADC14_MCTLN_EOS;  break;//P5.4 MEM0存储A1
           case(ADC_CH2): ADC14->MCTL[0] = ADC14_MCTLN_INCH_2|ADC14_MCTLN_EOS;  break;//P5.3 MEM0存储A2
           case(ADC_CH3): ADC14->MCTL[0] = ADC14_MCTLN_INCH_3|ADC14_MCTLN_EOS;  break;//P5.2 MEM0存储A3
           case(ADC_CH4): ADC14->MCTL[0] = ADC14_MCTLN_INCH_4|ADC14_MCTLN_EOS;  break;//P5.1 MEM0存储A4
           case(ADC_CH5): ADC14->MCTL[0] = ADC14_MCTLN_INCH_5|ADC14_MCTLN_EOS;  break;//P5.0 MEM0存储A5
           case(ADC_CH6): ADC14->MCTL[0] = ADC14_MCTLN_INCH_6|ADC14_MCTLN_EOS;  break;//P4.7 MEM0存储A6
           case(ADC_CH7): ADC14->MCTL[0] = ADC14_MCTLN_INCH_7|ADC14_MCTLN_EOS;  break;//P4.6 MEM0存储A7
           case(ADC_CH8): ADC14->MCTL[0] = ADC14_MCTLN_INCH_8|ADC14_MCTLN_EOS;  break;//P4.5 MEM0存储A8
           default:;
    }
    ADC14_convert_enable();//使能ADC14转换
    ADC14_convert_start();//开始一次转换
}
/*************************************************
 * 函  数  名:ADC14_read_data
 * 功       能:对指定通道进行一次转换后数据读取
 * 参       数:ADC14_CHA:ADC14可选通道，已在exinADC.h文件
 *                    中枚举
 * 注意事项:必须先通过ADC14_init函数对指定通道和ADC14进
 *          行初始化后，才能直接调用该函数读取AD转换值
 *************************************************/
int ADC14_read_data(ADC14_CHA_eunm ADC14_CHA)
{
    int ADC14_result=0;
    int PIN_CHEC = 0;
    switch(ADC14_CHA)//检测该口是否用于ADC通道
    {
           case(ADC_CH0):
                         if(((P5->SEL0 & BIT5)==BIT5)&&((P5->SEL1 & BIT5)==BIT5)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.5
           case(ADC_CH1):
                         if(((P5->SEL0 & BIT4)==BIT4)&&((P5->SEL1 & BIT4)==BIT4)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.5//P5.4
           case(ADC_CH2):
                         if(((P5->SEL0 & BIT3)==BIT3)&&((P5->SEL1 & BIT3)==BIT3)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.3
           case(ADC_CH3):
                         if(((P5->SEL0 & BIT2)==BIT2)&&((P5->SEL1 & BIT2)==BIT2)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.2
           case(ADC_CH4):
                         if(((P5->SEL0 & BIT1)==BIT1)&&((P5->SEL1 & BIT1)==BIT1)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.1
           case(ADC_CH5):
                         if(((P5->SEL0 & BIT0)==BIT0)&&((P5->SEL1 & BIT0)==BIT0)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.0
           case(ADC_CH6):
                         if(((P4->SEL0 & BIT7)==BIT7)&&((P4->SEL1 & BIT7)==BIT7)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.7
           case(ADC_CH7):
                         if(((P4->SEL0 & BIT6)==BIT6)&&((P4->SEL1 & BIT6)==BIT6)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.6
           case(ADC_CH8):
                         if(((P4->SEL0 & BIT5)==BIT5)&&((P4->SEL1 & BIT5)==BIT5)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.5
           default:PIN_CHEC = 0;
    }
    if(PIN_CHEC)
    {
        ADC14_start(ADC14_CHA);//开始一次AD转换
        while(!ADC14_STRUCT.CONVERT_SUCCESS_FLAG);
        ADC14_result =ADC14_STRUCT.convert_data;
        ADC14_STRUCT.CONVERT_SUCCESS_FLAG = 0;//清零完成标志位
    }
    else
        ADC14_result = 0;
    return ADC14_result;
}
/*************************************************
 * 函  数  名:ADC14_CHA_sel
 * 功       能:ADC通道端口选择，对指定的通道引脚进行初始化
 * 参       数:ADC14_CHA:ADC14可选通道，已在exinADC.h文件
 *                    中枚举
 * 注意事项:无
 *************************************************/
void ADC14_CHA_sel(ADC14_CHA_eunm ADC14_CHA)//ADC通道端口选择
{
        switch(ADC14_CHA)
        {
            case(ADC_CH0): P5->SEL1 |= BIT5;P5->SEL0 |= BIT5;  break;//P5.5
            case(ADC_CH1): P5->SEL1 |= BIT4;P5->SEL0 |= BIT4;  break;//P5.4
            case(ADC_CH2): P5->SEL1 |= BIT3;P5->SEL0 |= BIT3;  break;//P5.3
            case(ADC_CH3): P5->SEL1 |= BIT2;P5->SEL0 |= BIT2;  break;//P5.2
            case(ADC_CH4): P5->SEL1 |= BIT1;P5->SEL0 |= BIT1;  break;//P5.1
            case(ADC_CH5): P5->SEL1 |= BIT0;P5->SEL0 |= BIT0;  break;//P5.0
            case(ADC_CH6): P4->SEL1 |= BIT7;P4->SEL0 |= BIT7;  break;//P4.7
            case(ADC_CH7): P4->SEL1 |= BIT6;P4->SEL0 |= BIT6;  break;//P4.6
            case(ADC_CH8): P4->SEL1 |= BIT5;P4->SEL0 |= BIT5;  break;//P4.5
            default:;
        }
}

/*************************************************
 * 函  数  名:ADC14_CLK_sel
 * 功       能:ADC14时钟配置
 * 参       数:ADC14_CLK:ADC14可选时钟，已在exinADC.h文件
 *                    中枚举
 *          ADC14_DIV:分频系数，已在exinADC.h文件中枚
 *                    举
 * 注意事项:ADC14的时钟频率为ADC14_CLK / ADC14_DIV
 *          这决定了ADC14的采样频率
 *          ADC14的采样频率可通过以下公式粗略计算
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          其中tsample = 4 tphase = tdmove =1
 *          tconvert由分辨率决定:
 *          当 分辨率为 8bits(256) 时 tconvert = 9
 *          当 分辨率为 10bits(1024) 时 tconvert = 11
 *          当 分辨率为 12bits(4096) 时 tconvert = 14
 *          当 分辨率为 14bits(16384) 时 tconvert = 16
 *************************************************/
void ADC14_CLK_sel(ADC14_CLK_eunm ADC14_CLK,ADC14_DIV_eunm ADC14_DIV)//选择采样与转换时钟 默认选择 MCLK
{
    switch(ADC14_CLK)
    {
        case(ADC_MODCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__MODCLK; break;//MODCLK
        case(ADC_SYSCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__SYSCLK; break;//SYSCLK
        case(ADC_ACLK):   ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__ACLK;   break;//ACLK
        case(ADC_MCLK):   ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__MCLK;   break;//MCLK
        case(ADC_SMCLK):  ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__SMCLK;  break;//SMCLK
        case(ADC_HSMCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__HSMCLK; break;//HSMCLK
        default:ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    }
    switch(ADC14_DIV)
    {
        case(ADC_DIV1): ADC14->CTL0 |= ADC14_CTL0_DIV_0; break;//1
        case(ADC_DIV2): ADC14->CTL0 |= ADC14_CTL0_DIV_1; break;//2
        case(ADC_DIV3): ADC14->CTL0 |= ADC14_CTL0_DIV_2; break;//3
        case(ADC_DIV4): ADC14->CTL0 |= ADC14_CTL0_DIV_3; break;//4
        case(ADC_DIV5): ADC14->CTL0 |= ADC14_CTL0_DIV_4; break;//5
        case(ADC_DIV6): ADC14->CTL0 |= ADC14_CTL0_DIV_5; break;//6
        case(ADC_DIV7): ADC14->CTL0 |= ADC14_CTL0_DIV_6; break;//7
        case(ADC_DIV8): ADC14->CTL0 |= ADC14_CTL0_DIV_7; break;//8
        default:;
    }
    ADC14->CTL0 |= ADC14_CTL0_MSC ;//PULSE模式且MSC=1
}
/*************************************************
 * 函  数  名:ADC14_PREC_sel
 * 功       能:ADC14分辨率设置
 * 参       数:ADC_PREC:ADC14可选分辨率，已在exinADC.h文件
 *                    中枚举
 * 注意事项:无
 *************************************************/
void ADC14_PREC_sel(ADC14_PREC_eunm ADC_PREC)//选择分辨率
{
    ADC14_convert_disable();//禁能ADC14
    ADC14_convert_end();
    switch(ADC_PREC)
    {
        case(ADC14_BIT8):  ADC14->CTL1 = ADC14_CTL1_RES_0;break;//8BIT
        case(ADC14_BIT10): ADC14->CTL1 = ADC14_CTL1_RES_1;break;//10BIT
        case(ADC14_BIT12): ADC14->CTL1 = ADC14_CTL1_RES_2;break;//12BIT
        case(ADC14_BIT14): ADC14->CTL1 = ADC14_CTL1_RES_3;break;//14BIT
        default: ADC14->CTL1 = ADC14_CTL1_RES_0;break;//8BIT
    }
}
/*************************************************
 * 函  数  名:ADC14_init
 * 功       能:ADC14对指定通道及ADC14进行初始化,此函数将ADC14配置为单次转换模式
 * 参       数:
 *          ADC_PREC:ADC14可选分辨率，已在exinADC.h文件
 *                    中枚举
 *          ADC14_CHA:ADC14可选通道，已在exinADC.h文件
 *                    中枚举
 *          ADC14_CLK:ADC14可选时钟，已在exinADC.h文件
 *                    中枚举
 *          ADC14_DIV:分频系数，已在exinADC.h文件中枚
 *                    举
 * 注意事项:ADC14的采样频率可通过以下公式粗略计算
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          其中tsample = 4 tphase = tdmove =1
 *          tconvert由分辨率决定:
 *          当 分辨率为 8bits(256) 时 tconvert = 9
 *          当 分辨率为 10bits(1024) 时 tconvert = 11
 *          当 分辨率为 12bits(4096) 时 tconvert = 14
 *          当 分辨率为 14bits(16384) 时 tconvert = 16
 *
 *          当调用此函数时，则默认单通道单次转换，此时实际采样频率要小于计算所得频率
 *************************************************/

void ADC14_init(ADC14_CHA_eunm  ADC14_CHA,
              ADC14_CLK_eunm  ADC14_CLK,
              ADC14_DIV_eunm  ADC14_DIV,
              ADC14_PREC_eunm ADC_PREC)
{
    //对ADC14结构体进行初始化
    ADC14_STRUCT.CONVERT_SUCCESS_FLAG=0;//清零采集完成标志位
    ADC14_STRUCT.WORK_MOD=ONECE_CVRT_MOD;//单次转换模式
    ADC14_STRUCT.IRQ_FLG=ADC14_IER0_IE0;//存储中断源
    //_____________________
    ADC14_CHA_sel(ADC14_CHA);                //初始化ADC14通道
    __enable_interrupt();                    //打开总中断
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);//初始化NVIC中断
    ADC14_CLK_sel(ADC14_CLK ,ADC14_DIV);     //设置ADC14时钟
    ADC14_PREC_sel(ADC_PREC);                //选择分辨率
    ADC14->IER0 |= ADC14_IER0_IE0;           //使能ADC中断
}
/******************************************************************以下为重复采样模式下相关函数*********************************************************/
/*************************************************
 * 函  数  名:ADC14_CHAEND_set
 * 功       能:ADC14重复采样模式下的通道引脚初始化
 * 参       数:ADC14_CHA:截至通道设置，已在exinADC.h文件
 *                    中枚举
 * 注意事项:将依次对A0~ADC14_CHA的通道引脚进行初始化
 *          如 ADC14_CHAEND_set(ADC14_CH4)
 *          则对A0~A4的通道引脚进行初始化
 *************************************************/
void ADC14_CHAEND_set(ADC14_CHA_eunm  ADC14_CHA)//设置ADC14结束采样的通道
{
    switch(ADC14_CHA)
   {
      case(ADC_CH7): P4->SEL1 |= BIT6;P4->SEL0 |= BIT6;  //P4.6
      case(ADC_CH6): P4->SEL1 |= BIT7;P4->SEL0 |= BIT7;  //P4.7
      case(ADC_CH5): P5->SEL1 |= BIT0;P5->SEL0 |= BIT0;  //5.0
      case(ADC_CH4): P5->SEL1 |= BIT1;P5->SEL0 |= BIT1;  //P5.1
      case(ADC_CH3): P5->SEL1 |= BIT2;P5->SEL0 |= BIT2;  //P5.2
      case(ADC_CH2): P5->SEL1 |= BIT3;P5->SEL0 |= BIT3;  //P5.3
      case(ADC_CH1): P5->SEL1 |= BIT4;P5->SEL0 |= BIT4;  //P5.4
      case(ADC_CH0): P5->SEL1 |= BIT5;P5->SEL0 |= BIT5;  //P5.5
      default:;
   }
}
/*************************************************
 * 函  数  名:ADC14_MEM_set
 * 功       能:ADC14重复采样模式下各通道转化后数据存储配置
 * 参       数:ADC14_CHA:截至通道设置，已在exinADC.h文件
 *                    中枚举
 * 注意事项:将依次对A0~ADC14_CHA的通道转换数据与MEM[0]~MEM[ADC14_CHA]进行绑定
 *          如 ADC14_MEM_set(ADC14_CH4)
 *          则MEM0寄存A0转换数据
 *            MEM1寄存A1转换数据
 *            MEM2寄存A2转换数据
 *            MEM3寄存A3转换数据
 *            MEM4寄存A4转换数据
 *************************************************/
void ADC14_MEM_set(ADC14_CHA_eunm  ADC14_CHA)
{
    switch(ADC14_CHA)//分配各通道转换数据存储的寄存器
   {
       case(ADC_CH7): ADC14->MCTL[7] = ADC14_MCTLN_INCH_7 ;//MEM7=A7
       case(ADC_CH6): ADC14->MCTL[6] = ADC14_MCTLN_INCH_6 ;//MEM6=A6
       case(ADC_CH5): ADC14->MCTL[5] = ADC14_MCTLN_INCH_5 ;//MEM5=A5
       case(ADC_CH4): ADC14->MCTL[4] = ADC14_MCTLN_INCH_4 ;//MEM4=A4
       case(ADC_CH3): ADC14->MCTL[3] = ADC14_MCTLN_INCH_3 ;//MEM3=A3
       case(ADC_CH2): ADC14->MCTL[2] = ADC14_MCTLN_INCH_2 ;//MEM2=A2
       case(ADC_CH1): ADC14->MCTL[1] = ADC14_MCTLN_INCH_1 ;//MEM6=A6
       case(ADC_CH0): ADC14->MCTL[0] = ADC14_MCTLN_INCH_0 ;//MEM6=A6
       default:;
   }
    switch(ADC14_CHA)//设置转换结束标志位
    {
           case(ADC_CH7): ADC14->MCTL[7] |= ADC14_MCTLN_EOS ;break;//MEM7=A7
           case(ADC_CH6): ADC14->MCTL[6] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           case(ADC_CH5): ADC14->MCTL[5] |= ADC14_MCTLN_EOS ;break;//MEM5=A5
           case(ADC_CH4): ADC14->MCTL[4] |= ADC14_MCTLN_EOS ;break;//MEM4=A4
           case(ADC_CH3): ADC14->MCTL[3] |= ADC14_MCTLN_EOS ;break;//MEM3=A3
           case(ADC_CH2): ADC14->MCTL[2] |= ADC14_MCTLN_EOS ;break;//MEM2=A2
           case(ADC_CH1): ADC14->MCTL[1] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           case(ADC_CH0): ADC14->MCTL[0] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           default:;
    }
}
/*************************************************
 * 函  数  名:ADC14_IRQFG_set
 * 功       能:ADC14重复采样模式下中断触发标志位设置
 * 参       数:ADC14_CHA:截至通道设置，已在exinADC.h文件
 *                    中枚举
 * 注意事项:将对ADC14的中断服务函数的中断触发标志位进行设置
 *          如 ADC14_IRQFG_set(ADC14_CH4)
 *          则中断源为ADC14_IER0_IE4，这表示在MEM4寄存器数据存储后再触发中断
 *************************************************/
void ADC14_IRQFG_set(ADC14_CHA_eunm  ADC14_CHA)
{
        switch(ADC14_CHA)//设置转换结束标志位
       {
              case(ADC_CH7): ADC14->IER0 = ADC14_IER0_IE7; break;//MEM7=A7
              case(ADC_CH6): ADC14->IER0 = ADC14_IER0_IE6; break;//MEM6=A6
              case(ADC_CH5): ADC14->IER0 = ADC14_IER0_IE5; break;//MEM5=A5
              case(ADC_CH4): ADC14->IER0 = ADC14_IER0_IE4; break;//MEM4=A4
              case(ADC_CH3): ADC14->IER0 = ADC14_IER0_IE3; break;//MEM3=A3
              case(ADC_CH2): ADC14->IER0 = ADC14_IER0_IE2; break;//MEM2=A2
              case(ADC_CH1): ADC14->IER0 = ADC14_IER0_IE1; break;//MEM6=A6
              case(ADC_CH0): ADC14->IER0 = ADC14_IER0_IE0; break;//MEM6=A6
              default:;
       }
        ADC14_STRUCT.IRQ_FLG=ADC14->IER0;//存储中断源
}
/*************************************************
 * 函  数  名:ADC14_repeatmod_init
 * 功       能:将ADC14配置为重复转换并设置ADC14的时钟与分辨率
 * 参       数:
 *          ADC_PREC:ADC14可选分辨率，已在exinADC.h文件
 *                    中枚举
 *          ADC14_CHA:重复采样模式下的截止通道，已在exinADC.h文件
 *                    中枚举
 *          ADC14_CLK:ADC14可选时钟，已在exinADC.h文件
 *                    中枚举
 *          ADC14_DIV:分频系数，已在exinADC.h文件中枚
 *                    举
 * 注意事项:将对A0~ADC14_CHA进行初始化，
 *          如ADC14_repeatmod_init(ADC_CH2,ADC_MCLK, ADC_DIV2,ADC_BIT12)
 *          则会对A0~A2进行初始化，且选择MCLK进行2分频作为时钟，其分辨率为4096
 *          ADC14的采样频率可通过以下公式粗略计算
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          其中tsample = 4 tphase = tdmove =1
 *          tconvert由分辨率决定:
 *          当 分辨率为 8bits(256) 时 tconvert = 9
 *          当 分辨率为 10bits(1024) 时 tconvert = 11
 *          当 分辨率为 12bits(4096) 时 tconvert = 14
 *          当 分辨率为 14bits(16384) 时 tconvert = 16
 *
 *          当调用此函数时，则默认单通道单次转换，此时实际采样频率要小于计算所得频率
 *************************************************/
void ADC14_repeatmod_init(ADC14_CHA_eunm  ADC14_CHA,
                          ADC14_CLK_eunm  ADC14_CLK,
                          ADC14_DIV_eunm  ADC14_DIV,
                          ADC14_PREC_eunm ADC_PREC)
{
    //对ADC14结构体进行初始化
    ADC14_STRUCT.CONVERT_SUCCESS_FLAG=0;//清零采集完成标志位
    ADC14_STRUCT.WORK_MOD=REPEAT_CVRT_MOD;//单次转换模式
    ADC14_STRUCT.ADC_CHEND=ADC14_CHA;//记录截至通道
    //_____________________
    ADC14_CHAEND_set(ADC14_CHA);//设置结束通道
    __enable_interrupt();//打开全局中断
    NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);//使能ADC14中断
    ADC14_CLK_sel(ADC14_CLK,ADC14_DIV);//进行ADC时钟初始化
    //将ADC14配置为顺序转换
    ADC14->CTL0 &=~ADC14_CTL0_SHT0_2;//定义采样周期数
    ADC14->CTL0 |=ADC14_CTL0_SHT0__128|ADC14_CTL0_CONSEQ_3;//顺序采样
    //设置分辨率
    ADC14_PREC_sel(ADC_PREC);
    //配置存储寄存器
    ADC14_MEM_set(ADC14_CHA);
    //配置中断标志位
    ADC14_IRQFG_set(ADC14_CHA);
    ADC14_convert_enable();//使能ADC14转换
}

/*************************************************
 * 函  数  名:ADC14_repeatmod_rec
 * 功       能:重复转换模式下，用于将转换后的数据打入ADC_STRUCT结构体中的repeat_convert_CH缓冲区
 * 参       数:BUF:数据接收缓冲区
 *          ADC14_CHA:重复转换模式下的截止通道
 * 注意事项:将数据打入ADC_STRUCT结构体中的repeat_convert_CH后,可以直接通过以下方式获取数据
 *          ADC_STRUCT.repeat_convert_CH[0]   A0数据
 *          ADC_STRUCT.repeat_convert_CH[1]   A1数据
*           ADC_STRUCT.repeat_convert_CH[2]   A2数据
*           ~~~~~
*           ADC_STRUCT.repeat_convert_CH[7]   A7数据
 *************************************************/
void ADC14_repeatmod_rec(int * BUF,uint8  ADC14_CHA)
{
    int i ;
    for(i=0;i<=ADC14_CHA;i++)
    {
        BUF[i] = ADC14->MEM[i];
    }
}
extern void ADC14_repeat_test();
/*************************************************
 * 函  数  名:ADC14_IRQHandler
 * 功       能:ADC14中断服务函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void ADC14_IRQHandler(void) {
     if(ADC14_STRUCT.WORK_MOD == ONECE_CVRT_MOD)//如果是单次模式
     {
         ADC14_STRUCT.convert_data = ADC14->MEM[0];//读取转换值
         ADC14_STRUCT.CONVERT_SUCCESS_FLAG = 1;//转换完成标志位置1
     }
     else  if (ADC14->IFGR0 & ADC14_STRUCT.IRQ_FLG
                 && ADC14_STRUCT.WORK_MOD == REPEAT_CVRT_MOD)//判断中断标志位，判断是否为重复转换模式
     {
         ADC14_repeatmod_rec(ADC14_STRUCT.repeat_convert_CH,ADC14_STRUCT.ADC_CHEND);//务必保留该函数
         /***********************以下添加用户的处理函数*********************/

         /***********************用户处理函数添加结束行*********************/
     }
     else
     {
         /***********************以下添加用户的处理函数*********************/

         /***********************用户处理函数添加结束行*********************/
     }
}
