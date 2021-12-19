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
#include "exingpio.h"


/******************************/
 /*函数名: gpio_init
  * 初始化IO口
  *
  * 触发方式：mode=GPI(输入)GPO(输出)
  */
/*******************************/
void gpio_init(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_DIR_MODE MODE,unsigned int out_value)
{
    switch(MODE)
    {
        case(GPO): GPIO_setAsOutputPin(selectedPort,selectedPins);
                    if(out_value)
                        GPIO_setOutputHighOnPin(selectedPort,selectedPins);
                    else
                        GPIO_setOutputLowOnPin(selectedPort,selectedPins);
        break;
        case(GPI): GPIO_setAsInputPin(selectedPort,selectedPins);
                     if(out_value)
                        GPIO_setOutputHighOnPin(selectedPort,selectedPins);
                     else
                        GPIO_setOutputLowOnPin(selectedPort,selectedPins);
        break;
    }
}

/******************************/
 /*函数名: gpio_get
  * 获取IO口值
  * 需先初始化该IO口
  * 初始化函数 gpio_init
  */
/*******************************/
uint_fast8_t gpio_get(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    return GPIO_getInputPinValue(selectedPort, selectedPins );
}
/******************************/
 /*函数名: gpio_set
  * 设置IO口值
  * 需先初始化该IO口
  * 初始化函数 gpio_set
  */
/*******************************/
void gpio_set(uint_fast8_t selectedPort,uint_fast16_t selectedPins,unsigned int out_value)
{
    if(out_value)
        GPIO_setOutputHighOnPin(selectedPort,selectedPins);
    else
        GPIO_setOutputLowOnPin(selectedPort,selectedPins);
}
/******************************/
 /*函数名: gpio_toggle
  * 翻转引脚电平
  */
/*******************************/
void gpio_toggle(uint_fast8_t selectedPort, uint_fast16_t selectedPins)
{
    GPIO_toggleOutputOnPin(selectedPort,selectedPins);
}
/******************************/
 /*函数名: gpio_edg_sel
  * 选择外部中断触发方式
  *
  * 触发方式：mode=FALLING /RISING
  */
/*******************************/
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

/******************************/
 /*函数名:gpio_INT_EN
  * 中断使能
  */
/*******************************/
void gpio_INT_EN(uint_fast8_t selectedPort)
{
    switch(selectedPort)
    {
        case(GPIO_PORT_P1):Interrupt_enableInterrupt(INT_PORT1);break;
        case(GPIO_PORT_P2):Interrupt_enableInterrupt(INT_PORT2);break;
        case(GPIO_PORT_P3):Interrupt_enableInterrupt(INT_PORT3);break;
        case(GPIO_PORT_P4):Interrupt_enableInterrupt(INT_PORT4);break;
        case(GPIO_PORT_P5):Interrupt_enableInterrupt(INT_PORT5);break;
        case(GPIO_PORT_P6):Interrupt_enableInterrupt(INT_PORT6);break;
    }
}

/******************************/
 /*函数名:gpio_interrupt_INIT
  * 初始化外部中断IO口
  * selectedPort-->端口号
  * selectedPins-->引脚号
  *
  * 中断向量表在exinisr.c中注册
  */
/*******************************/
void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode)
{
    WDT_A_holdTimer();//关闭看门狗
    GPIO_setAsInputPinWithPullUpResistor(selectedPort, selectedPins);//允许中断使能
    gpio_edg_sel(selectedPort,selectedPins,mode);
    GPIO_clearInterruptFlag(selectedPort, selectedPins);
    GPIO_enableInterrupt(selectedPort, selectedPins);
    //Interrupt_enableInterrupt(INT_PORT1);
    gpio_INT_EN(selectedPort);
    SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);
    Interrupt_enableMaster();

}
