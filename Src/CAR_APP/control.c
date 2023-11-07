#include "math.h"
#include "stdlib.h"
#include "stm32f1xx_hal.h"
#include "control.h"


int   Dead_Zone=4350; //left 4450 right 4350  


//PID parameter9
struct pid_arg PID = {
	.Balance_Kp=-400 ,//-230 245
	.Balance_Kd=0, // -0.55
	
	.Velocity_Kp=0,//115 -48 70 100
	.Velocity_Ki=0,//-0.24 -0.24 0.21 0.325
	
	.Turn_Kp = 0, // 25
	.Turn_Kd = 0, //0.5
};

int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;  
		
   switch(TIMX)
	 {
		case 1:  Encoder_TIM = (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;	//1 left encoder
		case 2:  Encoder_TIM = (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	//2 right encoder
		default: Encoder_TIM = 0;
	 }
		return Encoder_TIM;
}

int	Vertical_Ring_PD(float Angle,float Gyro)
{
	float Bias;
	int balance;
	Bias=Angle-Mechanical_balance;
	balance=PID.Balance_Kp*Bias + Gyro*PID.Balance_Kd;
	
	return balance;
}

int Vertical_speed_PI(int encoder_left,int encoder_right,float Angle,float Movement )
{
	static float Velocity, Encoder_Least, Encoder;
	static float Encoder_Integral;

	Encoder_Least = (encoder_left + encoder_right) - 0;    
	Encoder *= 0.8f;																	
	Encoder += Encoder_Least*0.2f;    

	Encoder_Integral += Encoder;                       
	Encoder_Integral = Encoder_Integral - Movement; 

	if(Encoder_Integral>10000)    Encoder_Integral=10000;          
	if(Encoder_Integral<-10000)	  Encoder_Integral=-10000;            

	Velocity = Encoder*PID.Velocity_Kp + Encoder_Integral*PID.Velocity_Ki;      
	
	if(Turn_off(Angle)==1)   Encoder_Integral=0;            
	return Velocity;
}

int Vertical_turn_PD(float taget_yaw, float yaw, float gyro)
{
    float Turn;
    float Bias_yaw;
    Bias_yaw = taget_yaw - yaw;
	if (Bias_yaw < -180) Bias_yaw += 360;
	if (Bias_yaw >  180) Bias_yaw -= 360;
	
    Turn = -Bias_yaw*PID.Turn_Kp - gyro*PID.Turn_Kd;
    return Turn;
}

void PWM_Limiting(int *motor1,int *motor2)
{
	int Amplitude=7999;
	if(*motor1<-Amplitude) *motor1=-Amplitude;	
	if(*motor1>Amplitude)  *motor1=Amplitude;	
	if(*motor2<-Amplitude) *motor2=-Amplitude;	
	if(*motor2>Amplitude)  *motor2=Amplitude;		
}


u8 FS_state;

u8 Turn_off(const float Angle)
{
	u8 temp;
	if(fabs(Angle)>60){
		FS_state=1;
		temp=1;
		PWMA1=0;
		PWMA2=0;
		PWMB1=0;
		PWMB2=0;
	}
	else 
		temp=0;
		FS_state=0;
	return temp;
}

void Set_PWM(int motor1,int motor2)
{
    if(motor1>0)
    {
        PWMA2=Dead_Zone+(abs(motor1))*1.17;
        PWMA1=0;

    }
    else
    {
        PWMA2 =0;
        PWMA1=Dead_Zone+(abs(motor1))*1.17;
    }


    if(motor2>0)		{

        PWMB2 = Dead_Zone+(abs(motor2))*1.17;
        PWMB1 = 0;
    }
    else
    {   PWMB2 = 0;
        PWMB1=Dead_Zone+(abs(motor2))*1.17;
    }
}

void ApplyPIDParameters(struct pid_arg *params) {
    PID = *params;

}
