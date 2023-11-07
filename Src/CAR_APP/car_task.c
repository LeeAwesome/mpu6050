#include "car_task.h"
#include "mpu6050.h"
#include "stdio.h"
#include "inv_mpu.h"
#include "control.h"
#include "echo.h"
#include "my_usart.h"
#include "usart.h"
#define RXBUFFER_LEN 20


// global data
struct mpu6050_data outMpu;

int Balance_PWM, Velocity_PWM, Turn_PWM = 0;
int Encoder_left, Encoder_right;
int Motor1, Motor2;
int Contrl_Turn = 64;//

int rxloss_flag = 1,avoidance_flag = 0;
int rx_cnt = 0;//Ê§¿Ø±ê¼Ç

float Movement = 0; // target speed
float target_yaw = 0; // target turn yaw

// environment data collection task
void Car_Task_200HZ(void)
{
	mpu_dmp_get_data(&outMpu.pitch,&outMpu.roll,&outMpu.yaw); // yaw dift compensation wrote in this function
}


void Car_Task_100HZ(void)
{

	// 1. balance PWM
	Balance_PWM = Vertical_Ring_PD(outMpu.pitch, outMpu.gyro_y);
	
	// 2. Velocity PWM
	Encoder_left = Read_Encoder(1);
	Encoder_right = Read_Encoder(2);
	
	Velocity_PWM = Vertical_speed_PI(Encoder_left, Encoder_right, outMpu.pitch, Movement);

	// 3. turn PWM
  Turn_PWM = - Vertical_turn_PD(target_yaw, outMpu.yaw, outMpu.gyro_z);
	
	// 4. final PWM of Left & Right Motor
	Motor1 = Balance_PWM + Velocity_PWM + Turn_PWM;
	Motor2 = Balance_PWM + Velocity_PWM - Turn_PWM;


	Motor2*=1.08;
	PWM_Limiting(&Motor1, &Motor2);

	if(Turn_off(outMpu.pitch)!=1) Set_PWM(Motor1,Motor2);
}



void Car_Task_5HZ(void)
{
	Getdistance();
}





void Car_Task_Interaction(void)
{
		printf("mpu:%f,%f,%f\n", outMpu.pitch, outMpu.roll, outMpu.yaw);
		printf("encoder:%d,%d\n", Encoder_left, Encoder_right);
		printf("balance_pwm:%d\n", Balance_PWM);
		printf("dis:%f\n", dis);
		
}






