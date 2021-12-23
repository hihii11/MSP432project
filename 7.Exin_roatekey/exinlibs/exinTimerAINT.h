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

#ifndef _EXINTIMERAINT_H_
#define _EXINTIMERAINT_H_
#ifdef __cplusplus
extern "C"
{
#endif
//����ǰTimerAģ��ʱ��Ƶ��
#define TimerA0_BaseCLK  32768.0
#define TimerA1_BaseCLK  32768.0
#define TimerA2_BaseCLK  32768.0
#define TimerA3_BaseCLK  32768.0

extern uint16 CCRn_period_val[4][7];
extern int period_cvert(TIMERA_enum TIMERAn,int period);
extern void TimerA_CCR0INT_init(TIMERA_enum TIMERAn , int period);
extern void TimerA_CCRnINT_init(TIMERA_enum TIMERAn , TIMERA_CCR_enum TIMERA_CCR,int period);
#ifdef __cplusplus
}
#endif

#endif
