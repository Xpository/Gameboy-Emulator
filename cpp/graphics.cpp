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


Graphics::Graphics(){
    initGraphics();

    fragmentShader = loadShaderSource("shaders/shader.frag");
    vertexShader = loadShaderSource("shaders/shader.vert");
    
    for (int i = 0; i < 160; i++){
        for(int j = 0; j < 144; j++){
            screenMatrix[i][j] = 0x00;
        }
    }
    
}



Byte* Graphics::toArrayScreenMatrix() {
    Byte* screenArray = new Byte[160 * 144 * 3]; 

    int aI = 0;
    for (int y = 0; y < 144; ++y) {
        for (int x = 0; x < 160; ++x) {
            Byte grayValue = screenMatrix[x][y];
            screenArray[aI++] = grayValue; // R
            screenArray[aI++] = grayValue; // G
            screenArray[aI++] = grayValue; // B
        }
    }

    return screenArray;
}
void Graphics::RenderImageFromScreenMatrix() {
    Byte* arrayiedMatrix = toArrayScreenMatrix();

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, arrayiedMatrix);
    
    GLuint shaderProgram = LoadShaders(fragmentShader, vertexShader);
    glUseProgram(shaderProgram);

    // Definisci i vertici del quadrato e le coordinate della texture
    float vertices[] = {
        // Posizioni    // Coordinate della texture
        -1.0f,  1.0f,  0.0f, 1.0f, // Top-Left
        -1.0f, -1.0f,  0.0f, 0.0f, // Bottom-Left
         1.0f, -1.0f,  1.0f, 0.0f, // Bottom-Right
         1.0f,  1.0f,  1.0f, 1.0f  // Top-Right
    };

    unsigned int indices[] = {
        0, 1, 2, // Primo triangolo
        0, 2, 3  // Secondo triangolo
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posizioni
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Coordinate della texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Ciclo di rendering
    while (!glfwWindowShouldClose(window)) {
        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        // Usa il programma shader
        glUseProgram(shaderProgram);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Renderizza il quadrato
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Scambia i buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);

    delete[] arrayiedMatrix; // Libera la memoria allocata per l'array
}
