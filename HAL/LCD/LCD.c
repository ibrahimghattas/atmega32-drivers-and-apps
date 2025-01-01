#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"
#define  F_CPU   8000000
#include <util/delay.h>

#if LCD_MODE== _8_BIT

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}
void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

#else
void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	

	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}

void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	

	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);	
}
#endif

void NumToStr(s32 num,u8* str)
{
	
	s32  temp=num,len=0,rem;

	if (num<0)
	{
		str[0]='-';
		num=num*(-1);
		while(temp)
		{
			len++;
			temp=temp/10;
		}
		len++;

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%10;
			num=num/10;
			str[len-(i+1)]=rem+'0';
		}
		str[0]='-';
		str[len]=0;
	}
	else if (num==0)
	{
		str[0]='0';
		str[1]=0;
	}

	else
	{
		while(temp)
		{
			len++;
			temp=temp/10;
		}

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%10;
			num=num/10;
			str[len-(i+1)]=rem+'0';
		}

		str[len]=0;
	}



}

void HexToStr(s32 num,u8* str)
{
	
	s32  temp=num,len=0,rem;

	if (num<0)
	{
		str[0]='-';
		num=num*(-1);
		while(temp)
		{
			len++;
			temp=temp/16;
		}
		len++;

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%16;
			num=num/16;
			str[len-(i+1)]=rem+'0';
			if (rem>9)
			{
				rem=rem-10;
				str[len-(i+1)]=rem+'A';
			}
		}
		str[0]='-';
		str[len]=0;
	}
	else if (num==0)
	{
		str[0]='0';
		str[1]=0;
	}

	else
	{
		while(temp)
		{
			len++;
			temp=temp/16;
		}

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%16;
			num=num/16;
			
			str[len-(i+1)]=rem+'0';
			
			if (rem>9)
			{
				rem=rem-10;
				str[len-(i+1)]=rem+'A';
			}
		}

		str[len]=0;
	}



}

void BinToStr(s32 num,u8* str)
{
	
	s32  temp=num,len=0,rem;

	if (num<0)
	{
		str[0]='-';
		num=num*(-1);
		while(temp)
		{
			len++;
			temp=temp/2;
		}
		len++;

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%2;
			num=num/2;
			str[len-(i+1)]=rem+'0';
			
		}
		str[0]='-';
		str[len]=0;
	}
	else if (num==0)
	{
		str[0]='0';
		str[1]=0;
	}

	else
	{
		while(temp)
		{
			len++;
			temp=temp/2;
		}

		for (unsigned int i=0;i<len;i++)
		{
			rem=num%2;
			num=num/2;
			
			str[len-(i+1)]=rem+'0';
			
			
		}

		str[len]=0;
	}



}

// void WriteData(u8 data)
// {
// 	DIO_WritePin(RS,HIGH);
// 	DIO_WritePort(LCD_PORT,data);
// 	DIO_WritePin(EN,HIGH);
// 	_delay_ms(1);
// 	DIO_WritePin(EN,LOW);
// 	_delay_ms(1);
// }
// void WriteData4(u8 data)
//  {
// 
// PORTA =((PORTA | 0x78)&~(0x78))|((data& 0xf0)>>1);
// SET_BIT(PORTA,1);		/* RS=1, data reg. */
// SET_BIT(PORTA,2);
// _delay_us(1);
// CLR_BIT(PORTA,2);
// 
// _delay_us(200);
// 
// //LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
// PORTA =((PORTA | 0x78)&~(0x78))| ((data& 0x0f)<<3);
// SET_BIT(PORTA,1);
// SET_BIT(PORTA,2);
// _delay_us(1);
// CLR_BIT(PORTA,2);
// _delay_ms(2);
// }
void LCD_Init(void)
{
	_delay_ms(50);
	#if LCD_MODE== _4_BIT
	WriteIns(0x02);
	#endif
	WriteIns(0x28);
	WriteIns(0x0c);
	WriteIns(0x06);
	WriteIns(0x01);
}
// void LCD_Init4(void)
// {
// 	_delay_ms(50);
// 	WriteIns4(0x02);
// 	WriteIns4(0x28);
// 	WriteIns4(0x0c);
// 	
// 	WriteIns4(0x06);
// 	WriteIns4(0x01);
// 	_delay_ms(2);
// 	
// 	
// }
void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}
// void LCD_Clear4(void)
// {
// 	WriteIns4(0x01);
// 	_delay_ms(1);
// }

/**line 0:1 cell 0:15 **/
void LCD_GoTo(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80+cell);
	}
	else if(line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}
// void LCD_GoTo4(u8 line,u8 cell)
// {
// 	if (line==0)
// 	{
// 		WriteIns4(0x80+cell);
// 	}
// 	else if(line==1)
// 	{
// 		WriteIns4(0x80+0x40+cell);
// 	}
// }

void LCD_WriteString(char*str)
{
	
	for (u8 i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}
// void LCD_WriteString4(u8*str)
// {
// 	
// 	for (u8 i=0;str[i];i++)
// 	{
// 		LCD_WriteChar4(str[i]);
// 	}
// 	
// }
void LCD_WriteNumber(s32 num)
{
	u8 tempstr[1000];
	NumToStr(num,tempstr);
	LCD_WriteString((char*)tempstr);
}
void LCD_WriteNumber5(u8 num)
{
	u8 tempstr[1000];
	NumToStr(num,tempstr);
	LCD_WriteString((char*)tempstr);
}
void LCD_Write_4D(u16 num) //087
{
	LCD_WriteChar( ((num%10000)/1000)+'0');
	LCD_WriteChar( ((num%1000)/100)+'0');
	LCD_WriteChar( ((num%100)/10)+'0');
	LCD_WriteChar( ((num%10)/1)+'0');
}
// void LCD_WriteNumber4(s32 num)
// {
// 	u8 tempstr[1000];
// 	NumToStr(num,tempstr);
// 	LCD_WriteString4(tempstr);
// }
void LCD_WriteBinary(u8 num)
{
	u8 tempstr[1000];
	BinToStr(num,tempstr);
	LCD_WriteString((char*)tempstr);
}
// void LCD_WriteBinary4(u8 num)
// {
// 	u8 tempstr[1000];
// 	BinToStr(num,tempstr);
// 	LCD_WriteString4(tempstr);
// }

void LCD_WriteHex(u8 num)
{
	u8 tempstr[1000];
	HexToStr(num,tempstr);
	LCD_WriteString((char*)tempstr);
}
// void LCD_WriteHex4(u8 num)
// {
// 	u8 tempstr[1000];
// 	HexToStr(num,tempstr);
// 	LCD_WriteString4(tempstr);
// }
void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}
void LCD_WriteCharPos(u8 ch,u8 line,u8 cell)
{
	LCD_GoTo(line,cell);
	LCD_WriteChar(ch);
}

void LCD_CustomChar(u8 address,u8*pattern)
{
	WriteIns((address*8)+0x40);
	for(u8 i=0;i<8;i++ )
	{
		
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
	
}
void LCD_MoveString(u8*str)
{
	u8 l=0;
	for (u8 i=0;str[i];i++)
	{
		l++;
	}
	LCD_GoTo(0,0);
	for (u8 i=0;str[i];i++)
	{
		
		LCD_WriteChar(str[l-i]);
		_delay_ms(500);
		WriteIns(0x1c);
	}
	
}
void LCD_ShiftCursorLeft(void)
{
	
	WriteIns(0x10);
}

void LCD_WriteStringLength(u8*str,u16 len)
{
	
	for (u8 i=0;i<len;i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}