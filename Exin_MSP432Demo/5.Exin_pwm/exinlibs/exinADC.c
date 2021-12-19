/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include"headfile.h"
#include "exinADC.h"

volatile uint16_t A0results[THE_MAX_NUM_OF_ADC];
volatile uint16_t A1results[THE_MAX_NUM_OF_ADC];
volatile uint16_t A2results[THE_MAX_NUM_OF_ADC];
volatile uint16_t A3results[THE_MAX_NUM_OF_ADC];
char receive_success=0;
static uint8_t index;
/***********************************/
/* ADC_INIT
 *
 * ADC初始化
 *
 * 精度2^14 0~16384
 *
 * 可选端口
 * 5.5 5.4 5.3 5.2
 *
 *比较电压3.3V
 *
 *
 */
/**********************************/
void ADC_INIT()
{
    WDT_A->CTL = WDT_A_CTL_PW |
                 WDT_A_CTL_HOLD;

    // Configure GPIO
    P5->SEL1 |= BIT5 | BIT4 | BIT3 |BIT2;   // Enable A/D channel A0-A3
    P5->SEL0 |= BIT5 | BIT4 | BIT3 |BIT2;

    __enable_interrupt();
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);// Enable ADC interrupt in NVIC module

    // Turn on ADC14, extend sampling time to avoid overflow of results
    ADC14->CTL0 = ADC14_CTL0_ON |
                  ADC14_CTL0_MSC |
                  ADC14_CTL0_SHT0__192 |
                  ADC14_CTL0_SHP |
                  ADC14_CTL0_CONSEQ_3;

    ADC14->MCTL[0] = ADC14_MCTLN_INCH_0;    // ref+=AVcc, channel = A0
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_1;    // ref+=AVcc, channel = A1
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_2;    // ref+=AVcc, channel = A2
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_3|    // ref+=AVcc, channel = A3, end seq.
                     ADC14_MCTLN_EOS;

    ADC14->IER0 = ADC14_IER0_IE3;           // Enable ADC14IFG.3

    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR

        ADC14->CTL0 |= ADC14_CTL0_ENC |
                ADC14_CTL0_SC;

}

long int ADC_CA=0;
long int ADC_CB=0;
long int ADC_CC=0;
long int ADC_CD=0;
/*****************************
 * GET_ADC_VALUE
 * 获取ADC通道值
 * 可选通道已在exin.h中枚举
 ******************************/
long int GET_ADC_VALUE(ADC_CHA_eunm CHI)
{
    switch(CHI)
    {
        case(ADC_CHA):
                       return ADC_CA;break;
        case(ADC_CHB):
                       return ADC_CB;break;
        case(ADC_CHC):
                       return ADC_CC;break;
        case(ADC_CHD):
                       return ADC_CD;break;
    }
    return 0;
}


/*****************************
 * ADC_mean_filter
 * 可对ADC通道值均值滤波
 * 返回滤波后值
 * 可选通道已在exinADC.h中枚举
 ******************************/
int ii=0;

long int ADC_mean_filter(ADC_CHA_eunm CHI,unsigned int times)
{
    long int sum=0;
   for(ii=0;ii<times;ii++)
   {
       while(!receive_success);
       receive_success=0;
       sum+=GET_ADC_VALUE(CHI);
   }
   return sum/times;
}

int ADC_receive_count=0;

void ADC14_IRQHandler(void)
{
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG3)
    {
        ADC_receive_count++;
        A0results[index] = ADC14->MEM[0];   // Move A0 results, IFG is cleared
        A1results[index] = ADC14->MEM[1];   // Move A1 results, IFG is cleared
        A2results[index] = ADC14->MEM[2];   // Move A2 results, IFG is cleared
        A3results[index] = ADC14->MEM[3];   // Move A3 results, IFG is cleared
        index = (index + 1) & 0x7;          // Increment results index, modulo


        if(ADC_receive_count==8)
        {

            receive_success=1;
            ADC_receive_count=0;
            ADC_CA=(A0results[0]+A0results[1]+A0results[2]+A0results[3]+A0results[4]+A0results[5]+A0results[6]+A0results[7])/8;
            ADC_CB=(A1results[0]+A1results[1]+A1results[2]+A1results[3]+A1results[4]+A1results[5]+A1results[6]+A1results[7])/8;//p5.4
            ADC_CC=(A2results[0]+A2results[1]+A2results[2]+A2results[3]+A2results[4]+A2results[5]+A2results[6]+A2results[7])/8;
            ADC_CD=(A3results[0]+A3results[1]+A3results[2]+A3results[3]+A3results[4]+A3results[5]+A3results[6]+A3results[7])/8;


        }
        __no_operation();                   // Set Breakpoint1 here
    }
}
/*
void ADC14_IRQHandler(void)
{
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG3)
    {
        A0results[index] = ADC14->MEM[0];   // Move A0 results, IFG is cleared
        A1results[index] = ADC14->MEM[1];   // Move A1 results, IFG is cleared
        A2results[index] = ADC14->MEM[2];   // Move A2 results, IFG is cleared
        A3results[index] = ADC14->MEM[3];   // Move A3 results, IFG is cleared
        index = (index + 1) & 0x7;          // Increment results index, modulo
        __no_operation();                   // Set Breakpoint1 here
    }
}*/
long int ad_get;
void OLED_showADC()
{
    OLED_ShowString(0, 0, "ADC_CHA:");

    OLED_ShowNum(96, 0, ad_get, 5, 12);
    OLED_ShowNum(96, 2, ADC_CA, 5, 12);
    OLED_ShowNum(96, 3, ADC_CC, 5, 12);
    OLED_ShowNum(96, 4, ADC_CD, 5, 12);

}
void ADC_TEST()
{
    system_init(0);
    ADC_INIT();
    OLED_Init();
    OLED_showADC();
    while(1)
    {
        ad_get=ADC_mean_filter(ADC_CHA,12);
        OLED_showADC();
    }
}
