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
#include "exinisr.h"

extern char IRQ3_5flag;
extern char IRQ4_6flag;
extern char A_flag;
extern char B_flag;
extern uint8 dirf;
void PORT1_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P1->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P1->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P1->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P1->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P1->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P1->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P1->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P1->IFG &= ~IRQ_CLR;
}

void PORT2_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P2->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    else if(P2->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    else if(P2->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        encoder_B.dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        if(encoder_B.dir == 1)
            encoder_B.encoder++;
        else
            encoder_B.encoder--;

        /*添加程序*/
    }
    if(P2->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P2->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P2->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P2->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P2->IFG &= ~IRQ_CLR;
}

void PORT3_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P3->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P3->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P3->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P3->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P3->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        A_flag=1;
        B_flag=0;
        IRQ3_5flag=1;
    }
    if(P3->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P3->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P3->IFG &= ~IRQ_CLR;
}
void PORT4_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;

    if(P4->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P4->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P4->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P4->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        encoder_A.dir=gpio_get(GPIO_PORT_P4,GPIO_PIN5);
        if(encoder_A.dir == 1)
            encoder_A.encoder++;
        else
            encoder_A.encoder--;
    }
    if(P4->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P4->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        A_flag=0;
        B_flag=1;
        IRQ4_6flag=1;
    }
    if(P4->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P4->IFG &= ~IRQ_CLR;
}

void PORT5_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P5->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        encoder_D.dir=gpio_get(GPIO_PORT_P5,GPIO_PIN0);
        if(encoder_D.dir == 1)
            encoder_D.encoder++;
        else
            encoder_D.encoder--;
        /*添加程序*/
    }
    if(P5->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P5->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P5->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P5->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P5->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*添加程序*/
    }
    if(P5->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P5->IFG &= ~IRQ_CLR;
}

void PORT6_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P6->IFG & BIT0)
    {
        IRQ_CLR |= BIT0;
            /*添加程序*/
    }
    if(P6->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*添加程序*/
    }
    if(P6->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*添加程序*/
    }
    if(P6->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*添加程序*/
    }
    if(P6->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*添加程序*/
    }
    if(P6->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*添加程序*/
    }
    if(P6->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        encoder_C.dir=gpio_get(GPIO_PORT_P6,GPIO_PIN1);
        if(encoder_C.dir == 1)
            encoder_C.encoder++;
        else
            encoder_C.encoder--;
        /*添加程序*/
    }
    if(P6->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*添加程序*/
    }
    P6->IFG &= ~IRQ_CLR;
}


void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*添加程序*/
}

void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*添加程序*/
}
void TA2_0_IRQHandler(void) {
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    /*添加程序*/

}

extern void OLED_show();
void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    Encoder_clr(ENCODER_CHA);
    Encoder_clr(ENCODER_CHB);
}

void TA0_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA1_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA2_N_IRQHandler(void)
{
    /*添加程序*/
}

void TA3_N_IRQHandler(void)
{
    if((TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
          (TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIE))//判断CCR1中断是否使能
       {
           /***************将TA3_N用作定时器中断时这几行务必保留****************/
           TIMER_A3->CCTL[TIMERA_CCR0] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR1中断标志位
           TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR0,TIMER_A3->CCR[TIMERA_CCR0] + CCRn_period_val[TIMERA_A3][TIMERA_CCR0]);//更新CCR寄存器
           /***************将TA3_N用作定时器中断时这几行务必保留****************/


           /***********************以下添加用户的处理函数*********************/

           /***********************用户处理函数添加结束行*********************/
       }
    if((TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
       (TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIE))//判断CCR1中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR1] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR1中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR1,TIMER_A3->CCR[TIMERA_CCR1] + CCRn_period_val[TIMERA_A3][TIMERA_CCR1]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIE))//判断CCR2中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR2] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR2中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR2,TIMER_A3->CCR[TIMERA_CCR2] + CCRn_period_val[TIMERA_A3][TIMERA_CCR2]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIE))//判断CCR3中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR3] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR3中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR3,TIMER_A3->CCR[TIMERA_CCR3] + CCRn_period_val[TIMERA_A3][TIMERA_CCR3]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIFG)&&//判断中断标志位是否有效
            (TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIE))//判断CCR4中断是否使能
    {
        /***************将TA3_N用作定时器中断时这几行务必保留****************/
        TIMER_A3->CCTL[TIMERA_CCR4] &= ~TIMER_A_CCTLN_CCIFG;//清除CCR4中断标志位
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR4,TIMER_A3->CCR[TIMERA_CCR4] + CCRn_period_val[TIMERA_A3][TIMERA_CCR4]);//更新CCR寄存器
        /***************将TA3_N用作定时器中断时这几行务必保留****************/


        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
}
