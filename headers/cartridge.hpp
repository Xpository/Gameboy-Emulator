#include "types.hpp"
#include <fstream>
#include <string>
#include <map>
#include <iostream>

 

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
        
        bool ValidateCartridge();

        Byte ReadCart(Word);
        Byte* ReadFromToCart(Word, Word);
        Byte* GetData();
    private:
        Byte* data;
        
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};