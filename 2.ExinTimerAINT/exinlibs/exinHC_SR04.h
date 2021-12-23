/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��2��24��13:12:44
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
