#include "pid.h"

#define OUTMAX   1000
#define OUTMIN   -1000
#define ITERM_MAX  200
#define ITERM_MIN -200

typedef unsigned short int   uint16_t;

/*************************************************************************/
/*                       Output = kp*error + Iterm - kd*dInput           */
/*                       Iterm += ki*error;  dInput = Input - lastInput  */
/*************************************************************************/
float kp,ki,kd;
float Iterm = 0;
float lastInput = 0;
float temp,dInput;
float error[20];


float PID_Calc(float Input,float setpoint)
{
	static uint16_t left = 0;
	static uint16_t right = 0;
	static uint16_t flag = 0;
	
	error[right] = setpoint - Input;
	dInput = Input - lastInput;
	Iterm += ki*error[right];
	if(Iterm > ITERM_MAX)  Iterm = ITERM_MAX;
	else if(Iterm < ITERM_MIN)  Iterm = ITERM_MIN;

	temp = kp*error[right] + Iterm - kd*dInput;
	if(temp > OUTMAX)  temp = OUTMAX;
	else if(temp < OUTMIN)  temp = OUTMIN;
	lastInput = Input;
	
	right++;
	if(right >= 20)
	{
		flag = 1;
		right = 0;
	}
	if(flag)
	{
		Iterm -= ki*error[left++];
		if(left >= 20)
			left = 0;
	}
	
	return temp;
}

void Set_PID_Parameter(float KP,float KI,float KD)
{
    kp = KP;
    ki = KI;
    kd = KD;
}
