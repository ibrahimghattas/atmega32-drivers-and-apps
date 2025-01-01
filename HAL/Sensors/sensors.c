
#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"


u16 Get_Temp(void)
{
	u16 volt=ADC_GetVolt(LM35_CH);
	u16 temp;
	
	temp=volt;
	
	return temp;
}

u8 Get_Smoke(void)
{
	u16 adc=ADC_Read(SMOKE_CH);
	u8 r=(adc*(u32)100)/1023;
	
	
	return r;
}