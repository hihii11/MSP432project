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

#define OV_RCV_LENREAL		11		//��д�����ַ������λ��
#define OV_RCV_LEN			OV_RCV_LENREAL + 2		
#define OV_RCV_TEST			0


//�ַ�ת��
uint8 HexToChar(uint8 bChar);                                                                                          
//��ʼ��
#if !MSP432_ENABLE
void OV_RCV_Init(uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin);                                                
//UART��Ӧ����
void OV_RCV_Uart_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
#else
//��ʼ��
void OV_RCV_Init(void);
#endif
//��ȡ�������ݣ��������� OV_RCV_DATA_READ ��
void OV_RCV_ReadAll(void);
//��ȡ������ʵ��ֵ
uint8 OV_RCV_GetValue(uint8 num);

#if OV_RCV_TEST                 //���Ա�д
void OV_RCV_TEST_Handle(void);
#endif

#endif

