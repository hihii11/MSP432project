/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2019年1月23日22:29:47
-------------------------------------------------------------------------------------------------------*/
#include "headfile.h"
#include "exinadjust.h"


uint8 dirf=0;//编码器方向标志位
#define count_max  6//对应要调的变量数


int page_count = 0;
int start_flag = 1;//调参开始标志位
int count = 0;
/*****测试变量********/
int testA=100;
int testB=100;
/*****测试变量********/
/********************************
 * OLED_SHOW
 * 调参GUI
 * 此处增加变量显示
 ******************************/
void OLED_SHOW()
{
    if(page_count==0)
   {
        OLED_Show_String(0,0,"1:",8);
        OLED_Show_Num(21,0,(testA),4,8);
        OLED_Show_String(0,1,"2:",8);
        OLED_Show_Num(21,1,(testB),4,8);
        OLED_Show_String(0,2,"3:",8);
        OLED_Show_Num(21,2,(0),4,8);
        OLED_Show_String(0,3,"4:",8);
        OLED_Show_Num(21,3,(0),4,8);
        OLED_Show_String(0,4,"5:",8);
        OLED_Show_Num(21,4,(0),4,8);
   }

    if(page_count == 1)
    {

   }


    OLED_Show_String(64,count%(count_max+1),"<--",8);

}
char IRQ3_5flag=0;//3.5中断标志位
char IRQ4_6flag=0;//4.6中断标志位
char A_flag=0;//A相触发标志位
char B_flag=0;//B相触发标志位

/*---------------------------------------------------------------
【函    数】bianmaqi_tiaocan()
【功    能】调参
【参    数】无
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void bianmaqi_tiaocan()
{
     while(start_flag)
     {
       OLED_SHOW();
       if(A_flag&&!B_flag&&IRQ3_5flag&&IRQ4_6flag)
       {  dirf=2;A_flag=0;IRQ3_5flag=0;IRQ4_6flag=0;}
       else if(!A_flag&&B_flag&&IRQ3_5flag&&IRQ4_6flag)
       {  dirf=3;B_flag=0;IRQ3_5flag=0;IRQ4_6flag=0;}
       if(dirf==2)
       {
          dirf=0;
          if(count == 0)
          {testA++;}
          else if(count == 1)
          {testB++;}
          else if(count == 2)
          {/*添加调参变量*/;}
          else if(count == 3)
          {/*添加调参变量*/;}
          else if(count == 4)
          {/*添加调参变量*/;}
          else if(count == 5)
          {/*添加调参变量*/}
          else if(count == 6)
          {/*添加调参变量*/}
       }
       if(dirf==3)
       {
          dirf=0;
          if(count == 0)
          {testA--;}
          else if(count == 1)
          {testB--;}
          else if(count == 2)
          {/*添加调参变量*/;}
          else if(count == 3)
          {/*添加调参变量*/;}
          else if(count == 4)
          {/*添加调参变量*/;}
          else if(count == 5)
          {/*添加调参变量*/}
          else if(count == 6)
          {/*添加调参变量*/}
       }


         if(!gpio_get(GPIO_PORT_P3, GPIO_PIN7))
         {
           count++;//编码器按下,count+计数
           OLED_clr();
           if(count==count_max+1)
             count=0;
           while(!gpio_get(GPIO_PORT_P3, GPIO_PIN7));//0等待结束
         }
         if(key_get(KEY3)==0)//开始程序
         {
               start_flag=0;
         }
    }
}
/*---------------------------------------------------------------
【函    数】Rotate_INIT()
【功    能】有关旋转编码器的初始化
【参    数】无
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void Rotate_INIT()
{
    //编码开关初始化
    gpio_init(GPIO_PORT_P3, GPIO_PIN7,GPO,1);
   // gpio_init(GPIO_PORT_P3, GPIO_PIN5,GPO,1);

    gpio_interrupt_INIT(GPIO_PORT_P4, GPIO_PIN6,RISING);//A相
    gpio_interrupt_INIT(GPIO_PORT_P3, GPIO_PIN5,RISING);//B相
    key_init(KEY1|KEY2|KEY3|KEY4);
}

/*---------------------------------------------------------------
【函    数】Rotate_adjust_TEST
【功    能】编码器测试函数
【参    数】无
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void Rotate_adjust_TEST()
{
    system_init(0);
    OLED_init();
    Rotate_INIT();
    bianmaqi_tiaocan();
    while(1);
}
