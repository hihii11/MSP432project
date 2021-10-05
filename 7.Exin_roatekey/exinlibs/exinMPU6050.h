/*-----------------------------------------------------------------------------------------------------
【平    台】CCS
【适 用 单 片 机】msp432P401R
【底 层 库】TIVA WARE /msp432p4xx
【开 发】e芯工作室
/*@@ 库仅供参考 后果自负
 *
 * 版本 v1.0
 * 时间 2021年10月5日21:10:17
-------------------------------------------------------------------------------------------------------*/

#ifndef _exinMPU6050_h_
#define _exinMPU6050_h_

#define PI 3.1415926

typedef enum
{
  POWER1=0,
  POWER2=1,
  SMPLRT_DIV,
  FILTER,
  GYRO_CONFIG,
  ACCEL_CONFIG,
  AX_H,
  AX_L,
  AY_H,
  AY_L,
  AZ_H,
  AZ_L,
  TEMP_H,
  TEMP_L,
  GX_H,
  GX_L,
  GY_H,
  GY_L,
  GZ_H,
  GZ_L,
  FIFO,
  I2C_MST,
  INT_ENABLE,
  INT_PIN,
  USER,
  ID,
} MPU_Reg_Name;
MPU_Reg_Name MPU6050;
extern const uint8 MPU_reg[50];
extern uint8 MPU6050_write_Byte(uint8 reg,uint8 data);
extern uint8 MPU_read_Byte(uint8 reg);
extern void MPU_init();
extern uint8 MPU_Write_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf);
extern uint8 MPU_Read_Len(uint8 addr,uint8 reg,uint8 len,uint8 *buf);
extern short MPU_Get_Temp();
extern uint8 MPU_Get_Gyro(short * gx,short * gy,short * gz);
extern uint8 MPU_Get_Acc(short * ax,short * ay,short * az);
extern short MPU_Get_Angel(short ax,short ay,short az,float * roll,float * pitch,float *yaw);
extern float Low_filter(float K1,float angle_m, float gyro_m);
#endif /* EXINLIBS_EXINMPU6050_H_ */
