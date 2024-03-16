#include "../headers/bus.h"

Bus::Bus() {
	//clear RAM content
	for (auto &i : ram) i = 0x00;
}

Bus::~Bus() {
    // Finisci
}

void Bus::Write(Word addr, Byte data) {
	ram[addr] = data;
}

Byte Bus::Read(Word addr, bool bReadOnly = false) {
	return ram[addr];
}