#include "machine.h"
#include "types.h"
#include <iostream>


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

	ZF = false;
	CF = false;

	NF = false;
	HF = false;
	
}

// Scrivile in maiuscolo
void LR35902::UpdateRegister(Byte data, char r1)
{
	switch (r1){
	case 'A':
		A = data;
		break;
	case 'B':
		B = data;
		break;
	case 'C':
		C = data;
		break;
	case 'D':
		D = data;
		break;
	case 'E':
		E = data;
		break;
	case 'H':
		H = data;
		break;
	case 'L':
		L = data;
		break;
	default:
		std::cerr << "Come cazzo hai fatto a sbagliare registro?\n";
		break;
	}
}



// Inserisci prima l'alto poi il basso, vedi di non sbagliare registri...

void LR35902::UpdateFlag(char f, bool state)
{
	switch (f){
	case 'z':
		ZF = state;
		break;
	case 'c':
		CF = state;
		break;
	case 'n':
		NF = state;
		break;
	case 'h':
		HF = state;
		break;
	default:
		std::cerr << "CompileTimeError_FlagNotFound"; // Sembra troppo professionale infatti non l'ho scritto io
		break;
	}
}


void LR35902::UpdateRegister(Word data, std::string rx)
{
	if(rx == "BC"){
		B = ExtractUpper(data);
		C = ExtractLower(data);
	}else if(rx == "DE"){
		D = ExtractUpper(data);
		E = ExtractLower(data);
	}else if(rx == "HL"){
		H = ExtractUpper(data);
		L = ExtractLower(data);
	}
}

// Inserisci il carattere in minuscolo
Byte LR35902::GetRegister(char c)
{
    switch (c)
	{
	case 'a':
		/* code */
		break;
	
	default:
		break;
	}
}

Byte LR35902::ExtractUpper(Word data)
{
	Byte highByte = (data >> 8) & 0xFF; // Estrai il byte più significativo
	return highByte;
}

Byte LR35902::ExtractLower(Word data)
{
	Byte lowByte = data & 0xFF; // Estrai il byte meno significativo
	return lowByte;
}
