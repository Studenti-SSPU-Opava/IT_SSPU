# Jak spustit projekt (kruznice)

Předpoklad: Ubuntu, g++ nainstalován.

## VS Code (tasks)
1. Stáhněte repozitář:  
    git clone <repo-url> && cd <repo-folder>
2. Otevřete složku ve VS Code. `.vscode/tasks.json` je už v repu.
3. Spuštění: Terminal → Run Task... → build kruznice project
## CLion / CMake — správné připojení knihoven

- CLion obvykle vytvoří `CMakeLists.txt` automaticky. Pro správné připojení knihoven upravte tento soubor.
```cmake
cmake_minimum_required(VERSION 3.31)
project(Buffer C)

set(CMAKE_C_STANDARD 11)

add_executable(Buffer
    main.c
    bod.h
    bod.cpp
    kruznice.h
    kruznice.cpp
)
```

- Po změně CMake souboru: CLion obvykle provede automatické reloadování CMake; pokud ne, klikněte na "Reload CMake" nebo použijte tlačítko v horním panelu.
- Spuštění: v CLion vyberte vytvořenou run konfiguraci (CLion najde target z `CMakeLists.txt`) a stiskněte Run/Debug.

