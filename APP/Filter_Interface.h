/*
 * Filter_Interface.h
 *
 * Created: 6/26/2023 6:23:26 PM
 *  Author: Bero
 */ 


#ifndef FILTER_INTERFACE_H_
#define FILTER_INTERFACE_H_

s16 FILTER_GetUnFilterdTemp(void);
s16 FILTER_GetFilterdTemp(void);
void FILTER_Runnable(void);
void FILTER_Init(void);


#endif /* FILTER_INTERFACE_H_ */