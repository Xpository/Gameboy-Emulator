#include <iostream>
#include "headers/LR35902.h"
#include "cpp/cartridge.cpp"

// g++ -o main main.cpp cpp/cartridge.cpp cpp/LR35902.cpp cpp/opcodes.cpp cpp/bus.cpp -I headers

int main() {
	Cartridge cart("roms/PokemonRed.gb");
	
	Byte dt = cart.data[0x104];

	bool lol = cart.CheckLogo();

	std::cout << "NIGGA " << lol << " ";
	return 0;
}

// FFFF0