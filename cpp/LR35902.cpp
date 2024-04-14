#include "../headers/LR35902.hpp"
#include <iostream>



//personalmente penso che questa dichiarazione qua sotto debbe essere contenata in cartridge visto che 
//la riguarda totalmente 

// Ehm casotti fai poco il grosso eh




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

LR35902::LR35902(std::string filepath)
{
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

	thisContext = {0};

	// Very cool pointer shit :)
	cart = new Cartridge(filepath);
	mem = new Memory(cart->GetData(), cart->GetRomSize());
}

void LR35902::fetch_ins(){
	thisContext.currentOpcode=cart->ReadCart(thisContext.registers.PC++);
	thisContext.currentInstruction=instruction_by_opcode(thisContext.currentOpcode);
};


void LR35902::fetch_data(){

}

void LR35902::execute(){

}

bool LR35902::CPU_Step(){
	if(!thisContext.halt){
		fetch_ins();
		fetch_data();
		execute();
	}
	
	
	return false;
}