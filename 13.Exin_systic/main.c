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
    OLED_init();//OLED��ʼ��
    key_init(KEY1|KEY2);
    gpio_init(GPIO_PORT_P1, GPIO_PIN0,GPO,1);//����
    while(1)
    {
        if(!change_flag)//��ⰴ��s1����ʱ��
        {
           OLED_Show_String(0,2,"KEY1:",8);
           OLED_Show_float(64,2,press_time,2,8);
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
            OLED_Show_String(96,1,"Ms",8);
            OLED_Show_String(48,1,"Sec",8);
            OLED_Show_String(0,1,"Min:",8);
            OLED_Show_Num(90, 2, (int)(systic_read(ms) / 10 % 100),3,8);//����
            OLED_Show_Num(42,2,(int)(systic_read(s) % 60),2,8);//��
            OLED_Show_Num(0,2,(int)(systic_read(s) / 60),2,8);//��
        }
        if(key_get(KEY2)==0)//����key2����״̬�л�
        {
           delay_ms(10);
           if(key_get(KEY2)==0)
           {
               change_flag=!change_flag;
               OLED_clr();
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
