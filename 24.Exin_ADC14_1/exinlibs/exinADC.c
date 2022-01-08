/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��17��23:31:16
-------------------------------------------------------------------------------------------------------*/
#include"headfile.h"
#include "exinADC.h"

/*************************************************
 * ��  ��  ��:ADC14_convert_enable
 * ��       ��:ʹ��ADC14ת��
 * ��       ��:��
 * ע������:��
 *************************************************/
void ADC14_convert_enable()//ʹ��AD14ת��
{
    ADC14->CTL0 |= ADC14_CTL0_ENC;//����ENC��־λ
}
/*************************************************
 * ��  ��  ��:ADC14_convert_enable
 * ��       ��:����ADC14ת��
 * ��       ��:��
 * ע������:��
 *************************************************/
void ADC14_convert_disable()//����AD14ת��
{
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;//���ENC��־λ
}
/*************************************************
 * ��  ��  ��:ADC14_convert_start
 * ��       ��:��ʼһ��ADC14ת��
 * ��       ��:��
 * ע������:��
 *************************************************/
void ADC14_convert_start()
{
    ADC14->CTL0 |= ADC14_CTL0_SC;//����SC��־λ
}
/*************************************************
 * ��  ��  ��:ADC14_convert_end
 * ��       ��:����һ��ADC14ת��
 * ��       ��:��
 * ע������:��
 *************************************************/
void ADC14_convert_end()
{
    ADC14->CTL0 &= ~ADC14_CTL0_SC;//���SC��־λ
}
/*************************************************
 * ��  ��  ��:ADC14_start
 * ��       ��:��ָ��ͨ������һ�β�����ת��
 * ��       ��:ADC14_CHA:ADC14��ѡͨ��������exinADC.h�ļ�
 *                    ��ö��
 * ע������:��
 *************************************************/
void ADC14_start(ADC14_CHA_eunm ADC14_CHA)//ADC14��ʼһ��ת��
{
    ADC14_convert_disable();//����ADC14
    ADC14_convert_end();
    ADC14->MCTL[0] &= 0x00;//����MCTL������
    switch(ADC14_CHA)
    {
           case(ADC_CH0): ADC14->MCTL[0] = ADC14_MCTLN_INCH_0|ADC14_MCTLN_EOS;  break;//P5.5 MEM0�洢A0
           case(ADC_CH1): ADC14->MCTL[0] = ADC14_MCTLN_INCH_1|ADC14_MCTLN_EOS;  break;//P5.4 MEM0�洢A1
           case(ADC_CH2): ADC14->MCTL[0] = ADC14_MCTLN_INCH_2|ADC14_MCTLN_EOS;  break;//P5.3 MEM0�洢A2
           case(ADC_CH3): ADC14->MCTL[0] = ADC14_MCTLN_INCH_3|ADC14_MCTLN_EOS;  break;//P5.2 MEM0�洢A3
           case(ADC_CH4): ADC14->MCTL[0] = ADC14_MCTLN_INCH_4|ADC14_MCTLN_EOS;  break;//P5.1 MEM0�洢A4
           case(ADC_CH5): ADC14->MCTL[0] = ADC14_MCTLN_INCH_5|ADC14_MCTLN_EOS;  break;//P5.0 MEM0�洢A5
           case(ADC_CH6): ADC14->MCTL[0] = ADC14_MCTLN_INCH_6|ADC14_MCTLN_EOS;  break;//P4.7 MEM0�洢A6
           case(ADC_CH7): ADC14->MCTL[0] = ADC14_MCTLN_INCH_7|ADC14_MCTLN_EOS;  break;//P4.6 MEM0�洢A7
           case(ADC_CH8): ADC14->MCTL[0] = ADC14_MCTLN_INCH_8|ADC14_MCTLN_EOS;  break;//P4.5 MEM0�洢A8
           default:;
    }
    ADC14_convert_enable();//ʹ��ADC14ת��
    ADC14_convert_start();//��ʼһ��ת��
}
/*************************************************
 * ��  ��  ��:ADC14_read_data
 * ��       ��:��ָ��ͨ������һ��ת�������ݶ�ȡ
 * ��       ��:ADC14_CHA:ADC14��ѡͨ��������exinADC.h�ļ�
 *                    ��ö��
 * ע������:������ͨ��ADC14_init������ָ��ͨ����ADC14��
 *          �г�ʼ���󣬲���ֱ�ӵ��øú�����ȡADת��ֵ
 *************************************************/
int ADC14_read_data(ADC14_CHA_eunm ADC14_CHA)
{
    int ADC14_result=0;
    int PIN_CHEC = 0;
    switch(ADC14_CHA)//���ÿ��Ƿ�����ADCͨ��
    {
           case(ADC_CH0):
                         if(((P5->SEL0 & BIT5)==BIT5)&&((P5->SEL1 & BIT5)==BIT5)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.5
           case(ADC_CH1):
                         if(((P5->SEL0 & BIT4)==BIT4)&&((P5->SEL1 & BIT4)==BIT4)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.5//P5.4
           case(ADC_CH2):
                         if(((P5->SEL0 & BIT3)==BIT3)&&((P5->SEL1 & BIT3)==BIT3)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.3
           case(ADC_CH3):
                         if(((P5->SEL0 & BIT2)==BIT2)&&((P5->SEL1 & BIT2)==BIT2)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.2
           case(ADC_CH4):
                         if(((P5->SEL0 & BIT1)==BIT1)&&((P5->SEL1 & BIT1)==BIT1)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.1
           case(ADC_CH5):
                         if(((P5->SEL0 & BIT0)==BIT0)&&((P5->SEL1 & BIT0)==BIT0)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P5.0
           case(ADC_CH6):
                         if(((P4->SEL0 & BIT7)==BIT7)&&((P4->SEL1 & BIT7)==BIT7)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.7
           case(ADC_CH7):
                         if(((P4->SEL0 & BIT6)==BIT6)&&((P4->SEL1 & BIT6)==BIT6)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.6
           case(ADC_CH8):
                         if(((P4->SEL0 & BIT5)==BIT5)&&((P4->SEL1 & BIT5)==BIT5)) PIN_CHEC = 1;
                         else PIN_CHEC = 0;
                         break;//P4.5
           default:PIN_CHEC = 0;
    }
    if(PIN_CHEC)
    {
        ADC14_start(ADC14_CHA);//��ʼһ��ADת��
        while(!ADC14_STRUCT.CONVERT_SUCCESS_FLAG);
        ADC14_result =ADC14_STRUCT.convert_data;
        ADC14_STRUCT.CONVERT_SUCCESS_FLAG = 0;//������ɱ�־λ
    }
    else
        ADC14_result = 0;
    return ADC14_result;
}
/*************************************************
 * ��  ��  ��:ADC14_CHA_sel
 * ��       ��:ADCͨ���˿�ѡ�񣬶�ָ����ͨ�����Ž��г�ʼ��
 * ��       ��:ADC14_CHA:ADC14��ѡͨ��������exinADC.h�ļ�
 *                    ��ö��
 * ע������:��
 *************************************************/
void ADC14_CHA_sel(ADC14_CHA_eunm ADC14_CHA)//ADCͨ���˿�ѡ��
{
        switch(ADC14_CHA)
        {
            case(ADC_CH0): P5->SEL1 |= BIT5;P5->SEL0 |= BIT5;  break;//P5.5
            case(ADC_CH1): P5->SEL1 |= BIT4;P5->SEL0 |= BIT4;  break;//P5.4
            case(ADC_CH2): P5->SEL1 |= BIT3;P5->SEL0 |= BIT3;  break;//P5.3
            case(ADC_CH3): P5->SEL1 |= BIT2;P5->SEL0 |= BIT2;  break;//P5.2
            case(ADC_CH4): P5->SEL1 |= BIT1;P5->SEL0 |= BIT1;  break;//P5.1
            case(ADC_CH5): P5->SEL1 |= BIT0;P5->SEL0 |= BIT0;  break;//P5.0
            case(ADC_CH6): P4->SEL1 |= BIT7;P4->SEL0 |= BIT7;  break;//P4.7
            case(ADC_CH7): P4->SEL1 |= BIT6;P4->SEL0 |= BIT6;  break;//P4.6
            case(ADC_CH8): P4->SEL1 |= BIT5;P4->SEL0 |= BIT5;  break;//P4.5
            default:;
        }
}

/*************************************************
 * ��  ��  ��:ADC14_CLK_sel
 * ��       ��:ADC14ʱ������
 * ��       ��:ADC14_CLK:ADC14��ѡʱ�ӣ�����exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_DIV:��Ƶϵ��������exinADC.h�ļ���ö
 *                    ��
 * ע������:ADC14��ʱ��Ƶ��ΪADC14_CLK / ADC14_DIV
 *          �������ADC14�Ĳ���Ƶ��
 *          ADC14�Ĳ���Ƶ�ʿ�ͨ�����¹�ʽ���Լ���
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          ����tsample = 4 tphase = tdmove =1
 *          tconvert�ɷֱ��ʾ���:
 *          �� �ֱ���Ϊ 8bits(256) ʱ tconvert = 9
 *          �� �ֱ���Ϊ 10bits(1024) ʱ tconvert = 11
 *          �� �ֱ���Ϊ 12bits(4096) ʱ tconvert = 14
 *          �� �ֱ���Ϊ 14bits(16384) ʱ tconvert = 16
 *************************************************/
void ADC14_CLK_sel(ADC14_CLK_eunm ADC14_CLK,ADC14_DIV_eunm ADC14_DIV)//ѡ�������ת��ʱ�� Ĭ��ѡ�� MCLK
{
    switch(ADC14_CLK)
    {
        case(ADC_MODCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__MODCLK; break;//MODCLK
        case(ADC_SYSCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__SYSCLK; break;//SYSCLK
        case(ADC_ACLK):   ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__ACLK;   break;//ACLK
        case(ADC_MCLK):   ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__MCLK;   break;//MCLK
        case(ADC_SMCLK):  ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__SMCLK;  break;//SMCLK
        case(ADC_HSMCLK): ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_SSEL__HSMCLK; break;//HSMCLK
        default:ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;
    }
    switch(ADC14_DIV)
    {
        case(ADC_DIV1): ADC14->CTL0 |= ADC14_CTL0_DIV_0; break;//1
        case(ADC_DIV2): ADC14->CTL0 |= ADC14_CTL0_DIV_1; break;//2
        case(ADC_DIV3): ADC14->CTL0 |= ADC14_CTL0_DIV_2; break;//3
        case(ADC_DIV4): ADC14->CTL0 |= ADC14_CTL0_DIV_3; break;//4
        case(ADC_DIV5): ADC14->CTL0 |= ADC14_CTL0_DIV_4; break;//5
        case(ADC_DIV6): ADC14->CTL0 |= ADC14_CTL0_DIV_5; break;//6
        case(ADC_DIV7): ADC14->CTL0 |= ADC14_CTL0_DIV_6; break;//7
        case(ADC_DIV8): ADC14->CTL0 |= ADC14_CTL0_DIV_7; break;//8
        default:;
    }
    ADC14->CTL0 |= ADC14_CTL0_MSC ;//PULSEģʽ��MSC=1
}
/*************************************************
 * ��  ��  ��:ADC14_PREC_sel
 * ��       ��:ADC14�ֱ�������
 * ��       ��:ADC_PREC:ADC14��ѡ�ֱ��ʣ�����exinADC.h�ļ�
 *                    ��ö��
 * ע������:��
 *************************************************/
void ADC14_PREC_sel(ADC14_PREC_eunm ADC_PREC)//ѡ��ֱ���
{
    ADC14_convert_disable();//����ADC14
    ADC14_convert_end();
    switch(ADC_PREC)
    {
        case(ADC14_BIT8):  ADC14->CTL1 = ADC14_CTL1_RES_0;break;//8BIT
        case(ADC14_BIT10): ADC14->CTL1 = ADC14_CTL1_RES_1;break;//10BIT
        case(ADC14_BIT12): ADC14->CTL1 = ADC14_CTL1_RES_2;break;//12BIT
        case(ADC14_BIT14): ADC14->CTL1 = ADC14_CTL1_RES_3;break;//14BIT
        default: ADC14->CTL1 = ADC14_CTL1_RES_0;break;//8BIT
    }
}
/*************************************************
 * ��  ��  ��:ADC14_init
 * ��       ��:ADC14��ָ��ͨ����ADC14���г�ʼ��,�˺�����ADC14����Ϊ����ת��ģʽ
 * ��       ��:
 *          ADC_PREC:ADC14��ѡ�ֱ��ʣ�����exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_CHA:ADC14��ѡͨ��������exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_CLK:ADC14��ѡʱ�ӣ�����exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_DIV:��Ƶϵ��������exinADC.h�ļ���ö
 *                    ��
 * ע������:ADC14�Ĳ���Ƶ�ʿ�ͨ�����¹�ʽ���Լ���
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          ����tsample = 4 tphase = tdmove =1
 *          tconvert�ɷֱ��ʾ���:
 *          �� �ֱ���Ϊ 8bits(256) ʱ tconvert = 9
 *          �� �ֱ���Ϊ 10bits(1024) ʱ tconvert = 11
 *          �� �ֱ���Ϊ 12bits(4096) ʱ tconvert = 14
 *          �� �ֱ���Ϊ 14bits(16384) ʱ tconvert = 16
 *
 *          �����ô˺���ʱ����Ĭ�ϵ�ͨ������ת������ʱʵ�ʲ���Ƶ��ҪС�ڼ�������Ƶ��
 *************************************************/

void ADC14_init(ADC14_CHA_eunm  ADC14_CHA,
              ADC14_CLK_eunm  ADC14_CLK,
              ADC14_DIV_eunm  ADC14_DIV,
              ADC14_PREC_eunm ADC_PREC)
{
    //��ADC14�ṹ����г�ʼ��
    ADC14_STRUCT.CONVERT_SUCCESS_FLAG=0;//����ɼ���ɱ�־λ
    ADC14_STRUCT.WORK_MOD=ONECE_CVRT_MOD;//����ת��ģʽ
    ADC14_STRUCT.IRQ_FLG=ADC14_IER0_IE0;//�洢�ж�Դ
    //_____________________
    ADC14_CHA_sel(ADC14_CHA);                //��ʼ��ADC14ͨ��
    __enable_interrupt();                    //�����ж�
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);//��ʼ��NVIC�ж�
    ADC14_CLK_sel(ADC14_CLK ,ADC14_DIV);     //����ADC14ʱ��
    ADC14_PREC_sel(ADC_PREC);                //ѡ��ֱ���
    ADC14->IER0 |= ADC14_IER0_IE0;           //ʹ��ADC�ж�
}
/******************************************************************����Ϊ�ظ�����ģʽ����غ���*********************************************************/
/*************************************************
 * ��  ��  ��:ADC14_CHAEND_set
 * ��       ��:ADC14�ظ�����ģʽ�µ�ͨ�����ų�ʼ��
 * ��       ��:ADC14_CHA:����ͨ�����ã�����exinADC.h�ļ�
 *                    ��ö��
 * ע������:�����ζ�A0~ADC14_CHA��ͨ�����Ž��г�ʼ��
 *          �� ADC14_CHAEND_set(ADC14_CH4)
 *          ���A0~A4��ͨ�����Ž��г�ʼ��
 *************************************************/
void ADC14_CHAEND_set(ADC14_CHA_eunm  ADC14_CHA)//����ADC14����������ͨ��
{
    switch(ADC14_CHA)
   {
      case(ADC_CH7): P4->SEL1 |= BIT6;P4->SEL0 |= BIT6;  //P4.6
      case(ADC_CH6): P4->SEL1 |= BIT7;P4->SEL0 |= BIT7;  //P4.7
      case(ADC_CH5): P5->SEL1 |= BIT0;P5->SEL0 |= BIT0;  //5.0
      case(ADC_CH4): P5->SEL1 |= BIT1;P5->SEL0 |= BIT1;  //P5.1
      case(ADC_CH3): P5->SEL1 |= BIT2;P5->SEL0 |= BIT2;  //P5.2
      case(ADC_CH2): P5->SEL1 |= BIT3;P5->SEL0 |= BIT3;  //P5.3
      case(ADC_CH1): P5->SEL1 |= BIT4;P5->SEL0 |= BIT4;  //P5.4
      case(ADC_CH0): P5->SEL1 |= BIT5;P5->SEL0 |= BIT5;  //P5.5
      default:;
   }
}
/*************************************************
 * ��  ��  ��:ADC14_MEM_set
 * ��       ��:ADC14�ظ�����ģʽ�¸�ͨ��ת�������ݴ洢����
 * ��       ��:ADC14_CHA:����ͨ�����ã�����exinADC.h�ļ�
 *                    ��ö��
 * ע������:�����ζ�A0~ADC14_CHA��ͨ��ת��������MEM[0]~MEM[ADC14_CHA]���а�
 *          �� ADC14_MEM_set(ADC14_CH4)
 *          ��MEM0�Ĵ�A0ת������
 *            MEM1�Ĵ�A1ת������
 *            MEM2�Ĵ�A2ת������
 *            MEM3�Ĵ�A3ת������
 *            MEM4�Ĵ�A4ת������
 *************************************************/
void ADC14_MEM_set(ADC14_CHA_eunm  ADC14_CHA)
{
    switch(ADC14_CHA)//�����ͨ��ת�����ݴ洢�ļĴ���
   {
       case(ADC_CH7): ADC14->MCTL[7] = ADC14_MCTLN_INCH_7 ;//MEM7=A7
       case(ADC_CH6): ADC14->MCTL[6] = ADC14_MCTLN_INCH_6 ;//MEM6=A6
       case(ADC_CH5): ADC14->MCTL[5] = ADC14_MCTLN_INCH_5 ;//MEM5=A5
       case(ADC_CH4): ADC14->MCTL[4] = ADC14_MCTLN_INCH_4 ;//MEM4=A4
       case(ADC_CH3): ADC14->MCTL[3] = ADC14_MCTLN_INCH_3 ;//MEM3=A3
       case(ADC_CH2): ADC14->MCTL[2] = ADC14_MCTLN_INCH_2 ;//MEM2=A2
       case(ADC_CH1): ADC14->MCTL[1] = ADC14_MCTLN_INCH_1 ;//MEM6=A6
       case(ADC_CH0): ADC14->MCTL[0] = ADC14_MCTLN_INCH_0 ;//MEM6=A6
       default:;
   }
    switch(ADC14_CHA)//����ת��������־λ
    {
           case(ADC_CH7): ADC14->MCTL[7] |= ADC14_MCTLN_EOS ;break;//MEM7=A7
           case(ADC_CH6): ADC14->MCTL[6] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           case(ADC_CH5): ADC14->MCTL[5] |= ADC14_MCTLN_EOS ;break;//MEM5=A5
           case(ADC_CH4): ADC14->MCTL[4] |= ADC14_MCTLN_EOS ;break;//MEM4=A4
           case(ADC_CH3): ADC14->MCTL[3] |= ADC14_MCTLN_EOS ;break;//MEM3=A3
           case(ADC_CH2): ADC14->MCTL[2] |= ADC14_MCTLN_EOS ;break;//MEM2=A2
           case(ADC_CH1): ADC14->MCTL[1] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           case(ADC_CH0): ADC14->MCTL[0] |= ADC14_MCTLN_EOS ;break;//MEM6=A6
           default:;
    }
}
/*************************************************
 * ��  ��  ��:ADC14_IRQFG_set
 * ��       ��:ADC14�ظ�����ģʽ���жϴ�����־λ����
 * ��       ��:ADC14_CHA:����ͨ�����ã�����exinADC.h�ļ�
 *                    ��ö��
 * ע������:����ADC14���жϷ��������жϴ�����־λ��������
 *          �� ADC14_IRQFG_set(ADC14_CH4)
 *          ���ж�ԴΪADC14_IER0_IE4�����ʾ��MEM4�Ĵ������ݴ洢���ٴ����ж�
 *************************************************/
void ADC14_IRQFG_set(ADC14_CHA_eunm  ADC14_CHA)
{
        switch(ADC14_CHA)//����ת��������־λ
       {
              case(ADC_CH7): ADC14->IER0 = ADC14_IER0_IE7; break;//MEM7=A7
              case(ADC_CH6): ADC14->IER0 = ADC14_IER0_IE6; break;//MEM6=A6
              case(ADC_CH5): ADC14->IER0 = ADC14_IER0_IE5; break;//MEM5=A5
              case(ADC_CH4): ADC14->IER0 = ADC14_IER0_IE4; break;//MEM4=A4
              case(ADC_CH3): ADC14->IER0 = ADC14_IER0_IE3; break;//MEM3=A3
              case(ADC_CH2): ADC14->IER0 = ADC14_IER0_IE2; break;//MEM2=A2
              case(ADC_CH1): ADC14->IER0 = ADC14_IER0_IE1; break;//MEM6=A6
              case(ADC_CH0): ADC14->IER0 = ADC14_IER0_IE0; break;//MEM6=A6
              default:;
       }
        ADC14_STRUCT.IRQ_FLG=ADC14->IER0;//�洢�ж�Դ
}
/*************************************************
 * ��  ��  ��:ADC14_repeatmod_init
 * ��       ��:��ADC14����Ϊ�ظ�ת��������ADC14��ʱ����ֱ���
 * ��       ��:
 *          ADC_PREC:ADC14��ѡ�ֱ��ʣ�����exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_CHA:�ظ�����ģʽ�µĽ�ֹͨ��������exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_CLK:ADC14��ѡʱ�ӣ�����exinADC.h�ļ�
 *                    ��ö��
 *          ADC14_DIV:��Ƶϵ��������exinADC.h�ļ���ö
 *                    ��
 * ע������:����A0~ADC14_CHA���г�ʼ����
 *          ��ADC14_repeatmod_init(ADC_CH2,ADC_MCLK, ADC_DIV2,ADC_BIT12)
 *          ����A0~A2���г�ʼ������ѡ��MCLK����2��Ƶ��Ϊʱ�ӣ���ֱ���Ϊ4096
 *          ADC14�Ĳ���Ƶ�ʿ�ͨ�����¹�ʽ���Լ���
 *          ADC14_CLK / ADC14_DIV / (tsample+tphase+tconvert+tdmove)
 *          ����tsample = 4 tphase = tdmove =1
 *          tconvert�ɷֱ��ʾ���:
 *          �� �ֱ���Ϊ 8bits(256) ʱ tconvert = 9
 *          �� �ֱ���Ϊ 10bits(1024) ʱ tconvert = 11
 *          �� �ֱ���Ϊ 12bits(4096) ʱ tconvert = 14
 *          �� �ֱ���Ϊ 14bits(16384) ʱ tconvert = 16
 *
 *          �����ô˺���ʱ����Ĭ�ϵ�ͨ������ת������ʱʵ�ʲ���Ƶ��ҪС�ڼ�������Ƶ��
 *************************************************/
void ADC14_repeatmod_init(ADC14_CHA_eunm  ADC14_CHA,
                          ADC14_CLK_eunm  ADC14_CLK,
                          ADC14_DIV_eunm  ADC14_DIV,
                          ADC14_PREC_eunm ADC_PREC)
{
    //��ADC14�ṹ����г�ʼ��
    ADC14_STRUCT.CONVERT_SUCCESS_FLAG=0;//����ɼ���ɱ�־λ
    ADC14_STRUCT.WORK_MOD=REPEAT_CVRT_MOD;//����ת��ģʽ
    ADC14_STRUCT.ADC_CHEND=ADC14_CHA;//��¼����ͨ��
    //_____________________
    ADC14_CHAEND_set(ADC14_CHA);//���ý���ͨ��
    __enable_interrupt();//��ȫ���ж�
    NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);//ʹ��ADC14�ж�
    ADC14_CLK_sel(ADC14_CLK,ADC14_DIV);//����ADCʱ�ӳ�ʼ��
    //��ADC14����Ϊ˳��ת��
    ADC14->CTL0 &=~ADC14_CTL0_SHT0_2;//�������������
    ADC14->CTL0 |=ADC14_CTL0_SHT0__128|ADC14_CTL0_CONSEQ_3;//˳�����
    //���÷ֱ���
    ADC14_PREC_sel(ADC_PREC);
    //���ô洢�Ĵ���
    ADC14_MEM_set(ADC14_CHA);
    //�����жϱ�־λ
    ADC14_IRQFG_set(ADC14_CHA);
    ADC14_convert_enable();//ʹ��ADC14ת��
}

/*************************************************
 * ��  ��  ��:ADC14_repeatmod_rec
 * ��       ��:�ظ�ת��ģʽ�£����ڽ�ת��������ݴ���ADC_STRUCT�ṹ���е�repeat_convert_CH������
 * ��       ��:BUF:���ݽ��ջ�����
 *          ADC14_CHA:�ظ�ת��ģʽ�µĽ�ֹͨ��
 * ע������:�����ݴ���ADC_STRUCT�ṹ���е�repeat_convert_CH��,����ֱ��ͨ�����·�ʽ��ȡ����
 *          ADC_STRUCT.repeat_convert_CH[0]   A0����
 *          ADC_STRUCT.repeat_convert_CH[1]   A1����
*           ADC_STRUCT.repeat_convert_CH[2]   A2����
*           ~~~~~
*           ADC_STRUCT.repeat_convert_CH[7]   A7����
 *************************************************/
void ADC14_repeatmod_rec(int * BUF,uint8  ADC14_CHA)
{
    int i ;
    for(i=0;i<=ADC14_CHA;i++)
    {
        BUF[i] = ADC14->MEM[i];
    }
}
extern void ADC14_repeat_test();
/*************************************************
 * ��  ��  ��:ADC14_IRQHandler
 * ��       ��:ADC14�жϷ�����
 * ��       ��:��
 * ע������:��
 *************************************************/
void ADC14_IRQHandler(void) {
     if(ADC14_STRUCT.WORK_MOD == ONECE_CVRT_MOD)//����ǵ���ģʽ
     {
         ADC14_STRUCT.convert_data = ADC14->MEM[0];//��ȡת��ֵ
         ADC14_STRUCT.CONVERT_SUCCESS_FLAG = 1;//ת����ɱ�־λ��1
     }
     else  if (ADC14->IFGR0 & ADC14_STRUCT.IRQ_FLG
                 && ADC14_STRUCT.WORK_MOD == REPEAT_CVRT_MOD)//�ж��жϱ�־λ���ж��Ƿ�Ϊ�ظ�ת��ģʽ
     {
         ADC14_repeatmod_rec(ADC14_STRUCT.repeat_convert_CH,ADC14_STRUCT.ADC_CHEND);//��ر����ú���
         /***********************��������û��Ĵ�����*********************/
         ADC14_repeat_test();
         /***********************�û���������ӽ�����*********************/
     }
     else
     {
         /***********************��������û��Ĵ�����*********************/

         /***********************�û���������ӽ�����*********************/
     }
}
