#include "../headers/LR35902.h"
#include "../headers/bus.h"
#include <iostream>
#include <string>



LR35902::LR35902()
{
	for (int i = 0; i < 0x200000; i++) {
		this->Memory[i] = 0x00;  //cartridges memorie
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


/* UpdateRegister modifica il valore di un registro
*  @param1 dato byte da inserire
*  @param2 registro in maiuscolo
*/ 
void LR35902::UpdateRegister(Byte data, char r1)
{
	switch (r1) {
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
		std::cerr << "RunTimeError_FlagNotFound";
		break;
	}
}



/* UpdateFlag modifica il valore di una flag
*  @param1 flag da modificare
*  @param2 stato in cui modificarlo, inizalmente true
*/ 
void LR35902::UpdateFlag(char f, bool state = true)
{
	switch (f) {
	case 'Z':
		ZF = state;
		break;
	case 'C':
		CF = state;
		break;
	case 'N':
		NF = state;
		break;
	case 'H':
		HF = state;
		break;
	default:
		std::cerr << "RunTimeError_FlagNotFound"; // Sembra troppo professionale infatti non l'ho scritto io
		break;
	}
}

/* UpdateRegister modifica il valore di un registro
*  @param1 dato word da inserire
*  @param2 registro in maiuscolo
*/ 
void LR35902::UpdateRegister(Word data, std::string rx)
{
	if (rx == "BC") {
		B = ExtractUpper(data);
		C = ExtractLower(data);
	}
	else if (rx == "DE") {
		D = ExtractUpper(data);
		E = ExtractLower(data);
	}
	else if (rx == "HL") {
		H = ExtractUpper(data);
		L = ExtractLower(data);
	}
}

/* GetRegister ritorna il valore di un dato registro
*  @param1 registro da cui prendere il dato
*  @return valore del registro
*/ 
Byte LR35902::GetRegister(char c)
{
	switch (c)
	{
	case 'A':
		return A;
	case 'B':
		return B;
	case 'C':
		return C;
	case 'D':
		return D;
	case 'E':
		return E;
	case 'H':
		return H;
	case 'L':
		return L;									
	default:
		std::cerr << "RunTimeError_RegisterNotFound\n";
	}
	return 0x00;
}

/* GetDoubleRegister ritorna una word con i registri RX
 * @param1 2 caratteri che simboleggiano il registro
 * @return La word data dalla somma di parte alta + parte bassa (0x0000)
*/
Word LR35902::GetDoubleRegister(std::string rx){
	if (rx == "BC") {
		Word highByte = (B << 8);
		return highByte + C;
	}
	else if (rx == "DE") {
		Word highByte = (D << 8);
		return highByte + E;
	}
	else if (rx == "HL") {
		Word highByte = (H << 8);
		return highByte + L;
	}
   return 0x0000;
}


/* GetFlag ritorna il valore di un dato flag
*  @param1 flag da cui prendere il dato
*  @return valore del flag
*/ 
bool LR35902::GetFlag(char c)
{
	switch (c)
	{
	case 'Z':
		return ZF;
	case 'C':
		return CF;
	case 'N':
		return NF;
	case 'H':
		return HF;							
	default:
		std::cerr << "RunTimeError_FlagNotFound\n";
	}
	return false;
}

/* ExtractUpper estrae la parte superiore di una word
*  @param1 word da cui estrarre il valore
*  @return valore superiore
*/ 
Byte LR35902::ExtractUpper(Word data)
{
	Byte highByte = (data >> 8) & 0xFF; // Estrai il byte più significativo
	return highByte;
}

/* ExtractUpper estrae la parte inferiore di una word
*  @param1 word da cui estrarre il valore
*  @return valore inferiore
*/ 
Byte LR35902::ExtractLower(Word data)
{
	Byte lowByte = data & 0xFF; // Estrai il byte meno significativo
	return lowByte;
}
