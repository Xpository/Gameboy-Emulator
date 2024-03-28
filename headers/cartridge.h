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
        bool CheckLogo();
        std::string GetTitle();
        bool CheckCGBFlag();
        std::string GetNewLicenseeCode();
        std::string GetCartridgeType();
        std::string GetOldLicenseeCode();
        bool ComputeChecksum();

        // Questo sarebbe la grandezza effettiva del file, ma l'ho aumentata di 10k 
        // 1048575
        
    private:
        Byte data[1058575];

        // Ok, ora da qua bisogna vedere in che modo sono i valori, dovrebbero essere di 8 bit in 8 bit, cio significa che avremo le locazione FORSE giuste.
        // Dipende da entreremo nella cartridge. 
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};