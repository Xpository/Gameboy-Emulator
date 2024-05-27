#include "../headers/emu.hpp"

emu thisEmuContext = {0};

// Serve ancora implementazione
void emu_cycles(int cpu_cycles){
    for (int i=0; i<cpu_cycles; i++) {
        for (int n=0; n<4; n++) {
            thisEmuContext.ticks++;
            // da implementare
            // timer_tick(); 
            //da implementare
            // ppu_tick(); 
        }
        //da implementare
        // dma_tick();
    }

}