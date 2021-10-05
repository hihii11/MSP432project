#ifndef _exincitysensor_h
#define _exincitysensor_h
#ifdef __cplusplus
extern "C"
{
#endif

extern int num_ctl[10];
void Sensor_data_receive(unsigned char din);
void Exin_sensor_init();
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_GPIO_H__
