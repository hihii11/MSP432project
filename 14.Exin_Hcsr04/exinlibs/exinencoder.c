/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exinencoder.h"
#define NUMBER_TIMER_CAPTURES        20

volatile uint16_t timerAcaptureValues[NUMBER_TIMER_CAPTURES] = {0};
uint16_t timerAcapturePointer = 0;


/******************************
 * 编码器结构体定义
 *****************************/
Encoder_IncTypeDef encoder_A,encoder_B,encoder_C,encoder_D;

/******************************
 * 编码器结构体初始化
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道
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
 * 编码器对应方向引脚初始化
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道 p3.0
    ENCODER_CHB,//B通道 p3.1
    ENCODER_CHC,//C通道 p3.2
    ENCODER_CHD,//D通道 p3.3
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
 * 编码器上升沿计数器初始化
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道 p6.4
    ENCODER_CHB,//B通道 p6.5
    ENCODER_CHC,//C通道 p6.6
    ENCODER_CHD,//D通道 p6.7
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
  /*********************一个编码器对应一个外部中断可在此继续添加**********************/
}

/******************************
 * 编码器模块初始化
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道
 *
 *****************************/
void encoder_init(Encoder_Channel_enum CHI,unsigned char MODE)
{
    if(MODE==CAPTURE)//定时器上升沿捕获
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
        TIMER_A0->CCTL[2] = TIMER_A_CCTLN_CM_1 | // Capture rising edge,//捕获上升沿
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
    else//外部上升沿中断捕获
    {
        encoder_IncTypeDef_init(CHI);//结构体初始化
        encoder_dirpin_init(CHI);//方向引脚初始化
        encoder_interrupt_init(CHI);//外部中断初始化
    }


}

/******************************
 * 获取编码器脉冲数
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道
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
 * 获取编码器脉方向
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道
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
 * 清零编码器计数
 *
 * 可选通道:
 *  ENCODER_CHA,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道
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


/****************
 * 测试函数
 */
void OLED_show()
{
    unsigned char tmp[20]={};
    OLED_Show_String(0,1, "CH ",8);
    OLED_Show_String(40,1, "speed",8);
    OLED_Show_String(100,1, "dir",8);

    OLED_Show_String(0,2, "CHA",8);
    sprintf((char*)tmp,"%d   ", (int32)(GET_encoder_num(ENCODER_CHA)));
    OLED_Show_String(40, 2,tmp,8);

    OLED_Show_Num(100, 2,  GET_encoder_dir(ENCODER_CHA), 1, 8);

    OLED_Show_String(0,3, "CHB",8);
    sprintf((char*)tmp,"%d   ", (int32)(GET_encoder_num(ENCODER_CHB)));
    OLED_Show_String(40, 3,  tmp,8);
    OLED_Show_Num(100, 3,  GET_encoder_dir(ENCODER_CHB), 1, 8);
}
/*
Interrupt_setPriority（interrupt_number_1,0x00）; //最高优先级
Interrupt_setPriority（interrupt_number_2,0x20）;
Interrupt_setPriority（interrupt_number_3,0x40）;
Interrupt_setPriority（interrupt_number_4,0x60）;
Interrupt_setPriority（interrupt_number_5,0x80）;
Interrupt_setPriority（interrupt_number_6,0xA0）;
Interrupt_setPriority（interrupt_number_7,0xC0）;
Interrupt_setPriority（interrupt_number_8,0xE0）; //最低优先级
 */
void ENCODER_TEST()
{
   system_init(0);
   OLED_init();
     OLED_clr();
   encoder_init(ENCODER_CHA,INT);//其他通道根据需要自行配制

   encoder_init(ENCODER_CHB,INT);

   TimerA_CCR0INT_init(TIMERA_A3 , 100);
   while(1)
   {
       OLED_show();
   }
}

