#include "../headers/LR35902.hpp"
#include <iostream>



//personalmente penso che questa dichiarazione qua sotto debbe essere contenata in cartridge visto che 
//la riguarda totalmente 

// Ehm casotti fai poco il grosso eh





void LR35902::UpdateRegister(Byte data, char r1)
{
	switch (r1) {
	case 'A':
		thisContext.registers.A = data;
		break;
	case 'B':
		thisContext.registers.B = data;
		break;
	case 'C':
		thisContext.registers.C = data;
		break;
	case 'D':
		thisContext.registers.D = data;
		break;
	case 'E':
		thisContext.registers.E = data;
		break;
	case 'H':
		thisContext.registers.H = data;
		break;
	case 'L':
		thisContext.registers.L = data;
		break;
	default:
		std::cerr << "RunTimeError_FlagNotFound";
		break;
	}
}




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


void LR35902::UpdateRegister(Word data, std::string rx)
{
	if (rx == "BC") {
		thisContext.registers.B = ExtractUpper(data);
		thisContext.registers.C = ExtractLower(data);
	}
	else if (rx == "DE") {
		thisContext.registers.D = ExtractUpper(data);
		thisContext.registers.E = ExtractLower(data);
	}
	else if (rx == "HL") {
		thisContext.registers.H = ExtractUpper(data);
		thisContext.registers.L = ExtractLower(data);
	}
}


Byte LR35902::GetRegister(char c)
{
	switch (c)
	{
	case 'A':
		return thisContext.registers.A;
	case 'B':
		return thisContext.registers.B;
	case 'C':
		return thisContext.registers.C;
	case 'D':
		return thisContext.registers.D;
	case 'E':
		return thisContext.registers.E;
	case 'H':
		return thisContext.registers.H;
	case 'L':
		return thisContext.registers.L;									
	default:
		std::cerr << "RunTimeError_RegisterNotFound\n";
	}
	return 0x00;
}


Word LR35902::GetDoubleRegister(std::string rx){
	if (rx == "BC") {
		Word highByte = (thisContext.registers.B << 8);
		return highByte + thisContext.registers.C;
	}
	else if (rx == "DE") {
		Word highByte = (thisContext.registers.D << 8);
		return highByte + thisContext.registers.E;
	}
	else if (rx == "HL") {
		Word highByte = (thisContext.registers.H << 8);
		return highByte + thisContext.registers.L;
	}
   return 0x0000;
}



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

LR35902::LR35902(std::string filepath, Memory& memory)
{
	thisContext.registers.A = 0x01;

	thisContext.registers.B = 0xFF;
	thisContext.registers.C = 0x13;

	thisContext.registers.D = 0x00;
	thisContext.registers.E = 0xC1;

	thisContext.registers.H = 0x84;
	thisContext.registers.L = 0x03;

	thisContext.registers.SP = 0xFFFE;
	thisContext.registers.PC = 0x0100;

	fl.ZF = false;
	fl.CF = false;

	fl.NF = false;
	fl.HF = false;

	thisContext.IE = 0xFFFF;
	thisContext.IF = 0xFF0F;
	thisContext.IME = 0x01;

	// Very cool pointer shenanigans :)
	mem = &memory;
	
}

void LR35902::fetch_ins(){
	//viene preso il program counter dell'isttruzione corrente e aumentato
	thisContext.currentOpcode = mem->Read(thisContext.registers.PC++); 

	//una volta preso l'opcode nella riga precedente questo viene passato nel  context per ottenere l'istruzione corrispondente
	thisContext.currentInstruction = instruction_by_opcode(thisContext.currentOpcode); 
};


//  ------------------------ Casotti leggi qua ------------------------
//	Allora per fixare quello che abbiamo detto in classe ho fatto una funzione dentro "opcodes.cpp"
//  di nome "GetRegisterByName" te ci metti come parametro l'enum registri e ritorna una stringa 
//  poi cosa fai... fa un controllo sulla lunghezza, se e' di 0 e' un errore e ritorni "RunTimeError_RegisterNotFound"
//  Se e' di 1 allora chiami la funzione GetRegister, ora ATTENTO perche la funzione prende come parametro un char
// 	Potresti fare 2 cose
//  - Modifichi la funzione e cambi il parametro a stringa, e a quel punto dovrai cambiare lo switch con if, perche allo switch
//    non vanno bene le stringhe (da errore)
//  - Casti il risultato da string a char (molto piu veloce) pero non so se funziona.
//  Infine se la lunghezza e' pari a due, molto piu semplice chiami "GetDoubleRegister" che ritorna una Word.

void LR35902::fetch_data(){
	thisContext.memoryDestination = 0;
	thisContext.memoryDestination_is_mem = false;

	switch(thisContext.currentInstruction->indi){
		case AM_IMP:
			return;
		case AM_R:
			thisContext.fetchedData=GetRegister(thisContext.currentInstruction->reg1);
			return;
	}

}

void LR35902::execute(){

	//esecuzione istruzioni

	if(thisContext.IME && (mem->Read(thisContext.IF) & mem->Read(thisContext.IE))){
		handleInterrupt();
	}
}

void LR35902::handleInterrupt(){
	for (int i = 0; i < 5; ++i) {
		Byte interruptFlag = 1 << i;

		if ((mem->Read(thisContext.IF) & interruptFlag) && (mem->Read(thisContext.IE) & interruptFlag)) {
			pushStack(thisContext.registers.PC >> 8);
			pushStack(thisContext.registers.PC & 0xFF);

			thisContext.IME=false;

			Byte intF = mem->Read(thisContext.IF);
			intF &= ~interruptFlag;
			mem->Write(thisContext.IF, intF);

			//punta alle istruzioni della ISR
			switch (i) {
				case VBLANK:
					thisContext.registers.PC = 0x0040;
					break;
				case LCD_STAT:
					thisContext.registers.PC = 0x0048;
					break;
				case TIMER:
					thisContext.registers.PC = 0x0050;
					break;
				case SERIAL:
					thisContext.registers.PC = 0x0058;
					break;
				case JOYPAD:
					thisContext.registers.PC = 0x0060;
					break;
			}
			break;
		}
	}
}

void LR35902::requestInterrupt(InterruptType type) {
	Byte intF = mem->Read(thisContext.IF);
	intF |= (1 << type);
	mem->Write(thisContext.IF, intF);
}

void LR35902::pushStack(Byte value) {
	mem->Write(thisContext.registers.SP--, value);
}

Byte LR35902::popStack() {
	return mem->Read(++thisContext.registers.SP);
}

void LR35902::returnFromInterrupt() {
	// Ripristina lo stato del processore
	Byte low = popStack();
	Byte high = popStack();
	thisContext.registers.PC = (high << 8) | low;

	// Riabilita gli interrupt
	thisContext.IME = 1;
}

bool LR35902::CPU_Step(){
	if(!thisContext.halt){
		fetch_ins();
		fetch_data();
		execute();
	}
	
	
	return false;
}