#include "../headers/LR35902.hpp"
#include <iostream>



//personalmente penso che questa dichiarazione qua sotto debbe essere contenata in cartridge visto che 
//la riguarda totalmente 

// Ehm casotti fai poco il grosso eh





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

	if(thisContext.currentInstruction == NULL){
		std::cerr<<"Unknown Instruction", thisContext.currentInstruction ;
	}
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
		case AM_R_D8:
			thisContext.fetchedData=mem->Read(thisContext.registers.PC);
			emu_cycles(1);
			thisContext.registers.PC++;
			return;
		case AM_D16: {
			Word lo = mem->Read(thisContext.registers.PC);
			emu_cycles(1);

			Word hi =  mem->Read(thisContext.registers.PC+1);
			emu_cycles(1);

			thisContext.fetchedData= lo|(hi<<8);

			thisContext.registers.PC +=2;

			return;

		}

		default:
			std::cerr<<"Unknown addressing mode error (it's all fucked up)",thisContext.currentInstruction->indi;
			exit(-7);
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
			pushStack(reg.PC >> 8);
			pushStack(reg.PC & 0xFF);

			thisContext.IME=false;

			Byte intF = mem->Read(thisContext.IF);
			intF &= ~interruptFlag;
			mem->Write(thisContext.IF, intF);

			//punta alle istruzioni della ISR
			switch (i) {
				case VBLANK:
					reg.PC = 0x0040;
					break;
				case LCD_STAT:
					reg.PC = 0x0048;
					break;
				case TIMER:
					reg.PC = 0x0050;
					break;
				case SERIAL:
					reg.PC = 0x0058;
					break;
				case JOYPAD:
					reg.PC = 0x0060;
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
	mem->Write(reg.SP--, value);
}

Byte LR35902::popStack() {
	return mem->Read(++reg.SP);
}

void LR35902::returnFromInterrupt() {
	// Ripristina lo stato del processore
	Byte low = popStack();
	Byte high = popStack();
	reg.PC = (high << 8) | low;

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