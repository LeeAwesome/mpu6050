#include "my_usart.h"
#include "stdlib.h"
#include "control.h"
#include "string.h"
#include "stdio.h"

User_USART BT_Data;

void User_USART_Init(User_USART *Data)
{
    for (uint8_t i = 0; i < RXBUFFER_LEN; i++) Data->RxBuffer[i] = 0;
    Data->frame_head = 0xA5;
    Data->frame_tail = 0x5A;
    Data->Rx_flag = 0;
    Data->Rx_len = 0;
    
    // 初始化 PID 参数
    Data->Balance_Kp = 0.0;
    Data->Balance_Kd = 0.0;
    Data->Velocity_Kp = 0.0;
    Data->Velocity_Ki = 0.0;
    Data->Turn_Kp = 0.0;
    Data->Turn_Kd = 0.0;
		printf("User_USART_Init Complete \n");
	
}


void reverseBytes(unsigned char *start, int size) {
    unsigned char temp;
    for (int i = 0; i < size / 2; i++) {
        temp = start[i];
        start[i] = start[size - 1 - i];
        start[size - 1 - i] = temp;
    }
}

void BTData_Process(uint8_t *RxBuffer) {
    printf("data in, BTData_Process works \n");

    printf("Frame Head: Expected = %x, Received = %x\n", BT_Data.frame_head, RxBuffer[0]);
    printf("Frame Tail: Expected = %x, Received = %x\n", BT_Data.frame_tail, RxBuffer[RXBUFFER_LEN - 1]);
    printf("RxBuffer HEX: \n");
    for (int i = 0; i < RXBUFFER_LEN; i++) {
        printf("%02X ", RxBuffer[i]);
			
    }
		printf("\n");
		
		for (int i = 1; i < RXBUFFER_LEN - 1; i += 4) {
		reverseBytes(&RxBuffer[i], 4);
    }
		for (int i = 0; i < RXBUFFER_LEN; i++) {
    }
		
		for (int i = 0; i < RXBUFFER_LEN; i++) {
		printf("%02X ", RxBuffer[i]);
			
    }
    if (RxBuffer[0] != BT_Data.frame_head) return;
		if (RxBuffer[RXBUFFER_LEN - 1] != BT_Data.frame_tail) return;
		
		for (int i = 1; i < RXBUFFER_LEN - 1; i += 4) {
		reverseBytes(&RxBuffer[i], 4);
    }
		for (int i = 0; i < RXBUFFER_LEN; i++) {
    }
		
    // 从 RxBuffer 解析并更新 PID 参数
    memcpy(&BT_Data.Balance_Kp, &RxBuffer[1], sizeof(float)); 
    memcpy(&BT_Data.Balance_Kd, &RxBuffer[5], sizeof(float));
    memcpy(&BT_Data.Velocity_Kp, &RxBuffer[9], sizeof(float));
    memcpy(&BT_Data.Velocity_Ki, &RxBuffer[13], sizeof(float));
    memcpy(&BT_Data.Turn_Kp, &RxBuffer[17], sizeof(float));
    memcpy(&BT_Data.Turn_Kd, &RxBuffer[21], sizeof(float));

    printf("BTData_Process data analysis: \n %f, %f, %f, %f, %f, %f \n", BT_Data.Balance_Kp, BT_Data.Balance_Kd, BT_Data.Velocity_Kp, BT_Data.Velocity_Ki, BT_Data.Turn_Kp, BT_Data.Turn_Kd);
    UpdatePIDParamsToControl();
}



void UpdatePIDParamsToControl() 
{
    struct pid_arg new_params;
		printf("UpdatePIDParamsToControl Work \n");
    new_params.Balance_Kp = BT_Data.Balance_Kp;
    new_params.Balance_Kd = BT_Data.Balance_Kd;
    new_params.Velocity_Kp = BT_Data.Velocity_Kp;
    new_params.Velocity_Ki = BT_Data.Velocity_Ki;
    new_params.Turn_Kp = BT_Data.Turn_Kp;
    new_params.Turn_Kd = BT_Data.Turn_Kd;

    ApplyPIDParameters(&new_params);
}
