#include <iostream>
#include "RingBuffer.h"

using namespace std;
uint16_t buff[5];
RingBuffer_t rb;

int main()
{
    printf("\r\n\r\n");
    printf("Hello, World!\n");

    RB_Init(&rb, buff, sizeof(buff));
    printf("Capacity: %d\n", RB_Capacity(&rb));
    printf("Size: %d\n", RB_Size(&rb));
    printf("Is Empty: %d\n", RB_IsEmpty(&rb));
    printf("Is Full: %d\n", RB_IsFull(&rb));

    uint16_t val = 1234;
    //RB_Put(&rb,val, sizeof(val));
    RB_Put(&rb, &val, sizeof(val));
    printf("Capacity: %d\n", RB_Capacity(&rb));
    printf("Size: %d\n", RB_Size(&rb));
    printf("Is Empty: %d\n", RB_IsEmpty(&rb));
    printf("Is Full: %d\n", RB_IsFull(&rb));


}