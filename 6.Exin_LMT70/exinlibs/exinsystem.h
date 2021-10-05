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
#ifndef _exinsystem_h
#define _exinsystem_h
#ifdef __cplusplus
extern "C"
{
#endif

#define s  2
#define ms 1
#define us 0
#define SYSTIC_CONFIGURE SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk
//选用MSK时钟源(DCO时钟 3MHZ) 允许Systic中断

#define CPU_F                               ((double)48000000)//CPU主频
#define F_Div                              CPU_F/1000/1000//分频系数
//#define delay_us(x)                       __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay_us(x)                      systic_delayus((int)x)
#define delay_ms(x)                      systic_delayms((int)x)


extern long int time;

extern void system_init(char EN);
extern void systic_start();
extern void systic_end();
extern int systic_read();
extern void systic_clr();
extern void set_clock_period();
extern void set_DCO_48MH();
extern void systic_delayus(int n);
extern void systic_delayms(int n);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
