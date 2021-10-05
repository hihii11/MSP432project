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





/* 管脚分配表
 *
 * --------------------------------------------------
 * 模块           通道               引脚号                 推荐外设
 * -------------------------------------------------
 * PWM     pwm_CHA       p2.6            电机
 * PWM     pwm_CHB       p2.7            电机
 * PWM     pwm_CHC       p2.5            电机
 * PWM     pwm_CHD       p2.4            电机
 * PWM     pwm_CHE       p5.6            舵机
 * PWM     pwm_CHE       p5.7            舵机
 * UART    UART0         lanchpadUSB/PC  PC通信
 * UART    UART2         p3.2 p3.3       openmv
 * ADC     ADC_CHA       p5.2            传感器
 * ADC     ADC_CHB       p5.3            传感器
 * ADC     ADC_CHC       p5.4            传感器
 * ADC     ADC_CHD       p5.5            传感器
 * OLED    -------       查看oled.h
 * pit     PIT_CHA
 * pit     PIT_CHB
 * pit     PIT_CHC
 * pit     PIT_CHD
 * encoder ENCODER_CHA   p6.4            编码器
 * encoder ENCODER_CHB   自定义                   编码器
 * encoder ENCODER_CHC   自定义                   编码器
 * encoder ENCODER_CHD   自定义                   编码器
 * adjust  AB相旋钮编码器调参         查 exinadjust.h
 *-------------------------------------------------
 *-------------------------------------------------
 *-------------------------------------------------
 *-------------------------------------------------
 *库函数说明:
 *系统时钟库    exinsystem.c
 *定时器中断库 exin_pit.c
 *ADC库             exinADC.c
 *gpio库           exingpio.c
 *电机库           exinmotor.c
 *编码器库        exinencoder.c
 *pwm库             exinpwm.c
 *中断函数库     exinisr.c
 *调参库            exinadjust.c
 *超声波测距       exinHC_SR04.c
 *LMT70温度传感器       LMT70RD.c
 *按键库             exinkey.c
 *舵机驱动库      exinsteer.c
 *******************************************************************************/

