#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;   
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[63];
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED1; 
    volatile uint32_t EVENTS_TXDRDY;    
    volatile uint32_t RESERVED2[249];
    volatile uint32_t ENABLE;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RXD;
    volatile uint32_t RESERVED3[4];
    volatile uint32_t TXD;    

} NRF_UART_REG;

#define RTS_bt 5
#define TXD_bt 6
#define CTS_bt 7
#define RXD_bt 8

void uart_init(){
    GPIO->PIN_CNF[RXD_bt] &= ~(1 << 0);
    GPIO->PIN_CNF[TXD_bt] |= (1 << 0);
    UART->ENABLE |= (4 << 0);
    UART->PSELRTS |= (1 << 31);
    UART->PSELCTS |= (1 << 31);
    UART->BAUDRATE = 0x00275000;

    // Setting pin number for TXD and connecting
    UART->PSELTXD &= ~(1 << 31);
    UART->PSELTXD |= (TXD_bt << 0);
    UART->PSELRXD &= ~(1 << 31);
    UART->PSELRXD |= (RXD_bt << 0);

    // Starting task for receiving messages
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    //UART->EVENTS_TXDRDY = 0;
    UART->TXD = letter;

    while(!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
    

    UART->TASKS_STOPTX = 1;
}

char uart_read(){
    char letter;
    if (UART->EVENTS_RXDRDY){
        letter = UART->RXD;
        UART->EVENTS_RXDRDY = 0;
    } else {
        letter = '\0';
    }
    return letter;
}