/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨��CCS
���� �� �� Ƭ ����msp432P401R
���� �� �⡿TIVA WARE /msp432p4xx
���� ����eо������
/*@@ ������ο� ����Ը�
 *
 * �汾 v1.0
 * ʱ�� 2021��12��23��8:39:03
-------------------------------------------------------------------------------------------------------*/


#include "headfile.h"
#include "exinoled.h"
#include "exin_font.h"
#include "bmp.h"

uint8 GDDRAM[OLED_PAGE][OLED_SEG] = {0x00}; //OLED GDDRAM�ڴ�ӳ��

uint32 num_pow(uint8 m, uint8 n)
{
    uint32 result = 1;
    while (n--)
        result *= m;
    return result;
}

double sqr(double n) {
    double k=1.0;
    while(abs(k*k-n)>1e-2) {
        k=(k+n/k)/2;
    }
    return k;
}

/*************************************************
 * ��  ��  ��:OLED_SPI_configuration
 * ��       ��:��ʼ��OLED SPI�������
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_SPI_configuration(void)
{
    gpio_init(OLED_CK_PORT,OLED_CK_PIN,GPO,0);
    gpio_init(OLED_DI_PORT,OLED_DI_PIN,GPO,1);
    gpio_init(OLED_RES_PORT,OLED_RES_PIN,GPO,1);
    gpio_init(OLED_DC_PORT,OLED_DC_PIN,GPO,1);
    gpio_init(OLED_CS_PORT,OLED_CS_PIN,GPO,1);
}

/*************************************************
 * ��  ��  ��:SPI_write_byte
 * ��       ��:SPI����һ���ֽ�
 * ��       ��:data:��Ҫ���͵�8bits�ֽ�
 * ע������:��
 *************************************************/
void SPI_write_byte(uint8 data)
{
    uint8 i=0;
    for(i=0;i<8;i++)
    {
        gpio_set(OLED_CK_PORT,OLED_CK_PIN,0);
        if(data&0x80) gpio_set(OLED_DI_PORT,OLED_DI_PIN,1);  //�������
        else gpio_set(OLED_DI_PORT,OLED_DI_PIN,0);
        gpio_set(OLED_CK_PORT,OLED_CK_PIN,1);
        data<<=1;
    }
}

/*************************************************
 * ��  ��  ��:OLED_SPI_write_cmd
 * ��       ��:��OLED����һ��ָ��
 * ��       ��:spi_cmd:��Ҫ���͵�8bitsָ��
 * ע������:��
 *************************************************/
void OLED_SPI_write_cmd(uint8 spi_cmd)
{
    gpio_set(OLED_DC_PORT,OLED_DC_PIN,0);//����DC��ָʾ���ֽ�Ϊָ��
    gpio_set(OLED_CS_PORT,OLED_CS_PIN,0);//����Ƭѡ�ź�
    SPI_write_byte(spi_cmd);
    gpio_set(OLED_CS_PORT,OLED_CS_PIN,1);//����Ƭѡ�ź�
    gpio_set(OLED_DC_PORT,OLED_DC_PIN,1);
}

/*************************************************
 * ��  ��  ��:OLED_SPI_write_data
 * ��       ��:��OLED����һ������
 * ��       ��:spi_data:��Ҫ���͵�8bits����
 * ע������:��
 *************************************************/
void OLED_SPI_write_data(uint8 spi_data)
{
    gpio_set(OLED_DC_PORT,OLED_DC_PIN,1);//����DC��ָʾ���ֽ�Ϊ����
    gpio_set(OLED_CS_PORT,OLED_CS_PIN,0);//����Ƭѡ�ź�
    SPI_write_byte(spi_data);
    gpio_set(OLED_CS_PORT,OLED_CS_PIN,1);//����Ƭѡ�ź�
    gpio_set(OLED_DC_PORT,OLED_DC_PIN,1);
}


/*************************************************
 * ��  ��  ��:OLED_SetPos
 * ��       ��:����OLED��ʼλ��
 * ��       ��:x: ��ʼ������  0~127
 *          y: ��ʼҳ  0~7
 * ע������:��
 *************************************************/
void OLED_SetPos(uint8 x, uint8 y)
{
    OLED_SPI_write_cmd(0xb0|y);               //set OLED page 0~7
    OLED_SPI_write_cmd(((x&0xf0)>>4)|0x10);  //set high column address
    OLED_SPI_write_cmd((x&0x0f));       //set low column address
}

/*************************************************
 * ��  ��  ��:OLED_fill
 * ��       ��:���OLED��Ļ
 * ��       ��:fill_data:��Ҫ��������
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_fill(uint8 fill_data)
{
    uint8 i,j;
    OLED_SPI_write_cmd(0x20);//set OLED Memory Addressing Mode
    OLED_SPI_write_cmd(0x00);//set OLED Horizontal Addressing Mode

    for(i = 0;i < 8;i++)
    {
        for(j = 0;j < 128 ;j++)
        {
            OLED_SPI_write_data(fill_data);
            GDDRAM_Map_set(i,j, fill_data);
        }
    }
    OLED_SPI_write_cmd(0x20);//set OLED Memory Addressing Mode
    OLED_SPI_write_cmd(0x10);//set OLED PAGE Addressing Mode
}

/*************************************************
 * ��  ��  ��:OLED_clr
 * ��       ��:����
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_clr(void)
{
    OLED_fill(0x00);
}

/*************************************************
 * ��  ��  ��:OLED_Draw_Pixel
 * ��       ��:����Ļָ�����껭һ����
 * ��       ��:x:��ĺ����� 0~127
 *          y:���������0~63
 *          border_color:�����ɫ 0������õ� 1����������ص�
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_Pixel(uint8 x, uint8 y, uint8 border_color)
{
    if(x > 127)
    {
        x = 127;
    }
    else if(x < 0)
    {
        x = 0;
    }
    if(y > 63)
    {
        y = 63;
    }
    else if(y < 0)
    {
        y = 0;
    }
    uint8 page = y>>3;//get page of pixel
    uint8 data = (0x01)<<(y%8);
    if(border_color == 1)
    {
        GDDRAM_Map_set(page,x, GDDRAM[page][x]|data);
        OLED_SetPos(x, page);
        OLED_SPI_write_data(GDDRAM[page][x]);
    }
    else
    {
        GDDRAM_Map_set(page,x, GDDRAM[page][x]&(~data));
        OLED_SetPos(x, page);
        OLED_SPI_write_data(GDDRAM[page][x]);
    }
}

/*************************************************
 * ��  ��  ��:OLED_Draw_line
 * ��       ��:����Ļ�ϻ�һ��ֱ��
 *          �����:(x0,y0)�� (x1,y1)
 * ��       ��:x0:ֱ�ߵ���ʼλ�ú����� 0~127
 *          y0:ֱ�ߵ���ʼλ�������� 0~63
 *          x1:ֱ�ߵĽ���λ�ú����� 0~127
 *          y1:ֱ�ߵĽ���λ�������� 0~63
 *          border_color:�ߵ����ɫ 0��������� 1���������
 *          width:�������
 *          delay_time:���ߵ��ӳ�ʱ��
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_line(int16 x0, int16 y0, int16 x1, int16 y1, uint8 border_color,uint8 width,int delay_time)
{
    int16 delt_x,delt_y;
    uint8 i,j;
    uint8 chang_flg=0;
    float k;

    if(x0 > x1)
    {
        i=x1;x1=x0;x0=i;
        i=y1;y1=y0;y0=i;
        i=0;
        chang_flg = 1;
    }
    delt_x = x1 - x0;
    delt_y = y1 - y0;
    if(delt_x==0)//k do not exist
    {
        if(y0>=y1)
        {
            for(i=0;i<(y0-y1);i++)
            {
                for(j=0;j<width;j++)
                {
                    OLED_Draw_Pixel(x0+j,y0-i,border_color);
                }
                delay_us(delay_time);
            }
        }
        else
        {
            for(i=0;i<(y1-y0);i++)
            {
                for(j=0;j<width;j++)
                {
                    OLED_Draw_Pixel(x0+j,y0+i,border_color);
                }
                delay_us(delay_time);
            }
        }
    }
    else if(delt_y == 0)//when k = 0
    {
        if(chang_flg == 0)
        {
            for(i=0;i<delt_x;i++)
            {
                for(j=0;j<width;j++)
                {
                    OLED_Draw_Pixel(x0+i,y0-j,border_color);
                }
                delay_us(delay_time);
            }
        }
        else
        {
            for(i=0;i<delt_x;i++)
            {
                for(j=0;j<width;j++)
                {
                    OLED_Draw_Pixel(x1-i,y0-j,border_color);
                }
                delay_us(delay_time);
            }
        }
    }
    else//k exists
    {
        k = ((float)(delt_y))/((float)(delt_x));//get k
        float b = y1 - k * x1;
        if(k>-1&&k<1)
        {
            if(chang_flg==0)//x0 to x1
            {
                for(i=0;i<delt_x;i++)
                {
                    for(j=0;j<width;j++)
                    {
                        OLED_Draw_Pixel(x0+i,k*(x0+i)+b-j,border_color);
                    }
                    delay_us(delay_time);
                }
            }
            else
            {
                 ("check\n");
                for(i=0;i<delt_x;i++)
                {
                    for(j=0;j<width;j++)
                    {
                        OLED_Draw_Pixel(x1-i,k*(x1-i)+b-j,border_color);
                    }
                    delay_us(delay_time);
                }
            }
        }
        else
        {
            k = ((float)(delt_y))/((float)(delt_x));//get k
            float b = y1 - k * x1;
            if(chang_flg==0)
            {
                if(y0 > y1)
                {
                    for(i=0;i<(y0-y1);i++)
                    {
                        for(j=0;j<width;j++)
                        {
                            OLED_Draw_Pixel((y0-i-b)/k,y0-i-j,border_color);
                        }
                        delay_us(delay_time);
                    }
                }
                else
                {
                    for(i=0;i<(y1-y0);i++)
                    {
                        for(j=0;j<width;j++)
                        {
                            OLED_Draw_Pixel((y0+i-b)/k,y0+i-j,border_color);
                        }
                        delay_us(delay_time);
                    }
                }
            }
            else
            {
                if(y0 > y1)
                {
                    for(i=0;i<(y0-y1);i++)
                    {
                        for(j=0;j<width;j++)
                        {
                            OLED_Draw_Pixel((y1+i-b)/k,y1+i-j,border_color);
                        }
                        delay_us(delay_time);
                    }
                }
                else
                {
                    for(i=0;i<(y1-y0);i++)
                    {
                        for(j=0;j<width;j++)
                        {
                            OLED_Draw_Pixel((y1-i-b)/k,y1-i-j,border_color);
                        }
                        delay_us(delay_time);
                    }
                }
            }
        }
    }
}

/*************************************************
 * ��  ��  ��:OLED_Draw_Rectangle
 * ��       ��:����Ļ�ϻ�һ��������
 *          �����:(x0,y0)�� (x1,y1)
 * ��       ��:x0:�����ε���ʼλ�ú����� 0~127
 *          y0:�����ε���ʼλ�������� 0~63
 *          x1:�����εĽ���λ�ú����� 0~127
 *          y1:�����εĽ���λ�������� 0~63
 *          border_color:�����ε���ɫ 0������ó����� 1������ó�����
 *          width:�����α߿���
 *          delay_time:�������ε��ӳ�ʱ��
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_Rectangle(int16 x0, int16 y0, int16 x1, int16 y1, uint8 border_color,uint8 width,int delay_time)
{
     OLED_Draw_line(x0, y0, x1+width, y0,border_color,width,delay_time);
     OLED_Draw_line(x1, y0, x1, y1+1,border_color,width,delay_time);
     OLED_Draw_line(x1, y1, x0, y1,border_color,width,delay_time);
     OLED_Draw_line( x0, y1,x0, y0,border_color,width,delay_time);
}

/*************************************************
 * ��  ��  ��:OLED_Draw_Circle
 * ��       ��:����Ļ�ϻ�һ��Բ
 *          Բ��(x0,y0) ֱ��:diam
 * ��       ��:x0:Բ�ĺ����� 0~127
 *          y0:Բ�������� 0~63
 *          diam:Բֱ��
 *          border_color:Բ����ɫ 0�������Բ 1�������Բ
 *          width:Բ�߿���
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_Circle(int16 x0, int16 y0, uint8 diam,uint8 border_color,uint8 width)
{
    uint8 radius = (diam)>>1;
    int16 x1,y1;
    uint8 i = 0;
    while(i < width)
    {
        for(x1 = (x0-radius);x1 < (x0 + radius+1);x1++)
        {
                double newton_result = sqr((radius)*(radius)-(x1-x0)*(x1-x0));
                y1 = newton_result+y0;
                OLED_Draw_Pixel(x1, y1,border_color);
                y1 = -newton_result+y0;
                OLED_Draw_Pixel(x1, y1,border_color);

        }
        radius--;
        i++;
    }
}

/*************************************************
 * ��  ��  ��:OLED_Show_Char
 * ��       ��:����Ļ����ʾһ���ַ�
 * ��       ��:x:�ַ���ʾλ�ú����� 0~127
 *          y:�ַ���ʾλ��ҳ       0~7
 *          chr:�ַ�
 *          size:�ַ���С 8:6x8��С 16:8x16��С
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Show_Char(uint8 x, uint8 y, uint8 chr, uint8 size)
{
    uint8 index,i;
    index = chr - ' ';
    if(x > 121 && size == 8)
    {
        x = x%121;
        y ++;
    }
    if(x > 119 && size == 16)
    {
        x = x%119;
        y +=2;
    }

    switch(size)
    {
        case(8):
            OLED_SetPos(x, y);
            for (i = 0; i < 6; i++)
                {OLED_SPI_write_data(F6x8[index][i]);GDDRAM_Map_set(y,x+i, F6x8[index][i]);}
            break;
        case(16):
            OLED_SetPos(x, y);
            for (i = 0; i < 8; i++)
                {OLED_SPI_write_data(F8x16[(index<<4)+i]);GDDRAM_Map_set(y,x+i, F8x16[(index<<4)+i]);}
            OLED_SetPos(x, y+1);
            for (i = 0; i < 8; i++)
                {OLED_SPI_write_data(F8x16[(index<<4)+8+i]);GDDRAM_Map_set(y+1,x+i, F8x16[(index<<4)+8+i]);}
            break;
    }

}

/*************************************************
 * ��  ��  ��:OLED_Show_String
 * ��       ��:����Ļ����ʾһ���ַ���
 * ��       ��:x:�ַ�����ʾλ�ú����� 0~127
 *          y:�ַ�����ʾλ��ҳ       0~7
 *          str:�ַ���ָ��
 *          size:�ַ���С 8:6x8��С 16:8x16��С
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Show_String(uint8 x, uint8 y, uint8 * str, uint8 size)
{
    while(*str!='\0')
    {
        OLED_Show_Char(x , y , * str, size);
        if(size == 8)
            x = x + 6;
        else if(size == 16)
            x = x + 8;
        str++;
    }
}

/*************************************************
 * ��  ��  ��:OLED_Show_Num
 * ��       ��:����Ļ����ʾһ��������
 * ��       ��:x:������ʾλ�ú����� 0~127
 *          y:������ʾλ��ҳ       0~7
 *          num:��Ҫ��ʾ������
 *          len:��ʾ����
 *          size:�ַ���С 8:6x8��С 16:8x16��С
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Show_Num(uint8 x, uint8 y, int num ,uint8 len ,uint8 size)
{
    uint8 i = 1;
    uint8 num_len = 1;
    int temp = num/10;
    while(temp != 0)
    {
        num_len ++;
        temp /= 10;
    }

    while(i <= num_len)
    {
        temp = num;
        temp /= num_pow(10, num_len - i);
        OLED_Show_Char(x, y, '0'+temp,size);
        num = num - temp*num_pow(10, num_len - i);
        if(size == 8)
            x += 6;
        else if(size == 16)
            x += 8;
        i++;
    }

    while(num_len < len)
    {
        OLED_Show_Char(x, y, ' ',size);
        if(size == 8)
            x += 6;
        else if(size == 16)
            x += 8;
        num_len ++;
    }
}

/*************************************************
 * ��  ��  ��:OLED_Show_float
 * ��       ��:����Ļ����ʾһ��������
 * ��       ��:x:������ʾλ�ú����� 0~127
 *          y:������ʾλ��ҳ       0~7
 *          num:��Ҫ��ʾ������
 *          len:��ʾС�����λ��
 *          size:�ַ���С 8:6x8��С 16:8x16��С
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Show_float(uint8 x, uint8 y,float num ,uint8 len ,uint8 size)
{
    uint8 i = 1;
    uint8 num_len = 1;
    int temp = (int)num/10;
    int temp2 = (int)((num - (int)num)*num_pow(10, len));
    while(temp != 0)
    {
        num_len ++;
        temp /= 10;
    }

    while(i <= num_len)
    {
        temp = num;
        temp /= num_pow(10, num_len - i);
        OLED_Show_Char(x, y, '0'+temp,size);
        num = num - temp*num_pow(10, num_len - i);
        if(size == 8)
            x += 6;
        else if(size == 16)
            x += 8;
        i++;
    }
    OLED_Show_Char(x, y, '.',size);
    if(size == 8)
        x += 6;
    else if(size == 16)
        x += 8;
    OLED_Show_Num(x, y, temp2 , len,size);
}

/*************************************************
 * ��  ��  ��:OLED_Show_Hanzi
 * ��       ��:����Ļ����ʾһ������
 * ��       ��:x:������ʾλ�ú����� 0~127
 *          y:������ʾλ��ҳ       0~7
 *          index:����ʾ��������
 * ע������:�������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Show_Hanzi(uint8 x, uint8 y, uint8 index)
{
    uint8 i = 0;
    if(x > 111)
    {
        x = x%121;
        y ++;
    }
    OLED_SetPos(x, y);
    for(i = 0;i < 16; i++)
    {OLED_SPI_write_data(Chiness[index<<1][i]);GDDRAM_Map_set(y,x+i, Chiness[index<<1][i]);}
    OLED_SetPos(x, y+1);
    for(i = 0;i < 16; i++)
    {OLED_SPI_write_data(Chiness[(index<<1)+1][i]);GDDRAM_Map_set(y+1,x+i, Chiness[index<<1][i]);}
}

/*************************************************
 * ��  ��  ��:OLED_Draw_Bmp
 * ��       ��:����Ļ����ʾ��һ��BMPͼƬ
 * ��       ��:x0:��ʼ������ 0~127
 *          y0:��ʼҳ       0~7
            x1:���������� 0~127
 *          y1:����ҳ       0~7
 *          BMP:ͼ������
 * ע������:�ú�������ʾ��λ�������ͼ���ʽ
 *      �������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_Bmp(uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint8 BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++)
    {
        OLED_SetPos(x0, y);
        for (x = x0; x < x1; x++)
        {
            OLED_SPI_write_data(BMP[j]);
            GDDRAM_Map_set(y,x, BMP[j]);
            j++;
        }
    }
}

/*************************************************
 * ��  ��  ��:OLED_Draw_BmpPixel
 * ��       ��:����Ļ����ʾ��һ��BMPͼƬ
 * ��       ��:
 *          BMP:ͼ������
 * ע������:�ú���������ʾ��ֵ�����ͼ������
 *          �������ƺ���ʾ��ȫ����֪��ԭ��
 *************************************************/
void OLED_Draw_BmpPixel(uint8 BMP[])
{
    uint8 i,j;
    uint8 data = 0x00;
    OLED_SPI_write_cmd(0x20);//set OLED Memory Addressing Mode
    OLED_SPI_write_cmd(0x01);//set OLED Horizontal Vertical addressing Mode
    OLED_SetPos(0x00, 0x00);
    for(i = 0;i < 128;i++)
    {
        for(j = 0;j < 64; j++)
        {
            data = data>>1;
            data |=  BMP[i+j*128]<<(7);
            if((j+1)%8 == 0)
            {
                GDDRAM_Map_set(j/8,i, GDDRAM[(j)/8][i]|data);
                OLED_SPI_write_data(GDDRAM[(j)/8][i]);
                data = 0x00;
            }
        }
    }
    OLED_SPI_write_cmd(0x20);//set OLED Memory Addressing Mode
    OLED_SPI_write_cmd(0x10);//set OLED PAGE Addressing Mode
}

/*************************************************
 * ��  ��  ��:OLED_init
 * ��       ��:��ʼ��OLED
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_init(void)
{
    OLED_SPI_configuration();//IIC Master device init
    gpio_set(OLED_RES_PORT,OLED_RES_PIN,0);
    gpio_set(OLED_RES_PORT,OLED_RES_PIN,1);
    OLED_Delay;
    OLED_SPI_write_cmd(0xAE); //--turn off oled panel
	OLED_SPI_write_cmd(0x20); //---set low column address
	OLED_SPI_write_cmd(0x10); //---set high column address
	OLED_SPI_write_cmd(0xb0); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_SPI_write_cmd(0xc8); //--set contrast control register
	OLED_SPI_write_cmd(0x00); // Set SEG Output Current Brightness
	OLED_SPI_write_cmd(0x10); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_SPI_write_cmd(0x40); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_SPI_write_cmd(0x81); //--set normal display
	OLED_SPI_write_cmd(0xff); //--set multiplex ratio(1 to 64)
	OLED_SPI_write_cmd(0xa1); //--1/64 duty
	OLED_SPI_write_cmd(0xa6); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_SPI_write_cmd(0xa8); //-not offset
	OLED_SPI_write_cmd(0x3F); //--set display clock divide ratio/oscillator frequency
	OLED_SPI_write_cmd(0xa4); //--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_SPI_write_cmd(0xd3); //--set pre-charge period
	OLED_SPI_write_cmd(0x00); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_SPI_write_cmd(0xd5); //--set com pins hardware configuration
	OLED_SPI_write_cmd(0xf0);
	OLED_SPI_write_cmd(0xd9); //--set vcomh
	OLED_SPI_write_cmd(0x22); //Set VCOM Deselect Level
	OLED_SPI_write_cmd(0xda); //-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_SPI_write_cmd(0x12); //
	OLED_SPI_write_cmd(0xdb); //--set Charge Pump enable/disable
	OLED_SPI_write_cmd(0x20); //--set(0x10) disable
	OLED_SPI_write_cmd(0x8d); // Disable Entire Display On (0xa4/0xa5)
	OLED_SPI_write_cmd(0x14); // Disable Inverse Display On (0xa6/a7)
	OLED_SPI_write_cmd(0xaf); //--turn on oled panel
	
	OLED_SPI_write_cmd(0xAF); /*display ON*/
    GDDRAM_Map_clr();
    OLED_OFF();
    OLED_ON();
}

/*************************************************
 * ��  ��  ��:OLED_ON
 * ��       ��:OLED������Դ
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_ON(void)
{
    OLED_SPI_write_cmd(0X8D);
    OLED_SPI_write_cmd(0X14);
    OLED_SPI_write_cmd(0XAF);
}

/*************************************************
 * ��  ��  ��:OLED_OFF
 * ��       ��:OLED�رյ�Դ
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_OFF(void)
{
    OLED_SPI_write_cmd(0X8D);
    OLED_SPI_write_cmd(0X14);
    OLED_SPI_write_cmd(0XAE);
}

/*************************************************
 * ��  ��  ��:GDDRAM_Map_clr
 * ��       ��:OLED�ڴ�ӳ����պ���
 * ��       ��:��
 * ע������:��
 *************************************************/
void GDDRAM_Map_clr(void)
{
    uint8 i,j;
    for(i = 0;i < OLED_PAGE; i++)
    {
        for(j = 0;j < OLED_SEG; j++)
        {
            GDDRAM[i][j] = 0x00;
        }
    }
}

/*************************************************
 * ��  ��  ��:GDDRAM_Map_set
 * ��       ��:OLED����ӳ���ڴ�
 * ��       ��:��
 * ע������:��
 *************************************************/
void GDDRAM_Map_set(uint8 page,uint8 seg, uint8 data)
{
    if(page < OLED_PAGE && seg < OLED_SEG)
    {
        GDDRAM[page][seg] = data;
    }
}

/*************************************************
 * ��  ��  ��:OLED_test
 * ��       ��:OLED���Ժ���
 * ��       ��:��
 * ע������:��
 *************************************************/
void OLED_test()
{
    uint8 i = 0;
    int32 x0,y0,x1,y1,dir_flg=0,delay_time=0,finish_flg0=0,finish_flg1=0;
    uint8 state=0,state_count=0;

    x0 = 64;y0 = 32;
    x1 = 64;y1 = 32;

    OLED_Show_String(10, 2, "The OLED test!!!", 8);
    for(i=0;i<6;i++)
    {
        OLED_Show_Hanzi(10+16*i, 4, i);
    }
    delay_ms(2);
    while(1)
    {
        switch(state)
        {
            case(0):
                    OLED_Draw_Rectangle(x0+1, y0+1, x1-1,  y1-1,0,1,0);
                    OLED_Draw_Rectangle(x0--, y0--, x1++,  y1++,1,1,0);
                    delay_us(10000);

                    if(y0 <= 0)
                    {
                        state=1;state_count=0;
                        x0 = 32;y0 = 0;
                        x1 = 96;y1 = 63;
                    }
                break;
            case(1):
                    OLED_Draw_Rectangle(x0++, y0++, x1--,  y1--,1,1,0);
                    OLED_Draw_Rectangle(x0-1, y0-1, x1+1,  y1+1,0,1,0);
                    delay_us(5000);
                    state_count++;
                    if(state_count >= 31)
                    {
                        dir_flg = 0;i = 0;
                        x0 = 63;y0 = 32;
                        x1 = 63;y1 = 32;
                        state_count = 0;
                        state=3;
                    }break;
            case(3):
                    OLED_Draw_Rectangle(x0+2, y0+1, x1-2,  y1-1,0,1,0);
                    OLED_Draw_Rectangle(x0, y0, x1,  y1,1,1,0);
                    x0-=2;y0--;
                    x1+=2;y1++;
                    delay_us(5000);
                    if(state_count >= 31)
                    {
                        dir_flg = 1;state=4;
                        x0 = 0;y0 = 0;
                        x1 = 127;y1 = 63;
                    }

                    state_count++;
                    break;
            case(4):
                    if(y0<31)
                    {
                        OLED_Draw_Rectangle(x0, y0++, x1,  y1--,1,1,0);
                        OLED_Draw_Rectangle(x0, y0-1, x1,  y1+1,0,1,0);
                        delay_us(6000);
                    }
                    else
                    {
                        OLED_Draw_line(0, 32, 127, 32,1,1,0);
                        x0 = 64;y0 = 32;
                        x1 = 64;y1 = 32;
                        state=5;
                    }
                    break;
            case(5):
                    for(i=0;i<64;i++)
                    {
                        OLED_Draw_line(x0-i, y0, x1+i, y1,0,1,0);
                        delay_us(50000);
                    }

                    state = 6;
                    break;
            case(6):
                    x0 = 39;y0 = 16;
                    x1 = 89;y1 = 48;
                    for(i=0;i < 50;i++)
                    {
                        OLED_Draw_line(39, 16, x0+i,16 ,1,1,0);
                        OLED_Draw_line(89, 48, x1-i, 48,1,1,0);
                        delay_us(50000);
                    }
                    x0 = 39;y0 = 16;
                    x1 = 89;y1 = 48;
                    for(i=0;i < 25;i++)
                    {
                        OLED_Draw_line(x0, y0, x0+i,y0+i*1.7 ,1,1,0);
                        OLED_Draw_line(x1, y1, x1-i, y1-i*1.7,1,1,0);
                        delay_us(50000);
                    }
                    for(i=0;i < 25;i++)
                    {
                        OLED_Draw_line(64, 59, 64+i,59-i*1.7 ,1,1,0);
                        OLED_Draw_line(64, 10, 64-i, 10+i*1.7,1,1,0);
                        delay_us(50000);
                    }
                    state = 7;
                    break;
            case(7):
                        OLED_Draw_Rectangle(10, 61, 117,  63,1,1,0);
                        for(i = 0; i < 107;i++)
                        {
                            if(i%2 == 0)
                            {
                                OLED_Draw_Pixel(10+i, 62, 1);delay_us(400000);
                                OLED_Show_String(44, 3, "LOADING", 8);
                                OLED_Show_Num(56,4,((float)(i)/107)*100,3,8);
                                OLED_Show_String(72, 4, "%", 8);
                            }
                        }
                        state = 8;
            case(8):
                    OLED_Show_String(29, 5, "welcome user", 8);
                    delay_time = 50000;
                    while(state_count<3)
                    {
                        for(i = 0;i < 0x4f;i++)
                        {
                            OLED_SPI_write_cmd(0x81);
                            OLED_SPI_write_cmd(0xff - i);
                            delay_us(delay_time - i*i);
                        }
                        for(i = 0;i < 0x4f;i++)
                        {
                            OLED_SPI_write_cmd(0x81);
                            OLED_SPI_write_cmd(0xff + i);
                            delay_us(delay_time + i*i);
                        }
                        state_count++;
                    }
                    OLED_clr();
                    OLED_Draw_BmpPixel(bmp_pixel1);
                    delay_ms(4000);
                    OLED_SPI_write_cmd(0x81);
                    OLED_SPI_write_cmd(0xff);
                    state = 0;
                            break;
        }
    }
}

