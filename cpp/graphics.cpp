#include <graphics.hpp>

Graphics::Graphics(int width, int height, const char* title)
{
    // Inizializza la libreria 
    if (!glfwInit()){
        std::cerr << "Errore: impossibile inizializzare la libreria" << std::endl; 
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Imposta il profilo Core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 


    // Crea la finestra
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    // Se non si riesce lancia un errore
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Errore: errore durante l'inizializzazione della finestra. Riprovare" << std::endl; 
        return;
    }

    // Rendi la finestra questo contesto
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0,0, width, height);
    });
}

Graphics::~Graphics()
{
    glfwTerminate();
}

void Graphics::init()
{
}

bool Graphics::shouldClose()
{
    return false;
}

void Graphics::startFrame()
{
}

void Graphics::endFrame()
{
}

void Graphics::drawSprite(int x, int y, Byte *spriteData, int width, int height)
{
}

void Graphics::setPixel(int x, int y, Byte r, Byte g, Byte b)
{
}

void Graphics::setupTextures()
{
}
