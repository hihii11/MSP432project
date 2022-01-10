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
#ifndef _exinsteer_h
#define _exinsteer_h
#ifdef __cplusplus
extern "C"
{
#endif

#define steer_midA 100//舵机x,y平面中值
#define steer_midB 100//舵机y,z平面中值
typedef enum{
    steer_CHA=0,//A通道
    steer_CHB,//B通道
}STEERCH_enum;


extern void steer_pwm_init(STEERCH_enum CHI,int period,int duty);
extern void STEER_TEST();
extern void steer_pwm_duty(STEERCH_enum CHI,int duty);
extern int steer_limit(STEERCH_enum CHI,int duty);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
