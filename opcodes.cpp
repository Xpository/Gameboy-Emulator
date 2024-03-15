#include "types.h"
#include "opcodes.h"
#include "machine.cpp"

using namespace nstdtypes;

// Creare un overload di questa funzione perche e' obrobriosa
void Opcodes::ExecuteOpcodes(LR35902 machine, Byte opcode, Byte operand1 = 0x00, Byte operand2 = 0x00, Word wordop1 = 0x0000, Word wordop2 = 0x0000) {
	switch (opcode)
	{
	case 0x00:
		NOP();
		break;
	case 0x01:
		LD_BC_WORDDATA(machine);
		break;
	case 0x02:
		LD_FF00BC_A();
		break;
	}
}



void Opcodes::NOP()
{
	return;
}

void Opcodes::LD_BC_WORDDATA(LR35902 &machine, Word data)
{
	machine.UpdateRegister(data, 'B', 'C');
}

void Opcodes::LD_FF00BC_A()
{
}

void Opcodes::INC_BC()
{
}

void Opcodes::INC_B()
{
}

void Opcodes::DEC_B()
{
}

void Opcodes::LD_B_BYTEDATA()
{
}

void Opcodes::RLCA()
{
}

void Opcodes::LD_FF00WORDADDRESS_STACKPOINTER()
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


		
