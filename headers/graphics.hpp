#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "types.hpp"
#include "LR35902.hpp"

class Graphics{
    private:
        /* @brief Funzione che inizializza OpenGL
         * 
         * La funzione chiama glfwInit() e glfwWindowHint() impostando come versione la 3
         * Poi inizializza il puntatore "GLFWwindow* window" con una finestra 800x600
         * Ed infine setta la grandezza della viewport a 160x144 cioè quella dello schermo
         * del Gameboy
         * 
         * @note E' presente una linea commentata che consiste nel set della callback 
         * per il resize
        */
        void initGraphics();

        // Puntatore inizializzato nel costruttore
        // Conterra sempre il valore del registro LY 
        // Presente in memory.cpp/hpp
        Byte* pLY;

        // Counter dei clock per cambiare modalita
        int modeClock;
        // Contatore per la modalità (si potrebbe usare un enum?)
        int mode;
        // Puntatore alla memoria in caso di accesso (Ce ne saranno tanti)
        Memory* mem;
    public:
        Graphics(Memory);

        /* @brief Funzione che simula le diverse modalità della GPU/PPU
         * 
         * Incrementa il contatore interno del clock ed in base al suo valore esegue una 
         * delle possibili mode (o fasi) del rendering.            
         * - 2) Scan for OBJ 
         * - 3) Send pixels
         * - 0) Wait for end of the scanline
         * - 1) Wait for next frame
         * 
         * @param cycles il numero di cicli eseguiti
         * @attention Funzione incompleta e soggetta a possibile cambiamenti
        */
        void Update(int);

        /* @brief Funzione che renderizza la linea in base al registro LY
         * 
         * Carica valori nella matrice
         * 
         * @attention Per ora carica solamente bianchi e neri alternati non implementata del tutto
        */
        void renderCurrentScanline();

        // Funzione ancora non implementata
        void requestInterrupt(int);
        // Funzione non implementata interamente
        void RenderScreen();

        /* @brief Funzione che aggiorna la matrice.
         * 
         * Dato il dato con cui aggiornare la matrice e le coordinate
         * X e Y viene aggiornata. 
         * 
         * @param tileData Byte che rappresenta il valore da inserire
         * @param x Colonna in cui inserire il dato
         * @param y Riga in cui inserire il dato
         * 
         * @deprecated Non so minimamente perche questa funzione esista dato
         * che screenMatrix è pubblico
        */        
        void updateMatrix(Byte, Byte, Byte);

        /* @brief Funzione che carica la shader da un file e la ritorna sottoforma
         * di stringa c++.
         * 
         * @param filepath Il percorso al sorgente della shader 
        */  
        std::string loadShaderSource(const char*);

        // Puntatore alla finestra
        GLFWwindow* window;

        // Le shader da mettere poi nel programma
        std::string vertexShader;
        std::string fragmentShader;

        // La matrice che definisce lo schermo
        Byte screenMatrix[160][144];


};