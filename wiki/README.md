# Wiki Directory

Tento adresář obsahuje organizovaný obsah pro GitHub Wiki.

## 📋 Obsah

Všechny soubory v tomto adresáři jsou připravené k nahrání na GitHub Wiki:

- **Home.md** - Hlavní stránka wiki s přehledem obsahu
- **Git-Prikazy.md** - Kompletní přehled Git příkazů
- **Linux-Prikazy.md** - Přehled Linux příkazů
- **Windows-Prikazy.md** - Přehled Windows příkazů
- **Klavesove-Zkratky.md** - Jak psát speciální znaky
- **Uzitecne-Odkazy.md** - Užitečné odkazy na tutoriály a nástroje

## 🚀 Jak nahrát na GitHub Wiki

### Metoda 1: Přes webové rozhraní
1. Přejděte na https://github.com/Studenti-SSPU-Opava/IT_SSPU/wiki
2. Klikněte na "Create the first page" nebo "New Page"
3. Zkopírujte obsah z odpovídajícího .md souboru
4. Dejte stránce správný název (např. "Git Prikazy")
5. Uložte stránku

### Metoda 2: Git clone wiki repozitáře
GitHub Wiki je samostatný git repozitář. Můžete ho naklonovat a pushovat změny:

```bash
# Klonovat wiki repozitář
git clone https://github.com/Studenti-SSPU-Opava/IT_SSPU.wiki.git

# Zkopírovat soubory z tohoto adresáře
cp wiki/*.md IT_SSPU.wiki/

# Commitnout a pushnout
cd IT_SSPU.wiki
git add .
git commit -m "Přidání reorganizovaného obsahu"
git push
```

## 📝 Po nahrání na Wiki

Po úspěšném nahrání obsahu na GitHub Wiki můžete zvážit odstranění následujících souborů z hlavního repozitáře (jsou už na wiki):
- `kodyPrikazy.md`
- `uzitecneOdkazy.md`
- `klavesoveZkratky.md`

A nahradit je odkazem na wiki v README.md.

## 🔄 Údržba

Pokud budete provádět změny:
1. Upravte soubory v tomto adresáři
2. Nahrajte změny na GitHub Wiki (viz metody výše)
3. Commitněte změny v tomto repozitáři pro zachování verzí
