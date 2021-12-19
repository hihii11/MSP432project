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
volatile uint8_t UART3_RXDat= 0;
volatile uint8_t UART2_RXDat= 0;
volatile uint8_t UART0_RXDat= 0;

/*************************************************
 * ��  ��  ��:UART_IRQ_set
 * ��       ��:UART�ж�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:��
 *************************************************/
void UART_IRQ_set(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
    {
           case(UART0):EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); break;
           case(UART1):EUSCI_A1->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] = 1 << ((EUSCIA1_IRQn) & 31); break;
           case(UART2):EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] = 1 << ((EUSCIA2_IRQn) & 31); break;
           case(UART3):EUSCI_A3->CTLW0 |= EUSCI_A_CTLW0_SWRST;NVIC->ISER[0] = 1 << ((EUSCIA3_IRQn) & 31); break;
           default:;
    }
}
/*************************************************
 * ��  ��  ��:UART_IRQRX_set
 * ��       ��:UART�����ж�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:��
 *************************************************/
void UART_IRQRX_set(UART_CHA_enum UART_CHA)
{
    switch(UART_CHA)
    {
           case(UART0):EUSCI_A0->IE |= EUSCI_A_IE_RXIE; break;//����A0�����ж�
           case(UART1):EUSCI_A1->IE |= EUSCI_A_IE_RXIE; break;//����A1�����ж�
           case(UART2):EUSCI_A2->IE |= EUSCI_A_IE_RXIE; break;//����A2�����ж�
           case(UART3):EUSCI_A3->IE |= EUSCI_A_IE_RXIE; break;//����A3�����ж�
           default:;
    }
}
/*************************************************
 * ��  ��  ��:UART_USIC_init
 * ��       ��:eUSIC��ʼ������
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:��
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
 * ��  ��  ��:UART_PIN_sel
 * ��       ��:UART���ų�ʼ��
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:
 *          ͨ��            rx     tx
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
 * ��  ��  ��:UART_CLK_sel
 * ��       ��:UARTʱ��ѡ��
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          UART_CLK:UART��ѡʱ�ӣ���exinuart.h���г�
 * ע������:Ĭ��ѡ��UCLK
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
 * ��  ��  ��:UART_Baunds_set
 * ��       ��:UART����������
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          Baunds:��������д
 * ע������:��ʱ��Ϊ3Mhzʱ������������ܳ���115200
            BRDIV  = (int)(f(clk)/Baunds/16) ;�Ƚϴ��Եķ�Ƶϵ��
 *          UCxBRF = (int) (((f(clk)/Baunds/16) - BRDIV)*16+0.5)
 *          UCxBRS = (int)(((((f(clk)/Baunds/16) - BRDIV)*16+0.5) - UCxBRF)*16 + 0.5)
 *************************************************/
void UART_Baunds_set(UART_CHA_enum UART_CHA,int Baunds )
{
    uint16 BRDIV  = (SMCLK_FRE/Baunds)>>4;
    uint16 UCxBRF = (int)(((float)SMCLK_FRE/Baunds/16-SMCLK_FRE/Baunds/16)*16+0.5);
    uint16 UCxBRS = (int)(((((float)SMCLK_FRE/Baunds/16-SMCLK_FRE/Baunds/16)*16+0.5)-UCxBRF)*16+0.5);
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
/*************************************************
 * ��  ��  ��:UART_init
 * ��       ��:���ڳ�ʼ��
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          Baunds:��������д
 * ע������:��
 *************************************************/
void UART_init(UART_CHA_enum UART_CHA,int Baunds )
{
    UART_PIN_sel(UART_CHA);//��ʼ����Ӧ�˿�
    __enable_interrupt();//ʹ�����ж�
    UART_IRQ_set(UART_CHA);//�����ж����ȼ�
    UART_CLK_sel(UART_CHA,UART_SMCLK);//ѡ��UARTʱ��ΪSMCLK
    UART_Baunds_set(UART_CHA,Baunds);//�󶨲�����
    UART_USIC_init(UART_CHA);//��ʼ��eUSCI
    UART_IRQRX_set(UART_CHA);//�����ж�ʹ��

}
/*************************************************
 * ��  ��  ��:UART_send_Byte
 * ��       ��:����һ���ֽ�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          Data:Ҫ���͵�8λ����
 * ע������:��
 *************************************************/
void UART_send_Byte(UART_CHA_enum UART_CHA,uint8 Data)
{
    switch(UART_CHA)
    {
               case(UART0):while(!(EUSCI_A0->IFG&EUSCI_A_IFG_TXIFG));//�ȴ���һ�η������
                           EUSCI_A0->TXBUF = Data;
                           break;
               case(UART1):
                           while(!(EUSCI_A1->IFG&EUSCI_A_IFG_TXIFG));//�ȴ���һ�η������
                           EUSCI_A1->TXBUF = Data;
                           break;
               case(UART2):
                           while(!(EUSCI_A2->IFG&EUSCI_A_IFG_TXIFG));//�ȴ���һ�η������
                           EUSCI_A2->TXBUF = Data;
                           break;
               case(UART3):
                           while(!(EUSCI_A3->IFG&EUSCI_A_IFG_TXIFG));//�ȴ���һ�η������
                           EUSCI_A3->TXBUF = Data;
                           break;
               default:;
    }
}
/*************************************************
 * ��  ��  ��:UART_recv_Byte
 * ��       ��:����һ���ֽ�����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 * ע������:��
 *************************************************/
uint8 UART_recv_Byte(UART_CHA_enum UART_CHA)
{
    uint8 result;
    switch(UART_CHA)
   {
              case(UART0):result = EUSCI_A0->RXBUF; break;//ȡ������������
              case(UART1):result = EUSCI_A1->RXBUF; break;//ȡ������������
              case(UART2):result = EUSCI_A2->RXBUF; break;//ȡ������������
              case(UART3):result = EUSCI_A3->RXBUF; break;//ȡ������������
              default:;
   }
    return result;
}
/*************************************************
 * ��  ��  ��:UART_send_string
 * ��       ��:����һ���ַ���
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          txt:��Ҫ���͵��ַ���
 * ע������:��
 *************************************************/
void UART_send_string(UART_CHA_enum UART_CHA,char*txt)
{
    int i;
    for(i=0;txt[i];i++) {UART_send_Byte(UART_CHA,txt[i]);}
}
/*************************************************
 * ��  ��  ��:UART_send_short
 * ��       ��:����һ��16λ����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          num:��Ҫ���͵�16λ���ͱ���
 * ע������:�Ӹ�λ��ʼ����
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
 * ��  ��  ��:UART_send_int
 * ��       ��:����һ��32λ����
 * ��       ��:UART_CHA:UART��ѡͨ������exinuart.h���г�
 *          num:��Ҫ���͵�32λ���ͱ���
 * ע������:�Ӹ�λ��ʼ����
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
 * ��  ��  ��:EUSCIA0_IRQHandler
 * ��       ��:����0������
 * ��       ��:��
 * ע������:��
 *************************************************/
void EUSCIA0_IRQHandler(void)
{
    if (EUSCI_A0->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
}
/*************************************************
 * ��  ��  ��:EUSCIA1_IRQHandler
 * ��       ��:����1������
 * ��       ��:��
 * ע������:��
 *************************************************/
void EUSCIA1_IRQHandler(void)
{
    if (EUSCI_A1->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
}
/*************************************************
 * ��  ��  ��:EUSCIA2_IRQHandler
 * ��       ��:����2������
 * ��       ��:��
 * ע������:��
 *************************************************/
void EUSCIA2_IRQHandler(void)
{
    //�����ж�,uart���յ��ֽ�,�����жϱ�־λ����1
    if(EUSCI_A2->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
}
/*************************************************
 * ��  ��  ��:EUSCIA3_IRQHandler
 * ��       ��:����3������
 * ��       ��:��
 * ע������:��
 *************************************************/
void EUSCIA3_IRQHandler()
{
    if(EUSCI_A3->IFG & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        /***********************��������û��Ĵ�����*********************/

        /***********************�û���������ӽ�����*********************/
    }
}
