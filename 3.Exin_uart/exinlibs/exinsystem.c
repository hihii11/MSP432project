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
#include"headfile.h"
#include"exinsystem.h"
long int sysc=0;
long int systim=0;

/***********************************/
/* error
 *
 * 错误闪灯
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
 * 函  数  名:CS_unlocked
 * 功       能:CS寄存器解锁
 * 参       数:无
 * 注意事项:无
 *************************************************/
void CS_unlocked()
{
    CS->KEY = CS_KEY_VAL ;//解锁CS寄存器
}
/*************************************************
 * 函  数  名:CS_locked
 * 功       能:CS_寄存器上锁
 * 参       数:无
 * 注意事项:无
 *************************************************/
void CS_locked()
{
    CS->KEY = 0;          // CS寄存器上锁
}
/*************************************************
 * 函  数  名:DCO_set
 * 功       能:设置DCO频率
 * 参       数:DCO_FRE:DCO_FRE为DCO可选频率在exinsystem.h中列出
 * 注意事项:无
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
 * 函  数  名:MCLK_set
 * 功       能:设置MCLK
 * 参       数:
 *          CLK_source:时钟源列举，在exinsystem.h中列出
 *          CLK_DIV:为可选分频,在exinsystem.h中列出
 * 注意事项:无
 *************************************************/
void MCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK);//首先清零MCLK时钟源设置位和MCLK分频设置位
    switch(CLK_source)//进行MCLK时钟源的设置
    {
           case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELM__LFXTCLK;   break;
           case(VLOCLK):  CS->CTL1 |= CS_CTL1_SELM__VLOCLK;    break;
           case(REFOCLK): CS->CTL1 |= CS_CTL1_SELM__REFOCLK;   break;
           case(DCOCLK):  CS->CTL1 |= CS_CTL1_SELM__DCOCLK;    break;
           case(MODOSC):  CS->CTL1 |= CS_CTL1_SELM__MODOSC;    break;
           case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELM__HFXTCLK;   break;
           default:       CS->CTL1 |= CS_CTL1_SELM__DCOCLK;    break;
    }
    switch(CLK_DIV)//进行MCLK时钟源的设置
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
 * 函  数  名:SMCLK_set
 * 功       能:设置SMCLK
 * 参       数:
 *          CLK_source:时钟源列举，在exinsystem.h中列出
 *          CLK_DIV:为可选分频,在exinsystem.h中列出
 * 注意事项:无
 *************************************************/
void SMCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV)
{
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELS_MASK | CS_CTL1_DIVS_MASK);//首先清零SMCLK时钟源设置位和SMCLK分频设置位
    switch(CLK_source)//进行SMCLK时钟源的设置
    {
           case(LFXTCLK): CS->CTL1 |= CS_CTL1_SELS__LFXTCLK;   break;
           case(VLOCLK):  CS->CTL1 |= CS_CTL1_SELS__VLOCLK;    break;
           case(REFOCLK): CS->CTL1 |= CS_CTL1_SELS__REFOCLK;   break;
           case(DCOCLK):  CS->CTL1 |= CS_CTL1_SELS__DCOCLK;    break;
           case(MODOSC):  CS->CTL1 |= CS_CTL1_SELS__MODOSC;    break;
           case(HFXTCLK): CS->CTL1 |= CS_CTL1_SELS__HFXTCLK;   break;
           default:       CS->CTL1 |= CS_CTL1_SELS__DCOCLK;    break;
    }
    switch(CLK_DIV)//进行SMCLK时钟源的设置
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
 * 将DCO时钟设置为48MHZ
 */
/**********************************/
void set_DCO_48MH()
{
    //过渡到VCORE Level 1: AM0_LDO——> AM1_LDO
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
           FLCTL_BANK1_RDCTL_WAIT_2;  //配置flash
     CS_unlocked();
     DCO_set(DCO_48_0M);//设置DCO时钟到48Mhz
     MCLK_set(DCOCLK,CLK_DIV1);//设置MCL时钟源为DCOCLK 分频为1即f(MCLK) = f(DCO)
     SMCLK_set(DCOCLK,CLK_DIV2);//设置SMCLK时钟源为DCOCLK 分频2即f(SMCLK) = f(DCO)/2 = 24Mhz
     CS_locked();
}

/***********************************/
/* set_clock_period
 *
 * 计数器LOAD寄存器置数
 */
/**********************************/
void set_clock_period()
{
    SysTick->LOAD =0xFFFFFF;
}

/***********************************/
/* systic_init
 *
 * 滴答计时器初始化
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
 * 开始计时
 *
 *可用于记录高电平或低电平持续时长
 *与systic_end 配合使用
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
 * 停止计时
 *
 *可用于记录高电平或低电平持续时长
 *与systic_start 配合使用
 */
/**********************************/
void systic_end()
{
    SysTick->CTRL ^= SysTick->CTRL;
}
/***********************************/
/*  systic_read
 *
 * 读取当前计时
 *
 * 参数可填:us ms s,分别以us ms s为单位
 * 返回当前计时值
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
 * 清零当前计时值
 */
/**********************************/
void systic_clr()
{
    SysTick->VAL = 0x01; systim=0;
}


/***********************************/
/* system_init
 *
 * 系统初始化，EN=0不使用滴答计时器
 *             EN=1使用滴答计时器
 */
/**********************************/
char EN;//滴答计时器使能
void system_init(char EN)
{
    WDT_A->CTL = WDT_A_CTL_PW |             // 关闭看门狗
    WDT_A_CTL_HOLD;
    delay_ms(100);//等待外设上电
    if(EN)
    {
        systic_init();
    }
}
/***********************************/
/* SysTick_Handler
 *
 * SysTick->VAL减为0触发一次中断
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

