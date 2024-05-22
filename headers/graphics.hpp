#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "types.hpp"
#include "LR35902.hpp"

class Graphics{
    private:
        void initGraphics();
        Byte* toArrayScreenMatrix();
        Byte* pLY;


        int modeClock;
        int mode;
    public:
        Graphics(Memory);
        void update(int);
        void renderCurrentScanline();
        void requestInterrupt(int);


        void RenderImageFromScreenMatrix();
        void updateMatrix(Byte, Byte, Byte);
        std::string loadShaderSource(const char*);

        GLFWwindow* window;

        std::string vertexShader;
        std::string fragmentShader;

        Byte screenMatrix[160][144];


};