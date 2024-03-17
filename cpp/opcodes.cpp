#include "../headers/types.h"
#include "../headers/opcodes.h"
#include "../headers/LR35902.h"

using namespace nstdtypes;

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

void Opcodes::NOP()
{
	return;
}

void Opcodes::LD_BC_WORDDATA(LR35902 &machine, Word data)
{
	machine.UpdateRegister(data, "BC");
}

void Opcodes::LD_ADDRESSOFBC_A(LR35902 &machine)
{
	Byte A = machine.GetRegister('A');
	Word BC = machine.GetRegister('B') + machine.GetRegister('C');

	// Finire implementazione quando la memoria sara' finita.
}

void Opcodes::INC_BC(LR35902 &machine)
{
	machine.UpdateRegister(Word(machine.GetRegister('B') + machine.GetRegister('C') + 1), "BC");
}



void Opcodes::INC_B(LR35902 &machine)
{
	machine.UpdateRegister(Byte(machine.GetRegister('B') + 1), "B");
}

void Opcodes::DEC_B(LR35902 &machine)
{
	machine.UpdateRegister(Byte(machine.GetRegister('B') - 1), "B");

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

void Opcodes::ADD_HL_BC()
{
}

void Opcodes::LD_A_FF00BC()
{
}

void Opcodes::DEC_BC()
{
}

void Opcodes::INC_C()
{
}

void Opcodes::DEC_C()
{
}

void Opcodes::LD_C_BYTEDATA()
{
}

void Opcodes::RRCA()
{
}


		
