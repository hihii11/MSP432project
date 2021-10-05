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
///////////////////////////////////////////////////////////////////////////////////////////////////
// Openmv serial port transmission with seekfree's codes/exin's codes designed for RT1064/MSP432 //
// Lastest : 2020.9.25                                                                           //
//                                                                                               //
//*REMEMBER TO COMMENT THE CODES "EUSCIA2_IRQHandler(void)" in exinuart.c                        //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __OV_RCV_H__
#define __OV_RCV_H__

#ifndef MSP432_ENABLE
#define MSP432_ENABLE   1
#endif

#if !MSP432_ENABLE
#include "common.h"
#include "fsl_lpuart.h"
#include "zf_uart.h"

#define OV_RCV_UART_SELECT	 USART_1

#else
#include "headfile.h"
#include "exinuart.h"

#endif


#define OV_RCV_UART_PRE		 0x0A
#define OV_RCV_UART_PRO		 0x0D

#define OV_RCV_LENREAL		11		//填写发送字符串的最长位数
#define OV_RCV_LEN			OV_RCV_LENREAL + 2		
#define OV_RCV_TEST			0


//字符转化
uint8 HexToChar(uint8 bChar);                                                                                          
//初始化
#if !MSP432_ENABLE
void OV_RCV_Init(uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin);                                                
//UART响应函数
void OV_RCV_Uart_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
#else
//初始化
void OV_RCV_Init(void);
#endif
//获取所有数据，存在数组 OV_RCV_DATA_READ 中
void OV_RCV_ReadAll(void);
//提取单个真实数值
uint8 OV_RCV_GetValue(uint8 num);

#if OV_RCV_TEST                 //测试编写
void OV_RCV_TEST_Handle(void);
#endif

#endif

