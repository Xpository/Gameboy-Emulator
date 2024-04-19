#include <GLFW/glfw3.h>
#include <iostream>
#include <types.hpp>

class Graphics{
    public:
        Graphics(int, int, const char*);
        ~Graphics();
        void init();
        bool shouldClose();
        void startFrame();
        void endFrame();
        void drawSprite(int, int, Byte*, int, int);
        void setPixel(int, int, Byte, Byte, Byte);
    private:
        GLFWwindow* window;
        GLuint textureID;
        void setupTextures();
};