#include "cartridge.h"

Cartridge::Cartridge(){
    // Inizializzazione da ChatGPT, funziona ma non so minimamente perche <3
    std::ifstream file("roms/PokemonRed.gb", std::ios::binary);
	std::vector<Byte> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}