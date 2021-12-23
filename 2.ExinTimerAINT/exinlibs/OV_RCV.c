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
#include "OV_RCV.h"

#if OV_RCV_TEST
uint8 OV_RCV_TEST_FLAG = 0;
#endif

uint8 OV_RCV_FLAG = 0;
uint8 OV_RCV_STATE = 0;
uint8 OV_RCV_XYS[OV_RCV_LENREAL] = {0};
uint8 OV_RCV_DATA_READ[(OV_RCV_LENREAL >> 1)] = {0};
uint8 OV_RCV_DATA[OV_RCV_LEN] = {0};
#if !MSP432_ENABLE
uint8 OV_RCV_DATA_BUFFER;
lpuart_transfer_t   OV_RCV_DATA_INCLUDA;	
lpuart_handle_t     OV_RCV_UART_HANDLE;		
#endif


#if !MSP432_ENABLE
void OV_RCV_Init(uint32 baud, UARTPIN_enum tx_pin, UARTPIN_enum rx_pin)
{
	uart_init(OV_RCV_UART_SELECT, baud, tx_pin, rx_pin);
	uart_rx_irq(OV_RCV_UART_SELECT,1);
	systick_delay_ms(10);
	OV_RCV_DATA_INCLUDA.dataSize = 1;
        OV_RCV_DATA_INCLUDA.data = &OV_RCV_DATA_BUFFER;

	uart_set_handle(OV_RCV_UART_SELECT, &OV_RCV_UART_HANDLE, OV_RCV_Uart_Callback, NULL, 0, OV_RCV_DATA_INCLUDA.data, 1);
	uart_rx_irq(OV_RCV_UART_SELECT,0);
        systick_delay_ms(100);

}
#else
void OV_RCV_Init()
{
        UART2_init(115200);
        UART_disableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        delay_ms(100);

}
#endif

	
#if !MSP432_ENABLE
void OV_RCV_Uart_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        OV_RCV_DATA[OV_RCV_STATE] = OV_RCV_DATA_BUFFER;//鐏忓棙鏆熼幑顔煎絿閸戯拷
		OV_RCV_STATE ++;
		
		if(OV_RCV_STATE == 1 && OV_RCV_DATA[0] != OV_RCV_UART_PRE)
			OV_RCV_STATE = 0;
		if(OV_RCV_DATA[OV_RCV_STATE - 1] == OV_RCV_UART_PRO || OV_RCV_STATE == OV_RCV_LEN)
		{
			OV_RCV_STATE = 0;
#if OV_RCV_TEST
			OV_RCV_TEST_FLAG = 1;
#endif
			uart_rx_irq(OV_RCV_UART_SELECT,0);
		}
    }

    
    handle->rxDataSize = OV_RCV_DATA_INCLUDA.dataSize;  //鏉╂ê甯紓鎾冲暱閸栨椽鏆辨惔锟�
    handle->rxData = OV_RCV_DATA_INCLUDA.data;          //鏉╂ê甯紓鎾冲暱閸栧搫婀撮崸锟�
}
#else
/*
void EUSCIA2_IRQHandler(void)
{
    //閹恒儲鏁规稉顓熸焽,uart閹恒儲鏁归崚鏉跨摟閼猴拷,閹恒儲鏁规稉顓熸焽閺嶅洤绻旀担宥勭窗缂冿拷1
    if(EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);

        OV_RCV_DATA[OV_RCV_STATE] = UART_receiveData(EUSCI_A2_BASE);
        OV_RCV_STATE ++;

        if(OV_RCV_STATE == 1 && OV_RCV_DATA[0] != OV_RCV_UART_PRE)
            OV_RCV_STATE = 0;

        if(OV_RCV_DATA[OV_RCV_STATE - 1] == OV_RCV_UART_PRO || OV_RCV_STATE == OV_RCV_LEN)
        {
            OV_RCV_STATE = 0;
            OV_RCV_FLAG = 1;
            UART_disableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        }
    }
}*/
#endif

uint8 HexToChar(uint8 bChar)
{
    if((bChar >= 0x30)&&(bChar <= 0x39))
      bChar -= 0x30;
    else if((bChar>=0x41)&&(bChar<=0x46))//濠㈠爢鍐ㄦ櫢閻庢稒顨嗛惁锟�
      bChar -= 0x37;
    else if((bChar>=0x61)&&(bChar<=0x66))//閻忓繐绻愰崯鎾讹拷娑欘殕閻︼拷
      bChar -= 0x57;
    else 
      bChar = 0xff;
    return bChar;
}

void OV_RCV_ReadAll()
{
	uint8 R_DATA = 0;
    uint8 R_Flag = 0;
  	uint8 count_temp = 0;
  	static uint8 count_NF = 0;

#if !MSP432_ENABLE
  	uart_rx_irq(OV_RCV_UART_SELECT,1);
#else
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
#endif

  	if(!OV_RCV_FLAG)
  	{
  	    count_NF ++;
  	    if(count_NF > 50)
  	    {
  	        if(OV_RCV_DATA_READ[0] != 0)
  	        {
  	            for(count_NF = 0; count_NF < (OV_RCV_LENREAL >> 1); count_NF ++)
  	                OV_RCV_DATA_READ[count_NF] = 0x00;
  	        }
  	        count_NF = 0;
  	    }
  	}
  	else
  	{
  	    count_NF = 0;
  	    OV_RCV_FLAG = 0;

  	    for(count_temp = 0; count_temp < OV_RCV_LENREAL; count_temp ++)
  	    {
  	        OV_RCV_XYS[count_temp] = HexToChar(OV_RCV_DATA[1 + count_temp]);
  	        if(OV_RCV_XYS[count_temp] == 0xff)
  	            continue;
            
  	        R_DATA *= 10;
  	        R_DATA +=  OV_RCV_XYS[count_temp];

  	        if(OV_RCV_XYS[count_temp + 1] == 0xff)
  	        {
  	            OV_RCV_DATA_READ[R_Flag] = R_DATA;
  	            R_DATA = 0;
  	            R_Flag ++;
  	            continue;
  	        }
  	    }
  	}

}

uint8 OV_RCV_GetValue(uint8 num)
{
    if(num >= (OV_RCV_LENREAL >> 1))
        return 0xFF;
    else
        return OV_RCV_DATA_READ[num];
}

#if OV_RCV_TEST                 //婵炴潙顑堥惁顖滅磽閺嵮冩櫢
void OV_RCV_TEST_Handle()
{
  
}
#endif

    
