#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
 #include "DIO_private.h"
extern const DIO_PinStatus_type DIO_PinsStatusArr[TOTAL_PINS];




void DIO_Init(void)
{
	for (DIO_Pin_type i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,DIO_PinsStatusArr[i]);
	}
}
void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	u8 port=pin/8;
	u8 pin_num=pin%8;
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
			
		}
		break;
		
	}
}

void DIO_WritePin(DIO_Pin_type pin ,DIO_PinVoltage_type volt)
{
	u8 port=pin/8;
	u8 pin_num=pin%8;
	switch (volt)
	{
		case HIGH:
			switch(port)
			{
				case PA:
				SET_BIT(PORTA,pin_num);
				
				break;
				case PB:
				SET_BIT(PORTB,pin_num);
				
				break;
				case PC:
				SET_BIT(PORTC,pin_num);
				break;
				case PD:
				SET_BIT(PORTD,pin_num);
				break;
				
			}
			break;
		
			case LOW:
			switch(port)
			{
				case PA:
				CLR_BIT(PORTA,pin_num);
				
				break;
				case PB:
				CLR_BIT(PORTB,pin_num);
				
				break;
				case PC:
				CLR_BIT(PORTC,pin_num);
				break;
				case PD:
				CLR_BIT(PORTD,pin_num);
				break;
				
			}
			break;
	}
	
}



DIO_PinVoltage_type	DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_Port_type port=pin/8;
	u8 pin_num=pin%8;
	DIO_PinVoltage_type volt=LOW;
	
	switch(port)
	{
		case PA:
		
		volt=READ_BIT(PINA,pin_num);
		break;
		case PB:
		
		volt=READ_BIT(PINB,pin_num);
		break;
		case PC:
		
		volt=READ_BIT(PINC,pin_num);
		break;
		case PD:
		
		volt=READ_BIT(PIND,pin_num);
		break;
	}
	
	return volt;
}


void DIO_WritePort(DIO_Port_type port,u8 data)
{
	switch (port)
	{
		case PA:
			PORTA=data;
			break;
		case PB:
			PORTB=data;
			break;
		case PC:
			PORTC=data;
			break;
		case PD:
			PORTD=data;
			break;
	}
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	u8 port=pin/8;
	u8 pin_num=pin%8;
	
	switch(port)
	{
		case PA:
		TOGGLE_BIT(PORTA,pin_num);
		
		break;
		case PB:
		TOGGLE_BIT(PORTB,pin_num);
		
		break;
		case PC:
		TOGGLE_BIT(PORTC,pin_num);
		break;
		case PD:
		TOGGLE_BIT(PORTD,pin_num);
		break;
		
	}
	
}