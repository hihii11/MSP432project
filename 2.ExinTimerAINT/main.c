/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��21��17:01:05
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
��ʱ���жϲ�������
����TimerA��UPģʽ���ж�
��TImerA��CONTIUNOUSģʽ�µ��жϺ���
������:��1sΪ������˸LED1 ��250msΪ������˸LED2����
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"

void TimerA0_up_INTtest()
{
        gpio_toggle(GPIO_PORT_P1,GPIO_PIN0);//��תLED1
}
void TimerA3_continousup_INTtest()
{
        gpio_toggle(GPIO_PORT_P2,GPIO_PIN2);//��תLED2
}
void main()
{
    system_init(0);
    set_DCO_48MH();
    OLED_Init();
    gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,0);//ʹ��LED1
    gpio_init(GPIO_PORT_P2,GPIO_PIN2,GPO,0);//ʹ��LED2����
    TimerA_CCR0INT_init(TIMERA_A0 , 500);//����TimerA0 ��UPģʽ�µ��ж�����Ϊ500ms
    TimerA_CCRnINT_init(TIMERA_A3 , TIMERA_CCR1 ,125);//����TimerA3��CONTINUOUSģʽ��CCR1�ж�����Ϊ125ms
    while(1);
}
