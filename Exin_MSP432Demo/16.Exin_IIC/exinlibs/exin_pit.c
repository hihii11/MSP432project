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
#include "exin_pit.h"

int set_time_A1;
int set_time_A2;
int set_time_A3;
int set_time_A4;
/***********************************/
/* PIT_init
 *
 * ��ʱ���жϳ�ʼ�� time��λΪms
 *
 * ��ѡ��ʱ��ͨ��
 * PIT_CHA
 * PIT_CHB
 * PIT_CHC
 * PIT_CHD
 *
 * �жϺ�����einisr.c��ע��
 */
/**********************************/
void PIT_init(PIT_enum CHI,float time)
{
    //��ƵACLK/CCR[n]
    __enable_interrupt();
    time=time/1000*32768;//ACLKʱ��
    switch(CHI)
    {
        case(PIT_CHA):
                   NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
                   TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;//�ж�ʹ��
                   TIMER_A0->CCR[0] = time;//���ñȽϼĴ���
                   TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHB):
                   NVIC->ISER[0] = 1 << ((TA1_0_IRQn) & 31);
                   TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A1->CCTL[0] = TIMER_A_CCTLN_CCIE;//�ж�ʹ��
                   TIMER_A1->CCR[0] = time;//���ñȽϼĴ���
                    TIMER_A1->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHC):
                   NVIC->ISER[0] = 1 << ((TA2_0_IRQn) & 31);
                   TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                   TIMER_A2->CCTL[0] = TIMER_A_CCTLN_CCIE;//�ж�ʹ��
                   TIMER_A2->CCR[0] = time;//���ñȽϼĴ���
                   TIMER_A2->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                   TIMER_A_CTL_MC__UP;
                   break;
        case(PIT_CHD):
                    NVIC->ISER[0] = 1 << ((TA3_0_IRQn) & 31);
                    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
                    TIMER_A3->CCTL[0] = TIMER_A_CCTLN_CCIE;//�ж�ʹ��
                    TIMER_A3->CCR[0] = time;//���ñȽϼĴ���
                    TIMER_A3->CTL = TIMER_A_CTL_SSEL__ACLK | //32768
                    TIMER_A_CTL_MC__UP;
                    break;
    }

}

