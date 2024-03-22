#include "../headers/types.h"
#include "../headers/opcodes.h"
#include "../headers/LR35902.h"

using namespace nstdtypes;

/////////////////////////////////////////////////////
// 				Logica degli opcodes               //
/////////////////////////////////////////////////////
/*
	Z - Zero Flag
	N - Subtract Flag
	H - Half Carry Flag
	C - Carry Flag
	0 - The flag is reset
	1 - The flag is set
	- - The flag is left untouched

	In ordine sono:

			Z N H C
*/


void Opcodes::ExecuteOpcodes(LR35902 &machine, Byte opcode)
{
	switch(opcode)
	{
		case 0x00:
			NOP();
			break;

	}
}
 
void Opcodes::ExecuteOpcodes(LR35902 &machine, Byte opcode , Byte operand1)
{
	return;
}

void Opcodes::ExecuteOpcodes(LR35902 &machine, Byte opcode, Word operand1)
{
	switch (opcode)
	{
		case 0x01:
			LD_BC_WORDDATA(machine, operand1);
			break;
	}
}

void Opcodes::ExecuteOpcodes(LR35902 &machine, Byte opcode, Byte operand1, Byte operand2)
{
	return;
}

void Opcodes::ExecuteOpcodes(LR35902 &machine, Byte opcode, Word operand1, Word operand2)
{
}


// Funzioni degli opcodes

void Opcodes::NOP()
{
	// 4 Cicli
	return; 
}

void Opcodes::LD_BC_WORDDATA(LR35902 &machine, Word data)
{
	// 12 cicli
	machine.UpdateRegister(data, "BC");
}

void Opcodes::LD_ADDRESSOFBC_A(LR35902 &machine)
{
	// 8 cicli
	RAM.Write(machine.GetDoubleRegister("BC"), machine.GetRegister('A'));
}

void Opcodes::INC_BC(LR35902 &machine)
{
	// 8 cicli
	machine.UpdateRegister(machine.GetDoubleRegister("BC") + 1, "BC");
}



void Opcodes::INC_B(LR35902 &machine)
{
	// 4 cicli

	Byte result = machine.GetRegister('B') + 1;
	machine.UpdateRegister(result, "B");

	machine.UpdateFlag('N', false);
	if(result == 0)
		machine.UpdateFlag('Z', true);

	// Qualcuno implementi l'update del flag H dato che non so minimamente come fare :) @RehTrizZ
}

void Opcodes::DEC_B(LR35902 &machine)
{
	// 4 cicli

	Byte result = machine.GetRegister('B') - 1;
	machine.UpdateRegister(result, "B");

	machine.UpdateFlag('N', true);
	if(result == 0)
		machine.UpdateFlag('Z', true);

	// Qualcuno implementi l'update del flag H dato che non so minimamente come fare :) @RehTrizZ
}

void Opcodes::LD_B_BYTEDATA(LR35902 &machine, Byte data)
{
	machine.UpdateRegister(data, 'B');
}

void Opcodes::RLCA()
{
}

void Opcodes::LD_ADDRESSOFWORD_STACKPOINTER()
{
}

void Opcodes::ADD_HL_BC(LR35902 &machine)
{
	machine.UpdateRegister(machine.GetDoubleRegister("BC") + machine.GetDoubleRegister("BC"), 'HL');
}

void Opcodes::LD_A_ADDRESSOFBC(LR35902 &machine)
{

}

void Opcodes::DEC_BC(LR35902 &machine)
{
	machine.UpdateRegister(Word(machine.GetRegister('B') + machine.GetRegister('C') - 1), "BC");
}

void Opcodes::INC_C(LR35902 &machine)
{
	machine.UpdateRegister(Byte(machine.GetRegister('C') + 1), "B");
}

void Opcodes::DEC_C(LR35902 &machine)
{
	machine.UpdateRegister(Byte(machine.GetRegister('C') - 1), "B");
}

void Opcodes::LD_C_BYTEDATA(LR35902 &machine)
{
}

void Opcodes::RRCA()
{
}


		
