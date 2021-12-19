/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��2��23��22:29:47
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
�δ��ʱ������
1.��������ʱ�䣨��ƽʱ����
2.���
����s2ת��
-------------------------------------------------------------------------------------------------------*/
#include "exinlibs\headfile.h"
char change_flag=0;
float press_time=0;
void main()
{
    system_init(1);//1:��ʼ���δ��ʱ��
    set_DCO_48MH();
    OLED_Init();//OLED��ʼ��
    key_init(KEY1|KEY2);
    gpio_init(GPIO_PORT_P1, GPIO_PIN0,GPO,1);//����
    while(1)
    {
        if(!change_flag)//��ⰴ��s1����ʱ��
        {
           OLED_ShowString(0,2,"KEY1:");
           OLED_Showfloat(64,2,press_time);
            if(key_get(KEY1)==0)
            {
                delay_ms(10);
                if(key_get(KEY1)==0)
                {
                    systic_start();//����⵽����s1���£���ʼ��ʱ
                    while(!key_get(KEY1));
                    systic_end();//�����ɿ�ֹͣ��ʱ
                    press_time=(float)(systic_read( s)+(float)(systic_read(ms)%1000)/1000);//����ʱ����ȡ��ʱ��ת��Ϊs
                }
            }
        }
        else//���
        {
            OLED_ShowString(96,0,"Ms");
            OLED_ShowString(48,0,"Sec");
            OLED_ShowString(0,0,"Min:");
            OLED_ShowNum(90, 1, (int)(systic_read(ms) / 10 % 100),3,12);//����
            OLED_ShowNum(42,1,(int)(systic_read(s) % 60),2,12);//��
            OLED_ShowNum(0,1,(int)(systic_read(s) / 60),2,12);//��
        }
        if(key_get(KEY2)==0)//����key2����״̬�л�
        {
           delay_ms(10);
           if(key_get(KEY2)==0)
           {
               change_flag=!change_flag;
               OLED_Clear();
               systic_end();
               if(change_flag)
               {
                   systic_start();//������ʱ��
               }
               else
               {
                   systic_clr();//����ֵ����
               }
               while(!key_get(KEY2));
           }
        }
    }
}
