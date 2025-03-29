#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define SW0_bt 13
#define SW1_bt 14
#define LED1_bt 17
#define LED4_bt 20



void button_init(){ 
	// Setting both Buttons for pull up on pin and as outputs
	GPIO->PIN_CNF[SW0_bt] = (3 << 2);
	GPIO->PIN_CNF[SW1_bt] = (3 << 2);
}



int main(){
    // Configure LED Matrix
	for(int i = LED1_bt; i <= LED4_bt; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    button_init();
    uart_init();
    //int lightON = 0;
    for(int i = LED1_bt; i <= LED4_bt; i++){
		GPIO->OUT |= (1 << i);
	}
    //int sleep = 0;
    while(1){
        int buttonOnePressed = !(GPIO->IN & (1 << SW0_bt));
		int buttonTwoPressed = !(GPIO->IN & (1 << SW1_bt));
		if (buttonOnePressed) {
            //GPIO->OUT ^= (1 << LED1_bt);
            uart_send('A');
		}else if (buttonTwoPressed) {
            uart_send('B');
		}
        if (uart_read() != '\0'){
            for(int i = LED1_bt; i <= LED4_bt; i++){
                GPIO->OUT ^= (1 << i);
	        }
        }
    }

    return 0;
}