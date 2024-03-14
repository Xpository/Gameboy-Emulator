#pragma once

#include "types.h"
using namespace nstdtypes;

class Opcodes {
	public:
		// Stessa logica, crea un overload
		void ExecuteOpcodes(Byte, Byte, Byte, Word, Word);

	private:
		void NOP();
		void LD_BC_WORDDATA();
		void LD_FF00BC_A();
		void INC_BC();
		void INC_B();
		void DEC_B();
		void LD_B_BYTEDATA();
		void RLCA();								// L'istruzione RLCA nel set di istruzioni del processore LR35902, usato nel Game Boy, è un'operazione di rotazione a sinistra del registro A(l'accumulatore) attraverso il carry flag. Questo significa che il bit più significativo (MSB) del registro A viene spostato nella posizione del bit meno significativo (LSB) e anche nel carry flag. 
		void LD_FF00WORDADDRESS_STACKPOINTER();
		void ADD_HL_BC();
		void LD_A_FF00BC();
		void DEC_BC();
		void INC_C();
		void DEC_C();
		void LD_C_BYTEDATA();
		void RRCA();								// Stessa cosa del 0x07 ma a destra
};




												