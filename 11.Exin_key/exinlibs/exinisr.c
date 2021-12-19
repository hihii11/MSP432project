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
#include "exinisr.h"

extern char IRQ3_5flag;
extern char IRQ4_6flag;
extern char A_flag;
extern char B_flag;
extern uint8 dirf;
void PORT1_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);


    if(status & GPIO_PIN1)
    {
        gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);
        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN5)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN6)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}

void PORT2_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);


    if(status & GPIO_PIN1)
    {

        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        encoder_B.dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        if(encoder_B.dir == 1)
            encoder_B.encoder++;
        else
            encoder_B.encoder--;

        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN5)
      {
       // encoder++;
        //dir=gpio_get(GPIO_PORT_P3,GPIO_PIN0);
        /*添加程序*/
      }
    else if(status & GPIO_PIN6)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}

void PORT3_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, status);


    if(status & GPIO_PIN1)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN5)
      {
        //delay_ms(5);
        A_flag=1;
        B_flag=0;
        IRQ3_5flag=1;
      }
    else if(status & GPIO_PIN6)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}
void PORT4_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

    if(status & GPIO_PIN1)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
        encoder_A.dir=gpio_get(GPIO_PORT_P4,GPIO_PIN5);
        if(encoder_A.dir == 1)
            encoder_A.encoder++;
        else
            encoder_A.encoder--;
      }
    else if(status & GPIO_PIN5)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN6)
      {
        //delay_ms(5);
        A_flag=0;
        B_flag=1;
        IRQ4_6flag=1;
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}

void PORT5_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);


    if(status & GPIO_PIN1)
    {
        encoder_D.dir=gpio_get(GPIO_PORT_P5,GPIO_PIN0);
        if(encoder_D.dir == 1)
            encoder_D.encoder++;
        else
            encoder_D.encoder--;
        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN5)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN6)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}

void PORT6_IRQHandler(void)
{
    uint32_t status;
    //  清空标志位
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    if(status & GPIO_PIN0)
    {

            /*添加程序*/
    }
    else if(status & GPIO_PIN1)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN2)
    {
        /*添加程序*/
    }
    else if(status & GPIO_PIN3)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN4)
      {
        /*添加程序*/
      }
    else if(status & GPIO_PIN5)
      {  /*添加程序*/
      }
    else if(status & GPIO_PIN6)
      {
        encoder_C.dir=gpio_get(GPIO_PORT_P6,GPIO_PIN1);
        if(encoder_C.dir == 1)
            encoder_C.encoder++;
        else
            encoder_C.encoder--;
        /*添加程序*/
      }
    else if(status & GPIO_PIN7)
      {
        /*添加程序*/
      }
}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);
}


void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;


    /*添加程序*/
}
void TA2_0_IRQHandler(void) {
    TIMER_A2->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    /*添加程序*/

}

void TA3_0_IRQHandler(void) {
    TIMER_A3->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
}
