#include "../headers/LR35902.h"
#include "../headers/memory.h"
#include <iostream>
#include <string>


//personalmente penso che questa dichiarazione qua sotto debbe essere contenata in cartridge visto che 
//la riguarda totalmente 



LR35902::LR35902(std::string bootROMS = "DMG0", bool isChecksum00 = false, bool isAnyLicensee01 = false, Byte sumOfTitleBytes = 0x00)
{


	if(bootROMS == "DMG0"){
		reg.A = 0x01;

		reg.B = 0xFF;
		reg.C = 0x13;

		reg.D = 0x00;
		reg.E = 0xC1;

		reg.H = 0x84;
		reg.L = 0x03;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = false;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
	}else if(bootROMS == "DMG"){
		reg.A = 0x01;

		reg.B = 0x00;
		reg.C = 0x13;

		reg.D = 0x00;
		reg.E = 0xD8;

		reg.H = 0x01;
		reg.L = 0x4D;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;
		
		fl.ZF = true;
		fl.NF = false;
		if(isChecksum00){
			fl.CF = false;
			fl.HF = false;
		}else{
			fl.CF = true;
			fl.HF = true;
		}
	}else if(bootROMS == "MGB"){
		reg.A = 0xFF;

		reg.B = 0x00;
		reg.C = 0x13;

		reg.D = 0x00;
		reg.E = 0xD8;

		reg.H = 0x01;
		reg.L = 0x4D;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;
		
		fl.ZF = true;
		fl.NF = false;
		if(isChecksum00){
			fl.CF = false;
			fl.HF = false;
		}else{
			fl.CF = true;
			fl.HF = true;
		}
	}else if(bootROMS == "SGB"){
		reg.A = 0x01;

		reg.B = 0x00;
		reg.C = 0x14;

		reg.D = 0x00;
		reg.E = 0x00;

		reg.H = 0xC0;
		reg.L = 0x60;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = false;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
	}else if(bootROMS == "SBG2"){
		reg.A = 0xFF;

		reg.B = 0x00;
		reg.C = 0x14;

		reg.D = 0x00;
		reg.E = 0x00;

		reg.H = 0xC0;
		reg.L = 0x60;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = false;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
	}else if(bootROMS == "CGB-DMG"){
		reg.A = 0x11;
		if(isAnyLicensee01){
			reg.B = sumOfTitleBytes;
		}else{
			reg.B = 0x00;
		}
			


		reg.C = 0x00;

		reg.D = 0x00;
		reg.E = 0x08;

		if(reg.B == 0x43 || reg.B == 0x58){
			reg.H = 0x99;
			reg.L = 0x1A;
		}else{
			reg.H = 0x00;
			reg.L = 0x7C;
		}

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = true;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
	}else if(bootROMS == "AGB-DMG"){
		reg.A = 0x11;
		if(isAnyLicensee01){
			reg.B = sumOfTitleBytes + 1;
		}else{
			reg.B = 0x00;
		}
			


		reg.C = 0x00;

		reg.D = 0x00;
		reg.E = 0x08;

		if(reg.B == 0x44 || reg.B == 0x59){
			reg.H = 0x99;
			reg.L = 0x1A;
		}else{
			reg.H = 0x00;
			reg.L = 0x7C;
		}
		
		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		// Su come vengono settati questi due flag c'e' molta confusione.
		// Sono sulla base delle operazioni precedenti, qui sotto incollo la logica su come settarli
		// ****
		//		To determine the flags, take the B register you would have gotten on CGB3, and inc it. 
		// 		(To be precise: an inc b is the last operation to touch the flags.) The carry and direction flags are always clear, though.
		//																																	****
		// Anche se in un incremento non verra mai fuori zero, e il flag H si setta solo nelle sottrazioni.
		// Qualcuno puo' controllare piu a fondo tysm @0hM1C1uf1 @AleBitCode @Cyb3s
		fl.ZF = false;
		fl.HF = false;

		fl.CF = false;
		fl.NF = false;
	}else if(bootROMS == "CGB"){
		reg.A = 0x11;

		reg.B = 0x00;	
		reg.C = 0x00;

		reg.D = 0xFF;
		reg.E = 0x56;

		reg.H = 0x00;
		reg.L = 0x0D;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = true;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
	}else if(bootROMS == "AGB"){
		reg.A = 0x11;

		reg.B = 0x01;	
		reg.C = 0x00;

		reg.D = 0xFF;
		reg.E = 0x56;

		reg.H = 0x00;
		reg.L = 0x0D;

		reg.SP = 0xFFFE;
		reg.PC = 0x0100;

		fl.ZF = false;
		fl.CF = false;

		fl.NF = false;
		fl.HF = false;
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
		reg.A = data;
		break;
	case 'B':
		reg.B = data;
		break;
	case 'C':
		reg.C = data;
		break;
	case 'D':
		reg.D = data;
		break;
	case 'E':
		reg.E = data;
		break;
	case 'H':
		reg.H = data;
		break;
	case 'L':
		reg.L = data;
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
		fl.ZF = state;
		break;
	case 'C':
		fl.CF = state;
		break;
	case 'N':
		fl.NF = state;
		break;
	case 'H':
		fl.HF = state;
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
		reg.B = ExtractUpper(data);
		reg.C = ExtractLower(data);
	}
	else if (rx == "DE") {
		reg.D = ExtractUpper(data);
		reg.E = ExtractLower(data);
	}
	else if (rx == "HL") {
		reg.H = ExtractUpper(data);
		reg.L = ExtractLower(data);
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
		return reg.A;
	case 'B':
		return reg.B;
	case 'C':
		return reg.C;
	case 'D':
		return reg.D;
	case 'E':
		return reg.E;
	case 'H':
		return reg.H;
	case 'L':
		return reg.L;									
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
		Word highByte = (reg.B << 8);
		return highByte + reg.C;
	}
	else if (rx == "DE") {
		Word highByte = (reg.D << 8);
		return highByte + reg.E;
	}
	else if (rx == "HL") {
		Word highByte = (reg.H << 8);
		return highByte + reg.L;
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
		return fl.ZF;
	case 'C':
		return fl.CF;
	case 'N':
		return fl.NF;
	case 'H':
		return fl.HF;							
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



LR35902::CPU_Context thisContext ={0}; //0 corrisponde ad un valore di prova che va ad halt


static void fetch_ins(){
	thisContext.currentOpcode=B_Read(thisContext.registers.PC++);
	thisContext.currentInstruction=instruction_by_opcode(thisContext.currentOpcode);
};


static void fetch_data(){

}

static void execute(){

}

bool LR35902::CPU_Step(){
	if(!thisContext.halt){
		fetch_ins();
		fetch_data();
		execute();
	}
	
	
	return false;
}