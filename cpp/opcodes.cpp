#include "../headers/opcodes.hpp"


std::map<Byte, instruction> instructionsMap = {
    {0x00, {IN_NOP, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x01, {IN_LD, AM_R_D16, RT_BC, RT_NONE, CT_NONE, 0x00}},
    {0x02, {IN_LD, AM_MR_R, RT_BC, RT_A, CT_NONE, 0x00}},
    {0x03, {IN_INC, AM_R, RT_BC, RT_NONE, CT_NONE, 0x00}},
    {0x04, {IN_INC, AM_R, RT_B, RT_NONE, CT_NONE, 0x00}},
    {0x05, {IN_DEC, AM_R, RT_B, RT_NONE, CT_NONE, 0x00}},
    {0x06, {IN_LD, AM_R_D8, RT_B, RT_NONE, CT_NONE, 0x00}},
    {0x07, {IN_RLCA, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x08, {IN_LD, AM_A16_R, RT_SP, RT_NONE, CT_NONE, 0x00}},
    {0x09, {IN_ADD, AM_R_R, RT_HL, RT_BC, CT_NONE, 0x00}},
    {0x0A, {IN_LD, AM_R_MR, RT_A, RT_BC, CT_NONE, 0x00}},
    {0x0B, {IN_DEC, AM_R, RT_BC, RT_NONE, CT_NONE, 0x00}},
    {0x0C, {IN_INC, AM_R, RT_C, RT_NONE, CT_NONE, 0x00}},
    {0x0D, {IN_DEC, AM_R, RT_C, RT_NONE, CT_NONE, 0x00}},
    {0x0E, {IN_LD, AM_R_D8, RT_C, RT_NONE, CT_NONE, 0x00}},
    {0x0F, {IN_RRCA, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x10, {IN_STOP, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x11, {IN_LD, AM_R_D16, RT_DE, RT_NONE, CT_NONE, 0x00}},
    {0x12, {IN_LD, AM_MR_R, RT_DE, RT_A, CT_NONE, 0x00}},
    {0x13, {IN_INC, AM_R, RT_DE, RT_NONE, CT_NONE, 0x00}},
    {0x14, {IN_INC, AM_R, RT_D, RT_NONE, CT_NONE, 0x00}},
    {0x15, {IN_DEC, AM_R, RT_D, RT_NONE, CT_NONE, 0x00}},
    {0x16, {IN_LD, AM_R_D8, RT_D, RT_NONE, CT_NONE, 0x00}},
    {0x17, {IN_RLA, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x18, {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x19, {IN_ADD, AM_R_R, RT_HL, RT_DE, CT_NONE, 0x00}},
    {0x1A, {IN_LD, AM_R_MR, RT_A, RT_DE, CT_NONE, 0x00}},
    {0x1B, {IN_DEC, AM_R, RT_DE, RT_NONE, CT_NONE, 0x00}},
    {0x1C, {IN_INC, AM_R, RT_E, RT_NONE, CT_NONE, 0x00}},
    {0x1D, {IN_DEC, AM_R, RT_E, RT_NONE, CT_NONE, 0x00}},
    {0x1E, {IN_LD, AM_R_D8, RT_E, RT_NONE, CT_NONE, 0x00}},
    {0x1F, {IN_RRA, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x20, {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NZ, 0x00}},
    {0x21, {IN_LD, AM_R_D16, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x22, {IN_LD, AM_HLI_R, RT_HL, RT_A, CT_NONE, 0x00}},
    {0x23, {IN_INC, AM_R, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x24, {IN_INC, AM_R, RT_H, RT_NONE, CT_NONE, 0x00}},
    {0x25, {IN_DEC, AM_R, RT_H, RT_NONE, CT_NONE, 0x00}},
    {0x26, {IN_LD, AM_R_D8, RT_H, RT_NONE, CT_NONE, 0x00}},
    {0x27, {IN_DAA, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x28, {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_Z, 0x00}},
    {0x29, {IN_ADD, AM_R_R, RT_HL, RT_HL, CT_NONE, 0x00}},
    {0x2A, {IN_LD, AM_R_HLI, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x2B, {IN_DEC, AM_R, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x2C, {IN_INC, AM_R, RT_L, RT_NONE, CT_NONE, 0x00}},
    {0x2D, {IN_DEC, AM_R, RT_L, RT_NONE, CT_NONE, 0x00}},
    {0x2E, {IN_LD, AM_R_D8, RT_L, RT_NONE, CT_NONE, 0x00}},
    {0x2F, {IN_CPL, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x30, {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_NC, 0x00}},
    {0x31, {IN_LD, AM_R_D16, RT_SP, RT_NONE, CT_NONE, 0x00}},
    {0x32, {IN_LD, AM_HLD_R, RT_HL, RT_A, CT_NONE, 0x00}},
    {0x33, {IN_INC, AM_R, RT_SP, RT_NONE, CT_NONE, 0x00}},
    {0x34, {IN_INC, AM_MR, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x35, {IN_DEC, AM_MR, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x36, {IN_LD, AM_MR_D8, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0x37, {IN_SCF, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x38, {IN_JR, AM_D8, RT_NONE, RT_NONE, CT_C, 0x00}},
    {0x39, {IN_ADD, AM_R_R, RT_HL, RT_SP, CT_NONE, 0x00}},
    {0x3A, {IN_LD, AM_R_HLD, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x3B, {IN_DEC, AM_R, RT_SP, RT_NONE, CT_NONE, 0x00}},
    {0x3C, {IN_INC, AM_R, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0x3D, {IN_DEC, AM_R, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0x3E, {IN_LD, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0x3F, {IN_CCF, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x40, {IN_LD, AM_R_R, RT_B, RT_B, CT_NONE, 0x00}},
    {0x41, {IN_LD, AM_R_R, RT_B, RT_C, CT_NONE, 0x00}},
    {0x42, {IN_LD, AM_R_R, RT_B, RT_D, CT_NONE, 0x00}},
    {0x43, {IN_LD, AM_R_R, RT_B, RT_E, CT_NONE, 0x00}},
    {0x44, {IN_LD, AM_R_R, RT_B, RT_H, CT_NONE, 0x00}},
    {0x45, {IN_LD, AM_R_R, RT_B, RT_L, CT_NONE, 0x00}},
    {0x46, {IN_LD, AM_R_MR, RT_B, RT_HL, CT_NONE, 0x00}},
    {0x47, {IN_LD, AM_R_R, RT_B, RT_A, CT_NONE, 0x00}},
    {0x48, {IN_LD, AM_R_R, RT_C, RT_B, CT_NONE, 0x00}},
    {0x49, {IN_LD, AM_R_R, RT_C, RT_C, CT_NONE, 0x00}},
    {0x4A, {IN_LD, AM_R_R, RT_C, RT_D, CT_NONE, 0x00}},
    {0x4B, {IN_LD, AM_R_R, RT_C, RT_E, CT_NONE, 0x00}},
    {0x4C, {IN_LD, AM_R_R, RT_C, RT_H, CT_NONE, 0x00}},
    {0x4D, {IN_LD, AM_R_R, RT_C, RT_L, CT_NONE, 0x00}},
    {0x4E, {IN_LD, AM_R_MR, RT_C, RT_HL, CT_NONE, 0x00}},
    {0x4F, {IN_LD, AM_R_R, RT_C, RT_A, CT_NONE, 0x00}},
    {0x50, {IN_LD, AM_R_R, RT_D, RT_B, CT_NONE, 0x00}},
    {0x51, {IN_LD, AM_R_R, RT_D, RT_C, CT_NONE, 0x00}},
    {0x52, {IN_LD, AM_R_R, RT_D, RT_D, CT_NONE, 0x00}},
    {0x53, {IN_LD, AM_R_R, RT_D, RT_E, CT_NONE, 0x00}},
    {0x54, {IN_LD, AM_R_R, RT_D, RT_H, CT_NONE, 0x00}},
    {0x55, {IN_LD, AM_R_R, RT_D, RT_L, CT_NONE, 0x00}},
    {0x56, {IN_LD, AM_R_MR, RT_D, RT_HL, CT_NONE, 0x00}},
    {0x57, {IN_LD, AM_R_R, RT_D, RT_A, CT_NONE, 0x00}},
    {0x58, {IN_LD, AM_R_R, RT_E, RT_B, CT_NONE, 0x00}},
    {0x59, {IN_LD, AM_R_R, RT_E, RT_C, CT_NONE, 0x00}},
    {0x5A, {IN_LD, AM_R_R, RT_E, RT_D, CT_NONE, 0x00}},
    {0x5B, {IN_LD, AM_R_R, RT_E, RT_E, CT_NONE, 0x00}},
    {0x5C, {IN_LD, AM_R_R, RT_E, RT_H, CT_NONE, 0x00}},
    {0x5D, {IN_LD, AM_R_R, RT_E, RT_L, CT_NONE, 0x00}},
    {0x5E, {IN_LD, AM_R_MR, RT_E, RT_HL, CT_NONE, 0x00}},
    {0x5F, {IN_LD, AM_R_R, RT_E, RT_A, CT_NONE, 0x00}},
    {0x60, {IN_LD, AM_R_R, RT_H, RT_B, CT_NONE, 0x00}},
    {0x61, {IN_LD, AM_R_R, RT_H, RT_C, CT_NONE, 0x00}},
    {0x62, {IN_LD, AM_R_R, RT_H, RT_D, CT_NONE, 0x00}},
    {0x63, {IN_LD, AM_R_R, RT_H, RT_E, CT_NONE, 0x00}},
    {0x64, {IN_LD, AM_R_R, RT_H, RT_H, CT_NONE, 0x00}},
    {0x65, {IN_LD, AM_R_R, RT_H, RT_L, CT_NONE, 0x00}},
    {0x66, {IN_LD, AM_R_MR, RT_H, RT_HL, CT_NONE, 0x00}},
    {0x67, {IN_LD, AM_R_R, RT_H, RT_A, CT_NONE, 0x00}},
    {0x68, {IN_LD, AM_R_R, RT_L, RT_B, CT_NONE, 0x00}},
    {0x69, {IN_LD, AM_R_R, RT_L, RT_C, CT_NONE, 0x00}},
    {0x6A, {IN_LD, AM_R_R, RT_L, RT_D, CT_NONE, 0x00}},
    {0x6B, {IN_LD, AM_R_R, RT_L, RT_E, CT_NONE, 0x00}},
    {0x6C, {IN_LD, AM_R_R, RT_L, RT_H, CT_NONE, 0x00}},
    {0x6D, {IN_LD, AM_R_R, RT_L, RT_L, CT_NONE, 0x00}},
    {0x6E, {IN_LD, AM_R_MR, RT_L, RT_HL, CT_NONE, 0x00}},
    {0x6F, {IN_LD, AM_R_R, RT_L, RT_A, CT_NONE, 0x00}},
    {0x70, {IN_LD, AM_MR_R, RT_HL, RT_B, CT_NONE, 0x00}},
    {0x71, {IN_LD, AM_MR_R, RT_HL, RT_C, CT_NONE, 0x00}},
    {0x72, {IN_LD, AM_MR_R, RT_HL, RT_D, CT_NONE, 0x00}},
    {0x73, {IN_LD, AM_MR_R, RT_HL, RT_E, CT_NONE, 0x00}},
    {0x74, {IN_LD, AM_MR_R, RT_HL, RT_H, CT_NONE, 0x00}},
    {0x75, {IN_LD, AM_MR_R, RT_HL, RT_L, CT_NONE, 0x00}},
    {0x76, {IN_HALT, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0x77, {IN_LD, AM_MR_R, RT_HL, RT_A, CT_NONE, 0x00}},
    {0x78, {IN_LD, AM_R_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0x79, {IN_LD, AM_R_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0x7A, {IN_LD, AM_R_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0x7B, {IN_LD, AM_R_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0x7C, {IN_LD, AM_R_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0x7D, {IN_LD, AM_R_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0x7E, {IN_LD, AM_R_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x7F, {IN_LD, AM_R_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0x80, {IN_ADD, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0x81, {IN_ADD, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0x82, {IN_ADD, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0x83, {IN_ADD, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0x84, {IN_ADD, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0x85, {IN_ADD, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0x86, {IN_ADD, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x87, {IN_ADD, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0x88, {IN_ADC, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0x89, {IN_ADC, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0x8A, {IN_ADC, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0x8B, {IN_ADC, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0x8C, {IN_ADC, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0x8D, {IN_ADC, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0x8E, {IN_ADC, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x8F, {IN_ADC, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0x90, {IN_SUB, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0x91, {IN_SUB, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0x92, {IN_SUB, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0x93, {IN_SUB, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0x94, {IN_SUB, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0x95, {IN_SUB, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0x96, {IN_SUB, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x97, {IN_SUB, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0x98, {IN_SBC, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0x99, {IN_SBC, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0x9A, {IN_SBC, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0x9B, {IN_SBC, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0x9C, {IN_SBC, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0x9D, {IN_SBC, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0x9E, {IN_SBC, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0x9F, {IN_SBC, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0xA0, {IN_AND, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0xA1, {IN_AND, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0xA2, {IN_AND, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0xA3, {IN_AND, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0xA4, {IN_AND, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0xA5, {IN_AND, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0xA6, {IN_AND, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0xA7, {IN_AND, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0xA8, {IN_XOR, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0xA9, {IN_XOR, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0xAA, {IN_XOR, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0xAB, {IN_XOR, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0xAC, {IN_XOR, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0xAD, {IN_XOR, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0xAE, {IN_XOR, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0xAF, {IN_XOR, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0xB0, {IN_OR, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0xB1, {IN_OR, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0xB2, {IN_OR, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0xB3, {IN_OR, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0xB4, {IN_OR, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0xB5, {IN_OR, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0xB6, {IN_OR, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0xB7, {IN_OR, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0xB8, {IN_CP, AM_R, RT_A, RT_B, CT_NONE, 0x00}},
    {0xB9, {IN_CP, AM_R, RT_A, RT_C, CT_NONE, 0x00}},
    {0xBA, {IN_CP, AM_R, RT_A, RT_D, CT_NONE, 0x00}},
    {0xBB, {IN_CP, AM_R, RT_A, RT_E, CT_NONE, 0x00}},
    {0xBC, {IN_CP, AM_R, RT_A, RT_H, CT_NONE, 0x00}},
    {0xBD, {IN_CP, AM_R, RT_A, RT_L, CT_NONE, 0x00}},
    {0xBE, {IN_CP, AM_MR, RT_A, RT_HL, CT_NONE, 0x00}},
    {0xBF, {IN_CP, AM_R, RT_A, RT_A, CT_NONE, 0x00}},
    {0xC0, {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NZ, 0x00}},	
    {0xC1, {IN_POP, AM_R, RT_BC, RT_NONE, CT_NONE, 0x00}},				
    {0xC2, {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NZ, 0x00}},
    {0xC3, {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xC4, {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NZ, 0x00}},
    {0xC5, {IN_PUSH, AM_R, RT_BC, RT_NONE, CT_NONE, 0x00}},
    {0xC6, {IN_ADD, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xC7, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xC8, {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_Z, 0x00}},
    {0xC9, {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xCA, {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_Z, 0x00}},
    {0xCB, {IN_CB, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xCC, {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_Z, 0x00}},
    {0xCD, {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xCE, {IN_ADC, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xCF, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xD0, {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_NC, 0x00}},
    {0xD1, {IN_POP, AM_R, RT_DE, RT_NONE, CT_NONE, 0x00}},
    {0xD2, {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_NC, 0x00}},
	//	{0xD3} Non esiste
    {0xD4, {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_NC, 0x00}},
    {0xD5, {IN_PUSH, AM_R, RT_DE, RT_NONE, CT_NONE, 0x00}},
    {0xD6, {IN_SUB, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xD7, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xD8, {IN_RET, AM_IMP, RT_NONE, RT_NONE, CT_C, 0x00}},
    {0xD9, {IN_RETI, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xDA, {IN_JP, AM_D16, RT_NONE, RT_NONE, CT_C, 0x00}},
    {0xDC, {IN_CALL, AM_D16, RT_NONE, RT_NONE, CT_C, 0x00}},
    {0xDE, {IN_SBC, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xDF, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xE0, {IN_LD, AM_A8_R, RT_NONE, RT_A, CT_NONE, 0x00}},
    {0xE1, {IN_POP, AM_R, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0xE2, {IN_LD, AM_MR_R, RT_C, RT_A, CT_NONE, 0x00}},
    {0xE5, {IN_PUSH, AM_R, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0xE6, {IN_AND, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xE7, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xE8, {IN_ADD, AM_R_D8, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xE9, {IN_JP, AM_R, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xEA, {IN_LD, AM_A16_R, RT_NONE, RT_A, CT_NONE, 0x00}},
    {0xEE, {IN_XOR, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xEF, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xF0, {IN_LD, AM_R_A8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xF1, {IN_POP, AM_R, RT_AF, RT_NONE, CT_NONE, 0x00}},
    {0xF2, {IN_LD, AM_R_MR, RT_A, RT_C, CT_NONE, 0x00}},
    {0xF3, {IN_DI, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xF5, {IN_PUSH, AM_R, RT_AF, RT_NONE, CT_NONE, 0x00}},
    {0xF6, {IN_OR, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xF7, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xF8, {IN_LD, AM_HL_SPR, RT_HL, RT_NONE, CT_NONE, 0x00}},
    {0xF9, {IN_LD, AM_R_R, RT_SP, RT_HL, CT_NONE, 0x00}},
    {0xFA, {IN_LD, AM_R_A16, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xFB, {IN_EI, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xFE, {IN_CP, AM_R_D8, RT_A, RT_NONE, CT_NONE, 0x00}},
    {0xFF, {IN_RST, AM_IMP, RT_NONE, RT_NONE, CT_NONE, 0x00}},
};

instruction* instruction_by_opcode( Byte opcode){
   // if(istruzioni[opcode].type==IN_NOP)  --> if di test
   //    return NULL;

    return &instructionsMap[opcode];
}

std::string GetRegisterByName(registri input)
{
    switch (input)
    {
    case RT_A:
        return "A";
        break;
    case RT_F:
        return "F";
        break;
    case RT_B:
        return "B";
        break;
    case RT_C:
        return "C";
        break;
    case RT_D:
        return "D";
        break;
    case RT_E:
        return "E";
        break;
    case RT_H:
        return "H";
        break;
    case RT_L:
        return "L";
        break;
    case RT_AF:
        return "AF";
        break;
    case RT_BC:
        return "BC";
        break;
    case RT_DE:
        return "DE";
        break;
    case RT_HL:
        return "HL";
        break;   
    case RT_SP:
        return "SP";
        break;    
    case RT_PC:
        return "PC";
        break;   
    
    }

    return "";
}

