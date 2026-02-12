# Jak spustit projekt (zlomek)

Předpoklad: Ubuntu, g++ nainstalován.

Tento projekt je připravený bez zdrojových kódů. Skript kompilace se chová
milostivě: pokud v adresáři nejsou žádné `*.cpp` soubory, pouze vypíše
informaci a ukončí se úspěšně.

## VS Code (tasks)
1. Stáhněte repozitář:  
   `git clone <repo-url> && cd <repo-folder>`
2. Otevřete složku ve VS Code. `.vscode/tasks.json` už obsahuje úlohu pro `zlomek`.
3. Spuštění: Terminal → Run Task... → Build and Run zlomek

## Ručně v terminálu
```bash
cd 3_rocnik/Programovani/Cpp/Priklady/zlomek
bash ./compile.sh
```

Po přidání souborů (např. `main.cpp`) se skript pokusí projekt přeložit a spustit `./main`.
