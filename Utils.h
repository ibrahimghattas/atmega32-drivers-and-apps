/*
 * Utils.h
 *
 * Created: 6/10/2023 10:19:14 PM
 *  Author: Bero
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define  READ_BIT(reg,bit)		((reg>>bit)&1)
#define SET_BIT(reg,bit)	(reg=reg|(1<<bit))
#define CLR_BIT(reg,bit)	(reg=reg&~(1<<bit))
#define TOGGLE_BIT(reg,bit)  (reg=reg^(1<<bit))

#define F_CPU 8000000
#include <util/delay.h>



#endif /* UTILS_H_ */