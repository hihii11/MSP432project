/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日19:47:48
-------------------------------------------------------------------------------------------------------*/


/************************************************************************************
 *
 * 注意事项：本例程为MPU6050低通滤波器姿态解算例程
 *           MPU6050 AD0引脚接地 器件地址为0x68
 *           当MPU6050通信错误时，板载P1.0LED(即红灯)会闪烁，请检查IIC连线与器件地址，若没问题，则断电重联
 *           本例程完全信任加速度计，根据互补滤波得到倾角
 *           串口为launch pad usb接口，打开串口调试助手，观察角度值
 *           波特率:115200
 *************************************************************************************/



#include "exinlibs\headfile.h"

/*角速度误差值,陀螺仪静止不动测出的角速度值*/
#define Gyrox_erro          -36   //x轴角速度误差
#define Gyroy_erro          -27   //y轴误差
#define Gyroz_erro          -37   //z轴误差

short MPU_ID,temp,gx,gy,gz,ax,ay,az;
float roll,yaw,pitch,yaw_mid;
int8 Page=0;//当前页
char txt[80]={};

void MPU_Low_fillter_Get_Angle()//低通滤波器解算数据
{
    float acc_roll,acc_pitch,acc_yaw;

    float a = 0.9;//互补滤波系数
    MPU_Get_Gyro(&gx,&gy,&gz);
    MPU_Get_Acc(&ax,&ay,&az);

    MPU_Get_Angel(ax,ay,az,&acc_roll,&acc_pitch,&acc_yaw);

    roll =(a*(roll+(gy-Gyroy_erro)*0.005)+(1-a)*acc_roll);//5ms
    pitch =(a*(pitch+(gx-Gyrox_erro)*0.005)+(1-a)*acc_pitch);//5ms
    yaw =((yaw+(gz-Gyroz_erro)*0.005));//5ms
}

void MPU6050_uart_send()//MPU6050解算的姿态发送程序
{
    sprintf(txt,"PITCH:%.2f ,ROLL:%.2f ,YAW:%.2f \n",pitch,roll,yaw);
    UART_send_string(UART0,txt);
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
    UART_init(UART0,115200);//初始化串口
    TimerA_CCR0INT_init(TIMERA_A0 , 5);//每5ms采样一次陀螺仪数据
    Interrupt_setPriority(INT_TA0_0, 0x60);//可以调整后一项来调整定时器中断优先级
    TimerA_CCR0INT_init(TIMERA_A1 , 500);//每500ms发送一次数据
    Interrupt_setPriority(INT_TA1_0, 0x20);//可以调整后一项来调整定时器中断优先级

    while(1)
    {

    }
}
