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

instructions istruzioni[0x100]={
	[0x00]={IN_NOP, AM_IMP},
	[0X05]={IN_DEC, AM_R,RT_B},
	[0X0E]={IN_LD, AM_R_D8,RT_C},
	[0xAF]={IN_XOR, AM_R, RT_A},
	[0xC3]={IN_JP, AM_D16}
//DIVERTITEVI A FARLI

};


		
