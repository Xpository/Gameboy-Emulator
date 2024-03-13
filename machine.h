#pragma once


namespace LR35902 {
	using Byte = unsigned char; // 8 bit
	using Word = unsigned short; // 16 bit

	Byte Memory[0x200000];
	/* 
		Registri sono:
			A,B,C,D,E,H,L General Purpose
			Flag, sostituiscono AL, parte bassa del primo registro AF
			SP, Stack Pointer
			PC, Program Counter
	*/

	Byte A = 0x00;


	Byte B = 0x00; //high
	Byte C = 0x00; //low

	Byte D = 0x00; //high
	Byte E = 0x00; //low

	Byte H = 0x00; //high
	Byte L = 0x00; //low

	Word SP = 0x0000; //stack pointer
	Word PC = 0x0000; //program counter

	/* 
		I Flag sono:
			Zero Flag (z) settato a zero se il risultato dell'operazione � zero.
			Carry Flag (c) usato in questi casi:
				- Quando il risultato di un'addizione a 8 bit � maggiore di $FF.
				- Quando il risultato di un'addizione a 16 bit � maggiore di $FFFF.
				- Quando il risultato di una sottrazione o di un confronto � inferiore a zero (come nei processori Z80 e x86, ma diversamente nei processori 65XX e ARM).
				- Quando un'operazione di rotate/shift sposta fuori un bit "1".

			BCD Flags (N, H):
				Queste flag sono utilizzate solo dall'istruzione DAA. N indica se l'istruzione precedente � stata una sottrazione, 
				mentre H indica il riporto per i 4 bit meno significativi del risultato. DAA utilizza anche il flag C, 
				che deve indicare il riporto per i 4 bit pi� significativi. Dopo aver aggiunto/sottratto due numeri BCD, 
				DAA viene utilizzata per convertire il risultato nel formato BCD. I numeri BCD vanno da $00 a $99 invece che da $00 a $FF. 
				Poiche' esistono solo due flag (C e H) per indicare i riporti dei cifre BCD, DAA � inefficace per operazioni a 16 bit 
				(che hanno 4 cifre) e l'uso per le operazioni INC/DEC (che non influiscono sul flag C) ha dei limiti.
	*/
	// Con la F per distinguerli dai registri general purpose
	Byte ZF = 0x00;
	Byte NF = 0x00;
	Byte HF = 0x00;
	Byte CF = 0x00;

	struct Opcodes;
};

struct LR35902::Opcodes {
	static constexpr Byte
		NOP = 0x00,
		LD_REGISTER_ADDRESS = 0x01, // LD BC, A
		LD_POINTEDREGISTER_REGISTER = 0x02; // LD [BC], A
		
};


