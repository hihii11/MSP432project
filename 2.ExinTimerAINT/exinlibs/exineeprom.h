/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��15��21:11:15
-------------------------------------------------------------------------------------------------------*/

#ifndef _exineeprom_H_
#define _exineeprom_H_
#ifdef __cplusplus
extern "C"
{
#endif

//EEPROM IIC���Ŷ���
#define EROM_SCL_PORT          GPIO_PORT_P9
#define EROM_SCL_PIN           GPIO_PIN2  //P9.2

#define EROM_SDA_PORT          GPIO_PORT_P8
#define EROM_SDA_PIN           GPIO_PIN2  //P8.2

#define EROM_SCL_OUT           gpio_init(EROM_SCL_PORT,EROM_SCL_PIN,GPO,1)
#define EROM_SCL_IN            gpio_init(EROM_SCL_PORT,EROM_SCL_PIN,GPI,1)
#define EROM_SDA_OUT           gpio_init(EROM_SDA_PORT,EROM_SDA_PIN,GPO,0)
#define EROM_SDA_IN            gpio_init(EROM_SDA_PORT,EROM_SDA_PIN,GPI,0)

#define EROM_SCL_HIGH          gpio_set(EROM_SCL_PORT,EROM_SCL_PIN,1)
#define EROM_SCL_LOW           gpio_set(EROM_SCL_PORT,EROM_SCL_PIN,0)

#define EROM_SDA_HIGH          gpio_set(EROM_SDA_PORT,EROM_SDA_PIN,1)
#define EROM_SDA_LOW           gpio_set(EROM_SDA_PORT,EROM_SDA_PIN,0)

#define EROM_SDA_READ          gpio_get(EROM_SDA_PORT,EROM_SDA_PIN)
#define EROM_SCL_READ          gpio_get(EROM_SCL_PORT,EROM_SCL_PIN)

#define EROM_delay              delay_us(20)



//�����������������ݽ���ת��

//_________________�����嶨��_____________________
union short_chr
{
    short data;
    unsigned char data_buf[8];
}short_chr_convertor;//���������ַ�������ת��

union int_chr
{
    int data;
    unsigned char data_buf[8];
}int_chr_convertor;//�������ַ�������ת��

union flt_chr
{
    float data;
    unsigned char data_buf[4];
}flt_chr_convertor;//���������ַ�������ת��

union dub_chr
{
    double data;
    unsigned char data_buf[8];
}dub_chr_convertor;//˫���ȸ��������ַ�������ת��
//______________________________________________

extern void EROM_IIC_init();
extern void EROM_IIC_start();
extern void EROM_IIC_stop();
extern void EROM_IIC_ACK();
extern void EROM_IIC_NACK();
extern unsigned char EROM_Check_ACK();

extern void EROM_IIC_Send_Byte(uint8 Data);
extern unsigned char EROM_IIC_Read_Byte(uint8 ack);
extern void EEPROM_init();
extern void EEPROM_reset();//�����λ
extern uint8 EEPROM_write_len(uint8 page , uint8 addr , uint8 * data , uint8 len);//����д��
extern uint8 EEPROM_write_Byte(uint8 page,uint8 addr , uint8 data);
extern uint8 EEPROM_write_double(uint8 page , uint8 addr , double data);
extern uint8 EEPROM_write_float(uint8 page , uint8 addr , float data);
extern uint8 EEPROM_write_int(uint8 page , uint8 addr , int32 data);
extern uint8 EEPROM_write_short(uint8 page , uint8 addr , int16 data);
extern uint8 EEPROM_read_len(uint8 page , uint8 addr , uint8 * data_buf , uint8 len);//������
extern uint8 EEPROM_read_Byte(uint8 page,uint8 addr);
extern int16 EEPROM_read_short(uint8 page , uint8 addr);
extern int EEPROM_read_int(uint8 page , uint8 addr);
extern float EEPROM_read_float(uint8 page , uint8 addr);
extern double EEPROM_read_double(uint8 page , uint8 addr);


#ifdef __cplusplus
}
#endif

#endif /* EXINEEPROM_H_ */
