

#ifndef UART_CONTROL_H_
#define UART_CONTROL_H_

void ReceiveCommand(u8* str);
void UART_CONTROL_RUNNABLE(void);

typedef struct  
{
	u8 command_name[20];
	void(*f_ptr)(u8) ;
}tasks_t;

typedef enum{
	LED_RED=1,
	LED_GREEN,
	LED_BLUE
	}Leds_t;


#endif /* UART_CONTROL_H_ */