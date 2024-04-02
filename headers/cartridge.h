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
        unsigned int GetRamSize();
        std::string GetOldLicenseeCode();
        bool ComputeChecksum();
        
        Byte ReadCart(Word);
        Byte* ReadFromToCart(Word, Word);
    private:
        Byte* data;
        
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};