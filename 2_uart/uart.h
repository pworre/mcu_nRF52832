#pragma once
#include <stdint.h>


void uart_init();
void uart_send(char letter);
char uart_read();
