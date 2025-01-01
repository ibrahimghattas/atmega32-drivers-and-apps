#include "StdTypes.h"
#include "UART_interface.h"
#include "UART_Services.h"



void UART_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}


void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[0]=UART_Receive();
	for (;(str[i-1]!=0x0d);)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	
}
void UART_ReceiveString10(u8*str)
{
	u8 i=0;
	str[0]=UART_Receive();
	for (;i<9;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	
}


void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
}

u32 UART_ReceiveNumber(void)
{
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u32 num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	return num;
	
}


// void UART_SendNumber2(u32 num)
// {
// 	u8*p=(u8*)&num;
// 	UART_Send(p[0]);
// 	UART_Send(p[1]);
// 	UART_Send(p[2]);
// 	UART_Send(p[3]);
// }
// 
// u32 UART_ReceiveNumber2(void)
// {
// 	u8*p;
// 	u32 num;
// 	p=&num;
// 	p[0]=UART_Receive();
// 	p[1]=UART_Receive();
// 	p[2]=UART_Receive();
// 	p[3]=UART_Receive();
// 	
// 	return num;
// 	
// }


u8 endian_check(void)
{
	u32 num=1;
	u8*p=(u8*)&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
	
}



u16 endian_convert_u16(u16 num)
{
	return num>>8|num<<8;
}

u32 endian_convert_u32(u32 num)    //0xffee5522   55220000  00000055
{
	
	
	u32 num2;
	
	num2=num>>24|num<<24|((num>>8) & 0x0000ff00)|((num<<8)&0x00ff0000);
	//num2=num>>24|num<<24|((num<<16)>>24)<<16|(num<<8)&0x00ff0000;
	return num2;
}


u32 endian_convert_u32_2(u32 num)    //0xffee5522   55220000  00000055
{
	u8*p=(u8*)&num;
	u8 temp;
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	return num;
}


void UART_SendStringCheckSum(u8*str)
{
	u8 i,l;
	u16 sum=0;
	for(l=0;str[l];l++)
	{
		sum+=str[l];
	}
	UART_Send(l);
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
	
}

u8 UART_ReceiveStringCheckSum(u8*str)
{
	u8 l=UART_Receive();
	u16 sum=0;
	for(u8 i=0;i<l;i++)
	{
		str[i]=UART_Receive();
		sum+=str[i];
	}
	u16 ReceivedSum=UART_Receive();
	 ReceivedSum|=(UART_Receive()<<8);
	
	if(sum==ReceivedSum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}