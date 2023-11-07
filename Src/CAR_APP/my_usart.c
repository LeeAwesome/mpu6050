#include "my_usart.h"
#include "stdlib.h"
#include "usart.h"

User_USART BT_Data;	

// initialize pack for data recesiving Rx
void User_USART_Init(User_USART *Data)
{
    for(uint8_t i=0; i < RXBUFFER_LEN; i++)	Data->RxBuffer[i] = 0;
    Data->frame_head = 0xA5;
    Data->frame_tail = 0x5A;
    Data->Rx_flag = 0;
    Data->Rx_len = 0;
    Data->x = 0;
    Data->y = 0;
    Data->mode = 0;
    Data->rxflag = 0;
}

void BTData_Process(uint8_t *RxBuffer)
{
    //depart received data for use
    if(RxBuffer[0] != BT_Data.frame_head) return;
    if(RxBuffer[6] != BT_Data.frame_tail) return;

    BT_Data.x = RxBuffer[1];
    BT_Data.y = RxBuffer[2];
    BT_Data.mode = RxBuffer[3];
    BT_Data.rxflag = RxBuffer[4];


}




