/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��20��11:52:41
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exingpio.h"
/*************************************************
 * ��  ��  ��:gpio_set_Asout
 * ��       ��:��GPIO��������Ϊ���
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_set_Asout(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
          case(GPIO_PORT_P1):P1->DIR |= selectedPins; break;
          case(GPIO_PORT_P2):P2->DIR |= selectedPins; break;
          case(GPIO_PORT_P3):P3->DIR |= selectedPins; break;
          case(GPIO_PORT_P4):P4->DIR |= selectedPins; break;
          case(GPIO_PORT_P5):P5->DIR |= selectedPins; break;
          case(GPIO_PORT_P6):P6->DIR |= selectedPins; break;
          case(GPIO_PORT_P7):P7->DIR |= selectedPins; break;
          case(GPIO_PORT_P8):P8->DIR |= selectedPins; break;
          case(GPIO_PORT_P9):P9->DIR |= selectedPins; break;
          case(GPIO_PORT_P10):P10->DIR |= selectedPins; break;
          default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_set_Asin
 * ��       ��:��GPIO��������Ϊ����
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_set_Asin(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
          case(GPIO_PORT_P1):P1->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P2):P2->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P3):P3->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P4):P4->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P5):P5->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P6):P6->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P7):P7->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P8):P8->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P9):P9->DIR &= ~selectedPins; break;
          case(GPIO_PORT_P10):P10->DIR &= ~selectedPins; break;
          default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_set_High
 * ��       ��:��GPIO��������Ϊ�ߵ�ƽ
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:������������ʹ��ʱ���ú���������ʹ����������
 *************************************************/
void gpio_set_High(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
            case(GPIO_PORT_P1):P1->OUT |= selectedPins; break;
            case(GPIO_PORT_P2):P2->OUT |= selectedPins; break;
            case(GPIO_PORT_P3):P3->OUT |= selectedPins; break;
            case(GPIO_PORT_P4):P4->OUT |= selectedPins; break;
            case(GPIO_PORT_P5):P5->OUT |= selectedPins; break;
            case(GPIO_PORT_P6):P6->OUT |= selectedPins; break;
            case(GPIO_PORT_P7):P7->OUT |= selectedPins; break;
            case(GPIO_PORT_P8):P8->OUT |= selectedPins; break;
            case(GPIO_PORT_P9):P9->OUT |= selectedPins; break;
            case(GPIO_PORT_P10):P10->OUT |= selectedPins; break;
            default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_set_Low
 * ��       ��:��GPIO��������Ϊ�ߵ�ƽ
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:������������ʹ��ʱ���ú���������ʹ����������
 *************************************************/
void gpio_set_Low(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
            case(GPIO_PORT_P1):P1->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P2):P2->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P3):P3->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P4):P4->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P5):P5->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P6):P6->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P7):P7->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P8):P8->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P9):P9->OUT &= ~selectedPins; break;
            case(GPIO_PORT_P10):P10->OUT &= ~selectedPins; break;
            default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_enable_Ren
 * ��       ��:��GPIO��������������ʹ��
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_enable_Ren(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
           case(GPIO_PORT_P1):P1->REN |= selectedPins; break;
           case(GPIO_PORT_P2):P2->REN |= selectedPins; break;
           case(GPIO_PORT_P3):P3->REN |= selectedPins; break;
           case(GPIO_PORT_P4):P4->REN |= selectedPins; break;
           case(GPIO_PORT_P5):P5->REN |= selectedPins; break;
           case(GPIO_PORT_P6):P6->REN |= selectedPins; break;
           case(GPIO_PORT_P7):P7->REN |= selectedPins; break;
           case(GPIO_PORT_P8):P8->REN |= selectedPins; break;
           case(GPIO_PORT_P9):P9->REN |= selectedPins; break;
           case(GPIO_PORT_P10):P10->REN |= selectedPins; break;
           default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_disable_Ren
 * ��       ��:��GPIO�����������������
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_disable_Ren(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
      {
            case(GPIO_PORT_P1):P1->REN &= ~selectedPins; break;
            case(GPIO_PORT_P2):P2->REN &= ~selectedPins; break;
            case(GPIO_PORT_P3):P3->REN &= ~selectedPins; break;
            case(GPIO_PORT_P4):P4->REN &= ~selectedPins; break;
            case(GPIO_PORT_P5):P5->REN &= ~selectedPins; break;
            case(GPIO_PORT_P6):P6->REN &= ~selectedPins; break;
            case(GPIO_PORT_P7):P7->REN &= ~selectedPins; break;
            case(GPIO_PORT_P8):P8->REN &= ~selectedPins; break;
            case(GPIO_PORT_P9):P9->REN &= ~selectedPins; break;
            case(GPIO_PORT_P10):P10->REN &= ~selectedPins; break;
            default:;
      }
}
/*************************************************
 * ��  ��  ��:gpio_enable_IRQ
 * ��       ��:��GPIO�����ж�ʹ��
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_enable_IRQ(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
     {
           case(GPIO_PORT_P1):P1->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31); break;
           case(GPIO_PORT_P2):P2->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT2_IRQn) & 31); break;
           case(GPIO_PORT_P3):P3->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT3_IRQn) & 31); break;
           case(GPIO_PORT_P4):P4->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31); break;
           case(GPIO_PORT_P5):P5->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31); break;
           case(GPIO_PORT_P6):P6->IE |= selectedPins;NVIC->ISER[1] = 1 << ((PORT6_IRQn) & 31); break;
           default:;
     }
}
/*************************************************
 * ��  ��  ��:gpio_enable_IRQ
 * ��       ��:��GPIO�����жϽ���
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_disable_IRQ(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    switch(selectedPort)
     {
           case(GPIO_PORT_P1):P1->IE &= ~selectedPins; break;
           case(GPIO_PORT_P2):P2->IE &= ~selectedPins; break;
           case(GPIO_PORT_P3):P3->IE &= ~selectedPins; break;
           case(GPIO_PORT_P4):P4->IE &= ~selectedPins; break;
           case(GPIO_PORT_P5):P5->IE &= ~selectedPins; break;
           case(GPIO_PORT_P6):P6->IE &= ~selectedPins; break;
           default:;
     }
}
/*************************************************
 * ��  ��  ��:gpio_clr_GPIOIRQFLG
 * ��       ��:��GPIO�˿��жϱ�־λ����
 * ��       ��:selectedPort:�˿ں�
 * ע������:��
 *************************************************/
void gpio_clr_GPIOIRQFLG(uint_fast8_t selectedPort)
{
    switch(selectedPort)
     {
           case(GPIO_PORT_P1):P1->IFG = 0x00; break;
           case(GPIO_PORT_P2):P2->IFG = 0x00; break;
           case(GPIO_PORT_P3):P3->IFG = 0x00; break;
           case(GPIO_PORT_P4):P4->IFG = 0x00; break;
           case(GPIO_PORT_P5):P5->IFG = 0x00; break;
           case(GPIO_PORT_P6):P6->IFG = 0x00; break;
           default:;
     }
}

/*************************************************
 * ��  ��  ��:gpio_edg_sel
 * ��       ��:ѡ��GPIO�жϷ�ʽ
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 *          mode:��ʽѡ����exingpio.h�ļ�ö��
 * ע������:��
 *************************************************/
void gpio_edg_sel(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode)
{
    switch(selectedPort)
    {
        case(GPIO_PORT_P1):
                                if(mode==FALLING)
                                    P1->IES |= selectedPins;
                                else if(mode==RISING)
                                    P1->IES &= ~selectedPins;
                                break;
        case(GPIO_PORT_P2):
                               if(mode==FALLING)
                                   P2->IES |= selectedPins;
                               else if(mode==RISING)
                                   P2->IES &= ~selectedPins;
                               break;
        case(GPIO_PORT_P3):
                               if(mode==FALLING)
                                   P3->IES |= selectedPins;
                               else if(mode==RISING)
                                   P3->IES &= ~selectedPins;
                               break;
        case(GPIO_PORT_P4):
                               if(mode==FALLING)
                                   P4->IES |= selectedPins;
                               else if(mode==RISING)
                                   P4->IES &= ~selectedPins;
                               break;
        case(GPIO_PORT_P5):
                               if(mode==FALLING)
                                   P5->IES |= selectedPins;
                               else if(mode==RISING)
                                   P5->IES &= ~selectedPins;
                               break;
        case(GPIO_PORT_P6):
                               if(mode==FALLING)
                                   P6->IES |= selectedPins;
                               else if(mode==RISING)
                                   P6->IES &= ~selectedPins;
                               break;
    }
}
/*************************************************
 * ��  ��  ��:gpio_interrupt_INIT
 * ��       ��:GPIO�ж�����
 * ��       ��: selectedPort:�˿ں�
 *          selectedPins:���ź�
 *          mode���жϴ�����ʽ��exingpio.h���г�
 * ע������:��
 *************************************************/
void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode)
{
    //���Ƚ�GPIO������������������
    gpio_enable_Ren(selectedPort,selectedPins);//ʹ������������
    if(mode == RISING)
        gpio_set_Low(selectedPort,selectedPins);//ѡ����������
    else if(mode == FALLING)
        gpio_set_High(selectedPort,selectedPins);//ѡ����������
    //��ζ��崥������
    gpio_edg_sel(selectedPort,selectedPins,mode);
    //Ȼ���������ж�ǰ������жϱ�־λ
    gpio_clr_GPIOIRQFLG(selectedPort);
    //����GPIO�����ж�����
    gpio_enable_IRQ(selectedPort, selectedPins);//NVIC�ж�ʹ��
    __enable_interrupt();//�������ж�

}
/*************************************************
 * ��  ��  ��:gpio_init
 * ��       ��:��ʼ��gpio��
 * ��       ��:selectedPort:�˿ں�
 *          selectedPins:���ź�
 *          MODE:�������ģʽѡ����exingpio.h�ļ�ö��
 *          out_value:�����ó����ʱ����λ���������ƽ1:�ߵ�ƽ 0:�͵�ƽ
 *                    �����ó�����ʱ����λ�������������� 1:���� 0:����
 * ע������:��
 *************************************************/
void gpio_init(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_DIR_MODE MODE,unsigned int out_value)
{
    switch(MODE)
    {
        case(GPO):
                       gpio_set_Asout(selectedPort,selectedPins);
                       gpio_disable_Ren(selectedPort,selectedPins);
                       if(out_value)
                           gpio_set_High(selectedPort,selectedPins);
                       else
                           gpio_set_Low(selectedPort,selectedPins);
        break;
        case(GPI):
                        gpio_set_Asin(selectedPort,selectedPins);
                        gpio_enable_Ren(selectedPort,selectedPins);
                        if(out_value)
                            gpio_set_High(selectedPort,selectedPins);
                        else
                            gpio_set_Low(selectedPort,selectedPins);
        break;
    }
}
/*************************************************
 * ��  ��  ��:gpio_get
 * ��       ��:��ȡ���ŵ�ƽ
 * ��       ��: selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
uint_fast8_t gpio_get(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    uint8 staus = 0;
    switch(selectedPort)
    {
               case(GPIO_PORT_P1):staus = (P1->IN)&selectedPins; break;
               case(GPIO_PORT_P2):staus = (P2->IN)&selectedPins; break;
               case(GPIO_PORT_P3):staus = (P3->IN)&selectedPins; break;
               case(GPIO_PORT_P4):staus = (P4->IN)&selectedPins;  break;
               case(GPIO_PORT_P5):staus = (P5->IN)&selectedPins;  break;
               case(GPIO_PORT_P6):staus = (P6->IN)&selectedPins;  break;
               case(GPIO_PORT_P7):staus = (P7->IN)&selectedPins;  break;
               case(GPIO_PORT_P8):staus = (P8->IN)&selectedPins;  break;
               case(GPIO_PORT_P9):staus = (P9->IN)&selectedPins;  break;
               case(GPIO_PORT_P10):staus = (P10->IN)&selectedPins;  break;
               default:staus = 0x00 ;
    }
    return (staus==0)? 0:1;
}
/*************************************************
 * ��  ��  ��:gpio_set
 * ��       ��:�������ŵ�ƽ
 * ��       ��: selectedPort:�˿ں�
 *          selectedPins:���ź�
 *          out_value:���øߵ͵�ƽ
 * ע������:��
 *************************************************/
void gpio_set(uint_fast8_t selectedPort,uint_fast16_t selectedPins,unsigned int out_value)
{
    if(out_value)
        gpio_set_High(selectedPort,selectedPins);
    else
        gpio_set_Low(selectedPort,selectedPins);
}
/*************************************************
 * ��  ��  ��:gpio_toggle
 * ��       ��:��ת���ŵ�ƽ
 * ��       ��: selectedPort:�˿ں�
 *          selectedPins:���ź�
 * ע������:��
 *************************************************/
void gpio_toggle(uint_fast8_t selectedPort, uint_fast16_t selectedPins)
{
    switch(selectedPort)
   {
              case(GPIO_PORT_P1):P1->OUT ^= selectedPins; break;
              case(GPIO_PORT_P2):P2->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P3):P3->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P4):P4->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P5):P5->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P6):P6->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P7):P7->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P8):P8->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P9):P9->OUT ^= selectedPins;  break;
              case(GPIO_PORT_P10):P10->OUT ^= selectedPins;  break;
              default:;
   }
}





