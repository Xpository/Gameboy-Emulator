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
	std::string fp = "roms/Tetris.gb";
	LR35902 CPU(fp);

	Graphics graphics;

    // Crea un array di dati per lo schermo (160x144)
    // Qui creiamo un pattern semplice per testare il rendering
    Byte testScreenData[160][144];

    // Riempie il testScreenData con un pattern
    for (int y = 0; y < 144; ++y) {
        for (int x = 0; x < 160; ++x) {
            if ((x / 10) % 2 == (y / 10) % 2) {
                testScreenData[x][y] = 0xFF; // Bianco
            } else {
                testScreenData[x][y] = 0x00; // Nero
            }
        }
    }

    // Copia i dati nel screenMatrix del Graphics
    memcpy(graphics.screenMatrix, testScreenData, sizeof(testScreenData));

    // Carica e compila i shaders
    // graphics.vertexShader = graphics.loadShaderSource("shaders/shader.vert");
    // graphics.fragmentShader = graphics.loadShaderSource("shaders/shader.frag");

    // Loop di rendering
    while (!glfwWindowShouldClose(graphics.window)) {
        // Renderizza l'immagine dallo screenMatrix
        graphics.RenderImageFromScreenMatrix();

        // Scambia i buffer e processa gli eventi
        glfwSwapBuffers(graphics.window);
        glfwPollEvents();
    }

    // Termina GLFW
    glfwTerminate();

    return 0;
}