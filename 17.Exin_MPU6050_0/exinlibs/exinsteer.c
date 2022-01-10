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
#include "exinsteer.h"

/***********************************/
/* steer_pwm_init
 *
 * 舵机pwm
 *
 *
 *
 * 可选端口
 * 5.6(steer_CHA) 5.7(steer_CHB)
 *
 */
/**********************************/
void steer_pwm_init(STEERCH_enum CHI,int period,int duty)
{
    switch(CHI)
    {
        case(steer_CHA):
                    pwm_init(pwm_CHE,period,duty);
                    break;
        case(steer_CHB):
                    pwm_init(pwm_CHF,period,duty);
                    break;
    }
}
/***********************************/
/* steer_limit
 *
 * 舵机限幅
 *
 *
 */
/**********************************/
int steer_limit(STEERCH_enum CHI,int duty)
{
    if(CHI==steer_CHA)
    {
        if(duty>5100)
            return 5100;
        else if(duty<4190)
            return 4190;
        else
            return duty;
    }
    if(CHI==steer_CHB)
      {
          if(duty>5100)
              return 5100;
          if(duty<4190)
              return 4190;
          else
             return duty;
      }
    return 0;
}

/***********************************/
/* steer_pwm_duty
 *
 * 舵机占空比设置
 *
 *
 */
/**********************************/
void steer_pwm_duty(STEERCH_enum CHI,int duty)
{
    switch(CHI)
    {
    case(steer_CHA):pwm_duty(pwm_CHE,duty);break;
    case(steer_CHB):pwm_duty(pwm_CHF,duty);break;
    }
}
