//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : oled.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   :
//  功能描述   : 0.96寸OLED 接口演示例程(MSP430F5438A系列)
//  驱动IC     :SSD1306
//              说明:
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接3.3v电源
//              D0(SCL)   P86（时钟）
//              D1(SDA)  P84（数据）
//              RES  接P83
//              DC   接P91
//              CS   接P93
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   :
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H

#include <driverlib.h>

extern uint8_t screen_buf[128][64];
extern unsigned char bmp[1024];
extern void oled_update(char mode);
extern void OLED_PutPixel(unsigned char x,unsigned char y);
extern void OLED_pos_clr(unsigned char x,unsigned char y);
extern void OLED_Showfloat(unsigned char x, unsigned char y, float din);
#define u8 unsigned char
#define u32 unsigned int
#define OLED_CMD 0  //写命令
#define OLED_DATA 1 //写数据

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI  时钟D0
//#define       OLED_SSD1306_SCLK_DIR           (P1DIR)
//#define       OLED_SSD1306_SCLK_OUT           (P1OUT)
#define OLED_SSD1306_SCLK_PIN_NUM (GPIO_PIN0)
#define OLED_SSD1306_SCLK_PORT_NUM (GPIO_PORT_P6)

#define OLED_SSD1306_SCLK_IO_INIT (GPIO_setAsOutputPin(OLED_SSD1306_SCLK_PORT_NUM, OLED_SSD1306_SCLK_PIN_NUM))
#define OLED_SCLK_Set() (GPIO_setOutputHighOnPin(OLED_SSD1306_SCLK_PORT_NUM, OLED_SSD1306_SCLK_PIN_NUM))
#define OLED_SCLK_Clr() (GPIO_setOutputLowOnPin(OLED_SSD1306_SCLK_PORT_NUM, OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI 数据D1
//#define       OLED_SSD1306_SDIN_DIR           (P1DIR)
//#define       OLED_SSD1306_SDIN_OUT           (P1OUT)
#define OLED_SSD1306_SDIN_PIN_NUM (GPIO_PIN3)
#define OLED_SSD1306_SDIN_PORT_NUM (GPIO_PORT_P4)//3.2

#define OLED_SSD1306_SDIN_IO_INIT (GPIO_setAsOutputPin(OLED_SSD1306_SDIN_PORT_NUM, OLED_SSD1306_SDIN_PIN_NUM))
#define OLED_SDIN_Set() (GPIO_setOutputHighOnPin(OLED_SSD1306_SDIN_PORT_NUM, OLED_SSD1306_SDIN_PIN_NUM))
#define OLED_SDIN_Clr() (GPIO_setOutputLowOnPin(OLED_SSD1306_SDIN_PORT_NUM, OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 数据/命令DC
//#define       OLED_SSD1306_DC_DIR             (P1DIR)
//#define       OLED_SSD1306_DC_OUT             (P1OUT)
#define OLED_SSD1306_DC_PIN_NUM (GPIO_PIN1)
#define OLED_SSD1306_DC_PORT_NUM (GPIO_PORT_P6)

#define OLED_SSD1306_DC_IO_INIT (GPIO_setAsOutputPin(OLED_SSD1306_DC_PORT_NUM, OLED_SSD1306_DC_PIN_NUM))
#define OLED_DC_Set() (GPIO_setOutputHighOnPin(OLED_SSD1306_DC_PORT_NUM, OLED_SSD1306_DC_PIN_NUM))
#define OLED_DC_Clr() (GPIO_setOutputLowOnPin(OLED_SSD1306_DC_PORT_NUM, OLED_SSD1306_DC_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 ??片选CS
//#define       OLED_SSD1306_CE_DIR             (P1DIR)
//#define       OLED_SSD1306_CE_OUT             (P1OUT)
#define OLED_SSD1306_CE_PIN_NUM (GPIO_PIN5)
#define OLED_SSD1306_CE_PORT_NUM (GPIO_PORT_P1)

#define OLED_SSD1306_CE_IO_INIT (GPIO_setAsOutputPin(OLED_SSD1306_CE_PORT_NUM, OLED_SSD1306_CE_PIN_NUM))
#define OLED_CS_Set() (GPIO_setOutputHighOnPin(OLED_SSD1306_CE_PORT_NUM, OLED_SSD1306_CE_PIN_NUM))
#define OLED_CS_Clr() (GPIO_setOutputLowOnPin(OLED_SSD1306_CE_PORT_NUM, OLED_SSD1306_CE_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 复位/RES
//#define       OLED_SSD1306_RST_DIR            (P2DIR)
//#define       OLED_SSD1306_RST_OUT            (P1OUT)
#define OLED_SSD1306_RST_PIN_NUM (GPIO_PIN0)
#define OLED_SSD1306_RST_PORT_NUM (GPIO_PORT_P4)

#define OLED_SSD1306_RST_IO_INIT (GPIO_setAsOutputPin(OLED_SSD1306_RST_PORT_NUM, OLED_SSD1306_RST_PIN_NUM))
#define OLED_RST_Set() (GPIO_setOutputHighOnPin(OLED_SSD1306_RST_PORT_NUM, OLED_SSD1306_RST_PIN_NUM))
#define OLED_RST_Clr() (GPIO_setOutputLowOnPin(OLED_SSD1306_RST_PORT_NUM, OLED_SSD1306_RST_PIN_NUM))

#define SIZE 16
#define XLevelL 0x02
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64
//-----------------OLED端口定义----------------

//OLED控制用函数
void OLED_PutPixel(unsigned char x,unsigned char y);
void OLED_WR_Byte(u8 dat, u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y, u8 t);
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot);
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2);
void OLED_ShowString(u8 x, u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x, u8 y, u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
                  unsigned char y1, unsigned char BMP[]);
#endif
