// 
// 
// #include "StdTypes.h"
// 
// 
// 
// Error_t LED_GetTemp(u8 ledIdx,s16*PTemp);
// 
// /* 85 led max*/
// s16 max_temp=-42;
// #define LOWEST_TEMP (-42)
// s16 currentTemp;
// s16 lastTemp;
// 
// void ATHM_Init(void)
// {
// 	LED_GetTemp(40,lastTemp);
// 	currentTemp=lastTemp;
// }
// 
// void ATHM_Runnable(void)
// {
// 	max_temp=LOWEST_TEMP;
// 	s16 temp_temp;
// 	
// 	for (u8 i =0;i<85;i++)
// 	{
// 		LED_GetTemp(i,&temp_temp)
// 		if (temp_temp>max_temp)
// 		{
// 			max_temp=temp_temp;
// 		}
// 	}
// 	lastTemp=currentTemp;
// 	currentTemp=max_temp;
// 	 
// }
// 
// u16 ATHM_GetDeratingRation(void)
// {
// 	u16 deratingRat;
// 	
// 	if (currentTemp>105)
// 	{
// 		if (currentTemp>lastTemp)
// 		{
// 			deratingRat= (((max_temp)*(u32)1000)/15)-7000;
// 		}
// 		else
// 		{
// 			deratingRat=(((max_temp)*(u32)1000/15)-6672);
// 		}
// 	}
// 	else
// 	{
// 		deratingRat= 1000;
// 	}
// 	
// 	return deratingRat;
// }
