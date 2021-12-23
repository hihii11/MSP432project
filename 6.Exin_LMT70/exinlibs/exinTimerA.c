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
#include "exinTimerA.h"


/*************************************************
 * ��  ��  ��:TimerA_MOD_sel
 * ��       ��:TimerAģ�鹤��ģʽѡ��
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          TIMERA_MODE:��ѡ��TimerA������ʽ����exinTimerA.h�ļ���ö��
 * ע������:TIMERA_MODE��ѡSTOP��UP��CONTINUOUS��UP_DOWN
 *          STOP:��ʱTimerAģ�齫ֹͣ����
 *          UP:  ��ʱTimerAģ�齫��0~CCR0֮������ظ�����
 *          CONTINUOUS:��ʱTimerAģ�齫��0~0xffff�����ظ�����
 *          UP_DOWN:��ʱTimerAģ�齫�ȼ�����CCR0�ٴ�CCR0��ʼ��������0
 *************************************************/
void TimerA_MOD_sel(TIMERA_enum TIMER,TIMERA_MOD_enum TIMERA_MODE)
{
    uint16 MOD = 0x0000;
    switch(TIMERA_MODE)
    {
        case(STOP):      MOD = TIMER_A_CTL_MC__STOP;break;
        case(UP):        MOD = TIMER_A_CTL_MC__UP;break;
        case(CONTINUOUS):MOD = TIMER_A_CTL_MC__CONTINUOUS;break;
        case(UP_DOWN):   MOD = TIMER_A_CTL_MC__UPDOWN;break;
        default:MOD = TIMER_A_CTL_MC__STOP;
    }
    switch(TIMER)
    {
          case(TIMERA_A0):TIMER_A0->CTL |= MOD;break;
          case(TIMERA_A1):TIMER_A1->CTL |= MOD;break;
          case(TIMERA_A2):TIMER_A2->CTL |= MOD;break;
          case(TIMERA_A3):TIMER_A3->CTL |= MOD;break;
    }
}
/*************************************************
 * ��  ��  ��:TimerA_CLK_set
 * ��       ��:TimerAģ��ʱ������
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          TIMERA_CLK:��ѡ��TimerAʱ�ӣ���exinTimerA.h�ļ���ö��
 *          TIMERA_DIV:��ѡ��ʱ�ӷ�Ƶϵ������exinTimerA.h�ļ���ö��
 * ע������:��
 *************************************************/
void TimerA_CLK_set(TIMERA_enum TIMER,TIMERA_CLK_enum TIMERA_CLK,TIMERA_DIV_enum TIMERA_DIV)
{
    uint16 CLK=0x0000;
    uint16 DIV = 0x0000;
    switch(TIMERA_DIV)
   {
       case(TIMERA_DIV1):DIV = TIMER_A_CTL_ID_0;break;
       case(TIMERA_DIV2):DIV = TIMER_A_CTL_ID_1;break;
       case(TIMERA_DIV4):DIV = TIMER_A_CTL_ID_2;break;
       case(TIMERA_DIV8):DIV = TIMER_A_CTL_ID_3;break;
       default:DIV = TIMER_A_CTL_ID_0;
   }
    switch(TIMERA_CLK)
    {
        case(TIMERA_TACLK):CLK = TIMER_A_CTL_SSEL__TACLK;break;
        case(TIMERA_ACLK):CLK = TIMER_A_CTL_SSEL__ACLK;break;
        case(TIMERA_SMCLK):CLK = TIMER_A_CTL_SSEL__SMCLK;break;
        case(TIMERA_INCLK):CLK = TIMER_A_CTL_SSEL__INCLK;break;
        default:CLK = TIMER_A_CTL_SSEL__TACLK;
    }
    switch(TIMER)
    {
        case(TIMERA_A0):TIMER_A0->CTL |= CLK|DIV;break;
        case(TIMERA_A1):TIMER_A1->CTL |= CLK|DIV;break;
        case(TIMERA_A2):TIMER_A2->CTL |= CLK|DIV;break;
        case(TIMERA_A3):TIMER_A3->CTL |= CLK|DIV;break;
        default:;
    }
}
/*************************************************
 * ��  ��  ��:TimerA_NVIC_IRQ_set
 * ��       ��:TimerAģ���Ӽ��ж�ʹ��
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          TIMERA_NVIC:��ѡ���жϺ�
 * ע������:��
 *************************************************/
void TimerA_NVIC_IRQ_set(TIMERA_enum TIMER,TIMERA_NVIC_enum TIMERA_NVIC)
{
    switch(TIMER)//�жϱ�־λ����/�������ԱȽϲ���ģ����ж�����
  {
      case(TIMERA_A0):if(TIMERA_NVIC == TIMERA_TA0) NVIC->ISER[0] |= 1 << ((TA0_0_IRQn) & 31);
                      else if(TIMERA_NVIC == TIMERA_TAN) NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);
                      else {;} break;
      case(TIMERA_A1):if(TIMERA_NVIC == TIMERA_TA0) NVIC->ISER[0] |= 1 << ((TA1_0_IRQn) & 31);
                      else if(TIMERA_NVIC == TIMERA_TAN) NVIC->ISER[0] = 1 << ((TA1_N_IRQn) & 31);
                      else {;} break;
      case(TIMERA_A2):if(TIMERA_NVIC == TIMERA_TA0) NVIC->ISER[0] |= 1 << ((TA2_0_IRQn) & 31);
                      else if(TIMERA_NVIC == TIMERA_TAN) NVIC->ISER[0] |= 1 << ((TA2_N_IRQn) & 31);
                      else {;} break;
      case(TIMERA_A3):if(TIMERA_NVIC == TIMERA_TA0)   NVIC->ISER[0] |= 1 << ((TA3_0_IRQn) & 31);
                      else if(TIMERA_NVIC == TIMERA_TAN) NVIC->ISER[0] |= 1 << ((TA3_N_IRQn) & 31);
                      else {;} break;
      default:;
  }
}
/*************************************************
 * ��  ��  ��:TimerA_enable_CCRnIRQ
 * ��       ��:TimerAģ����������CCRn�Ĵ������ж�����
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          TIMERA_CCR:��ѡ��CCR�Ĵ�������exinTimerA.h�ļ���ö��
 * ע������:��
 *************************************************/
void TimerA_enable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR)
{
    switch(TIMER)//�жϱ�־λ����/�������ԱȽϲ���ģ����ж�����
    {
        case(TIMERA_A0):TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A0->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A1):TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A1->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A2):TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A2->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A3):TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A3->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        default:;
    }
}
/*************************************************
 * ��  ��  ��:TimerA_disable_CCRnIRQ
 * ��       ��:TimerAģ���ֹ����CCRn�Ĵ������ж�����
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          TIMERA_CCR:��ѡ��CCR�Ĵ�������exinTimerA.h�ļ���ö��
 * ע������:��
 *************************************************/
void TimerA_disable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR)
{
    switch(TIMER)//�жϱ�־λ����/�������ԱȽϲ���ģ����ж�����
    {
        case(TIMERA_A0):TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A1):TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A2):TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A3):TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        default:;
    }
}
/*************************************************
 * ��  ��  ��:TimerA_CCRVAL_set
 * ��       ��:��CCR�Ĵ���д��һ����ֵ
 * ��       ��:TIMER:��ѡ���TimerAģ�飬��exinTimerA.h�ļ���ö��
 *          val:��Ҫ���õ�����
 * ע������:��
 *************************************************/
void TimerA_CCRVAL_set(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR,uint16 val)
{
    switch(TIMER)
   {
       case(TIMERA_A0):TIMER_A0->CCR[TIMERA_CCR] = val;break;
       case(TIMERA_A1):TIMER_A1->CCR[TIMERA_CCR] = val;break;
       case(TIMERA_A2):TIMER_A2->CCR[TIMERA_CCR] = val;break;
       case(TIMERA_A3):TIMER_A3->CCR[TIMERA_CCR] = val;break;
       default:;
   }
}

