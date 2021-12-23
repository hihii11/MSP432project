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
#ifndef _exinencoder_h
#define _exinencoder_h
#ifdef __cplusplus
extern "C"
{
#endif

#define CAPTURE 0x01
#define INT     0x00


typedef enum{
    ENCODER_CHA=0,//Aͨ��
    ENCODER_CHB,//Bͨ��
    ENCODER_CHC,//Cͨ��
    ENCODER_CHD,//Dͨ��

}Encoder_Channel_enum;

typedef struct
{
  long int encoder;
  unsigned char dir;
} Encoder_IncTypeDef;
extern Encoder_IncTypeDef encoder_A,encoder_B,encoder_C,encoder_D;
extern void encoder_dirpin_init(Encoder_Channel_enum CHI);
extern void encoder_IncTypeDef_init(Encoder_Channel_enum CHI);
extern void encoder_interrupt_init(Encoder_Channel_enum CHI);
extern void encoder_init(Encoder_Channel_enum CHI,unsigned char MODE);
extern long int GET_encoder_num(Encoder_Channel_enum CHI);
extern unsigned char GET_encoder_dir(Encoder_Channel_enum CHI);
extern void Encoder_clr(Encoder_Channel_enum CHI);
extern void ENCODER_TEST();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
