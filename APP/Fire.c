#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD/LCD_Interface.h"
#include "Sensors/Sensors_Interface.h"
#include "KeyPad/KeyPad_Interface.h"
#include "Fire_Interface.h"
#include "MemMap.h"
#include "Utils.h"

#define NO_KEY  'T'
u16 Temperatue;
u8 SmokeLevel;
u8 password[4]={'1','2','3','4'};
u16 PassAddr=0;
	u8 pasget[4];
u8	i=0,k;
FireStates_t state;

void eepromwrite(u16 addr,u8 data)
{
	while (READ_BIT(EECR,EEWE));
	EEAR=addr;
	EEDR=data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
}

u8 eepromread(u16 addr)
{
	while(READ_BIT(EECR,EEWE));
	
	EEAR = addr;
	
	SET_BIT(EECR,EERE);
	
	
	return EEDR;
}
void Fire_Init(void)
{
	state=OK;
	Temperatue=Get_Temp();
	if (eepromread(PassAddr)!=0xff)
	{
		for (u8 i =0;i<4;i++)
		{
			password[i]=eepromread(PassAddr+i);
		}
	}
	
		
}

// PassState_t CheckPass()
// {
// 	u8 InPass[4];
// 	u8 k;
// 	LCD_Clear();
// 	
// 		k=KEYPAD_GetKey();
// 		if (k!=NO_KEY)
// 		{
// 			InPass[i]=k;
// 			if (InPass[i]!=password[i])
// 			{
// 				return BAD;
// 			}
// 			i++;
// 		}
// 		
// 	if (i==4)
// 	{
// 		i=0;
// 		return GOOD;
// 	}
// 	
// }

// void NewPass(void)
// {
// 	
// }
void checkCase(void)
{
	if ( (state==OK) && (Temperatue>500) )
	{
		LCD_Clear();
		state=HEAT;
	}
	else if ((state==HEAT) && (Temperatue<=450))
	{
		LCD_Clear();
		state=OK;
	}
	else if ((state==HEAT) && (SmokeLevel>50))
	{
		LCD_Clear();
		state=FIRE;
	}
	else if ((KEYPAD_GetKey()=='1') && (state==OK))
	{
		LCD_Clear();
		state=PASS_CHANGE1;
	}
	else
	{
		
	}
}

void CasesCode_LCD(void)
{
	switch(state)
	{
		case OK:
		
		LCD_GoTo(0,6);
		LCD_WriteString("Fine");
		LCD_GoTo(1,0);
		LCD_WriteString("1) to change pass");
		
		break;
		case HEAT:
		
		LCD_GoTo(0,6);
		LCD_WriteString("Heat");
		
		break;
		case FIRE:
		
		LCD_GoTo(0,6);
		LCD_WriteString("!!Fire!!");
		LCD_GoTo(1,0);
		LCD_WriteString("enter password");
		
		
		break;
		case PASS_CHANGE1:
		
		LCD_GoTo(0,0);
		LCD_WriteString("enter old pass");
		break;
		case PASS_CHANGE2:
		
		LCD_GoTo(0,0);
		LCD_WriteString("enter new pass");
		break;
	}
}

void CasesCode_HW(void)
{
	switch(state)
	{
		case OK:
		
		DIO_WritePin(GREEN_LED,HIGH);
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(BLUE_LED,LOW);
		DIO_WritePin(SMOKE_EN,LOW);
		DIO_WritePin(FAN,LOW);
		DIO_WritePin(WATER_MOTOR,LOW);
		DIO_WritePin(FAN,LOW);
		DIO_WritePin(BUZZER,LOW);
		
		Temperatue=Get_Temp();
		SmokeLevel=Get_Smoke();
		break;
		case HEAT:
		
		DIO_WritePin(GREEN_LED,LOW);
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(BLUE_LED,HIGH);
		DIO_WritePin(SMOKE_EN,HIGH);
		DIO_WritePin(WATER_MOTOR,LOW);
		DIO_WritePin(FAN,HIGH);
		DIO_WritePin(BUZZER,LOW);
		
		
		
		Temperatue=Get_Temp();
		SmokeLevel=Get_Smoke();
		break;
		case FIRE:
		
		DIO_WritePin(GREEN_LED,LOW);
		DIO_WritePin(RED_LED,HIGH);
		DIO_WritePin(BLUE_LED,LOW);
		DIO_WritePin(BUZZER,HIGH);
		DIO_WritePin(FAN,HIGH);
		DIO_WritePin(WATER_MOTOR,HIGH);
		
		Temperatue=Get_Temp();
		SmokeLevel=Get_Smoke();
		
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			if (k!=password[i])
			{
				LCD_GoTo(1,0);
				LCD_WriteString("wrong");
				LCD_WriteString("       ");
				
				i=0;
				
			}
			i++;
			if (i==4)
			{
				i=0;
				LCD_Clear();
				state=OK;
			}
				
		}
		
		break;
		case PASS_CHANGE1:
		k=KEYPAD_GetKey();
			if (k!=NO_KEY)
			{
				;
				if (k!=password[i])
				{
					i=0;
					LCD_Clear();
					state=OK;
				}
				i++;
				if (i==4)
				{
					LCD_Clear();
					state=PASS_CHANGE2;
					i=0;
				}
			}
			
		break;
		
		case PASS_CHANGE2:
		k=KEYPAD_GetKey();
			if (k!=NO_KEY)
			{
				password[i]=k;
				i++;
				if (i==4)
				{
					LCD_Clear();
					i=0;
					{
						for (u8 i=0;i<4;i++)
						{
							eepromwrite(PassAddr+i,password[i]);
						}
					}
					state=OK;
				}
			}
		break;
		
		
	}
}

void Fire_Runnable(void)
{
	
	checkCase();
	CasesCode_LCD();
	CasesCode_HW();
	
	
}


