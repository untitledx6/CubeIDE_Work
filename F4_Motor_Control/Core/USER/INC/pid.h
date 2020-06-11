
extern float kp,ki,kd;

extern float kp1,ki1,kd1;

extern float Iterm;
extern float error[20];

extern float Iterm1;
extern float error1[20];

float PID_Calc(float Input,float setpoint);
void Set_PID_Parameter(float KP,float KI,float KD);

float PID_Calc1(float Input,float setpoint);
void Set_PID_Parameter1(float KP,float KI,float KD);
