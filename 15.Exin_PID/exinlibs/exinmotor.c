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
#include "headfile.h"
#include "exinmotor.h"
#define MOTOR_R 1
#define MOTOR_L 0

/*******************************
 *
 * pwmpƵ��
 *
 *���ռ�ձȼ��� (200/perod)*15000
 *
 *����Ĭ��period����Ϊ1000hz���������ռ�ձ�Ϊduty=3000
 *
 ****************************/
void Motor_PWM_INIT(SMOTOR_enum CHI)
{
    switch(CHI)
    {
    case(MOTOR_CHA):pwm_init(pwm_CHA,3500,0);break;//pwm Aͨ��
    case(MOTOR_CHB):pwm_init(pwm_CHB,3500,0);break;//pwm Bͨ����1000��1khz
    case(MOTOR_CHC):pwm_init(pwm_CHC,3500,0);break;//pwm Cͨ��
    case(MOTOR_CHD):pwm_init(pwm_CHD,3500,0);break;//pwm Dͨ��
    }
}

/*******************************
 * Motor_DIR_PIN_INIT
 * ����������ų�ʼ��
 *
 *
 *
 ****************************/
void Motor_DIR_PIN_INIT(SMOTOR_enum CHI)
{
    switch(CHI)
    {
    case(MOTOR_CHA):gpio_init(GPIO_PORT_P8,GPIO_PIN6,GPO,0);break;//��������
    case(MOTOR_CHB):gpio_init(GPIO_PORT_P8,GPIO_PIN7,GPO,1);break;//��������
    case(MOTOR_CHC):gpio_init(GPIO_PORT_P4,GPIO_PIN1,GPO,1);break;//��������
    case(MOTOR_CHD):gpio_init(GPIO_PORT_P3,GPIO_PIN6,GPO,0);break;//��������
    }
}

/*******************************
 * Motor_init
 * �����ʼ�������������ų�ʼ��
 *��Ӧ�ĸ�ͨ�� ��·pwm
 *MOTOR_CHA pwm:p2.6 Dir:p3.6
 *MOTOR_CHB pwm:p2.7 Dir:p4.1
 *MOTOR_CHC pwm:p2.5 Dir:p8.6
 *MOTOR_CHD pwm:p2.4 Dir:p8.7
 ****************************/
void Motor_init(SMOTOR_enum CHI)
{

    Motor_DIR_PIN_INIT(CHI);
    Motor_PWM_INIT(CHI);
}

/*******************************
 * Motor_pwm_duty
 * ���õ��pwmռ�ձ���������
 *
 * DirΪ��������
 *
 ****************************/
void Motor_pwm_duty(SMOTOR_enum CHI,char Dir,int duty)//Dir=0ǰ��//Dir=1����
{
    if(duty> TIMER_A0->CCR[0])
    {
        duty=TIMER_A0->CCR[0];
    }
    if(duty<0)
    {
        duty=0;
    }

    switch(CHI)
    {
        case(MOTOR_CHA):
                pwm_duty(pwm_CHA,duty);
                if(Dir)//����
                    gpio_set(GPIO_PORT_P8,GPIO_PIN6,1);//������������
                else
                    gpio_set(GPIO_PORT_P8,GPIO_PIN6,0);//������������
                break;
        case(MOTOR_CHB):
                pwm_duty(pwm_CHB,duty);
                if(Dir)//����
                     gpio_set(GPIO_PORT_P8,GPIO_PIN7,1);//������������
                else
                     gpio_set(GPIO_PORT_P8,GPIO_PIN7,0);//������������
               break;
        case(MOTOR_CHC):
               pwm_duty(pwm_CHC,duty);
              if(Dir)//����
                     gpio_set(GPIO_PORT_P4,GPIO_PIN1,1);//������������
               else
                     gpio_set(GPIO_PORT_P4,GPIO_PIN1,0);//������������
               break;
        case(MOTOR_CHD):
                pwm_duty(pwm_CHD,duty);
                if(Dir)//����
                      gpio_set(GPIO_PORT_P3,GPIO_PIN6,1);//������������
                else
                      gpio_set(GPIO_PORT_P3,GPIO_PIN6,0);//������������
                 break;
    }
}


/*---------------------------------------------------------------
PID_SET
����PID��Ŀ����PID��ֵ
PID t p i d PIDΪ�Զ���ṹ����������
����ʾ��PID_SET(PID1,20,15,8,10)
----------------------------------------------------------------*/
void PID_SET(PID_IncTypeDef*PID,int t,uint16 p,uint16 i,uint16 d)
{
  PID->target=t;
  PID->P=p;
  PID->I=i;
  PID->D=d;
  PID->Error_now=0;
  PID->Error_pre=0;
  PID->Error_pre2=0;
}
/*---------------------------------------------------------------
PID_Inc
ʵ���ٶ�PIDɨ�����
PID���Զ������ͣ� ActualValue��ǰֵ
����PID���
����ʾ��PID_Inc��PID_left��Speedleft��Kp[e(k)-e(k-1)]+Kie(k)+Kd[e(k)-2e(k-1)+e(k-2)]
----------------------------------------------------------------*/
int PID_Inc( PID_IncTypeDef *PID, int ActualValue )
{
  int PIDInc=0;
  PID->Error_now = PID->target - ActualValue;//����e[k]
  PIDInc = (PID->P * (PID->Error_now - PID->Error_pre                  )) + //P��  Kp[e(k)-e(k-1)]
           (PID->I *  PID->Error_now                                    ) +//I��  Kie(k)
           (PID->D * (PID->Error_now - 2*PID->Error_pre+PID->Error_pre2));  //D��  Kd[e(k)-2e(k-1)+e(k-2)

  PID->Error_pre2 = PID->Error_pre;//����e[k-2]
  PID->Error_pre = PID->Error_now;//����e[k-1]

  return PIDInc;
}
/**������Ժ���**/
void MOTOR_TEST()
{
    system_init(0);
    Motor_init(MOTOR_CHC);
    Motor_init(MOTOR_CHD);
    Motor_pwm_duty(MOTOR_CHC,1,1000);
    Motor_pwm_duty(MOTOR_CHD,0,1000);
    while(1);
}
