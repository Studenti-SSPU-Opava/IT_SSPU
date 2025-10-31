# Příklad souboru v jazyce C

Tento soubor obsahuje ukázky kódu v jazyce C spolu s vysvětlením funkcí.

## Hello World

```c
#include <stdio.h>

int main() {
    // Výpis textu "Hello, World!" na standardní výstup.
    printf("Hello, World!\n");
    // Návratová hodnota 0 indikuje úspěšné provedení programu.
    return 0;
}
```

## Deklarace proměnných

```c
#include <stdio.h>

int main() {
    // Deklarace a inicializace celočíselné proměnné cislo.
    int cislo = 42;
    // Deklarace a inicializace desetinné proměnné desetinneCislo.
    float desetinneCislo = 3.14;
    // Deklarace a inicializace znakové proměnné znak.
    char znak = 'A';

    // Výpis hodnot proměnných na standardní výstup.
    printf("Cislo: %d\n", cislo);
    printf("Desetinne cislo: %f\n", desetinneCislo);
    printf("Znak: %c\n", znak);

    // Návratová hodnota 0 indikuje úspěšné provedení programu.
    return 0;
}
```

## Podmínky a smyčky

```c
#include <stdio.h>

int main() {
    // Inicializace celočíselné proměnné cislo.
    int cislo = 10;

    // Podmínka - provede se, pokud cislo je větší než 5.
    if (cislo > 5) {
        printf("Cislo je vetsi nez 5\n");
    } else {  // Jinak - provede se, pokud cislo není větší než 5.
        printf("Cislo neni vetsi nez 5\n");
    }

    // Smyčka for - vypíše hodnoty i od 0 do 4.
    for (int i = 0; i < 5; i++) {
        printf("Hodnota i: %d\n", i);
    }

    // Návratová hodnota 0 indikuje úspěšné provedení programu.
    return 0;
}
```

## Funkce v jazyce C

Funkce jsou klíčovým prvkem struktury programu v jazyce C. Slouží k organizaci kódu do samostatných bloků, které mohou být volány z jiných částí programu. Zde je vysvětlení některých klíčových prvků týkajících se funkcí v jazyce C:

1. **Deklarace a Definice:**
   - **Deklarace funkce:** Obsahuje název funkce, její návratový typ a parametry, ale neobsahuje samotný kód funkce.

     ```c
     // Deklarace funkce secti s parametry a, b a návratovým typem int.
     int secti(int a, int b);
     ```

   - **Definice funkce:** Obsahuje kód funkce, včetně těla a případných lokálních proměnných.

     ```c
     // Definice funkce secti, která sečte dva parametry a vrátí výsledek.
     int secti(int a, int b) {
         return a + b;
     }
     ```

2. **Návratový typ a Parametry:**
   - **Návratový typ:** Udává typ hodnoty, kterou funkce vrací.

   - **Parametry:** Jsou hodnoty, které může funkce přijmout.

3. **Volání Funkce:**
   - Funkce se volá pomocí jejího názvu, a předávají se jí hodnoty (argumenty), pokud má definované parametry.

     ```c
     // Volání funkce secti s argumenty 4 a 5 a přiřazení výsledku do proměnné vysledek.
     int vysledek = secti(4, 5);
     ```

4. **Lokální a Globální Proměnné:**
   - Proměnné definované v těle funkce jsou lokální.

   - Proměnné definované mimo funkce jsou globální.

5. **Rekurze:**
   - Funkce mohou volat samy sebe, což se nazývá rekurze.

     ```c
     // Rekurzivní funkce faktorial.
     int faktorial(int n) {
         if (n <= 1) {
             return 1;
         }
         return n * faktorial(n - 1);
     }
     ```

6. **Prototypy:**
   - Prototyp funkce je deklarace funkce bez jejího těla.

     ```c
     // Prototyp funkce secti, umožňuje kompilátoru předem vědět o existenci funkce.
     int secti(int a, int b);
     ```

Funkce umožňují strukturovat kód, zlepšují čitelnost a usnadňují znovupoužití kódu. Jejich správné používání je klíčové pro tvorbu efektivních a organizovaných programů v jazyce C.