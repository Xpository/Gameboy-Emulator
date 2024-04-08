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


//deefinizioni istruzioni

instruction istruzioni[0x100]={
	[0x00] = {IN_NOP, AM_IMP}, // NOP
   	[0x01] = {IN_LD, AM_R_D16, RT_BC}, // LD BC,d16
	[0x02] = {IN_LD, AM_MR_R, RT_BC, RT_A}, // LD (BC),A
	[0x03] = {IN_INC, AM_R, RT_BC}, // INC BC
	[0x04] = {IN_INC, AM_R, RT_B}, // INC B
	[0x05] = {IN_DEC, AM_R, RT_B}, // DEC B
    	[0x06] = {IN_LD, AM_R_D8, RT_B}, // LD B,d8
	[0x07] = {IN_RLCA, AM_IMP}, // RLCA
    	[0x08] = {IN_LD, AM_A16_R, RT_SP}, // LD (a16),SP
 	[0x09] = {IN_ADD, AM_R, RT_HL, RT_BC}, // ADD HL,BC
	[0x0A] = {IN_LD, AM_R_MR, RT_A, RT_BC}, // LD A,(BC)
	[0x0B] = {IN_DEC, AM_R, RT_BC}, // DEC BC
	[0x0C] = {IN_INC, AM_R, RT_C}, // INC C
	[0x0D] = {IN_DEC, AM_R, RT_C}, // DEC C
	[0x0E] = {IN_LD, AM_R_D8, RT_C}, // LD C,d8
	[0x0F] = {IN_RRCA, AM_IMP}, // RRCA
	[0x10] = {IN_STOP, AM_D8}, // STOP 0
	[0x11] = {IN_LD, AM_R_D16, RT_DE}, // LD DE,d16
	[0x12] = {IN_LD, AM_MR_R, RT_DE, RT_A}, // LD (DE),A
	[0x13] = {IN_INC, AM_R, RT_DE}, // INC DE
	[0x14] = {IN_INC, AM_R, RT_D}, // INC D
	[0x15] = {IN_DEC, AM_R, RT_D}, // DEC D
	[0x16] = {IN_LD, AM_R_D8, RT_D}, // LD D,d8
	[0x17] = {IN_RLA, AM_IMP}, // RLA
	[0x18] = {IN_JR, AM_R8}, // JR r8
	[0x19] = {IN_ADD, AM_R, RT_HL, RT_DE}, // ADD HL,DE
	[0x1A] = {IN_LD, AM_R_MR, RT_A, RT_DE}, // LD A,(DE)
	[0x1B] = {IN_DEC, AM_R, RT_DE}, // DEC DE
	[0x1C] = {IN_INC, AM_R, RT_E}, // INC E
	[0x1D] = {IN_DEC, AM_R, RT_E}, // DEC E
	[0x1E] = {IN_LD, AM_R_D8, RT_E}, // LD E,d8
	[0x1F] = {IN_RRA, AM_IMP}, // RRA
	[0x20] = {IN_JR, AM_COND_R8, CT_NZ}, // JR NZ,r8
	[0x21] = {IN_LD, AM_R_D16, RT_HL}, // LD HL,d16
	[0x22] = {IN_LD, AM_MR_R, RT_HLI, RT_A}, // LD (HL+),A
	[0x23] = {IN_INC, AM_R, RT_HL}, // INC HL
	[0x24] = {IN_INC, AM_R, RT_H}, // INC H
	[0x25] = {IN_DEC, AM_R, RT_H}, // DEC H
	[0x26] = {IN_LD, AM_R_D8, RT_H}, // LD H,d8
	[0x27] = {IN_DAA, AM_IMP}, // DAA
	[0x28] = {IN_JR, AM_COND_R8, CT_Z}, // JR Z,r8
	[0x29] = {IN_ADD, AM_R, RT_HL, RT_HL}, // ADD HL,HL
	[0x2A] = {IN_LD, AM_MR_R, RT_A, RT_HLI}, // LD A,(HL+)
	[0x2B] = {IN_DEC, AM_R, RT_HL}, // DEC HL
	[0x2C] = {IN_INC, AM_R, RT_L}, // INC L
	[0x2D] = {IN_DEC, AM_R, RT_L}, // DEC L
	[0x2E] = {IN_LD, AM_R_D8, RT_L}, // LD L,d8
	[0x2F] = {IN_CPL, AM_IMP}, // CPL
	[0x30] = {IN_JR, AM_COND_R8, CT_NC}, // JR NC,r8
	[0x31] = {IN_LD, AM_R_D16, RT_SP}, // LD SP,d16
	[0x32] = {IN_LD, AM_MR_R, RT_HLD, RT_A}, // LD (HL-),A
	[0x33] = {IN_INC, AM_R, RT_SP}, // INC SP
	[0x34] = {IN_INC, AM_MR, RT_HL}, // INC (HL)
	[0x35] = {IN_DEC, AM_MR, RT_HL}, // DEC (HL)
	[0x36] = {IN_LD, AM_MR_D8, RT_HL}, // LD (HL),d8
	[0x37] = {IN_SCF, AM_IMP}, // SCF
	[0x38] = {IN_JR, AM_COND_R8, CT_C}, // JR C,r8
	[0x39] = {IN_ADD, AM_R, RT_HL, RT_SP}, // ADD HL,SP
	[0x3A] = {IN_LD, AM_MR_R, RT_A, RT_HLD}, // LD A,(HL-)
	[0x3B] = {IN_DEC, AM_R, RT_SP}, // DEC SP
	[0x3C] = {IN_INC, AM_R, RT_A}, // INC A
	[0x3D] = {IN_DEC, AM_R, RT_A}, // DEC A
	[0x3E] = {IN_LD, AM_R_D8, RT_A}, // LD A,d8
	[0x3F] = {IN_CCF, AM_IMP}, // CCF
	[0x40] = {IN_LD, AM_R_R, RT_B, RT_B}, // LD B,B
	[0x41] = {IN_LD, AM_R_R, RT_B, RT_C}, // LD B,C
	[0x42] = {IN_LD, AM_R_R, RT_B, RT_D}, // LD B,D
	[0x43] = {IN_LD, AM_R_R, RT_B, RT_E}, // LD B,E
	[0x44] = {IN_LD, AM_R_R, RT_B, RT_H}, // LD B,H
	[0x45] = {IN_LD, AM_R_R, RT_B, RT_L}, // LD B,L
	[0x46] = {IN_LD, AM_R_MR, RT_B, RT_HL}, // LD B,(HL)
	[0x47] = {IN_LD, AM_R_R, RT_B, RT_A}, // LD B,A
	[0x48] = {IN_LD, AM_R_R, RT_C, RT_B}, // LD C,B
	[0x49] = {IN_LD, AM_R_R, RT_C, RT_C}, // LD C,C
	[0x4A] = {IN_LD, AM_R_R, RT_C, RT_D}, // LD C,D
	[0x4B] = {IN_LD, AM_R_R, RT_C, RT_E}, // LD C,E
	[0x4C] = {IN_LD, AM_R_R, RT_C, RT_H}, // LD C,H
	[0x4D] = {IN_LD, AM_R_R, RT_C, RT_L}, // LD C,L
	[0x4E] = {IN_LD, AM_R_MR, RT_C, RT_HL}, // LD C,(HL)
	[0x4F] = {IN_LD, AM_R_R, RT_C, RT_A}, // LD C,A
	[0x50] = {IN_LD, AM_R_R, RT_D, RT_B}, // LD D,B
	[0x51] = {IN_LD, AM_R_R, RT_D, RT_C}, // LD D,C
	[0x52] = {IN_LD, AM_R_R, RT_D, RT_D}, // LD D,D
	[0x53] = {IN_LD, AM_R_R, RT_D, RT_E}, // LD D,E
	[0x54] = {IN_LD, AM_R_R, RT_D, RT_H}, // LD D,H
	[0x55] = {IN_LD, AM_R_R, RT_D, RT_L}, // LD D,L
	[0x56] = {IN_LD, AM_R_MR, RT_D, RT_HL}, // LD D,(HL)
	[0x57] = {IN_LD, AM_R_R, RT_D, RT_A}, // LD D,A
	[0x58] = {IN_LD, AM_R_R, RT_E, RT_B}, // LD E,B
	[0x59] = {IN_LD, AM_R_R, RT_E, RT_C}, // LD E,C
	[0x5A] = {IN_LD, AM_R_R, RT_E, RT_D}, // LD E,D
	[0x5B] = {IN_LD, AM_R_R, RT_E, RT_E}, // LD E,E
	[0x5C] = {IN_LD, AM_R_R, RT_E, RT_H}, // LD E,H
	[0x5D] = {IN_LD, AM_R_R, RT_E, RT_L}, // LD E,L
	[0x5E] = {IN_LD, AM_R_MR, RT_E, RT_HL}, // LD E,(HL)
	[0x5F] = {IN_LD, AM_R_R, RT_E, RT_A}, // LD E,A
	[0x60] = {IN_LD, AM_R_R, RT_H, RT_B}, // LD H,B
	[0x61] = {IN_LD, AM_R_R, RT_H, RT_C}, // LD H,C
	[0x62] = {IN_LD, AM_R_R, RT_H, RT_D}, // LD H,D
	[0x63] = {IN_LD, AM_R_R, RT_H, RT_E}, // LD H,E
	[0x64] = {IN_LD, AM_R_R, RT_H, RT_H}, // LD H,H
	[0x65] = {IN_LD, AM_R_R, RT_H, RT_L}, // LD H,L
	[0x66] = {IN_LD, AM_R_MR, RT_H, RT_HL}, // LD H,(HL)
	[0x67] = {IN_LD, AM_R_R, RT_H, RT_A}, // LD H,A
	[0x68] = {IN_LD, AM_R_R, RT_L, RT_B}, // LD L,B
	[0x69] = {IN_LD, AM_R_R, RT_L, RT_C}, // LD L,C
	[0x6A] = {IN_LD, AM_R_R, RT_L, RT_D}, // LD L,D
	[0x6B] = {IN_LD, AM_R_R, RT_L, RT_E}, // LD L,E
	[0x6C] = {IN_LD, AM_R_R, RT_L, RT_H}, // LD L,H
	[0x6D] = {IN_LD, AM_R_R, RT_L, RT_L}, // LD L,L
	[0x6E] = {IN_LD, AM_R_MR, RT_L, RT_HL}, // LD L,(HL)
	[0x6F] = {IN_LD, AM_R_R, RT_L, RT_A}, // LD L,A
	[0x70] = {IN_LD, AM_MR_R, RT_HL, RT_B}, // LD (HL),B
	[0x71] = {IN_LD, AM_MR_R, RT_HL, RT_C}, // LD (HL),C
	[0x72] = {IN_LD, AM_MR_R, RT_HL, RT_D}, // LD (HL),D
	[0x73] = {IN_LD, AM_MR_R, RT_HL, RT_E}, // LD (HL),E
	[0x74] = {IN_LD, AM_MR_R, RT_HL, RT_H}, // LD (HL),H
	[0x75] = {IN_LD, AM_MR_R, RT_HL, RT_L}, // LD (HL),L
	[0x76] = {IN_HALT, AM_IMP}, // HALT
	[0x77] = {IN_LD, AM_MR_R, RT_HL, RT_A}, // LD (HL),A
	[0x78] = {IN_LD, AM_R_R, RT_A, RT_B}, // LD A,B
	[0x79] = {IN_LD, AM_R_R, RT_A, RT_C}, // LD A,C
	[0x7A] = {IN_LD, AM_R_R, RT_A, RT_D}, // LD A,D
	[0x7B] = {IN_LD, AM_R_R, RT_A, RT_E}, // LD A,E
	[0x7C] = {IN_LD, AM_R_R, RT_A, RT_H}, // LD A,H
	[0x7D] = {IN_LD, AM_R_R, RT_A, RT_L}, // LD A,L
	[0x7E] = {IN_LD, AM_R_MR, RT_A, RT_HL}, // LD A,(HL)
	[0x7F] = {IN_LD, AM_R_R, RT_A, RT_A}, // LD A,A
	[0x80] = {IN_ADD, AM_R, RT_A, RT_B}, // ADD A,B
	[0x81] = {IN_ADD, AM_R, RT_A, RT_C}, // ADD A,C
	[0x82] = {IN_ADD, AM_R, RT_A, RT_D}, // ADD A,D
	[0x83] = {IN_ADD, AM_R, RT_A, RT_E}, // ADD A,E
	[0x84] = {IN_ADD, AM_R, RT_A, RT_H}, // ADD A,H
	[0x85] = {IN_ADD, AM_R, RT_A, RT_L}, // ADD A,L
	[0x86] = {IN_ADD, AM_R_MR, RT_A, RT_HL}, // ADD A,(HL)
	[0x87] = {IN_ADD, AM_R, RT_A, RT_A}, // ADD A,A
	[0x88] = {IN_ADC, AM_R, RT_A, RT_B}, // ADC A,B
	[0x89] = {IN_ADC, AM_R, RT_A, RT_C}, // ADC A,C
	[0x8A] = {IN_ADC, AM_R, RT_A, RT_D}, // ADC A,D
	[0x8B] = {IN_ADC, AM_R, RT_A, RT_E}, // ADC A,E
	[0x8C] = {IN_ADC, AM_R, RT_A, RT_H}, // ADC A,H
	[0x8D] = {IN_ADC, AM_R, RT_A, RT_L}, // ADC A,L
	[0x8E] = {IN_ADC, AM_R_MR, RT_A, RT_HL}, // ADC A,(HL)
	[0x8F] = {IN_ADC, AM_R, RT_A, RT_A}, // ADC A,A
	[0x90] = {IN_SUB, AM_R, RT_B}, // SUB B
	[0x91] = {IN_SUB, AM_R, RT_C}, // SUB C
	[0x92] = {IN_SUB, AM_R, RT_D}, // SUB D
	[0x93] = {IN_SUB, AM_R, RT_E}, // SUB E
	[0x94] = {IN_SUB, AM_R, RT_H}, // SUB H
	[0x95] = {IN_SUB, AM_R, RT_L}, // SUB L
	[0x96] = {IN_SUB, AM_MR, RT_HL}, // SUB (HL)
	[0x97] = {IN_SUB, AM_R, RT_A}, // SUB A
	[0x98] = {IN_SBC, AM_R, RT_A, RT_B}, // SBC A,B
	[0x99] = {IN_SBC, AM_R, RT_A, RT_C}, // SBC A,C
	[0x9A] = {IN_SBC, AM_R, RT_A, RT_D}, // SBC A,D
	[0x9B] = {IN_SBC, AM_R, RT_A, RT_E}, // SBC A,E
	[0x9C] = {IN_SBC, AM_R, RT_A, RT_H}, // SBC A,H
	[0x9D] = {IN_SBC, AM_R, RT_A, RT_L}, // SBC A,L
	[0x9E] = {IN_SBC, AM_MR, RT_A, RT_HL}, // SBC A,(HL)
	[0x9F] = {IN_SBC, AM_R, RT_A, RT_A}, // SBC A,A
	[0xA0] = {IN_AND, AM_R, RT_B}, // AND B
	[0xA1] = {IN_AND, AM_R, RT_C}, // AND C
	[0xA2] = {IN_AND, AM_R, RT_D}, // AND D
	[0xA3] = {IN_AND, AM_R, RT_H}, // AND H
	[0xA4] = {IN_AND, AM_R, RT_L}, // AND L
	[0xA5] = {IN_AND, AM_MR, RT_HL}, // AND (HL)
	[0xA6] = {IN_AND, AM_R, RT_A}, // AND A
	[0xA7] = {IN_AND, AM_R, RT_A}, // AND A
	[0xA8] = {IN_XOR, AM_R, RT_B}, // XOR B
	[0xA9] = {IN_XOR, AM_R, RT_C}, // XOR C
	[0xAA] = {IN_XOR, AM_R, RT_D}, // XOR D
	[0xAB] = {IN_XOR, AM_R, RT_E}, // XOR E
	[0xAC] = {IN_XOR, AM_R, RT_H}, // XOR H
	[0xAD] = {IN_XOR, AM_R, RT_L}, // XOR L
	[0xAE] = {IN_XOR, AM_MR, RT_HL}, // XOR (HL)
	[0xAF] = {IN_XOR, AM_R, RT_A}, // XOR A
	[0xB0] = {IN_OR, AM_R, RT_B}, // OR B
	[0xB1] = {IN_OR, AM_R, RT_C}, // OR C
	[0xB2] = {IN_OR, AM_R, RT_D}, // OR D
	[0xB3] = {IN_OR, AM_R, RT_E}, // OR E
	[0xB4] = {IN_OR, AM_R, RT_H}, // OR H
	[0xB5] = {IN_OR, AM_R, RT_L}, // OR L
	[0xB6] = {IN_OR, AM_MR, RT_HL}, // OR (HL)
	[0xB7] = {IN_OR, AM_R, RT_A}, // OR A
	[0xB8] = {IN_CP, AM_R, RT_B}, // CP B
	[0xB9] = {IN_CP, AM_R, RT_C}, // CP C
	[0xBA] = {IN_CP, AM_R, RT_D}, // CP D
	[0xBB] = {IN_CP, AM_R, RT_E}, // CP E
	[0xBC] = {IN_CP, AM_R, RT_H}, // CP H
	[0xBD] = {IN_CP, AM_R, RT_L}, // CP L
	[0xBE] = {IN_CP, AM_MR, RT_HL}, // CP (HL)
	[0xBF] = {IN_CP, AM_R, RT_A}, // CP A
	[0xC0] = {IN_RET, AM_COND, CT_NZ}, // RET NZ
	[0xC1] = {IN_POP, AM_RR, RT_BC}, // POP BC
	[0xC2] = {IN_JP, AM_COND_A16, CT_NZ}, // JP NZ,a16
	[0xC3] = {IN_JP, AM_A16}, // JP a16
	[0xC4] = {IN_CALL, AM_COND_A16, CT_NZ}, // CALL NZ,a16
	[0xC5] = {IN_PUSH, AM_RR, RT_BC}, // PUSH BC
	[0xC6] = {IN_ADD, AM_R_D8, RT_A}, // ADD A,d8
	[0xC7] = {IN_RST, AM_ADDR, 0x00}, // RST 00H
	[0xC8] = {IN_RET, AM_COND, CT_Z}, // RET Z
	[0xC9] = {IN_RET, AM_IMP}, // RET
	[0xCA] = {IN_JP, AM_COND_A16, CT_Z}, // JP Z,a16
	[0xCB] = {IN_CB, AM_CB}, // CB Prefix
	[0xCC] = {IN_CALL, AM_COND_A16, CT_Z}, // CALL Z,a16
	[0xCD] = {IN_CALL, AM_A16}, // CALL a16
	[0xCE] = {IN_ADC, AM_R_D8, RT_A}, // ADC A,d8
	[0xCF] = {IN_RST, AM_ADDR, 0x08}, // RST 08H
	[0xD0] = {IN_RET, AM_COND, CT_NC}, // RET NC
	[0xD1] = {IN_POP, AM_RR, RT_DE}, // POP DE
	[0xD2] = {IN_JP, AM_COND_A16, CT_NC}, // JP NC,a16
	[0xD4] = {IN_CALL, AM_COND_A16, CT_NC}, // CALL NC,a16
	[0xD5] = {IN_PUSH, AM_RR, RT_DE}, // PUSH DE
	[0xD6] = {IN_SUB, AM_R_D8, RT_A}, // SUB d8
	[0xD7] = {IN_RST, AM_ADDR, 0x10}, // RST 10H
	[0xD8] = {IN_RET, AM_COND, CT_C}, // RET C
	[0xD9] = {IN_RETI, AM_IMP}, // RETI
	[0xDA] = {IN_JP, AM_COND_A16, CT_C}, // JP C,a16
	[0xDC] = {IN_CALL, AM_COND_A16, CT_C}, // CALL C,a16
	[0xDE] = {IN_SBC, AM_R_D8, RT_A}, // SBC A,d8
	[0xDF] = {IN_RST, AM_ADDR, 0x18}, // RST 18H
	[0xE0] = {IN_LDH, AM_A8_R, RT_A}, // LDH (a8),A
	[0xE1] = {IN_POP, AM_RR, RT_HL}, // POP HL
	[0xE2] = {IN_LD, AM_MR_R, RT_C, RT_A}, // LD (C),A
	[0xE5] = {IN_PUSH, AM_RR, RT_HL}, // PUSH HL
	[0xE6] = {IN_AND, AM_R_D8}, // AND d8
	[0xE7] = {IN_RST, AM_ADDR, 0x20}, // RST 20H
	[0xE8] = {IN_ADD, AM_SP_R8}, // ADD SP,r8
	[0xE9] = {IN_JP, AM_HL}, // JP (HL)
	[0xEA] = {IN_LD, AM_A16_R, RT_A}, // LD (a16),A
	[0xEE] = {IN_XOR, AM_R_D8}, // XOR d8
	[0xEF] = {IN_RST, AM_ADDR, 0x28}, // RST 28H
	[0xF0] = {IN_LDH, AM_R_A8, RT_A}, // LDH A,(a8)
	[0xF1] = {IN_POP, AM_RR, RT_AF}, // POP AF
	[0xF2] = {IN_LD, AM_R_MR, RT_A, RT_C}, // LD A,(C)
	[0xF3] = {IN_DI, AM_IMP}, // DI
	[0xF5] = {IN_PUSH, AM_RR, RT_AF}, // PUSH AF
	[0xF6] = {IN_OR, AM_R_D8}, // OR d8
	[0xF7] = {IN_RST, AM_ADDR, 0x30}, // RST 30H
	[0xF8] = {IN_LD, AM_HL_SP_R8}, // LD HL,SP+r8
	[0xF9] = {IN_LD, AM_SP_HL}, // LD SP,HL
	[0xFA] = {IN_LD, AM_A16_R, RT_A}, // LD A,(a16)
	[0xFB] = {IN_EI, AM_IMP}, // EI
	[0xFE] = {IN_CP, AM_R_D8}, // CP d8
	[0xFF] = {IN_RST, AM_ADDR, 0x38}, // RST 38H
//DIVERTITEVI A FARLI

};


		
