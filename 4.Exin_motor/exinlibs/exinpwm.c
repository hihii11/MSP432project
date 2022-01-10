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


/*************************************************
 * 函  数  名:pwm_pin_init
 * 功       能:PWM引脚初始化
 * 参       数:CHI:PWM可选通道
 * 注意事项:
PWM_CHA:P2.6
PWM_CHB:P2.7
PWM_CHC:P2.5
PWM_CHD:P2.4
PWM_CHE:P5.6
PWM_CHB:P5.7
 *************************************************/
void pwm_pin_init(PWMCH_enum CHI)
{
    switch(CHI)
    {
        case( pwm_CHA):P2->DIR |= BIT6;P2->SEL0 |= BIT6 ;break;
        case( pwm_CHB):P2->DIR |= BIT7;P2->SEL0 |= BIT7 ;break;
        case( pwm_CHC):P2->DIR |= BIT5;P2->SEL0 |= BIT5 ;break;
        case( pwm_CHD):P2->DIR |= BIT4;P2->SEL0 |= BIT4 ;break;
        case( pwm_CHE):P5->DIR |= BIT6;P5->SEL0 |= BIT6 ;break;
        case( pwm_CHF):P5->DIR |= BIT7;P5->SEL0 |= BIT7 ;break;
    }
}
/*************************************************
 * 函  数  名:pwm_pin_init
 * 功       能:PWM引脚初始化
 * 参       数:CHI:PWM可选通道
 *          FRE:频率 HZ
 * 注意事项:
 *************************************************/
void pwm_period_set(PWMCH_enum CHI,uint16 FRE)
{
    switch(CHI)
    {
           case( pwm_CHA):;
           case( pwm_CHB):;
           case( pwm_CHC):;
           case( pwm_CHD):FRE=SMCLK_FRE/(float)(FRE);TimerA_CCRVAL_set(TIMERA_A0,TIMERA_CCR0,FRE);break;
           case( pwm_CHE):;
           case( pwm_CHF):FRE=SMCLK_FRE/8/(float)(FRE);TimerA_CCRVAL_set(TIMERA_A2,TIMERA_CCR0,FRE);break;
           default:;
    }
}
/*************************************************
 * 函  数  名:pwm_init
 * 功       能:PWM初始化
 * 参       数:CHI:PWM可选通道
 *          FRE:频率 HZ
 *          duty:占空比调整
 * 注意事项:
 * duty范围为: 0~(SMCLK_FRE/FRE)-1
 *************************************************/
void pwm_init(PWMCH_enum CHI,int FRE,int duty)
{
    pwm_pin_init(CHI);
    pwm_period_set(CHI,FRE);
    switch(CHI)
    {
           case( pwm_CHA):;
           case( pwm_CHB):;
           case( pwm_CHC):;
           case( pwm_CHD):TimerA_CLK_set(TIMERA_A0,TIMERA_SMCLK,TIMERA_DIV1,TIMERA_DIV1);TimerA_MOD_sel(TIMERA_A0,UP);break;
           case( pwm_CHE):;
           case( pwm_CHF):TimerA_CLK_set(TIMERA_A2,TIMERA_SMCLK,TIMERA_DIV8,TIMERA_DIV1);TimerA_MOD_sel(TIMERA_A2,UP);break;
           default:;
    }
    switch(CHI)
    {
           case( pwm_CHA):CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR3,Reset_set);break;
           case( pwm_CHB):CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR4,Reset_set);break;
           case( pwm_CHC):CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR2,Reset_set);break;
           case( pwm_CHD):CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A0,TIMERA_CCR1,Reset_set);break;
           case( pwm_CHE):CCRn_MOD_sel(TIMERA_A2,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A2,TIMERA_CCR1,Reset_set);break;
           case( pwm_CHF):CCRn_MOD_sel(TIMERA_A2,TIMERA_CCR0,Reset_set);CCRn_MOD_sel(TIMERA_A2,TIMERA_CCR2,Reset_set);break;
           default:;
    }
    pwm_duty(CHI,duty);
}
/***********************************/
/*
 * 设置pwm占空比
 * 占空比范围0~TA0CCR0(0~基准计数寄存器设定值)
 */
/**********************************/
void pwm_duty(PWMCH_enum CHI,int duty)
{
    if(duty == 0)
    {
        duty=1;
    }
    switch(CHI)
       {
       case( pwm_CHA):TimerA_CCRVAL_set(TIMERA_A0,TIMERA_CCR3, duty-1);break;
       case( pwm_CHB):TimerA_CCRVAL_set(TIMERA_A0,TIMERA_CCR4, duty-1);break;
       case( pwm_CHC):TimerA_CCRVAL_set(TIMERA_A0,TIMERA_CCR2, duty-1);break;
       case( pwm_CHD):TimerA_CCRVAL_set(TIMERA_A0,TIMERA_CCR1, duty-1);break;
       case( pwm_CHE):TimerA_CCRVAL_set(TIMERA_A2,TIMERA_CCR1, duty-1);break;
       case( pwm_CHF):TimerA_CCRVAL_set(TIMERA_A2,TIMERA_CCR2, duty-1);break;
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
