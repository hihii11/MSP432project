/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2020年11月24日19:42:44
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

FILTER_CHA limit_filter;//限幅滤波结构体
FILTER_CHA limitmean_filter;//限幅均值滤波结构体
FILTER_CHA mean_filter;////均值滤波结构体
FILTER_CHA low_filter;//一阶低通限幅滤波结构体
FILTER_CHA lowsec_filter;//二阶低通滤波结构体(可衍生巴特沃斯滤波器)
FILTER_CHA push_mean_filter;//递推平均滤波
FILTER_CHA middle_filter;//中值滤波
FILTER_CHA shakeoff_filter;//削抖
FILTER_CHA kalman_filter;//卡尔曼滤波

float get_ADC_value();//模拟ADC值获取函数，真正使用时需替换该函数

void filter_LIMITMEAN_FILTER_init(FILTER_CHA *filter,float high,float low,int len);//限幅平均滤波
void filter_KALMAN_FILTER_init(FILTER_CHA *filter,float Q,float R);//卡尔曼
void filter_MIDLE_FILTER_init(FILTER_CHA *filter,int len);//中值滤波
void filter_LIMIT_FILTER_init(FILTER_CHA *filter,float high,float low);//限幅
void filter_PUSH_MEAN_FILTER_init(FILTER_CHA *filter,int len);//递推平均
void filter_MEAN_FILTER_init(FILTER_CHA *filter,int len);//均值
void filter_LOW_FILTER_init(FILTER_CHA *filter,float pr_a);//一阶低通
void filter_LOW_FILTERSEC_init(FILTER_CHA * filter,float k1,float k2,float k3,float k4,float k5);//二阶低通
void filter_SHAKEOFF_FILTER_init(FILTER_CHA *filter,int len);//削抖滤波


float filter_LIMIT_FILTER_run(FILTER_CHA*filter,float din);//限幅滤波
float filter_MEAN_FILTER_run(FILTER_CHA*filter,char mode,float din);//均值滤波
float filter_LIMITMEAN_FILTER_run(FILTER_CHA*filter,char mode,float din);//限幅均值滤波
float filter_LOW_FILTER_run(FILTER_CHA*filter,float din);//低通滤波
float filter_PUSH_MEAN_FILTER_run(FILTER_CHA*filter,float din);//递推平均滤波
float filter_MIDDLE_FILTER_run(FILTER_CHA*filter);//中位值滤波
float filter_SHAKEOFF_FILTER_run(FILTER_CHA*filter,float din);//限幅滤波
float filter_LOWSEC_FILTER_run(FILTER_CHA*filter,float din);//二阶低通滤波
float filter_KALMAN_FILTER_run(FILTER_CHA*filter,const float ResrcData,float InitialPrediction);//卡尔曼滤波
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
