#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/* vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	/* prescaller*/
	
	ADCSRA&=0XF8;
	scaler&=0X07;
	ADCSRA=ADCSRA|scaler;
	/* enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_Channel_type CH)
{
	
	
	/* set channel mux*/
	ADMUX=ADMUX&0xe0;
	//CH=CH&0x1f;
	ADMUX=ADMUX|CH;
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/* w8 ADC finish**/
	while(READ_BIT(ADCSRA,ADSC));
	/*get read*/
	
	
	return ADC;
	
	
}
u16 ADC_GetVolt(ADC_Channel_type CH)
{
	u16 x,volt;
	
	x=ADC_Read(CH);
	
	volt=((x)*(u32)5000)/1023;
	return volt;
}

