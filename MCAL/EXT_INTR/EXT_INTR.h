/*
 * EXT_INTR.h
 *
 * Created: 7/17/2023 5:27:08 PM
 *  Author: Bero
 */ 


#ifndef EXT_INTR_H_
#define EXT_INTR_H_


typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_type;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;


void EXI_Init(void);

#define   GLOBAL_ENABLE    sei

void EXI_Enable(ExInterruptSource_type Interrupt);
void EXI_Disable(ExInterruptSource_type Interrupt);
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge);
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void));




#endif /* EXT_INTR_H_ */