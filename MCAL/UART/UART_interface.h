/*
 * UART_interface.h
 *
 * Created: 8/12/2023 2:25:46 AM
 *  Author: Bero
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


typedef enum{
	UART_NORMALSPEED,
	UART_DOUBLESPEED
}UART_SPEED_t;

typedef enum{
	UART_NOPARITY,
	UART_EVENPARITY,
	UART_ODDPARITY
}UART_PARITY_t;

typedef enum{
	UART_FRAME5,
	UART_FRAME6,
	UART_FRAME7,
	UART_FRAME8,
	UART_FRAME9
}UART_FRAME_SIZE_t;
typedef enum{
	UART_1STOPBIT,
	UART_2STOPBIT
}UART_STOPBIT_t;

void UART_Init(void);

void UART_Send(u8 data);

u8 UART_Receive(void);

u8 UART_ReceivePerodic(u8*pdata);




#endif /* UART_INTERFACE_H_ */