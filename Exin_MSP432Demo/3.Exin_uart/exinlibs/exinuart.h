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
#ifndef _exinuart_h
#define _exinuart_h
#ifdef __cplusplus
extern "C"
{
#endif

/******************
 * ���ò���������
 *****************/
//DCOΪ48Mhz
//��   CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
//CS_CTL1_SELM_3|CS_CTL1_DIVS__16;��һ����  ����MCLK��ƵΪCS_CTL1_DIVS__16����16��Ƶ������MCLKΪ3000000hz

//���޸�����ʱ�ӻ���MCLK����ʱ�ӣ��˴��궨��Ӧ�޸�

/*******************************************************�����ʲ�����*****************************************/
#define MCLK_FRE            3000000//����ʹ��MCLKʱ�Ӿ���MCLK��Ƶ���Բ鿴exinsystem.c
//���Ⲩ��������
//��дbaunds �õ�����
#define BAUNDS_BF           2400    //�˴���д������  �����ʱ���С��MCLK_FRE/2
#define BRDIV_BAUNDS_BF     (MCLK_FRE/BAUNDS_BF)>>4
#define UCxBRF_BAUNDS_BF    (int)(((float)MCLK_FRE/BAUNDS_BF/16-MCLK_FRE/BAUNDS_BF/16)*16+0.5)
#define UCxBRS_BAUNDS_BF    (int)(((((float)MCLK_FRE/BAUNDS_BF/16-MCLK_FRE/BAUNDS_BF/16)*16+0.5)-UCxBRF_BAUNDS_BF)*16+0.5)
//115200����������
#define BRDIV_115200        (MCLK_FRE/115200)>>4
#define UCxBRF_115200       (int)(((float)MCLK_FRE/115200/16-MCLK_FRE/115200/16)*16+0.5)
#define UCxBRS_115200       (int)(((((float)MCLK_FRE/115200/16-MCLK_FRE/115200/16)*16+0.5)-UCxBRF_115200)*16+0.5)
//9600
#define BRDIV_9600          (MCLK_FRE/9600)>>4
#define UCxBRF_9600         (int)(((float)MCLK_FRE/9600/16-MCLK_FRE/9600/16)*16+0.5)
#define UCxBRS_9600         (int)(((((float)MCLK_FRE/9600/16-MCLK_FRE/9600/16)*16+0.5)-UCxBRF_9600)*16+0.5)

//4800
#define BRDIV_4800          (MCLK_FRE/4800)>>4
#define UCxBRF_4800         (int)(((float)MCLK_FRE/4800/16-MCLK_FRE/4800/16)*16+0.5)
#define UCxBRS_4800         (int)(((((float)MCLK_FRE/4800/16-MCLK_FRE/4800/16)*16+0.5)-UCxBRF_4800)*16+0.5)

/*******************************************************�����ʲ�����*****************************************/


extern void UART_send_string(uint32_t moduleInstance,char*txt);
extern void UART_send_Num(uint32_t moduleInstance,unsigned int num);
extern void UART0_init();
extern void UART2_init();
extern void UART0_TEST();
extern void UART3_init();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
