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
volatile uint8_t UART3_RXDat= 0;
volatile uint8_t UART2_RXDat= 0;
volatile uint8_t UART0_RXDat= 0;
volatile uint32  BRCLK      = 0;
//小数点存储表
const float FP_N[40] ={
                       0.0000,  0.5002,
                       0.0529,  0.5715,
                       0.0715,  0.6003,
                       0.0835,  0.6254,
                       0.1001,  0.6432,
                       0.1252,  0.6667,
                       0.1430,  0.7001,
                       0.1670,  0.7147,
                       0.2147,  0.7503,
                       0.2224,  0.7861,
                       0.2503,  0.8004,
                       0.3000,  0.8333,
                       0.3335,  0.8464,
                       0.3575,  0.8572,
                       0.3753,  0.8751,
                       0.4003,  0.9004,
                       0.4286,  0.9170,
                       0.4378,  0.9288
};


//BRS参数存储表
const uint8 BRS[40] ={
                       0x00,  0xAA,
                       0x01,  0x6B,
                       0x02,  0xAD,
                       0x04,  0xB5,
                       0x08,  0xB6,
                       0x10,  0xD6,
                       0x20,  0xB7,
                       0x11,  0xBB,
                       0x21,  0xDD,
                       0x22,  0xED,
                       0x44,  0xEE,
                       0x25,  0xBF,
                       0x49,  0xDF,
                       0x4A,  0xEF,
                       0x52,  0xF7,
                       0x92,  0xFB,
                       0x53,  0xFD,
                       0x55,  0xFE
};

/*************************************************
 * 函  数  名:UART_IRQ_set
 * 功       能:UART中断设置
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:无
 *************************************************/
void UART_IRQ_set(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
    {
           case(UART0):EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] |= 1 << ((EUSCIA0_IRQn) & 31); break;
           case(UART1):EUSCI_A1->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] |= 1 << ((EUSCIA1_IRQn) & 31); break;
           case(UART2):EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] |= 1 << ((EUSCIA2_IRQn) & 31); break;
           case(UART3):EUSCI_A3->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] |= 1 << ((EUSCIA3_IRQn) & 31); break;
           default:;
    }
}
/*************************************************
 * 函  数  名:UART_IRQRX_set
 * 功       能:UART接收中断设置
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:无
 *************************************************/
void UART_IRQRX_set(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
    {
           case(UART0):EUSCI_A0->IE |= EUSCI_A_IE_RXIE; break;//允许A0接收中断
           case(UART1):EUSCI_A1->IE |= EUSCI_A_IE_RXIE; break;//允许A1接收中断
           case(UART2):EUSCI_A2->IE |= EUSCI_A_IE_RXIE; break;//允许A2接收中断
           case(UART3):EUSCI_A3->IE |= EUSCI_A_IE_RXIE; break;//允许A3接收中断
           default:;
    }
}
/*************************************************
 * 函  数  名:UART_USIC_init
 * 功       能:eUSIC初始化函数
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:无
 *************************************************/
void UART_USIC_init(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
   {
          case(UART0):EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; break;
          case(UART1):EUSCI_A1->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; break;
          case(UART2):EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; break;
          case(UART3):EUSCI_A3->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; break;
          default:;
   }
}

/*************************************************
 * 函  数  名:UART_PIN_sel
 * 功       能:UART引脚初始化
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:
 *          通道            rx     tx
 *          UART0     p1.2   p1.3
 *          UART1     p2.2   p2.3
 *          UART2     p3.2   p3.3
 *          UART3     p9.6   p9.7
 *************************************************/
void UART_PIN_sel(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
    {
            case(UART0):P1->SEL0 |= BIT2 | BIT3; break;//P1.2 rx  P1.3 tx
            case(UART1):P2->SEL0 |= BIT2 | BIT3; break;//P2.2 rx  P2.3 tx
            case(UART2):P3->SEL0 |= BIT2 | BIT3; break;//p3.2 rx P3.3 tx
            case(UART3):P9->SEL0 |= BIT6 | BIT7; break;//P9.6 rx P9.7 tx
            default:;
    }
}
/*************************************************
 * 函  数  名:UART_CLK_sel
 * 功       能:UART时钟选择
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          UART_CLK:UART可选时钟，在exinuart.h中列出
 * 注意事项:默认选择UCLK
 *************************************************/
void UART_CLK_sel(UART_CHA_enum UART_CHA,UART_CLK_enum UART_CLK)
{
    switch(UART_CHA)
    {
        case(UART0):
                    if(UART_CLK == UART_SMCLK) {EUSCI_A0->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK;}
                    else if(UART_CLK == UART_ACLK) {EUSCI_A0->CTLW0 |= EUSCI_B_CTLW0_SSEL__ACLK;}
                    else {EUSCI_A0->CTLW0 = EUSCI_A0->CTLW0;}
                    break;
        case(UART1):
                    if(UART_CLK == UART_SMCLK) {EUSCI_A1->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK;}
                    else if(UART_CLK == UART_ACLK) {EUSCI_A1->CTLW0 |= EUSCI_B_CTLW0_SSEL__ACLK;}
                    else {EUSCI_A1->CTLW0 = EUSCI_A1->CTLW0;}
                    break;
        case(UART2):
                    if(UART_CLK == UART_SMCLK) {EUSCI_A2->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK;}
                    else if(UART_CLK == UART_ACLK) {EUSCI_A2->CTLW0 |= EUSCI_B_CTLW0_SSEL__ACLK;}
                    else {EUSCI_A2->CTLW0 = EUSCI_A2->CTLW0;}
                    break;
        case(UART3):
                    if(UART_CLK == UART_SMCLK) {EUSCI_A3->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK;}
                    else if(UART_CLK == UART_ACLK) {EUSCI_A3->CTLW0 |= EUSCI_B_CTLW0_SSEL__ACLK;}
                    else {EUSCI_A3->CTLW0 = EUSCI_A3->CTLW0;}
                    break;
    }
}
/*************************************************
 * 函  数  名:UART_BRS_val
 * 功       能:确定BRS参数值
 * 参       数:Baunds波特率
 * 注意事项:
 *************************************************/
uint8 UART_BRS_val(int Baunds)
{
    float NF = (float)BRCLK/Baunds - BRCLK/Baunds;
    uint8 i;
    for(i = 0;i<39;i++)//确定小数值范围
    {
        if(NF >= FP_N[i] && NF <= FP_N[i+1])
        {
            break;
        }
    }//确定浮点数位置
    if(abs(NF - FP_N[i]) >= abs(NF - FP_N[i+1]))
        i++;
    return BRS[i];
}
/*************************************************
 * 函  数  名:UART_Baunds_set
 * 功       能:UART波特率设置
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          Baunds:波特率填写
 * 注意事项:当时钟为3Mhz时，波特率最大不能超过115200
            BRDIV  = (int)(f(clk)/Baunds/16) ;比较粗略的分频系数
 *          UCxBRF = (int) (((f(clk)/Baunds/16) - BRDIV)*16+0.5)
 *          UCxBRS = 差表
 *************************************************/
void UART_Baunds_set(UART_CHA_enum UART_CHA,int Baunds )
{
    if(BRCLK == SMCLK_FRE)
    {
    //确定BRDIV
    uint16 BRDIV  = (BRCLK/Baunds)>>4;
    //确定BRF
    uint16 UCxBRF = (int)(((float)BRCLK/Baunds/16-BRCLK/Baunds/16)*16+0.5);
    //确定BRS
    uint16 UCxBRS = UART_BRS_val(Baunds);
        switch(UART_CHA)
        {
                case(UART0):
                            UCA0BR0 =  BRDIV & 0xff;
                            UCA0BR1  = BRDIV & 0xff00;
                            EUSCI_A0->MCTLW = UCxBRS<<8 | UCxBRF<<4 | EUSCI_A_MCTLW_OS16;
                            break;
                case(UART1):
                            UCA1BR0 = BRDIV & 0xff;
                            UCA1BR1  = BRDIV & 0xff00;
                            EUSCI_A1->MCTLW = UCxBRS<<8 | UCxBRF<<4 | EUSCI_A_MCTLW_OS16;
                            break;
                case(UART2):
                            UCA2BR0 = BRDIV & 0xff;
                            UCA2BR1  = BRDIV & 0xff00;
                            EUSCI_A2->MCTLW = UCxBRS<<8 | UCxBRF<<4 | EUSCI_A_MCTLW_OS16;
                                    break;
                case(UART3):
                            UCA3BR0 = BRDIV & 0xff;
                            UCA3BR1  = BRDIV & 0xff00;
                            EUSCI_A3->MCTLW = UCxBRS<<8 | UCxBRF<<4 | EUSCI_A_MCTLW_OS16;
                            break;
                default:;
        }
    }
    else if(BRCLK == ACLK_FRE){
          //确定BRDIV
           uint16 BRDIV  = (BRCLK/Baunds);
           //确定BRS
           uint16 UCxBRS = UART_BRS_val(Baunds);
           switch(UART_CHA)
           {
                   case(UART0):
                               UCA0BR0 =  BRDIV & 0xff;
                               UCA0BR1  = BRDIV & 0xff00;
                               EUSCI_A0->MCTLW = UCxBRS<<8 ;
                               break;
                   case(UART1):
                               UCA1BR0 = BRDIV & 0xff;
                               UCA1BR1  = BRDIV & 0xff00;
                               EUSCI_A1->MCTLW = UCxBRS<<8 ;
                               break;
                   case(UART2):
                               UCA2BR0 = BRDIV & 0xff;
                               UCA2BR1  = BRDIV & 0xff00;
                               EUSCI_A2->MCTLW = UCxBRS<<8 ;
                                       break;
                   case(UART3):
                               UCA3BR0 = BRDIV & 0xff;
                               UCA3BR1  = BRDIV & 0xff00;
                               EUSCI_A3->MCTLW = UCxBRS<<8 ;
                               break;
                   default:;
           }
    }
}
/*************************************************
 * 函  数  名:UART_init
 * 功       能:串口初始化
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          Baunds:波特率填写
 * 注意事项:无
 *************************************************/
void UART_init(UART_CHA_enum UART_CHA,int Baunds )
{
    UART_PIN_sel(UART_CHA);//初始化对应端口
    __enable_interrupt();//使能总中断
    UART_IRQ_set(UART_CHA);//设置中断优先级
    if((SMCLK_FRE/Baunds)>>4 > 0xff)
    {
        UART_CLK_sel(UART_CHA,UART_ACLK);//选择UART时钟为ACLK
        BRCLK = ACLK_FRE;
    }
    else
    {
        UART_CLK_sel(UART_CHA,UART_SMCLK);//选择UART时钟为SMCLK
        BRCLK = SMCLK_FRE;
    }
    UART_Baunds_set(UART_CHA,Baunds);//绑定波特率
    UART_USIC_init(UART_CHA);//初始化eUSCI
    UART_IRQRX_set(UART_CHA);//接收中断使能

}
/*************************************************
 * 函  数  名:UART_send_Byte
 * 功       能:发送一个字节数据
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          Data:要发送的8位数据
 * 注意事项:无
 *************************************************/
void UART_send_Byte(UART_CHA_enum UART_CHA,uint8 Data)
{
    switch(UART_CHA)
    {
               case(UART0):while(!(EUSCI_A0->IFG&EUSCI_A_IFG_TXIFG));//等待上一次发送完成
                           EUSCI_A0->TXBUF = Data;
                           break;
               case(UART1):
                           while(!(EUSCI_A1->IFG&EUSCI_A_IFG_TXIFG));//等待上一次发送完成
                           EUSCI_A1->TXBUF = Data;
                           break;
               case(UART2):
                           while(!(EUSCI_A2->IFG&EUSCI_A_IFG_TXIFG));//等待上一次发送完成
                           EUSCI_A2->TXBUF = Data;
                           break;
               case(UART3):
                           while(!(EUSCI_A3->IFG&EUSCI_A_IFG_TXIFG));//等待上一次发送完成
                           EUSCI_A3->TXBUF = Data;
                           break;
               default:;
    }
}
/*************************************************
 * 函  数  名:UART_recv_Byte
 * 功       能:接收一个字节数据
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 * 注意事项:无
 *************************************************/
uint8 UART_recv_Byte(UART_CHA_enum UART_CHA)
{
    uint8 result;
    switch(UART_CHA)
   {
              case(UART0):result = EUSCI_A0->RXBUF; break;//取出缓冲区数据
              case(UART1):result = EUSCI_A1->RXBUF; break;//取出缓冲区数据
              case(UART2):result = EUSCI_A2->RXBUF; break;//取出缓冲区数据
              case(UART3):result = EUSCI_A3->RXBUF; break;//取出缓冲区数据
              default:;
   }
    return result;
}
/*************************************************
 * 函  数  名:UART_send_string
 * 功       能:发送一个字符串
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          txt:所要发送的字符串
 * 注意事项:无
 *************************************************/
void UART_send_string(UART_CHA_enum UART_CHA,char*txt)
{
    int i;
    for(i=0;txt[i];i++) {UART_send_Byte(UART_CHA,txt[i]);}
}
/*************************************************
 * 函  数  名:UART_send_short
 * 功       能:发送一个16位整型
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          num:所要发送的16位整型变量
 * 注意事项:从高位开始发送
 *************************************************/
void UART_send_short(UART_CHA_enum UART_CHA,uint16 num)
{
    int i;
   for(i=0;i<2;i++)
   {
       UART_send_Byte(UART_CHA,(num & 0xff00)>>8);
       num = num<<8;
   }
}
/*************************************************
 * 函  数  名:UART_send_int
 * 功       能:发送一个32位整型
 * 参       数:UART_CHA:UART可选通道，在exinuart.h中列出
 *          num:所要发送的32位整型变量
 * 注意事项:从高位开始发送
 *************************************************/
void UART_send_int(UART_CHA_enum UART_CHA,uint32 num)
{
    int i;
    for(i=0;i<4;i++)
    {
        UART_send_Byte(UART_CHA,(num & 0xff000000)>>24);
        num = num<<8;
    }
}
/*************************************************
 * 函  数  名:EUSCIA0_IRQHandler
 * 功       能:串口0服务函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************以下添加用户的处理函数*********************/
        UART_send_Byte(UART0,UART_recv_Byte(UART0));
        /***********************用户处理函数添加结束行*********************/
    }
}
/*************************************************
 * 函  数  名:EUSCIA1_IRQHandler
 * 功       能:串口1服务函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EUSCIA1_IRQHandler(void)
{
    if (EUSCI_A1->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
}
/*************************************************
 * 函  数  名:EUSCIA2_IRQHandler
 * 功       能:串口2服务函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EUSCIA2_IRQHandler(void)
{
    //接收中断,uart接收到字节,接收中断标志位会置1
    if(EUSCI_A2->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
}
/*************************************************
 * 函  数  名:EUSCIA3_IRQHandler
 * 功       能:串口3服务函数
 * 参       数:无
 * 注意事项:无
 *************************************************/
void EUSCIA3_IRQHandler()
{
    if(EUSCI_A3->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************以下添加用户的处理函数*********************/

        /***********************用户处理函数添加结束行*********************/
    }
}
