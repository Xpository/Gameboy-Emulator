#include "types.hpp"
#include "cartridge.hpp"
#include "opcodes.hpp"
#include "memory.hpp"
#include <string>

// casotti stai lavorando, bravo russazzo <3 


class LR35902 {
	private:
		/*
			Registri principali sono:
				A,B,C,D,E,H,L General Purpose
				Flag, sostituiscono AL, parte bassa del primo registro AF
				SP, Stack Pointer
				PC, Program Counter
		*/
		struct CPU_Registers{
			Byte A; // high
			// Il low di A sarebbero i flag

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

		

		struct Flags fl;
		
		/* ExtractUpper() estrae la parte superiore di una Word
		*  @param Word word da cui estrarre il valore
		*  @return Il valore della parte superiore della word
		*/ 
		Byte ExtractUpper(Word);
		
		/* ExtractUpper() estrae la parte inferiore di una word
		*  @param Word word da cui estrarre il valore
		*  @return Il valore della parte inferiore della word
		*/ 
		Byte ExtractLower(Word);
		
		Cartridge* cart = nullptr;
		Memory* mem = nullptr;
	public:

		/* Costruttore della classe con 2 argomenti, inizializza il tutto
		* @param Stringa Il percorso alla ROM da avviare
		* @param Memory L'istanza di memory che si utilizza nel main
		*/
		LR35902(std::string, Memory&);

		/* UpdateRegister() modifica il valore di un registro
		*  @param Data enum registri da inserire
		*  @param Registro il registro in maiuscolo
		*/ 
		void UpdateRegister(registri, Word); // si updateta una parte del registro (basso o alto)
		
		/* UpdateFlag() modifica il valore di una flag
		*  @param Flag da modificare
		*  @param Stato stato in cui modificarlo, inizialmente true
		*/ 
		void UpdateFlag(char, bool);
		
		/* GetRegister() ritorna il valore di un dato registro
		*  @param Registro registro da cui prendere il dato
		*  @return Valore del registro
		*/ 
		Word GetRegister(registri);

		/* GetDoubleRegister() ritorna una word con i registri RX
		* @param RX una stringa composta da 2 caratteri che simboleggiano il registro
		* @return La Word che creata da parte alta + parte bassa del registro
		* @attention Non ci sono controlli sulla lunghezza della stringa,
		* quindi potrebbe ritornare 0x0000, cioe' indefinito o not-found 
		* @deprecated Andrebbe modificata e resa un enum dato che la string è inefficiente
		*/
        Word GetDoubleRegister(std::string rx);

		/* GetFlag() ritorna il valore di un dato flag
		*  @param Flag flag da cui prendere lo stato
		*  @return Il valore della flag
		*/ 
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

		enum InterruptType {
			VBLANK = 0,
			LCD_STAT = 1,
			TIMER = 2,
			SERIAL = 3,
			JOYPAD = 4
		};

		// Niente documentazione perche work in progress
		void cpu_init();

		void handleInterrupt();
		void requestInterrupt(InterruptType type);
		void pushStack(Byte value);
		Byte popStack();
		void returnFromInterrupt();


		bool CPU_Step();
		void fetch_ins();
		void fetch_data();
		void execute();
};

