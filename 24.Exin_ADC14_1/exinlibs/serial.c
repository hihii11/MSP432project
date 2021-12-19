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
#include "headfile.h"
#include "serial.h"

RX_STACK rx_stack;
TX_STACK tx_stack;
uint8 data_receive;

uint8 serial[12]={1,2,3,4};
extern int get_da_temp[5];
int test=0;
void serial_transmit_process() //閸忓牅缍�8閸氬酣鐝�8
{
	uint8 data_prcc = 0;
	//test=ADS_RCV_GetString(7);
	tx_stack.data[data_prcc++] |= (unsigned int)LMT_DataHandle();
	tx_stack.data[data_prcc++] |= ADS_RCV_GetString(6);
	tx_stack.data[data_prcc++] |= ADS_RCV_GetString(7);
	tx_stack.data[data_prcc++] |=ADS_RCV_GetString(8);
	tx_stack.data[data_prcc++] |=ADS_RCV_GetString(9);

	serial_send();
	serial_transmit_init();
}
/*
void serial_receive_process(void)
{
	flag[serial_synchronization] = 0;
	uint8 sum = 0, i = 0;
	uint8 data_prc = 0;
	if (rx_stack.lock_flag == LOCKED)
	{
		for (i = 0; i < DATA_RECEIVE_NUM; i++)
		{
			sum += rx_stack.data[i];
		}

		if (rx_stack.verify == sum)
		{

			flag[get] = rx_stack.data[data_prc++];

			data_prc = 0;
		}
		rx_stack.lock_flag = UNLOCK;
	}
}*/

void serial_send()
{
    uint8 i = 0;
	tx_stack.verify = 0;
	  MAP_UART_transmitData(EUSCI_A3_BASE,  0xA5);
	for ( i = 0; i < DATA_TRANSMIT_NUM; i++)
	{
	    MAP_UART_transmitData(EUSCI_A3_BASE, tx_stack.data[i]);
		tx_stack.verify += tx_stack.data[i];
	}
	//閸欐垿锟戒焦鐗庢灞界摟閼猴拷
	 MAP_UART_transmitData(EUSCI_A3_BASE, tx_stack.verify);
	//閸欐垿锟戒胶绮ㄩ弶鐔风摟閼猴拷
	 MAP_UART_transmitData(EUSCI_A3_BASE, 0X5A);
}
/*
void serial_receive(UART_Type *uratn)
{
	if (rx_stack.lock_flag == UNLOCK)
	{
		for (uint8 i = 0; i < DATA_RECEIVE_NUM + 3; i++)
		{
			timee[serial_start] = systime.get_time_ms();
			data_receive = UART_GetChar(uratn);
			if (flag[serial_skip] == 1)
			{
				serial_receive_init();
				flag[serial_skip] = 0;
				break;
			}
			else
			{
				switch (i)
				{
				case 0:
					flag[serial_select] = 0;
					break;
				case DATA_RECEIVE_NUM + 1:
					flag[serial_select] = 2;
					break;
				case DATA_RECEIVE_NUM + 2:
					flag[serial_select] = 3;
					break;
				default:
					flag[serial_select] = 1;
					break;
				}
				switch (flag[serial_select])
				{
				case 0:
					rx_stack.head = data_receive;
					break;
				case 1:
					rx_stack.data[rx_stack.pr++] = data_receive;
					break;
				case 2:
					rx_stack.verify = data_receive;
					break;
				case 3:
					rx_stack.tail = data_receive;
					rx_stack.lock_flag = LOCKED;
					break;
				default:
					break;
				}
				if (rx_stack.head != 0xA5)
					flag[serial_skip] = 1;
			}
			if (rx_stack.tail == 0x5A)
			{
				flag[serial_synchronization] = 1;
				break;
			}
		}
		if (flag[serial_synchronization] == 1)
			serial_receive_process();
		serial_receive_init();
	}
}

void serial_receive_init()
{
	rx_stack.pr = 0;
	for (uint8 i = 0; i < DATA_RECEIVE_NUM; i++)
		rx_stack.data[i] = 0;
	rx_stack.lock_flag = UNLOCK;
	rx_stack.head = 0;
	rx_stack.tail = 0;
	flag[serial_while] = 1;
}
*/
void serial_transmit_init()
{
    uint8 i = 0;
	for (i = 0; i < DATA_TRANSMIT_NUM; i++)
		tx_stack.data[i] = 0;
}

// //-------------------------------------------------------------------------*
// //閸戣姤鏆熼崥锟�: UART_GetChar
// //閸旓拷  閼筹拷: 閸欐垿锟戒礁鐡х粭锔胯(闁拷 NULL 閸嬫粍顒涢崣鎴︼拷锟�)
// //閸欙拷  閺侊拷: uratn:濡�虫健閸氬秴顩ч敍姝嶢RT0
// //鏉╋拷  閸ワ拷: 娑撴彃褰涢弨璺哄煂閻ㄥ嫭鏆熼幑锟�
// //缁狅拷  娓氾拷: UART_GetChar (UART4); 閼惧嘲褰囨稉鎻掑經閺�璺哄煂閻ㄥ嫭鏆熼幑锟�
// //-------------------------------------------------------------------------*
// char UART_GetChar(UART_Type * uratn)
// {
//      /* 缁涘绶熼幒銉︽暪濠娾�茬啊 */
//     while (!(UART_S1_REG(uratn) & UART_S1_RDRF_MASK))
//     {
// //      if(enable[serial_while])  //閽冩繄澧拫鍐槸閸ｃ劋濞囬懗锟�
// //          timee[serial_start]=systime.get_time_ms();
//       if(systime.get_time_ms() - timee[serial_start] > SERIAL_TIMEOUT )
//             {
//               flag[serial_skip]=1;
//               break;
//             }
//     }

//     /* 閼惧嘲褰囬幒銉︽暪閸掓壆娈�8娴ｅ秵鏆熼幑锟� */
//     return UART_D_REG(uratn);
// }
