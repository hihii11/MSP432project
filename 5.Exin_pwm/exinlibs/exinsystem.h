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
#ifndef _exinsystem_h
#define _exinsystem_h
#ifdef __cplusplus
extern "C"
{
#endif

#define s  2
#define ms 1
#define us 0
#define SYSTIC_CONFIGURE SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk

typedef enum{
    DCO_1_5M,
    DCO_3_0M,
    DCO_6_0M,
    DCO_12_0M,
    DCO_24_0M,
    DCO_48_0M,
    DC0_DEFAULTFRE
}DOC_FRE_enum;//DCO��ѡƵ��

typedef enum{
    LFXTCLK,
    VLOCLK,
    REFOCLK,
    DCOCLK,
    MODOSC,
    HFXTCLK,
    DEFAULTSOURCE
}CLK_source_enum;//��ѡʱ��Դö��

typedef enum{
    CLK_DIV1,//1��Ƶ
    CLK_DIV2,//2��Ƶ
    CLK_DIV4,//4��Ƶ
    CLK_DIV8,//8��Ƶ
    CLK_DIV16,//16��Ƶ
    CLK_DIV32,//32��Ƶ
    CLK_DIV64,//64��Ƶ
    CLK_DIV128,//128��Ƶ
}CLK_DIV_enum;//ʱ���źſ�ѡ��Ƶ�о�
/*******************ʱ��Ƶ�ʲ����궨��**********************/
#define MCLK_FRE             48000000
#define SMCLK_FRE            24000000
#define ACLK_FRE             32768
/**********************************************************/

#define CPU_F                               ((double)48000000)//CPU��Ƶ
#define F_Div                              CPU_F/1000/1000//��Ƶϵ��
//#define delay_us(x)                       __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay_us(x)                      systic_delayus((int)x)
#define delay_ms(x)                      systic_delayms((int)x)
extern long int time;
extern void CS_unlocked();
extern void CS_locked();
extern void DCO_set(DOC_FRE_enum DCO_FRE);
extern void MCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV);
extern void SMCLK_set(CLK_source_enum CLK_source,CLK_DIV_enum CLK_DIV);
extern void system_init(char EN);
extern void systic_start();
extern void systic_end();
extern int systic_read();
extern void systic_clr();
extern void set_clock_period();
extern void set_DCO_48MH();
extern void systic_delayus(int n);
extern void systic_delayms(int n);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
