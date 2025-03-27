#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define SW0_bt 13
#define SW1_bt 14


void button_init(){ 
	// Setting both Buttons for pull up on pin and as outputs
	GPIO->PIN_CNF[SW0_bt] = (3 << 2);
	GPIO->PIN_CNF[SW1_bt] = (3 << 2);
}

int main(){
    while(1){
        int buttonOnePressed = !(GPIO->IN & (1 << SW0_bt));
		int buttonTwoPressed = !(GPIO->IN & (1 << SW1_bt));
		if (buttonOnePressed) {
            uart_send("A");
		}else if (buttonTwoPressed) {
            uart_send("B");
		}
    }

    return 0;
}