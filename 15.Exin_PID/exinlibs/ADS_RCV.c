///////////////////////////////////////////////////////////////////////////////////////////////////
// ADS1292 serial port transmission with seekfree's codes/TI's codes designed for RT1064/MSP432  //
// Lastest : 2020.10.3                                                                           //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "ADS_RCV.h"

unsigned char R_FLAG = 0;
unsigned char ADS_RCV_FLAG = 0;
unsigned char ADS_RCV_STATE = 0;
unsigned char ADS_RCV_DATA[10] = {0};

#if !MSP432_ENABLE
unsigned char ADS_RCV_DATA_BUFFER;	//缓存区
lpuart_transfer_t   ADS_RCV_DATA_INCLUDA;	
lpuart_handle_t     ADS_RCV_UART_HANDLE;	

void ADS_RCV_Init(uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
	uart_init(ADS_RCV_UART_SELECT, baud, tx_pin, rx_pin);
	uart_rx_irq(ADS_RCV_UART_SELECT,1);
	systick_delay_ms(10);
	ADS_RCV_DATA_INCLUDA.dataSize = 1;
	ADS_RCV_DATA_INCLUDA.data = &ADS_RCV_DATA_BUFFER;

	uart_set_handle(ADS_RCV_UART_SELECT, &ADS_RCV_UART_HANDLE, ADS_RCV_Uart_Callback, NULL, 0, ADS_RCV_DATA_INCLUDA.data, 1);
//	uart_rx_irq(ADS_RCV_UART_SELECT,0);
	systick_delay_ms(100);

}

void ADS_RCV_Uart_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        ADS_RCV_DATA[ADS_RCV_STATE] = ADS_RCV_DATA_BUFFER;//将数据取出
		
		ADS_RCV_STATE ++;
		
		if(ADS_RCV_DATA[0] != ADS_RCV_UART)
			ADS_RCV_STATE = 0;
                else if(ADS_RCV_DATA[1] == ADS_RCV_UART)
                        ADS_RCV_STATE = 1;
		if(ADS_RCV_STATE > 1 && ADS_RCV_DATA[ADS_RCV_STATE - 1] == ADS_RCV_UART)
			ADS_RCV_STATE = 0;
		if(ADS_RCV_DATA[9] == ADS_RCV_UART)
		{
			ADS_RCV_DATA[9] = 0;
                        ADS_RCV_STATE = 0;
			ADS_RCV_FLAG = 1;
			uart_rx_irq(ADS_RCV_UART_SELECT,0);
		}
    }

    
    handle->rxDataSize = ADS_RCV_DATA_INCLUDA.dataSize;  //还原缓冲区长度
    handle->rxData = ADS_RCV_DATA_INCLUDA.data;          //还原缓冲区地址
}

#else
const eUSCI_UART_Config UART3_SET =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    13,
    0,
    37,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
};

void ADS_RCV_Init()
{
    //设置DCO频率24M(upping Vcore)
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    UART_initModule(EUSCI_A3_BASE, &UART3_SET);
    UART_enableModule(EUSCI_A3_BASE);
    UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    //UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT  );
    Interrupt_enableInterrupt(INT_EUSCIA3);

}
/*
void EUSCIA3_IRQHandler()
{
    uint8_t status = UART_getEnabledInterruptStatus(EUSCI_A3_BASE);

    if(status && EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        ADS_RCV_DATA[ADS_RCV_STATE] = UART_receiveData(EUSCI_A3_BASE);//将数据取出

        ADS_RCV_STATE ++;


        if(ADS_RCV_DATA[0] != ADS_RCV_UART)
            ADS_RCV_STATE = 0;
                else if(ADS_RCV_DATA[1] == ADS_RCV_UART)
                        ADS_RCV_STATE = 1;
        if(ADS_RCV_STATE > 1 && ADS_RCV_DATA[ADS_RCV_STATE - 1] == ADS_RCV_UART)
            ADS_RCV_STATE = 0;
        if(ADS_RCV_DATA[9] == ADS_RCV_UART)
        {
            ADS_RCV_DATA[9] = 0;
                        ADS_RCV_STATE = 0;
            ADS_RCV_FLAG = 1;
            UART_disableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        }

    }
}*/

#endif

int ADS_Get(unsigned char num)
{

	static unsigned char count_NF = 0;
	static int R_DATA = 0;

#if !MSP432_ENABLE
        uart_rx_irq(ADS_RCV_UART_SELECT,1);
#else
        UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
#endif
        
        
	while(!R_FLAG)
	{
		
//		count_NF ++;
//		if(count_NF > 120)
//		{
//		    count_NF = 0;
//			if(ADS_RCV_DATA[0] != ADS_RCV_UART)
//			{
//				return ERROR_ADS;
//			}

//		}

		if(ADS_RCV_FLAG)
		{
		    R_FLAG = 1;
		    ADS_RCV_FLAG = 0;
		    R_DATA = ADS_RCV_GetData32(num);
		}
	}

	R_FLAG = 0;
	return R_DATA;
}


int ADS_RCV_GetData32(unsigned char num)
{		
	if(num == BREATH)
		return (ADS_RCV_DATA[1] << 24) | (ADS_RCV_DATA[2] << 16) | (ADS_RCV_DATA[3] << 8) | ADS_RCV_DATA[4];
	else if(num == HEART)
		return (ADS_RCV_DATA[5] << 24) | (ADS_RCV_DATA[6] << 16) | (ADS_RCV_DATA[7] << 8) | ADS_RCV_DATA[8];
	return ERROR_ADS;
}
