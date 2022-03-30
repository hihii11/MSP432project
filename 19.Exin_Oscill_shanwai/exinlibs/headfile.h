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
#ifndef _headfile_h
#define _headfile_h
#ifdef __cplusplus



extern "C"
{
#endif


//432基础库头文件
#include <driverlib.h>

//基本头文件
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//其他模块头文件
#include "exinisr.h"
#include "exingpio.h"
#include "dat.h"
#include "exinpwm.h"
#include "exinTimerA.h"
#include "exinTimerAINT.h"
#include "exinADC.h"
#include "exinmotor.h"
#include "exinencoder.h"
#include "exinsystem.h"
#include "exinuart.h"
#include "exinadjust.h"
#include "exinkey.h"
#include "exinsteer.h"
#include "Oscill_OLED.h"
#include "LMT70RD.h"
#include "ADS1292.h"
#include "ADS_RCV.h"
//#include "exinfilter.h"
//#include "exincitysensor.h"
#include "exinHC_SR04.h"
#include "exinIIC.h"
#include "exinMPU6050.h"
#include "exineeprom.h"
#include "exinADC0832.h"
#include "exinoled.h"
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
