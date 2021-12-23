/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年8月1日22:52:44
-------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------
PID算法调试例程：请仔细阅读注意事项！！！！！！！！！！！！！！
-------------------------------------------------------------------------------------------------------*/

/**********************************************注意事项！！！！必看********************************************************/

//1.在调用本例程进行PID调试时，需要先调用电机测试例程，确定电机正反转方向，如果方向反了，闭环控制将变为正反馈，电机则会疯转
//2.本例程基于的驱动为带方向引脚的驱动。为了节省PWM资源，将pwm作为使能端输入，方向引脚通过逻辑门作用于原本的输入端
//3.务必注意，一旦电机疯转，应该立即切断电机电源！！！
//4.PID例程与其他例程不同在于，在system_init函数中，SMCLK分频由16分频改为2分频，电机频率改为3500，同时也修改了PWM占空比计算方式
//  对于串口，SMCLK时钟也修改为分频后的24Mhz，针对基频率，若频率太低，则会导致电机谐振发出声音，若出现此现象，可以适当提高基频率
//5.PID参数需要根据自身硬件系统确定！！！！

/**********************************************注意事项！！！！必看********************************************************/
#include "exinlibs\headfile.h"
float distance=0;

PID_IncTypeDef Motor1_PID;//定义一个PID结构体 Motor1_PID
int Motor1_speed=0;       //存储电机1速度值
int Motor1_pwm_duty=0;    //电机1PWM占空比

char txt[20]="";

//显示参数界面
void OLED_SHOW_PID()
{
    sprintf(txt,"speed:%d  ", Motor1_speed);
    OLED_ShowString(0,0,txt);//速度显示
    sprintf(txt, "duty:%d  ",  Motor1_pwm_duty);
    OLED_ShowString(0,1,txt);//当前占空比显示
}


//电机PID控制函数 target为目标值
void Motor_PID_CTL(int speed_now)
{
    //增量式PID反馈
    Motor1_pwm_duty  += PID_Inc( & Motor1_PID , speed_now );//将当前速度送入 使用Motor1_PID

    //电机pwm限幅
    if(Motor1_pwm_duty > 5000)//限幅值可以自行调整
        Motor1_pwm_duty = 5000;
    else if(Motor1_pwm_duty < -5000)
        Motor1_pwm_duty = -5000;
    else
        Motor1_pwm_duty = Motor1_pwm_duty;

    //改变电机通道A占空比
    if(Motor1_pwm_duty >= 0)
        Motor_pwm_duty( MOTOR_CHA , 1 , Motor1_pwm_duty );//正转  这边需要注意的是，是否正反转，需要先下载电机测试例程来测定
    else
        Motor_pwm_duty( MOTOR_CHA , 0 , -Motor1_pwm_duty );//反转  这边需要注意的是，是否正反转，需要先下载电机测试例程来测定
}

//MODE = 0 使用山外上位机调试波形
//MODE = 1 使用Exin_串口助手调试上位机，例程包下有，打开时间较长需等待。（此上位机为Exin制作）
//MODE != 0,1 关闭上位机打印
void oscil_print(int speed , char MODE)
{

    speed = (char)speed;//默认小于256
    if(MODE==0)//山外上位机
    {
        char DATA[5] ={};
        DATA[0] = 0x03;
        DATA[1] = 0xFC;

        DATA[2] = speed;

        DATA[3] = 0xFC;
        DATA[4] = 0x03;
        UART_send_string(UART0, DATA);
    }
    if(MODE==1)//Exin_串口助手
    {
        char DATA[11] ={};
        DATA[0] = 0x5a;
        DATA[1] = 0x00;
        DATA[2] = 0x00;

        DATA[3] = speed;//通道1

        DATA[4] = 0x00;//通道2
        DATA[5] = 0x00;//通道3
        DATA[6] = 0x00;//通道4
        DATA[7] = 0x00;//通道5
        DATA[8] = 0x00;//通道6
        DATA[9] = 0x00;//通道7
        DATA[10] = 0x00;//通道8
        UART_send_string(UART0, DATA);
    }

}

void main()
{
    system_init(1);//初始化滴答计时器
    set_DCO_48MH();//注意这边的函数与其他例程不同，其他例程SMCLK为3MHZ，为了得到更高占空比可调范围，以及更高的电机基频率，本例程分频SMCLK为24MHZ
    delay_ms(200);//等待外设上电
    UART_init(UART0,115200); //初始化串口0，用于上位机波形分析与调试
    OLED_Init();   //OLED初始化
    OLED_Clear();
    //电机相关初始化
    //电机初始化A通道
    Motor_PWM_INIT(MOTOR_CHA);//注意，这边的初始化函数也与之前例程不同，电机基频率为3500hz，同时周期计算方式也有改变，查看本函数与pwm_init函数
    //编码器初始化,A通道，外部中断采集方式
    encoder_init(ENCODER_CHA,INT);

    //PID相关初始化
    PID_SET( & Motor1_PID , 12 , 1 , 1 , 1);//设置PID参数值,目标值12,P=1,I=1,D=1,此处初值为随意设置，具体需要根据整体系统硬件来确定

    //中断初始化
    //定时器中断用于严格控制PID时间
    TimerA_CCR0INT_init(TIMERA_A3 , 2);//初始化D通道,扫描时间为2ms，查看isr A3中断！
    Interrupt_setPriority(INT_TA3_0, 0x60);//可以调整后一项来调整定时器中断优先级


    while(1)
    {
        Motor1_PID.target = 12;//改变电机1目标转速
        OLED_SHOW_PID();//参数显示
        oscil_print(Motor1_speed , 0);//山外上位机，速度波形上位机打印
    }
}
