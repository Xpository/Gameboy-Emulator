#include "../headers/memory.h"
#include "memory.h"

// Costruttore inizializza la classe
// @param ROM puntatore della ROM
Memory::Memory(Byte* datas, std::string CartridgeType)
{
	for(int i = 0; i < 0x7FFF; i++){
		cartridgeROM[i] = datas[i];
	}


	// Che obrobrio, pero non si puo usare lo switch con le string XD i wanna kms
	if(CartridgeType.find("MBC1") != std::string::npos){
		MBC = MBC1;
	}else if(CartridgeType.find("MBC2") != std::string::npos){
		MBC = MBC2;
	}else if(CartridgeType.find("MBC3") != std::string::npos){
		MBC = MBC3;
	}else if(CartridgeType.find("MBC5") != std::string::npos){
		MBC = MBC5;
	}else if(CartridgeType.find("MBC6") != std::string::npos){
		MBC = MBC6;
	}else if(CartridgeType.find("MBC7") != std::string::npos){
		MBC = MBC7;
	}else if(CartridgeType.find("MMM01") != std::string::npos){
		MBC = MMM01;
	}else if(CartridgeType.find("M161") != std::string::npos){
		MBC = M161;
	}else if(CartridgeType.find("HuC1") != std::string::npos){
		MBC = HuC1;
	}else if(CartridgeType.find("HuC3") != std::string::npos){
		MBC = HuC3;
	}else{
		MBC = NO_MBCS;
	}

	// Inizializza la memoria con i primi 32768 bytes della ROM
	for(Word i = 0x0000; i < 0x8000; i++){
			cartridgeROM[i] = datas[i];
	}
}

Byte Memory::Read(Word address)
{
    if(address <= 0x7FFF){

	}else if(address >= 0x8000 && address <= 0x9FFF){

	}
}

void Memory::Write(Word, Byte)
{

}


//
//	Serve implementazione dei diversi MBC qualcuno la faccia @0hM1C1uf1 @AleBitCode <3 da @RehTrizZ 
//
