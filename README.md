# Xpository - Multi retro-console emulator.

### Started 11/03/24

**ITALIAN** 🇮🇹

Progetto creato al fine di consegnarlo come *capolavoro* per la piattaforma
**Unica Istruzione**. L'idea del progetto sarebbe un programma che permette
di scaricare ed emulare giochi retrò in modo totalmente gratuito.

Per ora le risorse sono tutte impiegate sull'apprendimento e lo sviluppo
di un primo emulatore, quello per Gameboy™

**ENGLISH** 🇺🇸

Progect creato to be uploaded on the **Unica Istruzione** web site,
as part of the *capolavoro* school project. The base idead of the 
project is a program that lets you downloand and emulate games
from different retro consoles for free.

For now all resources are used to learn and develop the first emulator
that is for Gameboy™

---

### Update 14/04/24

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

**LAUNCH.JSON**
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
**TASKS.JSON -> Args** 
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
            "${workspaceFolder}/build/main.exe"
        ],
```
