#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include "types.hpp"

// Stringa che conterra la somma degli esadecimali della tile map
#define stringifiedArray std::string
#define tileDataLength 16


void addToLookup(stringifiedArray, Byte*);
stringifiedArray tileDataConvert(Byte*);


// initGraphics inizializza la libreria grafica OpenGL
// settando la versione minima e massima alla 3.3,
// imposta il profilo su Core,
// e infine crea una callback che ridimensiona la finestra
// @param width: La larghezza della finestra
// @param height: L'altezza della finestra
// @param title: Il titolo della finestra
// @return GLFWwindow pointer: ritorna un puntatore alla finestra 
GLFWwindow* initGraphics(int, int, const char*);

// terminateWindow distrugge la finestra fornita e termina la libreria OpenGL
// @param Window_Pointer: il puntatore alla finestra da distruggere
void terminateWindow(GLFWwindow* window);


void renderTile(int, int, Byte*);