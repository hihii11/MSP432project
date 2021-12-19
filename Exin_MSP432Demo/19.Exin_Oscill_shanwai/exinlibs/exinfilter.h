/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2020��11��24��19:42:44
-------------------------------------------------------------------------------------------------------*/
#ifndef _exinfilter_h
#define _exinfilter_h

#ifdef __cplusplus
extern "C"
{
#endif

#define buffersize 50

typedef struct
{
    char filter_success;
    float buffer[buffersize] ;
    float filter_out;
    float filter_a;
    float filter_pre;
    int filter_len;
    float threshold_high;
    float threshold_low;
    float ProcessNiose_Q;
    float MeasureNoise_R;
    float k1,k2,k3,k4,k5;
    float filter_pre_pre;
    float filter_value1;
    float filter_value2;
} FILTER_CHA;

FILTER_CHA limit_filter;//�޷��˲��ṹ��
FILTER_CHA limitmean_filter;//�޷���ֵ�˲��ṹ��
FILTER_CHA mean_filter;////��ֵ�˲��ṹ��
FILTER_CHA low_filter;//һ�׵�ͨ�޷��˲��ṹ��
FILTER_CHA lowsec_filter;//���׵�ͨ�˲��ṹ��(������������˹�˲���)
FILTER_CHA push_mean_filter;//����ƽ���˲�
FILTER_CHA middle_filter;//��ֵ�˲�
FILTER_CHA shakeoff_filter;//����
FILTER_CHA kalman_filter;//�������˲�

float get_ADC_value();//ģ��ADCֵ��ȡ����������ʹ��ʱ���滻�ú���

void filter_LIMITMEAN_FILTER_init(FILTER_CHA *filter,float high,float low,int len);//�޷�ƽ���˲�
void filter_KALMAN_FILTER_init(FILTER_CHA *filter,float Q,float R);//������
void filter_MIDLE_FILTER_init(FILTER_CHA *filter,int len);//��ֵ�˲�
void filter_LIMIT_FILTER_init(FILTER_CHA *filter,float high,float low);//�޷�
void filter_PUSH_MEAN_FILTER_init(FILTER_CHA *filter,int len);//����ƽ��
void filter_MEAN_FILTER_init(FILTER_CHA *filter,int len);//��ֵ
void filter_LOW_FILTER_init(FILTER_CHA *filter,float pr_a);//һ�׵�ͨ
void filter_LOW_FILTERSEC_init(FILTER_CHA * filter,float k1,float k2,float k3,float k4,float k5);//���׵�ͨ
void filter_SHAKEOFF_FILTER_init(FILTER_CHA *filter,int len);//�����˲�


float filter_LIMIT_FILTER_run(FILTER_CHA*filter,float din);//�޷��˲�
float filter_MEAN_FILTER_run(FILTER_CHA*filter,char mode,float din);//��ֵ�˲�
float filter_LIMITMEAN_FILTER_run(FILTER_CHA*filter,char mode,float din);//�޷���ֵ�˲�
float filter_LOW_FILTER_run(FILTER_CHA*filter,float din);//��ͨ�˲�
float filter_PUSH_MEAN_FILTER_run(FILTER_CHA*filter,float din);//����ƽ���˲�
float filter_MIDDLE_FILTER_run(FILTER_CHA*filter);//��λֵ�˲�
float filter_SHAKEOFF_FILTER_run(FILTER_CHA*filter,float din);//�޷��˲�
float filter_LOWSEC_FILTER_run(FILTER_CHA*filter,float din);//���׵�ͨ�˲�
float filter_KALMAN_FILTER_run(FILTER_CHA*filter,const float ResrcData,float InitialPrediction);//�������˲�
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
