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
#include"headfile.h"
#include "exinfilter.h"


float num111[15]={20,15,2,3,67,87,12,23,90,87,35,36,56,76,28};

/***********************************/
/* filter_LIMITMEAN_FILTER_init
 *
 * �޷�ƽ���˲���ʼ��
 *
 * high������ֵ   low������ֵ len�˲�������
 *
 *
 */
/**********************************/
void filter_LIMITMEAN_FILTER_init(FILTER_CHA *filter,float high,float low,int len)//�޷�ƽ��
{
    filter->filter_success=0;
    filter->threshold_high=high;
    filter->threshold_low=low;
    filter->filter_len=len;
}
/***********************************/
/* filter_KALMAN_FILTER_init
 *
 * �������˲���ʼ��
 *
 * Q��������  R��������
 *
 *
 */
/**********************************/
void filter_KALMAN_FILTER_init(FILTER_CHA *filter,float Q,float R)//������
{
    filter->filter_success=0;
    filter-> ProcessNiose_Q=Q;
    filter->MeasureNoise_R=R;
}
/***********************************/
/* filter_MIDLE_FILTER_init
 *
 * ��ֵ�˲���ʼ��
 *
 * len�˲�������get_ADC_value()��Ҫ�滻
 *
 *
 */
/**********************************/
void filter_MIDLE_FILTER_init(FILTER_CHA *filter,int len)//��ֵ�˲�
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
 * �޷���ֵ�˲���ʼ��
 *
 * high������ֵ   low������ֵ
 *
 *
 */
/**********************************/
void filter_LIMIT_FILTER_init(FILTER_CHA *filter,float high,float low)//�޷�
{
    filter->filter_success=0;
    filter-> threshold_high=high;
    filter->threshold_low=low;
}

/***********************************/
/* filter_PUSH_MEAN_FILTER_init
 *
 * ����ƽ���˲���ʼ��
 *
 *len�˲�������
 *
 */
/**********************************/
void filter_PUSH_MEAN_FILTER_init(FILTER_CHA *filter,int len)//����ƽ��
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
 * ��ֵ�˲���ʼ��
 *
 *len�˲�������
 *
 */
/**********************************/
void filter_MEAN_FILTER_init(FILTER_CHA *filter,int len)//��ֵ
{
    filter->filter_len=len;
    filter->filter_success=0;
}
/***********************************/
/* filter_LOW_FILTER_init
 *
 * ��ֵ�˲���ʼ��
 *
 *len�˲�������
 *
 */
/**********************************/
void filter_LOW_FILTER_init(FILTER_CHA *filter,float pr_a)//һ�׵�ͨ
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
 * ���׵�ͨ�˲���ʼ��
 *
 *k1  k2 k3 k4 k5 �˲������� �ܺ�Ϊ1
 *
 */
/**********************************/
void filter_LOW_FILTERSEC_init(FILTER_CHA * filter,float k1,float k2,float k3,float k4,float k5)//���׵�ͨ
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
 * �����˲���ʼ��
 *
 *len�˲���������
 *
 */
/**********************************/
void filter_SHAKEOFF_FILTER_init(FILTER_CHA *filter,int len)//�����˲�
{
    filter->filter_len=len;
    filter->filter_pre=0;
    filter->filter_success=0;
}


int i_test=0;
/***********************************/
/*  filter_LIMIT_FILTER_run
 *
 * �޷��˲�ִ�к���
 *
 *din�������
 *
 */
/**********************************/
float filter_LIMIT_FILTER_run(FILTER_CHA*filter,float din)//�޷��˲�
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
 * ��ֵ�˲�ִ�к���
 *
 *din������� modeģʽѡ�� mode=0�ȴ���� mode=1ɨ���ѯ���get_ADC_value()��Ҫ�滻
 *
 */
/**********************************/
float filter_MEAN_FILTER_run(FILTER_CHA*filter,char mode,float din)//��ֵ�˲�
{
    static int i;
    static float sum;
    static float result;
    filter->filter_success=0;
    if(mode==0)//�ȴ����
    {
        for ( i=0;i<filter->filter_len;i++)
       {
          sum += get_ADC_value();//�˴�Ϊ��ȡADC����ֵ
       }
        result=sum/filter->filter_len;
        i=0;
        sum=0;
        filter->filter_success=1;
       return result;
    }

    if(mode==1)//ɨ�����
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
    return 999;//�˲�δ��������999

}
/***********************************/
/* filter_LIMITMEAN_FILTER_run
 *
 * �޷���ֵ�˲�ִ�к���
 *
 *din������� modeģʽѡ�� mode=0�ȴ���� mode=1ɨ�����get_ADC_value()��Ҫ�滻
 *
 */
/**********************************/
float filter_LIMITMEAN_FILTER_run(FILTER_CHA*filter,char mode,float din)//�޷���ֵ�˲�
{
    static int i;
    static float sum;
    static float result;
    filter->filter_success=0;
    if(din>filter->threshold_high)
        din=filter->threshold_high;
    if(din<filter->threshold_low)
        din=filter->threshold_low;
    if(mode==0)//�ȴ����
    {
        for ( i=0;i<filter->filter_len;i++)
       {
          sum += get_ADC_value();//�˴�Ϊ��ȡADC����ֵ
       }
        result=sum/filter->filter_len;
        i=0;
        sum=0;
        filter->filter_success=1;
       return result;
    }

    if(mode==1)//ɨ�����
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
    return 999;//�˲�δ��������999

}
/***********************************/
/* filter_LOW_FILTER_run
 *
 *��ͨ�˲�ִ�к���
 *
 *din�������
 *
 */
/**********************************/
float filter_LOW_FILTER_run(FILTER_CHA*filter,float din)//��ͨ�˲�
{
    static float result;
    result=filter->filter_a*din+(1-filter->filter_a)*filter->filter_pre;
    filter->filter_pre=result;
    return result;
}

/***********************************/
/* filter_LOW_FILTER_run
 *
 *����ƽ���˲�ִ�к���
 *
 *din�������
 *
 */
/**********************************/
float filter_PUSH_MEAN_FILTER_run(FILTER_CHA*filter,float din)//����ƽ���˲�
{
    static float sum;
    static float result;
    static int i;
    filter->filter_success=0;
    for(i=filter->filter_len-1;i>0;i--)
    {
        filter->buffer[i]=filter->buffer[i-1];//����
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
 *��λֵ�˲�ִ�к���
 *
 *get_ADC_value()��Ҫ�滻
 *
 */
/**********************************/
float filter_MIDDLE_FILTER_run(FILTER_CHA*filter)//��λֵ�˲�
{
    static int i,j;
    int temp;
    filter->filter_success=0;

    for(i=0;i<filter->filter_len;i++)
    {
        filter->buffer[i]=get_ADC_value();//������ȡ����ֵ
    }
    //����
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
 *�޷��˲���ִ�к���
 *
 *din�������
 *
 */
/**********************************/
float filter_SHAKEOFF_FILTER_run(FILTER_CHA*filter,float din)//�޷��˲�
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
 *���׵�ͨ�˲�ִ�к���
 *
 *din�������
 *
 */
/**********************************/
float filter_LOWSEC_FILTER_run(FILTER_CHA*filter,float din)//���׵�ͨ�˲�
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
 *�������˲�ִ�к���
 *
 *ResrcData������� InitialPrediction������ֵ
 *
 */
/**********************************/
float filter_KALMAN_FILTER_run(FILTER_CHA*filter,const float ResrcData,float InitialPrediction)//�������˲�
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
        p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
        kg=p_mid/(p_mid+R); //kgΪkalman filter��RΪ����
        x_now=x_mid+kg*(ResrcData-x_mid);//���Ƴ�������ֵ
        p_now=(1-kg)*p_mid;//����ֵ��Ӧ��covariance
        p_last = p_now; //����covarianceֵ
        x_last = x_now; //����ϵͳ״ֵ̬
        return x_now;
}
/*���Ժ���*/
float get_ADC_value()
{
    static int i;
    if(i!=15)
       return num111[i++];
    else
        return 0;
}
