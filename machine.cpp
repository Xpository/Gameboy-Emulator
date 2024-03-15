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
}

void LR35902::UpdateRegister(Byte data, char r1)
{
	switch (r1)
	{
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
void LR35902::UpdateRegister(Word data, char r1, char r2)
{
	switch (r1)
	{
	case 'A':
		A = ExtractUpper(data);
		break;
	case 'B':
		B = ExtractUpper(data);
		break;
	case 'C':
		C = ExtractUpper(data);
		break;
	case 'D':
		D = ExtractUpper(data);
		break;
	case 'E':
		E = ExtractUpper(data);
		break;
	case 'H':
		H = ExtractUpper(data);
		break;
	case 'L':
		L = ExtractUpper(data);
		break;
	default:
		std::cerr << "Come cazzo hai fatto a sbagliare registro?\n";
		break;
	}

	switch (r2)
	{
	case 'A':
		A = ExtractLower(data);
		break;
	case 'B':
		B = ExtractLower(data);
		break;
	case 'C':
		C = ExtractLower(data);
		break;
	case 'D':
		D = ExtractLower(data);
		break;
	case 'E':
		E = ExtractLower(data);
		break;
	case 'H':
		H = ExtractLower(data);
		break;
	case 'L':
		L = ExtractLower(data);
		break;
	default:
		std::cerr << "Come cazzo hai fatto a sbagliare registro?\n";
		break;
	}
}

Byte LR35902::ExtractUpper(Word data)
{
	Byte highByte = (data >> 8) & 0xFF; // Estrai il byte pi� significativo
	return highByte;
}

Byte LR35902::ExtractLower(Word data)
{
	Byte lowByte = data & 0xFF; // Estrai il byte meno significativo
	return lowByte;
}
