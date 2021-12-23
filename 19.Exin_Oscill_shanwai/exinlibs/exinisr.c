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
#include "exinisr.h"

extern char IRQ3_5flag;
extern char IRQ4_6flag;
extern char A_flag;
extern char B_flag;
extern uint8 dirf;
void PORT1_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P1->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*��ӳ���*/
    }
    if(P1->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P1->IFG &= ~IRQ_CLR;
}

void PORT2_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P2->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*��ӳ���*/
    }
    else if(P2->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    else if(P2->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        encoder_B.dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        if(encoder_B.dir == 1)
            encoder_B.encoder++;
        else
            encoder_B.encoder--;

        /*��ӳ���*/
    }
    if(P2->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*��ӳ���*/
    }
    if(P2->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*��ӳ���*/
    }
    if(P2->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*��ӳ���*/
    }
    if(P2->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P2->IFG &= ~IRQ_CLR;
}

void PORT3_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P3->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*��ӳ���*/
    }
    if(P3->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    if(P3->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*��ӳ���*/
    }
    if(P3->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*��ӳ���*/
    }
    if(P3->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        A_flag=1;
        B_flag=0;
        IRQ3_5flag=1;
    }
    if(P3->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*��ӳ���*/
    }
    if(P3->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P3->IFG &= ~IRQ_CLR;
}
void PORT4_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;

    if(P4->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*��ӳ���*/
    }
    if(P4->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    if(P4->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*��ӳ���*/
    }
    if(P4->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        encoder_A.dir=gpio_get(GPIO_PORT_P4,GPIO_PIN5);
        if(encoder_A.dir == 1)
            encoder_A.encoder++;
        else
            encoder_A.encoder--;
    }
    if(P4->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*��ӳ���*/
    }
    if(P4->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        A_flag=0;
        B_flag=1;
        IRQ4_6flag=1;
    }
    if(P4->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P4->IFG &= ~IRQ_CLR;
}

void PORT5_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P5->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        encoder_D.dir=gpio_get(GPIO_PORT_P5,GPIO_PIN0);
        if(encoder_D.dir == 1)
            encoder_D.encoder++;
        else
            encoder_D.encoder--;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        /*��ӳ���*/
    }
    if(P5->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P5->IFG &= ~IRQ_CLR;
}

void PORT6_IRQHandler(void)
{
    uint8 IRQ_CLR = 0x00;
    if(P6->IFG & BIT0)
    {
        IRQ_CLR |= BIT0;
            /*��ӳ���*/
    }
    if(P6->IFG & BIT1)
    {
        IRQ_CLR |= BIT1;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT2)
    {
        IRQ_CLR |= BIT2;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT3)
    {
        IRQ_CLR |= BIT3;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT4)
    {
        IRQ_CLR |= BIT4;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT5)
    {
        IRQ_CLR |= BIT5;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT6)
    {
        IRQ_CLR |= BIT6;
        encoder_C.dir=gpio_get(GPIO_PORT_P6,GPIO_PIN1);
        if(encoder_C.dir == 1)
            encoder_C.encoder++;
        else
            encoder_C.encoder--;
        /*��ӳ���*/
    }
    if(P6->IFG & BIT7)
    {
        IRQ_CLR |= BIT7;
        /*��ӳ���*/
    }
    P6->IFG &= ~IRQ_CLR;
}


void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*��ӳ���*/
}

void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*��ӳ���*/
}
void TA2_0_IRQHandler(void) {
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    /*��ӳ���*/

}

extern void OLED_show();
void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    Encoder_clr(ENCODER_CHA);
    Encoder_clr(ENCODER_CHB);
}

void TA0_N_IRQHandler(void)
{
    /*��ӳ���*/
}

void TA1_N_IRQHandler(void)
{
    /*��ӳ���*/
}

void TA2_N_IRQHandler(void)
{
    /*��ӳ���*/
}

void TA3_N_IRQHandler(void)
{
    if((TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIFG)&&//�ж��жϱ�־λ�Ƿ���Ч
          (TIMER_A3->CCTL[TIMERA_CCR0]&TIMER_A_CCTLN_CCIE))//�ж�CCR1�ж��Ƿ�ʹ��
       {
           /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/
           TIMER_A3->CCTL[TIMERA_CCR0] &= ~TIMER_A_CCTLN_CCIFG;//���CCR1�жϱ�־λ
           TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR0,TIMER_A3->CCR[TIMERA_CCR0] + CCRn_period_val[TIMERA_A3][TIMERA_CCR0]);//����CCR�Ĵ���
           /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/


           /***********************��������û��Ĵ�����*********************/

           /***********************�û���������ӽ�����*********************/
       }
    if((TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIFG)&&//�ж��жϱ�־λ�Ƿ���Ч
       (TIMER_A3->CCTL[TIMERA_CCR1]&TIMER_A_CCTLN_CCIE))//�ж�CCR1�ж��Ƿ�ʹ��
    {
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/
        TIMER_A3->CCTL[TIMERA_CCR1] &= ~TIMER_A_CCTLN_CCIFG;//���CCR1�жϱ�־λ
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR1,TIMER_A3->CCR[TIMERA_CCR1] + CCRn_period_val[TIMERA_A3][TIMERA_CCR1]);//����CCR�Ĵ���
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/


        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIFG)&&//�ж��жϱ�־λ�Ƿ���Ч
            (TIMER_A3->CCTL[TIMERA_CCR2]&TIMER_A_CCTLN_CCIE))//�ж�CCR2�ж��Ƿ�ʹ��
    {
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/
        TIMER_A3->CCTL[TIMERA_CCR2] &= ~TIMER_A_CCTLN_CCIFG;//���CCR2�жϱ�־λ
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR2,TIMER_A3->CCR[TIMERA_CCR2] + CCRn_period_val[TIMERA_A3][TIMERA_CCR2]);//����CCR�Ĵ���
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/


        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIFG)&&//�ж��жϱ�־λ�Ƿ���Ч
            (TIMER_A3->CCTL[TIMERA_CCR3]&TIMER_A_CCTLN_CCIE))//�ж�CCR3�ж��Ƿ�ʹ��
    {
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/
        TIMER_A3->CCTL[TIMERA_CCR3] &= ~TIMER_A_CCTLN_CCIFG;//���CCR3�жϱ�־λ
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR3,TIMER_A3->CCR[TIMERA_CCR3] + CCRn_period_val[TIMERA_A3][TIMERA_CCR3]);//����CCR�Ĵ���
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/


        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
    if((TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIFG)&&//�ж��жϱ�־λ�Ƿ���Ч
            (TIMER_A3->CCTL[TIMERA_CCR4]&TIMER_A_CCTLN_CCIE))//�ж�CCR4�ж��Ƿ�ʹ��
    {
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/
        TIMER_A3->CCTL[TIMERA_CCR4] &= ~TIMER_A_CCTLN_CCIFG;//���CCR4�жϱ�־λ
        TimerA_CCRVAL_set(TIMERA_A3,TIMERA_CCR4,TIMER_A3->CCR[TIMERA_CCR4] + CCRn_period_val[TIMERA_A3][TIMERA_CCR4]);//����CCR�Ĵ���
        /***************��TA3_N������ʱ���ж�ʱ�⼸����ر���****************/


        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
}
