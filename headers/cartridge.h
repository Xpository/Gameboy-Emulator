#pragma once

#include "types.h"
#include <fstream>
#include <string>
#include <map>
#include <iostream>

 
using namespace nstdtypes;

class Cartridge{
    public:
        Cartridge(std::string);
        ~Cartridge();
        bool CheckLogo();
        std::string GetTitle();
        bool CheckCGBFlag();
        std::string GetNewLicenseeCode();
        std::string GetCartridgeType();
        unsigned int GetRomSize(Byte*);
        unsigned int GetRomSize();
        std::string GetOldLicenseeCode();
        bool ComputeChecksum();
        
    private:

        // 0xAF838
        // 1048576
        Byte* data;
        
        // Ok, ora da qua bisogna vedere in che modo sono i valori, dovrebbero essere di 8 bit in 8 bit, cio significa che avremo le locazione FORSE giuste.
        // Dipende da entreremo nella cartridge. 
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};