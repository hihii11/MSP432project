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
#ifndef _exingpio_h
#define _exingpio_h
#ifdef __cplusplus
extern "C"
{
#endif


typedef enum{
    FALLING,//下降沿
    RISING//上升沿
}GPIO_INT_MODE;//PWM(电机)双通道输出枚举A,B为双通道口,C为单通道


typedef enum{
    GPI,//下降沿
    GPO//上升沿
}GPIO_DIR_MODE;//PWM(电机)双通道输出枚举A,B为双通道口,C为单通道
extern void gpio_set_Asout(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_set_Asin(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_set_High(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_set_Low(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_enable_Ren(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_disable_Ren(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_enable_IRQ();
extern void gpio_disable_IRQ(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
extern void gpio_clr_GPIOIRQFLG(uint_fast8_t selectedPort);


extern void gpio_toggle(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
extern void gpio_init(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_DIR_MODE MDOE,unsigned int out_value);
extern void gpio_interrupt_INIT(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode);
extern void gpio_edg_sel(uint_fast8_t selectedPort,uint_fast16_t selectedPins,GPIO_INT_MODE mode);
extern void gpio_set(uint_fast8_t selectedPort,uint_fast16_t selectedPins,unsigned int out_value);
extern uint_fast8_t gpio_get(uint_fast8_t selectedPort,uint_fast16_t selectedPins);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
