#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "types.hpp"
#include "LR35902.hpp"

class Graphics{
    private:
        void initGraphics();
    public:
        Graphics();

        void RenderImageFromArray(Byte*);
        std::string loadShaderSource(const char*);

        GLFWwindow* window;

        std::string vertexShader;
        std::string fragmentShader;
};