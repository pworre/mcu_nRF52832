#include "ppi.h"
#include "gpiote.h"

void ppi_init(){
    for (int channel = 0; channel < 4; channel++){
        PPI->PPI_CH[channel].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
        PPI->PPI_CH[channel].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[1 + channel]);
        PPI->CHENSET |= (1 << channel);
    }
    
    //PPI->PPI_TASKS[0].EN = 1;

}
