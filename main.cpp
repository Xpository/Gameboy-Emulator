#include "headers/LR35902.hpp"
#include "headers/graphics.hpp"
#include <iostream>

// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v
// g++ -o build/main.exe main.cpp cpp/*.cpp -I headers -I C:/SDL2/include -LC:/SDL2/lib/x64 -lSDL2main -lSDL2


// int main() {	
// 	std::string fp = "roms/Tetris.gb";
// 	LR35902 thisCPU(fp);



// 	std::cout << "FINISH";
// }

int main()
{
	GLFWwindow* window = initGraphics(800, 800, "My nigga");
	Byte arr[] = {0x11, 0x4B, 0x3A, 0x7F, 0x9E, 0x22, 0x55, 0x88, 0xC4, 0x2F, 0x6A, 0xD3, 0x77, 0xA9, 0x5C, 0xE1};
	while(!glfwWindowShouldClose(window)){
		renderTile(1,1, arr);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "\nCiao";
	std::cin.get();
	return 0;
}
