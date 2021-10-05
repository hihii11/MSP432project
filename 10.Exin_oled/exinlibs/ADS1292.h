#ifndef _ADS1292_h
#define _ADS1292_h
#ifdef __cplusplus
extern "C"
{
#endif

extern long int breath;//呼吸
extern long int heart_beat;//心跳

extern uint8 data[10];//接收数据包 格式(AA AA <四位呼吸> <四位心跳>)
                                        //<低16位    高16位> 0000 0000 0000 0000 0000 0000 0000 0000
                                                        //    data5    data4      data3     data2
extern uint8 num;
extern void ADS1292_data(uint8 UART_BUFF);

#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
