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
#ifndef  _exinHC_SR04_h
#define  _exinHC_SR04_h

#ifdef __cplusplus
extern "C"
{
#endif

#define TRIG_PORT GPIO_PORT_P1
#define TRIG_PIN GPIO_PIN6    //P1.6
#define ECHO_PORT GPIO_PORT_P1
#define ECHO_PIN GPIO_PIN7    //P1.7

extern void HC_SR04_init();
extern float HC_SR04_dis();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
