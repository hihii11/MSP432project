/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月16日20:16:28
-------------------------------------------------------------------------------------------------------*/

#ifndef EXINADC0832_H_
#define EXINADC0832_H_
#ifdef __cplusplus
extern "C"
{
#endif

//ADC0832 通道枚举
typedef enum{
    CH0=0,//0通道
    CH1,  //1通道
    CH2,  //2通道
    CH3   //3通道
}ADC0832_CH;

//ADC0832 工作模式枚举
typedef enum{
    SINGLE=0,//A通道
    DUAL,    //B通道
}ADC0832_MOD;


#define ADC0832_VREF              5.0        //ADC0832参考电压
#define ADC0832_PREC              256        //ADC0832分辨率
//第一片0832引脚宏定义
#define ADC0832_DI0_PORT          GPIO_PORT_P9
#define ADC0832_DI0_PIN           GPIO_PIN5  //P9.5
#define ADC0832_DO0_PORT          GPIO_PORT_P7
#define ADC0832_DO0_PIN           GPIO_PIN0  //P7.0
#define ADC0832_CK0_PORT          GPIO_PORT_P7
#define ADC0832_CK0_PIN           GPIO_PIN1  //P7.1
#define ADC0832_CS0_PORT          GPIO_PORT_P7
#define ADC0832_CS0_PIN           GPIO_PIN2  //P7.2
//第二片0832引脚宏定义
#define ADC0832_DI1_PORT          GPIO_PORT_P7
#define ADC0832_DI1_PIN           GPIO_PIN3  //P7.3
#define ADC0832_DO1_PORT          GPIO_PORT_P6
#define ADC0832_DO1_PIN           GPIO_PIN3  //P6.3
#define ADC0832_CK1_PORT          GPIO_PORT_P9
#define ADC0832_CK1_PIN           GPIO_PIN3  //P9.3
#define ADC0832_CS1_PORT          GPIO_PORT_P6
#define ADC0832_CS1_PIN           GPIO_PIN2  //P6.2


//第一片相关电平逻辑宏定义
#define DI0_OUT                   gpio_init(ADC0832_DI0_PORT,ADC0832_DI0_PIN,GPO,0)
#define DI0_IN                    gpio_init(ADC0832_DI0_PORT,ADC0832_DI0_PIN,GPI,0)
#define DO0_OUT                   gpio_init(ADC0832_DO0_PORT,ADC0832_DO0_PIN,GPO,0)
#define DO0_IN                    gpio_init(ADC0832_DO0_PORT,ADC0832_DO0_PIN,GPI,0)
#define CK0_OUT                   gpio_init(ADC0832_CK0_PORT,ADC0832_CK0_PIN,GPO,0)
#define CK0_IN                    gpio_init(ADC0832_CK0_PORT,ADC0832_CK0_PIN,GPI,0)
#define CS0_OUT                   gpio_init(ADC0832_CS0_PORT,ADC0832_CS0_PIN,GPO,1)
#define CS0_IN                    gpio_init(ADC0832_CS0_PORT,ADC0832_CS0_PIN,GPI,0)

#define DI0_LOW                   gpio_set(ADC0832_DI0_PORT,ADC0832_DI0_PIN,0)
#define DI0_HIGH                  gpio_set(ADC0832_DI0_PORT,ADC0832_DI0_PIN,1)

#define DO0_READ                  gpio_get(ADC0832_DO0_PORT,ADC0832_DO0_PIN)

#define CK0_LOW                   gpio_set(ADC0832_CK0_PORT,ADC0832_CK0_PIN,0)
#define CK0_HIGH                  gpio_set(ADC0832_CK0_PORT,ADC0832_CK0_PIN,1)

#define CS0_LOW                   gpio_set(ADC0832_CS0_PORT,ADC0832_CS0_PIN,0)
#define CS0_HIGH                  gpio_set(ADC0832_CS0_PORT,ADC0832_CS0_PIN,1)

//第二片相关电平逻辑宏定义
#define DI1_OUT                   gpio_init(ADC0832_DI1_PORT,ADC0832_DI1_PIN,GPO,0)
#define DI1_IN                    gpio_init(ADC0832_DI1_PORT,ADC0832_DI1_PIN,GPI,0)
#define DO1_OUT                   gpio_init(ADC0832_DO1_PORT,ADC0832_DO1_PIN,GPO,0)
#define DO1_IN                    gpio_init(ADC0832_DO1_PORT,ADC0832_DO1_PIN,GPI,0)
#define CK1_OUT                   gpio_init(ADC0832_CK1_PORT,ADC0832_CK1_PIN,GPO,0)
#define CK1_IN                    gpio_init(ADC0832_CK1_PORT,ADC0832_CK1_PIN,GPI,0)
#define CS1_OUT                   gpio_init(ADC0832_CS1_PORT,ADC0832_CS1_PIN,GPO,1)
#define CS1_IN                    gpio_init(ADC0832_CS1_PORT,ADC0832_CS1_PIN,GPI,0)

#define DI1_LOW                   gpio_set(ADC0832_DI1_PORT,ADC0832_DI1_PIN,0)
#define DI1_HIGH                  gpio_set(ADC0832_DI1_PORT,ADC0832_DI1_PIN,1)

#define DO1_READ                  gpio_get(ADC0832_DO1_PORT,ADC0832_DO1_PIN)

#define CK1_LOW                   gpio_set(ADC0832_CK1_PORT,ADC0832_CK1_PIN,0)
#define CK1_HIGH                  gpio_set(ADC0832_CK1_PORT,ADC0832_CK1_PIN,1)

#define CS1_LOW                   gpio_set(ADC0832_CS1_PORT,ADC0832_CS1_PIN,0)
#define CS1_HIGH                  gpio_set(ADC0832_CS1_PORT,ADC0832_CS1_PIN,1)


#define ADC0832_delay             delay_us(1);//0832延时



extern void ADC0832_init(ADC0832_CH ADC0832_CHA);
extern void ADC0832_enable(ADC0832_CH ADC0832_CHA);
extern void ADC0832_disable(ADC0832_CH ADC0832_CHA);
extern void ADC0832_write_DI(ADC0832_CH ADC0832_CHA , uint8 DI_data);
extern void ADC0832_CHA_sel(ADC0832_CH ADC0832_CHA , ADC0832_MOD ADC0832_MODE);
extern uint8 ADC0832_read_Byte(ADC0832_CH ADC0832_CHA , ADC0832_MOD ADC0832_MODE , uint8 CHECK);
extern float get_voltage(int ADC_dat , float vref , int prec);

#ifdef __cplusplus
}
#endif

#endif /* EXINADC0832_H_ */
