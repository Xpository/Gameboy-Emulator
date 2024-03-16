#include "types.h"
#include "opcodes.h"
#include "machine.cpp"

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


		
