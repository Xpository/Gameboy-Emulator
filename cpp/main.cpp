// #include "headers/LR35902.hpp"
#include <iostream>
#include <filesystem>
#include "../headers/graphics.hpp"

// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v

//"roms/Tetris.gb";
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
    Memory memory(cart->GetData(), cart->GetRamSize());
    cart->~Cartridge();
    
    LR35902 cpu(fp, memory);
    Graphics graphics(memory);

    const int cyclesPerFrame = 70224; // Cicli di clock per frame (4194304 Hz / 60 FPS)
    int cyclesExecuted = 0;

    while (!glfwWindowShouldClose(graphics.window)) {
        while (cyclesExecuted < cyclesPerFrame) {
            cyclesExecuted += cpu.CPU_Step();
            graphics.Update(cyclesExecuted);
        }

        graphics.RenderPixels();
        glfwPollEvents();
        cyclesExecuted = 0;
        glfwSwapBuffers(graphics.window);
    }

    glfwTerminate();
    return 0;
}