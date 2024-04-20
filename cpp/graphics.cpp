#include "../headers/graphics.hpp"


// IDsmap contenente gli ID usati dalle texture, per usi frequenti questo ottimizza il tutto
std::map<stringifiedArray, Byte*> IDslookup;



void addToLookup(stringifiedArray key, Byte* tileData)
{
    IDslookup.insert({key, tileData});
}

stringifiedArray tileDataConvert(Byte* tileData)
{
    stringifiedArray str = "";
    for(int i = 0; i < tileDataLength; i++){
        str = str + std::to_string(tileData[i]);
    }
    // std::cout << str << std::endl << str.length(); // For debug
    return str;
}

GLFWwindow *initGraphics(int width, int height, const char *title)
{
    GLFWwindow* window;
    // Inizializza la libreria 
    if (!glfwInit()){
        std::cerr << "Errore: impossibile inizializzare la libreria" << std::endl; 
        return nullptr;
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
        return nullptr;
    }

    // Rendi la finestra questo contesto
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0,0, width, height);
    });

    return window;
}
void terminateWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


void renderTile(int x, int y, Byte* tileData){
    int width = 8, height = 8;
    // Immagine da renderizzare, moltiplicata *3 per via dell'RGB
    Byte pixelData[width * height * 3];

    for (int i = 0; i < height; ++i) {  
        for (int j = 0; j < width; ++j) {  
            int colorIndex = ((tileData[i] >> (7 - j)) & 1) | (((tileData[i + 1] >> (7 - j)) & 1) << 1);
            Byte colorValue = 85 * colorIndex;  
            int index = (i * width + j) * 3;
             // Setta l'RGB allo stesso colore dato che il Gameboy usa grafiche in bianco e nero
            pixelData[index] = pixelData[index + 1] = pixelData[index + 2] = colorValue;  // RGB
        }
    }

    glRasterPos2i(x, y);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
}