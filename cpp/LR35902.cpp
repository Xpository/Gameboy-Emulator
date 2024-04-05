#include "../headers/LR35902.h"
#include "../headers/bus.h"
#include <iostream>
#include <string>



LR35902::LR35902(std::string bootROMS = "DMG0", bool isChecksum00 = false, bool isAnyLicensee01 = false, Byte sumOfTitleBytes = 0x00)
{
	
	if(bootROMS == "DMG0"){
		A = 0x01;

		B = 0xFF;
		C = 0x13;

		D = 0x00;
		E = 0xC1;

		H = 0x84;
		L = 0x03;

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = false;
		CF = false;

		NF = false;
		HF = false;
	}else if(bootROMS == "DMG"){
		A = 0x01;

		B = 0x00;
		C = 0x13;

		D = 0x00;
		E = 0xD8;

		H = 0x01;
		L = 0x4D;

		SP = 0xFFFE;
		PC = 0x0100;
		
		ZF = true;
		NF = false;
		if(isChecksum00){
			CF = false;
			HF = false;
		}else{
			CF = true;
			HF = true;
		}
	}else if(bootROMS == "MGB"){
		A = 0xFF;

		B = 0x00;
		C = 0x13;

		D = 0x00;
		E = 0xD8;

		H = 0x01;
		L = 0x4D;

		SP = 0xFFFE;
		PC = 0x0100;
		
		ZF = true;
		NF = false;
		if(isChecksum00){
			CF = false;
			HF = false;
		}else{
			CF = true;
			HF = true;
		}
	}else if(bootROMS == "SGB"){
		A = 0x01;

		B = 0x00;
		C = 0x14;

		D = 0x00;
		E = 0x00;

		H = 0xC0;
		L = 0x60;

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = false;
		CF = false;

		NF = false;
		HF = false;
	}else if(bootROMS == "SBG2"){
		A = 0xFF;

		B = 0x00;
		C = 0x14;

		D = 0x00;
		E = 0x00;

		H = 0xC0;
		L = 0x60;

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = false;
		CF = false;

		NF = false;
		HF = false;
	}else if(bootROMS == "CGB-DMG"){
		A = 0x11;
		if(isAnyLicensee01){
			B = sumOfTitleBytes;
		}else{
			B = 0x00;
		}
			


		C = 0x00;

		D = 0x00;
		E = 0x08;

		if(B == 0x43 || B == 0x58){
			H = 0x99;
			L = 0x1A;
		}else{
			H = 0x00;
			L = 0x7C;
		}

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = true;
		CF = false;

		NF = false;
		HF = false;
	}else if(bootROMS == "AGB-DMG"){
		A = 0x11;
		if(isAnyLicensee01){
			B = sumOfTitleBytes + 1;
		}else{
			B = 0x00;
		}
			


		C = 0x00;

		D = 0x00;
		E = 0x08;

		if(B == 0x44 || B == 0x59){
			H = 0x99;
			L = 0x1A;
		}else{
			H = 0x00;
			L = 0x7C;
		}
		
		SP = 0xFFFE;
		PC = 0x0100;

		// Su come vengono settati questi due flag c'e' molta confusione.
		// Sono sulla base delle operazioni precedenti, qui sotto incollo la logica su come settarli
		// ****
		//		To determine the flags, take the B register you would have gotten on CGB3, and inc it. 
		// 		(To be precise: an inc b is the last operation to touch the flags.) The carry and direction flags are always clear, though.
		//																																	****
		// Anche se in un incremento non verra mai fuori zero, e il flag H si setta solo nelle sottrazioni.
		// Qualcuno puo' controllare piu a fondo tysm @0hM1C1uf1 @AleBitCode @Cyb3s
		ZF = false;
		HF = false;

		CF = false;
		NF = false;
	}else if(bootROMS == "CGB"){
		A = 0x11;

		B = 0x00;	
		C = 0x00;

		D = 0xFF;
		E = 0x56;

		H = 0x00;
		L = 0x0D;

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = true;
		CF = false;

		NF = false;
		HF = false;
	}else if(bootROMS == "AGB"){
		A = 0x11;

		B = 0x01;	
		C = 0x00;

		D = 0xFF;
		E = 0x56;

		H = 0x00;
		L = 0x0D;

		SP = 0xFFFE;
		PC = 0x0100;

		ZF = false;
		CF = false;

		NF = false;
		HF = false;
	}else{
		std::cerr << "Errore: Boot Rom non riconosciuta";
	}
}


/* UpdateRegister modifica il valore di un registro
*  @param dato byte da inserire
*  @param registro in maiuscolo
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
*  @param flag da modificare
*  @param stato in cui modificarlo, inizalmente true
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
*  @param dato word da inserire
*  @param registro in maiuscolo
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
*  @param registro da cui prendere il dato
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
 * @param 2 caratteri che simboleggiano il registro
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
*  @param flag da cui prendere il dato
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
*  @param word da cui estrarre il valore
*  @return valore superiore
*/ 
Byte LR35902::ExtractUpper(Word data)
{
	Byte highByte = (data >> 8) & 0xFF; // Estrai il byte più significativo
	return highByte;
}

/* ExtractUpper estrae la parte inferiore di una word
*  @param word da cui estrarre il valore
*  @return valore inferiore
*/ 
Byte LR35902::ExtractLower(Word data)
{
	Byte lowByte = data & 0xFF; // Estrai il byte meno significativo
	return lowByte;
}
