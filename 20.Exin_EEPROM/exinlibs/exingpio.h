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
#ifndef _exingpio_h
#define _exingpio_h
#ifdef __cplusplus
extern "C"
{
#endif


typedef enum{
    FALLING,//�½���
    RISING//������
}GPIO_INT_MODE;//PWM(���)˫ͨ�����ö��A,BΪ˫ͨ����,CΪ��ͨ��


typedef enum{
    GPI,//�½���
    GPO//������
}GPIO_DIR_MODE;//PWM(���)˫ͨ�����ö��A,BΪ˫ͨ����,CΪ��ͨ��

extern void gpio_toggle(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
extern void gpio_INT_EN(uint_fast8_t selectedPort);
extern void gpio_init(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_DIR_MODE MDOE,unsigned int out_value);
extern void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode);
extern void gpio_edg_sel(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode);
extern void gpio_set(uint_fast8_t selectedPort,uint_fast16_t selectedPins,unsigned int out_value);
extern uint_fast8_t gpio_get(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
