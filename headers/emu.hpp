// in this file we are gonna include the functions for the emulator context which it 
// will be overrunnig the other components, so it works even if the others don't
#pragma once

#include "types.hpp"

//underneath code must be implemented

struct thisEmuContext
{
    bool pause;
    bool running;
    B64 ticks;
};

void emu_cycles(int cpu_cycles);


