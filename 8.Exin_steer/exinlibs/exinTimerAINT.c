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

#include "headfile.h"
#include "exinTimerAINT.h"

/*************************************************
 * ��  ��  ��:period_cvert
 * ��       ��:����Ӧ������ת��Ϊ��Ҫд��CCR�Ĵ�������ֵ
 * ��       ��:TIMERAn:��ѡTimerAģ�飬��exinuart.h���г�
 *          period:���ڣ���λms
 * ע������:��
 *************************************************/
int period_cvert(TIMERA_enum TIMERAn,int period)
{
    switch(TIMERAn)
    {
        case(TIMERA_A0):return (int)((period/1000.0)*TimerA0_BaseCLK);
        case(TIMERA_A1):return (int)((period/1000.0)*TimerA1_BaseCLK);
        case(TIMERA_A2):return (int)((period/1000.0)*TimerA2_BaseCLK);
        case(TIMERA_A3):return (int)((period/1000.0)*TimerA3_BaseCLK);
        default:return 0;
    }
}

/*************************************************
 * ��  ��  ��:TimerA_CCR0INT_init
 * ��       ��:���ô˺�����TimerA����ΪUPģʽ��������CCR0�ж�
 * ��       ��:TIMERAn:��ѡTimerAģ�飬��exinuart.h���г�
 * ע������:���ô˺����󣬿���ʹ�õ��жϺ���Ϊ
 *          TA0_0_IRQHandler  TA1_0_IRQHandler
 *          TA2_0_IRQHandler  TA3_0_IRQHandler
 *************************************************/
void TimerA_CCR0INT_init(TIMERA_enum TIMERAn , int period)
{
    TimerA_CLK_set(TIMERAn,TIMERA_ACLK,TIMERA_DIV1,TIMERA_DIV1);//ѡ��ACLK��Ϊʱ�ӣ����ҷ�ƵΪID=1 IDEX=1  32768hz
    TimerA_MOD_sel(TIMERAn,UP);//ѡ��TimerA����ģʽΪUP ��������CCR0��������
    period = period_cvert(TIMERAn,period);//����д��CCR0����ֵ
    //����Ϊ�ж�����
    //1)����TImerA CCR0��NVIC�ж�ʹ��
    TimerA_NVIC_IRQ_set(TIMERAn,TIMERA_TA0);
    //2)��������CCR0���ж�����
    TimerA_enable_CCRnIRQ(TIMERAn,TIMERA_CCR0);
    //3)��CCR0д��Ƚ�ֵ
    TimerA_CCRVAL_set(TIMERAn,TIMERA_CCR0,period);
    //4)�������ж�
    __enable_interrupt();
}

/*************************************************
 * ��  ��  ��:TimerA_CCRnINT_init
 * ��       ��:���ô˺�����TimerA����ΪCONTIUNOUSģʽ��������CCRn�ж�
 * ��       ��:TIMERAn:��ѡTimerAģ�飬��exinuart.h���г�
 *          TIMERA_CCR:��ѡ��CCR����exinuart.h���г�
 *          period:��ʱ���ж����ڣ���λms
 * ע������:���ô˺����󣬿���ʹ�õ��жϺ���Ϊ
 *          TA0_N_IRQHandler  TA1_N_IRQHandler
 *          TA2_N_IRQHandler  TA3_N_IRQHandler
 *          ��isr.c���в鿴��Ŀǰֻд��TA3_N_IRQHandler�еļ���CCR���жϴ�������TIMERA���Ը����Լ���Ҫ��д
 *************************************************/
uint16 CCRn_period_val[4][7] = {0};//���ڴ洢���ڲ�������
void TimerA_CCRnINT_init(TIMERA_enum TIMERAn , TIMERA_CCR_enum TIMERA_CCR,int period)
{
    TimerA_CLK_set(TIMERAn,TIMERA_ACLK,TIMERA_DIV1,TIMERA_DIV1);//ѡ��ACLK��Ϊʱ�ӣ����ҷ�ƵΪID=1 IDEX=1  32768hz
    TimerA_MOD_sel(TIMERAn,CONTINUOUS);//ѡ��TimerA����ģʽΪCONTINUOUS ��������0xFFFFh ������
    period = period_cvert(TIMERAn,period);
    CCRn_period_val[TIMERAn][TIMERA_CCR]=period;
    //����Ϊ�ж�����
   //1)����TImerA CCRn��NVIC�ж�ʹ��
   TimerA_NVIC_IRQ_set(TIMERAn,TIMERA_TAN);
   //2)��������CCRn���ж�����
   TimerA_enable_CCRnIRQ(TIMERAn,TIMERA_CCR);
   //3)��CCRnд���ֵֵ
   TimerA_CCRVAL_set(TIMERAn,TIMERA_CCR,period);
   //4)�������ж�
   __enable_interrupt();
}
