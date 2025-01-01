

#include <MemMap.h>
#include <Utils.h>
#include "SevenSegm.h"



void sevenprint (char num)
{
	char arr[10]={0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};
	unsigned char d0=num/10;
	unsigned char d1=num%10;
	
	CLR_BIT(PORTC,6);
	SET_BIT(PORTC,7);
	
	PORTA=(arr[d0]);
	
	_delay_ms(5);
	CLR_BIT(PORTC,7);
	SET_BIT(PORTC,6);
	
	PORTA=arr[d1];
	
	_delay_ms(5);
	
	
}

void  sevensegBCD(int num)
{
	char d0,d1;
	d0=num/10;
	d1=num%10;
	PORTD=d1;
	PORTD=PORTD|(d0<<4);
}



