/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月21日16:46:33
-------------------------------------------------------------------------------------------------------*/

#include "headfile.h"
#include "exinTimerAINT.h"

/*************************************************
 * 函  数  名:period_cvert
 * 功       能:将对应的周期转换为需要写入CCR寄存器的数值
 * 参       数:TIMERAn:可选TimerA模块，在exinuart.h中列出
 *          period:周期，单位ms
 * 注意事项:无
 *************************************************/
int period_cvert(TIMERA_enum TIMERAn,int period)
{
    switch(TIMERAn)
    {
        case(TIMERA_A0):return (int)((period/1000.0)*TimerA0_BaseCLK);
        case(TIMERA_A1):return (int)((period/1000.0)*TimerA1_BaseCLK);
        case(TIMERA_A2):return (int)((period/1000.0)*TimerA2_BaseCLK);
        case(TIMERA_A3):return (int)((period/1000.0)*TimerA3_BaseCLK);
        default:return 0;
    }
}

/*************************************************
 * 函  数  名:TimerA_CCR0INT_init
 * 功       能:调用此函数将TimerA设置为UP模式，并允许CCR0中断
 * 参       数:TIMERAn:可选TimerA模块，在exinuart.h中列出
 * 注意事项:调用此函数后，可以使用的中断函数为
 *          TA0_0_IRQHandler  TA1_0_IRQHandler
 *          TA2_0_IRQHandler  TA3_0_IRQHandler
 *************************************************/
void TimerA_CCR0INT_init(TIMERA_enum TIMERAn , int period)
{
    TimerA_CLK_set(TIMERAn,TIMERA_ACLK,TIMERA_DIV1,TIMERA_DIV1);//选择ACLK作为时钟，并且分频为ID=1 IDEX=1  32768hz
    TimerA_MOD_sel(TIMERAn,UP);//选择TimerA工作模式为UP 即计数到CCR0结束计数
    period = period_cvert(TIMERAn,period);//计算写入CCR0的数值
    //以下为中断配置
    //1)设置TImerA CCR0的NVIC中断使能
    TimerA_NVIC_IRQ_set(TIMERAn,TIMERA_TA0);
    //2)允许来自CCR0的中断请求
    TimerA_enable_CCRnIRQ(TIMERAn,TIMERA_CCR0);
    //3)向CCR0写入比较值
    TimerA_CCRVAL_set(TIMERAn,TIMERA_CCR0,period);
    //4)开启总中断
    __enable_interrupt();
}

/*************************************************
 * 函  数  名:TimerA_CCRnINT_init
 * 功       能:调用此函数将TimerA设置为CONTIUNOUS模式，并允许CCRn中断
 * 参       数:TIMERAn:可选TimerA模块，在exinuart.h中列出
 *          TIMERA_CCR:可选的CCR，在exinuart.h中列出
 *          period:定时器中断周期，单位ms
 * 注意事项:调用此函数后，可以使用的中断函数为
 *          TA0_N_IRQHandler  TA1_N_IRQHandler
 *          TA2_N_IRQHandler  TA3_N_IRQHandler
 *          （isr.c）中查看，目前只写了TA3_N_IRQHandler中的几个CCR的中断处理其他TIMERA可以根据自己需要编写
 *************************************************/
uint16 CCRn_period_val[4][7] = {0};//用于存储周期参数设置
void TimerA_CCRnINT_init(TIMERA_enum TIMERAn , TIMERA_CCR_enum TIMERA_CCR,int period)
{
    TimerA_CLK_set(TIMERAn,TIMERA_ACLK,TIMERA_DIV1,TIMERA_DIV1);//选择ACLK作为时钟，并且分频为ID=1 IDEX=1  32768hz
    TimerA_MOD_sel(TIMERAn,CONTINUOUS);//选择TimerA工作模式为CONTINUOUS 即计数到0xFFFFh 再清零
    period = period_cvert(TIMERAn,period);
    CCRn_period_val[TIMERAn][TIMERA_CCR]=period;
    //以下为中断配置
   //1)设置TImerA CCRn的NVIC中断使能
   TimerA_NVIC_IRQ_set(TIMERAn,TIMERA_TAN);
   //2)允许来自CCRn的中断请求
   TimerA_enable_CCRnIRQ(TIMERAn,TIMERA_CCR);
   //3)向CCRn写入初值值
   TimerA_CCRVAL_set(TIMERAn,TIMERA_CCR,period);
   //4)开启总中断
   __enable_interrupt();
}
