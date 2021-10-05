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
#include "headfile.h"
#include "exin_pit.h"

int set_time_A1;
int set_time_A2;
int set_time_A3;
int set_time_A4;
/***********************************/
/* PIT_init
 *
 * 定时器中断初始化 time单位为ms
 *
 * 可选定时器通道
 * PIT_CHA
 * PIT_CHB
 * PIT_CHC
 * PIT_CHD
 *
 * 中断函数在einisr.c中注册
 */
/**********************************/
void PIT_init(PIT_enum CHI,float time)
{
    //分频ACLK/CCR[n]
    __enable_interrupt();
    time=time/1000*32768;//ACLK时钟
    switch(CHI)
    {
        case(PIT_CHA):
                   NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
                   TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;//中断使能
                   TIMER_A0->CCR[0] = time;//配置比较寄存器
                   TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHB):
                   NVIC->ISER[0] = 1 << ((TA1_0_IRQn) & 31);
                   TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A1->CCTL[0] = TIMER_A_CCTLN_CCIE;//中断使能
                   TIMER_A1->CCR[0] = time;//配置比较寄存器
                   TIMER_A1->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHC):
                   NVIC->ISER[0] = 1 << ((TA2_0_IRQn) & 31);
                   TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A2->CCTL[0] = TIMER_A_CCTLN_CCIE;//中断使能
                   TIMER_A2->CCR[0] = time;//配置比较寄存器
                   TIMER_A2->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHD):
                    NVIC->ISER[0] = 1 << ((TA3_0_IRQn) & 31);
                    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                    TIMER_A3->CCTL[0] = TIMER_A_CCTLN_CCIE;//中断使能
                    TIMER_A3->CCR[0] = time;//配置比较寄存器
                    TIMER_A3->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                    TIMER_A_CTL_MC__UP;
                    break;
    }

}

