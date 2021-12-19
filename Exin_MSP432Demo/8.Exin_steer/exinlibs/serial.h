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
#ifndef __serial_H
#define __serial_H

#define uint8 unsigned char

#define DATA_TRANSMIT_NUM 5
#define DATA_RECEIVE_NUM 24
#define SERIAL_TIMEOUT 100

typedef struct
{
    uint8 head;
    uint8 data[DATA_TRANSMIT_NUM];
    uint8 verify;
    uint8 tail;
}TX_STACK;

typedef struct
{
    uint8 head;
    uint8 data[DATA_RECEIVE_NUM];
    uint8 verify;
    uint8 tail;
    uint8 pr;
    uint8 lock_flag;
}RX_STACK;

typedef enum
{
    UNLOCK=0,
    LOCKED,
}LOCK_t;

typedef enum
{
    serial_synchronization=0,
    serial_skip,
    serial_select,
    serial_while,
    get,

    FLAG_MAX,
}flag_t;

typedef enum
{
    serial_start=0,

    TIME_MAX
}time_t;


extern uint8 serial[12];
extern char flag[FLAG_MAX];
extern char timee[TIME_MAX];


void serial_send();
//void serial_receive(UART_Type * uratn);
//void serial_receive_process(void);
void serial_transmit_process();
void serial_transmit_init();
void serial_receive_init();
void BLE_control();
void Turn();
void Back();

#endif
