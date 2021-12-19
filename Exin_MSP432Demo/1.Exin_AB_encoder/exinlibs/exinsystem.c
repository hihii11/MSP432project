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
#include"headfile.h"
#include"exinsystem.h"
long int sysc=0;
long int systim=0;

/***********************************/
/* error
 *
 * ��������
 */
/**********************************/
void error(void)
{
    volatile uint32_t i;

    while (1)
    {
        P1->OUT ^= BIT0;
        for(i = 20000; i > 0; i--);           // Blink LED forever
    }
}
/***********************************/
/* set_DCO_48MH
 *
 * ��DCOʱ������Ϊ48MHZ
 */
/**********************************/
void set_DCO_48MH()
{
    //���ɵ�VCORE Level 1: AM0_LDO����> AM1_LDO
    uint32_t currentPowerState;
    currentPowerState = PCM->CTL0 & PCM_CTL0_CPM_MASK;
    P1->DIR |= BIT0;
    if (currentPowerState != PCM_CTL0_CPM_0)
       error();

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    if (PCM->IFG & PCM_IFG_AM_INVALID_TR_IFG)
       error();
    if ((PCM->CTL0 & PCM_CTL0_CPM_MASK) != PCM_CTL0_CPM_1)
       error();
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL & (~FLCTL_BANK0_RDCTL_WAIT_MASK) |
               FLCTL_BANK0_RDCTL_WAIT_2;
    FLCTL->BANK1_RDCTL  = FLCTL->BANK0_RDCTL & (~FLCTL_BANK1_RDCTL_WAIT_MASK) |
           FLCTL_BANK1_RDCTL_WAIT_2;  //����flash
    // ����DCOʱ�ӵ�48Mhz
     CS->KEY = CS_KEY_VAL ;                  // ����CS�Ĵ���
     CS->CTL0 = 0;                           // ����CTL0�Ĵ���
     CS->CTL0 = CS_CTL0_DCORSEL_5;           // ����DCOʱ��Ϊ48M
    //��MCLKѡΪDCO
     CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
             CS_CTL1_SELM_3|CS_CTL1_DIVS__16;

     CS->KEY = 0;                            // CS�Ĵ�������
}

/***********************************/
/* set_clock_period
 *
 * ������LOAD�Ĵ�������
 */
/**********************************/
void set_clock_period()
{
    SysTick->LOAD =0xFFFFFF;
}

/***********************************/
/* systic_init
 *
 * �δ��ʱ����ʼ��
 */
/**********************************/
void systic_init()
{
    set_clock_period();
    SysTick->CTRL= SYSTIC_CONFIGURE;
    SysTick->VAL = 0x01;
    MPU->CTRL = MPU_CTRL_ENABLE_Msk | MPU_CTRL_PRIVDEFENA_Msk;
    __enable_interrupt();
    systic_clr();
    systic_end();

}
/***********************************/
/* systic_start
 *
 * ��ʼ��ʱ
 *
 *�����ڼ�¼�ߵ�ƽ��͵�ƽ����ʱ��
 *��systic_end ���ʹ��
 */
/**********************************/
void systic_start()
{
    systic_clr();
    SysTick->LOAD =0xFFFFFF;
    SysTick->CTRL= SYSTIC_CONFIGURE;
}

/***********************************/
/* systic_end
 *
 * ֹͣ��ʱ
 *
 *�����ڼ�¼�ߵ�ƽ��͵�ƽ����ʱ��
 *��systic_start ���ʹ��
 */
/**********************************/
void systic_end()
{
    SysTick->CTRL ^= SysTick->CTRL;
}
/***********************************/
/*  systic_read
 *
 * ��ȡ��ǰ��ʱ
 *
 * ��������:us ms s,�ֱ���us ms sΪ��λ
 * ���ص�ǰ��ʱֵ
 */
/**********************************/
int systic_read(unsigned int ss)
{
    static long int sys_us;
    sys_us=((0x1000000-SysTick->VAL)+0x1000000 * systim )/(F_Div);
    switch(ss)
    {
        case(us):return sys_us;
        case(ms):return sys_us/1000;
        case(s): return sys_us/1000/1000;
        default: return 0;
    }
}
/***********************************/
/* systic_clr
 *
 * ���㵱ǰ��ʱֵ
 */
/**********************************/
void systic_clr()
{
    SysTick->VAL = 0x01; systim=0;
}


/***********************************/
/* system_init
 *
 * ϵͳ��ʼ����EN=0��ʹ�õδ��ʱ��
 *             EN=1ʹ�õδ��ʱ��
 */
/**********************************/
char EN;//�δ��ʱ��ʹ��
void system_init(char EN)
{
    WDT_A->CTL = WDT_A_CTL_PW |             // �رտ��Ź�
    WDT_A_CTL_HOLD;
    delay_ms(100);//�ȴ������ϵ�
    if(EN)
    {
        systic_init();
    }
}
/***********************************/
/* SysTick_Handler
 *
 * SysTick->VAL��Ϊ0����һ���ж�
 */
/**********************************/
void SysTick_Handler(void)
{
    systim++;
}



void systic_delayus(int n)
{
    systic_init();
    systic_start();
    while(systic_read(us)<=n);
    systic_end();
}

void systic_delayms(int n)
{
    n*=1000;
    systic_delayus(n);
}

