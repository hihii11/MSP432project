/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月20日11:52:41
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exingpio.h"
/*************************************************
 * 函  数  名:gpio_set_Asout
 * 功       能:将GPIO引脚设置为输出
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_set_Asin
 * 功       能:将GPIO引脚设置为输入
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_set_High
 * 功       能:将GPIO引脚设置为高电平
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:当上下拉电阻使能时，该函数可设置使用上拉电阻
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
 * 函  数  名:gpio_set_Low
 * 功       能:将GPIO引脚设置为高电平
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:当上下拉电阻使能时，该函数可设置使用下拉电阻
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
 * 函  数  名:gpio_enable_Ren
 * 功       能:将GPIO引脚上下拉电阻使能
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_disable_Ren
 * 功       能:将GPIO引脚上下拉电阻禁能
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_enable_IRQ
 * 功       能:将GPIO引脚中断使能
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_enable_IRQ
 * 功       能:将GPIO引脚中断禁能
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_clr_GPIOIRQFLG
 * 功       能:将GPIO端口中断标志位清零
 * 参       数:selectedPort:端口号
 * 注意事项:无
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
 * 函  数  名:gpio_edg_sel
 * 功       能:选择GPIO中断方式
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 *          mode:方式选择，在exingpio.h文件枚举
 * 注意事项:无
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
 * 函  数  名:gpio_interrupt_INIT
 * 功       能:GPIO中断设置
 * 参       数: selectedPort:端口号
 *          selectedPins:引脚号
 *          mode：中断触发方式在exingpio.h中列出
 * 注意事项:无
 *************************************************/
void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode)
{
    //首先将GPIO口配置上拉下拉电阻
    gpio_enable_Ren(selectedPort,selectedPins);//使能上下拉电阻
    if(mode == RISING)
        gpio_set_Low(selectedPort,selectedPins);//选择下拉电阻
    else if(mode == FALLING)
        gpio_set_High(selectedPort,selectedPins);//选择上拉电阻
    //其次定义触发类型
    gpio_edg_sel(selectedPort,selectedPins,mode);
    //然后再允许中断前先清除中断标志位
    gpio_clr_GPIOIRQFLG(selectedPort);
    //允许GPIO引脚中断请求
    gpio_enable_IRQ(selectedPort, selectedPins);//NVIC中断使能
    __enable_interrupt();//开启总中断

}
/*************************************************
 * 函  数  名:gpio_init
 * 功       能:初始化gpio口
 * 参       数:selectedPort:端口号
 *          selectedPins:引脚号
 *          MODE:输入输出模式选择，在exingpio.h文件枚举
 *          out_value:当设置成输出时，此位设置输出电平1:高电平 0:低电平
 *                    当设置成输入时，此位设置上下拉电阻 1:上拉 0:下拉
 * 注意事项:无
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
 * 函  数  名:gpio_get
 * 功       能:读取引脚电平
 * 参       数: selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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
 * 函  数  名:gpio_set
 * 功       能:设置引脚电平
 * 参       数: selectedPort:端口号
 *          selectedPins:引脚号
 *          out_value:设置高低电平
 * 注意事项:无
 *************************************************/
void gpio_set(uint_fast8_t selectedPort,uint_fast16_t selectedPins,unsigned int out_value)
{
    if(out_value)
        gpio_set_High(selectedPort,selectedPins);
    else
        gpio_set_Low(selectedPort,selectedPins);
}
/*************************************************
 * 函  数  名:gpio_toggle
 * 功       能:翻转引脚电平
 * 参       数: selectedPort:端口号
 *          selectedPins:引脚号
 * 注意事项:无
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





