#ifndef EMU_HPP
#define EMU_HPP
// in this file we are gonna include the functions for the emulator context which it 
// will be overrunnig the other components, so it works even if the others don't

#include "types.hpp"

// underneath code must be implemented
struct emu
{
    bool pause;
    bool running;
    B64 ticks;
};

void emu_cycles(int cpu_cycles);


// Ma quanto sei british 

#endif