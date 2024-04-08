#pragma once

#include "types.h"
#include "array"
#include <string>

using namespace nstdtypes;


class Memory{
    private:
        // Divisa in due parti principali
        // [1] da 0x0000 a 0x3FFF e' ROM bank fissa | Contiene dati sempre necessari
        // [2] da 0x4000 a 0x7FFF e' ROM bank commutabile | Contiene dati che variano
        // 
        // Data la grandezza della ROM il tutto sara mappato nel corso del programma.
        std::array<Byte, 8 * 1024 * 1024> cartridgeROM;

        std::array<Byte, 32 * 1024> RAM;
        
        std::array<Byte, 8 * 1024> VRAM;

        std::array<Byte, 8 * 1024> WRAM;

        std::array<Byte, 160> OAM; 

        std::array<Byte, 128> IO;

        std::array<Byte, 127> HIGH_RAM;


        bool ramEnabled;

        int romBank;
        int ramBank;
        // false = ROM banking mode, true = RAM banking mode
        bool bankingMode; 
        
    public:
        Memory(Byte*);

        Byte Read(Word);
        void Write(Word, Byte);
        
};