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
#ifndef _exinencoder_h
#define _exinencoder_h
#ifdef __cplusplus
extern "C"
{
#endif

#define CAPTURE 0x01
#define INT     0x00


typedef enum{
    ENCODER_CHA=0,//A通道
    ENCODER_CHB,//B通道
    ENCODER_CHC,//C通道
    ENCODER_CHD,//D通道

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
