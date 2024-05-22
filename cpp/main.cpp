// #include "headers/LR35902.hpp"
#include <iostream>
#include "../headers/graphics.hpp"

// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v


// int main() {	
// 	std::string fp = "roms/Tetris.gb";
// 	LR35902 thisCPU(fp);



// 	std::cout << "FINISH";
// }



int main()
{

    Byte romData[32768]; // Simula una ROM di 32KB
    for (int i = 0; i < 32768; i++) {
        romData[i] = rand() % 0xFF + 1; // Inizializza con dati fittizi
    }
    Memory memory(romData, 32768);

    // Crea un'istanza di Graphics
    Graphics graphics(memory);

    // Simula il riempimento della screenMatrix con valori in scala di grigi
    for (int y = 0; y < 144; ++y) {
        for (int x = 0; x < 160; ++x) {
            graphics.updateMatrix(x + y, x, y); // Riempie con un gradiente
        }
    }

    // Ciclo di rendering
    while (!glfwWindowShouldClose(graphics.window)) {
        graphics.RenderImageFromScreenMatrix();
        glfwPollEvents();
    }

    // Termina GLFW
    glfwTerminate();
    return 0;

}