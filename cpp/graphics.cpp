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

	
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

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


Graphics::Graphics(){
    initGraphics();

    fragmentShader = loadShaderSource("shaders/shader.frag");
    vertexShader = loadShaderSource("shaders/shader.vert");
    
}


void Graphics::RenderImageFromArray(Byte * gameboyScreenData)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, gameboyScreenData);

    GLuint shaderProgram = LoadShaders(fragmentShader, vertexShader);
}