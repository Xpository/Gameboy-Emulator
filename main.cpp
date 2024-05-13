// #include "headers/LR35902.hpp"
#include <iostream>
#include "graphics.hpp"

// clang -o main.exe main.cpp cpp/*.cpp -I headers
// g++ -o main.exe main.cpp cpp/*.cpp -I headers -v
// g++ -o build/main.exe main.cpp cpp/*.cpp -I headers -I C:/SDL2/include -LC:/SDL2/lib/x64 -lSDL2main -lSDL2


// int main() {	
// 	std::string fp = "roms/Tetris.gb";
// 	LR35902 thisCPU(fp);



// 	std::cout << "FINISH";
// }




///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Questo e' il codice per visualizzare un triangolo, dopo bisogna metterlo in diverse classi/file /////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
 	Graphics graphicsEngine;

	while(!glfwWindowShouldClose(graphicsEngine.window)){
		glfwSwapBuffers(graphicsEngine.window);
		glfwPollEvents();
	}
	

	glfwTerminate();
	return 0;
}
