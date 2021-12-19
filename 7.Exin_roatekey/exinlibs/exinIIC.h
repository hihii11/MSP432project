/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日21:10:17
-------------------------------------------------------------------------------------------------------*/

#ifndef _exinIIC_H_
#define _exinIIC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define IIC_SCL_PORT         GPIO_PORT_P6
#define IIC_SCL_PIN          GPIO_PIN4  //P6.4

#define IIC_SDA_PORT         GPIO_PORT_P6
#define IIC_SDA_PIN          GPIO_PIN5  //P6.5

#define IIC_SCL_OUT           gpio_init(IIC_SCL_PORT,IIC_SCL_PIN,GPO,1)
#define IIC_SCL_IN            gpio_init(IIC_SCL_PORT,IIC_SCL_PIN,GPI,1)
#define IIC_SDA_OUT           gpio_init(IIC_SDA_PORT,IIC_SDA_PIN,GPO,0)
#define IIC_SDA_IN            gpio_init(IIC_SDA_PORT,IIC_SDA_PIN,GPI,0)

#define IIC_SCL_HIGH          gpio_set(IIC_SCL_PORT,IIC_SCL_PIN,1)
#define IIC_SCL_LOW           gpio_set(IIC_SCL_PORT,IIC_SCL_PIN,0)

#define IIC_SDA_HIGH          gpio_set(IIC_SDA_PORT,IIC_SDA_PIN,1)
#define IIC_SDA_LOW           gpio_set(IIC_SDA_PORT,IIC_SDA_PIN,0)

#define IIC_SDA_READ          gpio_get(IIC_SDA_PORT,IIC_SDA_PIN)
#define IIC_SCL_READ          gpio_get(IIC_SCL_PORT,IIC_SCL_PIN)

#define IIC_delay            delay_us(20)

uint8 IIC_DATA;

extern void IIC_init();
extern void IIC_start();
extern void IIC_stop();
extern void IIC_ACK();
extern void IIC_NACK();
extern unsigned char Check_ACK();
extern void IIC_Send_Byte(uint8 Data);
extern unsigned char IIC_Read_Byte(uint8 ack);
extern void IIC_reset();

#ifdef __cplusplus
}
#endif

#endif

