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
#include "exinencoder.h"
#define NUMBER_TIMER_CAPTURES        20

volatile uint16_t timerAcaptureValues[NUMBER_TIMER_CAPTURES] = {0};
uint16_t timerAcapturePointer = 0;


/******************************
 * �������ṹ�嶨��
 *****************************/
Encoder_IncTypeDef encoder_A,encoder_B,encoder_C,encoder_D;

/******************************
 * �������ṹ���ʼ��
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��
 *
 *****************************/
void encoder_IncTypeDef_init(Encoder_Channel_enum CHI)
{
    switch(CHI)
    {
        case(ENCODER_CHA):encoder_A.dir=0;encoder_A.encoder=0;break;
        case(ENCODER_CHB):encoder_B.dir=0;encoder_B.encoder=0;break;
        case(ENCODER_CHC):encoder_C.dir=0;encoder_C.encoder=0;break;
        case(ENCODER_CHD):encoder_D.dir=0;encoder_D.encoder=0;break;
    }
}
/******************************
 * ��������Ӧ�������ų�ʼ��
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ�� p3.0
    ENCODER_CHB,//Bͨ�� p3.1
    ENCODER_CHC,//Cͨ�� p3.2
    ENCODER_CHD,//Dͨ�� p3.3
 *
 *****************************/
void encoder_dirpin_init(Encoder_Channel_enum CHI)
{
    switch(CHI)
       {
       case(ENCODER_CHA):gpio_init(GPIO_PORT_P4,GPIO_PIN5,GPI,0);break;
       case(ENCODER_CHB):gpio_init(GPIO_PORT_P3,GPIO_PIN0,GPI,0);break;
       case(ENCODER_CHC):gpio_init(GPIO_PORT_P6,GPIO_PIN7,GPI,0);break;
       case(ENCODER_CHD):gpio_init(GPIO_PORT_P5,GPIO_PIN0,GPI,0);break;
       }
}
/******************************
 * �����������ؼ�������ʼ��
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ�� p6.4
    ENCODER_CHB,//Bͨ�� p6.5
    ENCODER_CHC,//Cͨ�� p6.6
    ENCODER_CHD,//Dͨ�� p6.7
 *
 *****************************/
void encoder_interrupt_init(Encoder_Channel_enum CHI)
{
    switch(CHI)
           {
           case(ENCODER_CHA):gpio_interrupt_INIT(GPIO_PORT_P4,GPIO_PIN4,RISING);break;
           case(ENCODER_CHB):gpio_interrupt_INIT(GPIO_PORT_P2,GPIO_PIN3,RISING);break;
           case(ENCODER_CHC):gpio_interrupt_INIT(GPIO_PORT_P6,GPIO_PIN6,RISING);break;
           case(ENCODER_CHD):gpio_interrupt_INIT(GPIO_PORT_P5,GPIO_PIN1,RISING);break;
           }
  /*********************һ����������Ӧһ���ⲿ�жϿ��ڴ˼������**********************/
}

/******************************
 * ������ģ���ʼ��
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��
 *
 *****************************/
void encoder_init(Encoder_Channel_enum CHI,unsigned char MODE)
{
    if(MODE==CAPTURE)//��ʱ�������ز���
    {
        // Configure GPIO
        P1->DIR |= BIT0;                        // Set P1.0 as output
        P1->OUT |= BIT0;                        // P1.0 high
        P2->SEL0 |= BIT5;                       // TA0.CCI2A input capture pin, second function
        P2->DIR &= ~BIT5;
        P4->SEL0 |= BIT2;                       // Set as ACLK pin, second function
        P4->DIR |= BIT2;

        CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
        // Select ACLK = REFO, SMCLK = MCLK = DCO
        CS->CTL1 = CS_CTL1_SELA_2 |
                CS_CTL1_SELS_3 |
                CS_CTL1_SELM_3;
        CS->KEY = 0;                            // Lock CS module from unintended accesses

        // Timer0_A3 Setup
        TIMER_A0->CCTL[2] = TIMER_A_CCTLN_CM_1 | // Capture rising edge,//����������
                TIMER_A_CCTLN_CCIS_0 |          // Use CCI2A=ACLK,
                TIMER_A_CCTLN_CCIE |            // Enable capture interrupt
                TIMER_A_CCTLN_CAP |             // Enable capture mode,
                TIMER_A_CCTLN_SCS;              // Synchronous capture

        TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2 | // Use SMCLK as clock source,
                TIMER_A_CTL_MC_2 |              // Start timer in continuous mode
                TIMER_A_CTL_CLR;                // clear TA0R



        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;    // Enable sleep on exit from ISR
        __enable_interrupt();
       // NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);
        MAP_Interrupt_setPriority(INT_TA0_N, 0x20);
    }
    else//�ⲿ�������жϲ���
    {
        encoder_IncTypeDef_init(CHI);//�ṹ���ʼ��
        encoder_dirpin_init(CHI);//�������ų�ʼ��
        encoder_interrupt_init(CHI);//�ⲿ�жϳ�ʼ��
    }


}

/******************************
 * ��ȡ������������
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��
 *
 *****************************/
long int GET_encoder_num(Encoder_Channel_enum CHI)
{
    switch(CHI)
              {
              case(ENCODER_CHA):return encoder_A.encoder;break;
              case(ENCODER_CHB):return encoder_B.encoder;break;
              case(ENCODER_CHC):return encoder_C.encoder;break;
              case(ENCODER_CHD):return encoder_D.encoder;break;
              }
}

/******************************
 * ��ȡ������������
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��
 *
 *****************************/
unsigned char GET_encoder_dir(Encoder_Channel_enum CHI)
{
    switch(CHI)
              {
              case(ENCODER_CHA):return encoder_A.dir;break;
              case(ENCODER_CHB):return encoder_B.dir;break;
              case(ENCODER_CHC):return encoder_C.dir;break;
              case(ENCODER_CHD):return encoder_D.dir;break;
              }
}


/******************************
 * �������������
 *
 * ��ѡͨ��:
 *  ENCODER_CHA,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��
 *
 *****************************/
void Encoder_clr(Encoder_Channel_enum CHI)
{
    switch(CHI)
              {
              case(ENCODER_CHA):return encoder_A.encoder=0;break;
              case(ENCODER_CHB):return encoder_B.encoder=0;break;
              case(ENCODER_CHC):return encoder_C.encoder=0;break;
              case(ENCODER_CHD):return encoder_D.encoder=0;break;
              }
}

// Timer A0 interrupt service routine
void TA0_N_IRQHandler(void)
{
    volatile uint32_t i;

    if (timerAcapturePointer >= NUMBER_TIMER_CAPTURES)
    {


        timerAcapturePointer=0;
            P1->OUT ^= 0x01;                         // Toggle P1.0 (LED)

    }
    else
    {
        //encoder++;
        //dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        timerAcaptureValues[timerAcapturePointer++] = TIMER_A0->CCR[2];
    }

    // Clear the interrupt flag
    TIMER_A0->CCTL[2] &= ~(TIMER_A_CCTLN_CCIFG);
}

/****************
 * ���Ժ���
 */
int time_counter=0;
void OLED_show()
{
    char tmp[20]={};
    OLED_ShowString(0, 0, "sp/dr:");

    sprintf(tmp,"%d  ", GET_encoder_num(ENCODER_CHA));
    OLED_ShowString(64, 0, tmp);

    OLED_ShowNum(96, 0,  GET_encoder_dir(ENCODER_CHA), 4, 12);

    sprintf(tmp,"%d  ",  GET_encoder_num(ENCODER_CHB));
    OLED_ShowString(64, 1, tmp);

    OLED_ShowNum(96, 1,  GET_encoder_dir(ENCODER_CHB), 4, 12);
    OLED_ShowNum(64, 2,  time_counter, 4, 12);

}
/*
Interrupt_setPriority��interrupt_number_1,0x00��; //������ȼ�
Interrupt_setPriority��interrupt_number_2,0x20��;
Interrupt_setPriority��interrupt_number_3,0x40��;
Interrupt_setPriority��interrupt_number_4,0x60��;
Interrupt_setPriority��interrupt_number_5,0x80��;
Interrupt_setPriority��interrupt_number_6,0xA0��;
Interrupt_setPriority��interrupt_number_7,0xC0��;
Interrupt_setPriority��interrupt_number_8,0xE0��; //������ȼ�
 */
void ENCODER_TEST()
{
   system_init(0);
   OLED_Init();
   gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,1);
   encoder_init(ENCODER_CHA,INT);//����ͨ��������Ҫ��������

   encoder_init(ENCODER_CHB,INT);
   //Interrupt_setPriority(INT_PORT6,0xE0);
   PIT_init(PIT_CHD,100);
   PIT_init(PIT_CHA,110);
   while(1)
   {
       OLED_show();
   }
}
