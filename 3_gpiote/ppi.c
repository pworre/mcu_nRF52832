#include "ppi.h"
#include "gpiote.h"

void ppi_init(){
    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[4]);
    PPI->PPI_TASKS[0].EN = 1;
    PPI->CHEN = (1 << 0);
}
