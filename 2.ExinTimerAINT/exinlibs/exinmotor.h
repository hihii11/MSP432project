/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2019��1��23��22:29:47
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
   int Error_now;//�������ֵ     e[k]
   int Error_pre;//ǰһ�����ֵ  e[k-1]
   int Error_pre2;//��ǰ�����ֵe[k-2]
} PID_IncTypeDef;

typedef enum{
    MOTOR_CHA=0,//Aͨ��
    MOTOR_CHB,//Bͨ��
    MOTOR_CHC,//Cͨ��
    MOTOR_CHD,//Dͨ��
}SMOTOR_enum;

extern void Motor_PWM_INIT(SMOTOR_enum CHI);
extern void Motor_DIR_PIN_INIT(SMOTOR_enum CHI);
extern void Motor_init(SMOTOR_enum CHI);
extern void Motor_pwm_duty(SMOTOR_enum CHI,char Dir,int duty);
extern void PID_SET(PID_IncTypeDef*PID,int t,uint16 p,uint16 i,uint16 d);
extern int PID_Inc( PID_IncTypeDef *PID, int ActualValue );
extern void MOTOR_TEST();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
