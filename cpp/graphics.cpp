#include "../headers/graphics.hpp"

// framebuffer_size_callback: funzione che serve per modificare la viewport della finestra
// @attention Molto probabilmente non verra mai usata
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLuint LoadShaders(std::string fragmentShaderSource, std::string vertexShaderSource){
    // Rendiamoli stringhe in C perchè sta schifo di libreria è in C...
    const char* vertexAsChar = vertexShaderSource.c_str();
    const char* fragmentAsChar = fragmentShaderSource.c_str();
    
    GLuint vertex, fragment;
    int success;
    char log[512];

    // Creazione e caricamento della Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexAsChar, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, log);
        std::cerr << "Errore durante la compilazione delle vertex shaders, di seguito il log:\n" << log << std::endl;
    }
    // Creazione e caricamento della Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentAsChar, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, log);
        std::cerr << "Errore durante la compilazione delle fragment shaders, di seguito il log:\n" << log << std::endl;
    }

    // Se tutto va a buon fine, sperando che tutto funzioni senno non ho la minima idea di come fixare 😭😭
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cerr << "Errore durante il linking delle shaders al program, di seguito il log:\n" << log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void Graphics::initGraphics()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	window = glfwCreateWindow(800, 600, "Gameboy Emulator", NULL, NULL);

    if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
    
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

    // 160x144 = La grandezza dello schermo del Gameboy
    glViewport(0, 0, 160, 144);

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

}

std::string Graphics::loadShaderSource(const char * filepath)
{
    std::ifstream file(filepath, std::ios::in);
    if(!file.is_open()){
        std::cerr << "Errore: Impossibile leggere il file";
        return "";
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return str;
}


Graphics::Graphics(Memory mem){
    initGraphics();

    fragmentShader = loadShaderSource("shaders/shader.frag");
    vertexShader = loadShaderSource("shaders/shader.vert");
    
    for (int i = 0; i < 160; i++){
        for(int j = 0; j < 144; j++){
            screenMatrix[i][j] = 0x00;
        }
    }
    
    mode = 2; // Inizia con la OAM Search mode
    modeClock = 0;
    this->mem = &mem;
    pLY = mem.RequestPointerTo("LY");
}

void Graphics::updateMatrix(Byte tileData, Byte x, Byte y)
{
    screenMatrix[y][x] = tileData; 
}

void Graphics::RenderPixels() {
    Byte ly = mem->RequestValueOfRegister("LY");
    bool use8x16 = (mem->RequestValueOfRegister("LCDC") & 0x04) != 0;

    for (int i = 0; i < 40; i++) {
        Byte spriteY = mem->OAM[i * 4] - 16;
        Byte spriteX = mem->OAM[i * 4 + 1] - 8;
        Byte tileIndex = mem->OAM[i * 4 + 2];
        Byte attributes = mem->OAM[i * 4 + 3];

        bool flipY = (attributes & 0x40) != 0;
        bool flipX = (attributes & 0x20) != 0;

        int spriteHeight = use8x16 ? 16 : 8;
        if (ly >= spriteY && ly < (spriteY + spriteHeight)) {
            int line = ly - spriteY;
            if (flipY) {
                line = spriteHeight - line - 1;
            }

            Byte tileLow = mem->Read(0x8000 + tileIndex * 16 + line * 2);
            Byte tileHigh = mem->Read(0x8000 + tileIndex * 16 + line * 2 + 1);

            for (int x = 0; x < 8; x++) {
                int colorBit = flipX ? x : 7 - x;
                int color = ((tileHigh >> colorBit) & 1) << 1 | ((tileLow >> colorBit) & 1);
                if (color != 0) {
                    int pixelX = spriteX + x;
                    if (pixelX >= 0 && pixelX < 160) {
                        screenMatrix[ly][pixelX] = color;
                    }
                }
            }
        }
    }
}


void Graphics::renderCurrentScanline() {
    Byte scx = mem->RequestValueOfRegister("SCX");
    Byte scy = mem->RequestValueOfRegister("SCY");
    Byte ly = mem->RequestValueOfRegister("LY");

    for (int x = 0; x < 160; x++) {
        // Calcola le coordinate dello sfondo
        int bgX = (scx + x) & 0xFF;
        int bgY = (scy + ly) & 0xFF;
        // Calcola l'indice della tile nella tile map
        int tileIndex = (bgY / 8) * 32 + (bgX / 8);
        // Calcola l'indirizzo della tile data
        int tileAddress = mem->Read(0x9800 + tileIndex) * 16 + (bgY % 8) * 2;
        // Leggi i byte della tile data
        Byte tileLow = mem->Read(tileAddress);
        Byte tileHigh = mem->Read(tileAddress + 1);
        // Calcola il colore del pixel
        int colorBit = 7 - (bgX % 8);
        int color = ((tileHigh >> colorBit) & 1) << 1 | ((tileLow >> colorBit) & 1);
        // Setta il pixel nel buffer dello schermo
        screenMatrix[ly][x] = color;
    }

    RenderPixels();


}



void Graphics::requestInterrupt(int interruptType){
    // Non so se serva Gori please cock
}

void Graphics::Update(int cycles)
{
    modeClock += cycles;

    mem->UpdateSTAT(modeClock);

    switch (mode)
    {
    case 2:
        if(modeClock >= 80){
            modeClock = 0;
            mode = 3;
        }
        break;
    case 3:
        if(modeClock >= 172){
            modeClock = 0;
            mode = 0;
            renderCurrentScanline();
        }
        break;
    case 0: 
        if(modeClock >= 204){
            modeClock = 0;
            // Anche se sembra strano, per via della associatività a sinistra, il seguente codice funziona cosi
            // << Il valore puntato da pLY va aumentato di uno >>
            // Se il ++ fosse stato dopo *pLY allora non avrebbe funzionato. 
            ++*pLY;
            if(*pLY == 144){
                mode = 1;
                requestInterrupt(0);
            }else{
                mode = 2;
            }
        }
        break;
    case 1:
        if(modeClock >= 456){
            modeClock = 0;
            ++*pLY;
            if(*pLY > 153){
                mode = 2;
                *pLY = 0;
            }
        }
        break;
    }
}