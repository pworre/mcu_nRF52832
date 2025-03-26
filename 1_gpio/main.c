#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define SW0_bt 13
#define SW1_bt 14
#define LED1_bt 17
#define LED4_bt 20


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

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

	// Configure buttons -> see button_init()
	button_init();
	//int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		int buttonOnePressed = !(GPIO->IN & (1 << SW0_bt));
		int buttonTwoPressed = !(GPIO->IN & (1 << SW1_bt));
		if (buttonOnePressed) {
			for(int i = LED1_bt; i <= LED4_bt; i++){
				GPIO->OUT &= ~(1 << i);
			}
		}
		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (buttonTwoPressed) {
			for(int i = LED1_bt; i <= LED4_bt; i++){
				GPIO->OUT |= (1 << i);
			}
		}

		//sleep = 10000;
		//while(--sleep); // Delay
	}
	return 0;
}
