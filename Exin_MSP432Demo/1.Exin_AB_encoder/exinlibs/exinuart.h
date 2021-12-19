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
//DCO为48Mhz
//在   CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
//CS_CTL1_SELM_3|CS_CTL1_DIVS__16;这一项中  由于MCLK分频为CS_CTL1_DIVS__16，即16分频，所以MCLK为3000000hz

//若修改了主时钟或者MCLK分配时钟，此处宏定义应修改

/*******************************************************波特率参数表*****************************************/
#define MCLK_FRE            3000000//串口使用MCLK时钟具体MCLK分频可以查看exinsystem.c
//任意波特率配置
//填写baunds 得到配置
#define BAUNDS_BF           2400    //此处填写波特率  波特率必须小于MCLK_FRE/2
#define BRDIV_BAUNDS_BF     (MCLK_FRE/BAUNDS_BF)>>4
#define UCxBRF_BAUNDS_BF    (int)(((float)MCLK_FRE/BAUNDS_BF/16-MCLK_FRE/BAUNDS_BF/16)*16+0.5)
#define UCxBRS_BAUNDS_BF    (int)(((((float)MCLK_FRE/BAUNDS_BF/16-MCLK_FRE/BAUNDS_BF/16)*16+0.5)-UCxBRF_BAUNDS_BF)*16+0.5)
//115200波特率配置
#define BRDIV_115200        (MCLK_FRE/115200)>>4
#define UCxBRF_115200       (int)(((float)MCLK_FRE/115200/16-MCLK_FRE/115200/16)*16+0.5)
#define UCxBRS_115200       (int)(((((float)MCLK_FRE/115200/16-MCLK_FRE/115200/16)*16+0.5)-UCxBRF_115200)*16+0.5)
//9600
#define BRDIV_9600          (MCLK_FRE/9600)>>4
#define UCxBRF_9600         (int)(((float)MCLK_FRE/9600/16-MCLK_FRE/9600/16)*16+0.5)
#define UCxBRS_9600         (int)(((((float)MCLK_FRE/9600/16-MCLK_FRE/9600/16)*16+0.5)-UCxBRF_9600)*16+0.5)

//4800
#define BRDIV_4800          (MCLK_FRE/4800)>>4
#define UCxBRF_4800         (int)(((float)MCLK_FRE/4800/16-MCLK_FRE/4800/16)*16+0.5)
#define UCxBRS_4800         (int)(((((float)MCLK_FRE/4800/16-MCLK_FRE/4800/16)*16+0.5)-UCxBRF_4800)*16+0.5)

/*******************************************************波特率参数表*****************************************/


extern void UART_send_string(uint32_t moduleInstance,char*txt);
extern void UART_send_Num(uint32_t moduleInstance,unsigned int num);
extern void UART0_init();
extern void UART2_init();
extern void UART0_TEST();
extern void UART3_init();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
