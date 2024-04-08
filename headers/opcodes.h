#pragma once

#include "types.h"
#include "LR35902.h"
#include "memory.h"
using namespace nstdtypes;


typedef enum { //--> typedef da un tag al tipo in questo caso ad enum

	//INSTRUCTION TABLE  	IN(INSTRUCTION)_XXX(NAME)

	IN_NOP,
	IN_LD,
	IN_INC,
	IN_DEC,
	IN_RLCA,
	IN_ADD,
	IN_RRCA,
	IN_STOP,
	IN_RLA,
	IN_JR,
	IN_RRA,
	IN_DAA,
	IN_CPL,
	IN_SCF,
	IN_CCF,
	IN_HALT,
	IN_ADC,
	IN_SUB,
	IN_SBC,
	IN_AND,
	IN_XOR,
	IN_OR,
	IN_CP,
	IN_POP,
	IN_JP,
	IN_PUSH,
	IN_RET,
	IN_CB,
	IN_CALL,
	IN_RETI,
	IN_LDH,
	IN_JPHL,
	IN_DI,
	IN_EI,
	IN_RST,
	IN_ERR,

	//CB INSTRUCTIONS (PREFIX CB)  -->  ISTRUZIONI NELLA SECONDA TABELLA 

	IN_RLC,
	IN_RRC,
	IN_RL,
	IN_RR,
	IN_SLA,
	IN_SRA,
	IN_SWAP,
	IN_SRL,
	IN_BIT,
	IN_RES,
	IN_SET
}tipo;


typedef enum {
	AM_R_D16,
	AM_R,
	AM_MR_R,
	AM_R,
	AM_R_D8,
	AM_R_MR,
	AM_R_HLI,
	AM_R_HLD,
	AM_HLI_R,
	AM_HLD_R,
	AM_R_A8,
	AM_A8_R,
	AM_HL_SPR,
	AM_D16,
	AM_D8,
	AM_IMP,
	AM_D16_R,
	AM_MR_D8,
	AM_MR,
	AM_A16_R,
	AM_R_A16
}indirizzamento;

typedef enum{
	RT_NONE,
	RT_A,
	RT_F,
	RT_B,
	RT_C,
	RT_D,
	RT_E,
	RT_H,
	RT_L,
	RT_AF,
	RT_BC,
	RT_DE,
	RT_HL,
	RT_SP,
	RT_PC
}registri;

typedef enum{// --> CONDIZIONI PER CUI UN ISTRUZIONE PUO' ESSERE ESEGUITA
	CT_NONE,   //nessuna
	CT_NZ,	//zero flag non settato
	CT_Z,	//zero flag settato
	CT_NC,	//carry flag non settato
	CT_C	//carry flag settato

}condizione;


// una volta necessaria un istruzione viene chiamata la struct passandoli le varie
// variabili di tipo enum, i quali possibili contenuti sono stati inseriti in 
// precedenza nella correspettiva enum

struct instruction 
{
	tipo type;
	indirizzamento indi;
	registri reg1;
	registri reg2;
	condizione cond;
	Byte parametri;  // variabile utilizzata da pochissime istruzioni ma necessaria 
};



class Opcodes {
	public:

	//roba inutile di merda non sapete fare un cazzo

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

	private:
		Memory memory;


};



												
