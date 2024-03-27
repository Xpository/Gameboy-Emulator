#include "cartridge.h"
#include <iostream>
 
Cartridge::Cartridge(std::string filepath) {
    // Apre il file in modalità binaria.
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cout << "File not found\n";
        return;
    }
    
    // Vai alla fine del file.
    file.seekg(0, std::ios::end);
    // Ottieni la dimensione del file.
    std::streamsize size = file.tellg();
    // Torna all'inizio del file.
    file.seekg(0, std::ios::beg);

    // Se la dimensione del file è maggiore della dimensione dell'array, è necessario gestire l'errore o ridimensionare l'array.
    if (size > sizeof(data)) {
        std::cerr << "Errore: Il file è troppo grande per essere caricato nell'array.\n";
        return;
    }

    // Legge il contenuto del file nell'array.
    if (!file.read(reinterpret_cast<char*>(data), size)) {
        std::cerr << "Errore durante la lettura del file.\n";
    }

    // Chiude il file.
    file.close();
}

/* CheckLogo controlla i Byte 0x0104 a 0x0133 per vedere se corrisponde
 * @return ritorna true se corrisponde, false altrimenti 
*/ 
bool Cartridge::CheckLogo(){
    Byte logo[48] = {
        0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    };

    for(Word i = 0x0104, j = 0; i <= 0x0133; i++, j++){
        if(data[i] != logo[j]){
            return false;
        }
    }
    return true;
}
