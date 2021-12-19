#ifndef _Oscill_OLED_h
#define _Oscill_OLED_h
#ifdef __cplusplus
extern "C"
{
#endif


#define OLED_Y_mid 32
#define OLED_X_mid 64


/************************示波器配置选项**********************/
//#define XLABEL_ON    (0x01<<0)
#define YLABEL_ON    (0x01<<1)
#define TITLE_ON     (0x01<<2)
//#define MAX_SHOW_ON  (0x01<<3)
//#define MIN_SHOW_ON  (0x01<<4)
/************************示波器配置选项**********************/
typedef struct{
    int middle_line;//中线
    float Enlarge;//倍率
    float Xlabel_Enlarge;//x轴分度值
    float Ylabel_Enlarge;//y轴分度值
    uint8 configure;
    uint8 *txt;
}Oscill;//示波器结构体定义
extern Oscill oscill1;
extern int  Oscill_data_buff[128];


void Oscill_test1();
void Oscill_Show_Menu(Oscill*oscill);
void Oscill_Init(Oscill*oscill,uint8 mode,unsigned char * TxT);
void Oscill_Title();
void set_Oscill_label(Oscill*oscill,float xlabel,float ylabel);
void set_Oscill_middle(Oscill*oscill,int middle);
void set_Oscill_Enlar(Oscill*oscill, float Enlarge);
void Oscill_dataget(int data);
void Oscill_show(Oscill *oscill,char mod,int din);
void Oscill_test2();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
