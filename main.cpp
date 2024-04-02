#include <iostream>
#include "headers/LR35902.h"
#include "cpp/cartridge.cpp"

// g++ -o main main.cpp cpp/cartridge.cpp cpp/LR35902.cpp cpp/opcodes.cpp cpp/bus.cpp -I headers

int main() {
	Cartridge cart("roms/MarioYoshi.gb");
	

	bool lol = cart.CheckLogo();
	std::string title = cart.GetTitle();
	std::string lic = cart.GetNewLicenseeCode();
	std::string type = cart.GetCartridgeType();
	unsigned int size = cart.GetRomSize();
	std::string oldlic = cart.GetOldLicenseeCode();
	bool cksum = cart.ComputeChecksum();


	std::cout << "| " << lol << " | " << title << " | " << lic << " | " << type << " | " << oldlic << " | " << cksum << " | " << "Size: " <<  size << "\n\n";
	
	return 0;
	//p}

