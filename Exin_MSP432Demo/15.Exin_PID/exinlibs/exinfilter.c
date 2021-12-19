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
#include"headfile.h"
#include "exinfilter.h"


float num111[15]={20,15,2,3,67,87,12,23,90,87,35,36,56,76,28};

/***********************************/
/* filter_LIMITMEAN_FILTER_init
 *
 * 限幅平均滤波初始化
 *
 * high上限阈值   low下限阈值 len滤波器长度
 *
 *
 */
/**********************************/
void filter_LIMITMEAN_FILTER_init(FILTER_CHA *filter,float high,float low,int len)//限幅平均
{
    filter->filter_success=0;
    filter->threshold_high=high;
    filter->threshold_low=low;
    filter->filter_len=len;
}
/***********************************/
/* filter_KALMAN_FILTER_init
 *
 * 卡尔曼滤波初始化
 *
 * Q过程噪声  R测量噪声
 *
 *
 */
/**********************************/
void filter_KALMAN_FILTER_init(FILTER_CHA *filter,float Q,float R)//卡尔曼
{
    filter->filter_success=0;
    filter-> ProcessNiose_Q=Q;
    filter->MeasureNoise_R=R;
}
/***********************************/
/* filter_MIDLE_FILTER_init
 *
 * 中值滤波初始化
 *
 * len滤波器长度get_ADC_value()需要替换
 *
 *
 */
/**********************************/
void filter_MIDLE_FILTER_init(FILTER_CHA *filter,int len)//中值滤波
{
    int i;
    filter->filter_success=0;
    int num=len%2;
    if(num!=0)
        len+=1;
    for(i=0;i<len;i++)
        filter->buffer[i]=0;
    filter->filter_len=len;
}
/***********************************/
/* filter_LIMIT_FILTER_init(
 *
 * 限幅中值滤波初始化
 *
 * high上限阈值   low下限阈值
 *
 *
 */
/**********************************/
void filter_LIMIT_FILTER_init(FILTER_CHA *filter,float high,float low)//限幅
{
    filter->filter_success=0;
    filter-> threshold_high=high;
    filter->threshold_low=low;
}

/***********************************/
/* filter_PUSH_MEAN_FILTER_init
 *
 * 递推平均滤波初始化
 *
 *len滤波器长度
 *
 */
/**********************************/
void filter_PUSH_MEAN_FILTER_init(FILTER_CHA *filter,int len)//递推平均
{
    int i;
    filter->filter_len=len;
    for(i=0;i<len;i++)
        filter->buffer[i]=0;
    filter->filter_success=0;
}
/***********************************/
/* filter_MEAN_FILTER_init
 *
 * 均值滤波初始化
 *
 *len滤波器长度
 *
 */
/**********************************/
void filter_MEAN_FILTER_init(FILTER_CHA *filter,int len)//均值
{
    filter->filter_len=len;
    filter->filter_success=0;
}
/***********************************/
/* filter_LOW_FILTER_init
 *
 * 均值滤波初始化
 *
 *len滤波器长度
 *
 */
/**********************************/
void filter_LOW_FILTER_init(FILTER_CHA *filter,float pr_a)//一阶低通
{
    if(pr_a>1)
        pr_a=1;
    filter->filter_a=pr_a;
    filter->filter_pre=0;
    filter->filter_success=0;
}
/***********************************/
/*  filter_LOW_FILTERSEC_init
 *
 * 二阶低通滤波初始化
 *
 *k1  k2 k3 k4 k5 滤波器参数 总和为1
 *
 */
/**********************************/
void filter_LOW_FILTERSEC_init(FILTER_CHA * filter,float k1,float k2,float k3,float k4,float k5)//二阶低通
{
    filter->k1=k1;
    filter->k2=k2;
    filter->k3=k3;
    filter->k4=k4;
    filter->k5=k5;
    filter->filter_pre=0;
    filter->filter_pre_pre=0;
    filter->filter_value1=0;
    filter->filter_value2=0;
    filter->filter_success=0;
}
/***********************************/
/*  filter_SHAKEOFF_FILTER_init
 *
 * 削抖滤波初始化
 *
 *len滤波器灵敏度
 *
 */
/**********************************/
void filter_SHAKEOFF_FILTER_init(FILTER_CHA *filter,int len)//削抖滤波
{
    filter->filter_len=len;
    filter->filter_pre=0;
    filter->filter_success=0;
}


int i_test=0;
/***********************************/
/*  filter_LIMIT_FILTER_run
 *
 * 限幅滤波执行函数
 *
 *din数据入口
 *
 */
/**********************************/
float filter_LIMIT_FILTER_run(FILTER_CHA*filter,float din)//限幅滤波
{
    if(din>filter->threshold_high)
        return filter->threshold_high;
    else if(din<filter->threshold_low)
        return filter->threshold_low;
    return din;
}

/***********************************/
/*  filter_MEAN_FILTER_run
 *
 * 均值滤波执行函数
 *
 *din数据入口 mode模式选择 mode=0等待输出 mode=1扫描查询输出get_ADC_value()需要替换
 *
 */
/**********************************/
float filter_MEAN_FILTER_run(FILTER_CHA*filter,char mode,float din)//均值滤波
{
    static int i;
    static float sum;
    static float result;
    filter->filter_success=0;
    if(mode==0)//等待输出
    {
        for ( i=0;i<filter->filter_len;i++)
       {
          sum += get_ADC_value();//此处为获取ADC等数值
       }
        result=sum/filter->filter_len;
        i=0;
        sum=0;
        filter->filter_success=1;
       return result;
    }

    if(mode==1)//扫描输出
    {
        sum+=din;
        i++;
        if(i==filter->filter_len)
        {
            result=sum/filter->filter_len;
             filter->filter_success=1;
            sum=0;
            i=0;
        }
        if( filter->filter_success)
                return result;
    }
    return 999;//滤波未结束返回999

}
/***********************************/
/* filter_LIMITMEAN_FILTER_run
 *
 * 限幅均值滤波执行函数
 *
 *din数据入口 mode模式选择 mode=0等待输出 mode=1扫描输出get_ADC_value()需要替换
 *
 */
/**********************************/
float filter_LIMITMEAN_FILTER_run(FILTER_CHA*filter,char mode,float din)//限幅均值滤波
{
    static int i;
    static float sum;
    static float result;
    filter->filter_success=0;
    if(din>filter->threshold_high)
        din=filter->threshold_high;
    if(din<filter->threshold_low)
        din=filter->threshold_low;
    if(mode==0)//等待输出
    {
        for ( i=0;i<filter->filter_len;i++)
       {
          sum += get_ADC_value();//此处为获取ADC等数值
       }
        result=sum/filter->filter_len;
        i=0;
        sum=0;
        filter->filter_success=1;
       return result;
    }

    if(mode==1)//扫描输出
    {
        sum+=din;
        i++;
        if(i==filter->filter_len)
        {
            result=sum/filter->filter_len;
             filter->filter_success=1;
            sum=0;
            i=0;
        }
        if( filter->filter_success)
                return result;
    }
    return 999;//滤波未结束返回999

}
/***********************************/
/* filter_LOW_FILTER_run
 *
 *低通滤波执行函数
 *
 *din数据入口
 *
 */
/**********************************/
float filter_LOW_FILTER_run(FILTER_CHA*filter,float din)//低通滤波
{
    static float result;
    result=filter->filter_a*din+(1-filter->filter_a)*filter->filter_pre;
    filter->filter_pre=result;
    return result;
}

/***********************************/
/* filter_LOW_FILTER_run
 *
 *递推平均滤波执行函数
 *
 *din数据入口
 *
 */
/**********************************/
float filter_PUSH_MEAN_FILTER_run(FILTER_CHA*filter,float din)//递推平均滤波
{
    static float sum;
    static float result;
    static int i;
    filter->filter_success=0;
    for(i=filter->filter_len-1;i>0;i--)
    {
        filter->buffer[i]=filter->buffer[i-1];//递推
        filter->buffer[0]=din;
    }
    for(i=0;i<filter->filter_len;i++)
    {
        sum+=filter->buffer[i];
    }
    result=sum/filter->filter_len;
        sum=0;
    filter->filter_success=1;
    return result;
}
/***********************************/
/* filter_LOW_FILTER_run
 *
 *中位值滤波执行函数
 *
 *get_ADC_value()需要替换
 *
 */
/**********************************/
float filter_MIDDLE_FILTER_run(FILTER_CHA*filter)//中位值滤波
{
    static int i,j;
    int temp;
    filter->filter_success=0;

    for(i=0;i<filter->filter_len;i++)
    {
        filter->buffer[i]=get_ADC_value();//连续获取采样值
    }
    //排序
     for(j = 0; j < filter->filter_len - 1; j++)
     {
        for(i = 0; i < filter->filter_len - 1 - j; i++)
        {
          if(filter->buffer[i] > filter->buffer[i + 1])
          {
            temp = filter->buffer[i];
            filter->buffer[i] = filter->buffer[i + 1];
            filter->buffer[i + 1] = temp;
          }
        }
     }

    filter->filter_success=1;
    return  filter->buffer[filter->filter_len/2];
}


/***********************************/
/* filter_SHAKEOFF_FILTER_run
 *
 *限幅滤波波执行函数
 *
 *din数据入口
 *
 */
/**********************************/
float filter_SHAKEOFF_FILTER_run(FILTER_CHA*filter,float din)//限幅滤波
{
    static float filter_value;
    static int i;
    if(filter_value!=din)
    {
        i++;
        if(i>filter->filter_len)
        {   filter_value=din;i=0;}
    }
    else
    {
        i=0;
    }
    return filter_value;
}

/***********************************/
/* filter_LOWSEC_FILTER_run
 *
 *二阶低通滤波执行函数
 *
 *din数据入口
 *
 */
/**********************************/
float filter_LOWSEC_FILTER_run(FILTER_CHA*filter,float din)//二阶低通滤波
{
    static float result;
    result=filter->k1*din+filter->k2*filter->filter_pre
           +filter->k3*filter->filter_pre_pre+filter->k4*filter->filter_value1
           +filter->k5*filter->filter_value2;
    filter->filter_pre_pre=filter->filter_pre;
    filter->filter_pre=din;
    filter->filter_value2=filter->filter_value1;
    filter->filter_value1=result;
    return result;
}
/***********************************/
/* filter_KALMAN_FILTER_run
 *
 *卡尔曼滤波执行函数
 *
 *ResrcData数据入口 InitialPrediction可任意值
 *
 */
/**********************************/
float filter_KALMAN_FILTER_run(FILTER_CHA*filter,const float ResrcData,float InitialPrediction)//卡尔曼滤波
{
        float R = filter->MeasureNoise_R;
        float Q = filter->ProcessNiose_Q;
        static float x_last;
        float x_mid = x_last;
        float x_now;
        static float p_last;
        float p_mid ;
        float p_now;
        float kg;
        x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
        p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
        kg=p_mid/(p_mid+R); //kg为kalman filter，R为噪声
        x_now=x_mid+kg*(ResrcData-x_mid);//估计出的最优值
        p_now=(1-kg)*p_mid;//最优值对应的covariance
        p_last = p_now; //更新covariance值
        x_last = x_now; //更新系统状态值
        return x_now;
}
/*测试函数*/
float get_ADC_value()
{
    static int i;
    if(i!=15)
       return num111[i++];
    else
        return 0;
}
