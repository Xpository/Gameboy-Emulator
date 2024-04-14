#include "../headers/cartridge.hpp"
#include "../headers/types.hpp"





 
Cartridge::Cartridge(std::string filepath) : data(nullptr) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cout << "File not found\n";
        return;
    }
    
    // Va alla fine del file per determinare la dimensione
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg); // Ritorna all'inizio del file

    // Alloca memoria temporanea per leggere il file
    Byte* tempBuffer = new Byte[size];

    // Leggi il file nel buffer temporaneo
    if (!file.read(reinterpret_cast<char*>(tempBuffer), size)) {
        std::cerr << "Errore durante la lettura del file.\n";
        delete[] tempBuffer;
        return;
    }
    
    // A questo punto, puoi determinare la dimensione effettiva della ROM
    // Assumendo che GetRomSize() possa ora operare correttamente sul buffer temporaneo
    unsigned int effectiveSize = GetRomSize(tempBuffer);

    // Alloca memoria basata sulla dimensione effettiva della ROM
    data = new Byte[effectiveSize];

    // Copia i dati necessari nel buffer definitivo `data`
    unsigned int bytesToCopy = std::min(static_cast<std::streamsize>(effectiveSize), size);
    for(unsigned int i = 0; i < bytesToCopy; i++) {
        data[i] = tempBuffer[i];
    }

    // Pulisci la memoria temporanea
    delete[] tempBuffer;
    file.close();
}

Cartridge::~Cartridge() {
    delete[] data; // Distruttore per pulire la memoria
}

/* CheckLogo controlla i Byte 0x0104 a 0x0133 per vedere se corrisponde
 * @return ritorna true se corrisponde, false altrimenti 
*/ 
bool Cartridge::CheckLogo(){
    Byte logo[48] = {
        0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    };

    for(Word i = 0x0104, j = 0; i <= 0x0133; i++, j++){
        if(data[i] != logo[j]){
            return false;
        }
    }
    return true;
}
/* GetTitle ritorna il titolo che si trova tra 0x0134 e 0x0143
 * @return ritorna il titolo in uppercase
*/ 
std::string Cartridge::GetTitle(){
    std::string title = "";
    for(Word i = 0x0134; i <= 0x0143; i++){
        if(data[i] == 0x00)
            break;
        title += data[i]; 
    }
    return title;
}

/* CheckCGBFlag controlla il byte a 0x0143 e ritorna se il CGB e' attivo o no
 * @return ritorna la presenza del CGB, true = attivo, false = disattivato
*/ 
bool Cartridge::CheckCGBFlag()
{
    if (data[0x0143] == 0x80){
        return true;
    }else{
        return false;
    }
}


/* GetNewLicenseeCode ritorna il codice licensa a 0x0145
 * @return ritorna la stringa con il nome della casa produttrice del gioco
*/ 
std::string Cartridge::GetNewLicenseeCode()
{
    std::map<Byte, std::string> NewLicenseeCodes = {
        {0x00, "None"},
        {0x01, "Nintendo R&D1"},
        {0x08, "Capcom"},
        {0x13, "Electronic Arts"},
        {0x18, "Hudson Soft"},
        {0x19, "b-ai"},
        {0x20, "kss"},
        {0x22, "pow"},
        {0x24, "PCM Complete"},
        {0x25, "san-x"},
        {0x28, "Kemco Japan"},
        {0x29, "seta"},
        {0x30, "Viacom"},
        {0x31, "Nintendo"},
        {0x32, "Bandai"},
        {0x33, "Ocean/Acclaim"},
        {0x34, "Konami"},
        {0x35, "Hector"},
        {0x37, "Taito"},
        {0x38, "Hudson"},
        {0x39, "Banpresto"},
        {0x41, "Ubi Soft"},
        {0x42, "Atlus"},
        {0x44, "Malibu"},
        {0x46, "angel"},
        {0x47, "Bullet-Proof"},
        {0x49, "irem"},
        {0x50, "Absolute"},
        {0x51, "Acclaim"},
        {0x52, "Activision"},
        {0x53, "American sammy"},
        {0x54, "Konami"},
        {0x55, "Hi tech entertainment"},
        {0x56, "LJN"},
        {0x57, "Matchbox"},
        {0x58, "Mattel"},
        {0x59, "Milton Bradley"},
        {0x60, "Titus"},
        {0x61, "Virgin"},
        {0x64, "LucasArts"},
        {0x67, "Ocean"},
        {0x69, "Electronic Arts"},
        {0x70, "Infogrames"},
        {0x71, "Interplay"},
        {0x72, "Broderbund"},
        {0x73, "sculptured"},
        {0x75, "sci"},
        {0x78, "THQ"},
        {0x79, "Accolade"},
        {0x80, "misawa"},
        {0x83, "lozc"},
        {0x86, "Tokuma Shoten Intermedia"},
        {0x87, "Tsukuda Original"},
        {0x91, "Chunsoft"},
        {0x92, "Video system"},
        {0x93, "Ocean/Acclaim"},
        {0x95, "Varie"},
        {0x96, "Yonezawa/s'pal"},
        {0x97, "Kaneko"},
        {0x99, "Pack in soft"},
        // {0x9H, "Bottom Up"},           Questa entry e' sbagliata ma secondo la documentazione il suo hex e' 0x09H ma non puo' assumere H... 
        {0xA4, "Konami (Yu-Gi-Oh!)"}
    };

    return NewLicenseeCodes[data[0x0145]];
}


/* GetCartridgeType ritorna il tipo della cartridge
 * @return ritorna la stringa con il tipo della cartridge
*/
std::string Cartridge::GetCartridgeType()
{
    std::map<Byte, std::string> cartridgeTypes = {
        {0x00, "ROM ONLY"},
        {0x01, "MBC1"},
        {0x02, "MBC1+RAM"},
        {0x03, "MBC1+RAM+BATTERY"},
        {0x05, "MBC2"},
        {0x06, "MBC2+BATTERY"},
        {0x08, "ROM+RAM"},
        {0x09, "ROM+RAM+BATTERY"},
        {0x0B, "MMM01"},
        {0x0C, "MMM01+RAM"},
        {0x0D, "MMM01+RAM+BATTERY"},
        {0x0F, "MBC3+TIMER+BATTERY"},
        {0x10, "MBC3+TIMER+RAM+BATTERY"},
        {0x11, "MBC3"},
        {0x12, "MBC3+RAM"},
        {0x13, "MBC3+RAM+BATTERY"},
        {0x19, "MBC5"},
        {0x1A, "MBC5+RAM"},
        {0x1B, "MBC5+RAM+BATTERY"},
        {0x1C, "MBC5+RUMBLE"},
        {0x1D, "MBC5+RUMBLE+RAM"},
        {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
        {0x20, "MBC6"},
        {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
        {0xFC, "POCKET CAMERA"},
        {0xFD, "BANDAI TAMA5"},
        {0xFE, "HuC3"},
        {0xFF, "HuC1+RAM+BATTERY"}
    };

    return cartridgeTypes[data[0x0147]];
}


/* !!!!! FUNZIONE UTILIZZATA NEL COSTRUCTOR NON USARE DA ALTRE PARTI !!!!!
 * GetRomSize ritorna la ROM size
 * @return ritorna un insigned int con la grandezza della ROM in base all'indirizzo di 0x0148
*/
unsigned int Cartridge::GetRomSize(Byte *dt)
{
    return 32 * 1024 * (1 << dt[0x148]);
}

/* GetRomSize ritorna la ROM size
 * @return ritorna un insigned int con la grandezza della ROM in base all'indirizzo di 0x0148
*/
unsigned int Cartridge::GetRomSize()
{
    return 32 * 1024 * (1 << data[0x148]);
}


/* GetNewLicenseeCode ritorna la RAM size
 * @return ritorna un insigned int con la grandezza della ROM in base all'indirizzo di 0x0148
*/
unsigned int Cartridge::GetRamSize()
{
    std::map<Byte, unsigned int> ramSizes = {
        {0x00, 0},          // No RAM
        {0x01, 0},          // Unused
        {0x02, 8 * 1024},   // 8 KiB
        {0x03, 32 * 1024},  // 32 KiB
        {0x04, 128 * 1024}, // 128 KiB
        {0x05, 64 * 1024},  // 64 KiB
    };

    return ramSizes[data[0x0149]];
}

/* GetOldLicenseeCode ritorna il vecchio Licensee code
 * @return ritorna il vecchio Licensee code. Se e' 0x33 usa il NewLicenseeCode
*/
std::string Cartridge::GetOldLicenseeCode()
{
    std::map<Byte, std::string> licenseeCodes = {
        {0x00, "None"},
        {0x01, "Nintendo"},
        {0x08, "Capcom"},
        {0x09, "Hot-B"},
        {0x0A, "Jaleco"},
        {0x0B, "Coconuts Japan"},
        {0x0C, "Elite Systems"},
        {0x13, "EA (Electronic Arts)"},
        {0x18, "Hudsonsoft"},
        {0x19, "ITC Entertainment"},
        {0x1A, "Yanoman"},
        {0x1D, "Japan Clary"},
        {0x1F, "Virgin Interactive"},
        {0x24, "PCM Complete"},
        {0x25, "San-X"},
        {0x28, "Kotobuki Systems"},
        {0x29, "Seta"},
        {0x30, "Infogrames"},
        {0x31, "Nintendo"},
        {0x32, "Bandai"},
        {0x33, "Indicates that the New licensee code should be used instead."},
        {0x34, "Konami"},
        {0x35, "HectorSoft"},
        {0x38, "Capcom"},
        {0x39, "Banpresto"},
        {0x3C, ".Entertainment i"},
        {0x3E, "Gremlin"},
        {0x41, "Ubisoft"},
        {0x42, "Atlus"},
        {0x44, "Malibu"},
        {0x46, "Angel"},
        {0x47, "Spectrum Holoby"},
        {0x49, "Irem"},
        {0x4A, "Virgin Interactive"},
        {0x4D, "Malibu"},
        {0x4F, "U.S. Gold"},
        {0x50, "Absolute"},
        {0x51, "Acclaim"},
        {0x52, "Activision"},
        {0x53, "American Sammy"},
        {0x54, "GameTek"},
        {0x55, "Park Place"},
        {0x56, "LJN"},
        {0x57, "Matchbox"},
        {0x59, "Milton Bradley"},
        {0x5A, "Mindscape"},
        {0x5B, "Romstar"},
        {0x5C, "Naxat Soft"},
        {0x5D, "Tradewest"},
        {0x60, "Titus"},
        {0x61, "Virgin Interactive"},
        {0x67, "Ocean Interactive"},
        {0x69, "EA (Electronic Arts)"},
        {0x6E, "Elite Systems"},
        {0x6F, "Electro Brain"},
        {0x70, "Infogrames"},
        {0x71, "Interplay"},
        {0x72, "Broderbund"},
        {0x73, "Sculptered Soft"},
        {0x75, "The Sales Curve"},
        {0x78, "t.hq"},
        {0x79, "Accolade"},
        {0x7A, "Triffix Entertainment"},
        {0x7C, "Microprose"},
        {0x7F, "Kemco"},
        {0x80, "Misawa Entertainment"},
        {0x83, "Lozc"},
        {0x86, "Tokuma Shoten Intermedia"},
        {0x8B, "Bullet-Proof Software"},
        {0x8C, "Vic Tokai"},
        {0x8E, "Ape"},
        {0x8F, "I’Max"},
        {0x91, "Chunsoft Co."},
        {0x92, "Video System"},
        {0x93, "Tsubaraya Productions Co."},
        {0x95, "Varie Corporation"},
        {0x96, "Yonezawa/S’Pal"},
        {0x97, "Kaneko"},
        {0x99, "Arc"},
        {0x9A, "Nihon Bussan"},
        {0x9B, "Tecmo"},
        {0x9C, "Imagineer"},
        {0x9D, "Banpresto"},
        {0x9F, "Nova"},
        {0xA1, "Hori Electric"},
        {0xA2, "Bandai"},
        {0xA4, "Konami"},
        {0xA6, "Kawada"},
        {0xA7, "Takara"},
        {0xA9, "Technos Japan"},
        {0xAA, "Broderbund"},
        {0xAC, "Toei Animation"},
        {0xAD, "Toho"},
        {0xAF, "Namco"},
        {0xB0, "acclaim"},
        {0xB1, "ASCII or Nexsoft"},
        {0xB2, "Bandai"},
        {0xB4, "Square Enix"},
        {0xB6, "HAL Laboratory"},
        {0xB7, "SNK"},
        {0xB9, "Pony Canyon"},
        {0xBA, "Culture Brain"},
        {0xBB, "Sunsoft"},
        {0xBD, "Sony Imagesoft"},
        {0xBF, "Sammy"},
        {0xC0, "Taito"},
        {0xC2, "Kemco"},
        {0xC3, "Squaresoft"},
        {0xC4, "Tokuma Shoten Intermedia"},
        {0xC5, "Data East"},
        {0xC6, "Tonkinhouse"},
        {0xC8, "Koei"},
        {0xC9, "UFL"},
        {0xCA, "Ultra"},
        {0xCB, "Vap"},
        {0xCC, "Use Corporation"},
        {0xCD, "Meldac"},
        {0xCE, ".Pony Canyon or"},
        {0xCF, "Angel"},
        {0xD0, "Taito"},
        {0xD1, "Sofel"},
        {0xD2, "Quest"},
        {0xD3, "Sigma Enterprises"},
        {0xD4, "ASK Kodansha Co."},
        {0xD6, "Naxat Soft"},
        {0xD7, "Copya System"},
        {0xD9, "Banpresto"},
        {0xDA, "Tomy"},
        {0xDB, "LJN"},
        {0xDD, "NCS"},
        {0xDE, "Human"},
        {0xDF, "Altron"},
        {0xE0, "Jaleco"},
        {0xE1, "Towa Chiki"},
        {0xE2, "Yutaka"},
        {0xE3, "Varie"},
        {0xE5, "Epcoh"},
        {0xE7, "Athena"},
        {0xE8, "Asmik ACE Entertainment"},
        {0xE9, "Natsume"},
        {0xEA, "King Records"},
        {0xEB, "Atlus"},
        {0xEC, "Epic/Sony Records"},
        {0xEE, "IGS"},
        {0xF0, "A Wave"},
        {0xF3, "Extreme Entertainment"},
        {0xFF, "LJN"}
    };

    if(data[0x014B] == 0x33)
        return GetNewLicenseeCode();
    else
        return licenseeCodes[data[0x014B]];
}

bool Cartridge::ComputeChecksum()
{
    //
    // Questo checksum controlla i byte da 0x0134 a 0x014C
    // Se il risultato non corrisponde al valore in 0x014D
    // L'esecuzione e' terminata
    //
    Byte checksum = 0;
    for (Word address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - data[address] - 1;
    }

    return checksum == data[0x014D];
}


/* ReadCart ritorna un valore, dato l'indirizzo come parametro
* @return ritorna un Byte presente all'indirizzo "address"
*/
Byte Cartridge::ReadCart(Word address) 
{   
    // Da modificare i bound per restringere l'accesso
    return data[address];
}

/* ReadFromCart ritorna un array con i valori da inizio a fine
 * @return ritorna un puntatore ad un array di (endAddress - startAddress) + 1 Byte,
 *         contenente i dati da startAddress a endAddress.
*/         
Byte* Cartridge::ReadFromToCart(Word startAddress, Word endAddress)
{
    // Scambia in caso di uso sbagliato
    if(startAddress > endAddress){
        std::swap(startAddress, endAddress);
    }
    int size = (endAddress - startAddress) + 1;
    Byte* dataArray = new Byte[size];

    for(Byte i = startAddress, j = 0; i <= endAddress; i++, j++){
        dataArray[j] = data[i];
    }

    return dataArray;
}

Byte *Cartridge::GetData()
{
    return data;
}

bool Cartridge::ValidateCartridge()
{
    // Controllo del logo
    if(!CheckLogo())
        return false;
    
    // Controllo del titolo
    std::string title = GetTitle();
    if(title.length() == 0)
        return false;
    
    // Controlla i licensee code
    std::string licensee = GetOldLicenseeCode();
    if(licensee.length() == 0)
        return false;
    
    // Controlla la checksum
    if(!ComputeChecksum())
        return false;
    

    return true;
} 