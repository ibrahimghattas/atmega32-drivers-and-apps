/*
 * Fire_Interface.h
 *
 * Created: 6/27/2023 12:49:05 AM
 *  Author: Bero
 */ 




#ifndef FIRE_INTERFACE_H_
#define FIRE_INTERFACE_H_


typedef enum{
	OK,
	HEAT,
	FIRE,
	PASS_CHANGE1,
	PASS_CHANGE2
}FireStates_t;

typedef enum {
	GOOD,
	BAD
	}PassState_t;

#define SMOKE_EN PINC6
#define RED_LED PINC0
#define  BLUE_LED PINC1
#define GREEN_LED PINC2
#define BUZZER PINC5

#define WATER_MOTOR PINC3
#define FAN	PINC4

void Fire_Init(void);

void Fire_Runnable(void);

#endif /* FIRE_INTERFACE_H_ */