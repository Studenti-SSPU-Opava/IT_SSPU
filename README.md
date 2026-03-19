# 📚 Vítejte v tomto repozitáři!

V tomto repozitáři najdete vše, co jsme dělali ve škole, narazíte tu i na drobné studentské projekty, zápisy a podobně.<br>
Snažíme se tento repositář udělat vhodným místem pro studium a pro odkládání souborů, které by mohly sloužit i ostatním.

## 📖 Dokumentace a návody

### 📚 Wiki
Pro přehledné návody, příkazy a užitečné odkazy navštivte naši **[Wiki](https://github.com/Studenti-SSPU-Opava/IT_SSPU/wiki)** nebo prohlédněte soubory v adresáři [`wiki/`](wiki/).

Wiki obsahuje:
- **[Git příkazy](wiki/Git-Prikazy.md)** - Kompletní přehled Git příkazů
- **[Linux příkazy](wiki/Linux-Prikazy.md)** - Užitečné příkazy pro Linux
- **[Windows příkazy](wiki/Windows-Prikazy.md)** - Příkazy pro Windows
- **[Klávesové zkratky](wiki/Klavesove-Zkratky.md)** - Jak psát speciální znaky
- **[Užitečné odkazy](wiki/Uzitecne-Odkazy.md)** - Tutoriály a validátory

### 💡 Jak provádět commity
mělo být přidáno později, jaksi nïkdo nemá čas i chuť, takže smolík

### 📋 Návod k commitování
Pravděpodobně taky nebude

### 🌐 Zobrazovač html souborů
[https://studenti-sspu-opava.github.io/IT_SSPU/](https://studenti-sspu-opava.github.io/IT_SSPU/)

<br>

# CHANGELOG:
<br>



## CHANGELOG

Níže je detailnější, verzovaný přehled hlavních změn — přehled je zaměřený na to, co bylo přidáno, změněno nebo opravováno. Neměním dřívější obsah repozitáře, pouze přeskupuji záznamy do přehlednějších verzí.

### Unreleased / v6.1 (work in progress)

Added
- Přidán nový C++ projekt "kružnice" ve složce s příklady (otevřený PR #57) — připravené zdrojové soubory a konfigurace pro VS Code.
- Přidán `tasks.json` pro snadnější spuštění/kompilaci některých projektů v editoru.

Changed
- Normalizace názvů složek a souborů (odstraněna diakritika a mezery) → sjednocení na `1_rocnik`, `2_rocnik`, `3_rocnik` a související úpravy odkazů a zobrazení.
- Upraveny cesty a odkazy pro zobrazení webových souborů (lepší kompatibilita s GitHub Pages a lokálním náhledem).

Fixed
- Opraveny GitHub Actions workflow (yaml indentace, odstranění neexistujících balíčků, přidání `-y` pro `apt-get`, odstranění nespolehlivých kroků). Výsledkem jsou stabilnější CI běhy.
- Opraveny shell skripty v rámci klonovaného Flask projektu (citování proměnných, direktivy pro ShellCheck, spouštěcí skripty pro gunicorn).

Notes
- Hromadné přeformátování a drobné úpravy dokumentace/souborů napříč repo; některé doplněné příklady v C/Python.

### v6.0 (stabilní vydání)

Added
- Workflow pro publikaci statických webových souborů na GitHub Pages.
- Zobrazovač HTML stránek pro snadné prohlížení (projekt nasazen na GitHub Pages).

Changed
- Struktura repozitáře upravena tak, aby byla přehlednější pro více ročníků (přesun souborů do složek podle ročníků).

Fixed
- Menší opravy odkazů a konfigurací pro správné zobrazení webových stránek.

### v5.0

Added
- Základní GitHub Actions workflow pro jazyky a nástroje používané v repozitáři (C, Python, Bash, statické HTML ověření).
- Soubory s ukázkami a prověrkami pro 2. ročník a další materiály.

Changed
- Přeorganizování materiálů do tematických složek a zlepšení navigace v repozitáři.

### v4.0 (historie)

Added
- .gitignore a počáteční sady příkladů (C, dokumenty Word -> MD konverze atd.).

Changed
- Přejmenování repozitáře a drobné organizační změny — doporučení práce přes větve + PR proces.

### Starší záznamy (shrnutí)

- V průběhu roku byly do repozitáře průběžně přidávány příklady z programování, materiály k OS, návody (např. jak na Home Assistant, Wordpress s Nginx), a soubory z hodin (úlohy/projekty). Tyto záznamy najdete v historických PR v GitHubu.

