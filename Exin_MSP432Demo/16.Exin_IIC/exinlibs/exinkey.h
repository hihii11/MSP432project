/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2019��1��23��22:29:47
-------------------------------------------------------------------------------------------------------*/
#ifndef _exinkey_h
#define _exinkey_h
#ifdef __cplusplus
extern "C"
{
#endif

#define KEY1 0x01<<0
#define KEY2 0x01<<1
#define KEY3 0x01<<2
#define KEY4 0x01<<3
extern void key_init(uint8 key);
extern uint8 key_get(uint8 key);
extern void key_test();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
