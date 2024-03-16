#pragma once

#include "types.h"
#include "LR35902.h"
#include <array>


using namespace nstdtypes;

class Bus {
    public:
        Bus();
        ~Bus();

        LR35902 cpu;

        std::array<Byte, 64 * 1024> ram  ;  // memoria fittizia 

        //Bus read & Write
        
        void Write(Word, Byte);
        Byte Read (Word, bool);
};