#pragma once

#include "types.h"
#include <fstream>
#include <vector>

using namespace nstdtypes;

class Cartridge{
    public:
        Cartridge();
    private:
        std::vector<Byte> data;

        // Ok, ora da qua bisogna vedere in che modo sono i valori, dovrebbero essere di 8 bit in 8 bit, cio significa che avremo le locazione FORSE giuste.
        // Dipende da entreremo nella cartridge. 
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};