#ifndef _ADS1292_h
#define _ADS1292_h
#ifdef __cplusplus
extern "C"
{
#endif

extern long int breath;//����
extern long int heart_beat;//����

extern uint8 data[10];//�������ݰ� ��ʽ(AA AA <��λ����> <��λ����>)
                                        //<��16λ    ��16λ> 0000 0000 0000 0000 0000 0000 0000 0000
                                                        //    data5    data4      data3     data2
extern uint8 num;
extern void ADS1292_data(uint8 UART_BUFF);

#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
