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
#ifndef  _exinmotor_h
#define  _exinmotor_h

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
   int target;
   uint16 P;
   uint16 I;
   uint16 D;
   int Error_now;//本次误差值     e[k]
   int Error_pre;//前一次误差值  e[k-1]
   int Error_pre2;//再前次误差值e[k-2]
} PID_IncTypeDef;

typedef enum{
    MOTOR_CHA=0,//A通道
    MOTOR_CHB,//B通道
    MOTOR_CHC,//C通道
    MOTOR_CHD,//D通道
}SMOTOR_enum;

extern void Motor_PWM_INIT(SMOTOR_enum CHI,int fre);
extern void Motor_DIR_PIN_INIT(SMOTOR_enum CHI);
extern void Motor_init(SMOTOR_enum CHI,int fre);
extern void Motor_pwm_duty(SMOTOR_enum CHI,char Dir,int duty);
extern void PID_SET(PID_IncTypeDef*PID,int t,uint16 p,uint16 i,uint16 d);
extern int PID_Inc( PID_IncTypeDef *PID, int ActualValue );
extern void MOTOR_TEST();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
