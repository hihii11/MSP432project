/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��17��23:32:56
-------------------------------------------------------------------------------------------------------*/
#ifndef _exinADC_h
#define _exinADC_h
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
   uint8 CONVERT_SUCCESS_FLAG;//ת����ɱ�־λ
   uint8 WORK_MOD;            //����ģʽ��־λ
   int32 convert_data;        //ADC14�ڵ���ת���£����ݱ����ڸñ���
   int32 repeat_convert_CH[8];//ADC14���ظ�ת��ģʽ�£����ݽ������ڸû�����
   uint32 IRQ_FLG;             //ADC14��ǰ�ж�Դ�����ڸñ���
   uint8 ADC_CHEND;            //���ظ�ת��ģʽ�µĽ���ͨ���洢����
} ADC14_TypeDef;//ADC14�ṹ�嶨�壬���ڱ���һЩ��־λ���ظ�ת��������

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
}ADC14_CHA_eunm;//ADC14��ѡͨ���о�

typedef enum{
  ADC_MODCLK,        //MODCLK
  ADC_SYSCLK,        //SYSCLK
  ADC_ACLK,          //ACLK
  ADC_MCLK,          //MCLK
  ADC_SMCLK,         //SMCLK
  ADC_HSMCLK,        //HSMCLK
  ADC_DEFAULTCLK     //Ĭ��
}ADC14_CLK_eunm;//ADC14��ѡʱ���о�

typedef enum{
  ADC_DIV1,        //1
  ADC_DIV2,        //2
  ADC_DIV3,        //3
  ADC_DIV4,        //4
  ADC_DIV5,        //5
  ADC_DIV6,        //6
  ADC_DIV7,        //7
  ADC_DIV8,        //8
  ADC_DEFAULTDIV   //Ĭ��1��Ƶ
}ADC14_DIV_eunm;//ADC14��ѡʱ�ӷ�Ƶ�о�

typedef enum{
  ADC14_BIT8,         //8
  ADC14_BIT10,        //10
  ADC14_BIT12,        //12
  ADC14_BIT14,        //14
  ADC14_DEFAULTBIT
}ADC14_PREC_eunm;//ADC14��ѡ�ֱ����о�

ADC14_TypeDef ADC14_STRUCT;      //ADC14�ṹ��
#define ADC14_REF         3.3//�ο���ѹ
#define ONECE_CVRT_MOD    0x00//����ת��
#define REPEAT_CVRT_MOD   0x01//�ظ�ת��

extern void ADC14_convert_enable();//ʹ��AD14ת��
extern void ADC14_convert_disable();//����AD14ת��
extern void ADC14_convert_start();
extern void ADC14_convert_end();
extern void ADC14_start(ADC14_CHA_eunm ADC14_CHA);//ADC14��ʼһ��ת��
extern int ADC14_read_data(ADC14_CHA_eunm ADC14_CHA);
extern void ADC14_CHA_sel(ADC14_CHA_eunm ADC14_CHA);//ADCͨ���˿�ѡ��
extern void ADC14_CLK_sel(ADC14_CLK_eunm ADC14_CLK,ADC14_DIV_eunm ADC14_DIV);//ѡ�������ת��ʱ�� Ĭ��ѡ�� MCLK
extern void ADC14_PREC_sel(ADC14_PREC_eunm ADC_PREC);//ѡ��ֱ���
extern void ADC14_init(ADC14_CHA_eunm  ADC14_CHA,ADC14_CLK_eunm  ADC14_CLK ,ADC14_DIV_eunm  ADC14_DIV,ADC14_PREC_eunm ADC_PREC);
extern void ADC14_repeatmod_init(ADC14_CHA_eunm  ADC14_CHA, ADC14_CLK_eunm  ADC14_CLK,ADC14_DIV_eunm  ADC14_DIV, ADC14_PREC_eunm ADC_PREC);
extern void ADC14_repeatmod_rec(int * BUF,ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_IRQFG_set(ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_MEM_set(ADC14_CHA_eunm  ADC14_CHA);
extern void ADC14_CHAEND_set(ADC14_CHA_eunm  ADC14_CHA);//����ADC14����������ͨ��

#ifdef __cplusplus
}
#endif

#endif
