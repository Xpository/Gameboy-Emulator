#include <iostream>
#include "machine.cpp"

int main() {
    
	unsigned char a = 0x0A;
	unsigned char b = 0xB3;
	unsigned short ab = a + b;
	std::cout << "AB: " << ab << "\n";
	ab += 1;
	std::cout << "AB: " << ab << "\n";
	
	return 0;
}