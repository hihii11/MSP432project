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
#ifndef _exin_pit_h
#define _exin_pit_h
#ifdef __cplusplus
extern "C"
{
#endif
typedef enum{
    PIT_CHA,
    PIT_CHB,
    PIT_CHC,
    PIT_CHD,
}PIT_enum;//PWM(电机)双通道输出枚举A,B为双通道口,C为单通道

extern void  PIT_init(PIT_enum CHI,float time);

#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
