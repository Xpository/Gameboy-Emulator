#pragma once

#include "types.h"
#include "LR35902.h"
#include "bus.h"
using namespace nstdtypes;

class Opcodes {
	public:
		// Opcode a 0 operandi byte
		void ExecuteOpcodes(LR35902&, Byte);
		// Opcode a 1 operando byte (registro h/l)
		void ExecuteOpcodes(LR35902&, Byte, Byte);
		// Opcode a 1 operando word(registri rx)
		void ExecuteOpcodes(LR35902&, Byte, Word);
		// Opcode a 2 operandi byte
		void ExecuteOpcodes(LR35902&, Byte, Byte, Byte);
		// Opcode a 2 operandi word
		void ExecuteOpcodes(LR35902&, Byte, Word, Word);

		Opcodes(Bus &bus){
			this->RAM = bus;
		}

	private:
		Bus RAM;

		void NOP();
		void LD_BC_WORDDATA(LR35902&, Word);
		void LD_ADDRESSOFBC_A(LR35902&);
		void INC_BC(LR35902&);
		void INC_B(LR35902&);
		void DEC_B(LR35902&);
		void LD_B_BYTEDATA(LR35902&, Byte);
		void RLCA();								// L'istruzione RLCA nel set di istruzioni del processore LR35902, usato nel Game Boy, e' un'operazione di rotazione a sinistra del registro A(l'accumulatore) attraverso il carry flag. Questo significa che il bit piu' significativo (MSB) del registro A viene spostato nella posizione del bit meno significativo (LSB) e anche nel carry flag. 
		void LD_ADDRESSOFWORD_STACKPOINTER();
		void ADD_HL_BC(LR35902&);
		void LD_A_ADDRESSOFBC(LR35902&);
		void DEC_BC(LR35902&);
		void INC_C(LR35902&);
		void DEC_C(LR35902&);
		void LD_C_BYTEDATA(LR35902&);
		void RRCA();								// Stessa cosa del 0x07 ma a destra
};




												