/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日15:13:36
-------------------------------------------------------------------------------------------------------*/


/************************************************************************************
 *
 * 注意事项：本例程为MPU6050调试例程
 *           MPU6050 AD0引脚接地 器件地址为0x68
 *           当MPU6050通信错误时，板载P1.0LED(即红灯)会闪烁，请检查IIC连线与器件地址，若没问题，则断电重联
 *           本例程完全信任加速度计，根据加速度直接得出倾角
 *************************************************************************************/



#include "exinlibs\headfile.h"


short MPU_ID,temp,gx,gy,gz,ax,ay,az;
float roll,yaw,pitch;
uint8 MPU_txt[50]={};//用于显示
int8 Page=0;//当前页


void OLED_MPU_SHOW()
{
    if(Page % 3 == 0)
    {
        OLED_Show_String(11,1,"MPU_6050:Gyro  ",8);

        OLED_Show_String(0,2,"Gyrox:",8);
        sprintf(MPU_txt,"%d    ",gx);
        OLED_Show_String(41,2,MPU_txt,8);//显示x轴角加速度

        OLED_Show_String(0,3,"Gyroy:",8);
        sprintf(MPU_txt,"%d    ",gy);
        OLED_Show_String(41,3,MPU_txt,8);//显示y轴角加速度


        OLED_Show_String(0,4,"Gytoz:",8);
        sprintf(MPU_txt,"%d    ",gz);
        OLED_Show_String(41,4,MPU_txt,8);//显示z轴角加速度


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//器件当前温度值
    }
    else if(Page % 3 == 1)
    {
        OLED_Show_String(11,1,"MPU_6050:Acc  ",8);

        OLED_Show_String(0,2,"Accx:",8);
        sprintf(MPU_txt,"%d    ",ax);
        OLED_Show_String(41,2,MPU_txt,8);//显示x轴加速度

        OLED_Show_String(0,3,"Accy:",8);
        sprintf(MPU_txt,"%d    ",ay);
        OLED_Show_String(41,3,MPU_txt,8);//显示y轴加速度


        OLED_Show_String(0,4,"Accz:",8);
        sprintf(MPU_txt,"%d    ",az);
        OLED_Show_String(41,4,MPU_txt,8);//显示z轴加速度


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//器件当前温度值
    }
    else
    {
        OLED_Show_String(11,1,"MPU_6050:Angle  ",8);

        OLED_Show_String(0,2,"Pitch:",8);
        sprintf(MPU_txt,"%.2f    ",pitch);
        OLED_Show_String(41,2,MPU_txt,8);//显示x轴加速度

        OLED_Show_String(0,3,"Roll:",8);
        sprintf(MPU_txt,"%.2f    ",roll);
        OLED_Show_String(41,3,MPU_txt,8);//显示y轴加速度


        OLED_Show_String(0,4,"Yaw:",8);
        sprintf(MPU_txt,"%.2f    ",yaw);
        OLED_Show_String(41,4,MPU_txt,8);//显示z轴加速度


        OLED_Show_String(0,5,"temp:",8);
        OLED_Show_float(41,5,((float)temp/100),2,8);//器件当前温度值
    }
    if(!key_get(KEY1))
    {
        delay_ms(10);
        Page--;
        OLED_clr();//清屏
        if(Page == -1)
            Page=3;
        while(!key_get(KEY1));
    }
    if(!key_get(KEY2))
    {
        delay_ms(10);
        Page++;
        OLED_clr();//清屏
        if(Page == 3)
            Page=0;
        while(!key_get(KEY2));
    }
}

void main()
{
    system_init(1);//初始化滴答计时器
    set_DCO_48MH();
    gpio_init(GPIO_PORT_P1,GPIO_PIN0,GPO,0);//初始化LED  IO口
    OLED_init();//OLED初始化
    OLED_clr();//清屏
    MPU_init();//MPU6050寄存器初始化
    key_init(KEY1|KEY2);//初始化按键S1、S2用于翻页

    while(1)
    {
        temp= MPU_Get_Temp();                     //获取陀螺仪温度
        MPU_Get_Gyro(&gx,&gy,&gz);                //获取陀螺仪原始数据
        MPU_Get_Acc(&ax,&ay,&az);                 //获取原始加速度数据
        MPU_Get_Angel(ax,ay,az,&roll,&pitch,&yaw);//通过加速度换算角度数据
        OLED_MPU_SHOW();
    }
}
