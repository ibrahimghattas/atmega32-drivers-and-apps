#include "StdTypes.h"
#include "UART_interface.h"
#include "UART_Services.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "UART_Control.h"
#include "Servo.h"
#include "Utils.h"
#include <string.h>

u8 GL_Str[20];
u8 Task_Str[20];
u8 Task_Val=0;
u8 new_command_flag =0;


// static u8 compare(u8* a,u8*b)
// {
// 	u8 flag=1;
// 	 while((*a<20) && (*b!='\0')) 
// 	 {
// 		 if(*a!=*b)
// 		 {
// 			 flag=0;
// 		 }
// 		 a++;
// 		 b++;
// 	 }
// 	 
// 	
// 	 
// 	 
// 	  return flag;
// }


void LEDON(u8 led)
{
	
		if (led==0)
		{
			DIO_WritePin(PINC0,HIGH);
		}
		else if (led==1)
		{
			DIO_WritePin(PINC1,HIGH);
		}
		else if (led==2)
		{
			DIO_WritePin(PINC2,HIGH);
		}
			
			
			
	}

void LEDOFF(u8 led)
{
	if (led==0)
	{
		DIO_WritePin(PINC0,LOW);
	}
	else if (led==1)
	{
		DIO_WritePin(PINC1,LOW);
	}
	else if (led==2)
	{
		DIO_WritePin(PINC2,LOW);
	}
}


static tasks_t tasks[4]={{"ledon",&LEDON},
                           {"ledoff",&LEDOFF},
						   {"lcd",&LCD_WriteNumber5},
					    	{"servo",&Servo_SetAngle}};


void ReceiveCommand(u8* str)
{
	
	if (new_command_flag==0)
	{
		for (u8 i=0;i<20;i++)
		{
			GL_Str[i]=0;
			Task_Str[i]=0;
			Task_Val=0;
		}
		u8 i=0;
		str[0]=UART_Receive();
		for (;(str[i]!=0x0a)&&(str[i-1]!=0x0d);)
		{
			i++;
			str[i]=UART_Receive();
		}
		str[i-1]=0;
		new_command_flag=1;
	}
	
	
	
}

u8 StrToInt(u8* str)
{
	u8 val=0;
	for(u8 i =0;str[i];i++)
	{
		val = val * 10 + ( str[i] - '0' );
	}
	
	return val;
}

void parser(u8 *GLSTR ,u8* Tstr,u8 *val)
{
	if (new_command_flag==1)
	{
		u8 i;
		for (i=0;GLSTR[i]!=' ';i++)
		{
			Tstr[i]=GLSTR[i];
			if (i==18)
			{
				Tstr[0]=0;
				GLSTR[0]=0;
				new_command_flag=0;
				return;
			}
		}
		Tstr[i+1]=0;
		*val=StrToInt(&GLSTR[i+1]);
		GLSTR[0]=0;
		new_command_flag=2;
	}
	
	
}
void checker_excuter(void)
{
	if (new_command_flag==2)
	{
		for (u8 i=0;i<4;i++)
		{
			if (!strcmp((char*)Task_Str,(char*)tasks[i].command_name))
			{

				tasks[i].f_ptr(Task_Val);
				

				
			}
			
			
		}
		new_command_flag=0;
	}
	
	
}

void UART_CONTROL_RUNNABLE(void)
{
	
	ReceiveCommand(GL_Str);
	parser(GL_Str,Task_Str,&Task_Val);
	checker_excuter();
	
	
}