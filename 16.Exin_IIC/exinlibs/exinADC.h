/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月17日23:32:56
-------------------------------------------------------------------------------------------------------*/
#ifndef _exinADC_h
#define _exinADC_h
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
   uint8 CONVERT_SUCCESS_FLAG;//转换完成标志位
   uint8 WORK_MOD;            //工作模式标志位
   int32 convert_data;        //ADC14在单次转换下，数据保存于该变量
   int32 repeat_convert_CH[8];//ADC14在重复转换模式下，数据将保持于该缓冲区
   uint32 IRQ_FLG;             //ADC14当前中断源保存于该变量
   uint8 ADC_CHEND;            //在重复转换模式下的结束通道存储变量
} ADC14_TypeDef;//ADC14结构体定义，用于保存一些标志位和重复转换的数据

typedef enum{
  ADC_CH0,        //A0     P5.5
  ADC_CH1,        //A1     P5.4
  ADC_CH2,        //A2     P5.3
  ADC_CH3,        //A3     P5.2
  ADC_CH4,        //A4     P5.1
  ADC_CH5,        //A5     P5.0
  ADC_CH6,        //A6     P4.7
  ADC_CH7,        //A7     P4.6
  ADC_CH8,        //A8     P4.5
}ADC14_CHA_eunm;//ADC14可选通道列举

typedef enum{
  ADC_MODCLK,        //MODCLK
  ADC_SYSCLK,        //SYSCLK
  ADC_ACLK,          //ACLK
  ADC_MCLK,          //MCLK
  ADC_SMCLK,         //SMCLK
  ADC_HSMCLK,        //HSMCLK
  ADC_DEFAULTCLK     //默认
}ADC14_CLK_eunm;//ADC14可选时钟列举

typedef enum{
  ADC_DIV1,        //1
  ADC_DIV2,        //2
  ADC_DIV3,        //3
  ADC_DIV4,        //4
  ADC_DIV5,        //5
  ADC_DIV6,        //6
  ADC_DIV7,        //7
  ADC_DIV8,        //8
  ADC_DEFAULTDIV   //默认1分频
}ADC14_DIV_eunm;//ADC14可选时钟分频列举

typedef enum{
  ADC14_BIT8,         //8
  ADC14_BIT10,        //10
  ADC14_BIT12,        //12
  ADC14_BIT14,        //14
  ADC14_DEFAULTBIT
}ADC14_PREC_eunm;//ADC14可选分辨率列举

ADC14_TypeDef ADC14_STRUCT;      //ADC14结构体
#define ADC14_REF         3.3//参考电压
#define ONECE_CVRT_MOD    0x00//单次转换
#define REPEAT_CVRT_MOD   0x01//重复转换

extern void ADC14_convert_enable();//使能AD14转换
extern void ADC14_convert_disable();//禁能AD14转换
extern void ADC14_convert_start();
extern void ADC14_convert_end();
extern void ADC14_start(ADC14_CHA_eunm ADC14_CHA);//ADC14开始一次转换
extern int ADC14_read_data(ADC14_CHA_eunm ADC14_CHA);
extern void ADC14_CHA_sel(ADC14_CHA_eunm ADC14_CHA);//ADC通道端口选择
extern void ADC14_CLK_sel(ADC14_CLK_eunm ADC14_CLK,ADC14_DIV_eunm ADC14_DIV);//选择采样与转换时钟 默认选择 MCLK
extern void ADC14_PREC_sel(ADC14_PREC_eunm ADC_PREC);//选择分辨率
extern void ADC14_init(ADC14_CHA_eunm  ADC14_CHA,ADC14_CLK_eunm  ADC14_CLK ,ADC14_DIV_eunm  ADC14_DIV,ADC14_PREC_eunm ADC_PREC);
extern void ADC14_repeatmod_init(ADC14_CHA_eunm  ADC14_CHA, ADC14_CLK_eunm  ADC14_CLK,ADC14_DIV_eunm  ADC14_DIV, ADC14_PREC_eunm ADC_PREC);
extern void ADC14_repeatmod_rec(int * BUF,ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_IRQFG_set(ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_MEM_set(ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_CHAEND_set(ADC14_CHA_eunm  ADC14_CHA);//设置ADC14结束采样的通道

#ifdef __cplusplus
}
#endif

#endif
