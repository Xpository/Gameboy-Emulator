#include "../headers/memory.h"
#include "memory.h"

// Costruttore inizializza la classe
// @param ROM puntatore della ROM
Memory::Memory(Byte* datas)
{
	for(int i = 0; i < 8 * 1024 * 1024; i++){
		cartridgeROM[i] = datas[i];
	}

	ramEnabled = false;
	romBank = 1;
	ramBank = 0;
	bankingMode = false;
}

Byte Memory::Read(Word address)
{
    if(address <= 0x3FFF){
		return cartridgeROM[address];
	}else if(address >= 0x4000 && address <= 0x7FFF){
		size_t offset = (romBank -1) * 0x4000 + (address -0x4000);
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
	}else if(address >= 0xFF80 && address <= 0xFFFE){
		return HIGH_RAM[address - 0xFF80];
	}

	return 0xFF;
}

//Cagotti russo di merda
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
			// Implementa dopo
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
	}else if(address >= 0xFF80 && address >= 0xFFFE){
		HIGH_RAM[address - 0xFF80] = data;
	}else if(address >= 0xFF00 && address <= 0xFF7F){
		IO[address - 0xFF00] = data;
	}
}


//
//	Serve implementazione dei diversi MBC qualcuno la faccia @0hM1C1uf1 @AleBitCode <3 da @RehTrizZ 
//
