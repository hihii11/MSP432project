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
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);


    if(status & GPIO_PIN1)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN5)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN6)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}

void PORT2_IRQHandler(void)
{
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);


    if(status & GPIO_PIN1)
    {

        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        encoder_B.dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        if(encoder_B.dir == 1)
            encoder_B.encoder++;
        else
            encoder_B.encoder--;

        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN5)
      {
       // encoder++;
        //dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN6)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}

void PORT3_IRQHandler(void)
{
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, status);


    if(status & GPIO_PIN1)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN5)
      {
        delay_ms(5);
        A_flag=1;
        B_flag=0;
        IRQ3_5flag=1;
      }
    else if(status & GPIO_PIN6)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}
void PORT4_IRQHandler(void)
{
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

    if(status & GPIO_PIN1)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
        encoder_A.dir=gpio_get(GPIO_PORT_P4,GPIO_PIN5);
        if(encoder_A.dir == 1)
            encoder_A.encoder++;
        else
            encoder_A.encoder--;
      }
    else if(status & GPIO_PIN5)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN6)
      {
        delay_ms(5);
        A_flag=0;
        B_flag=1;
        IRQ4_6flag=1;
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}

void PORT5_IRQHandler(void)
{
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);


    if(status & GPIO_PIN1)
    {
        encoder_D.dir=gpio_get(GPIO_PORT_P5,GPIO_PIN0);
        if(encoder_D.dir == 1)
            encoder_D.encoder++;
        else
            encoder_D.encoder--;
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN5)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN6)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}

void PORT6_IRQHandler(void)
{
    uint32_t status;
    //  ��ձ�־λ
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    if(status & GPIO_PIN0)
    {

            /*��ӳ���*/
    }
    else if(status & GPIO_PIN1)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN2)
    {
        /*��ӳ���*/
    }
    else if(status & GPIO_PIN3)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN4)
      {
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN5)
      {  /*��ӳ���*/
      }
    else if(status & GPIO_PIN6)
      {
        encoder_C.dir=gpio_get(GPIO_PORT_P6,GPIO_PIN1);
        if(encoder_C.dir == 1)
            encoder_C.encoder++;
        else
            encoder_C.encoder--;
        /*��ӳ���*/
      }
    else if(status & GPIO_PIN7)
      {
        /*��ӳ���*/
      }
}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);
}


void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*��ӳ���*/
}
void TA2_0_IRQHandler(void) {
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    /*��ӳ���*/

}

void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
}
