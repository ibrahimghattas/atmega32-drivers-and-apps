/*
 * UART_Services.h
 *
 * Created: 8/15/2023 5:33:44 PM
 *  Author: Bero
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

void UART_SendString(u8*str);

void UART_ReceiveString(u8*str);
void UART_ReceiveString10(u8*str);
void UART_SendNumber(u32 num);

u8 endian_check(void);

u32 endian_convert_u32(u32 num);


void UART_SendStringCheckSum(u8*str);

u8 UART_ReceiveStringCheckSum(u8*str);



#endif /* UART_SERVICES_H_ */