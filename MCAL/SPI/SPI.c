#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"

static void(*SPI_Fptr)(void)=NULL_PTR;


void SPI_Init(void )
{
	// SLAVE OR MASTER
	#if SPI_MODE==MASTER
	SET_BIT(SPCR,MSTR);
	//clock 2mhz
	#else
	CLR_BIT(SPCR,MSTR);
	#endif
	
	
	//enable
	
	SET_BIT(SPCR,SPE);
}
void SPI_IntEN(void)
{
	SET_BIT(SPCR,SPIE);
	
}
u8 SPI_SendReceive(u8 data)
{
	// write buffer
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	//READ PUFFER
	return SPDR;
	
}


u8 SPI_ReceivePeriodic(u8 * p_data)
{
	if (READ_BIT(SPSR,SPIF))
	{
		*p_data=SPDR;
		return 1;
	}
	return 0;
	
}
void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}
void SPI_SetCallBack(void(*fptr)(void))
{
	SPI_Fptr=fptr;
}


ISR(SPI_STC_vect)
{
	if ((void (*)(void *))SPI_Fptr!=(void (*)(void *))NULLPTR)
	{
		SPI_Fptr();
	}
	
}