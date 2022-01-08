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
#ifndef _exinTimerA_h
#define _exinTimerA_h
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    TIMERA_A0,
    TIMERA_A1,
    TIMERA_A2,
    TIMERA_A3
}TIMERA_enum;//定时器枚举
typedef enum{
    STOP,
    UP,
    CONTINUOUS,
    UP_DOWN
}TIMERA_MOD_enum;//定时器A工作模式枚举
typedef enum{
    TIMERA_TACLK,
    TIMERA_ACLK,
    TIMERA_SMCLK,
    TIMERA_INCLK,
    TIMERA_DEFAULTCLK
}TIMERA_CLK_enum;//定时器可选时钟枚举

typedef enum{
    TIMERA_DIV0,
    TIMERA_DIV1,
    TIMERA_DIV2,
    TIMERA_DIV3,
    TIMERA_DIV4,
    TIMERA_DIV5,
    TIMERA_DIV6,
    TIMERA_DIV7,
    TIMERA_DIV8,
    TIMERA_DEFAULTDIV
}TIMERA_DIV_enum;//定时器分频系数枚举

typedef enum{
    TIMERA_CCR0,
    TIMERA_CCR1,
    TIMERA_CCR2,
    TIMERA_CCR3,
    TIMERA_CCR4,
    TIMERA_CCR5,
    TIMERA_CCR6
}TIMERA_CCR_enum;//定时器比较捕获定时器枚举

typedef enum{
    Set,
    Toggle_reset,
    Set_reset,
    Toggle,
    Reset,
    Toggle_set,
    Reset_set
}TIMERA_CCRMOD_enum;//定时器比较捕获定时器枚举

typedef enum{
    TIMERA_TA0,
    TIMERA_TAN
}TIMERA_NVIC_enum;//定时器A子级中断枚举
void TimerA_CLK_set(TIMERA_enum TIMER,TIMERA_CLK_enum TIMERA_CLK,TIMERA_DIV_enum TIMERA_IDDIV,TIMERA_DIV_enum TIMERA_IDEXDIV);
extern void TimerA_enable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR);
extern void TimerA_NVIC_IRQ_set(TIMERA_enum TIMER,TIMERA_NVIC_enum TIMERA_NVIC);
extern void TimerA_MOD_sel(TIMERA_enum TIMER,TIMERA_MOD_enum TIMERA_MODE);
extern void TimerA_CCRVAL_set(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR,uint16 val);
extern void CCRn_MOD_sel(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR,TIMERA_CCRMOD_enum MOD);

#ifdef __cplusplus
}
#endif

#endif
