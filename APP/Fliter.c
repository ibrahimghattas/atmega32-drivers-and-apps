#include "StdTypes.h"
#include "Filter_Interface.h"
#include "Sensors_Interface.h"
s16 fILTER_TEMP;
s16 temptemp;
s16 arr[10];


void FILTER_Init(void)
{
	fILTER_TEMP=Get_Temp();
	for (u8 i=0;i<10;i++)
	{
		arr[i]=fILTER_TEMP;
	}
}

/* not more than 250 us*/
void FILTER_Runnable(void)
{
	static u8 i=0;
	s32 sum=0;
	temptemp=Get_Temp();
	arr[i]=temptemp;
	i++;
	if (i==10)
	{
		i=0;
	}
	for (u8 j=0;j<10;j++)
	{
		sum+=arr[j];
	}
	fILTER_TEMP=sum/10;
}

s16 FILTER_GetFilterdTemp(void)
{
	return fILTER_TEMP;
}

s16 FILTER_GetUnFilterdTemp(void)
{
	return temptemp;
}
