#define PORTC (*(volatile unsigned char *)0x35)
#define DDRC  (*(volatile unsigned char *)0x34)
#define PINC  (*(volatile unsigned char *)0x33)

#define PORTA (*(volatile unsigned char *)0x3b)
#define DDRA  (*(volatile unsigned char *)0x3a)
#define PINA  (*(volatile unsigned char *)0x39)

#define PORTB (*(volatile unsigned char *)0x38)
#define DDRB  (*(volatile unsigned char *)0x37)
#define PINB  (*(volatile unsigned char *)0x36)

#define PORTD (*(volatile unsigned char *)0x32)
#define DDRD  (*(volatile unsigned char *)0x31)
#define PIND  (*(volatile unsigned char *)0x30)

#define  READ_BIT(reg,bit)		((reg>>bit)&1)
#define SET_BIT(reg,bit)	(reg=reg|(1<<bit))
#define CLR_BIT(reg,bit)	(reg=reg&~(1<<bit))

#define F_CPU 8000000
#include <util/delay.h>


#define STARTVALUE 12

void sevenprint (char num)
{
	char arr[10]={0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};
	char d0=num/10;
	char d1=num%10;
	
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

typedef enum {
	stop=0,
	start,
	buzzzz
	}state_t;


typedef enum {
	notpressed,
	pressed
}buttonState_t;

typedef enum {
	config,
	timer
}Mode_t;

state_t togglestate(state_t state)
{
	if (state==start)
	{
		return stop;
	}
	else
	{
		return start;
	}
}

Mode_t togglemode(Mode_t mode)
{
	if (mode==config)
	{
		return timer;
	}
	else 
	{
		return config;
	}
}	
	
int main(void)
{
	unsigned char  xfirst =STARTVALUE;
	unsigned char x=xfirst;
	
    DDRD=0;
	DDRC=0xff;
	DDRA=0xff;
	PORTC=0;
	
	
	state_t state = stop;
	Mode_t mode =config;
	
	sevensegBCD(x);
    while (1) 
    {
		if (mode==config)
		{
			 SET_BIT(PORTC,0);
			
			if (!READ_BIT(PIND,2)){        //up
				for (int j=0;j<20;j++)
				{
					
					if (x==100)
					{
						xfirst=0;
						x=0;
					}
					
					sevenprint(x);
					_delay_ms(1);
				}
				x=++xfirst;
				while(!READ_BIT(PIND,2))   
			{
				for (int j=0;j<20;j++)
				{
					
					if (x==100)
					{
						xfirst=0;
						x=0;
					}
					
					sevenprint(x);
					_delay_ms(2);
				}
				x=++xfirst;
				
				
			}
			}
			
			if (!READ_BIT(PIND,3)){      //down
				for (int j=0;j<20;j++)
				{
					if (x==0xff)
					{
						xfirst=99;
						x=99;
					}
					sevenprint(x);
					_delay_ms(1);
				}
				x=--xfirst;
				
				
			while(!READ_BIT(PIND,3)) 
			{
				for (int j=0;j<20;j++)
				{
					
					if (x==0xff)
					{
						xfirst=99;
						x=99;
					}
					sevenprint(x);
					_delay_ms(2);
				}
				x=--xfirst;
				
				
				
			}
			}
			if (!READ_BIT(PIND,4)) //mode
			{
				_delay_ms(10);
				mode=togglemode(mode);
				while(!READ_BIT(PIND,4));
				
			}
			sevenprint(x);
		}
	if (mode==timer)
	{
		CLR_BIT(PORTC,0);
			for (int i=0;i<100;i++)
			{
				if (!READ_BIT(PIND,2)) //start stop
				{
					_delay_ms(5);
					state=togglestate(state);
					while(!READ_BIT(PIND,2));
				}
				
				if (!READ_BIT(PIND,3)) //reset
				{
					_delay_ms(5);
					state=stop;
					x=xfirst;
					while(!READ_BIT(PIND,3));
					
				}
				if (!READ_BIT(PIND,4)) //mode
				{
					_delay_ms(10);
					mode=togglemode(mode);
					while(!READ_BIT(PIND,4));
					break;
					
				}
				sevenprint(x);
				
				
				
				
			}
	}
	if (state==buzzzz)
	{
		while(READ_BIT(PIND,3)) //reset to exit buzzer mode
		{
			SET_BIT(PORTC,5);
			_delay_ms(100);
			CLR_BIT(PORTC,5);
			_delay_ms(100);
		}
		state=config;
		
	}	
	
	if (state==start)
	{
		x--;
		if (x==0)
		{
			state=buzzzz;
		}
	}
}

}