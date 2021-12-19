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
#include "exingpio.h"


/******************************/
 /*������: gpio_init
  * ��ʼ��IO��
  *
  * ������ʽ��mode=GPI(����)GPO(���)
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
 /*������: gpio_get
  * ��ȡIO��ֵ
  * ���ȳ�ʼ����IO��
  * ��ʼ������ gpio_init
  */
/*******************************/
uint_fast8_t gpio_get(uint_fast8_t selectedPort,uint_fast16_t selectedPins)
{
    return GPIO_getInputPinValue(selectedPort, selectedPins );
}
/******************************/
 /*������: gpio_set
  * ����IO��ֵ
  * ���ȳ�ʼ����IO��
  * ��ʼ������ gpio_set
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
 /*������: gpio_toggle
  * ��ת���ŵ�ƽ
  */
/*******************************/
void gpio_toggle(uint_fast8_t selectedPort, uint_fast16_t selectedPins)
{
    GPIO_toggleOutputOnPin(selectedPort,selectedPins);
}
/******************************/
 /*������: gpio_edg_sel
  * ѡ���ⲿ�жϴ�����ʽ
  *
  * ������ʽ��mode=FALLING /RISING
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
 /*������:gpio_INT_EN
  * �ж�ʹ��
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
 /*������:gpio_interrupt_INIT
  * ��ʼ���ⲿ�ж�IO��
  * selectedPort-->�˿ں�
  * selectedPins-->���ź�
  *
  * �ж���������exinisr.c��ע��
  */
/*******************************/
void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode)
{
    WDT_A_holdTimer();//�رտ��Ź�
    GPIO_setAsInputPinWithPullUpResistor(selectedPort, selectedPins);//�����ж�ʹ��
    gpio_edg_sel(selectedPort,selectedPins,mode);
    GPIO_clearInterruptFlag(selectedPort, selectedPins);
    GPIO_enableInterrupt(selectedPort, selectedPins);
    //Interrupt_enableInterrupt(INT_PORT1);
    gpio_INT_EN(selectedPort);
    SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);
    Interrupt_enableMaster();

}
