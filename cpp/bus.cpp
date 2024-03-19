#include "../headers/bus.h"

Bus::Bus() {
	//clear RAM content
	for (auto &i : RAM) i = 0x00;
}

Bus::~Bus() {
    // Finisci
}

void Bus::Write(Word addr, Byte data) {
	RAM[addr] = data;
}

Byte Bus::Read(Word addr, bool bReadOnly = false) {
	return RAM[addr];
}