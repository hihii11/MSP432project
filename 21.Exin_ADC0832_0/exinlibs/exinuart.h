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
#ifndef _exinuart_h
#define _exinuart_h
#ifdef __cplusplus
extern "C"
{
#endif

/******************
 * 常用波特率配置
 *****************/
/****************************************************波特率参数表*****************************************/

//任意波特率配置
//填写baunds 得到配置
#define BAUNDS_BF           2400    //此处填写波特率  波特率必须小于MCLK_FRE/2
#define BRDIV_BAUNDS_BF     (SMCLK_FRE/BAUNDS_BF)>>4
#define UCxBRF_BAUNDS_BF    (int)(((float)SMCLK_FRE/BAUNDS_BF/16-SMCLK_FRE/BAUNDS_BF/16)*16+0.5)
#define UCxBRS_BAUNDS_BF    (int)(((((float)SMCLK_FRE/BAUNDS_BF/16-SMCLK_FRE/BAUNDS_BF/16)*16+0.5)-UCxBRF_BAUNDS_BF)*16+0.5)
//115200波特率配置
#define BRDIV_115200        (SMCLK_FRE/115200)>>4
#define UCxBRF_115200       (int)(((float)SMCLK_FRE/115200/16-SMCLK_FRE/115200/16)*16+0.5)
#define UCxBRS_115200       (int)(((((float)SMCLK_FRE/115200/16-SMCLK_FRE/115200/16)*16+0.5)-UCxBRF_115200)*16+0.5)
//9600
#define BRDIV_9600          (SMCLK_FRE/9600)>>4
#define UCxBRF_9600         (int)(((float)SMCLK_FRE/9600/16-SMCLK_FRE/9600/16)*16+0.5)
#define UCxBRS_9600         (int)(((((float)SMCLK_FRE/9600/16-SMCLK_FRE/9600/16)*16+0.5)-UCxBRF_9600)*16+0.5)

//4800
#define BRDIV_4800          (SMCLK_FRE/4800)>>4
#define UCxBRF_4800         (int)(((float)SMCLK_FRE/4800/16-SMCLK_FRE/4800/16)*16+0.5)
#define UCxBRS_4800         (int)(((((float)SMCLK_FRE/4800/16-SMCLK_FRE/4800/16)*16+0.5)-UCxBRF_4800)*16+0.5)

/*******************************************************波特率参数表*****************************************/
typedef enum{
    UART0,
    UART1,
    UART2,
    UART3
}UART_CHA_enum;//串口可选通道枚举

typedef enum{
    UART_SMCLK,
    UART_ACLK,
    UART_DEFAULTCLK
}UART_CLK_enum;//串口时钟可选通道枚举

extern void UART_send_string(UART_CHA_enum UART_CHA,char*txt);
extern void UART_send_short(UART_CHA_enum UART_CHA,uint16 num);
extern void UART_send_int(UART_CHA_enum UART_CHA,uint32 num);
extern void UART_IRQ_set(UART_CHA_enum UART_CHA);
extern void UART_IRQRX_set(UART_CHA_enum UART_CHA);
extern void UART_USIC_init(UART_CHA_enum UART_CHA);
extern void UART_PIN_sel(UART_CHA_enum UART_CHA);
extern void UART_CLK_sel(UART_CHA_enum UART_CHA,UART_CLK_enum UART_CLK);
extern void UART_Baunds_set(UART_CHA_enum UART_CHA,int Baunds );
extern uint8 UART_BRS_val(int Baunds);
extern void UART_init(UART_CHA_enum UART_CHA,int Baunds );
extern void UART_send_Byte(UART_CHA_enum UART_CHA,uint8 Data);
extern uint8 UART_recv_Byte(UART_CHA_enum UART_CHA);
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
