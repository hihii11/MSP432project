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
