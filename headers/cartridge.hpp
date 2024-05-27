#include "types.hpp"
#include <fstream>
#include <string>
#include <map>
#include <iostream>

 

class Cartridge{
    public:
        /* @brief Costruttore che carica temporaneamente in memoria la cartridge
         * 
         * Il costruttore prima apre il file passatogli come argomento e ne controlla la grandezza.
         * Instanzia poi un buffer temporaneo per andare poi a leggere la dimensione effettiva della ROM
         * Con questo dato verra inizializzato "data" che conterrà la ROM, infine elimina il buffer
         * 
         * @param filepath Stringa contenente il percorso relativo alla rom da aprire
        */
        Cartridge(std::string);

        /* @brief Distruttore della classe, svuota la memoria occupata da data
        */
        ~Cartridge();

        /* @brief CheckLogo() confronta i Byte da 0x0104 a 0x0133 con l'esadecimale originale del logo Nintendo
         * @return Ritorna True se corrisponde al logo, False altrimenti 
        */ 
        bool CheckLogo();
        
        /* @brief GetTitle() ritorna il titolo del gioco che si trova da 0x0134 a 0x0143
         * @return Ritorna una stringa contenente il titolo in uppercase
        */ 
        std::string GetTitle();

        /* CheckCGBFlag() controlla il byte a 0x0143 e ritorna se il CGB (Gameboy a colori) e' attivo o no
         * @return Ritorna la presenza del CGB, true = attivo, false = disattivato
        */ 
        bool CheckCGBFlag();

        /* @brief GetNewLicenseeCode() ritorna il codice licensa presente all'indirizzo 0x0145
         * @return Ritorna una stringa corrispondendte al Byte nella cella di memoria all'indirizzo 0x0145
        */ 
        std::string GetNewLicenseeCode();

        /* @brief GetCartridgeType() ritorna il tipo della cartridge
         * @return Ritorna la stringa contenente il tipo della cartridge
        */
        std::string GetCartridgeType();

        /* @attention FUNZIONE UTILIZZATA NEL COSTRUCTOR NON USARE DA ALTRE PARTI 
         * @brief GetRomSize() ritorna la grandezza della ROM, dato un puntatore
         *
         * @param Un puntatore ad un array temporaneo
         * @return ritorna un insigned int con la grandezza della ROM in base all'indirizzo di 0x0148
        */
        unsigned int GetRomSize(Byte*);

        /* @brief GetRomSize() ritorna la grandezza della ROM
         * @return ritorna un insigned int con la grandezza della ROM in base all'indirizzo di 0x0148
        */
        unsigned int GetRomSize();

        /* GetRamSize() ritorna la grandezza della RAM 
         * @return ritorna un insigned int con la grandezza della RAM in base all'indirizzo di 0x0149
        */
        unsigned int GetRamSize();
        
        
        /* @brief GetOldLicenseeCode() ritorna il vecchio Licensee code
         * @return ritorna il vecchio Licensee code. Se l'esadecimale a 0x14B e' 0x33 ritornerà il NewLicenseeCode
        */
        std::string GetOldLicenseeCode();

        /* @brief ComputeChecksum() il checksum controlla i byte da 0x0134 a 0x014C.
         *  Se il risultato non corrisponde al valore in 0x014D l'esecuzione e' terminata
         *  
         *  @return Booleano contente il risultato del checksum
        */
        bool ComputeChecksum();
        

        /* @brief ValidateCartridge() controllo totale che ritorna un booleano in base
         * alla veridicità della cartridge
         *
         * @return True se la cartridge è legittima, False altrimenti
        */ 
        bool ValidateCartridge();


        /* @brief ReadCart() ritorna un valore, dato l'indirizzo come parametro
         * @return ritorna un Byte presente all'indirizzo "address"
         * 
         * @deprecated Non si userà piu dato che la cartridge viene caricata in memoria
        */
        Byte ReadCart(Word);

        /* @brief ReadFromCart() ritorna un array con i valori da inizio a fine
         * @return ritorna un puntatore ad un array di (endAddress - startAddress) + 1 Byte,
         *         contenente i dati da startAddress a endAddress.
         * @deprecated Non si userà piu dato che la cartridge viene caricata in memoria
        */  
        Byte* ReadFromToCart(Word, Word);

        /* @brief GetData() ritorna un puntatore all'array data
         * @return ritorna un puntatore all'array contenente la cartridge
         * 
         * @deprecated Non utilizzato ma mi dispiace cancellarlo lol
        */  
        Byte* GetData();
    private:
        Byte* data;
        
        // Documentazione: https://gbdev.io/pandocs/The_Cartridge_Header.html           
};