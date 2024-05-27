 // #include "headers/LR35902.hpp"
#include <iostream>
#include <filesystem>
#include "../headers/graphics.hpp"

// Comandi per compilare
// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v

// Funzione per stampare tutti i file nella cartella "roms"
std::string getPathFromInput(){
    std::cout << "Benvenuto nell'Emulatore per Gameboy!\n";
    std::cout << "Per iniziare scegli un gioco dalla seguente lista:\n";
    std::string path = "roms/";
    int index = 1;
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        std::string thisPath = entry.path().string();
        thisPath.erase(0, 5);
        std::cout << "[" << index << "] " << thisPath << std::endl;
        index++;
    }
    std::cin >> index;
    int it = 0;
    for(const auto &entry : std::filesystem::directory_iterator(path)){
        if(index-1 == it){
            return entry.path().string();
        }
        it++;
    } 
    return "";
}


int main()
{
    std::string fp = getPathFromInput();
    system("cls");

    Cartridge* cart = new Cartridge(fp);

    // Debug tattico
    std::cout << "Logo corretto: " << cart->CheckLogo() << std::endl;
    std::cout << "Titolo della cartuccia: " << cart->GetTitle() << std::endl;
    std::cout << "Codice di licensa: " << cart->GetOldLicenseeCode() << std::endl;
    std::cout << "Grandezza della ROM: " << cart->GetRomSize() << std::endl;
    std::cout << "Grandezza della RAM data dalla cartuccia: " << cart->GetRamSize() << std::endl;
    std::cout << "Risultato del checksum: " << cart->ComputeChecksum() << std::endl;

    Memory memory(cart->GetData(), cart->GetRamSize());
    cart->~Cartridge();
    
    LR35902 cpu(fp, memory);
    Graphics graphics(memory);


    while (!glfwWindowShouldClose(graphics.window)) {
        glfwPollEvents();
        glfwSwapBuffers(graphics.window);
    }

    glfwTerminate();
    return 0;
}