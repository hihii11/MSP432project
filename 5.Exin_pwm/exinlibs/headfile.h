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
#ifndef _headfile_h
#define _headfile_h
#ifdef __cplusplus



extern "C"
{
#endif


//432������ͷ�ļ�
#include <driverlib.h>

//����ͷ�ļ�
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//����ģ��ͷ�ļ�
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
