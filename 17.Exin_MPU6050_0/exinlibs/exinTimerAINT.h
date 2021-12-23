/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月21日16:46:33
-------------------------------------------------------------------------------------------------------*/

#ifndef _EXINTIMERAINT_H_
#define _EXINTIMERAINT_H_
#ifdef __cplusplus
extern "C"
{
#endif
//各当前TimerA模块时钟频率
#define TimerA0_BaseCLK  32768.0
#define TimerA1_BaseCLK  32768.0
#define TimerA2_BaseCLK  32768.0
#define TimerA3_BaseCLK  32768.0

extern uint16 CCRn_period_val[4][7];
extern int period_cvert(TIMERA_enum TIMERAn,int period);
extern void TimerA_CCR0INT_init(TIMERA_enum TIMERAn , int period);
extern void TimerA_CCRnINT_init(TIMERA_enum TIMERAn , TIMERA_CCR_enum TIMERA_CCR,int period);
#ifdef __cplusplus
}
#endif

#endif
