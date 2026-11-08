/*
 * Modbus.h
 *
 *  Created on: 1 Eyl 2026
 *      Author: LENOVO
 */

#ifndef SRC_MODBUS_H_
#define SRC_MODBUS_H_


#define SZ_BUF 256
#define sz_buf  256
#define sz_pdu	253
#define sz_adu 	256

#define MODBUS_ID       	7
#define MODBUS_BAUD  		115200
#define MODBUS_TIM  		TIMER_6
#define MODBUS_TIM_OUT		3000


void MB_init(int baud);
unsigned char UART_get_data(void);        // fifo bağlantısı
void UART_send_data(void *data);   // gönderilecek veri tipi void * tipine dönüşmeli. ne gönderiecek belli değil çünkü.
int UART_get_line( unsigned char *pline);
void IUART_Send_data(void *data, int size);
void IUART_get_data(const void *buf,int size);
void Modbus_init(int baud);
void mb_timer_init(void);
int Own_Modbus_Req(uint8_t adr,unsigned char *pdu,int pdu_len);		//adu layer
uint16_t CRC16(uint8_t *pMsg, uint8_t len);
void mb_task(void);


#endif /* SRC_MODBUS_H_ */
