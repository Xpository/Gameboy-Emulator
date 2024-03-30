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
		void RRCA();							// Stessa cosa del 0x07 ma a destra
		
		//necessita definizione

		void STOP();
		void LD_DE_WORDDATA(LR35902&, Word);
		void LD_ADDRESSOFDE_A(LR35902&);
		void INC_DE(LR35902&);
		void INC_D(LR35902&);
		void DEC_D(LR35902&);
		void LD_D_BYTEDATA(LR35902&, Byte);
		void RLA();
		void JR_BYTEDATA(LR35902&, Byte);				// assegna a PC il Byte
		void ADD_HL_DE(LR35902&);
		void LD_A_ADDRESSOFDE(LR35902&);
		void DEC_DE(LR35902&);
		void INC_E(LR35902&);
		void DEC_E(LR35902&);
		void LD_E_BYTEDATA(LR35902&, Byte);
		void RRA(LR35902&);
		void JR_NZ_BYTEDATA(LR35902&, Byte);
		void LD_HL_WORDDATA(LR35902&, Word);
		void LD_ADDRESSOFH_A_INC_H(LR35902&);
		void INC_HL(LR35902&);
		void INC_H(LR35902&);
		void DEC_H(LR35902&);
		void LD_H_BYTEDATA(LR35902&, Byte);
		void DAA(LR35902&);
		void JR_Z_BYTEDATA(LR35902&, Byte);
		void ADD_HL_HL(LR35902&);
		void LD_A_ADDRESSOFHL_INC_HL(LR35902&);
		void DEC_HL(LR35902&);
		void INC_L(LR35902&);
		void DEC_L(LR35902&);
		void LD_L_BYTEDATA(LR35902&);
		void CPL(LR35902&);				//complement, esegue il not logico sui bit del registro A
		void JR_NC_BYTEDATA(LR35902&, Byte);
		void LD_SP_WORDDATA(LR35902&, Word);
		void LD_ADDRESSOFHL_A_DEC_HL(LR35902&);
		void INC_SP(LR35902&);
		void INC_ADDRESSOFHL(LR35902&);
		void DEC_ADDRESSOFHL(LR35902&);
		void LD_ADDRESSOFHL_BYTEDATA(LR35902&, Byte);
		void SCF(LR35902&); 		//DA CONTROLLARE
		void JR_C_BYTEDATA(LR35902&, Byte);
		void ADD_HL_SP(LR35902&);
		void LD_A_ADDRESSOFHL_DEC_HL(LR35902&);
		void DEC_SP(LR35902&);
		void INC_A(LR35902&);
		void DEC_A(LR35902&);
		void LD_A_BYTEDATA(LR35902&, Byte);
		void CCF(LR35902&); 		//DA CONTROLLARE
		void LD_B_B(LR35902&);
		void LD_B_C(LR35902&);
		void LD_B_D(LR35902&);
		void LD_B_E(LR35902&);
		void LD_B_H(LR35902&);
		void LD_B_L(LR35902&);
		void LD_B_ADDRESSOFHL(LR35902&);
		void LD_B_A(LR35902&);
		void LD_C_B(LR35902&);
		void LD_C_C(LR35902&);
		void LD_C_D(LR35902&);
		void LD_C_E(LR35902&);
		void LD_C_H(LR35902&);
		void LD_C_L(LR35902&);
		void LD_C_ADDRESSOFHL(LR35902&);
		void LD_C_A(LR35902&);
		void LD_D_B(LR35902&);
		void LD_D_C(LR35902&);
		void LD_D_D(LR35902&);
		void LD_D_E(LR35902&);
		void LD_D_H(LR35902&);
		void LD_D_L(LR35902&);
		void LD_D_ADDRESSOFHL(LR35902&);
		void LD_D_A(LR35902&);
		void LD_E_B(LR35902&);
		void LD_E_C(LR35902&);
		void LD_E_D(LR35902&);
		void LD_E_E(LR35902&);
		void LD_E_H(LR35902&);
		void LD_E_L(LR35902&);
		void LD_E_ADDRESSOFHL(LR35902&);
		void LD_E_A(LR35902&);
		void LD_H_B(LR35902&);
		void LD_H_C(LR35902&);
		void LD_H_D(LR35902&);
		void LD_H_E(LR35902&);
		void LD_H_H(LR35902&);
		void LD_H_L(LR35902&);
		void LD_H_ADDRESSOFHL(LR35902&);
		void LD_H_A(LR35902&);
		void LD_L_B(LR35902&);
		void LD_L_C(LR35902&);
		void LD_L_D(LR35902&);
		void LD_L_E(LR35902&);
		void LD_L_H(LR35902&);
		void LD_L_L(LR35902&);
		void LD_L_ADDRESSOFHL(LR35902&);
		void LD_L_A(LR35902&);
		void LD_ADDRESSOFHL_B(LR35902&);
		void LD_ADDRESSOFHL_C(LR35902&);
		void LD_ADDRESSOFHL_D(LR35902&);
		void LD_ADDRESSOFHL_E(LR35902&);
		void LD_ADDRESSOFHL_H(LR35902&);
		void LD_ADDRESSOFHL_L(LR35902&);
		void HALT(LR35902&); 		//DA CONTROLLARE
		void LD_ADDRESSOFHL_A(LR35902&);
		void LD_A_B(LR35902&);
		void LD_A_C(LR35902&);
		void LD_A_D(LR35902&);
		void LD_A_E(LR35902&);
		void LD_A_H(LR35902&);
		void LD_A_L(LR35902&);
		void LD_A_ADDRESSOFHL(LR35902&);
		void LD_A_A(LR35902&);
		void ADD_A_B(LR35902&);
		void ADD_A_C(LR35902&);
		void ADD_A_D(LR35902&);
		void ADD_A_E(LR35902&);
		void ADD_A_H(LR35902&);
		void ADD_A_L(LR35902&);
		void ADD_A_ADDRESSOFHL(LR35902&);
		void ADD_A_A(LR35902&);
		void ADC_A_B(LR35902&);
		void ADC_A_C(LR35902&);
		void ADC_A_D(LR35902&);
		void ADC_A_E(LR35902&);
		void ADC_A_H(LR35902&);
		void ADC_A_L(LR35902&);
		void ADC_A_ADDRESSOFHL(LR35902&);
		void ADC_A_A(LR35902&);
		void SUB_B(LR35902&);
		void SUB_C(LR35902&);
		void SUB_D(LR35902&);
		void SUB_E(LR35902&);
		void SUB_H(LR35902&);
		void SUB_L(LR35902&);
		void SUB_ADDRESSOFHL(LR35902&);
		void SUB_A(LR35902&);
		void SBC_A_B(LR35902&);
		void SBC_A_C(LR35902&);
		void SBC_A_D(LR35902&);
		void SBC_A_E(LR35902&);
		void SBC_A_H(LR35902&);
		void SBC_A_L(LR35902&);
		void SBC_A_ADDRESSOFHL(LR35902&);
		void SBC_A_A(LR35902&);
		void AND_B(LR35902&);
		void AND_C(LR35902&);
		void AND_D(LR35902&);
		void AND_E(LR35902&);
		void AND_H(LR35902&);
		void AND_L(LR35902&);
		void AND_ADDRESSOFHL(LR35902&);
		void AND_A(LR35902&);
		void XOR_B(LR35902&);
		void XOR_C(LR35902&);
		void XOR_D(LR35902&);
		void XOR_E(LR35902&);
		void XOR_H(LR35902&);
		void XOR_L(LR35902&);
		void XOR_ADDRESSOFHL(LR35902&);
		void XOR_A(LR35902&);
		void OR_B(LR35902&);
		void OR_C(LR35902&);
		void OR_D(LR35902&);
		void OR_E(LR35902&);
		void OR_H(LR35902&);
		void OR_L(LR35902&);
		void OR_ADDRESSOFHL(LR35902&);
		void OR_A(LR35902&);
		void CP_B(LR35902&);
		void CP_C(LR35902&);
		void CP_D(LR35902&);
		void CP_E(LR35902&);
		void CP_H(LR35902&);
		void CP_L(LR35902&);
		void CP_ADDRESSOFHL(LR35902&);
		void CP_A(LR35902&);
		void RET_NZ(LR35902&);
		void POP_BC(LR35902&);
		void JP_NZ_WORDADDRES(LR35902&, Word);
		void JP_WORDADDRES(LR35902&, Word);
		void CALL_NZ_WOARDADDRES(LR35902&);
		void PUSH_BC(LR35902&);
		void ADD_A(LR35902&,Byte);
		void RST_00H(LR35902&,Byte);
		void RET_Z(LR35902&);
		void RET(LR35902&);
		void JP_Z(LR35902&,Word);
		void PREFIX_CB(LR35902&); //da controllare//
		void CALL_Z(LR35902&, Word);
		void CALL(LR35902&, Word);
		void ADC_A(LR35902&); //This opcode group adds the contents of the specified byte-valued input and the register F carry flag (Flag computed as a 1 or a 0) to the contents of register A, to be stored in register A. The formula can be seen as A=A+r+CY. //
		void RST_08H(LR35902&,Byte);
		void RET_NC(LR35902&);
		void POP_DE(LR35902&);
		void JP_NC(LR35902&, Word);
		void CALL_NC(LR35902&, Word);
		void PUSH_DE(LR35902&);
		void SUB(LR35902&,Byte);
		void RST_10H(LR35902&);
		void RET_C(LR35902&);
		void RETI(LR35902&);
		void JP_C(LR35902&, Word);
		void CALL_C(LR35902&,Word);
		void SBC_A(LR35902&,Byte);
		void RST_18H(LR35902&);
		void LDH_byte_A(LR35902&,Byte); //Put A into memory address $FF00+n//
		void POP_HL(LR35902&);
		void LD_C_A(LR35902&);
		void PUSH_HL(LR35902&);
		void AND(LR35902&,Byte);
		void RST_20H(LR35902&);
		void ADD_SP_R8(LR35902&,Byte);
		void JP_HL(LR35902&);
		void LD_WORD_A(LR35902&,Word);
		void XOR(LR35902&,Byte);
		void RST_28H(LR35902&);
		void LDH_A_BYTE(LR35902&);
		void POP_AF(LR35902&);
		void LD_A_C(LR35902&);
		void DI(LR35902&);
		void PUSH_AF(LR35902&);
		void OR(LR35902&,Byte);
		void RST_30H(LR35902&);
		void LD_HL_SP_Byte(LR35902&,Byte);
		void LD_SP_HL(LR35902&);
		void LD_A_WORD(LR35902&,Word);
		void EI(LR35902&);
		void CP(LR35902&,Byte);
		void RST_38H(LR35902&);
};




												
