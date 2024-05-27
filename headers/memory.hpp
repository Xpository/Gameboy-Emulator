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

        /* @brief Costruttore, inizializza la classe
         * 
         * Il costruttore inizializza i registri necessari alla renderizzazione grafica
         * e le variabili della classe, infine alloca nella memoria heap lo spazio per la ROM
         *
         * @param puntatore alla ROM
         * @param dimensione della ROM
        */
        Memory(Byte*, unsigned int);

        /* @brief Distruttore che dealloca dalla memoria heap lo spazio della ROM
        */
        ~Memory();
        
        /* @brief Legge un dato dalla memoria
         * 
         * l'indirizzo viene associato, in base al suo valore, alla memoria corrispondente,
         * tra ROM, RAM, VRAM, WRAM, OAM e i registri input/output, e ritorna il dato richiesto
         *
         * @param indirizzo della memoria in cui leggere i dati
         * @return ritorna il Byte all'indirizzo dato
        */
        Byte Read(Word);

        /* @brief Scrive un dato in memoria
         * 
         * l'indirizzo viene associato, in base al suo valore, alla memoria corrispondente,
         * tra ROM, RAM, VRAM, WRAM, OAM e i registri input/output, quindi viene scritto il dato
         *
         * @param indirizzo della memoria in cui scrivere il dato
         * @param Byte contenente il dato da inserire
        */
        void Write(Word, Byte);

        /* @brief copia 160 byte dalla RAM alla OAM
         * 
         * esegue un trasferimento diretto di memoria (Direct Memory Access, DMA) per la OAM
        */
        void OAMDMA();

        /* @brief aggiorna lo stato della memoria
         * 
         * aggiorna la modalità di rendering della memoria nella variabile STAT
         * in base al valore del registro LY e al clock della modalità,
         * infine aggiorna il flag che indica l'uguaglianza tra i registri LY e LYC
         *
         * @param clock della modalità di rendering
         *
        */
        void UpdateSTAT(int);

        /* @brief richiedi un puntatore di un registro di rendering
         * 
         * determina il registro corrispondente e ne ritorna il puntatore
         *
         * @param stringa contenente il nome del registro di rendering
         * @return puntatore al registro di rendering richiesto
        */
        Byte* RequestPointerTo(std::string);

        /* @brief richiedi il valore di un registro di rendering
         * 
         * determina il registro corrispondente e ne ritorna il valore
         *
         * @param stringa contenente il nome del registro di rendering
         * @return Byte con il valore del registro
        */
        Byte RequestValueOfRegister(std::string);

        
        
};



#endif