/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年2月24日13:12:44
-------------------------------------------------------------------------------------------------------*/
#include"headfile.h"
#include"exinHC_SR04.h"
//引脚配置查看exinHC_SR04.h
void HC_SR04_init()
{
    gpio_init(TRIG_PORT,TRIG_PIN,GPO,1);
    gpio_init(ECHO_PORT,ECHO_PIN,GPI,0);//初始化发送和接收引脚
}

float HC_SR04_dis()
{
   static float distance;
   gpio_set(TRIG_PORT,TRIG_PIN,0); //拉低发送引脚并等待，使得前次发送的超声波不会影响本次测距
   delay_us(5);       // 持续5us低电平
   gpio_set(TRIG_PORT,TRIG_PIN,1);  //拉高发送引脚发送超声波
   delay_us(12);  // 持续发送12us
   gpio_set(TRIG_PORT,TRIG_PIN,0); //拉低发送引脚
   while(gpio_get(ECHO_PORT,ECHO_PIN)==0);
   systic_start();//开启滴答计时器
   while(gpio_get(ECHO_PORT,ECHO_PIN)==1);//最大超时150ms
   systic_end();//关闭滴答计时器
   distance=(float)(systic_read(us)* 17/1000.0);
   distance=(int)(distance*100)/100.0;
   return distance;
}
