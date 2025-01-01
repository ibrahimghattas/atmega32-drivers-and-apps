#include "StdTypes.h"
#include "Timer.h"
#include "Servo.h"

void Servo_SetAngle(u8 angle)
{
	if (angle > 180)
	{
		angle=180;
	}
	OCR1B=((angle*(u32)1000)/(u32)180)+999;
}
