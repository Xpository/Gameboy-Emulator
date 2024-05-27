#include "../headers/LR35902.hpp"
#include "../headers/emu.hpp"
#include <iostream>



//personalmente penso che questa dichiarazione qua sotto debbe essere contenata in cartridge visto che 
//la riguarda totalmente 

// Ehm casotti fai poco il grosso eh





void LR35902::UpdateRegister(registri rx, Word data )
{
	switch (rx) {
	case RT_A:
		thisContext.registers.A = data;
		break;
	case RT_B:
		thisContext.registers.B = data;
		break;
	case RT_C:
		thisContext.registers.C = data;
		break;
	case RT_D:
		thisContext.registers.D = data;
		break;
	case RT_E:
		thisContext.registers.E = data;
		break;
	case RT_H:
		thisContext.registers.H = data;
		break;
	case RT_L:
		thisContext.registers.L = data;
		break;
	case RT_BC:
		thisContext.registers.B = ExtractUpper(data);
		thisContext.registers.C = ExtractLower(data);
		break;
	case RT_DE:
		thisContext.registers.D = ExtractUpper(data);
		thisContext.registers.E = ExtractLower(data);
		break;
	case RT_HL:
		thisContext.registers.H = ExtractUpper(data);
		thisContext.registers.L = ExtractLower(data);
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
		std::cerr << "RunTimeError_FlagNotFound"; // Sembra troppo professionale infatti non lRT_ho scritto io
		break;
	}
}



Word LR35902::GetRegister(registri c)
{
	switch (c)
	{
	case RT_A:
		return thisContext.registers.A;
	case RT_B:
		return thisContext.registers.B;
	case RT_C:
		return thisContext.registers.C;
	case RT_D:
		return thisContext.registers.D;
	case RT_E:
		return thisContext.registers.E;
	case RT_H:
		return thisContext.registers.H;
	case RT_L:
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
	case 'z':
		return fl.ZF;
	case 'c':
		return fl.CF;
	case 'n':
		return fl.NF;
	case 'h':
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
	//viene preso il program counter dellRT_isttruzione corrente e aumentato
	thisContext.currentOpcode = mem->Read(thisContext.registers.PC++); 

	//una volta preso lRT_oPCode nella riga precedente questo viene passato nel  context per ottenere lRT_istruzione corrispondente
	thisContext.currentInstruction = instruction_by_opcode(thisContext.currentOpcode); 

	if(thisContext.currentInstruction == NULL){
		std::cerr<<"Unknown Instruction", thisContext.currentInstruction ;
	}
};



//  ------------------------ Casotti leggi qua ------------------------
//	Allora per fixare quello che abbiamo detto in classe ho fatto una funzione dentro "oPCodes.cpp"
//  di nome "GetRegisterByName" te ci metti come parametro lRT_enum registri e ritorna una stringa 
//  poi cosa fai... fa un controllo sulla lunghezza, se eRT_ di 0 eRT_ un errore e ritorni "RunTimeError_RegisterNotFound"
//  Se eRT_ di 1 allora chiami la funzione GetRegister, ora ATTENTO perche la funzione prende come parametro un char
// 	Potresti fare 2 cose
//  - Modifichi la funzione e cambi il parametro a stringa, e a quel punto dovrai cambiare lo switch con if, perche allo switch
//    non vanno bene le stringhe (da errore)
//  - Casti il risultato da string a char (molto piu veloce) pero non so se funziona.
//  Infine se la lunghezza eRT_ pari a due, molto piu semplice chiami "GetDoubleRegister" che ritorna una Word.

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
		
        case AM_MR_R:
            thisContext.fetchedData = GetRegister(thisContext.currentInstruction->reg2);
            thisContext.memoryDestination = GetRegister(thisContext.currentInstruction->reg1);
            thisContext.memoryDestination_is_mem = true;

            if (thisContext.currentInstruction->reg1 == RT_C) {
                thisContext.memoryDestination |= 0xFF00;
            }

            return;

        case AM_R_MR: {
            Word addr = GetRegister(thisContext.currentInstruction->reg2);

            if (thisContext.currentInstruction->reg2 == RT_C) {
                addr |= 0xFF00;
            }

            thisContext.fetchedData = mem->Read(addr);
            emu_cycles(1);

        } return;

        case AM_R_HLI:
            thisContext.fetchedData = mem->Read(GetRegister(thisContext.currentInstruction->reg2));
            emu_cycles(1);
            UpdateRegister(RT_HL, GetRegister(RT_HL) + 1);
            return;

        case AM_R_HLD:
            thisContext.fetchedData = mem->Read(GetRegister(thisContext.currentInstruction->reg2));
            emu_cycles(1);
            UpdateRegister(RT_HL, GetRegister(RT_HL) - 1);
            return;

        case AM_HLI_R:
            thisContext.fetchedData = GetRegister(thisContext.currentInstruction->reg2);
            thisContext.memoryDestination = GetRegister(thisContext.currentInstruction->reg1);
            thisContext.memoryDestination_is_mem = true;
            UpdateRegister(RT_HL, GetRegister(RT_HL) + 1);
            return;

        case AM_HLD_R:
            thisContext.fetchedData = GetRegister(thisContext.currentInstruction->reg2);
            thisContext.memoryDestination = GetRegister(thisContext.currentInstruction->reg1);
            thisContext.memoryDestination_is_mem = true;
            UpdateRegister(RT_HL, GetRegister(RT_HL) - 1);
            return;

        case AM_R_A8:
            thisContext.fetchedData = mem->Read(thisContext.registers.PC);
            emu_cycles(1);
            thisContext.registers.PC++;
            return;

        case AM_A8_R:
            thisContext.memoryDestination = mem->Read(thisContext.registers.PC) | 0xFF00;
            thisContext.memoryDestination_is_mem = true;
            emu_cycles(1);
            thisContext.registers.PC++;
            return;

        case AM_HL_SPR:
            thisContext.fetchedData = mem->Read(thisContext.registers.PC);
            emu_cycles(1);
            thisContext.registers.PC++;
            return;

        case AM_D8:
            thisContext.fetchedData = mem->Read(thisContext.registers.PC);
            emu_cycles(1);
            thisContext.registers.PC++;
            return;

        case AM_A16_R:
        case AM_D16_R: {
            Word lo = mem->Read(thisContext.registers.PC);
            emu_cycles(1);

            Word hi = mem->Read(thisContext.registers.PC + 1);
            emu_cycles(1);

            thisContext.memoryDestination = lo | (hi << 8);
            thisContext.memoryDestination_is_mem = true;

            thisContext.registers.PC += 2;
            thisContext.fetchedData = GetRegister(thisContext.currentInstruction->reg2);

        } return;

        case AM_MR_D8:
            thisContext.fetchedData = mem->Read(thisContext.registers.PC);
            emu_cycles(1);
            thisContext.registers.PC++;
            thisContext.memoryDestination = GetRegister(thisContext.currentInstruction->reg1);
            thisContext.memoryDestination_is_mem = true;
            return;

        case AM_MR:
            thisContext.memoryDestination = GetRegister(thisContext.currentInstruction->reg1);
            thisContext.memoryDestination_is_mem = true;
            thisContext.fetchedData = mem->Read(GetRegister(thisContext.currentInstruction->reg1));
            emu_cycles(1);
            return;

        case AM_R_A16: {
            Word lo = mem->Read(thisContext.registers.PC);
            emu_cycles(1);

            Word hi = mem->Read(thisContext.registers.PC + 1);
            emu_cycles(1);

            Word addr = lo | (hi << 8);

            thisContext.registers.PC += 2;
            thisContext.fetchedData = mem->Read(addr);
            emu_cycles(1);

            return;
        }

		default:
			std::cerr<<"Unknown addressing mode error (itRT_s all fucked up)",thisContext.currentInstruction->indi;
			exit(-7);
			return;
	}

}

void LR35902::execute(){

	//esecuzione istruzioni
	std::cout<<"Executing Instruction:\nPC: \t", thisContext.currentInstruction;

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