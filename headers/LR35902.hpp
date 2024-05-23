#include "types.hpp"
#include "cartridge.hpp"
#include "opcodes.hpp"
#include "memory.hpp"
#include <string>

// casotti stai lavorando, bravo russazzo <3 





///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class LR35902 {
	private:
		/*
			Registri sono:
				A,B,C,D,E,H,L General Purpose
				Flag, sostituiscono AL, parte bassa del primo registro AF
				SP, Stack Pointer
				PC, Program Counter
		*/
		struct CPU_Registers{
			Byte A; // high

			Byte B; // high
			Byte C; // low

			Byte D; // high
			Byte E; // low

			Byte H; // high
			Byte L; // low

			Word SP; // Stack pointer
			Word PC; // Program counter
		};
		/*
			I Flag sono:
				Zero Flag (z) settato a zero se il risultato dell'operazione e' zero.
				Carry Flag (c) usato in questi casi:
					- Quando il risultato di un'addizione a 8 bit e' maggiore di $FF.
					- Quando il risultato di un'addizione a 16 bit e' maggiore di $FFFF.
					- Quando il risultato di una sottrazione o di un confronto e' inferiore a zero (come nei processori Z80 e x86, ma diversamente nei processori 65XX e ARM).
					- Quando un'operazione di rotate/shift sposta fuori un bit "1".

				BCD Flag (N, H):
					Queste flag sono utilizzate solo dall'istruzione DAA. N indica se l'istruzione precedente e' stata una sottrazione,
					mentre H indica il riporto per i 4 bit meno significativi del risultato. DAA utilizza anche il flag C,
					che deve indicare il riporto per i 4 bit pie' significativi. Dopo aver aggiunto/sottratto due numeri BCD,
					DAA viene utilizzata per convertire il risultato nel formato BCD. I numeri BCD vanno da $00 a $99 invece che da $00 a $FF.
					Poiche' esistono solo due flag (C e H) per indicare i riporti dei cifre BCD, DAA e' inefficace per operazioni a 16 bit
					(che hanno 4 cifre) e l'uso per le operazioni INC/DEC (che non influiscono sul flag C) ha dei limiti.
		*/
		struct Flags{
			bool ZF;
			bool CF;

			bool NF;
			bool HF;
		};

		

		struct CPU_Registers reg;
		struct Flags fl;
		
		Cartridge* cart = nullptr;
		Memory* mem = nullptr;

		Byte ExtractUpper(Word);
		Byte ExtractLower(Word);
		
	public:
		LR35902(std::string);


		void UpdateRegister(Byte, char); // si updateta una parte del registro (basso o alto)
		void UpdateRegister(Word, std::string); // si updateta l'intero registro (sia basso che alto)
		void UpdateFlag(char, bool);
		
		Byte GetRegister(char);
        Word GetDoubleRegister(std::string rx);

		
		bool GetFlag(char);

		struct CPU_Context{
			CPU_Registers registers;

			//fetching
			Word fetchedData;
			Word memoryDestination;
			bool memoryDestination_is_mem;
			Byte currentOpcode;
			instruction *currentInstruction;

			//condizioni di utilizzo degli interrupt
			Word IE;			//interrupt enable (abilitazione dei tipi specifici di interrupt)
			Word IF;	//interrupt flag (interrupt in sospeso)
			Byte IME;		//interrupt master enable (abilitazione generica)

			bool halt;
			bool stepping;
		};

		CPU_Context thisContext={0};

		bool CPU_Step();
		void fetch_ins();
		void fetch_data();
		void execute();
};

