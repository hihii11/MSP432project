/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年12月23日8:29:47
-------------------------------------------------------------------------------------------------------*/

#ifndef EXINLIBS_EXINOLED_H_
#define EXINLIBS_EXINOLED_H_
#define           OLED_PAGE                       8                          //<OLED页数>
#define           OLED_SEG                        128                        //<OLED横向像素点>

#define           OLED_Delay                     delay_ms(200)              //OLED开机延时
extern uint8 GDDRAM[OLED_PAGE][OLED_SEG];//OLED内存映射

/*********************OLED引脚定义**********************/
#define     OLED_CK_PORT                         GPIO_PORT_P6//P6.0
#define     OLED_CK_PIN                          GPIO_PIN0

#define     OLED_DI_PORT                         GPIO_PORT_P4//P4.3
#define     OLED_DI_PIN                          GPIO_PIN3

#define     OLED_RES_PORT                        GPIO_PORT_P4//P4.0
#define     OLED_RES_PIN                         GPIO_PIN0

#define     OLED_DC_PORT                         GPIO_PORT_P6//P6.1
#define     OLED_DC_PIN                          GPIO_PIN1

#define     OLED_CS_PORT                         GPIO_PORT_P1//P1.5
#define     OLED_CS_PIN                          GPIO_PIN5


extern void OLED_SPI_configuration(void);
extern void SPI_write_byte(uint8 data);
extern void OLED_SPI_write_cmd(uint8 spi_cmd);
extern void OLED_SPI_write_data(uint8 spi_data);
extern void OLED_init(void);
extern void OLED_SetPos(uint8 x, uint8 y);
extern void OLED_fill(uint8 fill_data);
extern void OLED_ON(void);
extern void OLED_OFF(void);
extern void OLED_clr(void);
extern void OLED_Show_Char(uint8 x, uint8 y, uint8 chr, uint8 size);
extern void OLED_Show_String(uint8 x, uint8 y, uint8 * str, uint8 size);
extern void OLED_Show_Num(uint8 x, uint8 y, int num ,uint8 len ,uint8 size);
extern void OLED_Show_float(uint8 x, uint8 y,float num ,uint8 len ,uint8 size);
extern void OLED_Show_Hanzi(uint8 x, uint8 y, uint8 index);
extern void OLED_Draw_Bmp(uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint8 BMP[]);
extern void OLED_Draw_BmpPixel(uint8 BMP[]);
extern void OLED_Draw_Pixel(uint8 x, uint8 y, uint8 border_color);
extern void OLED_Draw_line(int16 xx0, int16 yy0, int16 xx1, int16 yy1, uint8 border_color,uint8 width,int delay_time);
extern void OLED_Draw_Rectangle(int16 x0, int16 y0, int16 x1, int16 y1, uint8 border_color,uint8 width,int delay_time);
extern void OLED_Draw_Circle(int16 x0, int16 y0, uint8 diam,uint8 border_color,uint8 width);
extern void OLED_test();

extern void GDDRAM_Map_clr(void);
extern void GDDRAM_Map_set(uint8 page,uint8 seg, uint8 data);




#endif /* EXINLIBS_EXINOLED_H_ */
