#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

// PINS
#define LED1_bt 17
#define LED4_bt 20
#define SW0_bt 13
#define SW1_bt 14


void LED_init(){ 
	// Configure LED Matrix
	for(int i = LED1_bt; i <= LED4_bt; i++){
        // Pullup and output
        GPIO->PIN_CNF[i] |= (1 << 0) | (3 << 2);
        GPIO->OUT |= (1 << i);
	}
}

void button_init(){ 
	// Setting both Buttons for pull up on pin and as outputs
	GPIO->PIN_CNF[SW0_bt] = (3 << 2);
	GPIO->PIN_CNF[SW1_bt] = (3 << 2);
}

int main(){
    // INITIALISATION
    LED_init();
    button_init();
    GPIOTE_init();
    ppi_init();

    while(1);
    
    return 0;
}