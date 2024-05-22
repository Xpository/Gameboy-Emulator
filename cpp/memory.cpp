#include "../headers/memory.hpp"


/*
	LCDC (0xFF40 - LCD Control Register)
	Controlla l'abilitazione dello schermo LCD e varie modalità di visualizzazione.
	Bit significativi:
		Bit 7: LCD Display Enable (0 = Off, 1 = On)
		Bit 6: Window Tile Map Display Select (0 = 9800-9BFF, 1 = 9C00-9FFF)
		Bit 5: Window Display Enable (0 = Off, 1 = On)
		Bit 4: BG & Window Tile Data Select (0 = 8800-97FF, 1 = 8000-8FFF)
		Bit 3: BG Tile Map Display Select (0 = 9800-9BFF, 1 = 9C00-9FFF)
		Bit 2: OBJ (Sprite) Size (0 = 8x8, 1 = 8x16)
		Bit 1: OBJ (Sprite) Display Enable (0 = Off, 1 = On)
		Bit 0: BG Display (0 = Off, 1 = On)
	---------------------------------------------------------------------------------------------------------------------------------
	STAT (0xFF41 - LCDC Status Register)
	Controlla lo stato dell'LCD e gli interrupt LCD.
	Bit significativi:
		Bit 6: LYC=LY Coincidence Interrupt (1 = Enable)
		Bit 5: Mode 2 OAM Interrupt (1 = Enable)
		Bit 4: Mode 1 V-Blank Interrupt (1 = Enable)
		Bit 3: Mode 0 H-Blank Interrupt (1 = Enable)
		Bit 2: Coincidence Flag (0 = LY != LYC, 1 = LY == LYC)
		Bit 1-0: Mode Flag (00 = H-Blank, 01 = V-Blank, 10 = Searching OAM, 11 = Transferring Data to LCD Driver)
	---------------------------------------------------------------------------------------------------------------------------------
	SCY (0xFF42 - Scroll Y)
	Specifica la linea Y dello sfondo da visualizzare nella parte superiore dello schermo.
	---------------------------------------------------------------------------------------------------------------------------------
	SCX (0xFF43 - Scroll X)
	Specifica la linea X dello sfondo da visualizzare nella parte sinistra dello schermo.
	---------------------------------------------------------------------------------------------------------------------------------
	LY (0xFF44 - LCDC Y-Coordinate)
	Indica la linea corrente Y dello schermo LCD (0-153). Le linee 144-153 sono utilizzate per il V-Blank.
	---------------------------------------------------------------------------------------------------------------------------------
	LYC (0xFF45 - LY Compare)
	Confronta con il valore di LY. Quando LY coincide con LYC, viene impostata la Coincidence Flag in STAT e può essere generato un interrupt se abilitato.
	---------------------------------------------------------------------------------------------------------------------------------
	DMA (0xFF46 - DMA Transfer and Start Address)
	Utilizzato per trasferire rapidamente dati a OAM (Object Attribute Memory). Scrivendo un valore qui si inizia un trasferimento di 160 byte dall'indirizzo specificato (nella RAM) a OAM.
	---------------------------------------------------------------------------------------------------------------------------------
	BGP (0xFF47 - BG Palette Data)
	Definisce i colori utilizzati per lo sfondo e i tile della finestra. Codifica i colori per quattro sfumature di grigio.
	---------------------------------------------------------------------------------------------------------------------------------
	OBP0 (0xFF48 - Object Palette 0 Data)
	Definisce i colori utilizzati per gli sprite (oggetti) con la palette 0. Codifica i colori per quattro sfumature di grigio.
	---------------------------------------------------------------------------------------------------------------------------------
	OBP1 (0xFF49 - Object Palette 1 Data)
	Definisce i colori utilizzati per gli sprite con la palette 1. Codifica i colori per quattro sfumature di grigio.
	---------------------------------------------------------------------------------------------------------------------------------
	WY (0xFF4A - Window Y Position)
	Specifica la posizione Y della finestra sullo schermo. La finestra è un'area di visualizzazione separata dallo sfondo.
	---------------------------------------------------------------------------------------------------------------------------------
	WX (0xFF4B - Window X Position)
	Specifica la posizione X della finestra sullo schermo. La posizione effettiva è WX-7.
	---------------------------------------------------------------------------------------------------------------------------------

	Uso di questi Registri
		LCDC: Utilizzato per abilitare/disabilitare l'LCD, selezionare mappe tile, dimensioni degli sprite, ecc.
		STAT: Utilizzato per monitorare lo stato dell'LCD e abilitare gli interrupt.
		SCY e SCX: Utilizzati per lo scrolling dello sfondo.
		LY e LYC: Utilizzati per sincronizzare il rendering e generare interrupt.
		DMA: Utilizzato per caricare rapidamente sprite in OAM.
		BGP, OBP0, e OBP1: Utilizzati per definire i colori per lo sfondo e gli sprite.
		WY e WX: Utilizzati per posizionare la finestra sullo schermo.
*/


// Costruttore inizializza la classe
// @param ROM puntatore della ROM
Memory::Memory(Byte* datas, unsigned int size) 
{
	LCDC = 0x91; // Valore di default
    STAT = 0x85; // Valore di default
    SCY = 0x00;
    SCX = 0x00;
    LY = 0x00;
    LYC = 0x00;
    DMA = 0x00;
    BGP = 0xFC; // Valore di default
    OBP0 = 0xFF; // Valore di default
    OBP1 = 0xFF; // Valore di default
    WY = 0x00;
    WX = 0x00;
	
	cartridgeROM = new Byte[size];
	// Letteralmente cosa piu unsafe del mondo... spero vivamente che non crei errori
	memcpy(cartridgeROM, datas, size);
	

	ramEnabled = false;
	romBank = 1;
	ramBank = 0;
	bankingMode = false;
}

Memory::~Memory(){
	delete[] cartridgeROM;
}

Byte Memory::Read(Word address)
{
    if(address <= 0x3FFF){
		return cartridgeROM[address];
	}else if(address >= 0x4000 && address <= 0x7FFF){
		size_t offset = (romBank -1) * 0x4000 + (address - 0x4000);
		return cartridgeROM[offset];
	}else if(address >= 0xA000 && address <= 0xBFFF){
		if(!ramEnabled) return 0xFF;
		size_t offset = ramBank * 0x2000 + (address - 0xA000);
		return RAM[offset];
	}else if(address >= 0x8000 && address <= 0x9FFF){
		return VRAM[address - 0x8000];
	}else if(address >= 0xC000 && address <= 0xDFFF){
		return WRAM[address - 0xC000];
	}else if(address >= 0xFE00 && address <= 0xFE9F){
		return OAM[address - 0xFE00];
	}else if(address >= 0xFF00 && address <= 0xFF7F){
		switch (address) {
            case 0xFF40: return LCDC;
            case 0xFF41: return STAT;
            case 0xFF42: return SCY;
            case 0xFF43: return SCX;
            case 0xFF44: return LY;
            case 0xFF45: return LYC;
            case 0xFF46: return DMA;
            case 0xFF47: return BGP;
            case 0xFF48: return OBP0;
            case 0xFF49: return OBP1;
            case 0xFF4A: return WY;
            case 0xFF4B: return WX;
            default: 
				return IO[address - 0xFF00];
        }
	}else if(address >= 0xFF80 && address <= 0xFFFE){
		return HIGH_RAM[address - 0xFF80];
	}

	return 0xFF;
}

//Cagotti russo amorevole 
void Memory::Write(Word address, Byte data)
{
	if(address <= 0x1FFF){
		ramEnabled = (data & 0x0F) == 0xA;
	}else if (address >= 0x2000 && address <= 0x3FFF){
		data = data & 0x1F;
		if (data == 0) data = 1;
		romBank = data;
	}else if(address >= 0x4000 && address <= 0x5FFF){
		if (bankingMode){
			ramBank = data & 0x03;
		}else {
			int highBits = data & 0x03; 
     		romBank = (romBank & 0x1F) | (highBits << 5); 
		}
	}else if(address >= 0x6000 && address <= 0x7FFF){
		bankingMode = (data & 0x01) != 0;
	}else if(address >= 0xA000 && address <= 0xBFFF && ramEnabled){
		size_t offset = ramBank * 0x2000 + (address - 0xA000);
		RAM[offset] = data;
	}else if(address >= 0x8000 && address <= 0x9FFF){
		VRAM[address - 0x8000] = data;
	}else if(address >= 0xC000 && address <= 0xDFFF){
		WRAM[address - 0xC000] = data;
	}else if(address >= 0xFE00 && address <= 0xFE9F){
		OAM[address - 0xFE00] = data;
	}else if(address >= 0xFF80 && address <= 0xFFFE){
		HIGH_RAM[address - 0xFF80] = data;
	}else if(address >= 0xFF00 && address <= 0xFF7F){
		switch (address) {
            case 0xFF40: 
				LCDC = data; 
				break;
            case 0xFF41: 
				STAT = data; 
				break;
            case 0xFF42: 
				SCY = data; 
				break;
            case 0xFF43: 
				SCX = data; 
				break;
            case 0xFF44: 
				LY = 0; 
				break; // LY è un registro solo lettura, scrivere a LY resetta a 0
            case 0xFF45: 
				LYC = data; 
				break;
            case 0xFF46:
                DMA = data;
                // Implementa trasferimento DMA da OAM
                for (int i = 0; i < 0xA0; i++) {
                    OAM[i] = Read((data << 8) + i);
                }
                break;
            case 0xFF47: 
				BGP = data; 
				break;
            case 0xFF48: 
				OBP0 = data; 
				break;
            case 0xFF49: 
				OBP1 = data; 
				break;
            case 0xFF4A: 
				WY = data; 
				break;
            case 0xFF4B: 
				WX = data; 
				break;
            default: 
				IO[address - 0xFF00] = data; 
				break;
        }
	}else if (address >= 0xFF80 && address <= 0xFFFE){
		HIGH_RAM[address - 0xFF80] = data;
	}

}

void Memory::OAMDMA() {
    for(int i = 0; i < 0xA0; i++) {
        OAM[i] = Read((DMA << 8) + i);
    }
}

Byte* Memory::RequestPointerTo(std::string reg){
	if(reg == "LCDC"){
		return &LCDC;
	}else if(reg == "STAT"){
		return &STAT;		
	}else if(reg == "SCY"){
		return &SCY;
	}else if(reg == "SCX"){
		return &SCX;		
	}else if(reg == "LY"){
		return &LY;		
	}else if(reg == "LYC"){
		return &LYC;		
	}else if(reg == "DMA"){
		return &DMA;		
	}else if(reg == "BGP"){
		return &BGP;		
	}else if(reg == "OBP0"){
		return &OBP0;		
	}else if(reg == "OBP1"){
		return &OBP1;		
	}else if(reg == "WY"){
		return &WY;	
	}else if(reg == "WX"){
		return &WX;		
	}
	return nullptr;
}

//
//	Serve implementazione dei diversi MBC qualcuno la faccia @0hM1C1uf1 @AleBitCode <3 da @RehTrizZ 
//
