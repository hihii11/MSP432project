/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��21��16:46:33
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
}TIMERA_enum;//��ʱ��ö��
typedef enum{
    STOP,
    UP,
    CONTINUOUS,
    UP_DOWN
}TIMERA_MOD_enum;//��ʱ��A����ģʽö��
typedef enum{
    TIMERA_TACLK,
    TIMERA_ACLK,
    TIMERA_SMCLK,
    TIMERA_INCLK,
    TIMERA_DEFAULTCLK
}TIMERA_CLK_enum;//��ʱ����ѡʱ��ö��

typedef enum{
    TIMERA_DIV1,
    TIMERA_DIV2,
    TIMERA_DIV4,
    TIMERA_DIV8,
    TIMERA_DEFAULTDIV
}TIMERA_DIV_enum;//��ʱ����Ƶϵ��ö��

typedef enum{
    TIMERA_CCR0,
    TIMERA_CCR1,
    TIMERA_CCR2,
    TIMERA_CCR3,
    TIMERA_CCR4
  //  TIMERA_CCR5,
  //  TIMERA_CCR6
}TIMERA_CCR_enum;//��ʱ���Ƚϲ���ʱ��ö��
typedef enum{
    TIMERA_TA0,
    TIMERA_TAN
}TIMERA_NVIC_enum;//��ʱ��A�Ӽ��ж�ö��
extern void TimerA_CLK_set(TIMERA_enum TIMER,TIMERA_CLK_enum TIMERA_CLK,TIMERA_DIV_enum TIMERA_DIV);
extern void TimerA_enable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR);
extern void TimerA_NVIC_IRQ_set(TIMERA_enum TIMER,TIMERA_NVIC_enum TIMERA_NVIC);
extern void TimerA_MOD_sel(TIMERA_enum TIMER,TIMERA_MOD_enum TIMERA_MODE);
extern void TimerA_CCRVAL_set(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR,uint16 val);

#ifdef __cplusplus
}
#endif

#endif
