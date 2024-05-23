#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "types.hpp"
#include "array"
#include <string>




class Memory{
    private:
        Byte LCDC; // LCD Control
        Byte STAT; // LCDC Status
        Byte SCY;  // Scroll Y
        Byte SCX;  // Scroll X
        Byte LY;   // LCDC Y-Coordinate
        Byte LYC;  // LY Compare
        Byte DMA;  // DMA Transfer
        Byte BGP;  // BG Palette Data
        Byte OBP0; // Object Palette 0 Data
        Byte OBP1; // Object Palette 1 Data
        Byte WY;   // Window Y Position
        Byte WX;   // Window X Position

        bool ramEnabled;

        int romBank;
        int ramBank;
        // false = ROM banking mode, true = RAM banking mode
        bool bankingMode; 
        
    public:
        Byte* cartridgeROM;

        std::array<Byte, 32 * 1024> RAM;
        
        std::array<Byte, 8 * 1024> VRAM;

        std::array<Byte, 8 * 1024> WRAM;

        std::array<Byte, 160> OAM; 

        std::array<Byte, 128> IO;

        std::array<Byte, 127> HIGH_RAM;

        Memory(Byte*, unsigned int);
        ~Memory();
        
        Byte Read(Word);
        void Write(Word, Byte);

        void OAMDMA();
        void UpdateSTAT(int);

        Byte* RequestPointerTo(std::string);
        Byte RequestValueOfRegister(std::string);

        
        
};



#endif