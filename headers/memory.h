#pragma once

#include "types.h"
#include "array"
#include <string>

using namespace nstdtypes;


class Memory{
    private:
        // Enum per la definizione del MBC corretto
        enum MBCs {NO_MBCS, MBC1, MBC2, MBC3, MBC5, MBC6, MBC7, MMM01, M161, HuC1, HuC3};
        // Divisa in due parti principali
        // [1] da 0x0000 a 0x3FFF e' ROM bank fissa | Contiene dati sempre necessari
        // [2] da 0x4000 a 0x7FFF e' ROM bank commutabile | Contiene dati che variano
        // 
        // Data la grandezza della ROM il tutto sara mappato nel corso del programma.
        std::array<Byte, 0x8000> cartridgeROM;

        std::array<Byte, 8 * 1024> VRAM;

        std::array<Byte, 32 * 1024> RAM;

        std::array<Byte, 8 * 1024> WRAM;

        std::array<Byte, 512> ECHO_RAM;

        std::array<Byte, 160> OAM; 

        std::array<Byte, 128> IO;

        std::array<Byte, 127> HIGH_RAM;


        // MBC o Memory Bank Controller si occupa di scambiare la memoria al 0x4000 --> 0x7FFF
        // Ce ne sono diversi tipi, per questo utilizzeremo un enum per la sua definizione
        MBCs MBC;

        
    public:
        Memory(Byte*, std::string);
        
};