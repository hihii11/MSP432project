#include "headfile.h"
#include "Oscill_OLED.h"
#include "math.h"
//screen_buf[128][64]
//Oscill Oscill1;

int  Oscill_data_buff[128]={0};
Oscill oscill1;

void Oscill_Title()
{
    OLED_Show_String(OLED_X_mid-10,0, oscill1.txt,8);
}


void Oscill_Init(Oscill*oscill,uint8 mode,unsigned char * TxT)
{
    oscill->configure=mode;
    oscill->txt=TxT;
}
void Oscill_Show_Menu(Oscill*oscill)
{
    if((oscill->configure&YLABEL_ON))
    {
        OLED_Show_String(0, 2 , "8",8);
        OLED_Draw_Pixel(0, 2,1);
        OLED_Show_String(0, 0 , "24",8);
        OLED_Draw_Pixel(0, 0,1 );
        OLED_Show_String(0, 4 , "-8",8);
        OLED_Draw_Pixel(0, 4,1);
        OLED_Show_String(0, 6 , "-24",8);
        OLED_Draw_Pixel(0,6,1);
    }
    if((oscill->configure&TITLE_ON))
    {
        Oscill_Title();
    }
}
void set_Oscill_label(Oscill*oscill,float xlabel,float ylabel)
{
    oscill->Xlabel_Enlarge=xlabel;//x轴坐标倍率
    oscill->Ylabel_Enlarge=ylabel;//y轴坐标倍率
}


void set_Oscill_middle(Oscill*oscill,int middle)
{
    oscill->middle_line=middle;
}

void set_Oscill_Enlar(Oscill*oscill, float Enlarge)
{
    oscill->middle_line=Enlarge;
}

void Oscill_dataget(int data)
{
    int i=0;
    static int n;
    n++;
    if(n%10)
    {
        for(i=127;i>=1;i--)
        {
            Oscill_data_buff[127-i]=Oscill_data_buff[127-i+1];
        }
        Oscill_data_buff[127]=data;
    }

}

uint8 date_get_count=0;

void Oscill_show(Oscill *oscill,char mod,int din)
{
    static count_x = 0;
    static dat_rcv[2] = {0};
    int i;
   // oled_update(2);
    if(mod==0)//移位模式
    {
        for(i=127;i>=0;i--)
        {
            OLED_pos_clr(i-1,oscill->middle_line-Oscill_data_buff[i-1]);
            OLED_Draw_Pixel(i,oscill->middle_line-Oscill_data_buff[i],1);
        }
    }
    else if(mod==1)//均值模式
    {
        Oscill_dataget(din);
        date_get_count++;
        if(date_get_count==168)
        {oled_update(2);
         date_get_count=0;
            for(i=127;i>=0;i--)
            {
                  OLED_Draw_Pixel(i,(unsigned int)(oscill->middle_line-Oscill_data_buff[i]),1);
            }
        }
    }
    else if(mod == 2)
    {
        dat_rcv[1] = Oscill_data_buff[count_x];
        dat_rcv[0] = 64 - din;
        Oscill_data_buff[count_x] = (dat_rcv[0] + dat_rcv[1])/2;
        OLED_Draw_Pixel(count_x,Oscill_data_buff[count_x],1);
        count_x ++;
        if(count_x == 128)
        {
            count_x = 0;
            OLED_clr();
        }
    }
}

int countt=0;
char ad_flag=0;
void Oscill_test1()
{

    if(countt>10)
    {
        ad_flag=0;
    }
    if(countt<0)
    {
        ad_flag=1;
    }
    if(ad_flag)
        countt++;
    else
        countt--;
    Oscill_dataget(2*countt);

    /* countt++;
      if(countt<15)
                  Oscill_dataget(12);
              if(countt>=15)
                  Oscill_dataget(-10);
              if(countt==30)
                  countt=0;*/
              Oscill_show(&oscill1,0,0);
}
int data_test=0;
int cott2=0;
int k2=1;
void Oscill_test2()
{

    cott2++;
    if(cott2==140)
    {k2=2;
        cott2=0;
    }
    if(countt>10)
       {
           ad_flag=0;
       }
       if(countt<0)
       {
           ad_flag=1;
       }
       if(ad_flag)
           countt++;
       else
           countt--;

              Oscill_show(&oscill1,1,k2*countt);
             // Oscill_Show_Menu(&oscill1);
}
