#include "headers/LR35902.hpp"
#include <iostream>


// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v


int main() {	
	std::string fp = "roms/Tetris.gb";
	LR35902 thisCPU(fp);

	std::cout << "FINISH";
}


