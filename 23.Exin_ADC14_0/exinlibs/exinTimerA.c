/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月21日16:46:33
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exinTimerA.h"


/*************************************************
 * 函  数  名:TimerA_MOD_sel
 * 功       能:TimerA模块工作模式选择
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_MODE:可选的TimerA工作方式，在exinTimerA.h文件中枚举
 * 注意事项:TIMERA_MODE可选STOP、UP、CONTINUOUS、UP_DOWN
 *          STOP:此时TimerA模块将停止计数
 *          UP:  此时TimerA模块将在0~CCR0之间进行重复计数
 *          CONTINUOUS:此时TimerA模块将在0~0xffff进行重复计数
 *          UP_DOWN:此时TimerA模块将先计数到CCR0再从CCR0开始减计数到0
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
 * 函  数  名:TimerA_CLK_set
 * 功       能:TimerA模块时钟配置
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_CLK:可选的TimerA时钟，在exinTimerA.h文件中枚举
 *          TIMERA_DIV:可选的时钟分频系数，在exinTimerA.h文件中枚举
 * 注意事项:无
 *************************************************/
void TimerA_CLK_set(TIMERA_enum TIMER,TIMERA_CLK_enum TIMERA_CLK,TIMERA_DIV_enum TIMERA_IDDIV,TIMERA_DIV_enum TIMERA_IDEXDIV)
{
    uint16 CLK=0x0000;
    uint16 ID_DIV = 0x0000;
    uint16 IDEX_DIV = 0x0000;
    switch(TIMERA_IDDIV)
   {
       case(TIMERA_DIV1):ID_DIV = TIMER_A_CTL_ID_0;break;//1
       case(TIMERA_DIV2):ID_DIV = TIMER_A_CTL_ID_1;break;//2
       case(TIMERA_DIV4):ID_DIV = TIMER_A_CTL_ID_2;break;//4
       case(TIMERA_DIV8):ID_DIV = TIMER_A_CTL_ID_3;break;//8
       default:ID_DIV = TIMER_A_CTL_ID_0;
   }
    switch(TIMERA_IDEXDIV)
  {
      case(TIMERA_DIV1):IDEX_DIV = TIMER_A_EX0_TAIDEX_0;break;//1
      case(TIMERA_DIV2):IDEX_DIV = TIMER_A_EX0_TAIDEX_1;break;//2
      case(TIMERA_DIV3):IDEX_DIV = TIMER_A_EX0_TAIDEX_2;break;//3
      case(TIMERA_DIV4):IDEX_DIV = TIMER_A_EX0_TAIDEX_3;break;//4
      case(TIMERA_DIV5):IDEX_DIV = TIMER_A_EX0_TAIDEX_4;break;//5
      case(TIMERA_DIV6):IDEX_DIV = TIMER_A_EX0_TAIDEX_5;break;//6
      case(TIMERA_DIV7):IDEX_DIV = TIMER_A_EX0_TAIDEX_6;break;//7
      case(TIMERA_DIV8):IDEX_DIV = TIMER_A_EX0_TAIDEX_7;break;//8
      default:IDEX_DIV = TIMER_A_EX0_TAIDEX_0;
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
        case(TIMERA_A0):TIMER_A0->CTL |= CLK|ID_DIV;
                        TIMER_A0->EX0 |= IDEX_DIV;
                        break;
        case(TIMERA_A1):TIMER_A1->CTL |= CLK|ID_DIV;
                        TIMER_A1->EX0 |= IDEX_DIV;
                        break;
        case(TIMERA_A2):TIMER_A2->CTL |= CLK|ID_DIV;
                        TIMER_A2->EX0 |= IDEX_DIV;
                        break;
        case(TIMERA_A3):TIMER_A3->CTL |= CLK|ID_DIV;
                        TIMER_A3->EX0 |= IDEX_DIV;
                        break;
        default:;
    }
}
/*************************************************
 * 函  数  名:TimerA_NVIC_IRQ_set
 * 功       能:TimerA模块子级中断使能
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_NVIC:可选的中断号
 * 注意事项:无
 *************************************************/
void TimerA_NVIC_IRQ_set(TIMERA_enum TIMER,TIMERA_NVIC_enum TIMERA_NVIC)
{
    switch(TIMER)//中断标志位清零/允许来自比较捕获模块的中断请求
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
 * 函  数  名:TimerA_enable_CCRnIRQ
 * 功       能:TimerA模块允许来自CCRn寄存器的中断请求
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_CCR:可选的CCR寄存器，在exinTimerA.h文件中枚举
 * 注意事项:无
 *************************************************/
void TimerA_enable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR)
{
    switch(TIMER)//中断标志位清零/允许来自比较捕获模块的中断请求
    {
        case(TIMERA_A0):TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A0->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A1):TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A1->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A2):TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A2->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A3):TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A3->CCTL[TIMERA_CCR] |= TIMER_A_CCTLN_CCIE;break;
        default:;
    }
}
/*************************************************
 * 函  数  名:TimerA_disable_CCRnIRQ
 * 功       能:TimerA模块禁止来自CCRn寄存器的中断请求
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_CCR:可选的CCR寄存器，在exinTimerA.h文件中枚举
 * 注意事项:无
 *************************************************/
void TimerA_disable_CCRnIRQ(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR)
{
    switch(TIMER)//中断标志位清零/允许来自比较捕获模块的中断请求
    {
        case(TIMERA_A0):TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A0->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A1):TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A1->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A2):TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A2->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        case(TIMERA_A3):TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIFG;TIMER_A3->CCTL[TIMERA_CCR] &= ~TIMER_A_CCTLN_CCIE;break;
        default:;
    }
}
/*************************************************
 * 函  数  名:TimerA_CCRVAL_set
 * 功       能:向CCR寄存器写入一个数值
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          val:需要设置的数据
 * 注意事项:无
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
/*************************************************
 * 函  数  名:CCRn_MOD_sel
 * 功       能:将CCR配置为输出模式
 * 参       数:TIMER:可选择的TimerA模块，在exinTimerA.h文件中枚举
 *          TIMERA_CCR可选的CCR寄存器枚举
 *          MOD:输出模式
 * 注意事项:无
 *************************************************/
void CCRn_MOD_sel(TIMERA_enum TIMER,TIMERA_CCR_enum TIMERA_CCR,TIMERA_CCRMOD_enum MOD)
{
    uint16 status;
    switch(MOD)
    {
       case(Set):         status = TIMER_A_CCTLN_OUTMOD_1;break;
       case(Toggle_reset):status = TIMER_A_CCTLN_OUTMOD_2;break;
       case(Set_reset):   status = TIMER_A_CCTLN_OUTMOD_3;break;
       case(Toggle):      status = TIMER_A_CCTLN_OUTMOD_4;break;
       case(Reset):       status = TIMER_A_CCTLN_OUTMOD_5;break;
       case(Toggle_set):  status = TIMER_A_CCTLN_OUTMOD_6;break;
       case(Reset_set):   status = TIMER_A_CCTLN_OUTMOD_7;break;
       default:status = TIMER_A_CCTLN_OUTMOD_0;;
    }
    switch(TIMER)
   {
       case(TIMERA_A0):TIMER_A0->CCTL[TIMERA_CCR] = status;break;
       case(TIMERA_A1):TIMER_A1->CCTL[TIMERA_CCR] = status;break;
       case(TIMERA_A2):TIMER_A2->CCTL[TIMERA_CCR] = status;break;
       case(TIMERA_A3):TIMER_A3->CCTL[TIMERA_CCR] = status;break;
       default:;
   }
}
