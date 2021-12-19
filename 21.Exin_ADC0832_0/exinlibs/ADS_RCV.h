///////////////////////////////////////////////////////////////////////////////////////////////////
// ADS1292 serial port transmission with seekfree's codes/TI's codes designed for RT1064/MSP432  //
// Lastest : 2020.10.3                                                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ADS_RCV_H__
#define __ADS_RCV_H__

#ifndef MSP432_ENABLE
#define MSP432_ENABLE	1
#endif

#if !MSP432_ENABLE
#include "common.h"
#include "zf_systick.h"
#include "fsl_lpuart.h"
#include "zf_uart.h"

#define ADS_RCV_UART_SELECT	USART_2

#else
#include <driverlib.h>

#endif


#define ADS_RCV_UART	0xAA

typedef enum
{
	ERROR_ADS,
	BREATH,
	HEART,
}ADS_GET;

#if !MSP432_ENABLE
void ADS_RCV_Init(uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin);
void ADS_RCV_Uart_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

#else
void ADS_RCV_Init(void);

#endif


int ADS_Get(uint8_t num);


int ADS_RCV_GetData32(uint8_t num);



#endif


