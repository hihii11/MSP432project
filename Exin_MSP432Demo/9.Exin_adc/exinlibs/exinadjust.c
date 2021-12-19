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
#include "headfile.h"
#include "exinadjust.h"


uint8 dirf=0;//�����������־λ
int count_max = 6;//��ӦҪ������������


int page_count = 0;
int start_flag = 1;//���ο�ʼ��־λ
int count = 0;
/*****���Ա���********/
int testA=100;
int testB=100;
/*****���Ա���********/
/********************************
 * OLED_SHOW
 * ����GUI
 * �˴����ӱ�����ʾ
 ******************************/
void OLED_SHOW()
{
    if(page_count==0)
   {
        OLED_ShowString(0,0,"1:");
        OLED_ShowNum(21,0,(testA),4,16);
        OLED_ShowString(0,1,"2:");
        OLED_ShowNum(21,1,(testB),4,16);
        OLED_ShowString(0,2,"3:");
        OLED_ShowNum(21,2,(0),4,16);
        OLED_ShowString(0,3,"4:");
        OLED_ShowNum(21,3,(0),4,16);
        OLED_ShowString(0,4,"5:");
        OLED_ShowNum(21,4,(0),4,16);
   }

    if(page_count == 1)
    {

   }


    OLED_ShowString(64,count%(count_max+1),"<--");

}
char IRQ3_5flag=0;//3.5�жϱ�־λ
char IRQ4_6flag=0;//4.6�жϱ�־λ
char A_flag=0;//A�ഥ����־λ
char B_flag=0;//B�ഥ����־λ

/*---------------------------------------------------------------
����    ����bianmaqi_tiaocan()
����    �ܡ�����
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void bianmaqi_tiaocan()
{
   while(start_flag)
     {
       OLED_SHOW();
       if(A_flag&&!B_flag&&IRQ3_5flag&&IRQ4_6flag)
       {  dirf=2;A_flag=0;IRQ3_5flag=0;IRQ4_6flag=0;}
       if(!A_flag&&B_flag&&IRQ3_5flag&&IRQ4_6flag)
       {  dirf=3;B_flag=0;IRQ3_5flag=0;IRQ4_6flag=0;}
       if(dirf==2)
        {
          dirf=0;
          if(count == 0)
          {testA++;}
          else if(count == 1)
          {testB++;}
          else if(count == 2)
          {/*��ӵ��α���*/;}
          else if(count == 3)
          {/*��ӵ��α���*/;}
          else if(count == 4)
          {/*��ӵ��α���*/;}
          else if(count == 5)
          {/*��ӵ��α���*/}
          else if(count == 6)
          {/*��ӵ��α���*/}
        }
        if(dirf==3)
        {
          dirf=0;
          if(count == 0)
          {testA--;}
          else if(count == 1)
          {testB--;}
          else if(count == 2)
          {/*��ӵ��α���*/;}
          else if(count == 3)
          {/*��ӵ��α���*/;}
          else if(count == 4)
          {/*��ӵ��α���*/;}
          else if(count == 5)
          {/*��ӵ��α���*/}
          else if(count == 6)
          {/*��ӵ��α���*/}
       }


         if(!gpio_get(GPIO_PORT_P3, GPIO_PIN7))
         {
           count++;//����������,count+����
           OLED_Clear();
           if(count==count_max+1)
             count=0;
           while(!gpio_get(GPIO_PORT_P3, GPIO_PIN7));//0�ȴ�����
         }
         if(key_get(KEY3)==0)//��ʼ����
         {
               start_flag=0;
         }
    }
}
/*---------------------------------------------------------------
����    ����Rotate_INIT()
����    �ܡ��й���ת�������ĳ�ʼ��
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Rotate_INIT()
{
    //���뿪�س�ʼ��
    gpio_init(GPIO_PORT_P3, GPIO_PIN7,GPO,1);
   // gpio_init(GPIO_PORT_P3, GPIO_PIN5,GPO,1);

    gpio_interrupt_INIT(GPIO_PORT_P4, GPIO_PIN6,FALLING);//A��
    gpio_interrupt_INIT(GPIO_PORT_P3, GPIO_PIN5,FALLING);//B��
    key_init(KEY1|KEY2|KEY3|KEY4);
}

/*---------------------------------------------------------------
����    ����Rotate_adjust_TEST
����    �ܡ����������Ժ���
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Rotate_adjust_TEST()
{
    system_init(0);
    Rotate_INIT();
    bianmaqi_tiaocan();
    while(1);
}
