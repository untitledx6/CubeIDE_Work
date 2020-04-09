
extern float kp,ki,kd;

extern float Iterm;
extern float error[20];

float PID_Calc(float Input,float setpoint);
void Set_PID_Parameter(float KP,float KI,float KD);
