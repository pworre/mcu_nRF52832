#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)
/*
typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;   
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[62];
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED1; 
    volatile uint32_t EVENTS_TXDRDY;    
    volatile uint32_t RESERVED2[248];
    volatile uint32_t ENABLE;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RXD;
    volatile uint32_t RESERVED3[3];
    volatile uint32_t TXD;    
} NRF_UART_REG;
*/

typedef struct {
	//Tasks
	volatile uint32_t TASKS_STARTRX;
	volatile uint32_t TASKS_STOPRX;
	volatile uint32_t TASKS_STARTTX;
	volatile uint32_t TASKS_STOPTX;
	volatile uint32_t RESERVED0[3];
	volatile uint32_t TASKS_SUSPEND;
	volatile uint32_t RESERVED1[56];
 
	//Events
	volatile uint32_t EVENTS_CTS;
	volatile uint32_t EVENTS_NCTS;
	volatile uint32_t EVENTS_RXDRDY;
	volatile uint32_t RESERVED2[4];
	volatile uint32_t EVENTS_TXDRDY;
	volatile uint32_t RESERVED3;
	volatile uint32_t EVENTS_ERROR;
	volatile uint32_t RESERVED4[7];
	volatile uint32_t EVENTS_RXTO;
	volatile uint32_t RESERVED5[46];
 
	//Registers
	volatile uint32_t SHORTS;
	volatile uint32_t RESERVED6[64];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED7[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED8[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED9;
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED10;
	volatile uint32_t BAUDRATE;
	volatile uint32_t RESERVED11[17];
	volatile uint32_t CONFIG;
 
} NRF_UART_REG;

#define RTS_bt 5
#define TXD_bt 6
#define CTS_bt 7
#define RXD_bt 8

void uart_init(){
    //GPIO->PIN_CNF[RXD_bt] &= ~(1 << 0);
    //GPIO->PIN_CNF[TXD_bt] |= (1 << 0);
    GPIO->PIN_CNF[RXD_bt] = 0;  // Input med pull-up
    GPIO->PIN_CNF[TXD_bt] = 1;
    UART->ENABLE = 4;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    //UART->PSELRTS =~ 0;
    //UART->PSELCTS =~ 0;
    UART->BAUDRATE = 0x00275000;

    UART->PSELTXD = TXD_bt;
    UART->PSELRXD = RXD_bt;


    // Starting task for receiving messages
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter){
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STARTTX = 1;
    //UART->EVENTS_TXDRDY = 0;
    UART->TXD = letter;

    UART->EVENTS_TXDRDY = 0; 
    while(!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
    

    UART->TASKS_STOPTX = 1;
}

char uart_read(){
    UART->TASKS_STARTRX = 1;
    char letter;
    if (UART->EVENTS_RXDRDY){
        letter = UART->RXD;
        UART->EVENTS_RXDRDY = 0;
    } else {
        letter = '\0';
    }
    return letter;
}