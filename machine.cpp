#include "machine.h"
#include "types.h"

LR35902::LR35902()
{
	for (int i = 0; i < 0x200000; i++) {
		this->Memory[i] = 0x00;
	}
	A = 0x00; 

	B = 0x00;
	C = 0x00;

	D = 0x00;
	E = 0x00;

	H = 0x00;
	L = 0x00;

	SP = 0x0000;
	PC = 0x0000;
}
