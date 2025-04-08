#include "gpiote.h"

#define LED1_bt 17
#define LED4_bt 20
#define SW0_bt 13
#define GPIO_EVENT_SW1 0
#define GPIO_EVENT_LED

void GPIOTE_init(){
    GPIOTE->CONFIG[GPIO_EVENT_SW1] = (1 << 0) | (SW0_bt << 8) | (3 << 16);    // SW1 som EVENT       OBS!!! SJekk om må endre initial value i registeret!
    int task_number = 1;
    for (int i = LED1_bt; i <= LED4_bt; i++){
        GPIOTE->CONFIG[task_number] = (3 << 0) | (i << 8) | (3 << 16); // LED as EVENT and Toggle polarity
        task_number++;
    }
}