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
#include "headfile.h"
volatile uint8_t UART3_RXDat= 0;
volatile uint8_t UART2_RXDat= 0;
volatile uint8_t UART0_RXDat= 0;
/*******************/
/*串口参数定义
 *
 * 可选配置
 * 115200：
 *   BRDIV_115200,
    UCxBRF_115200,
    UCxBRS_115200,
    9600：
 *   BRDIV_9600,
    UCxBRF_9600,
    UCxBRS_9600,
 */
/********************/
const eUSCI_UART_Config  UART0 =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    BRDIV_115200,//115200波特率 其他波特率配置查看exinuart.h
    UCxBRF_115200,
    UCxBRS_115200,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
};
void UART0_init()
{
        FlashCtl_setWaitState(FLASH_BANK0, 2);
        FlashCtl_setWaitState(FLASH_BANK1, 2);
        PCM_setCoreVoltageLevel(PCM_VCORE1);
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
        UART_initModule(EUSCI_A0_BASE, & UART0);
        UART_enableModule(EUSCI_A0_BASE);
        UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT  );
        Interrupt_enableInterrupt(INT_EUSCIA0);
}
/*******************/
/*串口参数定义
 *
 * 可选配置
 * 115200：
 *   BRDIV_115200,
    UCxBRF_115200,
    UCxBRS_115200,
    9600：
 *   BRDIV_9600,
    UCxBRF_9600,
    UCxBRS_9600,
 */
/********************/
const eUSCI_UART_Config  UART2 =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    BRDIV_115200,//115200波特率 其他波特率配置查看exinuart.h
    UCxBRF_115200,
    UCxBRS_115200,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
};
/******************************

 *****************************/
void UART2_init()
{
       FlashCtl_setWaitState(FLASH_BANK0, 2);
       FlashCtl_setWaitState(FLASH_BANK1, 2);
       PCM_setCoreVoltageLevel(PCM_VCORE1);
       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
       UART_initModule(EUSCI_A2_BASE, & UART2);
       UART_enableModule(EUSCI_A2_BASE);
       UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
       UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);
       Interrupt_enableInterrupt(INT_EUSCIA2);
}

const eUSCI_UART_Config UART3 =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,
    BRDIV_115200,//115200波特率 其他波特率配置查看exinuart.h
    UCxBRF_115200,
    UCxBRS_115200,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
};

/*******************/
/*串口参数定义
 *
 * 可选配置
 * 115200：
 *   BRDIV_115200,
    UCxBRF_115200,
    UCxBRS_115200,
    9600：
 *   BRDIV_9600,
    UCxBRF_9600,
    UCxBRS_9600,
 */
/********************/
void UART3_init()
{
       FlashCtl_setWaitState(FLASH_BANK0, 2);
       FlashCtl_setWaitState(FLASH_BANK1, 2);
       PCM_setCoreVoltageLevel(PCM_VCORE1);
       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
       UART_initModule(EUSCI_A3_BASE, & UART3);
       UART_enableModule(EUSCI_A3_BASE);
       UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
       UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT  );
       Interrupt_enableInterrupt(INT_EUSCIA3);
}

/******************************
 * UART_send_string
 *
 * 发送一串字符串
 *
 *****************************/
void UART_send_string(uint32_t moduleInstance,char*txt)
{
    int i;
    for(i=0;txt[i];i++)
    {
       delay_ms(2);
       UART_transmitData(moduleInstance,txt[i]);
    }
}
/******************************
 * UART_send_string
 *
 * 发送一个8位整型
 *****************************/
void UART_send_Num(uint32_t moduleInstance,unsigned int num)
{
        UART_transmitData(moduleInstance,num);
}

void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
          UART0_RXDat = UART_receiveData(EUSCI_A0_BASE);
          UART_transmitData(EUSCI_A0_BASE,UART0_RXDat);
    }
}


void EUSCIA2_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    //接收中断,uart接收到字节,接收中断标志位会置1
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        /**********代码***************/
    }
}

void EUSCIA3_IRQHandler()
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A3_BASE);
    UART_clearInterruptFlag(EUSCI_A3_BASE, status);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
          UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
          /**********代码***************/
    }
}
