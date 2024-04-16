# Xpository - Multi retro-console emulator.


<details>
  <summary>🗂️ Table of Contents</summary>
  <ol>
    <li><a href="#todo-todos">⚒️ TODO</a></li>
    <li><a href="#updates-up">📥 Updates</a></li>
        <ol>
            <li><a href="#started-110324-up1">1️⃣ First Update</a></li>
            <li><a href="#update-140424-up2">2️⃣ Second Update</a></li>
            <li><a href="#update-160424-up3">3️⃣ Third Update</a></li>
        </ol>
  </ol>
</details>

## TODO {#todos}

 - [x] CPU Base
 - [x] Memory 
    - Memory map
    - Read and write
 - [x] Cartridge read
    - Read header
    - Verify header
 - [x] Place everything into CPU.cpp
 - [ ] Graphics
    - OpenGL
    - Sprite Rendering
 - [ ] Fetch
    - Execute Instructions
 - [ ] Optimization
    - Optimize most of the code

## Updates {#up}
### Started 11/03/24 {#up1}

**ITALIAN** 🇮🇹

Progetto creato al fine di consegnarlo come *capolavoro* per la piattaforma
**Unica Istruzione**. L'idea del progetto sarebbe un programma che permette
di scaricare ed emulare giochi retrò in modo totalmente gratuito.

Per ora le risorse sono tutte impiegate sull'apprendimento e lo sviluppo
di un primo emulatore, quello per Gameboy™

**ENGLISH** 🇺🇸

Project created to be uploaded on the **Unica Istruzione** web site,
as part of the *capolavoro* school project. The base idead of the 
project is a program that lets you downloand and emulate games
from different retro consoles for free.

For now all resources are used to learn and develop the first emulator
that is for Gameboy™

---

### Update 14/04/24 {#up2}

**ITALIAN** 🇮🇹 

Dati gli svariati problemi con i launch.json e tasks.json 
vi forniamo gli *args* usati da noi durante lo sviluppo.
Pur essendo una soluzione primitiva e non scalabile,
e' il meglio che possiamo fare per ora.


**ENGLISH** 🇺🇸

Because of the many problems regarding launch.json and task.json
here are the *args* we used while developing.
Even if its primitive and not so scalable way of doing it, its the best
we have for the time being.

#### **LAUNCH.JSON**
```
{
    "version": "2.0.0",
    "configurations": [
        {
            "name": "Debug C/C++",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/main.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\Program Files (x86)\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe build all files"
        },
        {
            "name": "C/C++: g++.exe build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/main.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\Program Files (x86)\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe build active file"
        }
    ]
}
```
#### **TASKS.JSON -> Args** 
```
"args": [
            "-fdiagnostics-color=always",
            "-g",
            "${workspaceFolder}/cpp/cartridge.cpp",
            "${workspaceFolder}/cpp/graphics.cpp",
            "${workspaceFolder}/cpp/LR35902.cpp",
            "${workspaceFolder}/cpp/memory.cpp",
            "${workspaceFolder}/cpp/opcodes.cpp",
            "${workspaceFolder}/headers/cartridge.hpp",
            "${workspaceFolder}/headers/bus.hpp",
            "${workspaceFolder}/headers/graphics.hpp",
            "${workspaceFolder}/headers/LR35902.hpp",
            "${workspaceFolder}/headers/types.hpp",
            "${workspaceFolder}/headers/opcodes.hpp",
            "${workspaceFolder}/headers/memory.hpp",
            "${workspaceFolder}/main.cpp",
            "-o",
            "${workspaceFolder}/build/main.exe",
            "-I",
            "C:\\OpenGL\\glfw-3.4.bin.WIN64\\include",
            "-I",
            "C:\\OpenGL\\glad\\include",
            "-L",
            "C:\\OpenGL\\glfw-3.4.bin.WIN64\\lib-mingw-w64",
            "C:\\OpenGL\\glfw-3.4.bin.WIN64\\lib-mingw-w64\\libglfw3dll.a",
            "C:\\OpenGL\\glfw-3.4.bin.WIN64\\lib-mingw-w64\\glfw3.dll",
            "-lopengl32",
        ],
```

#### **C_CPP_PROPERTIES.JSON**
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:\\OpenGL\\glfw-3.4.bin.WIN64\\include",
                "C:\\OpenGL\\glad\\include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "C:/Program Files (x86)/mingw64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

---

### Update 16/04/24 {#up3}

### Come installare OpenGL (SOLO WINDOWS)

Qui di seguito troverete i passaggi per l'installazione di OpenGL e Glad.

1. Scaricare la libreria [GLFW](https://www.glfw.org/download.html) per OpenGL e cliccare su **64-bit Windows binaries**
2. Scaricare [Glad](https://glad.dav1d.de/). Sul sito selezionare i seguenti parametri
    - Language: C/C++
    - Specification: OpenGL
    - Profile: Core
    - API: 
        1. gl -> 3.3
        2. gles1 -> None
        3. gles2 -> None
        4. gles3 -> None
    - Options: spuntare *Generate a loader*
    - Infine cliccare **Generate**
3. Estrarre le cartelle nel seguente percorso, ovviamente creare la cartella apposita: 
    - C:\OpenGL\  
4. Per **Glad** estrarre le cartelle *include* e *src* dentro a una cartella chiamata **glad**
5. Inserire il file *glfw3.dll* nella stessa directory in cui viene buildato il programma *(.exe)*

L'albero delle cartelle dovrebbe assomigliare a questo
```
C:.
├───glad
│   ├───include
│   │   ├───glad
│   │   └───KHR
│   └───src
└───glfw-3.4.bin.WIN64
    ├───docs
    │   └───html
    │       └───search
    ├───include
    │   └───GLFW
    ├───lib-mingw-w64
    ├───lib-static-ucrt
    ├───lib-vc2013
    ├───lib-vc2015
    ├───lib-vc2017
    ├───lib-vc2019
    └───lib-vc2022
```

### How to install OpenGL (WINDOWS ONLY)

Here you'll find the steps to install OpenGL and Glad.

1. Download the [GLFW](https://www.glfw.org/download.html) library by clicking **64-bit Windows binaries**
2. Download [Glad](https://glad.dav1d.de/). In the site select the following parameters
    - Language: C/C++
    - Specification: OpenGL
    - Profile: Core
    - API: 
        1. gl -> 3.3
        2. gles1 -> None
        3. gles2 -> None
        4. gles3 -> None
    - Options: tick *Generate a loader*
    - Finally click on **Generate**
3. Extract the folders at the following location, obviously create the dedicated folder: 
    - C:\OpenGL\  
4. For **Glad** extract the *include* and *src* folders inside a newly created folder named **glad**
5. Copy the *glfw3.dll* file in the same directory that contains the built program *(.exe)*


The directory tree should look like this:
```
C:.
├───glad
│   ├───include
│   │   ├───glad
│   │   └───KHR
│   └───src
└───glfw-3.4.bin.WIN64
    ├───docs
    │   └───html
    │       └───search
    ├───include
    │   └───GLFW
    ├───lib-mingw-w64
    ├───lib-static-ucrt
    ├───lib-vc2013
    ├───lib-vc2015
    ├───lib-vc2017
    ├───lib-vc2019
    └───lib-vc2022
```


**The team**
Alessandro Landi @RehTrizZ
Ivan Casotti @Cyb3s
Alessandro Enzo Gori @AleBitCode
Joseph Portera @0hM1C1uf1