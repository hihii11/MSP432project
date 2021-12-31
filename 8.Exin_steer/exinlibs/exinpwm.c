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
#include "exinpwm.h"

void pwm_clock_init()
{
    do
    {

          CS->CLRIFG |= CS_CLRIFG_CLR_DCOR_OPNIFG | CS_CLRIFG_CLR_HFXTIFG | CS_CLRIFG_CLR_LFXTIFG;
          SYSCTL->NMI_CTLSTAT &= ~ SYSCTL_NMI_CTLSTAT_CS_SRC;
    } while (SYSCTL->NMI_CTLSTAT & SYSCTL_NMI_CTLSTAT_CS_FLG);

          CS->KEY = 0;
}

/***********************************/
/*pwm可输出口p2.6 p2.7 p2.5 p2.4 p5.6 p5.7
  pwm_init()//通道在exinpwm.h文件中列出
 *
 *参数：CHI  PWM可选通道/在exinpwm.h中列出
 *period   周期 单位为hz
 *duty   初始化占空比
 *占空比最大值计算方式如下
 *
 *duty(max):3_000_000/period
 *如period为1000hz   则duty允许调整范围为0~3000
 *
/**********************************/
void pwm_init(PWMCH_enum CHI,int period,int duty)
{
    period=SMCLK_FRE/(float)(period);
    switch(CHI)
    {
    case( pwm_CHA):
         TA0CCR0 = period-1; // PWM周期T=512us
         P2->DIR |= BIT6;
         P2->SEL0 |= BIT6 ;
         pwm_clock_init();
         TIMER_A0->CCR[0] = period-1;
         TIMER_A0->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

         TIMER_A0->CCR[3] =  duty-1;
         TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;

         TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
         break;
    case( pwm_CHB):
          TA0CCR0 = period-1; // PWM周期T=512us
          P2->DIR |= BIT7;
          P2->SEL0 |= BIT7 ;
          pwm_clock_init();
          TIMER_A0->CCR[0] = period-1;
          TIMER_A0->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

          TIMER_A0->CCR[4] =  duty-1;
          TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

          TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
          break;
    case( pwm_CHC):
            TA0CCR0 = period-1; // PWM周期T=512us
            P2->DIR |= BIT5;
            P2->SEL0 |= BIT5 ;
            pwm_clock_init();
            TIMER_A0->CCR[0] = period-1;
            TIMER_A0->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

            TIMER_A0->CCR[2] =  duty-1;
            TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;

            TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
            break;
    case( pwm_CHD):
              TA0CCR0 = period-1; // PWM周期T=512us
              P2->DIR |= BIT4;
              P2->SEL0 |= BIT4;
              pwm_clock_init();
              TIMER_A0->CCR[0] = period-1;
              TIMER_A0->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

              TIMER_A0->CCR[1] =  duty-1;
              TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;

              TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
              break;
    case( pwm_CHE):
                  TA2CCR0 = period-1; // PWM周期T=512us
                  P5->DIR |= BIT6;
                  P5->SEL0 |= BIT6;
                  pwm_clock_init();
                  TIMER_A2->CCR[0] = period-1;
                  TIMER_A2->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

                  TIMER_A2->CCR[1] =  duty-1;
                  TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;

                  TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
                  break;
    case( pwm_CHF):
                    TA2CCR0 = period-1; // PWM周期T=512us
                    P5->DIR |= BIT7;
                    P5->SEL0 |= BIT7;
                    pwm_clock_init();
                    TIMER_A2->CCR[0] = period-1;
                    TIMER_A2->CCTL[0] = TIMER_A_CCTLN_OUTMOD_7;

                    TIMER_A2->CCR[2] =  duty-1;
                    TIMER_A2->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;

                    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//时钟1 比较输出
                    break;

    }


}
/***********************************/
/*
 * 设置pwm占空比
 * 占空比范围0~TA0CCR0(0~基准计数寄存器设定值)
 */
/**********************************/
void pwm_duty(PWMCH_enum CHI,int duty)
{
    switch(CHI)
       {
       case( pwm_CHA):TIMER_A0->CCR[3] =  duty-1;break;
       case( pwm_CHB):TIMER_A0->CCR[4] =  duty-1;break;
       case( pwm_CHC):TIMER_A0->CCR[2] =  duty-1;break;
       case( pwm_CHD):TIMER_A0->CCR[1] =  duty-1;break;
       case( pwm_CHE):TIMER_A2->CCR[1] =  duty-1;break;
       case( pwm_CHF):TIMER_A2->CCR[2] =  duty-1;break;
       }
}

int duty=0;
void PWM_TEST()
{
    system_init(0);
    pwm_init(pwm_CHA,1000,0);
    while(1)
    {
        duty+=100;
        if(duty>=1000)
            duty=0;
        delay_ms(200);
        pwm_duty(pwm_CHA,duty);

    }
}
