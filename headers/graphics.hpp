#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "types.hpp"
#include "LR35902.hpp"

class Graphics{
    private:
        void initGraphics();
        Byte* pLY;


        int modeClock;
        int mode;
        Memory* mem;
    public:
        Graphics(Memory);
        void Update(int);
        void renderCurrentScanline();
        void requestInterrupt(int);


        void RenderPixels();
        void updateMatrix(Byte, Byte, Byte);
        std::string loadShaderSource(const char*);

        GLFWwindow* window;

        std::string vertexShader;
        std::string fragmentShader;

        Byte screenMatrix[160][144];


};