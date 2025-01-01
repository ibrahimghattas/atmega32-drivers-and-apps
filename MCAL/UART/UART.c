/*
 * UART.c
 *
 * Created: 8/12/2023 2:25:28 AM
 *  Author: Bero
 */ 



#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "UART_interface.h"
#include "UART_Cfg.h"




void UART_Init(void)
{
	//baud rate 9600
	UBRRL=51;
	//normal speed
	CLR_BIT(UCSRA,U2X);
	
	
	//frame (stop ,data ,parity) 1 STOP NO PARITY 8 DATA
	
	// ENABLE RX TX
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}




u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}


u8 UART_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(UCSRA,RXC))
	{
		
		*pdata=UDR;
		return 1;
	}
	return 0;
}