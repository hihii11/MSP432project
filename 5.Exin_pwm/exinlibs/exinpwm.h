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
#ifndef _exinpwm_h
#define _exinpwm_h
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    pwm_CHA=0,//A通道
    pwm_CHB,//B通道
    pwm_CHC,//C通道
    pwm_CHD,//D通道
    pwm_CHE,//E通道
    pwm_CHF,//F通道
    //pwm_CHG//G通道
}PWMCH_enum;
extern void pwm_duty(PWMCH_enum CHI,int duty);
extern void pwm_init(PWMCH_enum CHI,int FRE,int duty);
extern void PWM_TEST();
extern void pwm_pin_init(PWMCH_enum CHI);
extern void pwm_period_set(PWMCH_enum CHI,uint16 FRE);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
