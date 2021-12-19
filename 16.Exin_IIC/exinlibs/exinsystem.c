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
/*************************************************
 * ��  ��  ��:CS_unlocked
 * ��       ��:CS�Ĵ�������
 * ��       ��:��
 * ע������:��
 *************************************************/
void CS_unlocked()
{
    CS->KEY = CS_KEY_VAL ;//����CS�Ĵ���
}
/*************************************************
 * ��  ��  ��:CS_locked
 * ��       ��:CS_�Ĵ�������
 * ��       ��:��
 * ע������:��
 *************************************************/
void CS_locked()
{
    CS->KEY = 0;          // CS�Ĵ�������
}
/*************************************************
 * ��  ��  ��:DCO_set
 * ��       ��:����DCOƵ��
 * ��       ��:DCO_FRE:DCO_FREΪDCO��ѡƵ����exinsystem.h���г�
 * ע������:��
 *************************************************/
void DCO_set(DOC_FRE_enum DCO_FRE)
{
    CS->CTL0 = 0;
    switch(DCO_FRE)
    {
         case(DCO_1_5M): CS->CTL0 = CS_CTL0_DCORSEL_0;   break;//1.5Mhz
         case(DCO_3_0M): CS->CTL0 = CS_CTL0_DCORSEL_1;   break;//3Mhz
         case(DCO_6_0M): CS->CTL0 = CS_CTL0_DCORSEL_2;   break;//6Mhz
         case(DCO_12_0M): CS->CTL0 = CS_CTL0_DCORSEL_3;   break;//12Mhz
         case(DCO_24_0M): CS->CTL0 = CS_CTL0_DCORSEL_4;   break;//24Mhz
         case(DCO_48_0M): CS->CTL0 = CS_CTL0_DCORSEL_5;   break;//48Mhz
         default:CS->CTL0 = CS_CTL0_DCORSEL_1;   break;//3Mhz
    }
}
/*************************************************
 * ��  ��  ��:MCLK_set
 * ��       ��:����MCLK
 * ��       ��:
 *          CLK_source:ʱ��Դ�о٣���exinsystem.h���г�
 *          CLK_DIV:Ϊ��ѡ��Ƶ,��exinsystem.h���г�
 * ע������:��
 *************************************************/
void MCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK);//��������MCLKʱ��Դ����λ��MCLK��Ƶ����λ
    switch(CLK_source)//����MCLKʱ��Դ������
    {
           case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELM__LFXTCLK;   break;
           case(VLOCLK):  CS->CTL1 |= CS_CTL1_SELM__VLOCLK;    break;
           case(REFOCLK): CS->CTL1 |= CS_CTL1_SELM__REFOCLK;   break;
           case(DCOCLK):  CS->CTL1 |= CS_CTL1_SELM__DCOCLK;    break;
           case(MODOSC):  CS->CTL1 |= CS_CTL1_SELM__MODOSC;    break;
           case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELM__HFXTCLK;   break;
           default:       CS->CTL1 |= CS_CTL1_SELM__DCOCLK;    break;
    }
    switch(CLK_DIV)//����MCLKʱ��Դ������
   {
          case(CLK_DIV1):   CS->CTL1 |= CS_CTL1_DIVM__1;   break;
          case(CLK_DIV2):   CS->CTL1 |= CS_CTL1_DIVM__2;    break;
          case(CLK_DIV4):   CS->CTL1 |= CS_CTL1_DIVM__4;   break;
          case(CLK_DIV8):   CS->CTL1 |= CS_CTL1_DIVM__8;    break;
          case(CLK_DIV16):  CS->CTL1 |= CS_CTL1_DIVM__16;    break;
          case(CLK_DIV32):  CS->CTL1 |= CS_CTL1_DIVM__32;   break;
          case(CLK_DIV64):  CS->CTL1 |= CS_CTL1_DIVM__64;   break;
          case(CLK_DIV128): CS->CTL1 |= CS_CTL1_DIVM__128;   break;
          default:          CS->CTL1 |= CS_CTL1_DIVM__1;    break;
   }
}
/*************************************************
 * ��  ��  ��:SMCLK_set
 * ��       ��:����SMCLK
 * ��       ��:
 *          CLK_source:ʱ��Դ�о٣���exinsystem.h���г�
 *          CLK_DIV:Ϊ��ѡ��Ƶ,��exinsystem.h���г�
 * ע������:��
 *************************************************/
void SMCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELS_MASK | CS_CTL1_DIVS_MASK);//��������SMCLKʱ��Դ����λ��SMCLK��Ƶ����λ
    switch(CLK_source)//����MCLKʱ��Դ������
    {
           case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELS__LFXTCLK;   break;
           case(VLOCLK):  CS->CTL1 |= CS_CTL1_SELS__VLOCLK;    break;
           case(REFOCLK): CS->CTL1 |= CS_CTL1_SELS__REFOCLK;   break;
           case(DCOCLK):  CS->CTL1 |= CS_CTL1_SELS__DCOCLK;    break;
           case(MODOSC):  CS->CTL1 |= CS_CTL1_SELS__MODOSC;    break;
           case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELS__HFXTCLK;   break;
           default:       CS->CTL1 |= CS_CTL1_SELM__DCOCLK;    break;
    }
    switch(CLK_DIV)//����MCLKʱ��Դ������
   {
          case(CLK_DIV1):   CS->CTL1 |= CS_CTL1_DIVS__1;   break;
          case(CLK_DIV2):   CS->CTL1 |= CS_CTL1_DIVS__2;    break;
          case(CLK_DIV4):   CS->CTL1 |= CS_CTL1_DIVS__4;   break;
          case(CLK_DIV8):   CS->CTL1 |= CS_CTL1_DIVS__8;    break;
          case(CLK_DIV16):  CS->CTL1 |= CS_CTL1_DIVS__16;    break;
          case(CLK_DIV32):  CS->CTL1 |= CS_CTL1_DIVS__32;   break;
          case(CLK_DIV64):  CS->CTL1 |= CS_CTL1_DIVS__64;   break;
          case(CLK_DIV128): CS->CTL1 |= CS_CTL1_DIVS__128;   break;
          default:          CS->CTL1 |= CS_CTL1_DIVS__1;    break;
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
     CS_unlocked();
     DCO_set(DCO_48_0M);//����DCOʱ�ӵ�48Mhz
     MCLK_set(DCOCLK,CLK_DIV1);//����MCLʱ��ԴΪDCOCLK ��ƵΪ1��f(MCLK) = f(DCO)
     SMCLK_set(DCOCLK,CLK_DIV16);//����SMCLKʱ��ԴΪDCOCLK ��Ƶ16��f(SMCLK) = f(DCO)/16
     CS_locked();
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

